set(SRC 
    mylib.cpp
)
add_library(json-parser ${SRC})
target_include_directories (json-parser PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})