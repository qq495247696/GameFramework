#pragma once
#include "main.h"
#include <imgui.h>
#include "input.h"
#include <imgui_impl_dx11.h>
#include <imgui_impl_win32.h>
#include "World.h"
#include "player.h"
class DirectXAPI;
class Debug
{
public:
	static Debug* Get()
	{
		static Debug p;
		return &p;
	}

	void Init(HWND hWnd, DirectXAPI* api) 
	{
		IMGUI_CHECKVERSION();
		ImGui::CreateContext();
		ImGuiIO& io = ImGui::GetIO();
		io.ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard;     // 允许键盘控制
		io.ConfigWindowsMoveFromTitleBarOnly = true;              // 仅允许标题拖动
		io.FontGlobalScale = 2.5f;

		// 设置Dear ImGui风格
		ImGui::StyleColorsDark();

		// 设置平台/渲染器后端
		ImGui_ImplWin32_Init(hWnd);
		ImGui_ImplDX11_Init(api->GetDevice().Get(),api->GetDeviceContext().Get());
	};

	void SetWorld(World* world)
	{
		_world = world;
	}

	void NewFrame()
	{
		ImGui_ImplDX11_NewFrame();
		ImGui_ImplWin32_NewFrame();
		ImGui::NewFrame();
	
	}
	void Update()
	{
		if (GetKeyboardTrigger(DIK_O))
		{
			debug = !debug;
		}
		if (ImGui::Begin("Debug")&& debug)
		{
			auto player = _world->GetObjectWithTag<Player>("Player");
			ImGui::Text("position:");
			ImGui::NewLine();
			ImGui::TextColored({1,0,0,1}, "X:%.2f", player->GetPosition().x);
			ImGui::SameLine(150, 0);
			ImGui::TextColored({ 0,1,0,1 }, "Y:%.2f", player->GetPosition().y);
			ImGui::SameLine(250, 0);
			ImGui::TextColored({ 0,0,1,1 }, "Z:%.2f", player->GetPosition().z);
		}
		ImGui::End();
		
	}

	void Draw()
	{
		if (debug==true)
		{
			ImGui::Render();
			ImGui_ImplDX11_RenderDrawData(ImGui::GetDrawData());
		}
		else
		{
			ImGui::EndFrame();
		}
	}
private:
	Debug() {};
	~Debug() {};
	bool debug  =false;
	World* _world;
};
