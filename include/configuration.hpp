#ifndef __CONFIGURATION_HPP__
#define __CONFIGURATION_HPP__

/**
 * @file configuration.cpp
 *
 * @brief Configuration class to hold the contents of the application configuration TOML file
 *
 * @author EquiLend
 * Contact: Dharm Kapadia <dharm.kapadia@equilend.com>
 *
 */

#include <iostream>
#include <string>

#include "toml.hpp"

using namespace std;
using namespace std::string_view_literals;

/**
 * Configuration class
 *
 * Configuration class reads the TOML file which contains
 * the configurations for the application.
 *
 */
class Configuration
{
private:
    string filename;
    toml::table tbl;

    std::optional<std::string> auth_url;
    std::optional<std::string> realm_name;

    std::optional<std::string> events;
    std::optional<std::string> parties;
    std::optional<std::string> agreements;
    std::optional<std::string> contracts;
    std::optional<std::string> rerates;
    std::optional<std::string> returns;
    std::optional<std::string> recalls;
    std::optional<std::string> buyins;
    std::optional<std::string> delegations;

    std::optional<std::string> auth_type;
    std::optional<std::string> grant_type;
    std::optional<std::string> client_id;
    std::optional<std::string> username;
    std::optional<std::string> password;
    std::optional<std::string> client_secret;

public:
    // Constructor
    Configuration(string filename);

    // Read in configuration from TOML file
    int readConfiguration();

    string getAuthURL();
    string getRealmName();

    string getEventsEndpoint();
    string getPartiesEndpoint();
    string getAgreementsEndpoint();
    string getContractsEndpoint();
    string getReratesEndPoint();
    string getReturnsEndPoint();
    string getRecallsEndPoint();
    string getBuyinsEndPoint();
    string getDelegationsEndPoint();

    string getAuthType();
    string getGrantType();
    string getClientId();
    string getUsername();
    string getPassword();
    string getClientSecret();
};

#endif
