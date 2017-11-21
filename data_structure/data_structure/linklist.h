#ifndef _LINKLIST_H_INCLUDED
#define _LINKLIST_H_INCLUDED

#include <iostream>
#include "node.h"
#include <cassert>		
#include "Assistance.h"


template <typename T>
class CLinkList
{
protected:
	CNode<T> *m_head;        //ͷ���ָ��
	int m_nlenth;           // ������

public:
	CLinkList();
	CLinkList(T v[], int n);
	virtual ~CLinkList();	 // ��������
	void Clear();            // �������

	bool IsEmpty() const;    // �ж������Ƿ�Ϊ��
	int GetLength() const;	 // ��������	
	void Traverse(void(*Visit)(const T &)) const;// ����������
	int LocateElem(const T &e) const;	         // Ԫ�ض�λ 
	Status GetElem(int position, T &e) const;	 // ��ָ��λ�õ�Ԫ��	
	Status SetElem(int position, const T &e);	 // ����ָ��λ�õ�Ԫ��ֵ
	Status DeleteElem(int position, T &e);		 // ɾ��Ԫ��		
	Status InsertElem(int position, const T &e);	 // ��ָ��λ�ò���Ԫ��
	Status InsertElem(const T &e);	             // �ڱ�β����Ԫ��
	CLinkList(const CLinkList<T> &la);            // ���ƹ��캯��
	CLinkList<T> &operator =(const CLinkList<T> &la); // ���ظ�ֵ����
};

template <typename T>
CLinkList<T>::CLinkList()   //���������
{
	m_head = new CNode<T>;       //����ͷ���
	assert(m_head);         //����ͷ���ʧ�ܣ���ֹ����
	m_nlenth = 0;
} 

template <typename T>
CLinkList<T>::CLinkList(T v[], int n) //��������v�е�Ԫ�ع�������
{
	CNode<T> *m_p;
	m_p = m_head = new CNode<T>;      //����ͷ���
	assert(m_head);              //����ͷ���ʧ�ܣ���ֹ����
	for (int i = 0; i < n; i++)
	{
		m_p->m_next = new CNode<T>(v[i], nullptr);
		assert(m_p->m_next);
		m_p = m_p->m_next;
	}
	m_nlenth = n;
}

template <typename T>
CLinkList<T>::~CLinkList()
{
	Clear();
	delete m_head;
}

template <typename T>
void CLinkList<T>::Clear()                 //��������е����нڵ�
{
	CNode<T> *m_p = m_head->m_next;
	while (m_p != nullptr)                
	{
		m_head->m_next = m_p->m_next;
		delete m_p;
		m_p = m_head->m_next;
	}
	m_nlenth = 0;
}



template <typename T>
bool CLinkList<T>::IsEmpty() const       // �ж������Ƿ�Ϊ��
{
	return m_head->m_next == nullptr;
}

template <class T>
// ������������ص�����ĳ��� 
int CLinkList<T>::GetLength() const
{
	return m_nlenth;
}

template <class T>
// ������������ζԵ������ÿ��Ԫ�ص��ú���(*visit)����
void CLinkList<T>::Traverse(void(*Visit)(const T &)) const
{
	CNode<T> *p = m_head->m_next;
	while (p != NULL) 
	{
		(*Visit)(p->m_data);	// �Ե�������ÿ��Ԫ�ص��ú���(*visit)���� 
		p = p->m_next;
	}
}

template <class T>
// Ԫ�ض�λ
int CLinkList<T>::LocateElem(const T &e) const 
{
	CNode<T> *p = m_head->m_next;
	int count = 1;
	while (p != NULL && p->m_data != e) {
		count++;
		p = p->m_next;
	}
	return  (p != NULL) ? count : 0;
}

template <class T>
// �������������������ڵ�i��Ԫ��ʱ����e������ֵ����������ENTRY_FOUND,
//	����������NOT_PRESENT
Status CLinkList<T>::GetElem(int i,T &e) const
{
	if (i < 1 || i > m_nlenth)
		return RANGE_ERROR;
	else 
	{
		CNode<T> *p = m_head->m_next;
		int count;
		for (count = 1; count < i; count++)
			p = p->m_next;	            // pָ���i�����
		e = p->m_data;				// ��e���ص�i��Ԫ�ص�ֵ
		return ENTRY_FOUND;
	}
}

template <class T>
// �����������������ĵ�i��λ�õ�Ԫ�ظ�ֵΪe,
//	i��ȡֵ��ΧΪ1��i��length,
//	i�Ϸ�ʱ��������SUCCESS,����������RANGE_ERROR
Status CLinkList<T>::SetElem(int i, const T &e)
{
	if (i < 1 || i > m_nlenth)
		return RANGE_ERROR;
	else 
	{
		CNode<T> *p = m_head->m_next;
		int count;
		for (count = 1; count < i; count++)
			p = p->m_next;	           // ȡ��ָ���i������ָ��	
		p->m_data = e;			   // �޸ĵ�i��Ԫ�ص�ֵΪe 
		return SUCCESS;
	}
}

template <class T>
// ���������ɾ��������ĵ�i��λ�õ�Ԫ��, ����e������ֵ,
//	i��ȡֵ��ΧΪ1��i��length,
//	i�Ϸ�ʱ��������SUCCESS,����������RANGE_ERROR
Status CLinkList<T>::DeleteElem(int i, T &e)
{
	if (i < 1 || i > m_nlenth)
		return RANGE_ERROR;   // i��Χ��		 
	else 
	{
		CNode<T> *p = m_head, *q;
		int count;
		for (count = 1; count < i; count++)
			p = p->m_next;	      // pָ���i-1�����	
		q = p->m_next;	      // qָ���i�����
		p->m_next = q->m_next;	  // ɾ�����
		e = q->m_data;		  // ��e���ر�ɾ���Ԫ��ֵ	
		m_nlenth--;			  // ɾ���ɹ���Ԫ�ظ�����1 
		delete q;			  // �ͷű�ɾ���
		return SUCCESS;
	}
}

template <class T>
// ����������ڵ�����ĵ�i��λ��ǰ����Ԫ��e
//	i��ȡֵ��ΧΪ1��i��length+1
//	i�Ϸ�ʱ����SUCCESS, ����������RANGE_ERROR
Status CLinkList<T>::InsertElem(int i, const T &e)
{
	if (i < 1 || i > m_nlenth + 1)
		return RANGE_ERROR;
	else 
	{
		CNode<T> *p = m_head, *q;
		int count;
		for (count = 1; count < i; count++)
			p = p->m_next;	                    // pָ���i-1�����	
		q = new CNode<T>(e, p->m_next); // �����½��q
		assert(q);                          // ������ʧ�ܣ���ֹ�������� 
		p->m_next = q;				        // ��q���뵽������
		m_nlenth++;							// ����ɹ��󣬵������ȼ�1 
		return SUCCESS;
	}
}

template <class T>
// ����������ڵ�����ĩβ����Ԫ��e
Status CLinkList<T>::InsertElem(const T &e)
{
	CNode<T> *p, *q;

	for (p = m_head; p->m_next != nullptr; p = p->m_next);
	q = new CNode<T>(e, nullptr);       // �����½��q
	assert(q);                          // ������ʧ�ܣ���ֹ�������� 
	p->m_next = q;				        // ��q���뵽������
	m_nlenth++;							// ����ɹ��󣬵������ȼ�1 
	
	return SUCCESS;
}

template <class T>
// ������������ƹ��캯�����ɵ�����la�����µ�����
CLinkList<T>::CLinkList(const CLinkList<T> &la)
{
	int laLength = la.GetLength();	// ȡ�����Ƶ�����ĳ���
	T e;
	m_head = new CNode<T>;		// ����ͷָ��
	assert(m_head);                   // ����ͷָ��ʧ�ܣ���ֹ�������� 
	m_nlenth = 0;						// ��ʼ��Ԫ�ظ���

	for (int i = 1; i <= laLength; i++) 
	{	
		// ��������Ԫ��
		la.GetElem(i, e);	       // ȡ����i��Ԫ�ص�ֵ����e�� 
		InsertElem(e);		       // ��e���뵽��ǰ������ı�β 
	}
}

template <class T>
// ������������ظ�ֵ���������������la��ֵ����ǰ������
CLinkList<T> &CLinkList<T>::operator =(const CLinkList<T> &la)
{
	if (&la != this) 
	{
		int laLength = la.GetLength();// ȡ����ֵ������ĳ���
		T e;
		Clear();							// ��յ�ǰ������
		for (int i = 1; i <= laLength; i++) 
		{
			la.GetElem(i, e);		    // ȡ����i��Ԫ�ص�ֵ����e��
			InsertElem(e);		            // ��e���뵽��ǰ������ı�β
		}
	}
	return *this;
}

#endif