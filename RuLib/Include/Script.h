#pragma once
#include <vector>
#include <string>
#include <map>
#include "ECS.h"

class Object;

//Commands
#define CMD_GOTO "GOTO" //Goes to line
#define CMD_EXECLINE "." //Defines that this line executes code
#define CMD_COMMENT "//"
#define CMD_PRINT "PRINT"
#define CMD_IF "?"
#define CMD_STR_BEGIN "["
#define CMD_STR_END "]"
#define CMD_STOP "stp" //Stops the script
#define CMD_WAIT "WAIT"

//Game Specific commands
#define CMD_OWNER "OWNER" // Gets Owner
#define CMD_PLAYER "PLAYER" // Gets Player
#define CMD_POS "POS"
#define CMD_MOVE "MOVE"     //Moves object to value
#define CMD_CREATE_OBJ "OBJ" //Creates an OBJ
#define CMD_DISTANCE "DIST" //checks distance of 1 & 2 and stores it in 4

//Variables TYPE [IDENTIFIER] VALUE/VALUES
//Ex.: v2 Position 1,1
#define VAR_INT "#"
#define VAR_STRING "@"
#define VAR_BOOL "b"
#define VAR_FLOAT "f"
#define VAR_VECTOR2 "v2"

//Simple Operations
#define OP_ADD "+"
#define OP_SUB "-"
#define OP_DIVIDE "/"
#define OP_MULTIPLY "*"
#define OP_EQUAL ":"
#define OP_ISEQUAL "::"
#define OP_ISNOTEQUAL "!:"
#define OP_BIGGER_THAN ">"
#define OP_BIGGER_THAN_EQUAL ">:"
#define OP_SMALLER_THAN "<"
#define OP_SMALLER_THAN_EQUAL "<:"

//Type Flags
#define FLAG_TYPE_INT    1 << 1
#define FLAG_TYPE_STRING 1 << 2
#define FLAG_TYPE_FLOAT  1 << 3
#define FLAG_TYPE_BOOL   1 << 4


//Value Structs
struct ValueInterface
{
    int m_size;
    char type;
    ~ValueInterface() = default;
};

template <typename T>
struct Value : public ValueInterface
{
    T v;
};

class RuScript : public Component
{
public:

    std::string ScriptName;
    std::vector< std::vector<std::string>> Lines;
    std::map< std::string, ValueInterface*> values;
};