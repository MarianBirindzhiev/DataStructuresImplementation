#include <iostream>
#include <vector>
#include <string>

template <typename T>
class LinkedList
{
public:

    LinkedList()
    {
        nullAllVariables();
    }

    LinkedList(const LinkedList& other)
    {
        nullAllVariables();
        clone();
    }

    ~LinkedList()
    {
        nullAllVariables();
        clear();
    }

    LinkedList& operator=(const LinkedList& other)
    {
        if (this!=&other)
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

    size_t size()
    {
        return m_size;
    }

    bool empty() 
    {
        return m_size == 0;
    }

    bool contains()
    {
        return contains(m_pFirst);
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
    void reverse()
    {
        reverse(m_pFirst);
    }


private:

    template<typename nodeType>
    struct Node
    {
        nodeType data;
        Node<nodeType>* pNext;

        Node(const nodeType& value, Node<nodeType>* next = nullptr)
            :data(value), pNext(next) {}
    };

    Node<T>* m_pFirst;
    size_t m_size;

    void display(Node<T>* node)
    {
        if (node)
        {
            std::cout << node->data << ' ';
            display(node->pNext);
        }
    }

    bool checkIfIndexIsValid(size_t index)
    {
        return (index >= 0 && index <= m_size);
    }

    bool contains(Node<T>* node,const T& key)
    {
        bool contains = false;

        while (node)
        {
            if (node->data == key)
            {
                contains= true;
            }
            node = node->pNext;
        }
        return contains;
    }

    void insertAt(size_t index, const T& value)
    {
        if (!checkIfIndexIsValid(index))
            throw std::out_of_range("The passed index is out of range");

        Node<T>* newNode = new Node{ value };

        if (index == 0)
        {
            newNode->pNext = m_pFirst;
            m_pFirst = newNode;
        }
        else
        {
            Node<T>* nodeBeforeInserted = returnNodeAtDesiredIndex(index-1);
            newNode->pNext = nodeBeforeInserted->pNext;
            nodeBeforeInserted->pNext = newNode;
        }

        ++m_size;
    }

    void deleteAt(size_t index)
    {
        if (!checkIfIndexIsValid(index))
            throw std::out_of_range("The passed index is out of range");

        if (index==0)
        {
            Node<T>*tempNode = m_pFirst;
            m_pFirst = m_pFirst->pNext;
            delete tempNode;
        }
        else
        {
            Node<T>* nodeBeforeDeleted = returnNodeAtDesiredIndex(index - 1);
            Node<T>* deletedNode = returnNodeAtDesiredIndex(index);

            nodeBeforeDeleted->pNext = deletedNode->pNext;
            delete deletedNode;
        }
        --m_size;
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

    bool isSorted()
    {
        int checkValue = INT_MIN;
        Node<T>* currentNode = m_pFirst;
        while (currentNode)
        {
            if (currentNode->data < checkValue)
                return false;

            checkValue = currentNode->data;
            currentNode = currentNode->pNext;
        }
        return true;

    }
    
    void deleteDublicates()
    {
        Node<T>* currentNode = m_pFirst;
        Node<T>* nodeAfterTheCurrent = m_pFirst->pNext;

        while (nodeAfterTheCurrent)
        {
            if (currentNode->data!=nodeAfterTheCurrent->data)
            {
                currentNode = nodeAfterTheCurrent;
                nodeAfterTheCurrent = nodeAfterTheCurrent->pNext;
            }
            else
            {
                currentNode->pNext = nodeAfterTheCurrent->pNext;
                delete nodeAfterTheCurrent;
                nodeAfterTheCurrent = currentNode->pNext;
            }
        }
    }
    void reverse(Node<T>* front)
    {
        Node<T>* firstHelper = nullptr;
        Node<T>* secondHelper = nullptr;

        while (front)
        {
            secondHelper = firstHelper;
            firstHelper = front;
            front = front->pNext;
            firstHelper->pNext = secondHelper;
        }
        m_pFirst = firstHelper;

    }

//-------------------------------------------------/HELPER FUNCTIONS FOR CONSTUCTORS AND OPERATOR=/----------------------------------------------------------
    
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
        }
    }

    static void clone(const LinkedList& other)
    {
        Node<T>* traverseOther = other.m_pFirst;
        while (traverseOther)
        {
            push_front(traverseOther->data);
            traverseOther = traverseOther->pNext;
        }
        reverse();
    }

};

int main()
{
    LinkedList<int> li;
    li.push_back(10);
    li.push_back(20);
    li.push_back(30);
    li.push_back(40);
    li.push_back(50);
    li.push_back(60);
    li.reverse();
    li.display();

}


