#include "Scaner.h"
#include <sstream>
#include <cctype>

Token::Token(LexemType type) : _type(type), _value(0), _str() {}
Token::Token(int value) : _type(LexemType::num), _value(value), _str() {}
Token::Token(LexemType type, const string &s) : _type(type), _value(0), _str(s) {}
Token::Token(char c) : _type(LexemType::chr), _value(static_cast<int>(c)), _str() {}

LexemType Token::type() const { 
    return _type; 
}
int Token::value() const { 
    return _value; 
}
string Token::str() const { 
    return _str; 
}

string Token::lexemTypeToString(LexemType t) {
    switch (t) {
        case LexemType::num: 
            return "num";
        case LexemType::chr: 
            return "chr";
        case LexemType::str: 
            return "str";
        case LexemType::id: 
            return "id";
        case LexemType::lpar: 
            return "lpar";
        case LexemType::rpar: 
            return "rpar";
        case LexemType::lbrace: 
            return "lbrace";
        case LexemType::rbrace: 
            return "rbrace";
        case LexemType::lbracket: 
            return "lbracket";
        case LexemType::rbracket: 
            return "rbracket";
        case LexemType::semicolon: 
            return "semicolon";
        case LexemType::comma: 
            return "comma";
        case LexemType::colon: 
            return "colon";
        case LexemType::opassign: 
            return "opassign";
        case LexemType::opplus: 
            return "opplus";
        case LexemType::opminus: 
            return "opminus";
        case LexemType::opmult: 
            return "opmult";
        case LexemType::opinc: 
            return "opinc";
        case LexemType::opeq: 
            return "opeq";
        case LexemType::opne: 
            return "opne";
        case LexemType::oplt: 
            return "oplt";
        case LexemType::opgt: 
            return "opgt";
        case LexemType::ople: 
            return "ople";
        case LexemType::opnot: 
            return "opnot";
        case LexemType::opor: 
            return "opor";
        case LexemType::opand: 
            return "opand";
        case LexemType::kwint: 
            return "kwint";
        case LexemType::kwchar: 
            return "kwchar";
        case LexemType::kwif: 
            return "kwif";
        case LexemType::kwelse: 
            return "kwelse";
        case LexemType::kwswitch: 
            return "kwswitch";
        case LexemType::kwcase: 
            return "kwcase";
        case LexemType::kwwhile: 
            return "kwwhile";
        case LexemType::kwfor: 
            return "kwfor";
        case LexemType::kwreturn: 
            return "kwreturn";
        case LexemType::kwin: 
            return "kwin";
        case LexemType::kwout: 
            return "kwout";
        case LexemType::eof: 
            return "eof";
        case LexemType::error: 
            return "error";
    }
    return "unknown";
}

void Token::print(ostream &stream) const {
    switch (_type) {
        case LexemType::error:
            stream << "[error, \"" << _str << "\"]\n"; return;
        case LexemType::eof:
            stream << "[eof]\n"; return;
        case LexemType::num:
            stream << "[num, " << _value << "]\n"; return;
        case LexemType::chr:
            stream << "[chr, '" << static_cast<char>(_value) << "']\n"; return;
        case LexemType::str:
            stream << "[str, \"" << _str << "\"]\n"; return;
        case LexemType::id:
            stream << "[id, \"" << _str << "\"]\n"; return;
        default:
            stream << "[" << lexemTypeToString(_type) << "]\n"; return;
    }
}

int main() {
    Token token1('a');
    token1.print(std::cout);
    Token token2(LexemType::opeq);
    token2.print(std::cout);
    Token token3(LexemType::id, "asadasd");
    token3.print(std::cout);
    Token token4(123);
    token4.print(std::cout);
    return 0;
}