#pragma once
#include "Graphics.h"
#include "Vec3.h"


class ScreenTransform
{
public:
	ScreenTransform()
		:xFactor(Graphics::ScreenWidth), yFactor(Graphics::ScreenHeight)
	{}
	Vec3& Transfrom(Vec3& Campos)const
	{
		//Campos(-1 ~ 1) => NDCpos(0 ~ 1) 
		//and window's Y is down to up ,the coordinate system we want is up to down !
		Campos.x =  (Campos.x * 0.5f * 1 / Campos.z + 0.5f)* xFactor;
		Campos.y = (-Campos.y * 0.5f * 1 / Campos.z + 0.5f)* yFactor*(xFactor/ yFactor) - (xFactor- yFactor)/2.0;
		
		return Campos;
	}
	Vec3 GetTransfrom(const Vec3& Campos)const
	{			
		return Transfrom(Vec3(Campos));
	}
private:
	float xFactor;
	float yFactor;	
};
