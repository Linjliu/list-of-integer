
#ifndef DSA_H
#define DSA_H

#include <iostream>
#include <stdexcept>
#include <string>
#include <utility>

template<typename T>
class DynamicGenericArrayADT
{
public:
    virtual void pushBack(const T& itemToPush) = 0;

    virtual ~DynamicGenericArrayADT() = default;
};

template<typename SomeDataType>
class RawDynamicArray : public DynamicGenericArrayADT<SomeDataType>
{
private:
    int max_capacity;

    SomeDataType* ramPtrToDynamicList;
   
    int current_size;

    // Resize the dynamic array
    void resize()
    {
        int newCapacity = (max_capacity == 0) ? 5 : max_capacity * 2;

        SomeDataType* biggerList = new SomeDataType[newCapacity];

        try
        {
            for (int i = 0; i < current_size; i++)
            {
                biggerList[i] = ramPtrToDynamicList[i];
            }
        }

        catch (...)
        {
            delete[] biggerList;
            throw;
        }

        delete[] ramPtrToDynamicList;

        ramPtrToDynamicList = biggerList;
        max_capacity = newCapacity;
    }

public:
    // Default constructor
    RawDynamicArray(): max_capacity(5), ramPtrToDynamicList(new SomeDataType[5]), current_size(0)
    {
    
    }

    // Add an element
    void pushBack(const SomeDataType& itemToPush) override
    {
        if (current_size == max_capacity)
        {
            resize();
        }

        ramPtrToDynamicList[current_size] = itemToPush;
        ++current_size;
    }

    // Overload [] operator
    SomeDataType& operator[](int index)
    {
        if (index < 0 || index >= current_size)
        {
            throw std::out_of_range("Index is out of bounds");
        }

        return ramPtrToDynamicList[index];
    }

    // Get current size
    int size() const
    {
        return current_size;
    }

    // Get current capacity
    int capacity() const
    {
        return max_capacity;
    }

    // Swap two elements
    void swap(int leftIndex, int rightIndex)
    {
        SomeDataType copyOfLeftElement = ramPtrToDynamicList[leftIndex];

        ramPtrToDynamicList[leftIndex] = ramPtrToDynamicList[rightIndex];

        ramPtrToDynamicList[rightIndex] = copyOfLeftElement;
    }

    // Selection sort
    void sort()
    {
        for (int i = 0; i < current_size - 1; i++)
        {
            int smallestIndex = i;

            for (int j = i + 1; j < current_size; j++)
            {
                if (ramPtrToDynamicList[j] < ramPtrToDynamicList[smallestIndex])
                {
                    smallestIndex = j;
                }
            }

            swap(i, smallestIndex);
        }
    }

    // Sequential search
    int sequentialSearch(const SomeDataType& target) const
    {
        for (int i = 0; i < current_size; i++)
        {
            if (ramPtrToDynamicList[i] == target)
            {
                return i;
            }
        }

        return -1;
    }

    // Print elements
    void print(const std::string& separator = " ") const
    {
        for (int i = 0; i < current_size; i++)
        {
            std::cout << ramPtrToDynamicList[i] << separator;
        }

        std::cout << "\n";
    }

    // Destructor
    ~RawDynamicArray() override
    {
        delete[] ramPtrToDynamicList;
    }

    // Disable copy constructor
    RawDynamicArray(const RawDynamicArray&) = delete;

    // Disable copy assignment
    RawDynamicArray& operator=(const RawDynamicArray&) = delete;

    // Move constructor
    RawDynamicArray(RawDynamicArray&& other) noexcept
        : max_capacity(other.max_capacity), ramPtrToDynamicList(other.ramPtrToDynamicList),
        current_size(other.current_size)
    {
        other.max_capacity = 0;
        
        other.ramPtrToDynamicList = nullptr;
        
        other.current_size = 0;
    }

    // Move assignment operator
    RawDynamicArray& operator=(RawDynamicArray&& other) noexcept
    {
        if (this != &other)
        {
            delete[] ramPtrToDynamicList;

            max_capacity = other.max_capacity;
           
            ramPtrToDynamicList = other.ramPtrToDynamicList;
            
            current_size = other.current_size;

            other.max_capacity = 0;
            
            other.ramPtrToDynamicList = nullptr;
            
            other.current_size = 0;
        }

        return *this;
    }
};

#endif