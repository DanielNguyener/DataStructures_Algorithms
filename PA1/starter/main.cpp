#include <iostream>
using namespace std;
#include "AbstractStack.h"
#include "StackArrayDouble.h"
#include "StackArrayLinear.h"
#include "StackLinkedList.h"

int main() {
    // Write your own tests here
    enum STACK_TYPE {
    ARRAY_LINEAR,
    ARRAY_DOUBLE,
    LINKED_LIST
    };

    StackLinkedList<int> s;

    s.push(1);
    s.push(2);

    StackLinkedList<int> s2(s);

    cout << "s head: " << s.top() << " s2 head: " << s2.top() << endl;
    cout << "s head: " << s.pop() << " s2 head: " << s2.pop() << endl;
    cout << "s new head: " << s.top() << " s2 new head: " << s2.top() << endl;

    return 0;
}