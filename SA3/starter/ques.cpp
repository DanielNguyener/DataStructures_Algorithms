#include <iostream>
#include <vector>
#include <queue>
#include <unordered_map>
#include "PriorityQueueHeap.h"

using namespace std;

#ifndef INTERSECTION_ARRAY
 
vector<int> intersectionOfTwoArrays(vector<int> nums, vector<int> otherNums) {
    vector<int> intersection;

    unordered_map<int, int> map; // make a map that contains number of occurances
    // for every number in nums, and otherNums

    //for nums
    for(int i = 0; i < nums.size(); i++){
        map[nums[i]]++;
    }

    //iterate through otherNums and check if the number is already in the map
    for(int i = 0; i < otherNums.size(); i++){

        //if the number is already in the map, add it to the intersection vector.
        if(map[otherNums[i]] > 0){
            intersection.push_back(otherNums[i]); //push the number, NOT count. to intersection

            map[otherNums[i]]--; //then we decrease the number of occurance of that number in the map
            // this will account for the case where there are multiple in Nums, AND otherNums
        }
    }

    return intersection;
}

#endif

#ifndef ROPE_GAME

int ropesGameCost(vector<int> ropes) {

    int sum = 0; //the total cost we'll be returning.

    //we need to sort, following O(nlogN) -> use heap/priority_queue
    //make a min heap. -> will be used to sort path distances.
    priority_queue<int, vector<int>, greater<int>> heap;

    //insert into heap
    for(int i = 0; i < ropes.size(); i++){
        heap.push(ropes[i]);
    }

    //now we iterate until theres only one rope.
    while(heap.size() > 1){

        int rope1 = heap.top(); // get the minimum rope
        // remove from heap
        heap.pop();

        //get the second min
        int rope2 = heap.top();
        //remove from heap
        heap.pop();

        //add the two ropes together
        int new_rope = rope1 + rope2;
        //also, add length to counting sum
        sum += new_rope;

        //insert the new rope into heap.
        heap.push(new_rope);
    }


    return sum;
}

#endif

#ifndef TEST_MODE

int main() {
    // Test cases for intersectionOfTwoArrays:
    cout << "TEST CASES FOR intersectionOfTwoArrays" << endl;
    {
        cout << "Test Case 1:" << endl;
        vector<int> nums = {9, 8, 8, 7};
        vector<int> otherNums = {8, 8, 8, 9};

        vector<int> result = intersectionOfTwoArrays(nums, otherNums);
        cout << "Returned intersection: ";
        for (int i = 0; i < result.size(); i++) {
            cout << result[i] << " ";
        }
        cout << endl;
        cout << "The above intersection should contain two 8's and one 9" << endl;
        cout << endl;
    }

    {
        cout << "Test Case 2:" << endl;
        vector<int> nums = {1, 8, 1, 8, 1, 7, 46, 1};
        vector<int> otherNums = {8, 1, 8, 1, 1, 203};

        vector<int> result = intersectionOfTwoArrays(nums, otherNums);
        cout << "Returned intersection: ";
        for (int i = 0; i < result.size(); i++) {
            cout << result[i] << " ";
        }
        cout << endl;
        cout << "The above intersection should contain two 8's and three 1's" << endl;
        cout << endl;
    }

    {
        cout << "Test Case 3:" << endl;
        vector<int> nums = {1, 8, 7, 5, 53};
        vector<int> otherNums = {102, 203, 201, 103, 106, 107};

        vector<int> result = intersectionOfTwoArrays(nums, otherNums);
        cout << "Returned intersection: ";
        for (int i = 0; i < result.size(); i++) {
            cout << result[i] << " ";
        }
        cout << endl;
        cout << "The above intersection should be empty (should not see any numbers)" << endl;
        cout << endl;
    }

    cout << "TEST CASES FOR ropesGameCost" << endl;

    {
        cout << "Test Case 1: " << endl;
        vector<int> ropes = {3, 8, 4, 6, 7};
        int actualCost = ropesGameCost(ropes);
        int expectedCost = 63;
        cout << "Returned Total Cost: " << actualCost << endl;
        cout << "Expected Total Cost: " << expectedCost << endl;
        cout << endl;
    }

     {
        cout << "Test Case 2: " << endl;
        vector<int> ropes = {3, 7, 9, 4};
        int actualCost = ropesGameCost(ropes);
        int expectedCost = 44;
        cout << "Returned Total Cost: " << actualCost << endl;
        cout << "Expected Total Cost: " << expectedCost << endl;
    }

    return 0;
}
#endif