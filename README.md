# 1Source-CPP

Demonstration code which accesses the 1Source REST API in a command-line C++ program

## Description

This project provides sample code and a template for accessing the 1Source REST API in C++. The code runs as a command-line program which utilizes switch to exercise the various API endpoints.

To view sample code in Python, Java, and JavaScript, please see the following GitHub repository:

https://github.com/Equilend/1source-api

## Getting Started

### Dependencies

* A C++ compiler: gcc/clang (c++20 or greater) is recommended but other c++ compilers might work, such as Visual C++.
* CMake
* All other feature dependencies are included in the projects as self-contained .hpp files (cpr, fmt, JSON, logger, TOML, etc.)
* OpenSSL libraries => openssl, openssl-libs, openssl-devel

In Fedora, the OpenSSL libraries are installed with the following command:
```
> sudo dnf install openssl openssl-libs openssl-devel
```

### Installing

Clone the code repository locally from GitHub with the following command:
```
> git clone https://github.com/dharm-kapadia/1source-cpp
> cd 1source-cpp
```

### Creating the Build files

If the code directory is opened in Visual Studio Code (or equivalent), open a Terminal from the menu View -> Terminal (Ctrl+`). Or, the build commands can be entered from a standard BASH terminal.

In the terminal, make sure you are in the 1source-cpp root directory. Enter the following command:
```
> cmake .
```
This will execute a script to create the necessary CMake artifacts needed for the subsequent build.
* It will also create "_deps" and "CMakeFiles" subdirectories.
* The logs for this process are located in the CMakeFiles/CMakeError.log and CMakeFiles/CMakeOutput.log files.
 
If the script is successful, it will output the following few lines in the terminal similar to:
```
-- Configuring done (35.8s)
-- Generating done (0.4s)
-- Build files have been written to: /<dir>/1source-cpp
```

### Compiling/Building the program
Once the Build files have been created, enter the following in the terminal to actually build the 1source executable:
```
> cmake --build .
```

If the build is successful, it will output the following few lines in the terminal similar to:
```
[100%] Linking C shared library libz.so
[100%] Built target zlib
```
After a successful build, an executable file called '1source' will be created in the 1source-cpp root directory. There will also be residual files and directiories created as part of the cmake and build process.

### Executing program

The 1source application can be run directly from the command line in the terminal after it is successfully built. The following comman will run the application:

```
> ./1source
```

The output of that will show the command line options available:

```
1source-cpp> ./1source
-t: required.
Usage: 1Source [--help] [--version] -t VAR [-o VAR] [-a VAR] [-e VAR] [-c VAR] [-p VAR]

Optional arguments:
  -h, --help     shows help message and exits
  -v, --version  prints version information and exits
  -t             1Source configuration TOML file [required]
  -o             1Source API Endpoint to query [agreements, contracts, events, parties ]
  -a             1Source API Endpoint to query trade agreements by agreement_id
  -e             1Source API Endpoint to query events by event_id
  -c             1Source API Endpoint to query contracts by contract_id
  -p             1Source API Endpoint to query parties by party_id
```

The '-t' command line parameter specifies the application TOML configuration file and is required, even if no other command line parameters are included.

The default TOML configuration file is called 'configuration.toml' and is included in the respoitory.

```
1source-cpp> ./1source -t configuration.toml

```

The 1Source REST API can return the following entities:
* events
* parties
* agreements
* contracts

#### Events
To retrieve all events which the user is authorized to view, the following command will do so:

```
1source-cpp> ./1source -t configuration.toml -o events
```

The output of the command to retrieve events will be a JSON response from the 1Source REST API similar to:
```
1Source events
==============
[
  {
    "eventDateTime": "2023-11-02T13:42:16.049Z",
    "eventId": 10012358,
    "eventType": "TRADE",
    "resourceUri": "/v1/ledger/agreements/2cf9d8cc-2b77-49bf-8bb2-9956aaf9cf97"
  },

  .
  .
  .

  {
    "eventDateTime": "2023-11-02T11:00:05.436Z",
    "eventId": 10012335,
    "eventType": "TRADE",
    "resourceUri": "/v1/ledger/agreements/ed0b656e-6931-4b85-b5be-1bbe6b71b099"
  }
]
```

The REST API can be queried for a particular event with an event_id
```
1source-cpp> ./1source -t configuration.toml -e 10012349
```

The expected response for that call would be similar to:
```
1Source event
=============
{
  "eventDateTime": "2023-11-02T11:00:11.448Z",
  "eventId": 10012349,
  "eventType": "TRADE",
  "resourceUri": "/v1/ledger/agreements/d7f0cf8d-2c8f-4741-bf4c-3e793b67a0ee"
}
```

#### Parties
Similar to the Events call, to retrieve all parties which the user is authorized to view, the following command will do so:

```
1source-cpp> ./1source -t configuration.toml -o parties
```

The REST API can be queried for a particular party with a party_id
```
1source-cpp> ./1source -t configuration.toml -p XXXX-US
```

#### Agreements
Similar to the Events call, to retrieve all agreements which the user is authorized to view, the following command will do so:

```
1source-cpp> ./1source -t configuration.toml -o agreements
```

The REST API can be queried for a particular agreement with an agreement_id
```
1source-cpp> ./1source -t configuration.toml -a 56e7a7fb-309b-4f49-b92f-b789b37e3f07
```

#### Contracts
Similar to the Events call, to retrieve all contracts which the user is authorized to view, the following command will do so:

```
1source-cpp> ./1source -t configuration.toml -o contracts
```

The REST API can be queried for a particular contract with a contract_id
```
1source-cpp> ./1source -t configuration.toml -c c2098d72-89c0-49f7-829a-e9
```

### Configuration TOML Specification
The 1source command-line application reads data from a configuration file in TOML format. The file contains information required for the application to connect to the 1Source REST API, the individual endpoints, and the authentication details. The TOML file reflects that by have 3 required sections
* general
* endpoints
* authentication

Of the 3 sections, only a few of the attributes in the authentication section should be changed by the user. The rest should be left as-is unless otherwise instructed.

#### General

This section contains one key/value pair, that of the 1Source REST API "auth_url." This endpoint is for user login authentication and retrieval of the auth token on successful login. That auth token is required on subsequent calls to the 1Source REST API.

This values should not be changed by the user unless otherwise instructed.

#### Endpoints
This section contains key/value pairs related to the 1Source REST API endpoints for events, parties, agreements, and contracts. These values should not be changed by the user unless otherwise instructed.

#### Authentication
This section contains key/value pairs related to the 1Source REST API login authentication (username, password, etc.)

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
