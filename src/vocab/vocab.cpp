//
// voacab - a vocab testing tool
// written by NewDawn0 (Tom) 1.12.2022
//

// libs
#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>
#include <random>
#include <regex>
#include <tuple>
#include <map>

// using...
using std::string;
using std::vector;
using std::tuple;
using std::map;

// macros
#define red "\033[1;31m"
#define green "\033[1;32m"
#define yellow "\033[1;33m"
#define reset "\033[0m"
#define strikethrough "\033[9m"
#define HELP "\033[1;34mVocab - A simple app learn vocab\033[0m\n\033[1;34mSYPNOSIS\033[0m\n\t\033[0;35m\033[0;35mvocab\033[0m\033[0m [\033[0;36m-dhs\033[0m]\n\033[1;34mUSAGE\033[0m\n\t\033[0;35mvocab\033[0m <\033[0;36minput file: \033[0;33mstring\033[0m> <\033[0;36moptions\033[0m>\n\t\033[0;35mvocab\033[0m <\033[0;36minput file: \033[0;33mstring\033[0m> \033[0;36m-h\033[0m\t\t // Print this\n\t\033[0;35mvocab\033[0m <\033[0;36minput file: \033[0;33mstring\033[0m> \033[0;36m-s\033[0m\t\t // Switch questions and answers\n\t\033[0;35mvocab\033[0m <\033[0;36minput file: \033[0;33mstring\033[0m> \033[0;36m-d\033[0m <\033[0;36mdelimiter: \033[0;33mchar\033[0m>\t\t// default '|'"

// global stuff
static int oldRand = 0;
static char delim = '|';
static bool switchQA = false;
static vector<string> opts = {"-d", "-h", "-s"};

// function declarations
static int genRandNoRep(int max);
static void tokenize(string const &str, vector<string> &out);
static void whoAsked(tuple<vector<string>, map<string, string>> in);
static tuple<vector<string>, map<string, string>> scanFile(string inFileName);
static inline void ltrim(string &s);
static inline void rtrim(string &s);
static inline void trim(string &s);
static inline vector<string> split(string str);
static void preprocess(string inFileName);

// main
int main(int argc, char **argv) {
    // fail if no input file is provided
    if (argc == 1) {
        std::cerr << red << "Provide at least one input file\n" << reset << std::endl;
        std::cout << HELP << std::endl;
        return 1;
    }
    for (int n = 2; n < argc; n++) {
        if (argv[n] == opts[1]) {
            std::cout << HELP << std::endl;
            exit(1);
        }
        if (argv[n] == opts[0]) {
            if (argc >= 4) {
                if (strlen(argv[n+1]) == 1) {
                    ::delim = argv[n+1][0];
                } else {
                    std::cerr << red << "Input is not of type char" << reset << std::endl;
                    exit(1);
                }
            } else {
                std::cerr << red << "Missing argument for this option" << reset << std::endl;
                exit(1);
            }
        }
        if (argv[n] == opts[2]) {
            ::switchQA = true;
        }
    }
    // scan file and unpack
    string inFileName = argv[1];
    preprocess(inFileName);
    whoAsked(scanFile(inFileName));
    // ask questions
    return 0;
}

// generate random number
int genRandNoRep(int max) {
    vector<int> nums;
    for (int i = 0; i < max; i++) {nums.push_back(i);}
    std::shuffle(nums.begin(), nums.end(), std::random_device());
    if (nums[0] == ::oldRand) {
        return nums[1];
    };
    return nums[0];
}

// split input
void tokenize(string const &str, vector<string> &out) {
    char *token = strtok(const_cast<char*>(str.c_str()), &::delim);
    while (token != nullptr) {
        out.push_back(string(token));
        token = strtok(nullptr, &::delim);
    }
}

// ask Questions
void whoAsked(tuple<vector<string>, map<string, string>> in) {
    // unpack
    vector<string> askVec = std::get<0>(in);
    map<string, string> map = std::get<1>(in);
    // set vars
    srand(time(0));
    ::oldRand = rand() % askVec.size();
    string userInput;
    // ask
    while (askVec.size() > 0) {
        if (askVec.size() > 1) {
            int rand = genRandNoRep(askVec.size());
            std::cout << "Enter word(s) for \"" << askVec[rand] << "\":  ";
            std::getline(std::cin, userInput); trim(userInput);
            if (map[askVec[rand]] == userInput) {
                std::cout << green << "Correct  " << reset << "   Only " << askVec.size()-1 << " more to go!" << std::endl;
                askVec.erase(askVec.begin()+rand);
            } else {
                vector<string> inVec = split(userInput);
                vector<string> solVec = split(map[askVec[rand]]);
                // same amount of words
                if (inVec.size() == solVec.size()) {
                    for (int index = 0; index < solVec.size(); index++) {
                        if (solVec[index] != inVec[index]) {
                            std::cout << red;
                        }
                        std::cout << solVec[index] << reset << " ";
                    }
                // if input is longer
                } else if (inVec.size() > solVec.size()) {
                    for (int index = 0; index < solVec.size(); index++) {
                        if (solVec[index] != inVec[index]) {
                            std::cout << red;
                        }
                        std::cout << solVec[index] << reset << " ";
                    }
                    for (int index = solVec.size(); index < inVec.size(); index++) {
                        std::cout << yellow << strikethrough << inVec[index] << reset " ";
                    }
                // if input is shorter
                } else {
                    for (int index = 0; index < inVec.size(); index++) {
                        if (solVec[index] != inVec[index]) {
                            std::cout << red;
                        }
                        std::cout << solVec[index] << reset << " ";
                    }
                    for (int index = inVec.size(); index < solVec.size(); index++) {
                        std::cout << yellow << solVec[index] << reset " ";
                    }
                }
                std::cout << std::endl;
            }
            ::oldRand = rand;
        } else {
            std::cout << "Enter word(s) for \"" << askVec[0] << "\":  ";
            std::getline(std::cin, userInput); trim(userInput);
            if (map[askVec[0]] == userInput) {
                askVec.pop_back();
            } else {
                std::cout << red << map[askVec[0]] << reset << std::endl;
            }
        }
        userInput.clear();
        std::cout<<std::endl;
    }
    std::cout << green << "100% Completed" << reset << "   Here is your trophy 🏆" << std::endl;
}

// scan voacab text
tuple<vector<string>, map<string, string>> scanFile(string inFileName) {
    // Create vars
    map<string, string> map;
    vector<string> askVec;
    vector<string> temporaryOut;
    // readfile
    std::ifstream in(inFileName);
    if (in.is_open()) {
        string line;
        while (std::getline(in, line)) {
            if (line.empty()) {
            } else {
                tokenize(line, temporaryOut);
                trim(temporaryOut[0]);
                trim(temporaryOut[1]);
                if (::switchQA) {
                    map.insert({temporaryOut[1], temporaryOut[0]});
                    askVec.push_back(temporaryOut[1]);
                } else {
                    map.insert({temporaryOut[0], temporaryOut[1]});
                    askVec.push_back(temporaryOut[0]);
                }
                temporaryOut.clear();
            }
        }
        in.close();
    } else {
        std::cerr << red << "Error whilst opening file" << red << std::endl;
        exit(1);
    }
    // pack to return
    return tuple<vector<string>, std::map<string, string>>{askVec, map};
}

// left trim string
static inline void ltrim(std::string &s) {
    s.erase(s.begin(), std::find_if(s.begin(), s.end(), [](unsigned char ch) {
        return !std::isspace(ch);
    }));
}

// right trim string
static inline void rtrim(string &s) {
    s.erase(std::find_if(s.rbegin(), s.rend(), [](unsigned char ch) {
        return !std::isspace(ch);
    }).base(), s.end());
}
// trim string
static inline void trim(string &s) {
    std::regex re(R"(\s+)");
    s = std::regex_replace(s, re, " ");
    rtrim(s);
    ltrim(s);
}

// split string by spaces:
static inline vector<string> split(string str) {
    std::stringstream ss(str);
    std::istream_iterator<string> begin(ss);
    std::istream_iterator<string> end;
    vector<string> ret(begin, end);
    return ret;
}

// preprocess file
static void preprocess(string inFileName) {
    std::ifstream f(inFileName);
    int lineNum = 0;
    bool hasErrors = false;
    vector<int> ln;
    if (f.good()) {
        std::ifstream in(inFileName);
        if (in.is_open()) {
            string line;
            while (std::getline(in, line)) {
                lineNum++;
                if (line.empty()) {
                } else {
                    for (int i = 0; i < line.size(); i++) {
                        if (line[i] == ::delim) {
                            ln.push_back(i);
                        }
                    }
                    if (ln.size() == 0) {
                        std::cout <<yellow<<"Line "<<lineNum<<reset<<"\t"<<line<<yellow<<"  <- Add value to key"<<reset<< std::endl;
                        hasErrors = true;
                    } else if (ln.size() > 1) {
                        std::cout <<yellow<<"Line "<<lineNum<<reset<<"\t";
                        for (int i = 0; i < line.size(); i++) {
                            if (ln[1] > i) {
                                putchar(line[i]);
                            } else {
                                std::cout << red;
                                putchar(line[i]);
                            }
                        }
                        std::cout <<reset<<yellow<<"  <- Remove this"<<reset<< std::endl; 
                        hasErrors = true;
                    }
                    ln.clear();
                }
            }
            in.close();
            if (hasErrors) {
                std::cerr << red << "\nInput file has errors" << reset << std::endl;
                exit(1);
            }
        } else {
            std::cerr << red << "Error whilst opening file" << reset << std::endl;
            exit(1);
        }
    } else {
        std::cerr << red << "File doesn't exist" << reset << std::endl;
        exit(1);
    }
}
