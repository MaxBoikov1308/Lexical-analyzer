#include <iostream>
#include <fstream>
#include "Scaner.h"

int main() {
    std::ifstream ifile("myprog.minic");

    Scaner scanner(ifile);
    for (;;) {
        Token currentLexem = scanner.getNextToken();
        currentLexem.print(std::cout);

        if (currentLexem.type() == LexemType::error ||
            currentLexem.type() == LexemType::eof) {
            break;
        }
    }
    return 0;
}
