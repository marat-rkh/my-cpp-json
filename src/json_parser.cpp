#include "json_parser.h"

#include <fstream>
#include <cctype>
#include <map>
#include <utility>
#include <string>

#include "lexer.h"

using std::istream;
using std::ifstream;
using std::string;
using std::shared_ptr;
using std::make_shared;
using std::map;
using std::pair;

using json_cpp::ParseResult;
using json_cpp::ParseError;
using json_cpp::ParsedJson;
using json_cpp::internal::lexer::Lexer;
using json_cpp::internal::lexer::Token;

using json_cpp::as;

using json_cpp::JsonObject;
using json_cpp::JsonValue;

shared_ptr<ParseResult> json_cpp::JsonParser::Parse(string const &file_path) {
    ifstream ifs(file_path);
    lexer_.init(&ifs);
    auto res = ParseObject();
    if(error_occured_) {
        return make_shared<ParseError>(error_line_, error_pos_, error_msg_);
    } else if (ifs) {
        // parsing succeeded but input still has some characters
        return make_shared<ParseError>(
            0, 0, "json file must contain one top level object"
        );
    } else {
        return make_shared<ParsedJson>(res);
    }
}

void json_cpp::JsonParser::Error(std::string const &msg, unsigned int line, unsigned int pos) {
    error_occured_ = true;
    error_msg_ = msg;
    error_line_ = line;
    error_pos_ = pos;
}

shared_ptr<JsonObject> json_cpp::JsonParser::ParseObject() {
    if(lexer_.PeekToken().type() != Token::Type::C_BR_OPEN) {
        Error("expected '{' at the beginning of json object", 0, 0);
        return shared_ptr<JsonObject>();
    }
    map<string, shared_ptr<JsonValue>> values;
    do {
        lexer_.GetToken();
        auto res = ParseKeyValue();
        if(error_occured_) {
            return shared_ptr<JsonObject>();
        }
        values.insert(res);
    } while(lexer_.PeekToken().type() == Token::Type::COMMA);
    if(lexer_.GetToken().type() != Token::Type::C_BR_CLOSED) {
        Error("expected '}' at the end of json object", 0, 0);
        return shared_ptr<JsonObject>();
    }
    return make_shared<JsonObject>(values);
}

pair<string, shared_ptr<JsonValue>> json_cpp::JsonParser::ParseKeyValue() {
    return {"field", shared_ptr<JsonValue>()};
}