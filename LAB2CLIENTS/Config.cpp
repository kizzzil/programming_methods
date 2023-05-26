#include <iostream>
#include <fstream>
#include <string>
#include <map>

using namespace std;

class Config{
private:
    map <string,int> confMap = {};
public:
    int getConfMap(string param){
        return confMap[param];
    }
    Config(){
        ifstream configFile;("config.txt");
        string line;
        while (getline(configFile, line)){
            int pos = line.find('=');
            if (pos == string::npos) {
                cerr << "Invalid line in configuration file: " << line << std::endl;
                continue;
            }
            confMap[line.substr(0, pos)] = stoi(line.substr(pos+1));
        }
	    configFile.close();
    }
};
