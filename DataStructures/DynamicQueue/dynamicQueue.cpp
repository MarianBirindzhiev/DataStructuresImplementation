#include <iostream>
#include <vector>
#include <string>

template <typename T>
class Queue
{
private:
    T* m_data;
    int m_capacity;
    int m_size;
    int m_frontElement;
    int m_lastElement;

    void resize(int capacity)
    {
        T* tempData = new T[capacity];
        for (int i = 0; i < m_size; i++)
        {
            tempData[i] = m_data[i];
        }
        delete[] m_data;
        m_data = tempData;
        m_capacity = capacity;
        
    }

    void deepCopy(const Queue& other)
    {
        m_capacity = other.m_capacity;
        m_size = other.m_size;
        m_data = new T[m_capacity];
        m_frontElement = other.m_frontElement;
        m_lastElement = other.m_lastElement;
        for (int i = 0; i < m_size; i++)
        {
            m_data[i] = other.m_data[i];
        }
    }

public:
    Queue()
    {
        m_capacity = 1;
        m_size = 0;
        m_data = new T[m_capacity];
        m_frontElement = 0;
        m_lastElement = -1;
    }
    Queue(int capacity)
    {
        m_data = new T[capacity];
    }
    Queue(const Queue& other)
    {
        deepCopy(other);
    }
    ~Queue()
    {
        delete[] m_data;
    }
    Queue& operator=(const Queue& other)
    {
        if (this!=&other)
        {
            delete[] m_data;
            deepCopy(other);
        }
        return *this;
    }

    void enqueue(int value)
    {
        if (isFull())
        {
            resize(m_capacity * 2);
        }
        m_lastElement = (m_lastElement + 1) % m_capacity;
        m_data[m_lastElement] = value;
        ++m_size;
    }

    T dequeue()
    {
        if (isEmpty())
        {
            throw std::out_of_range("The queue is empty");
        }
        int removedElement = m_data[m_frontElement];

        m_frontElement = (m_frontElement + 1) % m_capacity;
        --m_size;
        return removedElement;
    }

    T peek()
    {
        if (isEmpty())
        {
            throw std::out_of_range("The queue is empty");
        }   
        return m_data[m_frontElement];
    }

    bool isEmpty()
    {
        return m_size == 0;
    }
    int getSize()
    {
        return m_size;
    }
    bool isFull()
    {
        return m_size == m_capacity;
    }
};

int main()
{

}


