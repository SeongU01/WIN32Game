#pragma once
#include"WinApp.h"
#include"InputSystem.h"
class Scene
{
private:
	const char* sceneName;
protected:
	bool isPlayMusic = false;
public:
	Scene() {}
	~Scene(){}

	virtual void Update()=0;
	virtual void Render()=0;

};



