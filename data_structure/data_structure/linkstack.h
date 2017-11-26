#ifndef __LK_STACK_H__
#define __LK_STACK_H__

#include "node.h"				// �����
#include "Assistance.h"

// ��ջ��
template<class T>
class CLinkStack
{
protected:
	//  ��ջ�����ݳ�Ա:
	CNode<T> *m_pTop;							// ջ��ָ��

public:
	//  ��ջ�ĺ�����Ա:
	CLinkStack();									// �޲����Ĺ��캯��
	virtual ~CLinkStack();							// ��������
	int GetLength() const;							// ��ջ����			 
	bool IsEmpty() const;							// �ж�ջ�Ƿ�Ϊ��
	void Clear();									// ��ջ���
	void Traverse(void(*Visit)(const T &)) const;	// ����ջ
	Status Push(const T e);					// ��ջ
	Status Top(T &e) const;					// ����ջ��Ԫ��
	Status Pop(T &e);						// ��ջ
	CLinkStack(const CLinkStack<T> &s);		// ���ƹ��캯��
	CLinkStack<T> &operator =(const CLinkStack<T> &s); // ��ֵ�������
};


// ��ջ���ʵ�ֲ���
template<class T>
// �������������һ����ջ��
CLinkStack<T>::CLinkStack()
{
	m_pTop = nullptr;
}

template<class T>
// �������������ջ
CLinkStack<T>::~CLinkStack()
{
	Clear();
}

template <class T>
// �������������ջԪ�ظ���
int CLinkStack<T>::GetLength() const
{
	int count = 0;		// ������ 
	CNode<T> *p;
	for (p = m_pTop; p != nullptr; p = p->m_pNext)		// ��p������Ѱÿ��Ԫ��
		count++;		// ͳ����ջ�н����
	return count;
}

template<class T>
// �����������ջΪ�գ��򷵻�true�����򷵻�false
bool CLinkStack<T>::IsEmpty() const
{
	return m_pTop == nullptr;
}

template<class T>
// ������������ջ
void CLinkStack<T>::Clear()
{
	CNode<T> *p;
	while (m_pTop != nullptr) 
	{
		p = m_pTop;
		m_pTop = m_pTop->m_pNext;
		delete p;
	}
}

template <class T>
// �����������ջ����ջ�����ζ�ջ��ÿ��Ԫ�ص��ú���(*visit)���� 
void CLinkStack<T>::Traverse(void(*Visit)(const T &)) const
{
	CNode<T> *p;
	for (p = m_pTop; p != nullptr; p = p->m_pNext)	// ��p������Ѱ��ǰջ��ÿ��Ԫ��
		(*Visit)(p->m_data);		// ��p��ָ���Ԫ�ص��ú���(*visit)���� 
}

template<class T>
// �����������Ԫ��e׷�ӵ�ջ��,��ɹ��򷵼�SUCCESS,�����綯̬�ڴ��Ѻľ�
//	������OVER_FLOW
Status CLinkStack<T>::Push(const T e)
{
	CNode<T> *p = new CNode<T>(e, m_pTop);
	if (p == nullptr) 	// ϵͳ�ڴ�ľ�
		return OVER_FLOW;
	else 
	{	// �����ɹ�
		m_pTop = p;
		return SUCCESS;
	}
}

template<class T>
// �����������ջ�ǿ�,��e����ջ��Ԫ��,��������SUCCESS,����������UNDER_FLOW
Status CLinkStack<T>::Top(T &e) const
{
	if (IsEmpty())	// ջ��
		return UNDER_FLOW;
	else 
	{	// ջ�ǿ�,�����ɹ�
		e = m_pTop->m_data;				// ��e����ջ��Ԫ��
		return SUCCESS;
	}
}

template<class T>
// �����������ջ�ǿ�,ɾ��ջ��Ԫ��,����e����ջ��Ԫ��,��������SUCCESS,����
//	��������UNDER_FLOW
Status CLinkStack<T>::Pop(T &e)
{
	if (IsEmpty())	// ջ��
		return UNDER_FLOW;
	else 
	{	// �����ɹ�
		CNode<T> *p = m_pTop;	// ����ԭջ��
		e = m_pTop->m_data;				// ��e����ջ��Ԫ��
		m_pTop = m_pTop->m_pNext;			// �޸�ջ��
		delete p;					// ɾ��ԭջ����� 
		return SUCCESS;
	}
}

template<class T>
// �����������ջs������ջ--���ƹ��캯��
CLinkStack<T>::CLinkStack(const CLinkStack<T> &s)
{
	if (s.IsEmpty())	// sΪ��
		m_pTop = nullptr;									// ����һ��ջ
	else 
	{	                                    // s�ǿ�,����ջ
		m_pTop = new CNode<T>(s.m_pTop->m_data);	// ���ɵ�ǰջ��
		CNode<T> *q = m_pTop;			        // ���õ�ǰջ��ָ��
		for (CNode<T> *p = s.m_pTop->m_pNext; p != nullptr; p = p->m_pNext) 
		{
			q->m_pNext = new CNode<T>(p->m_data); // ��ջ��׷��Ԫ��	
			q = q->m_pNext;					       // �޸�ջ��ָ�� 
		}
	}
}


template<class T>
// �����������ջs��ֵ����ǰջ--��ֵ�������
CLinkStack<T> &CLinkStack<T>::operator = (const CLinkStack<T> &s)
{
	if (&s != this) 
	{
		Clear();			// ��յ�ǰջ
		if (!s.IsEmpty()) 
		{	                            // s�ǿ�,����ջ
			m_pTop = new CNode<T>(s.m_pTop->m_data);       // ���ɵ�ǰջ��
			CNode<T> *q = m_pTop;			            // ���õ�ǰջ��ָ��
			for (CNode<T> *p = s.m_pTop->m_pNext; p != nullptr; p = p->m_pNext)
			{
				q->m_pNext = new CNode<T>(p->m_data);      // ��ջ��׷��Ԫ��	
				q = q->m_pNext;			                    // �޸�ջ��ָ��
			}
		}
	}
	return *this;
}

#endif