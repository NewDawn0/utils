///////////////////////////////////////////////////
// argparse - A simple cpp argument parser       //
// Writeen/Copyright by NewDawn0 (Tom) 7.12.2022 //
// Code is licensed under the MIT license        //
///////////////////////////////////////////////////

// libs
#include <map>
#include <vector>
#include <string>
#include <iostream>
#include "argparse.hpp"

//definitions
#define red "\033[1;31m"
#define reset "\033[0m"

// use
using std::vector;
using std::string;
using std::map;

// parser contains
int parsing::ArgParser::contains(vector<string> targetVec, string item) {
    auto res = std::find(targetVec.begin(), targetVec.end(), item);
    if (res != targetVec.end()) {
        return res - targetVec.begin();
        
    } else {
        return -1; 
    }
}

// parser addArg
void parsing::ArgParser::addArg(string arg, bool reqNextArg, bool multipleAllowed) {
    if (multipleAllowed) parsing::ArgParser::multi.push_back(arg);
    if (!reqNextArg) parsing::ArgParser::noNextReq.push_back(arg);
    parsing::ArgParser::argKeys.push_back(arg);
}

// parser parse
void parsing::ArgParser::parse(int argc, char *argv[]) {
    if (argc == 1) {
        std::cerr << red << "ArgParser Error "<< reset << ArgParserNoFileErr << std::endl;
        exit(1);
    } else {
        for (int argIndex = 1; argIndex < argc; argIndex++) {
            int in = contains(parsing::ArgParser::argKeys, argv[argIndex]);
            if (in != -1) {
                // if able to have multiple instances or not done yet
                if (contains(parsing::ArgParser::multi, argv[argIndex]) != -1 || contains(parsing::ArgParser::multiDone, argv[argIndex]) == -1) {
                    parsing::ArgParser::multiDone.push_back(argv[argIndex]);
                    std::cout << "Argument " << argv[argIndex] << " OK"<< std::endl;
                } else {
                    std::cout << "Argument " << argv[argIndex] << " disallowed"<< std::endl;
                }
            } else {
                std::cerr << red << "ArgParser Error " << reset << ArgParserInvalidArgErr << std::endl;
                exit(1);
            }
        }
    }
}
