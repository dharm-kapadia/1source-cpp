﻿#include <iostream>
#include <string>

#include "1source.hpp"
#include <cpr/cpr.h>

#include "include/argparse.hpp"
#include "include/logger.hpp"
#include "include/json.hpp"
#include "include/toml.hpp"
#include "include/argparse.hpp"
#include "include/configuration.hpp"

using namespace std;
using namespace cpr;
using namespace string_view_literals;

using json = nlohmann::json;

// Create a logger for the application
Logger logger = Logger("1source.log");

/**
 * Gets the Auth token from 1Source
 *
 * @param config Configuration object which contains the details from the TOML file
 *
 * @return auth_token or ""
 */
string getAuthToken(Configuration config)
{
    // Get the auth token
    logger.INFO("Getting AUTH token");

    Response r = Post(Url{config.getAuthURL()},
                      Bearer{config.getAuthType()},
                      Payload{
                          {"grant_type", config.getGrantType()},
                          {"client_id", config.getClientId()},
                          {"username", config.getUsername()},
                          {"password", config.getPassword()},
                          {"client_secret", config.getClientSecret()}});

    string auth_token = "";
    json resp;

    // Get the HTTP return status
    if (r.status_code == 200)
    {
        logger.INFO("Successfully retrieved AUTH token from 1Source API");

        resp = json::parse(r.text);

        // Extract auth_token
        logger.INFO("Extract AUTH token from response");
        auth_token = resp["access_token"];
    }
    else
    {
        logger.ERR("Error retrieving AUTH token from 1Source API");
        cout << "Error retrieving AUTH token from 1Source API" << endl;
        exit(10);
    }

    return auth_token;
}

/**
 * Outputs the response from the 1Source to the console
 *
 * @param resp JSON response object to interate through and output
 * @param item Reponse object type
 *
 * @return None
 */
void outputResponse(const json resp, const string item)
{
    // Create the output header
    const string header = "1Source " + item;

    // Output the response to the console
    cout << " " << endl;

    // Output header and underline
    cout << header << endl;
    cout << string(header.length(), '=') << endl;

    // Output JSON response
    cout << resp.dump(2) << endl;
    cout << " " << endl;
}

int main(int argc, char **argv)
{
    logger.INFO("Starting application...");

    argparse::ArgumentParser program("1Source", "1.0.2");

    program.add_argument("-t").required().help("1Source configuration TOML file");
    program.add_argument("-o").help("1Source API Endpoint to query [agreements, contracts, events, parties ]");
    program.add_argument("-a").help("1Source API Endpoint to query trade agreements by agreement_id");
    program.add_argument("-e").help("1Source API Endpoint to query events by event_id");
    program.add_argument("-c").help("1Source API Endpoint to query contracts by contract_id");
    program.add_argument("-p").help("1Source API Endpoint to query parties by party_id");

    try
    {
        // Parse command line arguments
        program.parse_args(argc, argv);
        string args = "";

        for (int i = 1; i < argc; i++)
        {
            args = args + argv[i] + " ";
        }

        // Log command line arguments
        logger.DEBUG("User args entered: " + args);
    }
    catch (const runtime_error &err)
    {
        cerr << err.what() << endl;
        cerr << program;
        return 1;
    }

    string filename = "";

    // Get TOML configuration file name
    if (auto cfg = program.present("-t"))
    {
        filename = *cfg;
        logger.INFO("Reading configuration from TOML file: [" + filename + "]");
    }
    else
    {
        cerr << "No config TOML file specified" << endl;
        return 2;
    }

    // Open up and read TOML configuration file
    Configuration config = Configuration(filename);

    if (config.readConfiguration() != 0)
    {
        logger.FATAL("Could not parse configuration file:" + filename);
        cout << "Could not parse configuration file:" + filename << endl;
        return 3;
    }

    // Get the Auth token
    const string auth_token = getAuthToken(config);

    // If -a is on the command line, get the trade agreement by agreement_id
    if (auto cfg = program.present("-a"))
    {
        // Get the party from 1Source via the party_id
        string agreement_id = *cfg;

        string url = config.getAgreementsEndpoint() + "//" + agreement_id;
        Response r = Get(Url{url}, Bearer{auth_token});

        if (r.status_code == 200)
        {
            logger.INFO(url + " data received");
            json resp = json::parse(r.text);

            outputResponse(resp, "trade agreement");
        }
        else
        {
            // Error returned
            logger.INFO("agreement_id error returned: " + r.error.message);
            cerr << r.error.message << endl;
        }

        return 0;
    }

    // If -e is on the command line, get the event by event_id
    if (auto cfg = program.present("-e"))
    {
        // Get the event from 1Source via the party_id
        string event_id = *cfg;

        string url = config.getEventsEndpoint() + "//" + event_id;
        Response r = Get(Url{url}, Bearer{auth_token});

        if (r.status_code == 200)
        {
            logger.INFO(url + " data received");
            json resp = json::parse(r.text);

            outputResponse(resp, "event");
        }
        else
        {
            // Error returned
            logger.INFO("event_id error returned: " + r.error.message);
            cerr << r.error.message << endl;
        }

        return 0;
    }

    // If -c is on the command line, get the contract by contract_id
    if (auto cfg = program.present("-c"))
    {
        // Get the contract from 1Source via the contract_id
        string contract_id = *cfg;

        string url = config.getContractsEndpoint() + "//" + contract_id;
        Response r = Get(Url{url}, Bearer{auth_token});

        if (r.status_code == 200)
        {
            logger.INFO(url + " data received");
            json resp = json::parse(r.text);

            outputResponse(resp, "contract");
        }
        else
        {
            // Error returned
            logger.INFO("contract_id error returned: " + r.error.message);
            cerr << r.error.message << endl;
        }

        return 0;
    }

    // If -p is on the command line, get the party by party_id
    if (auto cfg = program.present("-p"))
    {
        // Get the party from 1Source via the party_id
        string party_id = *cfg;

        string url = config.getPartiesEndpoint() + "//" + party_id;
        Response r = Get(Url{url}, Bearer{auth_token});

        if (r.status_code == 200)
        {
            logger.INFO(url + " data received");
            json resp = json::parse(r.text);

            outputResponse(resp, "party");
        }
        else
        {
            // Error returned
            logger.INFO("party_id error returned: " + r.error.message);
            cerr << r.error.message << endl;
        }

        return 0;
    }

    // Query the 1Source API endpoint based on the endpoint specified
    if (auto cfg = program.present("-o"))
    {
        string endpoint = *cfg;
        Response r;

        if (endpoint.compare("agreements") == 0)
        {
            // Get Trade Agreements
            r = Get(Url{config.getAgreementsEndpoint()}, Bearer{auth_token});
        }
        else if (endpoint.compare("contracts") == 0)
        {
            // Get Contracts
            r = Get(Url{config.getContractsEndpoint()}, Bearer{auth_token});
        }
        else if (endpoint.compare("events") == 0)
        {
            // Get Events
            r = Get(Url{config.getEventsEndpoint()}, Bearer{auth_token});
        }
        else if (endpoint.compare("parties") == 0)
        {
            // Get Parties

            r = Get(Url{config.getPartiesEndpoint()}, Bearer{auth_token});
        }
        else
        {
            // Unknown endpoint specified
            logger.ERR("Unknown 1Source API endpoint requested: " + endpoint);
            cerr << "Unknown 1Source API endpoint requested: " + endpoint << endl;
        }

        if (r.status_code == 200)
        {
            logger.INFO(endpoint + " data received");

            json resp = json::parse(r.text);
            outputResponse(resp, endpoint);
        }
        else
        {
            // Error returned
            logger.INFO(endpoint + " error returned: " + r.error.message);
            cerr << r.error.message << endl;
        }
    }

    logger.INFO("Ending application...");
    return 0;
}