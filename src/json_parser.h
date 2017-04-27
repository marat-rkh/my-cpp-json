#ifndef __JSON_PARSER_H__
#define __JSON_PARSER_H__

#include <string>
#include <memory>

#include "json_value.h"

namespace json_cpp {

class ParseResult {
public:
    enum class Type {
        ERROR,
        SUCCESS
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
    explicit ParsedJson(std::shared_ptr<JsonValue> const &value): json_value_(value) {}

    Type type() const override { return Type::SUCCESS; }
    std::shared_ptr<JsonValue> const& json_value() const { return json_value_; }
private:
    std::shared_ptr<JsonValue> json_value_;
};

std::shared_ptr<ParseResult> Parse(std::string const &file_path);

}

#endif