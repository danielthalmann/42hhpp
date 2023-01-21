#include <Json.hpp>
#include <sstream>

namespace json
{
    Json::Json(const std::string &s)
    {
        _s = s;
        _pos = 0;
    }

    Json::~Json()
    {

    }

	bool Json::isWhitespace()
    {
        if (_pos < _s.length())
        {
            if (_s[_pos] == ' ' ||
                _s[_pos] == '\n' ||
                _s[_pos] == '\r' ||
                _s[_pos] == '\t')
                return true;
        }
        return false;
    }

	bool Json::isNumber()
    {
        if (_pos < _s.length())
        {
            if (_s[_pos] == '-' ||
                _s[_pos] == '+' ||
                isDigit())
                return true;
        }
        return false;
    }
    
    bool Json::isDigit()
    {
        if (_pos < _s.length())
        {
            if (_s[_pos] >= '0' &&
                 _s[_pos] <= '9')
                return true;
        }
        return false;
    }

    bool Json::isBoolean()
    {
        if (_pos < _s.length())
        {
            
            if (_s.compare(_pos, 4, "true") == 0 ||
                _s.compare(_pos, 4, "false") == 0 )
                return true;
        }
        return false;
    }

    bool Json::isNull()
    {
        if (_pos < _s.length())
        {
            
            if (_s.compare(_pos, 4, "null") == 0)
                return true;
        }
        return false;
    }

    JsonValue *Json::parseValue()
    {

        JsonValue *j = NULL;

        while (_pos < _s.length())
        {
            if(isWhitespace())
                _pos++;
            else if (_s[_pos] == '{')
                j = parseObject();
            else if (_s[_pos] == '[')
                j = parseArray();
            else if (_s[_pos] == '"')
                j = parseString();
            else if (isNumber())
                j = parseNumber();
            else if (isBoolean())
                j = parseBoolean();
            else if (isNull())
                j = parseNull();
            else
                throw std::exception();

        }

        return j;

    };

    JsonValue *Json::parseObject()
    {

        JsonValue *j = new JsonObject();
        return j;

    };

    JsonValue *Json::parseArray()
    {
        return NULL;
    }

    JsonValue *Json::parseString()
    {
        JsonValue *j = new JsonString();
        std::string buf(255, 0);
        size_t i = 0;

        if (_s[_pos] == '"')
            _pos++;

        while (_pos < _s.length())
        {
            if (_s[_pos] == '"'){
                break;
            }

            if (_s[_pos] == '\\')
            {
                _pos++;
                if (_pos < _s.length())
                {
                    switch (_s[_pos])
                    {
                    case '"':
                    case '\\':
                    case '/':
                        buf[i] = _s[_pos];
                        break;
                    case 'b':
                        buf[i] = '\b';
                        break;
                    case 'f':
                        buf[i] = '\f';
                        break;
                    case 'n':
                        buf[i] = '\n';
                        break;
                    case 'r':
                        buf[i] = '\r';
                        break;
                    case 't':
                        buf[i] = '\t';
                        break;
                    case 'u':
                        // TODO 4 digit for 1 caracter
                        break;
                    
                    default:
                        buf[i] = _s[_pos];
                        break;
                    }

                } else {
                    std::string m;
                    std::stringstream ms;
                    ms << "invalid caracter at " << _pos;
                    ms >> m;
                    throw std::logic_error(m.c_str());
                }
            }
            else
                buf[i] = _s[_pos];
            i++;
            _pos++;
        }

        if (_s[_pos] == '"')
            _pos++;

        j->set(buf);
        return j;
    }

    JsonValue *Json::parseNumber()
    {
        return NULL;
    }

    JsonValue *Json::parseBoolean()
    {
        return NULL;
    }

    JsonValue *Json::parseNull()
    {
        return NULL;
    }
}


