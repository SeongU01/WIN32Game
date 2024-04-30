#pragma once

template<typename T>
class DoubleLinkedList
{
public:
   
    struct Node 
    {
        T data;
        Node* prev;
        Node* next;
        Node(T data, Node* prev = nullptr, Node* next = nullptr) : data(data), prev(prev), next(next) {}
    };

    class Iterator
    {
    private:
        Node* curNode;
        
    public:
        Iterator(Node* node) : curNode(node) {}
        Node* GetCurrentNode() const
        {
            if(curNode!=nullptr)
                return curNode;

            return nullptr;
        }
        Iterator& operator++()
        {
            curNode = curNode->next;
            return *this;
        }

        Iterator& operator--()
        {
            curNode = curNode->prev;
            return *this;
        }

        bool operator!=(const Iterator& other)const
        {
            return curNode != other.curNode;
        }

        bool operator==(const Iterator& other)const
        {
            return curNode == other.curNode;
        }
        T& operator*() const
        {
            return curNode->data;
        }
    };
private:
    Node* head;
    Node* tail;

public:
    DoubleLinkedList():head(nullptr),tail(nullptr){}
    ~DoubleLinkedList()
    {
        while (head != nullptr)
        {
            Node* next = head->next;
            delete head;
            head = next;
        }
    }

    Node* PushBack(T data)
    {
        Node* node = new Node(data);
        if (tail == nullptr)
        {
            head = tail = node;
        }
        else
        {
            tail->next = node;
            node->prev = tail;
            tail = node;
        }
        return node;
    }

    Node* Insert(Node* pPos, T data)
    {
        if (!pPos)
            return PushBack(data);
        Node* node = new Node(data, pPos, pPos->next);
        if (pPos->next)
            pPos->next->prev = node;
        pPos->next = node;
        if (tail == pPos) 
            tail = node;
        return node;
    }

    Node* Erase(Node* pPos)
    {
        if (!pPos) 
            return nullptr;
        if (pPos->prev)
            pPos->prev->next = pPos->next;
        if (pPos->next)
            pPos->next->prev = pPos->prev;
        if (pPos == head)
            head = pPos->next;
        if (pPos == tail)
            tail = pPos->prev;
        Node* nextNode = pPos->next;
        delete pPos;
        return nextNode;
    }

    Iterator Begin()
    {
        return Iterator(head);
    }

    Iterator End()
    {
        return Iterator(nullptr);
    }
};