#pragma once
typedef bool (*cmptor)(int, int);
void sortTester(void (*func)(int*, int, cmptor), int times, int maxVar, int maxLen);
double testSortingTime(void (*sortFunc)(int*, int), int numComparisons, int dataSize, int maxValue);