#pragma once
#include "Singleton.h"
#include <string>
#include <memory>
#include <vector>

namespace cri
{
	class Scene;
	class SceneManager final : public Singleton<SceneManager>
	{
	public:
		Scene& CreateScene(const std::string& name);


		void NextScene();
		void PreviousScene();
		void OpenScene(int sceneIdx);
		Scene& GetScene(int sceneIdx);
		Scene& GetCurrentScene();

		void Update();
		void FixedUpdate();
		void LateUpdate();
		void Render();
	private:
		int m_CurrentSceneIdx = -1;
		friend class Singleton<SceneManager>;
		SceneManager() = default;
		std::vector<std::shared_ptr<Scene>> m_Scenes;
	};
}
