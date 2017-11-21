#ifndef __LK_STACK_H__
#define __LK_STACK_H__

#include "node.h"				// 结点类
#include "Assistance.h"

// 链栈类
template<class T>
class CLinkStack
{
protected:
	//  链栈的数据成员:
	CNode<T> *m_top;							// 栈顶指针

public:
	//  链栈的函数成员:
	CLinkStack();									// 无参数的构造函数
	virtual ~CLinkStack();							// 析构函数
	int GetLength() const;							// 求栈长度			 
	bool IsEmpty() const;							// 判断栈是否为空
	void Clear();									// 将栈清空
	void Traverse(void(*Visit)(const T &)) const;	// 遍历栈
	Status Push(const T e);					// 入栈
	Status Top(T &e) const;					// 返回栈顶元素
	Status Pop(T &e);						// 出栈
	CLinkStack(const CLinkStack<T> &s);		// 复制构造函数
	CLinkStack<T> &operator =(const CLinkStack<T> &s); // 赋值语句重载
};


// 链栈类的实现部分
template<class T>
// 操作结果：构造一个空栈表
CLinkStack<T>::CLinkStack()
{
	m_top = nullptr;
}

template<class T>
// 操作结果：销毁栈
CLinkStack<T>::~CLinkStack()
{
	Clear();
}

template <class T>
// 操作结果：返回栈元素个数
int CLinkStack<T>::GetLength() const
{
	int count = 0;		// 计数器 
	CNode<T> *p;
	for (p = m_top; p != nullptr; p = p->m_next)		// 用p依次搜寻每个元素
		count++;		// 统计链栈中结点数
	return count;
}

template<class T>
// 操作结果：如栈为空，则返回true，否则返回false
bool CLinkStack<T>::IsEmpty() const
{
	return m_top == nullptr;
}

template<class T>
// 操作结果：清空栈
void CLinkStack<T>::Clear()
{
	CNode<T> *p;
	while (m_top != nullptr) 
	{
		p = m_top;
		m_top = m_top->m_next;
		delete p;
	}
}

template <class T>
// 操作结果：从栈顶到栈底依次对栈的每个元素调用函数(*visit)访问 
void CLinkStack<T>::Traverse(void(*Visit)(const T &)) const
{
	CNode<T> *p;
	for (p = m_top; p != nullptr; p = p->m_next)	// 用p依次搜寻当前栈的每个元素
		(*Visit)(p->m_data);		// 对p所指向的元素调用函数(*visit)访问 
}

template<class T>
// 操作结果：将元素e追加到栈顶,如成功则返加SUCCESS,否则如动态内存已耗尽
//	将返回OVER_FLOW
Status CLinkStack<T>::Push(const T e)
{
	CNode<T> *p = new CNode<T>(e, m_top);
	if (p == nullptr) 	// 系统内存耗尽
		return OVER_FLOW;
	else 
	{	// 操作成功
		m_top = p;
		return SUCCESS;
	}
}

template<class T>
// 操作结果：如栈非空,用e返回栈顶元素,函数返回SUCCESS,否则函数返回UNDER_FLOW
Status CLinkStack<T>::Top(T &e) const
{
	if (IsEmpty())	// 栈空
		return UNDER_FLOW;
	else 
	{	// 栈非空,操作成功
		e = m_top->m_data;				// 用e返回栈顶元素
		return SUCCESS;
	}
}

template<class T>
// 操作结果：如栈非空,删除栈顶元素,并用e返回栈顶元素,函数返回SUCCESS,否则
//	函数返回UNDER_FLOW
Status CLinkStack<T>::Pop(T &e)
{
	if (IsEmpty())	// 栈空
		return UNDER_FLOW;
	else 
	{	// 操作成功
		CNode<T> *p = m_top;	// 保留原栈顶
		e = m_top->m_data;				// 用e返回栈顶元素
		m_top = m_top->m_next;			// 修改栈顶
		delete p;					// 删除原栈顶结点 
		return SUCCESS;
	}
}

template<class T>
// 操作结果：由栈s构造新栈--复制构造函数
CLinkStack<T>::CLinkStack(const CLinkStack<T> &s)
{
	if (s.IsEmpty())	// s为空
		m_top = nullptr;									// 构造一空栈
	else 
	{	                                    // s非空,复制栈
		m_top = new CNode<T>(s.m_top->m_data);	// 生成当前栈项
		CNode<T> *q = m_top;			        // 设置当前栈底指针
		for (CNode<T> *p = s.m_top->m_next; p != nullptr; p = p->m_next) 
		{
			q->m_next = new CNode<T>(p->m_data); // 向栈底追加元素	
			q = q->m_next;					       // 修改栈底指针 
		}
	}
}


template<class T>
// 操作结果：将栈s赋值给当前栈--赋值语句重载
CLinkStack<T> &CLinkStack<T>::operator = (const CLinkStack<T> &s)
{
	if (&s != this) 
	{
		Clear();			// 清空当前栈
		if (!s.IsEmpty()) 
		{	                            // s非空,复制栈
			m_top = new CNode<T>(s.m_top->m_data);       // 生成当前栈项
			CNode<T> *q = m_top;			            // 设置当前栈底指针
			for (CNode<T> *p = s.m_top->m_next; p != nullptr; p = p->m_next)
			{
				q->m_next = new CNode<T>(p->m_data);      // 向栈底追加元素	
				q = q->m_next;			                    // 修改栈底指针
			}
		}
	}
	return *this;
}

#endif