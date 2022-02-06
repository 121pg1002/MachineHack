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

		virtual	void	Init() override;
		virtual	void	Input(AppFrame::Input::InputComponent& input) override;
		virtual	void	Update() override;
		virtual	void	Draw() override;

		/// ���[���h�s��̌v�Z
	   /// ���f���̃��[�J��Z���W���t�Ȃ̂ł�����180�x��]������
		void ComputeWorldTransform() override;

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