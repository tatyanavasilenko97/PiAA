#pragma once
#include <vector>
#include <string>
#include <iostream>

void PrefixFunction(std::string& Common, std::vector<unsigned long long int>& Pi, unsigned long long int start, unsigned long long int end);//префикс-функция
unsigned long long int AlgorithmKMP(std::string& A, std::string& B);//алгоритм Кнута-Морриса-Пратта