# 1Source-CPP

Demonstration code which accesses the 1Source REST API in a command-line C++ program

## Description

This project provides sample code and a template for accessing the 1Source REST API in C++. The code runs as a command-line program which utilizes switch to exercise the various API endpoints.

To view sample code in Python, Java, and JavaScript, please see the following GitHub repository:

https://github.com/Equilend/1source-api

## Getting Started

### Dependencies

* A C++ compiler: gcc/clang (c++17) is recommended but other c++ compilers might work
* CMake
* All other feature dependencies are included in the projects as self-contained .hpp files (JSON, logger, TOML, etc.)
* Visual Studio Code or equivalent C++ IDE/environment


### Installing

Get the code locally from GitHub with the following command:
```
> git clone https://github.com/dharm-kapadia/1source-cpp
> cd 1source-cpp
```

### Compiling/Building the program

If the code directory is opened in Visual Studio Code (or equivalent), open a Terminal from the menu View -> Terminal (Ctrl+`)

In the terminal, make sure you are in the 1source-cpp root directory. Enter the following command:
```
> cmake CMakeLists.txt
```
After a successful build, an "output" directory will be created in the 1source-cpp root dir with the compiled program

### Executing program

* How to run the program
* Step-by-step bullets
```
code blocks for commands
```

## Help

Any advise for common problems or issues.
```
command to run if program contains helper info
```

## Authors

Contributors names and contact info

[@Dharm Kapadia](dharm.kapadia@equilend.com)

## Version History

* 0.1
    * Initial Release

## Acknowledgments

* [argparse](http://github.com/p-ranav/argparse)
* [JSON for Modern C++](https://github.com/nlohmann/json)
* [tomlplusplus](https://github.com/marzer/tomlplusplus)
