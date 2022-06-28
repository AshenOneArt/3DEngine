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
	auto ver_Vstruct = cube.Get_VStruct_Buffer();
	auto ver_VTstruct = cube.Get_VTStruct_Buffer();
	Matrix3 matrix = Matrix3::RotationX(theta_x) * Matrix3::RotationY(theta_y) * Matrix3::RotationZ(theta_z);	
	for (auto& i : ver_VTstruct.vertex)
	{
		i.pos *= matrix;
		i.pos += { 0.0f, 0.0f, 1.0f };
	}

	for (size_t i = 0; i < ver_VTstruct.faceIndex.size() / 3; i++)
	{
		Vec3 vec3_0 = ver_VTstruct.vertex[ver_VTstruct.faceIndex[i * 3]].pos;
		Vec3 vec3_1 = ver_VTstruct.vertex[ver_VTstruct.faceIndex[i * 3 + 1]].pos;
		Vec3 vec3_2 = ver_VTstruct.vertex[ver_VTstruct.faceIndex[i * 3 + 2]].pos;
		ver_VTstruct.normalDir[i] = ((vec3_1 - vec3_0).Cross((vec3_2 - vec3_0))).GetNormalized();
		ver_VTstruct.cullBack[i] = ver_VTstruct.normalDir[i] * vec3_0.GetNormalized() <= 0.0f;
	}

	for (auto& i : ver_VTstruct.vertex)
	{
		toScreen.Transfrom(i.pos);
	}
	for (auto i = ver_VTstruct.faceIndex.begin(); i< ver_VTstruct.faceIndex.end(); i += 3)
	{
		int index = std::distance(ver_VTstruct.faceIndex.begin(), i);
		if (ver_VTstruct.cullBack[index/3])
		{
			gfx.DrawTriangle(ver_VTstruct.vertex[*i].pos, ver_VTstruct.vertex[*(i + 1)].pos, ver_VTstruct.vertex[*(i + 2)].pos, col[index / 3]);
			//gfx.DrawTriangleTex(ver_VTstruct.vertex[*i], ver_VTstruct.vertex[*(i + 1)], ver_VTstruct.vertex[*(i + 2)], sbTex);
		}		
		
	}
	/*for (auto i = ver_Vstruct.lineIndex.begin(); i < ver_Vstruct.lineIndex.end(); i += 2)
	{
		gfx.DrawLine(ver_Vstruct.vertex[*i], ver_Vstruct.vertex[*(i + 1)], Colors::White);
	}*/
}