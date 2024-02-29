// MyFunc.cpp
#include <pthread.h>
#include <unordered_map>
#include <set>
#include <string>
#include <iostream>
using namespace std;
extern "C"
{

    std::unordered_map<void *, std::string> variableNames;

    // address of lock
    std::unordered_map<void *, std::set<pthread_mutex_t *>> locksets;

    std::set<std::string> raceVariables;

    // the lock of thread
    std::unordered_map<pthread_t, std::set<pthread_mutex_t *>> threadLocks;

    std::unordered_map<void *, pthread_t> visited;

    void reportRaceVariables()
    {
        std::cout << "race variables: [";
        bool firstVariable = true;
        for (auto p = raceVariables.begin(); p != raceVariables.end(); ++p)
        {
            if (*p == "")
                continue;
            if (!firstVariable)
            {
                std::cout << ", ";
            }
            std::cout << *p;
            firstVariable = false;
        }
        std::cout << "]" << std::endl;
    }

    void accessVariable(void *variableAddress, const char *variableName, bool isWrite)
    {
        pthread_t currentThread = pthread_self();
        variableNames[variableAddress] = std::string(variableName);
        if (!isWrite || raceVariables.count(std::string(variableName)) > 0)
        {
            return;
        }
        if (locksets.find(variableAddress) == locksets.end())
        {
            if (visited.find(variableAddress) == visited.end() || visited[variableAddress] == currentThread)
            {
                visited[variableAddress] = currentThread;
                locksets[variableAddress] = threadLocks[currentThread];
            }
            else
            {
                raceVariables.insert(variableNames[variableAddress]);
            }
        }
        else
        {
            // locks of current Thread
            std::set<pthread_mutex_t *> &locks = threadLocks[currentThread];

            // locks of current Address
            std::set<pthread_mutex_t *> &addressLocks = locksets[variableAddress];

            std::set<pthread_mutex_t *> intersection;

            for (const auto &element : locks)
            {
                if (addressLocks.count(element) > 0)
                {
                    intersection.insert(element);
                }
            }
            // 检查交集是否为空
            if (intersection.empty())
            {
                raceVariables.insert(variableNames[variableAddress]);
            }
            else
            {
                locksets[variableAddress] = intersection;
            }
        }
    }

    void lockVariable(pthread_mutex_t *lock)
    {
        pthread_t currentThread = pthread_self();
        threadLocks[currentThread].insert(lock);
    }

    void unlockVariable(pthread_mutex_t *lock)
    {
        pthread_t currentThread = pthread_self();
        threadLocks[currentThread].erase(lock);
    }

} // extern "C"
