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
		void Update();


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
		virtual void Move(std::string_view enemyName, int num = 0, double speed = 0.0, int numRange = 0);

		/**
		 * @brief �n�b�L���O����Ă��Ȃ��Ƃ��̌��������߂�
		 */
		void Direction();


		/**
		 * @brief  �n�b�L���O���ꂽ�Ƃ��̈ړ�
		 * @param  lx �������̌X��
		 * @param  ly �c�����̌X��
		 */
		const void HuckedMove(const double lx, const double ly);

		/**
		 * @brief ���G���̈ړ����[�`��
		 * @param num      ���[�`���ԍ�
		 * @param speed    �ړ��X�s�[�h
		 * @param numRange �񐔔͈�
		 */
		void RoutineMove(int num, double speed, int numRange = 100);


		//void ParameterLoad();

		/**
		 * @brief �O�����ւ̑��x
		 * @param forwardSpeed
		 */

		void SetForwardSpeed(float forwardSpeed) { _forwardSpeed = forwardSpeed; }

	protected:


		STATUS _status{ STATUS::WAIT };
		double _forwardSpeed;
		int _numberTimes{ -1 };
		int _soundFrame;

	};
}


