#include "json_parser.h"

#include <fstream>
#include <cctype>

#include "lexer.h"

using std::istream;
using std::ifstream;
using std::string;
using std::shared_ptr;

using namespace json_cpp;

shared_ptr<ParseResult> ParseObject(istream &is);

shared_ptr<ParseResult> Parse(string const &file_path) {
    ifstream ifs(file_path);
    shared_ptr<ParseResult> res = ParseObject(ifs);
    if(res->type() == ParseResult::Type::SUCCESS && ifs) {
        // parsing succeeded but input still has some characters
        return std::make_shared<ParseError>(
            0, 0, "json file must contain one top level object"
        );
    } else {
        return res;
    }
}