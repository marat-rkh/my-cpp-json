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
    explicit ParsedJson(std::shared_ptr<JsonObject> const &value): value_(value) {}

    Type type() const override { return Type::JSON; }
    std::shared_ptr<JsonObject> const& value() const { return value_; }
private:
    std::shared_ptr<JsonObject> value_;
};

class JsonParser {
public:
    std::shared_ptr<ParseResult> Parse(std::string const &file_path);
private:
    void Error(std::string const &msg, unsigned int line, unsigned int pos);

    std::shared_ptr<JsonObject> ParseObject();
    std::pair<std::string, std::shared_ptr<JsonValue>> ParseKeyValue();

    internal::lexer::Lexer lexer_;
    
    bool error_occured_ = false;
    std::string error_msg_;
    unsigned int error_line_ = 0;
    unsigned int error_pos_ = 0;
};

}

#endif