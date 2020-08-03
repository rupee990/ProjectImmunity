#pragma once

namespace ru
{
    class Engine;
}

/*
*   Class which has access to Engine.
*/
class RUClass
{
public:
    RUClass(ru::Engine* a_engine) { m_engine = a_engine; };
    ~RUClass() {};

    ru::Engine* m_engine;
};