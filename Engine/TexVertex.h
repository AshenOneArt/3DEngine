#pragma once
#include "Vec2.h"
#include "Vec3.h"

class TexVertex
{
public:
	TexVertex(const Vec3& pos,const Vec2& tc)
		:pos(pos), texCoord(tc)
	{}
	TexVertex InterpolateTo(const TexVertex& dest, float alpha)const
	{
		return 
		{
			pos.InterpolateTo(dest.pos,alpha),
			texCoord.InterpolateTo(dest.texCoord,alpha)
		};
	}
	TexVertex& operator-=(const TexVertex& rhs)
	{
		pos -= rhs.pos;
		texCoord -= rhs.texCoord;
		return *this;
	}
	TexVertex operator-(const TexVertex& rhs) const
	{
		return TexVertex(*this) -= rhs;
	}
	TexVertex& operator/=(float rhs)
	{
		pos /= rhs;
		texCoord /= rhs;
		return *this;
	}
	TexVertex operator/(float rhs) const
	{
		return TexVertex(*this) /= rhs;
	}
	TexVertex& operator*=(float rhs)
	{
		pos *= rhs;
		texCoord *= rhs;
		return *this;
	}
	TexVertex operator*(float rhs) const
	{
		return TexVertex(*this) *= rhs;
	}
	TexVertex& operator+=(const TexVertex& rhs)
	{
		pos += rhs.pos;
		texCoord += rhs.texCoord;
		return *this;
	}
	TexVertex operator+(const TexVertex& rhs) const
	{
		return TexVertex(*this) += rhs;
	}
	Vec3 pos;
	Vec2 texCoord;
};
