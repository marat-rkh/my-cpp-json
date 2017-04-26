set(SRC 
    json_value.cpp
)
add_library(json-cpp ${SRC})
target_include_directories (json-cpp PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})