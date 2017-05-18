set(SRC 
    json_model.cpp
    json.cpp
    json_parser.cpp
    lexer.cpp
    json_serializer.cpp
    json_ref.cpp
    json_basic.cpp
    json_mutable.cpp
    const_json_ref.cpp
)
add_library(json-cpp ${SRC})
target_include_directories (json-cpp PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})