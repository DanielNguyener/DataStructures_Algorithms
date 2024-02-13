#include <iostream>
#include "deque.h"
using namespace std;

void testDequeDeconstructor(){

        Deque<int> q;
        q.insertFirst(3);
        q.insertFirst(2);
        q.insertFirst(1);

        cout << "size before deconstruction: " << q.size() << endl;

        q.~Deque();

        if(q.size() != 0){
            cout << "destructor failed, size: " << q.size() << endl;
        }else{
            cout << "destructor passed" << endl;
        }
    }

int main() {
    // Test insertFirst
    {
        Deque<int> q;
        q.insertFirst(3);
        q.insertFirst(2);
        q.insertFirst(1);

        // Now the deque should be [1, 2, 3]
        
        if (q.size() != 3) {
            cout << "Test insertFirst failed: Incorrect size" << endl;
            
        } else if (q.first() != 1 || q.last() != 3) {
            cout << "Test insertFirst failed: Incorrect elements" << endl;
   
        } else {
            cout << "Test insertFirst passed" << endl;
        }
        
    }
    
    // // Test insertLast
    {
        Deque<int> q;
        q.insertLast(1);
        q.insertLast(2);
        q.insertLast(3);
        
        // Now the deque should be [1, 2, 3]
        
        if (q.size() != 3) {
            cout << "Test insertLast failed: Incorrect size" << endl;
        } else if (q.first() != 1 || q.last() != 3) {
            cout << "Test insertLast failed: Incorrect elements" << endl;
        } else {
            cout << "Test insertLast passed" << endl;
        }
        
    }

    //test copy constructor

    {
        Deque<int> q;
        q.insertFirst(3);
        q.insertFirst(2);
        q.insertFirst(1);

        Deque<int> copyConstructor(q);

        if (copyConstructor.size() != 3) {
            cout << "Test copyConstructor failed: Incorrect size: " << copyConstructor.size() << endl;
            
        } else if (copyConstructor.first() != 1 || copyConstructor.last() != 3) {
            cout << "Test copyConstructor failed: Incorrect elements" << endl;
   
        } else {
            cout << "Test copyConstructor passed" << endl;
        }

    }

    // test copy assignment

    {
        Deque<int> q;
        q.insertFirst(3);
        q.insertFirst(2);
        q.insertFirst(1);

        Deque<int> copyConstructor;

        copyConstructor = q;

        if (copyConstructor.size() != 3) {
            cout << "Test copyConstructor failed: Incorrect size: " << copyConstructor.size() << endl;
            
        } else if (copyConstructor.first() != 1 || copyConstructor.last() != 3) {
            cout << "Test copyConstructor failed: Incorrect elements" << endl;
   
        } else {
            cout << "Test copyConstructor passed" << endl;

        } 
    }

    // test remove
    {
        Deque<int> q;
        q.insertFirst(3);
        q.insertFirst(2);
        q.insertFirst(1);

        int score = 0;


        while(!q.isEmpty()){
            if(q.last() != q.removeLast()){
                cout << "data doesn't match" << endl;
            }else{
                score++;
            }
        }

        if(score == 3){
            cout << "removeLast works" << endl;
        }else{
            cout << "remove incorrect number elements" << endl;
        }
    }

    //test removefirst

    {
        Deque<int> q;
        q.insertFirst(3);
        q.insertFirst(2);
        q.insertFirst(1);

        int score = 0;


        while(!q.isEmpty()){
            if(q.first() != q.removeFirst()){
                cout << "data doesn't match" << endl;
            }else{
                score++;
            }
        }

        if(score == 3){
            cout << "removeFirst works" << endl;
        }else{
            cout << "remove incorrect number elements" << endl;
        }

    }

    testDequeDeconstructor();

    return 0;
}