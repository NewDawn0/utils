///////////////////////////////////////////////////
// argparse - A simple cpp argument parser       //
// Written/Copyright by NewDawn0 (Tom) 7.12.2022 //
// Code is licensed under the MIT license        //
///////////////////////////////////////////////////

// libs
#include <cstddef>
#include <map>
#include <vector>
#include <string>
#include <utility>
#include <iostream>
#include "argparse.hpp"

//definitions
#define red "\033[1;31m"
#define reset "\033[0m"

// use
using std::map;
using std::pair;
using std::vector;
using std::string;

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
void parsing::ArgParser::parse(int argc, char *argv[], bool allowInvalidArguments, bool allowNoArguments) {
    if (argc == 1 && !allowNoArguments) {
        // Override default
        if (parsing::ArgParser::events["NoArguments"] != NULL) {
            events["NoArguments"]();
        } else {
            // err out if no argument is listed and allow no arguments is listed as false
            std::cerr << red << "ArgParse Error "<< reset << ArgParserNoArgErr << std::endl;
            exit(1);
        }
    } else if (argc == 1) {
        // Override default
        if (parsing::ArgParser::events["AllowNoArguments"] != NULL) {
            events["AllowNoArguments"]();
        }
    } else {
        int argIndex = 1;
        while (argIndex < argc) {
            if (contains(parsing::ArgParser::argKeys, argv[argIndex]) != -1) {
                if (contains(parsing::ArgParser::multi, argv[argIndex]) != -1 || contains(parsing::ArgParser::multiDone, argv[argIndex]) == -1) {
                    multiDone.push_back(argv[argIndex]);
                    // create temporary container
                    pair<string, string> pContainer;
                    // check if argument needs next arg
                    if (contains(parsing::ArgParser::noNextReq, argv[argIndex]) != -1) {
                        // add arg to container
                        pContainer = std::make_pair(argv[argIndex], NULL);
                        container.push_back(pContainer);
                    } else {
                        // look if there is next arg
                        if (argc-1 >= argIndex+1) {
                            // add arg to container
                            pContainer = std::make_pair(argv[argIndex], argv[argIndex+1]);
                            container.push_back(pContainer);
                            argIndex++;
                        } else {
                            // Override default
                            if (parsing::ArgParser::events["MissingArg"] != NULL) {
                                events["MissingArg"]();
                            } else {
                                // err if no next arg is found
                                std::cerr << red << "ArgParse Error " << reset << ArgParserMissingArgErr << std::endl;
                                exit(1);
                            }
                        }
                    }
                } else {
                    // Override default
                    if (parsing::ArgParser::events["MultiArg"] != NULL) {
                        events["MultiArg"]();
                    } else {
                        // err if there are multiple of the same arg which is not allowed as default
                        std::cerr << red << "ArgParse Error " << reset << ArgParserMultiArgErr << red << " \'" << reset << argv[argIndex] << red << "\'" << reset << std::endl; 
                        exit(1);
                    }
                }
            } else {
                // err if invalid arguments aren't allowed
                if (!allowInvalidArguments) {
                    // Override default
                    if (parsing::ArgParser::events["InvalidArg"] != NULL) {
                        events["InvalidArg"]();
                    } else {
                        std::cerr << red << "ArgParse Error " << reset << ArgParserInvalidArgErr <<red << " \'" << reset << argv[argIndex] << red << "\'" << reset << std::endl;
                        exit(1);
                    }
                }
                // collect "invalid" argument as otherArgs
                otherArgs.push_back(argv[argIndex]);
            }
            argIndex++;
        }
    }
}

// addTrigger - Override default behaviour
void parsing::ArgParser::addTrigger(string event, void (*fnPtr)()) {
    // if event exist overwrite original behaviour
    if (contains(parsing::ArgParser::eventTriggers, event) != -1) {
        events[event] = fnPtr;
    }
}
