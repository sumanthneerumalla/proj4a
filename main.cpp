#include <iostream>
#include "MinMaxHeap.h"



void testExceptions(){
    MinMaxHeap<int> F(25);

    try {
        cout<< "Attempting to insert more items than are allowed: "<<endl;
        for (int i = 0; i < 26; ++i) {
            F.insert(5);
        }
    }
    catch (exception e) {
        cout << "Tested insertion exception successfully" << endl;

    }

};



void testPercolate(){
    MinMaxHeap<int> H(25) ;
    H.insert(5) ;
    H.insert(10) ;
//    H.insert(7) ;
//    H.insert(9) ;
//    H.insert(6) ;
//    H.insert(2) ;
//    H.insert(16) ;
//    H.insert(12) ;
//    H.insert(11) ;
    cout << "Initial MinMax Heap\n" ;
    H.dump() ;
};


int main() {

testPercolate();
//testExceptions();



}