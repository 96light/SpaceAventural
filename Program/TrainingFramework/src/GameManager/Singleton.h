#pragma once


template <class T>
class CSingleton
{
public:
	static T* GetInstance()
	{
		if(s_instance == 0)
			s_instance = new T;
		return s_instance;
	}

	static bool HasInstance()
	{
		return s_instance != 0;
	}
	static void FreeInstance()
	{
		if(s_instance)
		{
			delete s_instance;
			s_instance = 0;
		}
	}
protected:
	CSingleton()
	{
		s_instance = (T*)this;
	}
	virtual ~CSingleton(){
		s_instance = 0;
	}
private:
	static T* s_instance;
};

template <class T> T* CSingleton<T>::s_instance = 0;


