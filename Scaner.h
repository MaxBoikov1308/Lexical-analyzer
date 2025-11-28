#pragma once
#include <string>
#include <iostream>
#include <istream>
#include <map>

using std::string;
using std::ostream;
using std::istream;

enum class LexemType { num, chr, str, id, lpar, rpar, lbrace, rbrace, lbracket, rbracket,
semicolon, comma, colon, opassign, opplus, opminus, opmult, opinc, opeq, opne, oplt, opgt, ople,
opnot, opor, opand, kwint, kwchar, kwif, kwelse, kwswitch, kwcase, kwwhile, kwfor, kwreturn,
kwin, kwout, eof, error };

class Token {
    LexemType _type;
    int _value;
    string _str;
public:
    Token(LexemType type = LexemType::eof);
    Token(int value);
    Token(LexemType type, const string &s);
    Token(char c);
    
    LexemType type() const;
    int value() const;
    string str() const;
    void print(ostream &stream) const;
    static string lexemTypeToString(LexemType t);
};

class Scaner {
    istream &_in;
    std::map<string, LexemType> keywords;
    std::map<char, LexemType> punctuation;

    int nextChar();
    void putbackChar(char c);

    size_t line;
    size_t column;

public:
    Scaner(istream &stream);
    Token getNextToken();
};
