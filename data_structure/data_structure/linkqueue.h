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
	CNode<T> *m_pFront, *m_pRear;        //ͷ����β���ָ��

public:
	CLinkQueue();
	virtual ~CLinkQueue();	             // ��������
	void Clear();                        // �������

	bool IsEmpty() const;                // �ж������Ƿ�Ϊ��
	int GetLength() const;	             // �����ӳ���	
	void Traverse(void(*Visit)(const T &)) const;             // ��������
	Status GetHead(T &e) const;	                              // ȡ��ͷԪ��	
	Status DelQueue(T &e);		                              // ����		
	Status EnQueue(const T &e);	                              // ���
	CLinkQueue(const CLinkQueue<T> &q);                      // ���ƹ��캯��
	CLinkQueue<T> &operator =(const CLinkQueue<T> &q);       // ���ظ�ֵ����
};

template <typename T>
CLinkQueue<T>::CLinkQueue()                                  //���������
{
	m_pRear = m_pFront = new CNode<T>;                       //��������ͷ���
	assert(m_pFront);                                        //����ʧ�ܣ���ֹ����
	assert(m_pRear);
}

template <typename T>
CLinkQueue<T>::~CLinkQueue()
{
	Clear();
	delete m_pFront;
}

template <typename T>
//��������е����нڵ�
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
// �ж������Ƿ�Ϊ��
bool CLinkQueue<T>::IsEmpty() const       
{
	return m_pFront == m_pRear;
}

template <class T>
// ����������������ӵĳ��� 
int CLinkQueue<T>::GetLength() const
{
	int count = 0;		                                                // ��ʼ�������� 
	for (CNode<T> *p = m_pFront->m_pNext; p !=nullptr; p = p->m_pNext)
		count++;		                                                // ͳ���������еĽ���� 
	return count;
}

template <class T>
// ������������ζ����ӵ�ÿ��Ԫ�ص��ú���(*visit)����
void CLinkQueue<T>::Traverse(void(*Visit)(const T &)) const
{
	for (CNode<T> *p = m_pFront->m_pNext; p != nullptr; p = p->m_pNext)
		(*Visit)(p->m_data);
}

template <class T>
// ���������������ͷ���ֵ��e����
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
// ���������������ͷ���ֵ��e���أ���ɾ����ͷ
Status CLinkQueue<T>::DelQueue(T &e)
{
	if (!IsEmpty())
	{
		CNode<T> *p = m_pFront->m_pNext;
		e = p->m_data;
		m_pFront->m_pNext = p->m_pNext;
		if (m_pRear == p)    //����ǰ������ֻ��һ��Ԫ��
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
// �����������Ԫ��e�����β�������Ӳ���
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
// ������������ƹ��캯����������q����������
CLinkQueue<T>::CLinkQueue(const CLinkQueue<T> &q)
{
	m_pFront = m_pRear = new CNode<T>;
	for (CNode<T> *p = q.m_pFront->m_pNext; p != nullptr; p = p->m_pNext)
		EnQueue(p->m_data);
}

template <class T>
// ������������ظ�ֵ�������������q��ֵ����ǰ����
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