#include <iostream>
using namespace std;
 
template <class T> class SmartPointer {
private:
    T* ptr;
public:
    explicit SmartPointer(T* p = NULL) { 
        ptr = p; 
    }

    T& operator*() { return *ptr; }

    T* operator->() { return ptr; }
 
};

#ifndef TEST
void memoryLeakCheck()
{
    SmartPointer<int> p1(new int(10000));

    *p1 = 2000;
    return;
}


int main()
{   
   memoryLeakCheck();
   return 0;
}
#endif