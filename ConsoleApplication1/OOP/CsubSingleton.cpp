#include "CsubSingleton.h"

CsubSingleton::CsubSingleton(void)
{
}


CsubSingleton::~CsubSingleton(void)
{
}

bool CsubSingleton::isKeyDown(int KeyCode)
{
	std::cout << KeyCode << std::endl;
	return true;
}