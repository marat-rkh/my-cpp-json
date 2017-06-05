# my-cpp-json
C++ 11 json library (written just for fun)

## Features overview

### Parsing and serialization

```cpp
#include "my_cpp_json.h"
using namespace my_cpp_json;

// 1. Parse
JsonParser parser;
Json json = parser.Parse("path/to/json_file.json");

// 2. Serialize
JsonSerializer ser;
// convert to string
string res = ser.PrettyPrint(json);
// or print to any output stream
ofstream ofs("result.json");
ser.PrettyPrint(json, ofs);
// you can also print without any formatting to make result compact
string compact = ser.CompactPrint(json);
```

### Working with json 

```cpp
#include "my_cpp_json.h"
using namespace my_cpp_json;

// 1. Create json object
Json json {
    {"Name", "Mark Menders"},
    {"Age", 31},
    {"Additional info", {
        {"Has a driver's license", true}
    }},
    {"Interests", Json::arr({"cooking", "reading", "table tennis"})}
};

// 2. Access fields
int age = json["Age"].AsDouble();
bool b = json["Additional info"]["Has a driver's license"].AsBool();

// 3. Check json value type
json["Name"].Type() == JType::JSTRING; // true
json["Additional info"].Type() == JType::JOBJECT; // true
```
