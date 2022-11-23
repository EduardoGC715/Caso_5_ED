# pragma once
# include "PriorityNode.hpp"

template<class T>
class PriorityQueue
{
    private:
        PriorityNode<T>* head;
        PriorityNode<T>* tail;
        int size;

        PriorityNode<T>* getNode(int pIndex) {
            if ( pIndex < size ) {
                PriorityNode<T>* current = head;
                while (pIndex > 0) {    // Link hops until pIndex runs out
                    current = current->next;
                    pIndex--;
                }
                return current;
            }
            return NULL;
        }
        
        int getPriorityIndex(int pPriority) {
            int index = size - 2;
            PriorityNode<T>* current = tail->prev;
            while (current != NULL) {
                if (pPriority >= current->priority) {
                    return index;
                }
                current = current->prev;
                index--;
            }
            return index;
        }

        void insertHead(T* pData, int pPriority) {
            PriorityNode<T>* newNode = new PriorityNode<T>(pData, pPriority);
            newNode->next = head;
            head->prev = newNode;
            head = newNode;
        }

        void insertTail(T* pData, int pPriority) {
            PriorityNode<T>* newNode = new PriorityNode<T>(pData, pPriority);
            newNode->prev = tail;
            tail->next = newNode;
            tail = newNode;
        }

        void insertNode(T* pData, int pPriority, int pIndex) {
            PriorityNode<T>* newNode = new PriorityNode<T>(pData, pPriority);
            PriorityNode<T>* prior = getNode(pIndex);
            PriorityNode<T>* after = prior->next;
            prior->next = newNode;
            if (prior == tail) {
                tail = newNode;
            } else {
                after->prev = newNode;
            }
            newNode->prev = prior;
            newNode->next = after;
        }

    public:
        PriorityQueue() {
            size = 0;
            head = NULL;
            tail = NULL;
        }

        ~PriorityQueue() {
            while (! isEmpty()) {
                dequeue();
            }
        }

        bool isEmpty() const {
            return size == 0;
        }

        const T* getFront() const {
            return head->data;
        }

        T* getFront() {
            return head->data;
        }

        void enqueue(T* pData, int pPriority) {
            if (head != NULL){
                if (pPriority < head->priority) {         // Head insert if (Highest Priority)
                    insertHead(pData, pPriority);
                } else if (pPriority >= tail->priority) { // Tail insert if (Lowest Priority)
                    insertTail(pData, pPriority);
                } else {                          // Inserts at [1, N-1] via priority position
                    int index = getPriorityIndex(pPriority);
                    insertNode(pData, pPriority, index);
                }
            } else {    // Tail Insert if (Empty)
                head = tail = new PriorityNode<T>(pData, pPriority);
            }
            size++;
        }

        T* dequeue() {
            T* result = NULL;
            PriorityNode<T>* search = head;
            head = search->next;
            if (head != NULL) {
                head->prev = NULL;   // Unlink newHead's *prev
            }
            result = search->data;
            delete search;
            size--;
            return result;
        }
};