cmake_minimum_required (VERSION 3.8)

# Enable Hot Reload for MSVC compilers if supported.
if (POLICY CMP0141)
  cmake_policy(SET CMP0141 NEW)
  set(CMAKE_MSVC_DEBUG_INFORMATION_FORMAT "$<IF:$<AND:$<C_COMPILER_ID:MSVC>,$<CXX_COMPILER_ID:MSVC>>,$<$<CONFIG:Debug,RelWithDebInfo>:EditAndContinue>,$<$<CONFIG:Debug,RelWithDebInfo>:ProgramDatabase>>")
endif()

project("Hx3ditr")

set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/../Lib)
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/../Lib)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/../Bin)

add_executable(Hx3ditr
    Source/ConsoleOutput.cpp 
    Source/ConsoleOutput.hpp
    Source/UserInput.cpp
    Source/UserInput.hpp
    Source/Hxditr.cpp
    Source/Hxditr.hpp)

if (CMAKE_VERSION VERSION_GREATER 3.12)
    set_property(TARGET Hx3ditr PROPERTY CXX_STANDARD 20)
endif()

if(MSVC)
	target_compile_options(Hx3ditr PRIVATE /W4 /WX)
else()
	target_compile_options(Hx3ditr PRIVATE -Wall -Wextra -Wpedantic -Werror)
endif()

target_compile_definitions(Hx3ditr PRIVATE
    $<$<CONFIG:Debug>:
        _DEBUG
    >
)
