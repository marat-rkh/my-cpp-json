set(SRC 
    my_cpp_json/internal/lexer/lexer.cpp
    my_cpp_json/internal/proxy_impl/json_basic.cpp
    my_cpp_json/internal/repr/json_model.cpp
    my_cpp_json/const_json_ref.cpp
    my_cpp_json/json.cpp
    my_cpp_json/json_parser.cpp
    my_cpp_json/json_ref.cpp
    my_cpp_json/json_serializer.cpp
    my_cpp_json/json_type.cpp
)
add_library(my-cpp-json ${SRC})
target_include_directories (my-cpp-json PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/my_cpp_json)
target_include_directories (my-cpp-json PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/my_cpp_json/internal)
target_include_directories (my-cpp-json PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/my_cpp_json/internal/lexer)
target_include_directories (my-cpp-json PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/my_cpp_json/internal/proxy_impl)
target_include_directories (my-cpp-json PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/my_cpp_json/internal/repr)
target_include_directories (my-cpp-json PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/my_cpp_json/internal/utils)