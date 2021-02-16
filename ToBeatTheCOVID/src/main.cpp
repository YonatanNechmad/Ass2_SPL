#include <iostream>
#include "../include/Session.h"
#include "ostream"
#define JSON_PATH "output.json"
using namespace std;

int main(int argc, char** argv){
    if (argc != 2) {
        cout << "usage cTrace <config_path>" << endl;
        return 1;
    } else {
        std::string path = argv[1];
        Session session(path);
        session.simulate();
        return 0;
    }
}

