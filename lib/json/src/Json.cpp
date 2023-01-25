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

    void Json::invalidCharacter()
    {
        std::string m;
        std::stringstream ms;
        ms << "invalid caracter at " << _pos;
        ms >> m;
        throw std::logic_error(m.c_str());        
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

    bool Json::isEndOfString()
    {
        if (_pos >= _s.length()) {
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

    bool Json::isEndOfAccolade()
    {
        if (_pos < _s.length())
        {
            if (_s[_pos] == ',' ||
                _s[_pos] <= ']' ||
                _s[_pos] <= '}')
                return true;
        }
        return false;    
    }
    

    bool Json::isBoolean()
    {
        if (!isEndOfString())
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

        while (!isEndOfString())
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
                invalidCharacter();
            if (j != NULL)
                break;
        }

        return j;

    };

    JsonValue *Json::parseObject()
    {
        JsonObject *j = new JsonObject();
        JsonValue *value = NULL;
        
        std::string key;
        size_t i;

        if (_s[_pos] == '{')
            _pos++;

        while (!isEndOfString())
        {
            while (isWhitespace()) {
                _pos++;
            }

            if (_s[_pos] == '}')
                break;           

            if (_s[_pos] == '"')
                _pos++;
            else
                invalidCharacter();
            
            key.resize(255, 0);
            i = 0;
            while (_pos < _s.length())
            {
                if (_s[_pos] == '"'){
                    _pos++;
                    break;
                }

                key[i] = _s[_pos];
                i++;
                _pos++;
            }
            key.resize(i, '\0');

            while (isWhitespace()) {
                _pos++;
            }

            if (_s[_pos] == ':')
                _pos++;
            else
                invalidCharacter();
            
            value = parseValue();

            j->put(key, value);

            while (isWhitespace()) {
                _pos++;
            }

            if (_s[_pos] == ',')
                _pos++;
            else if (_s[_pos] == '}')
                break;
            else
                invalidCharacter();


        }
        if (!isEndOfString() && _s[_pos] == '}')
            _pos++;

        return j;
    };

    JsonValue *Json::parseArray()
    {
        JsonValue *j = new JsonArray();

        if (_s[_pos] == '[')
            _pos++;

        while (isWhitespace()) {
            _pos++;
        }
        
        if (isEndOfString())
            invalidCharacter();

        if (_s[_pos] != ']') {

            while (_pos < _s.length())
            {

                JsonValue *jval = parseValue();
                j->push(jval);

                while (isWhitespace()) {
                    _pos++;
                }
                if (_s[_pos] == ']'){
                    break;
                }else if (_s[_pos] == ',')
                    _pos++;
                else
                    invalidCharacter();
            }
        } else {
            _pos++;
        }

        return j;
    }

    JsonValue *Json::parseString()
    {
        JsonString *j = new JsonString();    
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
                   invalidCharacter();
                }
            }
            else
                buf[i] = _s[_pos];
            i++;
            _pos++;

            if ( i == buf.capacity()) {
                buf.resize(buf.capacity() * 2, 0);
            }
        }

        buf.resize(i, '\0');

        if (_s[_pos] == '"')
            _pos++;

        if (!(isEndOfString() || isWhitespace() || isEndOfAccolade()))
            invalidCharacter();

        j->set(buf);
        return j;
    }

    JsonValue *Json::parseNumber()
    {
        JsonNumber *j = new JsonNumber();

        bool negative = false;
        float divFraction = 1;
        float fraction = 0;
        float value = 0;

        if (_s[_pos] == '+')
            _pos++;

        if (_s[_pos] == '-') {
           _pos++;
            negative = true;
        }

        if (!isDigit()) {
            invalidCharacter();
        }

        while (isDigit()) {
            value = (value * 10) + (_s[_pos] - '0');
            _pos++;
        }
        
        if(_s[_pos] == '.') {

            _pos++;

            if (!isDigit()) {
                invalidCharacter();
            }

            while (isDigit()) {
                divFraction /= 10;
                fraction = (fraction * 10) + (_s[_pos] - '0');
                _pos++;
            }
            fraction = fraction * divFraction;
        }

        if (!(isEndOfString() || isWhitespace() || isEndOfAccolade()))
            invalidCharacter();

        // TODO Exponent

        if (negative)
                value *= -1;
        j->set(value + fraction);
        return j;
    }

    JsonValue *Json::parseBoolean()
    {
        JsonBoolean *j = new JsonBoolean();

        if (_s.compare(_pos, 4, "true") == 0)
            j->set(true);
        else if (_s.compare(_pos, 4, "false") == 0)
            j->set(false);
        _pos += 4;

        if (!(isEndOfString() || isWhitespace() || isEndOfAccolade()))
            invalidCharacter();

        return j;
    }

    JsonValue *Json::parseNull()
    {
        JsonValue *j = new JsonValue();
        _pos += 4;

        if (!(isEndOfString() || isWhitespace() || isEndOfAccolade()))
            invalidCharacter();

        return j;
    }
}


