#include "Hxditr.hpp"

int main(int argc, char* argv[]) {
    using namespace std;
    using fstream = std::fstream;

    // Decide if passed arguments are viable
    if (argc < 2 ||
        // strcmp() returns 0 if strings are identical
        !strcmp(argv[1], "--help") ||
        !strcmp(argv[1], "-h") ||
        !fstream(argv[1]).is_open()) {
        
        cout << "Passed argument is invalid." << endl
             << endl
             << "Use: " << endl
             << "   Hx3ditr [Path to a file]" << endl;

#ifndef _DEBUG
        return 1;
#endif // !_DEBUG
    }

    // Initialize variables
    std::shared_ptr<HX::ditr> pDitr = std::make_shared<HX::ditr>();
    HX::ConsoleOut out = HX::ConsoleOut();
    HX::InputThread it = HX::InputThread(pDitr);

    // Enter the main loop
    while (!it.Exit()) {

    }

    // Clean up

    return 0;
}