// MyFunc.cpp
#include "llvm/Support/raw_ostream.h"
#include <unordered_set>
#include <iostream>

using namespace std;

std::unordered_set<int> CoveredBlocks;

extern "C" __attribute__((visibility("default"))) void instrumentBasicBlocks(uint32_t BlockNumber) {
  CoveredBlocks.insert(BlockNumber);
}

extern "C" __attribute__((visibility("default"))) void printBasicBlockCoverage(uint32_t allNumber) {
  cout << "Basic Block Coverage: " << CoveredBlocks.size() << "/" << allNumber << "\n";
}
