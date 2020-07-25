#include <string>
#include <iostream>
#include <random>
#include <fstream>
#include <map>
#include <sstream>
#include <ctime>
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

CHARTRAIT EMPTY = string("");

map<char, int> A;
map<int, char> B;

const string alphabet = "0ABCDEFGHIJKLMNOPQRSTUVWXYZ";

void init(map<char, int>& MapWaitingForInitialization0, map<int, char>& Map1) {
    int ctr = 1;
    for (char a = 'A'; a <= 'Z'; a++) {
        MapWaitingForInitialization0[a] = ctr;
        Map1[ctr] = a;
        ctr++;
    }
    Map1[0] = '-';
    return;
}

string getNumbersInString(map<char, int> ConfigurationMap, string str) {
    string ret = "";
    
    for (unsigned long i = 0; i < str.size(); i++) {
        stringstream ss;
        // cout<<"Now: " << str[i] << endl;
        ss.clear();
        if (ConfigurationMap[str[i]] < 10) ss<<0;
        ss<<ConfigurationMap[str[i]];
        ret += ss.str();
    }
    return ret;
}

string getCalculatedData(string NumbersInString) {
    string ret = "";
    for (unsigned long i = 0; i < NumbersInString.length() - 1; i++) {
        unsigned int a = 0, b = 0, full = 0;
        stringstream ss;
        ss<<NumbersInString[i];
        ss>>a;
        ss.clear();
        ss<<NumbersInString[i+1];
        ss>>b;
        ss.clear();
        ss<<NumbersInString[i]<<NumbersInString[i+1];
        ss >> full;
        unsigned int c = a + b;
        if (full >= 26) {
            ret += alphabet[c];
        } else if (c < 10) {
            ss.clear();
            ss<<c;
            ret += ss.str();
        } else if (full < 26) {
            ret += alphabet[full];
        }
        if (i == NumbersInString.length() - 2) ret += string("+")+alphabet[a]+alphabet[b]+string("-");
        else
        ret += string("+")+alphabet[a]+string("-");
        //cout<<i<<": Worked!"<<endl;
        
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

string getDecr(string CalculatedData, map<int, char> Map0, map<char, int> Map1) {
    string ret = "", ret0 = "";
    bool foundS = false, foundE = false;
    for (int i = 0; i < CalculatedData.length(); i++) {
        if (CalculatedData[i]=='+') { foundS = true; i += 1; }
        if (CalculatedData[i]=='-') foundE = true;
        if (foundS && foundE) { foundS = 0; foundE = 0; }
        if (foundS) { 
            int idx = Map1[CalculatedData[i]];
            // cout<<CalculatedData[i];
            stringstream ss;
            ss<<idx;
            ret+=ss.str();
        }
    }
    for (int i = 0; i < ret.length(); i+=2) {
        string tmp = "";
        tmp += ret[i];
        tmp += ret[i+1];
        stringstream ss;
        ss<<tmp;
        int pt;
        ss>>pt;
        ret0 += Map0[pt];
    }

    return ret0;
}

void MainFunction(

    BOOL FILEOUTPUT = FALSE,
    CHARTRAIT FILENAME = EMPTY,

    BOOL ENCRYPT = FALSE,
    CHARTRAIT ENCRYPTED = EMPTY,

    BOOL DECRYPT = FALSE,
    CHARTRAIT DECRYPTED = EMPTY,

    BOOL HELP = FALSE,

    BOOL ABOUT = FALSE,

    BOOL VERSION = FALSE

) {
    if (ENCRYPT) {
        if (FILEOUTPUT) {
            ofstream of(FILENAME.c_str());
            of<<getCalculatedData(getNumbersInString(A,ENCRYPTED));
            of.close();
        } else {
            cout<<getCalculatedData(getNumbersInString(A,ENCRYPTED));
        }
    }

    if (DECRYPT) {
        if (FILEOUTPUT) {
            ofstream of(FILENAME.c_str());
            of<<getDecr(DECRYPTED,B,A);
            of.close();
        } else {
            cout<<getDecr(DECRYPTED,B,A);
        }
    }

    if (HELP) {
        cout << "===== Help of GR Encryptor / Decryptor =====" << endl
            <<  "-e <what:string>\t:\tEncrypt the string <what> using the GR algorithm." << endl
            <<  "-d <what:string>\t:\tDecrypt the string <what> using the GR algorithm." << endl
            <<  "-h              \t:\tShow this help file." << endl
            <<  "-a              \t:\tShow about file." << endl
            <<  "-v              \t:\tShow the version." << endl
            <<  "-f <what:string>\t:\tOutput in file named <what>.";
    }

    if (ABOUT) {
        cout << "===== About GR  =====" << endl
            <<  "Author: Sam Huang (GitHub/@k612created, Twitter/@sammmmmmyh)" << endl
            <<  "An application which encrypts and decrypts a specific " << endl
            <<  "string. Safety is not proved. But you can easily make other people confused." << endl
            <<  "Feel free to re-write this in other languages and give me a star! :P" << endl;
    }

    if (VERSION) {
        cout << "v0.0.1 alpha" << endl;
    }

    return;
}

string toValid(string x) {
    string ret = "";
    for (int i = 0; i < x.size(); i++) {
        if (x[i] >= 'A' && x[i] <= 'Z') ret += x[i];
        else if (x[i] >= 'a' && x[i] <= 'z') ret += x[i] - 32;
    }
    return ret;
}

int main(int argc, char** argv) {
    init(A,B);
    time_t prev = time(0);
    string param = "";
    for (int i = 1; i < argc; i++) {
        param += string(argv[i]) + string(" ");
    }
    vector<string> splited = split(param, ' ');
    BOOL F = FALSE,E = FALSE,D = FALSE,H = FALSE,V = FALSE,A = FALSE;
    CHARTRAIT FN = EMPTY, EC = EMPTY, DC = EMPTY;
    for (int i = 0; i < splited.size(); i++) {
        if (splited[i] == string("-f")) {
            F = TRUE;
            FN = splited[i+1];
            i += 1;
        } else if (splited[i] == string("-e")) {
            E = TRUE;
            EC = toValid(splited[i+1]);
            i += 1;
        } else if (splited[i] == string("-d")) {
            D = TRUE;
            DC = splited[i+1];
            i += 1;
        } else if (splited[i] == string("-h")) { H = TRUE; }
        else if (splited[i] == string("-v")) { V = TRUE; }
        else if (splited[i] == string("-a")) { A = TRUE; }
    }
    MainFunction(F,FN,E,EC,D,DC,H,A,V);
    time_t now = time(0);
    cout << endl << "Elapsed time: " << (double)(now - prev) << " second(s)." << endl;
    return 0;
}
