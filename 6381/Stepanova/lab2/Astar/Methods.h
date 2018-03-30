#pragma once
#include <vector>
#include <algorithm>
#include "Vertex.h"
#include <stddef.h>

void ProcessingData(char Vertex1, char Vertex2, double Weight, std::vector<Vertex*>& MyGraph);

void AstarAlgorithm(Vertex* StartVertex, Vertex* EndVertex, std::vector<char>& Way, std::vector<Vertex*>& Queue);