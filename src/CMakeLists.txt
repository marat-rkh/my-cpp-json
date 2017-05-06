set(SRC 
    json_model.cpp
    json.cpp
    json_parser.cpp
    lexer.cpp
    json_serializer.cpp
)
add_library(json-cpp ${SRC})
target_include_directories (json-cpp PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})