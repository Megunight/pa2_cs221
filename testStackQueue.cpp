/**
 * @file        testStackQueue.cpp
 * @description Basic test cases for CPSC 221 2023S PA2 - Stack and Queue
 *              Add your own code to this!
 *
 */

#define CATCH_CONFIG_MAIN
#include <iostream>
#include "cs221util/catch.hpp"

#include "stack.h"
#include "queue.h"

using namespace std;

TEST_CASE("Stack::basic functions", "[weight=1][part=stack]") {
    //cout << "Testing Stack..." << endl;
    Stack<int> intStack;
    vector<int> result;
    vector<int> expected;
    for (int i = 10; i > 0; i--) {
        expected.push_back(i);
    }
    for (int i = 1; i <= 10; i++) {
        intStack.Push(i);
    }
    //cout << intStack.peek() << endl;
    while (!intStack.IsEmpty()) {
        result.push_back(intStack.Pop());
        //cout << intStack.pop() << " ";
    }
    REQUIRE(result == expected);
}
TEST_CASE("Queue::basic functions", "[weight=1][part=queue]") {
    //cout << "Testing Queue..." << endl;
    Queue<int> intQueue;
    vector<int> result;
    vector<int> expected;
    for (int i = 1; i <= 10; i++) {
        expected.push_back(i);
    }
    for (int i = 1; i <= 10; i++) {
        intQueue.Enqueue(i);
    }
    //cout << intStack.peek() << endl;
    while (!intQueue.IsEmpty()) {
        result.push_back(intQueue.Dequeue());
        //cout << intStack.pop() << " ";
    }
    REQUIRE(result == expected);
}
TEST_CASE("Queue::misc push pop", "[weight=1][part=queue]") {
    //cout << "Testing Queue..." << endl;
    Queue<int> intQueue;
    vector<int> result;
    vector<int> expected;
    intQueue.Enqueue(5);
    intQueue.Enqueue(10);
    intQueue.Dequeue();
    intQueue.Enqueue(15);
    expected.push_back(10);
    expected.push_back(15);
    //cout << intStack.peek() << endl;
    while (!intQueue.IsEmpty()) {
        result.push_back(intQueue.Dequeue());
        //cout << intStack.pop() << " ";
    }
    REQUIRE(result == expected);
}
TEST_CASE("Stack::test resize up", "[weight=1][part=stack]") {
    //cout << "Testing Stack..." << endl;
    Stack<int> intStack;

    for (int i = 1; i <= 10; i++) {
        intStack.Push(i);
    }

    int cap = intStack.Capacity();
    int num_items = intStack.Size();
    REQUIRE(num_items == 10);
    REQUIRE(cap == 16);
}
TEST_CASE("Stack::test resize down", "[weight=1][part=stack]") {
    //cout << "Testing Stack..." << endl;
    Stack<int> intStack;

    // Add 10 items to stack
    for (int i = 1; i <= 10; i++) {
        intStack.Push(i);
        REQUIRE(intStack.Size() == i);
    }

    // Checking initial number of item and capacity
    int cap = intStack.Capacity();
    int num_items = intStack.Size();
    REQUIRE(num_items == 10);
    REQUIRE(cap == 16);

    // remove 7 items from stack
    for (int i = 0; i < 7; i++) {
        intStack.Pop();
    }

    //
    cap = intStack.Capacity();
    num_items = intStack.Size();
    REQUIRE(num_items == 3);
    REQUIRE(cap == 8);

    for (int i = 0; i < 3; i++) {
        intStack.Pop();
    }

    cap = intStack.Capacity();
    num_items = intStack.Size();
    REQUIRE(num_items == 0);
    REQUIRE(cap == 4);
}