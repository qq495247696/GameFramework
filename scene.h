#pragma once
class Game;
class World;
class RenderComponentManager;
class Scene
{
public:
	Scene() = default;
	virtual ~Scene() {}

	virtual void InitScene(Game * game, RenderComponentManager* rManager) = 0;
	virtual void UpdateScene(double deltaTime,Game* game, RenderComponentManager* component) = 0;
	virtual void UnInitScene(Game* game) = 0;
protected:
	World* _world;
};
