#ifndef __JSON_PARSER_H__
#define __JSON_PARSER_H__

#include <string>
#include <stdexcept>

#include "my_cpp_json.h"
#include "lexer.h"

namespace my_cpp_json {

class JsonParser {
public:
    Json Parse(std::string const &file_path);
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

struct JsonParseException: public std::runtime_error {
    explicit JsonParseException(
        std::string const &msg, 
        unsigned int line = 0,
        unsigned int pos = 0
    )
        : std::runtime_error(msg)
        , error_line_(line)
        , error_pos_(pos)
    {}

    unsigned line() const noexcept { return error_line_; }
    unsigned pos() const noexcept { return error_pos_; }
private:
    unsigned int error_line_ = 0;
    unsigned int error_pos_ = 0;
};

}

#endif