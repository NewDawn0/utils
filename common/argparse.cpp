///////////////////////////////////////////////////
// argparse - A simple cpp argument parser       //
// Written/Copyright by NewDawn0 (Tom) 7.12.2022 //
// Code is licensed under the MIT license        //
///////////////////////////////////////////////////

// libs
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
void parsing::ArgParser::parse(int argc, char *argv[], bool allowInvalidArguments) {
    if (argc == 1 && parsing::ArgParser::argKeys.size() == 0) {
        // err out if no argument is listed
        std::cerr << red << "ArgParse Error "<< reset << ArgParserNoFileErr << std::endl;
        exit(1);
    } else {
        int argIndex = 1;
        while (argIndex < argc) {
            if (contains(parsing::ArgParser::argKeys, argv[argIndex]) != -1) {
                if (contains(parsing::ArgParser::multi, argv[argIndex]) != -1 || contains(parsing::ArgParser::multiDone, argv[argIndex]) == -1) {
                    parsing::ArgParser::multiDone.push_back(argv[argIndex]);
                    // create temporary container
                    pair<string, string> pContainer;
                    // check if argument needs next arg
                    if (contains(parsing::ArgParser::noNextReq, argv[argIndex]) != -1) {
                        // add arg to container
                        pContainer = std::make_pair(argv[argIndex], NULL);
                        parsing::ArgParser::container.push_back(pContainer);
                    } else {
                        // look if there is next arg
                        if (argc-1 >= argIndex+1) {
                            // add arg to container
                            pContainer = std::make_pair(argv[argIndex], argv[argIndex+1]);
                            parsing::ArgParser::container.push_back(pContainer);
                            argIndex++;
                        } else {
                            // err if no next arg is found
                            std::cerr << red << "ArgParse Error " << reset << ArgParserNoArgErr << std::endl;
                            exit(1);
                        }
                    }
                } else {
                    // err if there are multiple of the same arg which is not allowed as default
                    std::cerr << red << "ArgParse Error " << reset << ArgParserMultiargErr << red << " \'" << reset << argv[argIndex] << red << "\'" << reset << std::endl; 
                    exit(1);
                }
            } else {
                // err if invalid arguments aren't allowed
                if (!allowInvalidArguments) {
                    std::cerr << red << "ArgParse Error " << reset << ArgParserInvalidArgErr <<red << " \'" << reset << argv[argIndex] << red << "\'" << reset << std::endl;
                    exit(1);
                }
                // collect "invalid" argument as otherArgs
                otherArgs.push_back(argv[argIndex]);
            }
            argIndex++;
        }
    }
}

// parser reorder and make available
void parsing::ArgParser::pprint() {
    for (auto &item: parsing::ArgParser::container) {
        std::cout << "first:"<<std::get<0>(item)<<" second:"<<std::get<1>(item) << std::endl;
    }
}
