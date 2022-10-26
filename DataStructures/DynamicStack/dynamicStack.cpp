#include <iostream>
#include <vector>
#include <string>

template <typename T>
class Stack
{
private:
    T* m_data{};
    size_t m_capacity{};
    size_t m_size{};

    void resize(int capacity)
    {
        T* temp = new T[capacity];
        for (int i = 0; i < m_size; ++i)
        {
            temp[i] = m_data[i];
        }
        delete[] m_data;
        m_data = temp;
        m_capacity = capacity;
    }

    void copy(const Stack& copy)
    {
        m_capacity = copy.m_capacity;
        m_size = copy.m_size;
        m_data = new T[m_capacity];
        for (size_t i = 0; i < m_size; i++)
        {
            m_data[i] = copy.m_data[i];
        }
    }

    class Iterator
    {
    private:
        Stack* m_stack{};
        int m_top;
    public:
        Iterator()
            :m_stack{ nullptr }, m_top{ -1 }
        {
        }
        Iterator(Stack* stack)
            :m_stack{ stack }, m_top{ stack->m_capacity - 1 }
        {
        }
        void operator++()
        {
            --m_top;
        }
        bool operator!=(const Iterator& other)
        {
            return m_top != other.m_top;
        }
        T& operator*()
        {
            return m_stack->m_data[m_top];
        }
    };

public:
    Stack()
    {
        m_capacity = 1;
        m_data = new T[m_capacity];
        m_size = 0;
    }
    Stack(const Stack& other)
    {
        copy(other);

    }
    ~Stack()
    {
        delete[] m_data;
    }

    Stack& operator=(const Stack& other)
    {
        if (this!=&other)
        {
            delete[] m_data;
            copy(other);
        }
        return *this;
    }

    void push(const T& item)
    {
        if (m_size == m_capacity)
        {
            resize(m_capacity * 2);
        }
        m_data[m_size] = item;
        m_size++;
    }

    T pop()
    {
        if (isEmpty())
        {
            throw std::out_of_range("There are no elements in the stack");
        }
        T item = m_data[--m_size];
        return item;
    }
    T peek()
    {
        if (isEmpty())
        {
            throw std::out_of_range("There are no elements in the stack");
        }
        int tempSize = m_size;
        return m_data[--tempSize];
    }
    int getSize()
    {
        return m_size;
    }
    bool isEmpty()
    {
        return m_size == 0;
    }
    Iterator begin()
    {
        return Iterator(this);
    }
    Iterator end()
    {
        return Iterator();
    }
};

int main()
{

}


