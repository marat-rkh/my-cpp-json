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

// Parser and serializer both preserves json object entries order
// and json array elements order
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
    {"Hobbies", Json::arr({"cooking", "reading", "table tennis"})}
};
// You can also create string
Json jstr = "str";
// number
Json jnum = 123;
// boolean
Json jbool = false;
// null value
Json jnull;
// array and object explicitly
Json jarr = Json::arr({});
Json jobj = Json::obj({});

// 2. Access fields
int age = json["Age"].AsDouble();
bool b = json["Additional info"]["Has a driver's license"].AsBool();
// Available conversions: AsDouble(), AsString(), AsBool(), AsNull()

// 3. Check json value type
json["Name"].Type() == JType::JSTRING; // true
json["Additional info"].Type() == JType::JOBJECT; // true
// Available types: JSTRING, JNUMBER, JOBJECT, JARRAY, JBOOL, JNULL

// 4. Work with sub objects through proxy types
// JsonRef behaves like Json&
// ConstJsonRef behaves like Json const&
ConstJsonRef cref = json["Additional info"]; // can call any const methods on cref
JsonRef ref = json["Additional info"]; // can call any Json methods on ref
// Json can be converted to JsonRef and ConstJsonRef
JsonRef just_ref = json; // no copy of the original json is created
// JsonRef and ConstJsonRef can be converted to Json
Json copy = cref; // creates copy of the whole object referenced by cref;
Json also_copy = json["Additional info"]; // NOTE! this one also creates copy

// 5. Modify json
json["Name"] = "Matt Morris"; // assign new value of any type
json["Hobbies"] += "skiing"; // add new element to array
json["email"] = "m.morris@email.com" // add new field to object

// 6. Iterate json object and json array
// json object entries are iterated in the order 
// they were added to json object
for(auto it = json.ObjectBegin(); it != json.ObjectEnd(); ++it) {
    JsonRef val = (*it).second;
    if(val.Type() == JType::JSTRING) {
        cout << (*it).first << ": " << val.AsString() << endl;
    }
}
```
