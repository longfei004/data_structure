#ifndef _LINKQUEUE_H_INCLUDED
#define _LINKQUEUE_H_INCLUDED

#include <iostream>
#include "node.h"
#include <cassert>		
#include "Assistance.h"


template <typename T>
class CLinkQueue
{
protected:
	CNode<T> *m_pFront, *m_pRear;        //头结点和尾结点指针

public:
	CLinkQueue();
	virtual ~CLinkQueue();	             // 析构函数
	void Clear();                        // 清空链队

	bool IsEmpty() const;                // 判断链队是否为空
	int GetLength() const;	             // 求链队长度	
	void Traverse(void(*Visit)(const T &)) const;             // 遍历链队
	Status GetHead(T &e) const;	                              // 取队头元素	
	Status DelQueue(T &e);		                              // 出队		
	Status EnQueue(const T &e);	                              // 入队
	CLinkQueue(const CLinkQueue<T> &q);                      // 复制构造函数
	CLinkQueue<T> &operator =(const CLinkQueue<T> &q);       // 重载赋值运算
};

template <typename T>
CLinkQueue<T>::CLinkQueue()                                  //构造空链队
{
	m_pRear = m_pFront = new CNode<T>;                       //生成链队头结点
	assert(m_pFront);                                        //构造失败，终止运行
	assert(m_pRear);
}

template <typename T>
CLinkQueue<T>::~CLinkQueue()
{
	Clear();
	delete m_pFront;
}

template <typename T>
//清除链队中的所有节点
void CLinkQueue<T>::Clear()     
{
	CNode<T> *p = m_pFront->m_pNext;
	while (p != nullptr)
	{
		m_pFront->m_pNext = p->m_pNext;
		delete p;
		p = m_pFront->m_pNext;
	}
	m_pRear = m_pFront;
}

template <typename T>
// 判断链队是否为空
bool CLinkQueue<T>::IsEmpty() const       
{
	return m_pFront == m_pRear;
}

template <class T>
// 操作结果：返回链队的长度 
int CLinkQueue<T>::GetLength() const
{
	int count = 0;		                                                // 初始化计数器 
	for (CNode<T> *p = m_pFront->m_pNext; p !=nullptr; p = p->m_pNext)
		count++;		                                                // 统计链队列中的结点数 
	return count;
}

template <class T>
// 操作结果：依次对链队的每个元素调用函数(*visit)访问
void CLinkQueue<T>::Traverse(void(*Visit)(const T &)) const
{
	for (CNode<T> *p = m_pFront->m_pNext; p != nullptr; p = p->m_pNext)
		(*Visit)(p->m_data);
}

template <class T>
// 操作结果：将链队头结点值用e返回
Status CLinkQueue<T>::GetHead(T &e) const
{
	if (!IsEmpty())
	{
		e = m_pFront->m_pNext->m_data;
		return SUCCESS;
	}
	else
	{
		cout << endl;
		cout << "ERROR: The queue is empty!" << endl;
		return UNDER_FLOW;
	}
}

template <class T>
// 操作结果：将链队头结点值用e返回，并删除队头
Status CLinkQueue<T>::DelQueue(T &e)
{
	if (!IsEmpty())
	{
		CNode<T> *p = m_pFront->m_pNext;
		e = p->m_data;
		m_pFront->m_pNext = p->m_pNext;
		if (m_pRear == p)    //出队前队列中只有一个元素
			m_pRear = m_pFront;
		delete p;
		return SUCCESS;
	}
	else
	{
		cout << endl;
		cout << "ERROR: The queue is empty!" << endl;
		return UNDER_FLOW;
	}
}

template <class T>
// 操作结果：将元素e插入队尾，完成入队操作
Status CLinkQueue<T>::EnQueue(const T &e)
{
	CNode<T> *p;
	p = new CNode<T>(e);
	if (p)
	{
		m_pRear->m_pNext = p;
		m_pRear = p;
		return SUCCESS;
	}
	else
		return OVER_FLOW;
}

template <class T>
// 操作结果：复制构造函数，由链队q构造新链队
CLinkQueue<T>::CLinkQueue(const CLinkQueue<T> &q)
{
	m_pFront = m_pRear = new CNode<T>;
	for (CNode<T> *p = q.m_pFront->m_pNext; p != nullptr; p = p->m_pNext)
		EnQueue(p->m_data);
}

template <class T>
// 操作结果：重载赋值运算符，将链队q赋值给当前链队
CLinkQueue<T> &CLinkQueue<T>::operator =(const CLinkQueue<T> &q)
{
	if (&q != this)
	{
		Clear();
		for (CNode<T> *p = q.m_pFront->m_pNext; p != nullptr; p = p->m_pNext)
			EnQueue(p->m_data);
	}
	return *this;
}

#endif