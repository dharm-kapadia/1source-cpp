﻿#include "1source.hpp"

#include "include/argparse.hpp"
#include "include/logger.hpp"
#include "include/json.hpp"
#include "include/configuration.hpp"
#include "include/utilities.hpp"

using namespace std;
using namespace cpr;
using namespace string_view_literals;
using namespace utilities;

// Create a logger for the application
Logger logger = Logger("1source.log");

int main(int argc, char **argv)
{
    logger.INFO("Starting application...");

    argparse::ArgumentParser program("1Source", "1.0.2");

    setHelpDetails(program);

    try
    {
        // Parse command line arguments
        program.parse_args(argc, argv);
        string args;

        for (int i = 1; i < argc; i++)
        {
            args = args.append(argv[i]).append(" ");
        }

        // Log command line arguments`
        logger.DEBUG("User args entered: " + args);
    }
    catch (const runtime_error &err)
    {
        cout << err.what() << endl;
        cout << program;
        return 1;
    }

    string filename;

    // Get TOML configuration file name
    if (auto cfg = program.present("-t"))
    {
        filename = *cfg;
        logger.INFO("Reading configuration from TOML file: [" + filename + "]");
    }
    else
    {
        cout << "No config TOML file specified" << endl;
        return 2;
    }

    // Open up and read TOML configuration file
    Configuration config = Configuration(filename);

    if (config.readConfiguration() != 0)
    {
        logger.FATAL("Could not parse configuration file: " + filename);
        cout << "Could not parse configuration file:" + filename << endl;
        return 3;
    }
    else
    {
        logger.INFO("Success reading and parsing configuration file: " + filename);
    }

    // Get the Auth token
    const string auth_token = getAuthToken(config, logger);

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
            cout << r.error.message << endl;
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
            logger.INFO("event_id error returned: " + r.text);
            cout << r.text << endl;
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
            logger.INFO("contract_id error returned: " + r.text);
            cout << r.text << endl;
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
            logger.INFO("party_id error returned: " + r.text);
            cout << r.text << endl;
        }

        return 0;
    }

    // if -d is on the command line, get the delegation by delegation_id
    if (auto cfg = program.present("-d"))
    {
        // Get the delegation from 1Source via the delegation_id
        string delegation_id = *cfg;

        string url = config.getDelegationsEndPoint() + "//" + delegation_id;
        Response r = Get(Url{url}, Bearer{auth_token});

        if (r.status_code == 200) {
            logger.INFO(url + " data received");
            json resp = json::parse(r.text);

            outputResponse(resp, "delegation");
        }
        else {
            // Error returned
            logger.INFO("delegation_id error returned: " + r.text);
            cout << r.text << endl;
        }
        
        return 0;
    }

    // Query the 1Source API endpoint based on the endpoint specified
    if (auto cfg = program.present("-g"))
    {
        string endpoint = *cfg;
        Response resp;

        if (endpoint == "agreements")
        {
            // Get Trade Agreements
            resp = Get(Url{config.getAgreementsEndpoint()}, Bearer{auth_token});
        }
        else if (endpoint == "contracts")
        {
            // Get Contracts
            resp = Get(Url{config.getContractsEndpoint()}, Bearer{auth_token});
        }
        else if (endpoint == "events")
        {
            // Get Events
            resp = Get(Url{config.getEventsEndpoint()}, Bearer{auth_token});
        }
        else if (endpoint == "parties")
        {
            // Get Parties
            resp = Get(Url{config.getPartiesEndpoint()}, Bearer{auth_token});
        }
        else if (endpoint == "delegations")
        {
            // Get Delegations
            resp = Get(Url{config.getDelegationsEndPoint()}, Bearer{auth_token});
        }
        else
        {
            // Unknown endpoint specified
            logger.ERR("Unknown 1Source API endpoint requested: " + endpoint);
            cout << "Unknown 1Source API endpoint requested: " + endpoint << endl;
        }

        if (resp.status_code == 200)
        {
            logger.INFO(endpoint + " data received");
            outputResponse(json::parse(resp.text), endpoint);
        }
        else
        {
            // Error returned
            logger.INFO(endpoint + " error returned: " + resp.text);
            cout << resp.text << endl;
        }
    }

    logger.INFO("Ending application...");
    return 0;
}
