#ifndef _NODE_H
#define _NODE_H

//½ÚµãÀà
template <typename T>
struct CNode
{
	T m_data;
	CNode<T> *m_pNext;

	CNode();
	CNode(T e, CNode<T> *link = nullptr);
};

template <typename T>
CNode<T>::CNode()
{
	m_pNext = nullptr;
}

template <typename T>
CNode<T>::CNode(T e, CNode<T> *link)
{
	m_data = e;
	m_pNext = link;
}

#endif
