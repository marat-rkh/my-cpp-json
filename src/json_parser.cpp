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
using json_cpp::JsonString;
using json_cpp::JsonNumber;
using json_cpp::JsonBool;
using json_cpp::JsonNull;
using json_cpp::JsonArray;

shared_ptr<ParseResult> json_cpp::JsonParser::Parse(string const &file_path) {
    ifstream ifs(file_path);
    lexer_.init(&ifs);
    auto res = ParseJObject();
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

shared_ptr<JsonObject> json_cpp::JsonParser::ParseJObject() {
    if(lexer_.GetToken().type() != Token::Type::C_BR_OPEN) {
        Error("expected '{' at the beginning of json object");
        return shared_ptr<JsonObject>();
    }
    map<string, shared_ptr<JsonValue>> values;
    if(lexer_.PeekToken().type() == Token::Type::C_BR_CLOSED) {
        return make_shared<JsonObject>(values);
    }
    while(true) {
        auto res = ParseKeyValue();
        if(error_occured_) {
            return shared_ptr<JsonObject>();
        }
        values.insert(res);
        if(lexer_.PeekToken().type() == Token::Type::COMMA) {
            lexer_.GetToken();
        } else {
            break;
        }
    }
    if(lexer_.GetToken().type() != Token::Type::C_BR_CLOSED) {
        Error("expected '}' at the end of json object");
        return shared_ptr<JsonObject>();
    }
    return make_shared<JsonObject>(values);
}

pair<string, shared_ptr<JsonValue>> json_cpp::JsonParser::ParseKeyValue() {
    auto key = lexer_.GetToken();
    if(key.type() != Token::Type::STRING) {
        Error("expected string as field name");
        return {"", shared_ptr<JsonValue>()};
    }
    if(lexer_.GetToken().type() != Token::Type::COLUMN) {
        Error("expected ':' after field name");
        return {"", shared_ptr<JsonValue>()};
    }
    auto val = ParseJValue();
    if(error_occured_) {
        return {"", shared_ptr<JsonValue>()};
    }
    return {key.value(), val};
}

shared_ptr<JsonValue> json_cpp::JsonParser::ParseJValue() {
    if(lexer_.PeekToken().type() == Token::Type::STRING) {
        return make_shared<JsonString>(lexer_.GetToken().value());
    }
    if(lexer_.PeekToken().type() == Token::Type::NUMBER) {
        return make_shared<JsonNumber>(std::stod(lexer_.GetToken().value()));
    }
    if(lexer_.PeekToken().type() == Token::Type::TRUE_LITERAL) {
        lexer_.GetToken();
        return make_shared<JsonBool>(true);
    }
    if(lexer_.PeekToken().type() == Token::Type::FALSE_LITERAL) {
        lexer_.GetToken();
        return make_shared<JsonBool>(false);
    }
    if(lexer_.PeekToken().type() == Token::Type::NULL_LITERAL) {
        lexer_.GetToken();
        return JsonNull::GetPtr();
    }
    if(lexer_.PeekToken().type() == Token::Type::SQ_BR_OPEN) {
        auto arr = ParseJArray();
        if(error_occured_) {
            return shared_ptr<JsonValue>();
        }
        return arr;
    }
    if(lexer_.PeekToken().type() == Token::Type::C_BR_OPEN) {
        auto j_obj = ParseJObject();
        if(error_occured_) {
            return shared_ptr<JsonValue>();
        }
        return j_obj;
    }
    Error("invalid json value declaration");
    return shared_ptr<JsonValue>();
}

shared_ptr<JsonArray> json_cpp::JsonParser::ParseJArray() {
    return shared_ptr<JsonArray>();
}