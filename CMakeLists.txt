# CMakeList.txt : CMake project for 1source, include source and define
# project specific logic here.
#
cmake_minimum_required (VERSION 3.16)

# Enable Hot Reload for MSVC compilers if supported.
if (POLICY CMP0141)
  cmake_policy(SET CMP0141 NEW)
  set(CMAKE_MSVC_DEBUG_INFORMATION_FORMAT "$<IF:$<AND:$<C_COMPILER_ID:MSVC>,$<CXX_COMPILER_ID:MSVC>>,$<$<CONFIG:Debug,RelWithDebInfo>:EditAndContinue>,$<$<CONFIG:Debug,RelWithDebInfo>:ProgramDatabase>>")
endif()

project (1source VERSION 1.0)

# Add source to this project's executable.
add_executable (1source 1source.cpp 1source.hpp configuration.cpp   )

if (CMAKE_VERSION VERSION_GREATER 3.12)
  set_property(TARGET 1source PROPERTY CXX_STANDARD 20)
endif()

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_BUILD_TYPE debug)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++20")

# Add external libraries here

include(FetchContent)

FetchContent_Declare(cpr GIT_REPOSITORY https://github.com/libcpr/cpr.git
        GIT_TAG 6b3e3531d3e5781b4b19e7cf64ed76035bf59d37)

FetchContent_Declare(fmt GIT_REPOSITORY https://github.com/fmtlib/fmt.git
        GIT_TAG 05dda9490ddd5cb89db5f5b8ec85a399d5945deb)

FetchContent_MakeAvailable(cpr fmt)

target_link_libraries(1source PRIVATE cpr fmt)

 
# TODO: Add tests and install targets if needed.
