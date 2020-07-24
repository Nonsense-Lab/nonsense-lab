#include <iostream>
#include <string>
#include <random>
#include <sstream>
#include <ctime>
#include <fstream>
#include <cstdlib>
#include <vector>
using namespace std;

#define FALSE false
#define TRUE true
#define BOOL bool
typedef string CHARTRAIT;
typedef int TERMINALINTEGER;
typedef char CHAR;
#define TOINT stoi
#define TOLONG stol

string getRandomNumbersInString(unsigned long How_Long) {
    srand(time(0));
    stringstream ss;
    static uniform_int_distribution<unsigned int> dist(0, 9);
    static default_random_engine rng(time(nullptr)+rand());
    for (unsigned long i = 0; i < How_Long; i++) {
        ss << dist(rng);
    }
    return ss.str();
}

const string alphabet = "0ABCDEFGHIJKLMNOPQRSTUVWXYZ";

string getCalculatedData(string Random_Numbers_In_String, unsigned long Separate, string Separator) {
    string ret = "";
    for (unsigned long i = 0; i < Random_Numbers_In_String.length() - 1; i++) {
        unsigned int a = 0, b = 0, full = 0;
        stringstream ss;
        ss<<Random_Numbers_In_String[i];
        ss>>a;
        ss.clear();
        ss<<Random_Numbers_In_String[i+1];
        ss>>b;
        ss.clear();
        ss<<Random_Numbers_In_String[i]<<Random_Numbers_In_String[i+1];
        ss>>full;
        unsigned int c = a + b;
        if (full > 26) {
            ret += alphabet[c];
        } else if (full % 2 == 0) ret += alphabet[full];
        else if (c < 10) {
            ss.clear();
            ss<<c;
            ret += ss.str();
        } else {
            srand(c);
            ret += alphabet[rand()%c];
        }
        if (i % Separate == 0) ret += Separator;
    }
    return ret;
}

vector<string> split(string par, char sep) {
    vector<string> ret;
    ret.clear();
    string tmp = "";
    for (int i = 0; i < par.size(); i++) {
        if (par[i] != sep) {
            tmp += par[i];
        } else {
            ret.push_back(tmp);
            tmp = "";
        }
    }
    return ret;
}

string standard(string a, string b) {
    return string("Random Number: ") + a + string("\n\nGenerated Key: ") + b;
}

string oe(string a) {
    return a;
}

string on(string a) {
    return a;
}

void MainFunction(

                  BOOL FILEOUTPUT = FALSE,
                  CHARTRAIT FILENAME = string(""),

                  BOOL ONLYENCRYPTED = FALSE,

                  BOOL ONLYNUMBER = FALSE,

                  BOOL HELP = FALSE,

                  BOOL ABOUT = FALSE,

                  BOOL VERSION = FALSE,

                  TERMINALINTEGER HOWLONG = 0,

                  BOOL NEEDSEPARATOR = FALSE,
                  TERMINALINTEGER SEPARATE = 0,
                  CHARTRAIT SEPARATOR = string("\0")
                  ) {

                      BOOL HLISZERO = FALSE;

                      // cout<<HOWLONG<<endl;

                      if (HOWLONG == 0) HLISZERO = TRUE;

                      if (!HLISZERO) {
                        string xptr = getRandomNumbersInString(HOWLONG);

                        if (ONLYENCRYPTED) {
                            if (FILEOUTPUT) {
                                ofstream of(FILENAME.c_str());
                                of<<oe(getCalculatedData(xptr, (NEEDSEPARATOR)?(unsigned int)SEPARATE:1, (NEEDSEPARATOR)?SEPARATOR:string("\0")));
                                of.close();
                            } else {
                                cout<<oe(getCalculatedData(xptr, (NEEDSEPARATOR)?(unsigned int)SEPARATE:1, (NEEDSEPARATOR)?SEPARATOR:string("\0")));
                            }
                        }

                        if (ONLYNUMBER) {
                            if (FILEOUTPUT) {
                                ofstream of(FILENAME.c_str());
                                of<<on(xptr);
                                of.close();
                            } else {
                                cout << on(xptr);
                            }
                        }

                        if (!ONLYENCRYPTED && !ONLYNUMBER) {
                            if (FILEOUTPUT) {
                                ofstream of(FILENAME.c_str());
                                of<<standard(xptr, getCalculatedData(xptr, (NEEDSEPARATOR)?(unsigned int)SEPARATE:1, (NEEDSEPARATOR)?SEPARATOR:string("\0")));
                                of.close();
                            } else {
                                cout << standard(xptr, getCalculatedData(xptr, (NEEDSEPARATOR)?(unsigned int)SEPARATE:1, (NEEDSEPARATOR)?SEPARATOR:string("\0")));
                            }
                        }
                      }

                      if (HELP) {
                        cout << "===== Help of GR =====" << endl
                            <<  "--only-number\t:\tShow only generated big number." << endl
                            <<  "--only-encrypted\t:\tShow only generated result." << endl
                            <<  "--help\t:\tShow this help." << endl
                            <<  "--about\t:\tShow about file." << endl
                            <<  "--version\t:\tShow the version of GR you current using." << endl
                            <<  "--separator <i:int> <j:char>\t:\tAutomatically adds a separator <j> every <i> characters." << endl
                            <<  "--length <i:int>\t:\t**IMPORTANT**: Set the length of the generated number to <i>." << endl;
                      }

                      if (ABOUT) {
                        cout << "===== About GR =====" << endl
                            <<  "Author: Sam Huang (GitHub/@k612created, Twitter/@sammmmmmyh)" << endl
                            <<  "An application which generates a theorically random & unique " << endl
                            <<  "Number and key." << endl
                            <<  "Feel free to re-write this in other languages and give me a star! :P" << endl;
                      }

                      if (VERSION) {
                        cout << "===== The version of GR =====" << endl
                            <<  "Version: v0.0.1 alpha" << endl
                            <<  "Waiting for enhancements & contributions..." << endl;
                      }

                      return;
                  }

int main(int argc, char** argv) {
    time_t prev = time(0);
    string param = "";
    for (int i = 1; i < argc; i++) {
            /*cout<<argv[i]<<" ";*/
        param += string(argv[i]) + string(" ");
    }
    vector<string> splited = split(param, ' ');
    /*for (int i = 0; i < splited.size(); i++) cout << splited[i] << endl;
    cout << (splited[0] == string("--help"));*/
    BOOL F = FALSE, OE = FALSE, ON = FALSE, H = FALSE, A = FALSE, V = FALSE, N = FALSE;
    TERMINALINTEGER HL = 0, SP = 0;
    CHARTRAIT FN = "";
    CHARTRAIT S = "\0";
    for (int i = 0; i < splited.size(); i++) {
        if (splited[i] == string("--file-output")) {
            F = TRUE;
            FN = splited[i+1];
            i += 1;
        } else if (splited[i] == string("--only-encrypted")) {
            OE = TRUE;
        } else if (splited[i] == string("--only-number")) {
            ON = TRUE;
        } else if (splited[i] == string("--help")) {
            H = TRUE;
        } else if (splited[i] == string("--about")) {
            A = TRUE;
        } else if (splited[i] == string("--version")) {
            V = TRUE;
        } else if (splited[i] == string("--separator")) {
            N = TRUE;
            SP = TOINT(splited[i+1]);
            S = splited[i+2];
            i += 2;
        } else if (splited[i] == string("--length")) {
            HL = stoi(splited[i+1]);
            i += 1;
        }
    }
    /*cout<<F<<endl<<FN<<endl<<OE<<endl<<ON<<endl<<H<<endl<<A<<endl<<V<<endl<<HL<<endl<<N<<endl<<SP<<endl<<S<<endl;*/
    MainFunction(F,FN,OE,ON,H,A,V,HL,N,SP,S);
    time_t now = time(0);
    cout << endl << "Elapsed time: " << (double)(now - prev) << " second(s).";
    return 0;
}
