#pragma once
#include <vector>
#include "Vec3.h"
template <class T>
struct VertexStruct
{
	std::vector<T> vertex;
	std::vector<unsigned int> lineIndex;
	std::vector<unsigned int> faceIndex;
	std::vector<Vec3> normalDir;
	std::vector<bool> cullBack;
};
