#include <iostream>
#include "deque.h"
using namespace std;

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
    
    // Test insertLast
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

    return 0;
}