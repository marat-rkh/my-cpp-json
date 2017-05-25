set(SRC 
    json_cpp/internal/lexer/lexer.cpp
    json_cpp/internal/proxy_impl/json_basic.cpp
    json_cpp/internal/repr/json_model.cpp
    json_cpp/const_json_ref.cpp
    json_cpp/json.cpp
    json_cpp/json_parser.cpp
    json_cpp/json_ref.cpp
    json_cpp/json_serializer.cpp
    json_cpp/json_type.cpp
)
add_library(json-cpp ${SRC})
target_include_directories (json-cpp PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/json_cpp)
target_include_directories (json-cpp PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/json_cpp/internal)
target_include_directories (json-cpp PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/json_cpp/internal/lexer)
target_include_directories (json-cpp PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/json_cpp/internal/proxy_impl)
target_include_directories (json-cpp PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/json_cpp/internal/repr)
target_include_directories (json-cpp PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/json_cpp/internal/utils)