#include "Hxditr.hpp"
#include <cstdlib>
#include <fstream>
#include <ios>
#include <stdexcept>
#include <filesystem>

HX::ditr::ditr(const char* szFile) {
    // There is no way to communicate that file was invalid so we are throwing.
    if (!SetFile(szFile))
        throw std::runtime_error("File was invalid");
}

HX::ditr::~ditr() {
    if (m_pFile)
        free(m_pFile);
}

bool HX::ditr::SetFile(const char* szFile) {
    using fstrm = std::ifstream;
    using std::filesystem::file_size;

    // Open the file
    fstrm inFile = fstrm(szFile, std::ios::binary | std::ios_base::in);
    if (!inFile.is_open())
        return  false;
    
    // Get file size
    m_uFileSize = file_size(szFile);

    // Create buffer for the binary data
    m_pFile = (HX::Byte*)malloc(sizeof(HX::Byte) * m_uFileSize);

    // Read the file in to the buffer
    inFile.read(reinterpret_cast<char*>(m_pFile), m_uFileSize);
    
    return true;
}

void HX::ditr::Move(const HX::MoveDirection& md, const uint32_t& amount) {
    int8_t directionalMul = 1;
    uint64_t newPos;

    switch (md) {
    case HX::MoveDirection::Left:
        directionalMul = -1;
        [[fallthrough]];
    case HX::MoveDirection::Right:   
        newPos = m_uCurrentFilePos + (directionalMul * amount);
        break;

    case HX::MoveDirection::Up:
        directionalMul = -1;
        [[fallthrough]];
    case HX::MoveDirection::Down:
        newPos  = m_uCurrentFilePos + (directionalMul * amount * this->GetCurUiWidth());
        break;

#ifdef _DEBUG
    default:
        throw std::runtime_error("Error: MoveDirection enum in HX::ditr::Move() is outside of scope");
#endif // _DEBUG
    }

    // Only asign new position if it's in boundries of file size and it didn't 
    // overflow.
    if (newPos < m_uFileSize)
        m_uCurrentFilePos = newPos;
}

uint32_t HX::ditr::GetCurUiWidth() {
    return -1;
}

int main(int argc, char* argv[]) {
    using namespace std;
    using fstrm = std::fstream;

    // Decide if passed arguments are viable
    if (argc < 2 ||
        // strcmp() returns 0 if strings are identical
        !strcmp(argv[1], "--help") ||
        !strcmp(argv[1], "-h") ||
        !fstrm(argv[1]).is_open()) {
        
        cout << "Passed argument is invalid." << endl
             << endl
             << "Use: " << endl
             << "   Hx3ditr [Path to a file]" << endl;

        // In debug version, we don't care if any arguments has been passed.
        // Clear the screen and proceed anyway.
#ifdef _DEBUG
        HX::ConsoleOut::Clear();
#else
        return 1;
#endif // !_DEBUG
    }

    HX_DBG_PRT_N("Program was started with following arguments: ");
    HX_DBG_PRT_FE(argv, argc);

    // Initialize variables
    std::shared_ptr<HX::ditr> myDitrPtr = std::make_shared<HX::ditr>();
    HX::ConsoleOut myOut = HX::ConsoleOut();
    HX::InputThread myIn = HX::InputThread(myDitrPtr);
  
#ifdef _DEBUG
    if (myDitrPtr->SetFile("../TestFile.txt")) {
        HX_DBG_PRT_N("Sucessfully opened the test file");
    }
    else {
        HX_DBG_PRT_N("Failed to open the test file");
    }
#endif // _DEBUG

    // Enter the main loop
    while (!myIn.Exit()) {
        // Update ui objects queued for output
        myOut.Update();

        // Repaint output
        myOut.Clear();
        myOut.Paint();
    }

    // Clean up

    return 0;
}


