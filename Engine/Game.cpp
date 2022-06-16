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
	/*auto lines = cube.Get_VL_Buffer();
	Matrix3 matrix = Matrix3::RotationX(theta_x) * Matrix3::RotationY(theta_y) * Matrix3::RotationZ(theta_z);
	for (Vec3& i : lines.vertex)
	{
		i *= matrix;
		i  += { 0.0f, 0.0f, 1.0f };
		toScreen.Transfrom(i);
	}
	for (auto i = lines.vertexIndex.begin(); i< lines.vertexIndex.end(); i += 2)
	{
		gfx.DrawLine(lines.vertex[*i], lines.vertex[*std::next(i)], Colors::White);
	}*/
	gfx.DrawTriangle(Vec2(10, 50), Vec2(40, 80), Vec2(25, 0), Colors::White);
}