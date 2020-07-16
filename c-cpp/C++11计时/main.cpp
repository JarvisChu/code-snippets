#include <iostream>
#include <chrono>
#include <thread>

using namespace std;

// https://juejin.im/post/5eab934d6fb9a0438d405eda
// g++ main.cpp --std=c++11 && ./a.out
int main()
{
    auto start = chrono::steady_clock::now();
    
    // your codes
    this_thread::sleep_for(chrono::seconds(2));

    auto end = chrono::steady_clock::now();
    auto dur = chrono::duration_cast<chrono::milliseconds>(end - start).count();

    cout<< dur <<endl;
}