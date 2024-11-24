#pragma once
#include "Functions.h"

template <typename T>
class Node
{
public:
	T car;
	Node* next;
	Node* prev;
};