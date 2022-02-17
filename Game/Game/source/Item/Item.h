/*****************************************************************//**
 * @file   Item.h
 * @brief  �A�C�e���N���X
 *
 * @author kyoga Tagawa
 * @date   2022/02/01
 *********************************************************************/
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
		void	Init();
		virtual	void	Update() override;
		virtual	void	Draw() override;

		//���[���h�s��̌v�Z
		//void ComputeWorldTransform() override;

		virtual TypeId GetTypeId()const override { return TypeId::Item; };
	   /**
	    * @brief �G�l���M�[�T�b�N�̎擾�t���O���Z�b�g(TRUE:�擾���Ă���AFLASE�F�擾���Ă��Ȃ��j
	    * @param flg
	    */
		void SetSuckFlg(bool flg) { _suckFig = flg; }

		/**
		* @brief�G�l���M�[�T�b�N�̎擾�t���O���擾
		*/
		bool  GetSuckFlg() { return _suckFig; }



	private:
		enum class STATUS
		{
			SUCK,
			TANK,
			KEYITEM,
		};

		

		STATUS _status;
		bool itemflg;
		bool _suckFig;//�G�l���M�[�T�b�N���擾�������B

	public:

		STATUS GetStatus() const { return _status; }
		void SetStatus(STATUS status) { _status = status; }

	};
}