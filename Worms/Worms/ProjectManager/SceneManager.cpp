#include "framework.h"

SceneManager::~SceneManager()
{
	for(std::pair<std::string, Scene*> scene : scenes)
	{
		delete scene.second;
	}
}

void SceneManager::Update()
{
	if (curScene == nullptr)
		return;

	curScene->Update();
}

void SceneManager::Render(HDC hdc)
{
    if (curScene == nullptr)
        return;

    curScene->Render(hdc);
}

void SceneManager::Add(std::string sceneKey, Scene* scene)
{
    if (scenes.count(sceneKey) > 0)
        return;

    scenes[sceneKey] = scene;
}

void SceneManager::ChangeScene(std::string sceneKey, std::string msg)
{
    std::map<std::string, Scene*>::iterator iter = scenes.find(sceneKey);
    assert(iter != scenes.end());

    if (iter->second == curScene)
        return;

    if (curScene != nullptr)
        curScene->End();

    curScene = iter->second;
    curScene->Start(msg);
}
