#define TEST
#include "main.cpp"

void memoryLeakCheck()
{
    // Allocate memory to pointer p
    SmartPointer<int> p1(new int(10000));
    SmartPointer<double> p2(new double(5.2));

    *p1 = 2000;
    return;
}

int main(){
    memoryLeakCheck();
    return 0;
}