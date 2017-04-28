#ifndef __LEXER_H__
#define __LEXER_H__

#include <string>
#include <istream>

namespace json_cpp {
namespace internal {
namespace lexer {

using std::string;
using std::istream;

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
    explicit Token(Type t): Token(t, "") {}

    bool operator==(Token const &other) const {
        return type_ == other.type_ && value_ == other.value_;
    }

    Type type() const { return type_; }
    string const& value() const { return value_; }
private:
    Type type_;
    string value_;
};

class Lexer {
public:
    explicit Lexer(istream &is): is_(is) {}

    Token GetToken();
    Token const& PeekToken();
private:
    istream &is_;
    bool peeked_ = false;
    Token peeked_token_ = Token(Token::Type::UNKNOWN);
};

}
}
}

#endif