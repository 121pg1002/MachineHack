
/*****************************************************************//**
 * @file   SceneLoading.h
 * @brief  InGame‚Æ‚Ì‚Â‚È‚¬–Ú‚ÌƒNƒ‰ƒX
 * 
 * @author hikaru Goto
 * @date   January 2022
 *********************************************************************/

#pragma once
#include "AppFrame.h"

namespace MachineHuck::Scene {

	class SceneLoading : public AppFrame::Scene::Scene {
	public:

		SceneLoading(AppFrame::Game& game);

		~SceneLoading() = default;

		void Init() override {};

		void Update() override;

	private:



	};

}

