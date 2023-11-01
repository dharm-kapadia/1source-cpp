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

# Add external libraries here
include(FetchContent)
FetchContent_Declare(cpr GIT_REPOSITORY https://github.com/libcpr/cpr.git
        GIT_TAG 0817715923c9705e68994eb52ef9df3f6845beba) # The commit hash for 1.10.x. Replace with the latest from: https://github.com/libcpr/cpr/releases
FetchContent_MakeAvailable(cpr)

target_link_libraries(1source PRIVATE cpr::cpr)

# TODO: Add tests and install targets if needed.
