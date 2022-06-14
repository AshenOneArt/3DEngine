#pragma once
#include <vector>
#include "Vec3.h"

struct VertexLineStruct
{
	std::vector<Vec3> vertex;
	std::vector<unsigned int> vertexIndex;
};