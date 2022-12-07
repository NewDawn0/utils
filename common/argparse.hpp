///////////////////////////////////////////////////
// argparse - A simple cpp argument parser       //
// Writeen/Copyright by NewDawn0 (Tom) 7.12.2022 //
// Code is licensed under the MIT license        //
///////////////////////////////////////////////////
#include <string>
#include <vector>
#include <map>
using std::string;
using std::vector;
using std::map;

// definitions
#define ArgParserNoFileErr "Provide at least one file"
#define ArgParserNoArgErr "Provide an argument for this option"
#define ArgParserInvalidArgErr "Invalid argument"

// argument parser
namespace parsing {
    class ArgParser {
        vector<string> argKeys, multi, multiDone, noNextReq;
        map<string, vector<string>> container;
        private:
            int contains(vector<string> targetVec, string item);
        public:
            void addArg(string arg, bool reqNextArg = true, bool multipleAllowed = false);
            void parse(int argc, char *argv[]);
    };
}
