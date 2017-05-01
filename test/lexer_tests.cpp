#include "gtest/gtest.h"
 
#include "lexer.h"

#include <fstream>
#include <vector>
#include <utility>
#include <string>

using namespace json_cpp::internal::lexer;
using Type = Token::Type;

using std::ifstream;
using std::vector;
using std::pair;
using std::string;

void HasTokens(ifstream &ifs, vector<pair<Token::Type, string>> expected) {
    Lexer lexer(&ifs);
    for(auto const& e: expected) {
        ASSERT_EQ(lexer.GetToken(), Token(e.first, e.second));
    }
}

TEST(lexer, should_peek) {
    ifstream ifs("data/empty_object.json");
    Lexer lexer(&ifs);
    Token expected(Type::C_BR_OPEN);
    ASSERT_EQ(lexer.PeekToken(), expected);
    ASSERT_EQ(lexer.PeekToken(), expected);
    ASSERT_EQ(lexer.GetToken(), expected);
    ASSERT_EQ(lexer.GetToken(), Token(Type::C_BR_CLOSED));
}

TEST(lexer, should_prcess_empty_object) {
    ifstream ifs("data/empty_object.json");
    HasTokens(ifs, {
        {Type::C_BR_OPEN, ""},
        {Type::C_BR_CLOSED, ""},
        {Type::END, ""}
    });
}

TEST(lexer, should_prcess_all_field_types) {
    ifstream ifs("data/all_field_types.json");
    HasTokens(ifs, {
        {Type::C_BR_OPEN, ""},

        {Type::STRING, R"("str_field")"},
        {Type::COLUMN, ""},
        {Type::STRING, R"("str_value")"},
        {Type::COMMA, ""},
        
        {Type::STRING, R"("arr_field")"},
        {Type::COLUMN, ""},
        {Type::SQ_BR_OPEN, ""},
        {Type::NUMBER, "1"},
        {Type::COMMA, ""},
        {Type::NUMBER, "2"},
        {Type::SQ_BR_CLOSED, ""},
        {Type::COMMA, ""},

        {Type::STRING, R"("num_field")"},
        {Type::COLUMN, ""},
        {Type::NUMBER, "-123.4"},
        {Type::COMMA, ""},

        {Type::STRING, R"("bool_field")"},
        {Type::COLUMN, ""},
        {Type::FALSE_LITERAL, ""},
        {Type::COMMA, ""},

        {Type::STRING, R"("null_field")"},
        {Type::COLUMN, ""},
        {Type::NULL_LITERAL, ""},
        {Type::COMMA, ""},

        {Type::STRING, R"("obj_field")"},
        {Type::COLUMN, ""},
        {Type::C_BR_OPEN, ""},
        {Type::C_BR_CLOSED, ""},
        
        {Type::C_BR_CLOSED, ""},

        {Type::END, ""}
    });
}

int main(int argc, char **argv) {
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}