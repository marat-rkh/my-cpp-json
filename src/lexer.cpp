#include "lexer.h"

#include <cctype>
#include <stdexcept>

using std::istream;
using std::string;

using json_cpp::internal::lexer::Token;

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
        word.push_back(is.get());
        string digits = ReadDigits(is);
        if(digits.empty()) {
            return Token(Token::Type::UNKNOWN, word);
        }
        word += digits;
    }
    return Token(Token::Type::NUMBER, word);
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

void json_cpp::internal::lexer::Lexer::init(istream *is) { 
    is_ = is; 
    peeked_ = false;
}

Token json_cpp::internal::lexer::Lexer::GetToken() {
    if(!is_) {
        throw std::runtime_error("Attemp to use uninitialized lexer");
    }
    if(peeked_) {
        peeked_ = false;
        return peeked_token_;
    }
    return NextToken(*is_);
}

Token const &json_cpp::internal::lexer::Lexer::PeekToken() {
    if(!is_) {
        throw std::runtime_error("Attemp to use uninitialized lexer");
    }
    if(!peeked_) {
        peeked_token_ = NextToken(*is_);
        peeked_ = true;
    }
    return peeked_token_;
}