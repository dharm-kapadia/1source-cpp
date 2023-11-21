#ifndef UTILITIES_H_
#define UTILITIES_H_

/**
 * @file utilities.cpp
 *
 * @brief Class to contain small utilties
 *
 * @author EquiLend
 * Contact: Dharm Kapadia <dharm.kapadia@equilend.com>
 *
 */

#include <chrono>
#include <iostream>
#include <string>

#include "argparse.hpp"

namespace utilities
{
    using json = nlohmann::json;

    // Get current date/time, format is YYYY-MM-DD.HH:mm:ss
    std::string CurrentDateTime()
    {
        const auto now = std::chrono::system_clock::now();
        return std::format("{:%Y-%m-%d.%X}", now);
    }

    // Set the command line parameter help text
    void setHelpDetails(argparse::ArgumentParser &program) {
        program.add_argument("-t").required().help("1Source configuration TOML file");
        program.add_argument("-g").help("1Source API Endpoint to get [agreements, contracts, events, parties, rerates, returns, recalls, buyins]");
        program.add_argument("-a").help("1Source API Endpoint to get trade agreements by agreement_id");
        program.add_argument("-e").help("1Source API Endpoint to get events by event_id");
        program.add_argument("-c").help("1Source API Endpoint to get contracts by contract_id");
        program.add_argument("-ch").help("1Source API Endpoint to get contract history by contract_id");
        program.add_argument("-p").help("1Source API Endpoint to get parties by party_id");

        program.add_argument("-cp").help("1Source API Endpoint to PROPOSE a contract from a JSON file");
        program.add_argument("-cc").help("1Source API Endpoint to CANCEL a proposed contract by contract_id");
        program.add_argument("-ca").help("1Source API Endpoint to APPROVE a proposed contract by contract_id");
        program.add_argument("-cd").help("1Source API Endpoint to DECLINE a proposed contract by contract_id");
    }

    /**
 * Outputs the response from the 1Source to the console
 *
 * @param resp JSON response object to iterate through and output
 * @param item Response object type
 *
 * @return None
 */
    void outputResponse(const json& resp, const string& item)
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
}

#endif
