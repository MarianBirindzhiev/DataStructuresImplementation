#include <iostream>
#include <vector>
#include <string>

template <typename T>
class DynamicArray
{
    T* m_data;
    size_t m_size;
    size_t m_capacity;
    
    void deepCopy(const DynamicArray& other)
    {
        m_capacity = other.m_capacity;
        m_size = other.m_size;
        m_data = new T[m_capacity];

        for (size_t i = 0; i < m_size; i++)
        {
            m_data[i] = other.m_data[i];
        }
    }

    void clear()
    {
        delete[] m_data;
        m_data = nullptr;
        m_size = 0;
        m_capacity = 1;
    }

    size_t calculateGrowth(size_t desiredCapacity)
    {
        if (desiredCapacity<m_capacity)
        {
            return m_capacity;
        }
        return std::max(desiredCapacity, m_capacity * 2);
    }

    void resize(size_t desiredCapacity)
    {
        if (desiredCapacity == m_capacity)
        {
            return;
        }
        size_t elementsToCopy = std::min(desiredCapacity, m_size);
        T* tempData = new T[desiredCapacity];
        if (desiredCapacity != 0)
        {
            for (size_t i = 0; i < elementsToCopy; i++)
            {
                tempData[i] = m_data[i];
            }
        }
        m_data = tempData;
        m_capacity = desiredCapacity;
        m_size = elementsToCopy;
    }

public:
    DynamicArray()
      : m_data(new T[m_capacity]),
        m_size(0),
        m_capacity(1)
    {}

    DynamicArray(const DynamicArray& other)
    {
        deepCopy(other);
    }

    DynamicArray& operator=(const DynamicArray& other)
    {
        if (this!=&other)
        {
            clear();
            deepCopy(other);
        }
        return *this;
    }

    ~DynamicArray()
    {
        clear();
    }

    void push_back(const T& element)
    {
        if (full())
        {
            resize(calculateGrowth(m_size + 1));
        }
        m_data[m_size++] = element;
    }
    
    void pop_back()
    {
        if (empty())
        {
            throw std::out_of_range("the array is empty");
        }
        --m_size;
    }

    T& getAt(size_t index)
    {
        if (index > m_size)
        {
            throw std::out_of_range("index out of range");
        }
        return m_data[index];
    }
    void setAt(size_t index,const T& value)
    {
        if (index > m_size)
        {
            throw std::out_of_range("index out of range");
        }
        m_data[index] = value;
    }

    void reserve(size_t desiredCapacity)
    {
        resize(calculateGrowth(desiredCapacity));
    }

    bool empty() { return m_size == 0; }
    bool full() { return m_size == m_capacity; }
    size_t size() { return m_size; }

    T& operator[](size_t index)
    {
        if (index > m_size)
        {
            throw std::out_of_range("index out of range");
        }
        return m_data[index];
    }
    const T& operator[](size_t index) const
    {
        if (index > m_size)
        {
            throw std::out_of_range("index out of range");
        }
        return m_data[index];
    }

    DynamicArray& operator+=(const DynamicArray& other)
    {
        reserve(m_size + other.m_size);
        for (size_t i = 0; i < other.m_size; i++)
        {
            push_back(other.m_data[i]);
        }
        return *this;
    }
   const DynamicArray operator+(const DynamicArray& other) const
    {
       DynamicArray tempArray;
       tempArray.reserve(m_size + other.m_size);
       tempArray += *this;
       tempArray += other;
      
       return tempArray;

    }
   public:
        class Iterator
        {
        private:
            DynamicArray* m_array;
            size_t m_index;
        public:
            Iterator(DynamicArray* array)
              : m_array (array),
                m_index(0)
            {}

            T& getCurrent() const
            {
                return m_array->getAt(m_index);
            }

            void setCurrent(const T& value)
            {
                m_array->setAt(m_index, value);
            }

            void moveNext()
            {
                if (m_index<m_array->size())
                {
                    ++m_index;
                }
            }
            
            void rewind()
            {
                m_index = 0;
            }

            bool end() const
            {
                return m_index == m_array->size();
            }
        };

    Iterator getIterator()
    {
        return Iterator(this);
    }

};

int main()
{

}
