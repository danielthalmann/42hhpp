#include <JsonObject.hpp>

namespace json
{
	JsonObject::JsonObject()
    {
        _valueType = json_type_object;
    }

	JsonObject::JsonObject(const JsonObject& other) : JsonValue()
    {
        *this = other;
    }

	JsonObject::~JsonObject()
    {
        clear();
    }

    JsonObject &JsonObject::operator=(const JsonObject& other)
    {
        clear();
        JsonValue *j;
        JsonBoolean *b;
        JsonNumber *n;
        JsonString *s;
        JsonObject *o;
        JsonArray *a;
        for (std::map<std::string, JsonValue*>::const_iterator it = other._value.begin(); it != other._value.end() ; ++it) {
            
            j = NULL;

            switch((*it).second->getValueType())
            {
                case json_type_boolean :
                    b = dynamic_cast<JsonBoolean *>((*it).second);
                    j = new JsonBoolean(*b);
                break;
                
                case json_type_number :
                    n = dynamic_cast<JsonNumber *>((*it).second);
                    j = new JsonNumber(*n);
                break;

                case json_type_string :
                    s = dynamic_cast<JsonString *>((*it).second);
                    j = new JsonString(*s);
                break;

                case json_type_object :
                    o = dynamic_cast<JsonObject *>((*it).second);
                    j = new JsonObject(*o);
                break;

                case json_type_array :
                    a = dynamic_cast<JsonArray *>((*it).second);
                    j = new JsonArray(*a);
                break;

                case json_type_null :
                default :
                    j = new JsonValue();
                break;
            }
            _value[(*it).first] = j;
        }

        return *this;
    }

    void JsonObject::clear()
    {
        for (std::map<std::string, JsonValue*>::iterator it = _value.begin(); it != _value.end() ; ++it) {
            if((*it).second)
                delete (*it).second;
        }
        _value.clear();
    }

	JsonValue *JsonObject::at(const std::string& s)
    {
        return _value.at(s);
    }

    bool JsonObject::exists(const std::string& s)
    {
        try {
            _value.at(s);
        } catch (std::exception &e)
        {
            (void) e;
            return false;
        }
        return true;
    }

	void JsonObject::put(const std::string& key, const int i)
    {
        JsonValue *j;
        try {
            j = at(key);
            delete j;
        } catch(std::exception &e) {
            // on ne fait rien
        }
        j = new JsonNumber();
        j->set(i);
        _value[key] = j;
    }

	void JsonObject::put(const std::string& key, const float f)
    {
        JsonValue *j;
        try {
            j = at(key);
            delete j;
        } catch(std::exception &e) {
            // on ne fait rien
        }
        j = new JsonNumber();
        j->set(f);
        _value[key] = j;
    }

	void JsonObject::put(const std::string& key, const std::string& s)
    {
        JsonValue *j;
        try {
            j = at(key);
            delete j;
        } catch(std::exception &e) {
            // on ne fait rien
        }
        j = new JsonString();
        j->set(s);
        _value[key] = j;
    }

	void JsonObject::put(const std::string& key, JsonValue* v)
    {
        try {
            JsonValue *j = at(key);
            delete j;
        } catch(std::exception &e) {
            // on ne fait rien
        }
        _value[key] = v;
    }

	void JsonObject::put(const std::string& key, JsonArray* a)
    {
        try {
            JsonValue *j = at(key);
            delete j;
        } catch(std::exception &e) {
            // on ne fait rien
        }
        _value[key] = a;
    }

	void JsonObject::put(const std::string& key, JsonObject* o)
    {
        try {
            JsonValue *j = at(key);
            delete j;
        } catch(std::exception &e) {
            // on ne fait rien
        }
        _value[key] = o;
    }

    std::size_t JsonObject::length() const
    {
        return _value.size();
    }

    std::vector<std::string> JsonObject::keys() const
    {
        std::vector<std::string> k;

        for (std::map<std::string, JsonValue *>::const_iterator it = _value.begin(); it != _value.end() ; ++it) {
            k.push_back((*it).first);
        }

        return k;
    }

}


