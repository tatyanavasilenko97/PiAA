#pragma once
#include <vector>
#include "Vertex.h"
#include <stddef.h>

void ProcessingData(char Vertex1, char Vertex2, double Weight, std::vector<Vertex*>& MyGraph);

bool GreedyAlgorithm(Vertex* StartVertex, Vertex* EndVertex, std::vector<char>& Way);