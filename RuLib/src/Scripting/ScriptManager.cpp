#include "SCripting/ScriptManager.h"
#include "Transform.h"

#include <fstream>
#include <iostream>
#include <sstream>

ScriptManager::ScriptManager()
{
    
}

ScriptManager::~ScriptManager()
{

}

void ScriptManager::LoadScripts(std::string filePath)
{
    std::ifstream stream;
   
    std::string str;
    RuScript scr;
    
    stream.open(filePath);

    int line = 0;

    while (std::getline(stream, str))
    {
        std::stringstream str_stream(str);
        std::vector<std::string> words;
        bool skipLine = false;

        while (std::getline(str_stream, str, ' '))
        {
            if (str == CMD_COMMENT)
            {
                break;
            }
                scr.ScriptName = "TestScript";
                words.push_back(str);
        }

        if(words.size() != 0)
            scr.Lines.push_back(words);

        line++;
    }

    scripts.push_back(scr);
}

void ScriptManager::ParseScript()
{

}

int ScriptManager::ExecuteScript(RuScript _scr)
{
    auto oldClock = clock;

    if (waitTime <= 0.0f && isRunning)
    {
        std::string word;
        std::vector<std::string>& line = _scr.Lines[RunLine];

        word = _scr.Lines[RunLine][0];

        if (word == VAR_INT)
        {
            if (line[2] == OP_EQUAL)
            {
                CreateValue<int>(_scr, line[1], FLAG_TYPE_INT, std::stoi(line[3]));
            }
            else
            {
                CreateValue<int>(_scr, line[1], FLAG_TYPE_INT, 0);
            }
        }
        else if (word == VAR_BOOL)
        {
            if (line[2] == OP_EQUAL)
            {
                CreateValue<bool>(_scr, line[1], FLAG_TYPE_BOOL, std::stoi(line[3]));
            }
            else
            {
                CreateValue<bool>(_scr, line[1], FLAG_TYPE_BOOL, false);
            }
        }
        else if (word == VAR_FLOAT)
        {
            if (line[2] == OP_EQUAL)
            {
                CreateValue<float>(_scr, line[1], FLAG_TYPE_FLOAT, std::stof(line[3]));
            }
            else
            {
                CreateValue<float>(_scr, line[1], FLAG_TYPE_FLOAT, 0.0f);
            }
        }
        else if (word == VAR_STRING)
        {
            if (line[2] == OP_EQUAL)
            {
                CreateValue<std::string>(_scr, line[1], FLAG_TYPE_STRING, line[3]);
            }
            else
            {
                CreateValue<std::string>(_scr, line[1], FLAG_TYPE_STRING, "");
            }
        }

        else if (word == CMD_IF)
        {
            //Gets PARAM, GET OPERATOR, GET PARAM2
            //Define variable types
            bool isTrue = false;

            if (_scr.values[line[1]]->type == FLAG_TYPE_INT)
                isTrue = ExecuteOperation<int>(_scr.values[line[1]], line[2], _scr.values[line[3]]);
            else if (_scr.values[line[1]]->type == FLAG_TYPE_FLOAT)
                isTrue = ExecuteOperation<float>(_scr.values[line[1]], line[2], _scr.values[line[3]]);
            else if(_scr.values[line[1]]->type == FLAG_TYPE_BOOL)
                isTrue = ExecuteOperation<bool>(_scr.values[line[1]], line[2], _scr.values[line[3]]);
            else if (_scr.values[line[1]]->type == FLAG_TYPE_STRING)
                isTrue = ExecuteOperation<bool>(_scr.values[line[1]], line[2], _scr.values[line[3]]);

            if (isTrue)
            {
                RunLine++;
            }
            else
            {
                RunLine += 2;
            }
            return 0;
        }

        else if (word == CMD_PRINT)
        {
            for (int j = 1; j < line.size(); j++)
            {
                if (_scr.values.find(line[j]) != _scr.values.end())
                {
                    PrintValue(_scr, line[j]);
                }
                else
                {
                    std::cout << " " << line[j] << " ";
                }
            }

            std::cout << std::endl;
        }

        else if (word == CMD_STOP)
        {
            isRunning = false;
        }

        else if (word == CMD_WAIT)
        {
            waitTime = std::stof(line[1]);
            clock = std::chrono::high_resolution_clock::now();

            return 0;
        }

        else if (word == CMD_GOTO)
        {
            RunLine = std::stoi(line[1]);
        }

        else if (word == CMD_MOVE)
        {
            if (!_scr.entity)
            {
                std::cout << "NO OWNER SET, CANNOT EXECUTE MOVE COMMAND" << std::endl;
                
            }
            else
            {
                sf::Vector2f newPos;

                newPos.x = line[1][0] - '0';
                newPos.y = line[1][2] - '0'; 

                _scr.entity->GetComponent<ru::TransformComponent>().transform.pos = newPos;

                //std::cout << _scr.Owner->position.x << " " << _scr.Owner->position.y << std::endl;
            }
        }

        //Check if its a value, if true, assume its an operation
        else if (_scr.values.find(word) != _scr.values.end())
        {
            //Get Value

                //Perform Operation on value
                /*GetOperation(line[j + 1]);*/

                //Get Next Value
                //std::string value2 = line[j + 2];

            if (_scr.values.find(word) != _scr.values.end())
            {

            }
        }

        if (RunLine < _scr.Lines.size() - 1)
            RunLine++;

        return 0;
    }

    oldClock = clock;

    clock = std::chrono::high_resolution_clock::now();
    std::chrono::duration<float> dt2(clock - oldClock);
    waitTime -= dt2.count();

    if (waitTime <= 0.0f)
        RunLine++;

    return 0;
}

std::string ScriptManager::GetName(int& _i)
{
    int j = _i + 1;
    std::string name;
    std::string line = scripts[RunningScript].Lines[RunLine][0];

    while (line[j] != *CMD_STR_END)
    {
        name += line[j];
        j += 1;
    }

    _i = j;

    return name;
}

void ScriptManager::PrintValue(RuScript& execScript, std::string _name)
{
    ValueInterface* v_in = execScript.values[_name];

    if (v_in->type == FLAG_TYPE_INT)
    {
        Value<int>* val = static_cast<Value<int>*>(v_in);
        std::cout << " " << _name << " " << val->v << " ";
    }
    else if (v_in->type == FLAG_TYPE_BOOL)
    {
        Value<bool>* val = static_cast<Value<bool>*>(v_in);
        std::cout << " " << _name << " " << val->v << " ";
    }
    else if (v_in->type == FLAG_TYPE_FLOAT)
    {
        Value<float>* val = static_cast<Value<float>*>(v_in);
        std::cout << " " << _name << " " << val->v << " ";
    }
    else if (v_in->type == FLAG_TYPE_STRING)
    {
        Value<std::string>* val = static_cast<Value<std::string>*>(v_in);
        std::cout << " " << _name << " " << val->v << " ";
    }

    //std::cout << std::endl;
}

template<typename T>
void ScriptManager::CreateValue(RuScript& execScript, std::string _name, char flag,  T value)
{
    Value<T>* val = new Value<T>();
    val->type |= flag;
    val->v = value;

    execScript.values[_name] = val;
}

template<typename T>
bool ScriptManager::ExecuteOperation(ValueInterface* _paramA, std::string _op, ValueInterface* _paramB)
{
    Value<T>* pA = static_cast<Value<T>*>(_paramA);
    Value<T>* pB = static_cast<Value<T>*>(_paramB);

    if (_op == OP_BIGGER_THAN)
    {
        if (pA->v > pB->v)
        {
            return true;
        }
    }
    else if (_op == OP_BIGGER_THAN_EQUAL)
    {
        if (pA->v >= pB->v)
        {
            return true;
        }
    }
    else if (_op == OP_SMALLER_THAN)
    {
        if (pA->v < pB->v)
        {
            return true;
        }
    }
    else if (_op == OP_SMALLER_THAN_EQUAL)
    {
        if (pA->v <= pB->v)
        {
            return true;
        }
    }
    else if (_op == OP_ISEQUAL)
    {
        if (pA->v == pB->v)
        {
            return true;
        }
    }
    else if (_op == OP_ISNOTEQUAL)
    {
        if (pA->v != pB->v)
        {
            return true;
        }
    }

    return false;
}
