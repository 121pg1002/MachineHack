/*****************************************************************//**
 * @file  StateBaseRoot .cpp
 * @brief  ステートベース
 *
 * @author yamawaki kota
 * @date   December 6 2021
 *********************************************************************/

#pragma once
#include <string>
#include <unordered_map>
#include <memory>


//class Actor;



namespace AppFrame::Input {
	class InputComponent;
}

namespace MachineHuck::State {
	class StateBaseRoot {
	public:
		StateBaseRoot() {};
		virtual void Enter() {};
		virtual void Input(AppFrame::Input::InputComponent& input) {};
		virtual void Update() {};
		virtual void Draw() {};
	};
}