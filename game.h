/*********************************************************************
 * \file   game.h
 * \brief   
 * \author MA HANGLONG
 * \date   2024 \ 02 \ 16
 *********************************************************************/
#pragma once
#include "main.h"
#include "render.h"
#include "Scene.h"
#include "TitleScnne.h"
#include "RenderComponent.h"
#include "AssetManager.h"
#include "input.h"
#include "sound.h"
#include "Debug.h"

class Game
{
public:
	Game() {}
	~Game() {}
	//游戏系统部分在这初始化
	void InitSystem(HINSTANCE hInstance, HWND hWnd, BOOL bWindow)
	{
		_dApi.Init(hInstance, hWnd, bWindow);
		AssetManager::Get()->Init(&_dApi);
		_renderComponent = new RenderComponentManager(&_dApi);
		Debug::Get()->Init(hWnd, &_dApi);
		InitInput(hInstance, hWnd);
		InitSound(hWnd);
	}
	void UnitSystem()
	{
		//_dApi.UnInit();
		UninitSound();
		UninitInput();
		delete _renderComponent;
		AssetManager::Get()->UnInit();
		delete _currentScene;
	}

	//游戏循环
	void Update(double deltaTime) 
	{
		if (_currentScene != nullptr)
		{
			UpdateInput();
			_currentScene->UpdateScene(deltaTime,this, _renderComponent); 
		}
		else
		{
			_currentScene = new TitleScene();
			_currentScene -> InitScene(this, _renderComponent);
		}
	}

	//切换场景，利用了状态机的概膩E
	void ChangeScene(Scene* nextScene)
	{
		if (_currentScene != nullptr)
		{
			_currentScene->UnInitScene(this);
			delete _currentScene;
			_currentScene = nextScene;
			nextScene->InitScene(this, _renderComponent);
		}
	};


private:
	Scene*						_currentScene=nullptr;
	DirectXAPI					_dApi;
	RenderComponentManager*		_renderComponent;
};
