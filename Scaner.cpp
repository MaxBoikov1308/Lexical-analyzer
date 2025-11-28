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

Scaner::Scaner(istream &stream) : _in(stream), line(1), column(0) {
    keywords["int"] = LexemType::kwint;
    keywords["char"] = LexemType::kwchar;
    keywords["if"] = LexemType::kwif;
    keywords["else"] = LexemType::kwelse;
    keywords["switch"] = LexemType::kwswitch;
    keywords["case"] = LexemType::kwcase;
    keywords["while"] = LexemType::kwwhile;
    keywords["for"] = LexemType::kwfor;
    keywords["return"] = LexemType::kwreturn;
    keywords["in"] = LexemType::kwin;
    keywords["out"] = LexemType::kwout;

    punctuation['('] = LexemType::lpar;
    punctuation[')'] = LexemType::rpar;
    punctuation['{'] = LexemType::lbrace;
    punctuation['}'] = LexemType::rbrace;
    punctuation['['] = LexemType::lbracket;
    punctuation[']'] = LexemType::rbracket;
    punctuation[';'] = LexemType::semicolon;
    punctuation[','] = LexemType::comma;
    punctuation[':'] = LexemType::colon;
}

int Scaner::nextChar() {
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

void Scaner::putbackChar(char c) {
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

Token Scaner::getNextToken() {
    int state = 0;
    string buf;
    int numVal = 0;

    while (1) {
        int c = nextChar();
        
        if (c == -1) {
            if (state == 0) {
                return Token(LexemType::eof);
            }
            if (state == 3) {
                return Token(LexemType::error, "unclosed string literal");
            }
            if (state == 2 || state == 4) {
                return Token(LexemType::error, "error in char literal");
            }
            if (state == 1) {
                return Token(numVal);
            }
            if (state == 5) {
                if (keywords.find(buf) != keywords.end()) {
                    return Token(keywords[buf]);
                }
                return Token(LexemType::id, buf);
            }
            return Token(LexemType::eof);
        }

        char ch = (char)c;
        
        switch (state) {
            case 0:
                if (isspace(ch)) {
                    break;
                }

                if (isdigit(ch)) {
                    numVal = ch - '0';
                    state = 1;
                    break;
                }
                
                if (isalpha(ch) || ch == '_') {
                    buf = ch;
                    state = 5;
                    break;
                }
                
                if (ch == '\'') {
                    buf.clear();
                    state = 2;
                    break;
                }
                
                if (ch == '"') {
                    buf.clear();
                    state = 3;
                    break;
                }
                
                if (ch == '!') { 
                    state = 6; 
                    break; 
                }
                if (ch == '<') { 
                    state = 7; 
                    break; 
                }
                if (ch == '=') { 
                    state = 8; 
                    break; 
                }
                if (ch == '+') { 
                    state = 9; 
                    break; 
                }
                if (ch == '|' || ch == '&') {
                    buf = ch;
                    state = 10;
                    break;
                }
                
                if (ch == '-') {
                    return Token(LexemType::opminus);
                }
                if (ch == '*') {
                    return Token(LexemType::opmult);
                }
                
                if (punctuation.count(ch)) {
                    return Token(punctuation[ch]);
                }
                
                return Token(LexemType::error, string("incorrect char '") + ch + "'");

            case 1:
                if (isdigit(ch)) {
                    numVal = numVal * 10 + (ch - '0');
                } else {
                    putbackChar(ch);
                    return Token(numVal);
                }
                break;

            case 2:
                if (ch == '\'') {
                    return Token(LexemType::error, "пусто");
                }
                buf = ch;
                state = 4;
                break;

            case 3:
                if (ch == '"') {
                    return Token(LexemType::str, buf);
                }
                if (ch == '\n') {
                    return Token(LexemType::error, "\n in str");
                }
                buf += ch;
                break;

            case 4:
                if (ch == '\'') {
                    return Token(buf[0]);
                }
                putbackChar(ch);
                return Token(LexemType::error, "error in char literal");

            case 5:
                if (isalnum(ch) || ch == '_') {
                    buf += ch;
                } else {
                    putbackChar(ch);
                    auto it = keywords.find(buf);
                    if (it != keywords.end()) 
                        return Token(it->second);
                    return Token(LexemType::id, buf);
                }
                break;

            case 6:
                if (ch == '=') {
                    return Token(LexemType::opne);
                }
                putbackChar(ch);
                return Token(LexemType::opnot);

            case 7:
                if (ch == '=') {
                    return Token(LexemType::ople);
                }
                putbackChar(ch);
                return Token(LexemType::oplt);

            case 8:
                if (ch == '=') {
                    return Token(LexemType::opeq);
                }
                putbackChar(ch);
                return Token(LexemType::opassign);

            case 9:
                if (ch == '+') {
                    return Token(LexemType::opinc);
                }
                putbackChar(ch);
                return Token(LexemType::opplus);

            case 10:
                if ((buf[0] == '|' && ch == '|') || (buf[0] == '&' && ch == '&')) {
                    return Token(buf[0] == '|' ? LexemType::opor : LexemType::opand);
                }
                putbackChar(ch);
                return Token(LexemType::error, string("lonely ") + buf[0]);

            default:
                return Token(LexemType::error, "unknown error");
        }
    }
}