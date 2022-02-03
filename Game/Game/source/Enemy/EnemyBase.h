/*****************************************************************//**
 * @file   EnemyBase.h
 * @brief  �G�l�~�[�̊��N���X
 * 
 * @author hikaru Goto
 * @date   December 19 2021
 *********************************************************************/

#pragma once
#include "../Actor/Actor.h"
#include <string_view>

namespace MachineHuck::Enemy {
	class EnemyBase : public Actor::Actor
	{
	public:
		EnemyBase(AppFrame::Game& game);
		~EnemyBase();

		//bool IsHucked(const EnemyBase& enemy);

		enum class Type
		{
			Base = 0,
			Tackle,
			Catch,
		};

		enum class STATUS
		{
			NONE,
			WAIT,
			WALK,
			ISHUCKING,
			ISHUCKED,
			SEARCH,
			CHASE,
			DYING
		};
		virtual Type GetType() const = 0;

		STATUS GetStatus() const { return _status; }
		void SetStatus(STATUS status) { _status = status; }

		virtual TypeId GetTypeId() const override = 0;

		/**
		 * @brief  �n�b�L���O����Ă��Ȃ��Ƃ��̈ړ�       
		 * @param  enemyName
		 */
		virtual void Move(std::string_view enemyName);
		
		/**
         * @brief  �n�b�L���O���ꂽ�Ƃ��̈ړ�  
         * @param  lx �������̌X��
         * @param  ly �c�����̌X��
         */
		const void HuckedMove(const double lx, const double ly);

		void SetForwardSpeed(float forwardSpeed) { _forwardSpeed = forwardSpeed; }

	protected:


		STATUS _status{ STATUS::WAIT };
		double _forwardSpeed;

	};
}


