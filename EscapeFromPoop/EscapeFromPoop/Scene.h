#pragma once
#include"WinApp.h"
#include"InputSystem.h"
class Scene
{
private:
	const char* sceneName;
public:
	Scene() {}
	~Scene(){}

	virtual void Update()=0;
	virtual void Render()=0;

};



