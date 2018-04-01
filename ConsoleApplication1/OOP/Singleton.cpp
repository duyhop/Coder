#include "CsubSingleton.h"
template <class T>
T *CSingleton<T>::m_Instance = NULL;

template <class T>
CSingleton<T>::CSingleton(void)
{
}

template <class T>
CSingleton<T>::~CSingleton(void)
{
}

template <class T>
T* CSingleton<T>::getInstance()
{
	if(m_Instance == NULL)
		m_Instance = new  T();
	return m_Instance;
}

template <class T>
void CSingleton<T>::method()
{
	std::cout << "This is singleton parttern";
}

template <class T>
void CSingleton<T>::release()
{
	if (m_Instance)
	{
		delete m_Instance;
		m_Instance = NULL;
	}
}
