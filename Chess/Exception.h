#pragma once
#include "Header.h"

class PositionOutOfRangeException : public exception
{
public:
};

class UninitializedException : public exception
{
public:

};

class WrongConnection : public exception {
public:

};