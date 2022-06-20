/******************************************************************************************
*	Chili DirectX Framework Version 16.10.01											  *
*	Game.cpp																			  *
*	Copyright 2016 PlanetChili.net <http://www.planetchili.net>							  *
*																						  *
*	This file is part of The Chili DirectX Framework.									  *
*																						  *
*	The Chili DirectX Framework is free software: you can redistribute it and/or modify	  *
*	it under the terms of the GNU General Public License as published by				  *
*	the Free Software Foundation, either version 3 of the License, or					  *
*	(at your option) any later version.													  *
*																						  *
*	The Chili DirectX Framework is distributed in the hope that it will be useful,		  *
*	but WITHOUT ANY WARRANTY; without even the implied warranty of						  *
*	MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the						  *
*	GNU General Public License for more details.										  *
*																						  *
*	You should have received a copy of the GNU General Public License					  *
*	along with The Chili DirectX Framework.  If not, see <http://www.gnu.org/licenses/>.  *
******************************************************************************************/
#include "MainWindow.h"
#include "Game.h"
#include "Mat2.h"
#include "Matrix3.h"
#include <sstream>
Game::Game( MainWindow& wnd )
	:
	wnd( wnd ),
	gfx( wnd ),
	cube(0.5)
{
}

void Game::Go()
{
	gfx.BeginFrame();
	UpdateModel();
	ComposeFrame();
	gfx.EndFrame();
}

void Game::UpdateModel()
{
	std::stringstream str;
	const float dt = 1.0f / 120.0f;
	if (wnd.kbd.KeyIsPressed('W'))
	{
		theta_x += dTheta * dt;
		
		str << theta_x << std::endl;
		OutputDebugStringA(str.str().c_str());
	}
	if (wnd.kbd.KeyIsPressed('S'))
	{
		theta_x -= dTheta * dt;
		str << theta_x << std::endl;
		OutputDebugStringA(str.str().c_str());
	}
	if (wnd.kbd.KeyIsPressed('D'))
	{
		theta_y += dTheta * dt;
		str << theta_y << std::endl;
		OutputDebugStringA(str.str().c_str());
	}
	if (wnd.kbd.KeyIsPressed('A'))
	{
		theta_y -= dTheta * dt;
		str << theta_y << std::endl;
		OutputDebugStringA(str.str().c_str());
	}
	if (wnd.kbd.KeyIsPressed('Q'))
	{
		theta_z -= dTheta * dt;
		str << theta_z << std::endl;
		OutputDebugStringA(str.str().c_str());
	}
	if (wnd.kbd.KeyIsPressed('E'))
	{
		theta_z += dTheta * dt;
		str << theta_z << std::endl;
		OutputDebugStringA(str.str().c_str());
	}
}

void Game::ComposeFrame()
{
	std::vector<Color> col =
	{
		Colors::Blue,
		Colors::Cyan,
		Colors::Gray,
		Colors::Green,
		Colors::LightGray,
		Colors::Magenta,
		Colors::Red,
		Colors::White,
		Colors::Yellow,
		Colors::Blue,
		Colors::Cyan,
		Colors::Gray
	};
	auto ver = cube.Get_VStruct_Buffer();
	
	Matrix3 matrix = Matrix3::RotationX(theta_x) * Matrix3::RotationY(theta_y) * Matrix3::RotationZ(theta_z);	
	for (Vec3& i : ver.vertex)
	{
		i *= matrix;
		i  += { 0.0f, 0.0f, 1.0f };		
	}

	for (size_t i = 0; i < ver.faceIndex.size() / 3; i++)
	{
		Vec3 vec3_0 = ver.vertex[ver.faceIndex[i * 3]];
		Vec3 vec3_1 = ver.vertex[ver.faceIndex[i * 3 + 1]];
		Vec3 vec3_2 = ver.vertex[ver.faceIndex[i * 3 + 2]];
		ver.normalDir[i] = ((vec3_1 - vec3_0).Cross((vec3_2 - vec3_0)));
		ver.cullBack[i] = ver.normalDir[i] * vec3_0 <= 0.0f;
	}

	for (Vec3& i : ver.vertex)
	{
		toScreen.Transfrom(i);
	}
	for (auto i = ver.faceIndex.begin(); i< ver.faceIndex.end(); i += 3)
	{
		int index = std::distance(ver.faceIndex.begin(), i);
		if (ver.cullBack[index/3])
		{
			gfx.DrawTriangle(ver.vertex[*i], ver.vertex[*(i+1)], ver.vertex[*(i + 2)], col[index/3]);
		}

		//float a =  ver.normalDir[index / 3] * ver.vertex[ver.faceIndex[index]].GetNormalized() ;
		
	}

	//gfx.DrawTriangle(Vec2(theta_z, 250), Vec2(200, 250), Vec2(50, 50), Colors::White);
	//gfx.DrawTriangle(Vec2(50, 250), Vec2(200, 250), Vec2(50, 50), Colors::White);
}