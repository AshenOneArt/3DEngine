#pragma once
#include <vector>
#include "Vec3.h"
#include <memory>
#include <iostream>
#include "VertexLineStruct.h"

class Cube
{
public:
	Cube(const float& size)		
	{
		float s = size / 2;
		vertex =
		{
			Vec3(-s, s, -s), Vec3(s, s, -s), Vec3(s, s, s), Vec3(-s, s, s),
			Vec3(-s, -s, -s), Vec3(s, -s, -s), Vec3(s, -s, s), Vec3(-s, -s, s)
		};
		vertexLine.vertex.emplace_back(Vec3 (-s, s,-s) );
		vertexLine.vertex.emplace_back(Vec3 ( s, s,-s) );
		vertexLine.vertex.emplace_back(Vec3 ( s, s, s) );
		vertexLine.vertex.emplace_back(Vec3 (-s, s, s) );
		vertexLine.vertex.emplace_back(Vec3 (-s,-s,-s) );
		vertexLine.vertex.emplace_back(Vec3 ( s,-s,-s) );
		vertexLine.vertex.emplace_back(Vec3 ( s,-s, s) );
		vertexLine.vertex.emplace_back(Vec3 (-s,-s, s) );

		vertexLine.vertexIndex =
		{
			0,1,  1,2,  2,3,  3,0,
			4,5,  5,6,  6,7,  7,4,
			0,4,  1,5,  2,6,  3,7
		};
	}
	VertexLineStruct Get_VL_Buffer()const
	{
		return vertexLine;
	}
private:
	std::vector<Vec3> vertex;		
	VertexLineStruct vertexLine;
};
