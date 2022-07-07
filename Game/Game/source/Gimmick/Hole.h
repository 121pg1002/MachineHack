#pragma once
#include "AppFrame.h"
#include "GimmickBase.h"

namespace MachineHuck::Gimmick {

	class Hole : public GimmickBase {
	public:

		Hole(AppFrame::Game& game);
		~Hole() override = default;

		TypeId GetTypeId() const override { return TypeId::Gimmick; }

		void Update();
		void Draw();
	private:

	};

}




