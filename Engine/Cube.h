#pragma once
#include <vector>
#include "Vec3.h"
#include <memory>
#include <iostream>
#include "VertexStruct.h"
#include "TexVertex.h"

class Cube
{
public:
	Cube(const float& size, float texdim = 1.0f)
	{
		float s = size / 2;
		vertex =
		{
			Vec3(-s, s, -s), Vec3(s, s, -s), Vec3(s, s, s), Vec3(-s, s, s),
			Vec3(-s, -s, -s), Vec3(s, -s, -s), Vec3(s, -s, s), Vec3(-s, -s, s)
		};
		vertexStruct.vertex.emplace_back(Vec3 (-s, s,-s) );
		vertexStruct.vertex.emplace_back(Vec3 ( s, s,-s) );
		vertexStruct.vertex.emplace_back(Vec3 ( s, s, s) );
		vertexStruct.vertex.emplace_back(Vec3 (-s, s, s) );
		vertexStruct.vertex.emplace_back(Vec3 (-s,-s,-s) );
		vertexStruct.vertex.emplace_back(Vec3 ( s,-s,-s) );
		vertexStruct.vertex.emplace_back(Vec3 ( s,-s, s) );
		vertexStruct.vertex.emplace_back(Vec3 (-s,-s, s) );

		texCoord.emplace_back(0.0f, texdim);
		texCoord.emplace_back(texdim, texdim);
		texCoord.emplace_back(0.0f, 0.0f);
		texCoord.emplace_back(texdim, 0.0f);
		texCoord.emplace_back(texdim, texdim);
		texCoord.emplace_back(0.0f, texdim);
		texCoord.emplace_back(texdim, 0.0f);
		texCoord.emplace_back(0.0f, 0.0f);

		vertexStruct.lineIndex =
		{
			0,1,  1,2,  2,3,  3,0,
			4,5,  5,6,  6,7,  7,4,
			0,4,  1,5,  2,6,  3,7
		};
		vertexStruct.faceIndex =
		{
			0,3,2,  2,1,0,  6,7,4,  4,5,6,
			1,5,4,  4,0,1,  4,7,3,  3,0,4,
			3,7,6,  6,2,3,  1,2,6,  6,5,1,

		}; 
		vertexStruct.normalDir.resize(vertexStruct.faceIndex.size()/3);
		vertexStruct.cullBack.resize(vertexStruct.faceIndex.size()/3);
	}
	VertexStruct<Vec3> Get_VStruct_Buffer()const
	{
		return vertexStruct;
	}
	VertexStruct<TexVertex> Get_VTStruct_Buffer()const
	{
		std::vector<TexVertex> tverts;
		tverts.reserve(vertex.size());
		for (size_t i = 0; i < vertex.size(); i++)
		{
			tverts.emplace_back(vertexStruct.vertex[i], texCoord[i]);
		}
		return
		{
			std::move(tverts),
			vertexStruct.lineIndex,
			vertexStruct.faceIndex,
			vertexStruct.normalDir,
			vertexStruct.cullBack
		};
	}
	void SetNormal()
	{
		for (size_t i = 0;i < vertexStruct.faceIndex.size()/3;i++)
		{
			Vec3 vec3_0 = vertexStruct.vertex[vertexStruct.faceIndex[i*3]];
			Vec3 vec3_1 = vertexStruct.vertex[vertexStruct.faceIndex[i*3+1]];
			Vec3 vec3_2 = vertexStruct.vertex[vertexStruct.faceIndex[i * 3 + 2]];
			vertexStruct.normalDir[i] = ((vec3_1- vec3_0).Cross((vec3_2 - vec3_0))).GetNormalized();
		}
	}
	bool isCulBack(int index)const
	{
		//最好需要计算三角形的重心位置作为ViewDirection
		auto cosAB = vertexStruct.normalDir[index/3] * vertexStruct.vertex[vertexStruct.faceIndex[index]].GetNormalized();
		return cosAB <= 0.0f;
	}
public:
	static constexpr int vertexNum = 8;
private:
	
	std::vector<Vec3> vertex;		
	std::vector<Vec2> texCoord;
	VertexStruct<Vec3> vertexStruct;
};
