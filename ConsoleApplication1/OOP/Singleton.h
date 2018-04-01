#pragma once
#ifndef _SINGLETON_H
#define _SINGLETON_H

#include<iostream>
template <class T>
class CSingleton
{
public:
	static    void        release();
	static    T*  getInstance();
 
	          void       method();
private:
	static    T*  m_Instance;

	CSingleton();
	~CSingleton();
};
#endif
