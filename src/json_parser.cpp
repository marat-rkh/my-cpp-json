#include "json_parser.h"

#include <ifstream>
#include <fstream>
#include <cctype>

using std::istream;
using std::ifstream;
using std::string;
using std::shared_ptr;

using namespace json_cpp;

shared_ptr<ParseResult> ParseObject(istream &is);

shared_ptr<ParseResult> Parse(string const &file_path) {
    ifstream ifs(file_path);
    shared_ptr<ParseResult> res = ParseObject(ifs);
    if(res.type() == ParseResult::Type::SUCCESS && ifs) {
        // parsing succeeded but input still has some characters
        return std::make_shared(
            new ParseError(0, 0, "json file must contain one top level object")
        );
    } else {
        return res;
    }
}

class Token {
public:
    enum class Type {
        C_BR_OPEN,
        C_BR_CLOSED,
        SQ_BR_OPEN,
        SQ_BR_CLOSED,
        COLUMN,
        COMMA,
        STRING,
        NUMBER,
        TRUE_LITERAL,
        FALSE_LITERAL,
        NULL_LITERAL,
        END,
        UNKNOWN
    };

    Token(Type t, string const &v): type_(t), value_(v) {}
    Token(Type t): type_(t), value_("") {}

    Type type() const { return type_; }
    string const& value() const { return value_; }
private:
    Type type_;
    string value_;
};

void SkipSpaces(istream &is) {
    while(is) {
        if(isspace(is.peek())) {
            is.get();
        } else {
            break;
        }
    }
}

Token ReadString(istream &is) {
    string word(1, is.get());
    while(is) {
        word.push_back(is.get());
        if(word.back() == '\"') {
            return Token(Token::Type::STRING, word);
        }
    }
    return Token(Token::Type::UNKNOWN, word);
}

string ReadDigits(istream &is) {
    string word;
    while(is) {
        if(isdigit(is.peek())) {
            word.push_back(is.get());
        } else {
            break;
        }
    }
    return word;
}

Token ReadNumber(istream &is) {
    string word;
    if(is.peek() == '-') {
        word.push_back(is.get());
    }
    if(is.peek() == '0') {
        word.push_back(is.get());
    } else {
        string digits = ReadDigits(is);
        if(digits.empty()) {
            return Token(Token::Type::UNKNOWN, word);
        }
        word += digits;
    }
    if(is.peek() == '.') {
        word.push_bach(is.get());
        digits = ReadDigits(is);
        if(digits.empty()) {
            return Token(Token::Type::UNKNOWN, word);
        }
        word += digits;
    }
    return word;
}

string ReadAlphas(istream &is) {
    string word;
    while(is) {
        if(isalpha(is.peek())) {
            word.push_back(is.get());
        } else {
            break;
        }
    }
    return word;
}

Token NextToken(istream &is) {
    SkipSpaces(is);
    if(!is) {
        return Token(Token::Type::END);
    }
    char ch = is.peek();
    if(ch == '{') {
        is.get();
        return Token(Token::Type::C_BR_OPEN);
    } else if(ch == '}') {
        is.get();
        return Token(Token::Type::C_BR_CLOSED);
    } else if(ch == '[') {
        is.get();
        return Token(Token::Type::SQ_BR_OPEN);
    } else if(ch == ']') {
        is.get();
        return Token(Token::Type::SQ_BR_CLOSED);
    } else if(ch == ':') {
        is.get();
        return Token(Token::Type::COLUMN);
    } else if(ch == ',') {
        is.get();
        return Token(Token::Type::COMMA);
    } else if(ch == '\"') {
        return ReadString(is);
    } else if(ch == '-' || isdigit(ch)) {
        return ReadNumber(is);
    } else {
        string word = ReadAlphas(is);
        if(word == "true") {
            return Token(Token::Type::TRUE_LITERAL);
        } else if(word == "false") {
            return Token(Token::Type::FALSE_LITERAL);
        } else if(word == "null") {
            return Token(Token::Type::NULL_LITERAL);
        }
        return Token(Token::Type::UNKNOWN, word);
    }
}