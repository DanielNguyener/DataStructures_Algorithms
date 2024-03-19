#define TEST_MODE
#include <iostream>
#include <cassert>
#include <vector>
#include <cstdlib> 
#include <ctime>   
#include <string>
#include "ques.cpp" 

using namespace std;

int testEmptyListPalindromic() {
    DoublyLinkedList<int> list;
    if (list.isPalindromic() != true) {
        return 0;
    }
    return 1;
}

int testSingleElementPalindromic() {
    srand(time(NULL)); 
    DoublyLinkedList<int> list;
    list.append(rand() % 100 + 1); 

    if (list.isPalindromic() != true) {
        return 0;
    }
    return 1;
}

int testEvenElementsPalindromic() {
    srand(time(NULL)); 
    DoublyLinkedList<int> list;
    int n = rand() % 50 + 12; 

    vector<int> v(n);
    for (int i = 0; i < n; ++i) {
        v[i] = rand() % 100 + 29;
        list.append(v[i]);
    }
    for (int i = n - 1; i >= 0; --i) {
        list.append(v[i]); 
    }
    if (list.isPalindromic() != true) {
        return 0;
    }

    DoublyLinkedList<string> list2;
    list2.append("8");
    list2.append("6");
    list2.append("6");
    list2.append("8");

    if (list2.isPalindromic() != true) {
        return 0;
    }
    return 10;
}

int testOddElementsPalindromic() {
    srand(time(NULL) + 1); // Slightly adjust seed
    DoublyLinkedList<int> list;
    int n = rand() % 50 + 1; 

    vector<int> v(n);
    for (int i = 0; i < n; ++i) {
        v[i] = rand() % 100 + 29;
        list.append(v[i]);
    }
    list.append(n);
    for (int i = n - 1; i >= 0; --i) {
        list.append(v[i]); 
    }

    if (list.isPalindromic() != true) {
        return 0;
    }

    DoublyLinkedList<string> list2;
    list2.append("4");
    list2.append("3");
    list2.append("4");

    if (list2.isPalindromic() != true) {
        return 0;
    }
    return 5;
}

int testNonPalindromic() {
    srand(time(NULL) + 2); 
    DoublyLinkedList<int> list;
    int n = rand() % 50 + 30; 
    for (int i = 0; i < n; ++i) {
        int value = rand() % 200 + 28;
        list.append(value);
    }

    if (list.isPalindromic() != false) {
        return 0;
    }

    DoublyLinkedList<string> list2;
    list2.append("4");
    list2.append("3");
    list2.append("7");

    if (list2.isPalindromic() != false) {
        return 0;
    }
    return 10;
}

int main() {
    int score = 0;
    score += testEmptyListPalindromic();
    score += testSingleElementPalindromic();
    score += testNonPalindromic();
    score += testEvenElementsPalindromic();
    score += testOddElementsPalindromic();

    cout << "Your score is: " << score << " / 27" << endl;

}
