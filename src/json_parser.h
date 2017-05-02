#ifndef __JSON_PARSER_H__
#define __JSON_PARSER_H__

#include <string>
#include <memory>

#include "json_value.h"
#include "lexer.h"

namespace json_cpp {

class ParseResult {
public:
    enum class Type {
        ERROR,
        JSON
    };
    virtual Type type() const = 0;
};

class ParseError: public ParseResult {
public:
    ParseError(unsigned int line, unsigned int pos, std::string const &msg)
        : line_(line)
        , pos_(pos)
        , message_(msg)
    {}

    Type type() const override { return Type::ERROR; }
    unsigned int line() const { return line_; }
    unsigned int pos() const { return pos_; }
    std::string const& message() const { return message_; }
private:
    unsigned int line_;
    unsigned int pos_;
    std::string message_;
};

class ParsedJson: public ParseResult {
public:
    explicit ParsedJson(Json const &value): value_(value) {}

    Type type() const override { return Type::JSON; }
    Json const& value() const { return value_; }
private:
    Json value_;
};

class JsonParser {
public:
    using ParseResultPtr = std::shared_ptr<ParseResult>;

    ParseResultPtr Parse(std::string const &file_path);
private:
    void Error(std::string const &msg, unsigned int line = 0, unsigned int pos = 0);

    Json ParseJValue();
    Json ParseJObject();
    std::pair<std::string, Json> ParseKeyValue();
    Json ParseJArray();

    internal::lexer::Lexer lexer_;
    
    bool error_occured_ = false;
    std::string error_msg_;
    unsigned int error_line_ = 0;
    unsigned int error_pos_ = 0;
};

}

#endif