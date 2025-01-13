#pragma once

class SceneManager : public Singleton<SceneManager>
{
private:
	friend Singleton;

    SceneManager() = default;
    ~SceneManager();

public:
    void Update();
    void Render(HDC hdc);

    void Add(std::string sceneKey, Scene* scene);

    void ChangeScene(std::string sceneKey, std::string msg = "");

private:
    std::map<std::string, Scene*> scenes;

    Scene* curScene = nullptr;
};