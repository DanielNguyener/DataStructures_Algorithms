#define TEST
#include "skiplist.h"
#include <chrono>
#include <algorithm>
using namespace std;

int main() {
    int score = 0;
    int maxLevel = 10;
    double probability = 0.5;
    SkipList skipList(maxLevel, probability);

    skipList.insertElement(3);
    skipList.insertElement(6);
    skipList.insertElement(9);
    skipList.insertElement(2);
    skipList.insertElement(8);
    skipList.insertElement(4);
    skipList.insertElement(5);

    int vec[] = {2, 3, 4, 5, 6, 8, 9};
    for (int i = 0; i < 7; i++) {
        int searchKey = vec[i];
        if (!skipList.searchElement(searchKey)) {
            cout << "Search failed" << endl;
        }
    }

    skipList.displayList();
    
    //test deletion
    int deleteOrder[] = {3, 6, 9, 2, 8, 4, 5};
    for (int i = 0; i < 7; i++) {
        int deleteKey = deleteOrder[i];
        skipList.deleteElement(deleteKey); //delete key at i
        if (skipList.searchElement(deleteKey)) {
            cout << "was not deleted" << endl;
        }
        for (int j = i + 1; j < 7; j++) {
            if (!skipList.searchElement(deleteOrder[j])) {
                cout << deleteOrder[j] << " was not found" << endl;
            }
        }
    }

    cout << "Delete passed in hardcoded skip list" << endl;

    skipList.displayList();

}