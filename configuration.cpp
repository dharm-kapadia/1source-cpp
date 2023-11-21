#include "include/configuration.hpp"

using namespace std;

Configuration::Configuration(string filename)
{
    this->filename = filename;
}

/**
 * Read and parse the contents of the TOML file using tomlplusplus:
 *
 * https://marzer.github.io/tomlplusplus/
 *
 * Return an error if the file cannot be read or any other TOML errors
 *
 * @param None
 */
int Configuration::readConfiguration()
{
    try
    {
        tbl = toml::parse_file(this->filename);
    }
    catch (const toml::parse_error &err)
    {
        std::cerr << "Parsing project TOML file '" << this->filename << "' failed : \n"
                  << err << "\n";
        return 1;
    }

    // Get config data out of the TOML file
    this->auth_url = tbl["general"]["auth_url"].value<string>();
    this->realm_name = tbl["general"]["realm_name"].value<string>();

    this->events = tbl["endpoints"]["events"].value<string>();
    this->parties = tbl["endpoints"]["parties"].value<string>();
    this->agreements = tbl["endpoints"]["agreements"].value<string>();
    this->contracts = tbl["endpoints"]["contracts"].value<string>();
    this->rerates = tbl["endpoints"]["rerates"].value<string>();
    this->returns = tbl["endpoints"]["returns"].value<string>();
    this->recalls = tbl["endpoints"]["recalls"].value<string>();
    this->buyins = tbl["endpoints"]["buyins"].value<string>();

    this->auth_type = tbl["authentication"]["auth_type"].value<string>();
    this->grant_type = tbl["authentication"]["grant_type"].value<string>();
    this->client_id = tbl["authentication"]["client_id"].value<string>();
    this->username = tbl["authentication"]["username"].value<string>();
    this->password = tbl["authentication"]["password"].value<string>();
    this->client_secret = tbl["authentication"]["client_secret"].value<string>();

    return 0;
}

string Configuration::getAuthURL()
{
    return *this->auth_url;
}

string Configuration::getRealmName() {
    return *this->realm_name;
}

string Configuration::getEventsEndpoint()
{
    return *this->events;
}

string Configuration::getPartiesEndpoint()
{
    return *this->parties;
}

string Configuration::getAgreementsEndpoint()
{
    return *this->agreements;
}

string Configuration::getContractsEndpoint()
{
    return *this->contracts;
}

string Configuration::getReratesEndPoint()
{
    return *this->rerates;
}

string Configuration::getReturnsEndPoint()
{
    return *this->returns;
}

string Configuration::getRecallsEndPoint()
{
    return *this->recalls;
}

string Configuration::getBuyinsEndPoint()
{
    return *this->buyins;
}

string Configuration::getAuthType()
{
    return *this->auth_type;
}

string Configuration::getGrantType()
{
    return *this->grant_type;
}

string Configuration::getClientId()
{
    return *this->client_id;
}

string Configuration::getUsername()
{
    return *this->username;
}

string Configuration::getPassword()
{
    return *this->password;
}

string Configuration::getClientSecret()
{
    return *this->client_secret;
}
