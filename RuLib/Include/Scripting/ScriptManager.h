#pragma once

#include "Script.h"

#include <time.h>
#include <chrono>
#include <map>

class ScriptManager
{
public:
    ScriptManager();
    ~ScriptManager();

    void LoadScripts(std::string filepath);
    void ParseScript();                     // Parse Script into the Struct and save it in vector
    int ExecuteScript(RuScript _scr);                   // Runs the Commands on script

    RuScript& GetScript(int _i) { RunningScript = _i;  return scripts[_i]; }

    template<typename T>
    void CreateValue(RuScript& execScript, std::string _name, char flag, T value);
    
    template <typename T>
    bool ExecuteOperation(ValueInterface* _paramA, std::string _op, ValueInterface* _paramB);

    void PrintValue(RuScript& execScript, std::string _name);

    std::string GetName(int& _i);

public:
    bool isRunning = true;

private:
    std::vector<RuScript> scripts;

    int RunLine = 0;
    int RunningScript = 0;

     //timer;
    float waitTime = 0.0f;
    std::chrono::time_point<std::chrono::steady_clock> clock;

    ru::Engine* m_engine;
    //float clock;
};