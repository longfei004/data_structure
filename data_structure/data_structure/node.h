#ifndef _NODE_H
#define _NODE_H

//½ÚµãÀà
template <typename T>
struct CNode
{
	T m_data;
	CNode<T> *m_next;

	CNode();
	CNode(T e, CNode<T> *link = nullptr);
};

template <typename T>
CNode<T>::CNode()
{
	m_next = nullptr;
}

template <typename T>
CNode<T>::CNode(T e, CNode<T> *link)
{
	m_data = e;
	m_next = link;
}

#endif
