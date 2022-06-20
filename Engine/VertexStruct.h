#pragma once
#include <vector>
#include "Vec3.h"

struct VertexStruct
{
	std::vector<Vec3> vertex;
	std::vector<unsigned int> lineIndex;
	std::vector<unsigned int> faceIndex;
	std::vector<Vec3> normalDir;
	std::vector<bool> cullBack;
};
//struct VertexLineStruct
//{
//	std::vector<Vec3> vertex;
//	std::vector<unsigned int> vertexIndex;
//};