#include <iostream>
#include <map>
#include <string>
#include "EventHandler.h"
template<typename...Args>
class Event
{
	using m_func = BasicalEventHandler<Args...>*;
private:
	std::map<int,m_func> HandlerList; 
	m_func m_handler;
	int defultKey;
public:
	//���캯��ȫ����ʼ��Ϊ��
	Event()
	{
		m_handler = nullptr;
		defultKey = 0;
	}
	//�º�������̬������lambda���ʽ
	template <typename T>
	int connect(T func)
	{
		auto handler = new CommonEventHandler<T, Args...>(func);
		defultKey++;
		HandlerList.insert(std::pair<int, m_func>(defultKey, handler));
		return defultKey;
	}
	//ȫ�ֺ���
	template <typename T>
	int connect(T* func)
	{
		auto handler = new CommonEventHandler<T*, Args...>(func);
		defultKey++;
		HandlerList.insert(std::pair<int, m_func>(defultKey,handler));
		return defultKey;
	}
	//������Ա����
	template <typename T>
	int connect(T* receiver, void(T::* func)(Args...))
	{
		auto handler = new ClassEventHandler<T, Args...>(receiver, func);
		defultKey++;
		HandlerList.insert(std::pair<int, m_func>(defultKey, handler));
		return defultKey;
		
	}
	bool disconncet(int funcNumber)
	{
		delete HandlerList.at(funcNumber);
		HandlerList.erase(funcNumber);
		return HandlerList.count(funcNumber) == 1;
	}
	//�����ź�Ҳ���Ǵ���֮ǰ����º���
	void emit(Args&...args)
	{
		for (auto it = HandlerList.begin(); it != HandlerList.end(); it++)
		{
			(*it->second)(args...);
		}
	}
	void emit(Args&&...args)
	{
		for (auto it = HandlerList.begin(); it != HandlerList.end(); it++)
		{
			(*it->second)(args...);
		}
	}
};