//
// Created by Sumanth on 4/24/2017.
//

#ifndef PROJ4A_MINMAXHEAP_H
#define PROJ4A_MINMAXHEAP_H

#include <iostream>
#include <utility>      // std::pair, std::make_pair
#include <stdexcept>      // std::out_of_range


using namespace std;

template<class T>
class Heap {

public:

    // required functions by UML
    Heap();

    Heap(int someSize);

    Heap(const Heap<T> &origHeap);

    bool Contains(const T &needle) const;

    const T *Find(const T &needle) const;

    T &Remove();

    void Insert(T &insertable);

    void PercolateUp();

    void PercolateDown(const T Comparable);

    // student-made functions below
    ~Heap();


    // UML-required member variables
    std::pair<T, int> *m_array;


    // student-made member variables
    Heap<T> *otherHeap;
    int currentSize;
    int currentLocation;
    int maxSize;
    T myValue;

    bool (*fptr)(T first, T second);

};

template<class T>
Heap<T>::Heap() {

    //this constructor should never be called really
    otherHeap = NULL;
    currentSize = 0;
    maxSize = 1;
    fptr = NULL;
}

template<class T>
Heap<T>::Heap(int someSize) {
    m_array = new pair<T, int>[someSize];
    maxSize = someSize;
    currentSize = 0;
    currentLocation = 0;
}

template<class T>
Heap<T>::~Heap() {
//delete dynamically allocated memory
    delete m_array;

}

template<class T>
void Heap<T>::Insert(T &insertable) {

    if (maxSize == currentSize) {
        throw std::out_of_range("Heap has been filled");
    }

    pair<T, int> myPair = make_pair(insertable, otherHeap->currentSize);
    //the second value is because we are inserting int o the end of the other heap
    //it will be modified when percolate up is called

    cout << "Just inserted " << insertable << endl;
    cout << "other index is " << otherHeap->currentSize << endl;
    currentSize++;
    currentLocation++;
    m_array[currentLocation] = myPair;
    m_array[currentLocation].second = otherHeap->currentSize +1;
}

template<class T>
void Heap<T>::PercolateUp() {
    int hole = currentLocation;

    pair<T, int> latest = m_array[hole];

    //calling fptr will return true if it needs to swap
    for (; hole > 1 && fptr(latest.first, m_array[hole / 2].first); hole /= 2) {
// swap, from child to parent
        m_array[hole] = m_array[hole / 2];
        //if we swap, we go over to its twin, and set its second value to be updated
        otherHeap->m_array[hole].second = hole;
    }
    m_array[hole] = latest;
    otherHeap->m_array[latest.second].second = hole;
}


/**********************************************************************
global namespace functions, used for function pointers
***********************************************************************/


template<class T>
bool greaterThan(T first, T second) {
    return first > second;
};

template<class T>
bool lessThan(T first, T second) {
    return second > first;
};


template<typename T>
class MinMaxHeap {
public:

    MinMaxHeap(int capacity);

    MinMaxHeap(const MinMaxHeap<T> &other);

    ~MinMaxHeap();

    const MinMaxHeap<T> &operator=(const MinMaxHeap<T> &rhs);

    int size();

    void insert(const T &data);

    T deleteMin();

    T deleteMax();

    void dump();

    void locateMin(int pos, T &data, int &index);

    void locateMax(int pos, T &data, int &index);


    Heap<T> *myMinHeap;
    Heap<T> *myMaxHeap;

    int m_size;

};

template<typename T>
MinMaxHeap<T>::MinMaxHeap(int capacity) {
    m_size = capacity;
    myMinHeap = new Heap<T>(m_size);
    myMaxHeap = new Heap<T>(m_size);
    myMinHeap->fptr = &lessThan;
    myMaxHeap->fptr = &greaterThan;
    myMinHeap->otherHeap = myMaxHeap;
    myMaxHeap->otherHeap = myMinHeap;

}

template<typename T>
MinMaxHeap<T>::~MinMaxHeap() {
    delete myMaxHeap;
    delete myMinHeap;
}


template<typename T>
void MinMaxHeap<T>::insert(const T &data) {

    T temp = data;
    myMinHeap->Insert(temp);
    myMaxHeap->Insert(temp);

    myMinHeap->PercolateUp();
    myMaxHeap->PercolateUp();
}

template<typename T>
void MinMaxHeap<T>::dump() {
    cout << "... MinMaxHeap::dump() ..." << endl;

    cout << "------------Min Heap------------" << endl;
    cout << "size = " << myMinHeap->currentSize << ", capacity = " << myMinHeap->maxSize << endl << endl;

    for (int i = 1; i<= myMinHeap->currentSize; ++i) {
        cout << "Heap[" << i << "] = (" << myMinHeap->m_array[i].first << "," << myMinHeap->m_array[i].second << ")\n";
    }

    cout << "------------Max Heap------------" << endl;
    cout << "size = " << myMaxHeap->currentSize << ", capacity = " << myMaxHeap->maxSize << endl << endl;
    for (int i = 1; i <= myMaxHeap->currentSize ; ++i) {
        cout << "Heap[" << i << "] = (" << myMaxHeap->m_array[i].first << "," << myMaxHeap->m_array[i].second << ")\n";
    }

}


#endif //PROJ4A_MINMAXHEAP_H
