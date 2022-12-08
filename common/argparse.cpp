///////////////////////////////////////////////////
// argparse - A simple cpp argument parser       //
// Writeen/Copyright by NewDawn0 (Tom) 7.12.2022 //
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
    if (argc == 1) {
        std::cerr << red << "ArgParse Error "<< reset << ArgParserNoFileErr << std::endl;
        exit(1);
    } else {
        int argIndex = 1;
        while (argIndex < argc) {
            if (contains(parsing::ArgParser::argKeys, argv[argIndex]) != -1) {
                if (contains(parsing::ArgParser::multi, argv[argIndex]) != -1 || contains(parsing::ArgParser::multiDone, argv[argIndex]) == -1) {
                    parsing::ArgParser::multiDone.push_back(argv[argIndex]);
                    std::cout << "Argument: " << argv[argIndex] << " is OK" << std::endl;
                    if (argc-1 >= argIndex+1) {
                        argIndex++;
                    } else {
                        std::cerr << red << "ArgParse Error " << reset << ArgParserNoArgErr << std::endl;
                        exit(1);

                    }
                } else {
                    std::cerr << red << "ArgParse Error " << reset << ArgParserMultiargErr << red << " \'" << reset << argv[argIndex] << red << "\'" << reset << std::endl; 
                    exit(1);
                }
            } else {
                if (!allowInvalidArguments) {
                    std::cerr << red << "ArgParse Error " << reset << ArgParserInvalidArgErr <<red << " \'" << reset << argv[argIndex] << red << "\'" << reset << std::endl;
                    exit(1);
                }
                otherArgs.push_back(argv[argIndex]);
            }
            std::cout << "arg: " << argv[argIndex] << std::endl;
            argIndex++;
        }
    }
}
