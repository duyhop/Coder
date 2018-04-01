#pragma once
#ifndef _CSUBSINGLETON_H
#define _CSUBSINGLETON_H

#include "Singleton.h"


class CsubSingleton
{
public:
	bool isKeyDown(int KeyCode);

	CsubSingleton(void);
	~CsubSingleton(void);
};
#endif
