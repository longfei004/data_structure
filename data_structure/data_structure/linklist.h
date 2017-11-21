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
	CNode<T> *m_head;        //头结点指针
	int m_nlenth;           // 链表长度

public:
	CLinkList();
	CLinkList(T v[], int n);
	virtual ~CLinkList();	 // 析构函数
	void Clear();            // 清空链表

	bool IsEmpty() const;    // 判断链表是否为空
	int GetLength() const;	 // 求单链表长度	
	void Traverse(void(*Visit)(const T &)) const;// 遍历单链表
	int LocateElem(const T &e) const;	         // 元素定位 
	Status GetElem(int position, T &e) const;	 // 求指定位置的元素	
	Status SetElem(int position, const T &e);	 // 设置指定位置的元素值
	Status DeleteElem(int position, T &e);		 // 删除元素		
	Status InsertElem(int position, const T &e);	 // 在指定位置插入元素
	Status InsertElem(const T &e);	             // 在表尾插入元素
	CLinkList(const CLinkList<T> &la);            // 复制构造函数
	CLinkList<T> &operator =(const CLinkList<T> &la); // 重载赋值运算
};

template <typename T>
CLinkList<T>::CLinkList()   //构造空链表
{
	m_head = new CNode<T>;       //构造头结点
	assert(m_head);         //构造头结点失败，终止运行
	m_nlenth = 0;
} 

template <typename T>
CLinkList<T>::CLinkList(T v[], int n) //根据数组v中的元素构造链表
{
	CNode<T> *m_p;
	m_p = m_head = new CNode<T>;      //构造头结点
	assert(m_head);              //构造头结点失败，终止运行
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
void CLinkList<T>::Clear()                 //清除链表中的所有节点
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
bool CLinkList<T>::IsEmpty() const       // 判断链表是否为空
{
	return m_head->m_next == nullptr;
}

template <class T>
// 操作结果：返回单链表的长度 
int CLinkList<T>::GetLength() const
{
	return m_nlenth;
}

template <class T>
// 操作结果：依次对单链表的每个元素调用函数(*visit)访问
void CLinkList<T>::Traverse(void(*Visit)(const T &)) const
{
	CNode<T> *p = m_head->m_next;
	while (p != NULL) 
	{
		(*Visit)(p->m_data);	// 对单链表中每个元素调用函数(*visit)访问 
		p = p->m_next;
	}
}

template <class T>
// 元素定位
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
// 操作结果：当单链表存在第i个元素时，用e返回其值，函数返回ENTRY_FOUND,
//	否则函数返回NOT_PRESENT
Status CLinkList<T>::GetElem(int i,T &e) const
{
	if (i < 1 || i > m_nlenth)
		return RANGE_ERROR;
	else 
	{
		CNode<T> *p = m_head->m_next;
		int count;
		for (count = 1; count < i; count++)
			p = p->m_next;	            // p指向第i个结点
		e = p->m_data;				// 用e返回第i个元素的值
		return ENTRY_FOUND;
	}
}

template <class T>
// 操作结果：将单链表的第i个位置的元素赋值为e,
//	i的取值范围为1≤i≤length,
//	i合法时函数返回SUCCESS,否则函数返回RANGE_ERROR
Status CLinkList<T>::SetElem(int i, const T &e)
{
	if (i < 1 || i > m_nlenth)
		return RANGE_ERROR;
	else 
	{
		CNode<T> *p = m_head->m_next;
		int count;
		for (count = 1; count < i; count++)
			p = p->m_next;	           // 取出指向第i个结点的指针	
		p->m_data = e;			   // 修改第i个元素的值为e 
		return SUCCESS;
	}
}

template <class T>
// 操作结果：删除单链表的第i个位置的元素, 并用e返回其值,
//	i的取值范围为1≤i≤length,
//	i合法时函数返回SUCCESS,否则函数返回RANGE_ERROR
Status CLinkList<T>::DeleteElem(int i, T &e)
{
	if (i < 1 || i > m_nlenth)
		return RANGE_ERROR;   // i范围错		 
	else 
	{
		CNode<T> *p = m_head, *q;
		int count;
		for (count = 1; count < i; count++)
			p = p->m_next;	      // p指向第i-1个结点	
		q = p->m_next;	      // q指向第i个结点
		p->m_next = q->m_next;	  // 删除结点
		e = q->m_data;		  // 用e返回被删结点元素值	
		m_nlenth--;			  // 删除成功后元素个数减1 
		delete q;			  // 释放被删结点
		return SUCCESS;
	}
}

template <class T>
// 操作结果：在单链表的第i个位置前插入元素e
//	i的取值范围为1≤i≤length+1
//	i合法时返回SUCCESS, 否则函数返回RANGE_ERROR
Status CLinkList<T>::InsertElem(int i, const T &e)
{
	if (i < 1 || i > m_nlenth + 1)
		return RANGE_ERROR;
	else 
	{
		CNode<T> *p = m_head, *q;
		int count;
		for (count = 1; count < i; count++)
			p = p->m_next;	                    // p指向第i-1个结点	
		q = new CNode<T>(e, p->m_next); // 生成新结点q
		assert(q);                          // 申请结点失败，终止程序运行 
		p->m_next = q;				        // 将q插入到链表中
		m_nlenth++;							// 插入成功后，单链表长度加1 
		return SUCCESS;
	}
}

template <class T>
// 操作结果：在单链表末尾插入元素e
Status CLinkList<T>::InsertElem(const T &e)
{
	CNode<T> *p, *q;

	for (p = m_head; p->m_next != nullptr; p = p->m_next);
	q = new CNode<T>(e, nullptr);       // 生成新结点q
	assert(q);                          // 申请结点失败，终止程序运行 
	p->m_next = q;				        // 将q插入到链表中
	m_nlenth++;							// 插入成功后，单链表长度加1 
	
	return SUCCESS;
}

template <class T>
// 操作结果：复制构造函数，由单链表la构造新单链表
CLinkList<T>::CLinkList(const CLinkList<T> &la)
{
	int laLength = la.GetLength();	// 取被复制单链表的长度
	T e;
	m_head = new CNode<T>;		// 构造头指针
	assert(m_head);                   // 构造头指针失败，终止程序运行 
	m_nlenth = 0;						// 初始化元素个数

	for (int i = 1; i <= laLength; i++) 
	{	
		// 复制数据元素
		la.GetElem(i, e);	       // 取出第i个元素的值放在e中 
		InsertElem(e);		       // 将e插入到当前单链表的表尾 
	}
}

template <class T>
// 操作结果：重载赋值运算符，将单链表la赋值给当前单链表
CLinkList<T> &CLinkList<T>::operator =(const CLinkList<T> &la)
{
	if (&la != this) 
	{
		int laLength = la.GetLength();// 取被赋值单链表的长度
		T e;
		Clear();							// 清空当前单链表
		for (int i = 1; i <= laLength; i++) 
		{
			la.GetElem(i, e);		    // 取出第i个元素的值放在e中
			InsertElem(e);		            // 将e插入到当前单链表的表尾
		}
	}
	return *this;
}

#endif