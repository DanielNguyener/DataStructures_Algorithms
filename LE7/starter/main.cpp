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
}