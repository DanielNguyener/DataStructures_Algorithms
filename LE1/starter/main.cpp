#include <iostream>
using namespace std;
#include "AbstractStack.h"
#include "StackArrayDouble.h"
#include "StackArrayLinear.h"

int main() {
    // Write your own tests here

    StackArrayDouble<int> intStack;

    intStack.push(10);
    std::cout << "size: " << intStack.size() << std::endl;


    return 0;
}