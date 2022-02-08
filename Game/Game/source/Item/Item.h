#pragma once
#include "../Actor/Actor.h"

namespace MachineHuck::Item {

	class Item :public Actor::Actor {
	public:
		/// �R���X�g���N�^
	   /// @param[in] _game �Q�[���N���X�ւ̎Q��
		Item(AppFrame::Game& game);
		/// �f�X�g���N�^
		virtual ~Item() override = default;

		virtual	void	Update() override;
		virtual	void	Draw() override;

		//���[���h�s��̌v�Z
		//void ComputeWorldTransform() override;

		virtual TypeId GetTypeId()const override { return TypeId::Item; };

	private:
		enum class STATUS
		{
			SUCK,
			TANK,
			KEYITEM,
		};

		

		STATUS _status;
		bool itemflg;

	public:

		STATUS GetStatus() const { return _status; }
		void SetStatus(STATUS status) { _status = status; }

	};
}