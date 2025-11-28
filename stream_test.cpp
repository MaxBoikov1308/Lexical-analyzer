#include <sstream>
#include <cctype>
#include <iostream>
#include <fstream>
#include <istream>

using std::istream;

int nextChar(istream &_in, int &line, int &column) {
    int c = _in.get();
    if (c == EOF) {
        return -1;
    }
    if (c == '\n') { 
        line++; 
        column = 0; 
    } else {
        column++;
    }
    return c;
}

void putbackChar(istream &_in, int &line, char c) {
    if (c == (char)-1) {
        return;
    }
    _in.putback(c);
    if (c == '\n') {
        if (line > 1) {
            line--;
        }
    }
}

int main() {
    int line = 1;
    int column = 1;
    std::ifstream ifile("myprog.minic");
    int c = nextChar(ifile, line, column);
    std::cout << char(c) << " " << line << " " << column << std::endl;
    c = nextChar(ifile, line, column);
    std::cout << char(c) << " " << line << " " << column << std::endl;
    putbackChar(ifile, line, 'w');
    std::cout << char(c) << " " << line << " " << column << std::endl;
    c = nextChar(ifile, line, column);
    std::cout << char(c) << " " << line << " " << column << std::endl;
    return 0;
}