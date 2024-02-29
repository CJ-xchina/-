// MyFunc.cpp
#include <pthread.h>
#include <unordered_map>
#include <set>
#include <string>
#include <iostream>

#include <algorithm> 
using namespace std;
extern "C" {

// 全局数据结构，用于跟踪共享变量名称
std::unordered_map<void*, std::string> variableNames;
// 地址被哪些线程访问
std::unordered_map<void*, std::set<pthread_t>> variableAccess;

std::set<std::string> sharedVariables;



void reportSharedVariables() {


    // 报告所有发现的共享变量

    std::cout << "shared variables: [";
    bool first = true;
    for (const auto& varName : sharedVariables) {
        if (!first) {
            std::cout << ", ";
        }
        std::cout << varName;
        first = false;
    }
    std::cout << "]" << std::endl;
}

void recordAccess(void* variableAddress, const char* variableName) {
    pthread_t currentThread = pthread_self();
    variableAccess[variableAddress].insert(currentThread);
    variableNames[variableAddress] = std::string(variableName);

    // 如果此变量被多于一个线程访问，则标记为共享
    if (variableAccess[variableAddress].size() > 1) {
        sharedVariables.insert(variableName);
    }
}


} // extern "C"
