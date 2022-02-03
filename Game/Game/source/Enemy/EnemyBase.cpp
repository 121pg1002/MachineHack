/*****************************************************************//**
 * @file   EnemyBase.h
 * @brief  �G�l�~�[�̊��N���X
 *
 * @author hikaru Goto
 * @date   December 19 2021
 *********************************************************************/

#include "EnemyBase.h"
#include "../Actor/ActorServer.h"
#include "../Gauge/GaugeBase.h"
#include "../Gauge/GaugeEnemy.h"

namespace MachineHuck::Enemy {
	//�R���X�g���N�^
	EnemyBase::EnemyBase(AppFrame::Game& game) : Actor::Actor{ game } {
	}
	//�f�X�g���N�^
	EnemyBase::~EnemyBase() {
	}

	void EnemyBase::Move(std::string_view enemyName, int num) {

		//// �v���C���[�Ɍ������P�ʃx�N�g��
        //auto forward = GetForward();
        //// �v���C���[�Ɍ������ړ��ʃx�N�g��
        //auto delta = forward * _forwardSpeed;
        //// �v���C���[�Ɍ������Ĉړ�
        //_position = _position + delta;

		_oldPos = _position;

		//���G���ł͂Ȃ�
		if (_status != STATUS::SEARCH) {

			//�n�b�L���O���ꂽ�܂��̓n�b�L���O���ł͂Ȃ�
			if (_status != STATUS::ISHUCKED && _status != STATUS::ISHUCKING) {
				auto player = GetActorServer().GetPosition("Player");
				// �v���C���[�Ɍ������x�N�g��
				player = { player.GetX(), 0.0, player.GetZ() };
				auto forward = player - _position;
				// �v���C���[�Ɍ������P�ʃx�N�g��
				if (Math::Vector4 v{ 0.0, 0.0, 0.0 }; forward.GetX() != v.GetX() && forward.GetZ() != v.GetZ()) {
					forward = forward.Normalize();
				}
				// �v���C���[�Ɍ������ړ��ʃx�N�g��
				auto delta = forward * _forwardSpeed;
				// �v���C���[�Ɍ������Ĉړ�
				_position = _position + delta;

				// Y���̉�]�p�x�����߂遦���v���z��x
				auto rotY = std::atan2(forward.GetX(), forward.GetZ());
				Math::Vector4 rot = { 0.0, rotY, 0.0 };
				SetRotation(rot);

				// �A�N�^�[�T�[�o�[�Ɉʒu��ʒm
				std::pair<Math::Vector4, Math::Vector4> posDir = { _position, rot };
				GetActorServer().Register(enemyName, posDir);


				// ���[���h�s��̌v�Z
				//ComputeWorldTransform();
			} //�n�b�L���O���ł͂Ȃ�
			else if (_status != STATUS::ISHUCKING) {
				//auto playermove = GetActorServer().GetPosition("Player");
				//_position = playermove;
				//// Y���̉�]�p�x�����߂遦���v���z��x
				//auto dir = GetActorServer().GetDir("Player");
				//auto rotY = std::atan2(dir.GetX(), dir.GetZ());
				//Math::Vector4 rot = { 0.0, rotY, 0.0 };
				//SetRotation(rot);
				//LockOn();




				//ComputeWorldTransform();
			}



		}
		else {


			//���G���̈ړ����[�`��
			//RoutineMove(num, 2.0);

		}

		//if (CollisionFloor(_oldPos)) {
		//
		//	int x = 0;
		//}
		CollisionFloor(_oldPos, GetR());

	}
	//�n�b�N����
	//bool IsHucked(const EnemyBase& enemy)
	//{
	//    if (enemy.GetTypeId() != Actor::Actor::TypeId::Enemy)
	//    {
	//        return false;
	//    }
	//    else
	//    {
	//        if (enemy.isDead())
	//        {
	//            return false;
	//        }
	//        else
	//        {
	//            if (enemy.GetStatus() != EnemyBase::STATUS::ISHUCKED)
	//            {
	//                return false;
	//            }
	//            else
	//            {
	//                return true;
	//            }
	//        }
	//    }
	//}


		//�n�b�L���O���ꂽ�Ƃ��̈ړ�
	const void EnemyBase::HuckedMove(const double lx, const double ly) {

		_move = { 0.0, 0.0, 0.0 };

		//_oldPos = _position;
		//�������̌X���Əc�����̌X���̑傫��
		double length = sqrt(lx * lx + ly * ly);
		if (length < 0.3) {
			// ���͂������������瓮���Ȃ��������Ƃɂ���
			length = 0.0;
		}
		else {
			length = 5.0;
		}

		//�������Əc�����̊p�x
		double rad = atan2(ly, lx);

		//x�������̈ړ���
		auto moveX = std::cos(rad) * length;

		//z�������̈ړ���
		auto moveZ = std::sin(rad) * length;

		_move = { moveX, 0.0, moveZ };
		// �ړ�
		_position = _position + _move;

		if (_move.Length() > 0.0)
		{
			auto dir = _move;
			auto yRot = std::atan2(dir.GetX(), dir.GetZ());

			Math::Vector4 rot = { 0.0, yRot, 0.0 };
			SetRotation(rot);

			//�ړ����Ă����猸�炷
			GetGaugeBase().Update(*this);
			GetGaugeEnemy().Update(*this);
		}

		//��l���̃J�����Ɉړ��ʂ𑗂�
		SetHuckedMove(_move);



		// ���[���h�s��̍X�V
		//ComputeWorldTransform();

		// Y���̉�]�p�x�����߂遦���v���z��x
		//auto dir = GetActorServer().GetDir("Player");

		//Math::Vector4 rot = { 0.0, rad, 0.0 };

		//rot.Set(0.0, rad, 0.0);
		//SetRotation(rot);
		//LockOn();


	}

	void EnemyBase::RoutineMove(int num, double speed, int numRange) {

		Math::Vector4 move = { 0.0, 0.0, 0.0 };
		double rotY = 0.0;

		//���E�ړ�
		if (num == 1) {

			if (_numberTimes < numRange/2) {
				 move = { speed, 0.0, 0.0 };

			}
			else {
				 move = { -speed, 0.0, 0.0 };


			}


		} //�㉺�ړ�
		else if (num == 2) {

			if (_numberTimes < numRange/2) {
				 move = { 0.0, 0.0, speed };
			}
			else {
				 move = { 0.0, 0.0, -speed };
			}



		}//��]�ړ�(�E��])
		else if (num == 3) {

			if (_numberTimes < numRange/4) {
				
				 move = { 0.0, 0.0, speed };

			}
			else if (numRange / 4 <= _numberTimes && _numberTimes < numRange / 4 * 2) {
			
				 move = { speed, 0.0, 0.0 };
			
			}
			else if (numRange / 4 * 2 <= _numberTimes && _numberTimes < numRange / 4 * 3) {
			
				 move = { 0.0, 0.0, -speed };
			
			}
			else {
				 move = { -speed, 0.0, 0.0 };
			}

		
		
		}

		_position = _position + move;
		// Y���̉�]�p�x�����߂�(���v���z��x)
		rotY = std::atan2(move.GetX(), move.GetZ());

		Math::Vector4 rot = { 0.0, rotY, 0.0 };
		SetRotation(rot);

		//�񐔂����Z�b�g
		if (_numberTimes < 0) {
			_numberTimes = numRange;
		}
		else {
			_numberTimes--;
		}

	}
}