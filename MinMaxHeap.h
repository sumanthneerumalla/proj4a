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

    void Insert(T &insertable);

    void PercolateUp();

    void PercolateDown(int index);

    // student-made functions below
    ~Heap();


    // UML-required member variables
    std::pair<T, int> *m_array;
    std::pair<T, int> *latestModified;


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
    m_array = new pair<T, int>[someSize + 1]; // one extra because we dont use slot 0
    maxSize = someSize;
    currentSize = 0;
    currentLocation = 1;
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

    pair<T, int> myPair = make_pair(insertable, otherHeap->currentLocation);
    //the second value is because we are inserting int o the end of the other heap
    //it will be modified when percolate up is called

//    cout << "Just inserted " << insertable << endl;
//    cout << "other index is " << otherHeap->currentLocation << endl;


    m_array[currentLocation] = myPair;
    m_array[currentLocation].second = otherHeap->currentLocation;
    latestModified = &m_array[currentLocation];

}

template<class T>
void Heap<T>::PercolateUp() {
    int hole = currentSize;

    pair<T, int> latest = m_array[hole];

    //calling fptr will return true if it needs to swap
    for (; hole > 1 && fptr(latest.first, m_array[hole / 2].first); hole /= 2) {
// swap, from child to parent
        m_array[hole] = m_array[hole / 2];
        //if we swap, we go over to its twin, and set its second value to be updated
        otherHeap->m_array[hole].second = hole;

        latestModified = &m_array[hole];//used for debugging
        otherHeap->latestModified = &otherHeap->m_array[hole]; //used for debugging
    }
    m_array[hole] = latest;
    otherHeap->m_array[latest.second].second = hole;
    latestModified = &m_array[hole];//used for debugging
    otherHeap->latestModified = &otherHeap->m_array[hole];//used for debugging
}

template<class T>
Heap<T>::Heap(const Heap<T> &origHeap) {

    int someSize = origHeap.currentSize;
    m_array = new pair<T, int>[someSize + 1]; // one extra because we dont use slot 0
    maxSize = someSize;
    currentSize = origHeap.currentSize;
    currentLocation = origHeap.currentLocation;
    for (int i = 1; i < currentSize + 1; ++i) {
        m_array[i] = origHeap.m_array[i];
        m_array[i] = origHeap.m_array[i];
    }

    fptr = origHeap.fptr;
}

template<class T>
void Heap<T>::PercolateDown(int index) {
    while (2 * index + 1 < maxSize) {
        pair<T, int> selection = m_array[index];


        //check if there is a let child
        // if no left child, swap with right child

        int leftIndex = (index * 2) + 1;
        pair<T, int> left = m_array[leftIndex];


        //check if there is a right child
        //if no right child, swap with left child
        int rightIndex = (index * 2) + 2;
        pair<T, int> right = m_array[rightIndex];

        if (leftIndex > currentSize + 1) {
        }


        //if two children, figure out max
        //swap with the max
    }
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

    myMinHeap->currentLocation++;
    myMinHeap->currentSize++;
    myMaxHeap->currentLocation++;
    myMaxHeap->currentSize++;

    myMinHeap->PercolateUp();
    myMaxHeap->PercolateUp();
}

template<typename T>
void MinMaxHeap<T>::dump() {
    cout << "... MinMaxHeap::dump() ..." << endl;

    cout << "------------Min Heap------------" << endl;
    cout << "size = " << myMinHeap->currentSize << ", capacity = " << myMinHeap->maxSize << endl << endl;

    for (int i = 1; i <= myMinHeap->currentSize; ++i) {
        cout << "Heap[" << i << "] = (" << myMinHeap->m_array[i].first << "," << myMinHeap->m_array[i].second << ")\n";
    }

    cout << "------------Max Heap------------" << endl;
    cout << "size = " << myMaxHeap->currentSize << ", capacity = " << myMaxHeap->maxSize << endl << endl;
    for (int i = 1; i <= myMaxHeap->currentSize; ++i) {
        cout << "Heap[" << i << "] = (" << myMaxHeap->m_array[i].first << "," << myMaxHeap->m_array[i].second << ")\n";
    }

}

template<typename T>
MinMaxHeap<T>::MinMaxHeap(const MinMaxHeap<T> &other) {

    if (&other == NULL) {
        m_size = 0;
    } else {
        m_size = other.m_size;
    }

    //use Heap copy constructors to copy over heap content
    myMinHeap = new Heap<T>(*other.myMinHeap);
    myMaxHeap = new Heap<T>(*other.myMaxHeap);

    myMinHeap->fptr = &lessThan;
    myMaxHeap->fptr = &greaterThan;
    myMinHeap->otherHeap = myMaxHeap;
    myMaxHeap->otherHeap = myMinHeap;

}

template<class T>
const MinMaxHeap<T> &MinMaxHeap<T>::operator=(const MinMaxHeap<T> &rhs) {
    if (&rhs == this) {
        return *this;
    }

    delete this;

    MinMaxHeap* temp = new MinMaxHeap<T>(rhs);
    return *temp;


}

template<class T>
int MinMaxHeap<T>::size() {
    //this is all we need to return
    return m_size;
}

template<class T>
T MinMaxHeap<T>::deleteMin() {
    if (m_size == 0) {
        throw std::out_of_range("Heap is empty, cannot delete");
    }

    // get info from teh node that we just deleted
    myMinHeap->m_array[0].first = myMinHeap->m_array[1].first;
    int twinLocation = myMinHeap->m_array[1].second;


    //move the last pair over to the place of the first pair
    myMinHeap->m_array[1] = myMinHeap->m_array[myMinHeap->currentSize];

    myMinHeap->currentSize--;
    myMinHeap->currentLocation--;

    //use the twin location
    //move the last item in the max array to the location of the twin of the deleted node
    myMaxHeap->m_array[twinLocation + 1] = myMaxHeap->m_array[myMaxHeap->currentSize];

    myMaxHeap->currentSize--;
    myMaxHeap->currentLocation--;

    //now that the node has been deleted form each heap, we percolate down at that index
    //for both heaps, starting at that location
    myMaxHeap->PercolateDown(twinLocation + 1);
    myMinHeap->PercolateDown(1);


    //we dont return a temp variable because it would be destroyed after
    //the function runs
    return myMinHeap->m_array[0].first;
}

template<class T>
T MinMaxHeap<T>::deleteMax() {
    if (m_size == 0) {
        throw std::out_of_range("Heap is empty, cannot delete");
    }

    // get info from teh node that we just deleted
    myMaxHeap->m_array[0].first = myMaxHeap->m_array[1].first;
    int twinLocation = myMaxHeap->m_array[1].second;


    //move the last pair over to the place of the first pair
    myMaxHeap->m_array[1] = myMaxHeap->m_array[myMaxHeap->currentSize];

    myMaxHeap->currentSize--;
    myMaxHeap->currentLocation--;

    //use the twin location
    //move the last item in the max array to the location of the twin of the deleted node
    myMinHeap->m_array[twinLocation + 1] = myMinHeap->m_array[myMaxHeap->currentSize];

    myMinHeap->currentSize--;
    myMinHeap->currentLocation--;

    //now that the node has been deleted form each heap, we percolate down at that index
    //for both heaps, starting at that location
    myMinHeap->PercolateDown(twinLocation + 1);
    myMaxHeap->PercolateDown(1);

    //we dont return a temp variable because it would be destroyed after
    //the function runs
    return myMaxHeap->m_array[0].first;
}

template<class T>
void MinMaxHeap<T>::locateMin(int pos, T &data, int &index) {
    data = myMinHeap->m_array[1].first;
    index = myMinHeap->m_array->second;
}

template<class T>
void MinMaxHeap<T>::locateMax(int pos, T &data, int &index) {
    data = myMaxHeap->m_array[1].first;
    index = myMaxHeap->m_array->second;
}


#endif //PROJ4A_MINMAXHEAP_H
