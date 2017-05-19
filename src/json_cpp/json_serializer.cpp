#include "json_serializer.h"

#include <string>
#include <sstream>

using std::ostream;
using std::endl;
using std::string;
using std::stringstream;

namespace json_cpp {

void JsonSerializer::PrettyPrint(Json const &json, std::ostream &os, unsigned int indent_size) {
    indent_size_ = indent_size;
    compact_mode_ = false;
    Print(json, os, 0);
}

void JsonSerializer::CompactPrint(Json const &json, std::ostream &os) {
    indent_size_ = 0;
    compact_mode_ = true;
    Print(json, os, 0);
}

std::string JsonSerializer::PrettyPrint(Json const &json, unsigned int indent_size) {
    stringstream s;
    PrettyPrint(json, s, indent_size);
    return s.str();
}

std::string JsonSerializer::CompactPrint(Json const &json) {
    stringstream s;
    CompactPrint(json, s);
    return s.str();
}

void JsonSerializer::Print(
    ConstJsonRef const &json,
    std::ostream &os,
    unsigned int cur_indent
) {
    switch(json.Type()) {
        case JType::JSTRING: {
            os << '\"' << json.AsString() << '\"';
            break;
        }
        case JType::JNUMBER: {
            os << json.AsDouble();
            break;
        }
        case JType::JBOOL: {
            os << (json.AsBool() ? "true" : "false");
            break;
        }
        case JType::JNULL: {
            os << "null";
            break;
        }
        case JType::JOBJECT: {
            os << '{';
            unsigned int new_indent = cur_indent + indent_size_;
            bool not_first = false;
            for(auto it = json.ObjectBegin(); it != json.ObjectEnd(); ++it) {
                if(not_first) {
                    os << ',';
                } else {
                    not_first = true;
                }
                MaybeEndl(os);
                MaybeSpaces(os, new_indent);
                os << '\"' << (*it).first << ":";
                MaybeSpaces(os, 1);
                Print((*it).second, os, new_indent);
            }
            MaybeEndl(os);
            MaybeSpaces(os, cur_indent);
            os << '}';
            break;
        }
        case JType::JARRAY: {
            os << '[';
            unsigned int new_indent = cur_indent + indent_size_;
            bool not_first = false;
            for(auto it = json.ArrayBegin(); it != json.ArrayEnd(); ++it) {
                if(not_first) {
                    os << ',';
                } else {
                    not_first = true;
                }
                MaybeEndl(os);
                MaybeSpaces(os, new_indent);
                Print(*it, os, new_indent);
            }
            MaybeEndl(os);
            MaybeSpaces(os, cur_indent);
            os << ']';
            break;
        }
        default:
            throw std::runtime_error("unexcepted JType enum value");
    }
}

inline void JsonSerializer::MaybeEndl(std::ostream &os) {
    if(!compact_mode_) {
        os << endl;
    }
}

inline void JsonSerializer::MaybeSpaces(std::ostream &os, unsigned int spaces_number) {
    if(!compact_mode_) {
        os << string(spaces_number, ' ');
    }
}

}