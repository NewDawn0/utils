///////////////////////////////////////////////////
// argparse - A simple cpp argument parser       //
// Written/Copyright by NewDawn0 (Tom) 7.12.2022 //
// Code is licensed under the MIT license        //
///////////////////////////////////////////////////
#pragma once

// libs
#include <map>
#include <string>
#include <vector>
#include <utility>

// use
using std::map;
using std::pair;
using std::string;
using std::vector;

// definitions
#define ArgParserNoFileErr "Provide at least one file"
#define ArgParserNoArgErr "Provide an argument for this option"
#define ArgParserInvalidArgErr "Invalid argument"
#define ArgParserMultiargErr "This Argument can only be provided once"

// argument parser
namespace parsing {
    class ArgParser {
        vector<string> argKeys, multi, multiDone, noNextReq, otherArgs;
        vector<pair<string, string>> container;
        map<string, vector<string>> argtainer;
        private:
            int contains(vector<string> targetVec, string item);
            void order();
        public:
            void addArg(string arg, bool reqNextArg = true, bool multipleAllowed = false);
            void parse(int argc, char *argv[], bool allowInvalidArguments = false);
            void pprint();
    };
}
