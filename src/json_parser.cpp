#include "json_parser.h"

#include <fstream>
#include <cctype>
#include <map>
#include <utility>
#include <string>
#include <vector>

#include "lexer.h"

using std::istream;
using std::ifstream;
using std::string;
using std::shared_ptr;
using std::make_shared;
using std::map;
using std::pair;
using std::vector;

using namespace json_cpp;
using namespace json_cpp::internal::lexer;

JsonParser::ParseResultPtr JsonParser::Parse(string const &file_path) {
    ifstream ifs(file_path);
    lexer_.init(&ifs);
    auto res = ParseJObject();
    if(error_occured_) {
        return make_shared<ParseError>(error_line_, error_pos_, error_msg_);
    } else if (lexer_.GetToken().type() != Token::Type::END) {
        // parsing succeeded but input still has some characters
        return make_shared<ParseError>(
            0, 0, "json file must contain one top level object"
        );
    } else {
        return make_shared<ParsedJson>(res);
    }
}

void JsonParser::Error(std::string const &msg, unsigned int line, unsigned int pos) {
    error_occured_ = true;
    error_msg_ = msg;
    error_line_ = line;
    error_pos_ = pos;
}

Json JsonParser::ParseJValue() {
    if(lexer_.PeekToken().type() == Token::Type::STRING) {
        return Json(lexer_.GetToken().value());
    }
    if(lexer_.PeekToken().type() == Token::Type::NUMBER) {
        return Json(std::stod(lexer_.GetToken().value()));
    }
    if(lexer_.PeekToken().type() == Token::Type::TRUE_LITERAL) {
        lexer_.GetToken();
        return Json(true);
    }
    if(lexer_.PeekToken().type() == Token::Type::FALSE_LITERAL) {
        lexer_.GetToken();
        return Json(false);
    }
    if(lexer_.PeekToken().type() == Token::Type::NULL_LITERAL) {
        lexer_.GetToken();
        return Json();
    }
    if(lexer_.PeekToken().type() == Token::Type::SQ_BR_OPEN) {
        auto arr = ParseJArray();
        if(error_occured_) {
            return Json();
        }
        return arr;
    }
    if(lexer_.PeekToken().type() == Token::Type::C_BR_OPEN) {
        auto j_obj = ParseJObject();
        if(error_occured_) {
            return Json();
        }
        return j_obj;
    }
    Error("invalid json value declaration");
    return Json();
}

Json JsonParser::ParseJObject() {
    if(lexer_.GetToken().type() != Token::Type::C_BR_OPEN) {
        Error("expected '{' at the beginning of json object");
        return Json();
    }
    if(lexer_.PeekToken().type() == Token::Type::C_BR_CLOSED) {
        lexer_.GetToken();
        return Json::MakeObject();
    }
    Json obj;
    while(true) {
        auto res = ParseKeyValue();
        if(error_occured_) {
            return Json();
        }
        obj += res;
        if(lexer_.PeekToken().type() == Token::Type::COMMA) {
            lexer_.GetToken();
        } else {
            break;
        }
    }
    if(lexer_.GetToken().type() != Token::Type::C_BR_CLOSED) {
        Error("expected '}' at the end of json object");
        return Json();
    }
    return obj;
}

pair<string, Json> JsonParser::ParseKeyValue() {
    auto key = lexer_.GetToken();
    if(key.type() != Token::Type::STRING) {
        Error("expected string as field name");
        return {"", Json()};
    }
    if(lexer_.GetToken().type() != Token::Type::COLUMN) {
        Error("expected ':' after field name");
        return {"", Json()};
    }
    auto val = ParseJValue();
    if(error_occured_) {
        return {"", Json()};
    }
    return {key.value(), val};
}

Json JsonParser::ParseJArray() {
    if(lexer_.GetToken().type() != Token::Type::SQ_BR_OPEN) {
        Error("expected '[' at the beginning of json array");
        return Json();
    }
    if(lexer_.PeekToken().type() == Token::Type::SQ_BR_CLOSED) {
        lexer_.GetToken();
        return Json::MakeArray();
    }
    Json arr;
    while(true) {
        auto res = ParseJValue();
        if(error_occured_) {
            return Json();
        }
        arr += res;
        if(lexer_.PeekToken().type() == Token::Type::COMMA) {
            lexer_.GetToken();
        } else {
            break;
        }
    }
    if(lexer_.GetToken().type() != Token::Type::SQ_BR_CLOSED) {
        Error("expected ']' at the end of json array");
        return Json();
    }
    return arr;
}