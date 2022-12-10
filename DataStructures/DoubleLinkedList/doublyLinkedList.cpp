#include <iostream>
#include <vector>
#include <string>


template<typename T>
class DoubleLinkedList
{
public:

    DoubleLinkedList()
    {
        nullAllVariables();
    }

    DoubleLinkedList(const DoubleLinkedList& other)
    {
        nullAllVariables();
        clone();
    }

    ~DoubleLinkedList()
    {
        nullAllVariables();
        clear();
    }

    DoubleLinkedList& operator=(const DoubleLinkedList& other)
    {
        if (this != &other)
        {
            clear();
            clone();
        }
        return *this;
    }

    void display()
    {
        display(m_pFirst);
    }
    void push_back(const T& value)
    {
        insertAt(m_size, value);
    }

    void push_front(const T& value)
    {
        insertAt(0, value);
    }

    void insert(size_t index, const T& value)
    {
        insertAt(index, value);
    }
    void pop_front()
    {
        deleteAt(0);
    }

    void pop_back()
    {
        deleteAt(m_size - 1);
    }

    void remove(size_t index)
    {
        deleteAt(index);
    }

    size_t size()
    {
        return m_size;
    }

    bool empty()
    {
        return m_size == 0;
    }


private:

    template<typename G>
    struct Node
    {
        G data;
        Node<G>* pPrevious;
        Node<G>* pNext;

        Node(const G& data)
            :data(data), pPrevious(nullptr), pNext(nullptr) {}
    };

    Node<T>* m_pFirst;
    size_t m_size;

    void display(Node<T>* node)
    {
        Node<T>* currentNode=node;
        while (currentNode)
        {
            std::cout << currentNode->data << ' ';
            currentNode = currentNode->pNext;
        }
    }

    void insertAt(size_t index, const T& value)
    {
        if (!checkIfIndexIsValid(index))
            throw std::out_of_range("The passed index is out of range");

        Node<T>* nodeToInsert = new Node{ value };
        if (index==0)
        {
            nodeToInsert->pNext = m_pFirst;

            if (m_pFirst)
                m_pFirst->pPrevious = nodeToInsert;

            m_pFirst = nodeToInsert;
        }
        else
        {
            Node<T>* nodeBeforeInserted = returnNodeAtDesiredIndex(index - 1);
            Node<T>* nodeAfterInserted = nodeBeforeInserted->pNext;

            if (nodeAfterInserted)
            {
                nodeToInsert->pNext = nodeAfterInserted;
                nodeAfterInserted->pPrevious = nodeToInsert;
            }
            nodeToInsert->pPrevious = nodeBeforeInserted;
            nodeBeforeInserted->pNext = nodeToInsert;
        }

        ++m_size;
    }

    void deleteAt(size_t index)
    {
        if (!checkIfIndexIsValid(index))
            throw std::out_of_range("The passed index is out of range");

        if (index==0)
        {
            Node<T>* tempNode = m_pFirst->pNext;
            tempNode->pPrevious = nullptr;
            delete m_pFirst;
            m_pFirst = tempNode;
        }
        else
        {
            Node<T>* nodeBeforeDeleted = returnNodeAtDesiredIndex(index - 1);
            Node<T>* deletedNode = nodeBeforeDeleted->pNext;
            Node<T>* nodeAfterDeleted = deletedNode->pNext;

            nodeBeforeDeleted->pNext = nodeAfterDeleted;
           
            if (nodeAfterDeleted)
                nodeAfterDeleted->pPrevious = nodeBeforeDeleted;
            
            delete deletedNode;
        }
        --m_size;
    }

    bool checkIfIndexIsValid(size_t index)
    {
        return (index >= 0 && index <= m_size);
    }

    Node<T>* returnNodeAtDesiredIndex(size_t index)
    {
        if (!checkIfIndexIsValid(index))
            throw std::out_of_range("The passed index is out of range");

        Node<T>* desiredNode = m_pFirst;

        for (size_t i = 0; i < index; i++)
            desiredNode = desiredNode->pNext;

        return desiredNode;
    }


    void nullAllVariables()
    {
        m_pFirst = nullptr;
        m_size = 0;
    }

    void clear()
    {
        Node<T>* currentNode = m_pFirst;
        Node<T>* oldNode = m_pFirst;

        while (currentNode)
        {
            oldNode = currentNode;
            currentNode = currentNode->pNext;
            delete oldNode;
            --m_size;
        }
    }

    static void clone(const DoubleLinkedList& other)
    {
        Node<T>* traverseOther = other.m_pFirst;
        int index = 0;
        while (index<other.m_size)
        {
            insertAt(traverseOther->data,index++);
            traverseOther = traverseOther->pNext;
        }
    }
};


int main()
{
    DoubleLinkedList<int> da;
    da.push_back(10);
    da.push_back(20);
    da.push_back(30);
    da.push_back(40);
    da.display();
}


