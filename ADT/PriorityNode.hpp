# pragma once

template<class T>
struct PriorityNode
{
    public:
        T* data;
        PriorityNode* prev;
        PriorityNode* next;
        int priority;

        PriorityNode(T* pData, int pPriority)
        : data(pData), prev(NULL), next(NULL), priority(pPriority)
        {}
};