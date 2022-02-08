/*****************************************************************//**
 * @file   TackleEnemy.h
 * @brief  �^�b�N������G
 *
 * @author hikaru Goto
 * @date   December 19 2021
 *********************************************************************/
#include "AppFrame.h"
#include "TackleEnemy.h"
#include "../Actor/ActorServer.h"
#include "../Model/ModelAnimComponent.h"
#include "../Collision/CollisionComponent.h"
#include "../Gauge/GaugeBase.h"
#include "../Gauge/GaugeEnemy.h"
#include "../Gauge/GaugePlayer.h"
#include "../Flag/FlagData.h"

#include <cmath>
 //#include <numbers>
#include <random>
#include "EnemyParameter.h"

//namespace Math = AppFrame::Math;

namespace MachineHuck::Enemy {

	//�ÓI�ȃ����o�\�ϐ������̉�������
	int TackleEnemy::StateBase::_huckNoDamageTime;

	TackleEnemy::TackleEnemy(AppFrame::Game& game) : EnemyBase{ game } {

		_r = 0.0;
		_huckR = 0.0;
		_minXZ = { -200.0, -100.0 };
		_maxXZ = { 200.0, 100.0 };
		_lmin = { 0.0, -100.0, 0.0 };
		_lmax = { 0.0, 100.0, 0.0 };
		_status = STATUS::WAIT;
		_searchRange = 0.0;
		_huckingRange = 0.0;
		_gaugeBase->Init();
		_gaugeEnemy->Init(*this);//�G�l�~�[�̃G�l���M�[�Q�[�W�̏�����
	}

	void TackleEnemy::LoadJson(const std::string& filePath)
	{
		auto eParam = std::make_unique<EnemyParameter>();
		eParam->LoadEnemyParam(filePath);

		//auto eParam = std::make_unique<EnemyParameter>();
		//eParam->LoadEnemyParam("resource/json/tackle.json");
		////2�߂̒l�����x��
		//_r = eParam->GetEnemyParam("r", 0);
		_r = 150.0;
		//_huckR = eParam->GetEnemyParam("r", 0);
		_huckR = 200.0;

		_searchRange = eParam->GetEnemyParam("searchrange", 1);
		_huckingRange = eParam->GetEnemyParam("searchrange", 0);////////���Ƃ肠�����A��



	}

	//�e��p�����[�^�[��ǂݍ���
	//void TackleEnemy::ParameterLoad() {


	//	
	//}


	void TackleEnemy::Update() {

		EnemyBase::Update();
		//�Q�[�W
		_gaugeEnemy->Update();

		if (_status != STATUS::DYING) {

			if (GetActorState() == ActorState::Hucking) {
				_status = STATUS::ISHUCKING;
			}
			else if (GetActorState() == ActorState::Hucked) {
				_status = STATUS::ISHUCKED;
			}
			else if (GetActorState() == ActorState::Active) {

				if (_status != STATUS::CHASE) {
					_status = STATUS::SEARCH;
				}

				//if (_status != STATUS::WAIT) 
				//{
				   // _status = STATUS::WALK;
				//}
			}
		}

		if (_status != STATUS::DYING && _status != STATUS::CHASE) {
			Move("TackleEnemy", _routine, 2.0, 200);
		}

		if (_status == STATUS::ISHUCKED) {
			SetShadowMapflg(TRUE);
		}
		else
		{
			SetShadowMapflg(FALSE);
		}

		_state->Update();

		//// ���[���h�s��̌v�Z
		ComputeWorldTransform();

		// ���f���̍X�V
		_modelAnime->Update();

	}

	void TackleEnemy::Input(AppFrame::Input::InputComponent& input) {
		_state->Input(input);
	}

	void TackleEnemy::Draw() {
		// ���̃g�Q�ׂ̈̃A���t�@�e�X�g�ݒ�
		MV1SetMaterialDrawAlphaTest(_modelAnime->GetHandle(), 3, TRUE, DX_CMP_LESS, 200);
#ifdef _DEBUG
		//auto pos = _position;
		//pos.y += 40;
		//DrawSphere3D(pos, 50, 16, GetColor(255, 0, 0), GetColor(0, 0, 0), TRUE);
		_modelAnime->Draw(*this, _isHit, _searchRange, true);
		_modelAnime->Draw(*this, _isHit, _huckingRange, false);
		_modelAnime->Draw(*this, GetActorServer().GetPosition("Player"));

		_gaugeBase->Draw(*this);
#endif
		_state->Draw();
		//if (!GetShadowMapflg() == TRUE) {
		_gaugeEnemy->Draw(*this);
		//	}
	}

	void TackleEnemy::ComputeWorldTransform() {
		auto world = MGetScale(ToDX(_scale));
		world = MMult(world, MGetRotZ(static_cast<float>(_rotation.GetZ())));
		world = MMult(world, MGetRotX(static_cast<float>(_rotation.GetX())));
		world = MMult(world, MGetRotY(static_cast<float>(_rotation.GetY()) + DX_PI_F));
		_worldTransform = MMult(world, MGetTranslate(ToDX(_position)));
	}

	//void TackleEnemy::Move() {
	//	//// �v���C���[�Ɍ������P�ʃx�N�g��
	//	//auto forward = GetForward();
	//	//// �v���C���[�Ɍ������ړ��ʃx�N�g��
	//	//auto delta = forward * _forwardSpeed;
	//	//// �v���C���[�Ɍ������Ĉړ�
	//	//_position = _position + delta;

	//	_oldPos = _position;

	//	//���G���ł͂Ȃ�
	//	if (_status != STATUS::SEARCH) {

	//		//�n�b�L���O���ꂽ�܂��̓n�b�L���O���ł͂Ȃ�
	//		if (_status != STATUS::ISHUCKED && _status != STATUS::ISHUCKING) {
	//			auto player = GetActorServer().GetPosition("Player");
	//			// �v���C���[�Ɍ������x�N�g��
	//			player = { player.GetX(), 0.0, player.GetZ() };
	//			auto forward = player - _position;
	//			// �v���C���[�Ɍ������P�ʃx�N�g��
	//			if (Math::Vector4 v{ 0.0, 0.0, 0.0 }; forward.GetX() != v.GetX() && forward.GetZ() != v.GetZ())
	//			{
	//				forward = forward.Normalize();
	//			}
	//			// �v���C���[�Ɍ������ړ��ʃx�N�g��
	//			auto delta = forward * _forwardSpeed;
	//			// �v���C���[�Ɍ������Ĉړ�
	//			_position = _position + delta;

	//			// Y���̉�]�p�x�����߂遦���v���z��x
	//			auto rotY = std::atan2(forward.GetX(), forward.GetZ());
	//			Math::Vector4 rot = { 0.0, rotY, 0.0 };
	//			SetRotation(rot);

	//			// �A�N�^�[�T�[�o�[�Ɉʒu��ʒm
	//			std::pair<Math::Vector4, Math::Vector4> posDir = { _position, rot };
	//			GetActorServer().Register("TackleEnemy", posDir);


	//			// ���[���h�s��̌v�Z
	//			//ComputeWorldTransform();
	//		} //�n�b�L���O���ł͂Ȃ�
	//		else if (_status != STATUS::ISHUCKING) {
	//			//auto playermove = GetActorServer().GetPosition("Player");
	//			//_position = playermove;
	//			//// Y���̉�]�p�x�����߂遦���v���z��x
	//			//auto dir = GetActorServer().GetDir("Player");
	//			//auto rotY = std::atan2(dir.GetX(), dir.GetZ());
	//			//Math::Vector4 rot = { 0.0, rotY, 0.0 };
	//			//SetRotation(rot);
	//			//LockOn();
	//			


	//			
	//			//ComputeWorldTransform();
	//		}



	//	}
	//	else 
	//	{
	//		/// <summary>
	//		///���̓���(���E)
	//		/// </summary>
	//		if (_numberTimes < 100)
	//		{
	//			Math::Vector4 move = { 2.0, 0.0, 0.0 };
	//			_position = _position + move;
	//			// Y���̉�]�p�x�����߂遦���v���z��x
	//			auto rotY = std::atan2(move.GetX(), move.GetZ());
	//			Math::Vector4 rot = { 0.0, rotY, 0.0 };
	//			SetRotation(rot);

	//		}
	//		else
	//		{
	//			Math::Vector4 move = { -2.0, 0.0, 0.0 };
	//			_position = _position + move;
	//			// Y���̉�]�p�x�����߂遦���v���z��x
	//			auto rotY = std::atan2(move.GetX(), move.GetZ());
	//			Math::Vector4 rot = { 0.0, rotY, 0.0 };
	//			SetRotation(rot);
	//		}

	//		if (_numberTimes > 200)
	//		{
	//			_numberTimes = 0;
	//		}
	//		else
	//		{
	//			_numberTimes++;
	//		}

	//	}

	//	CollisionFloor(_oldPos);

	//}

	//�n�b�L���O���ꂽ�Ƃ��̈ړ�
	//void TackleEnemy::HuckedMove(double lx, double ly) {
	//
	//	_move = { 0.0, 0.0, 0.0 };

	//	//_oldPos = _position;
	//	//�������̌X���Əc�����̌X���̑傫��
	//	double length = sqrt(lx * lx + ly * ly);
	//	if (length < 0.3) {
	//		// ���͂������������瓮���Ȃ��������Ƃɂ���
	//		length = 0.0;
	//	}
	//	else {
	//		length = 5.0;
	//	}

	//	//�������Əc�����̊p�x
	//	double rad = atan2(ly, lx);

	//	//x�������̈ړ���
	//	auto moveX = cos(rad) * length;

	//	//z�������̈ړ���
	//	auto moveZ = sin(rad) * length;

	//	_move = { moveX, 0.0, moveZ };
	//	// �ړ�
	//	_position = _position + _move;

		   //�ړ����Ă����猸�炷
		//   _gaugeBase->Update(*this);

		//}

	//	   Math::Vector4 rot = { 0.0, yRot, 0.0 };
	//	   SetRotation(rot);

	//	   //�ړ����Ă����猸�炷
	//	   _gaugeBase->Update(*this);
	//	}

	//	//��l���̃J�����Ɉړ��ʂ𑗂�
	//	SetHuckedMove(_move);



	//	// ���[���h�s��̍X�V
	//	//ComputeWorldTransform();

	//	// Y���̉�]�p�x�����߂遦���v���z��x
	//	//auto dir = GetActorServer().GetDir("Player");
	//	
	//	//Math::Vector4 rot = { 0.0, rad, 0.0 };
	//		
	//	//rot.Set(0.0, rad, 0.0);
	//	//SetRotation(rot);
	//	//LockOn();


	//}

	//void TackleEnemy::LockOn() {
	//	auto player = GetActorServer().GetPosition("Player");
	//	// �v���C���[�Ɍ������x�N�g��
	//	auto forward = player - _position;
	//	// �v���C���[�Ɍ������P�ʃx�N�g��
	//	forward = forward.Normalize();
	//	// Y���̉�]�p�x�����߂遦���v���z��x
	//	auto rotY = std::atan2(forward.GetX(), forward.GetZ());
	//	Math::Vector4 rot = { 0.0, rotY, 0.0 };
	//	SetRotation(rot);
	//}

	//void TackleEnemy::Tackle(Math::Vector4 target) {

	//	//���łɌ��܂������؂܂Ń^�b�N������@�\������

	//}

	//void TackleEnemy::HitCheckFrom() {
	//	//auto& report = _collision->GetReport();
	//	//if (report.id == CollisionComponent::ReportId::HitFromPlayer) {
	//	//	_state->GoToState("Die");
	//	//	GetGame().GetSoundComponent().Play("damage");
	//	//}
	//	//else if (report.id == CollisionComponent::ReportId::HuckedFromPlayer) 
	//	//{
	//	//	_state->GoToState("Idle");
	//	//}
	//}



	void TackleEnemy::StateBase::Draw() {

		if (_owner.GetStatus() != STATUS::ISHUCKED) {
			_owner.GetModelAnime().Draw();
		}
		else {
			_owner.GetModelAnime().SpecificDraw();
		}
	}

	// �ҋ@
	void TackleEnemy::StateFall::Enter() {
		_owner.GetModelAnime().ChangeAnime("Walk", true);
	}

	void TackleEnemy::StateFall::Update() {

		//_owner.LockOn();
		if (_owner._position.GetY() > 0) {
			auto posY = _owner._position.GetY() - 5;
			//Math::Vector4 _pos = { 0.0, _pos_y, 0.0 };
			_owner._position = { _owner.GetPosition().GetX(), posY, _owner.GetPosition().GetZ() };
		}
		else {
			Math::Vector4 pos = { _owner.GetPosition().GetX(), 0.0, _owner.GetPosition().GetZ() };
			_owner._position = pos;
			_owner._state->GoToState("Idle");
		}
	}

	//�ҋ@
	void TackleEnemy::StateIdle::Enter() {
		_owner.GetModelAnime().ChangeAnime("Walk", true);
	}

	void TackleEnemy::StateIdle::Update() {


		if (_owner.GetStatus() == STATUS::ISHUCKING)
		{
			_owner._state->GoToState("IsHucking");
		}

		for (auto i = _owner.GetActorServer().GetActors().begin(); i != _owner.GetActorServer().GetActors().end(); i++)
		{
			//!< �v���C���[�ł͂Ȃ������玟��
			if ((*i)->GetTypeId() != TypeId::Player) {
				continue;
			}
			else {

				//if (_owner._collision->FanToPoint(_owner, **i)){
				//	_owner._state->GoToState("Run");
				//	_owner._status = STATUS::CHASE;
				//}

				if (_owner._collision->FanToPoint(_owner, **i, true)) {
					_owner._state->GoToState("Run");
					_owner._status = STATUS::CHASE;
					//*se �v���C���[����
					_owner.GetGame().GetSoundComponent().Play("contact");

				}

			}
		}
	}

	// ����
	void TackleEnemy::StateRun::Enter() {
		_tacklePreTime = 60;
		_owner.GetModelAnime().ChangeAnime("Walk", true);
	}

	void TackleEnemy::StateRun::Update() {
		//auto player = _owner.GetActorServer().GetPosition("Player");
		//// �v���C���[�Ɍ������x�N�g��
		//auto forward = player  - _owner._position;
		//auto distSq = std::pow(forward.Length(), 2.0);

		if (_owner.GetStatus() == STATUS::ISHUCKING)
		{
			_owner._state->GoToState("IsHucking");
			//_loseSightTime = 60;
		}
		//if (distSq < 130 * 130) {
		//	_owner._state->PushBack("Attack");
		//	return;
		//}
		/*_owner.LockOn();*/
		Math::Vector4 oldPos = _owner.GetPosition();
		//_owner.Move("TackleEnemy");
		_owner.Direction();


		//�ǐՏ�Ԃ�
		if (_owner._status == STATUS::CHASE)
		{
			////���G�͈͂���O��Ă��邩
			//if (IsLoseSight())
			//{
			//	_loseSightTime--;
			//}
			//else 
			//{
			//	_loseSightTime = 60;
			//}
			_dif = _owner.GetActorServer().GetPosition("Player") - _owner.GetPosition();
			//���G�P�\���Ԃ�0��؂�����
			//if (_loseSightTime < 0)
			//{
			//	//�{����Ԃɖ߂�
			//	_owner._status = STATUS::SEARCH;
			//	_owner._state->GoToState("Idle");
			//	_loseSightTime = 60;
			//}

			//�^�b�N���������Ԃ�0
			if (_tacklePreTime < 0) {

				_owner._state->GoToState("Tackle");
				//*se �U��(�^�b�N���j
				_owner.GetGame().GetSoundComponent().Play("tackle");

			}
			else {//�^�b�N��������
				_tacklePreTime--;
			}

		}
	}

	bool TackleEnemy::StateRun::IsLoseSight() {

		auto player = _owner.GetActorServer().GetPosition("Player");
		auto range = player - _owner.GetPosition();
		auto length = range.Length();

		//player�Ǝ����̈ʒu�̍������G�͈͂��z���Ă�����
		if (length > _owner.GetR()) {
			return true;
		}
		else {
			return false;
		}
	}

	//bool TackleEnemy::StateRun::IsViewPlayer() {
	//
	//	_owner.GetPosition();
	//
	//}

	//���S
	void TackleEnemy::StateDie::Enter() {
		_owner.GetModelAnime().ChangeAnime("Die");
	}

	void TackleEnemy::StateDie::Update() {
		auto cnt = _owner.GetModelAnime().GetRepeatedCount();
		if (cnt > 0) {
			_owner.SetActorState(ActorState::Dead);
		}
		auto handle = _owner.GetModelAnime().GetHandle();
		auto progress = _owner.GetModelAnime().GetPlayProgress();
		auto num = MV1GetMeshNum(handle);
		for (auto i = 0; i < num; ++i) {
			MV1SetMeshOpacityRate(handle, i, 1.f - progress);
		}
	}

	//�n�b�L���O���̃_���[�W
	void TackleEnemy::StateDamage::Enter() {
		_owner.GetModelAnime().ChangeAnime("Damage", true);

	}

	void TackleEnemy::StateDamage::Update() {

		if (_owner.GetModelAnime().GetRepeatedCount() > 0) {

			_owner._state->PopBack();

		}

	}

	TackleEnemy::StateTackle::StateTackle(TackleEnemy& owner) :StateBase{ owner } {

		_tackleTime = 60;
		_speed = 10.0;
	}

	void TackleEnemy::StateTackle::Enter() {




		_tackleTime = 60;

		//�n�b�L���O����Ă���ꍇ
		if (_owner.GetStatus() == STATUS::ISHUCKED) {

			//�Q�[�W����
			_owner.GetGaugeBase().DownGauge(30);
			_owner.GetGaugeEnemy().DownGauge(30);
			//auto player = _owner.GetActorServer().GetDir("Player");

			auto rot = _owner.GetRotation();

			//z����0�x�Ƃ���
			auto nine = DX_PI * 90.0 / 180.0;

			//�d�l�����6m/s
			auto length = 9900.0;

			//��l���̉�]�����͔��Ό����̂��߃}�C�i�X
			Math::Vector4 move = { std::cos(-rot.GetY() + nine), 0.0, std::sin(-rot.GetY() + nine) };


			//�ڐ��̐�ɖڕW������
			auto forward = move * length;


			_norm = forward.Normalize();



		}
		else {

			//�ǐՒ�
			auto player = _owner.GetActorServer().GetPosition("Player");
			player = { player.GetX(), 0.0, player.GetZ() };
			auto dif = player - _owner.GetPosition();
			auto length = dif.Length_XZ();

			auto rotY = std::atan2(dif.GetX(), dif.GetZ());
			Math::Vector4 rot = { 0.1, rotY, 0.0 };
			_owner.SetRotation(rot);

			//if (length < 600.0) {

			//	auto mat = length / 600.0;
			//	dif = dif / mat;
			//}
			_norm = dif.Normalize();

		}


		_owner.GetModelAnime().ChangeAnime("Attack", true);
	}

	void TackleEnemy::StateTackle::Update() {





		//�O�t���[���̈ʒu��ۑ�
		Math::Vector4 oldPos = _owner.GetPosition();

		_owner._position = _owner.GetPosition() + _norm * _speed;

		//������o����^�b�N���I��
		if (!_owner.CollisionFloor()) {
			_owner._state->GoToState("TackleAfter");
			_owner._position = oldPos;
		}

		////�n�ʂƐG��Ă��邩�ǂ���
		//_owner.CollisionFloor(oldPos, _owner.GetR());

		//��l���̃J�����Ɉړ��ʂ𑗂�
		//_owner.SetHuckedMove(_norm * _speed);


		//}
		//else {
		//
		//	Math::Vector4 zero = { 0.0, 0.0, 0.0 };
		//	//��l���̃J�����Ɉړ��ʂ𑗂�
		//	_owner.SetHuckedMove(zero);
		//}

		////�n�b�L���O����Ă��邩(�ǐՎ��̃^�b�N�����Ȃ�)
		if (_owner.IsHucked()) {

			for (auto i = _owner.GetActorServer().GetActors().begin(); i != _owner.GetActorServer().GetActors().end(); i++) {

				//!< �G�ł͂Ȃ������玟��
				if ((*i)->GetTypeId() != TypeId::Enemy) {

					//�M�~�b�N�ł͂Ȃ������玟��
					if ((*i)->GetTypeId() != TypeId::Gimmick) {

						continue;
					
					}


					//�󂹂�ǂƓ���������
					if (_owner.CollisionWall(**i, _norm)) {
						//���������ǂ����S��ԂɕύX
						(*i)->SetActorState(ActorState::Dead);

						//�X���C�h�A�E�g�t���O���I����
						//Flag::FlagData::SetSlideOut(true);

						//*se �ǂ�����(������)
						_owner.GetGame().GetSoundComponent().Play("broken");

					}


				}//�G������
				else {

					//�n�b�L���O����Ă����玟��	
					if ((*i)->IsHucked()) {
						continue;
					}
					else {

						//����G�l�~�[�̉~�Ǝ�����AABB
						if (_owner._collision->CircleToOrientedAABB(**i, _owner)) {


							(*i)->SetActorState(ActorState::Dead);
							//_owner._state->GoToState("Run");
							//_owner._status = STATUS::CHASE;
						}

					}

				}
			}


		}
		else {

			//�v���C���[���G���Ԓ��ƃv���C���[�_���[�W�t���O���I���̂Ƃ��́A�ʂ��Ȃ�
			if (Flag::FlagData::GetNoDamageFlag() == false && Flag::FlagData::GetDamageFlag() == false) {

				//�n�b�L���O���̖��G���Ԓ��ƃn�b�L���O�_���[�W�t���O���I���̂Ƃ��́A�ʂ��Ȃ�
				if (Flag::FlagData::GetHuckDamageFlag() == false && Flag::FlagData::GetHuckNoDamageFlag() == false) {

					for (auto i = _owner.GetActorServer().GetActors().begin(); i != _owner.GetActorServer().GetActors().end(); i++) {

						//�G�l�~�[�ł͂Ȃ������玟��
						if ((*i)->GetTypeId() != TypeId::Enemy) {

							//�v���C���[�ł͂Ȃ������玟��
							if ((*i)->GetTypeId() != TypeId::Player) {
								continue;
							}
							else {

								if ((*i)->IsHucked()) {

									continue;

								}
								else {

									//�v���C���[���~�œG��AABB�Ƃ̓����蔻��
									if (_owner._collision->CircleToOrientedAABB(**i, _owner)) {

										//*se �_���[�W
										_owner.GetGame().GetSoundComponent().Play("damage");

										//�v���C���[�̃Q�[�W������������
										(*i)->GetGaugeBase().DownGauge(15);
										(*i)->GetGaugePlayer().DownGauge(15);

										//�v���C���[�𖳓G���Ԃɂ���
										//_invincibleTime = true;

										//�v���C���[�̃_���[�W�t���O��ݒ�
										Flag::FlagData::SetDamageFlag(true);

										//�v���C���[���_���[�W��ԂɕύX
										(*i)->GetState().GoToState("Damage");

									}

								}


							}

						}
						else {


							//�n�b�L���O����Ă��邩
							if ((*i)->IsHucked()) {

								//�n�b�L���O����Ă���G���~�œG��AABB�Ƃ̓����蔻��
								if (_owner._collision->CircleToOrientedAABB(**i, _owner)) {

									//�n�b�L���O����Ă���G�̃Q�[�W������������
									(*i)->GetGaugeBase().DownGauge(15);
									(*i)->GetGaugeEnemy().DownGauge(15);

									//�n�b�L���O����Ă���G���_���[�W��ԂɕύX
									(*i)->GetState().PushBack("Damage");

									Flag::FlagData::SetHuckDamageFlag(true);
								}


							}
							else {
								continue;
							}







						}


					}

				}


			}



		}





		auto headPos = _owner.GetModelAnime().GetHeadPos("Character1_Head");
		Flag::FlagData::SetHeadPos(headPos);
		_tackleTime--;

	}

	void TackleEnemy::StateTackleAfter::Enter() {
		_owner.GetModelAnime().ChangeAnime("Walk", true);
		_tackleAfterTime = 120;
	}

	void TackleEnemy::StateTackleAfter::Update() {


		if (_owner.GetGaugeBase().IsGaugeZero(_owner)) {
			_owner._state->GoToState("Die");

			for (auto&& actor : _owner.GetActorServer().GetActors()) {

				if (actor->GetTypeId() != TypeId::Player) {
					continue;
				}
				else {
					actor->SetActorState(ActorState::Active);
				}

			}

		}
		else {

			if (_owner.GetStatus() == STATUS::ISHUCKING) {
				_owner._state->GoToState("IsHucking");
				//_loseSightTime = 60;
			}
			else if (_owner.GetStatus() == STATUS::ISHUCKED) {
				_owner._state->GoToState("IsHucked");
			}

		}

		//_invincibleTime = false;
		////�v���C���[�̖��G���Ԃ����Z�b�g
		//Flag::FlagData::SetNoDamageTime(_invincibleTime);

		if (_tackleAfterTime < 0) {

			_owner._state->GoToState("Run");

		}
		else {
			_tackleAfterTime--;
		}

	}


	void TackleEnemy::StateHucking::Enter()
	{
		_owner.GetModelAnime().ChangeAnime("Die", false);
	}

	void TackleEnemy::StateHucking::Update()
	{
		//// �n�b�L���O���ꂽ���m�F
		//_owner.HitCheckFrom();


		if (_owner.GetStatus() == STATUS::ISHUCKING)
		{
			auto player = _owner.GetActorServer().GetPosition("Player");

			if (player.GetX() - 1 < _owner._position.GetX() && _owner._position.GetX() < player.GetX() + 1 && player.GetZ() - 1 < _owner._position.GetZ() && _owner._position.GetZ() < player.GetZ() + 1/* && player.GetY() - 1 < 200.0 && 200.0 < player.GetY() + 1*/)
			{
				_owner.SetActorState(ActorState::Hucked);
				_owner._state->GoToState("IsHucked");

				auto headPos = _owner.GetModelAnime().GetHeadPos("Character1_Head");
				Flag::FlagData::SetHeadPos(headPos);
			}
		}



	}


	void TackleEnemy::StateHucked::Enter() {
		_owner.GetModelAnime().ChangeAnime("Idle", true);
	}

	void TackleEnemy::StateHucked::Input(AppFrame::Input::InputComponent& input) {

		auto& joypad = input.GetJoypad();
		auto& key = input.GetKeyBoard();
		_lx = 0.0, _ly = 0.0;

		// �E�ړ��ƍ��ړ�
		if (joypad.LHorison() != 0.0)
		{
			_lx = input.GetJoypad().LHorison() / 1000.0;
		}
		else if (key.Button_D() != 0)
		{
			_lx = 1.0;
		}
		else if (key.Button_A() != 0)
		{
			_lx = -1.0;
		}

		// �O�i�ƌ��
		if (input.GetJoypad().LVertical() != 0.0)
		{
			_ly = input.GetJoypad().LVertical() / 1000.0;
		}
		else if (key.Button_W() != 0)
		{
			_ly = 1.0;
		}
		else if (key.Button_S() != 0)
		{
			_ly = -1.0;
		}

		if (input.GetJoypad().Button_RT() || input.GetKeyBoard().Button_Space()) {

			_owner._state->GoToState("Tackle");
		}

	}

	void TackleEnemy::StateHucked::Update() {

		if (_lx != 0.0 || _ly != 0.0) {
			_owner.GetModelAnime().ChangeAnime("Walk", true);//����ꂽ�Ƃ��Ɉړ�����
		}
		else {
			_owner.GetModelAnime().ChangeAnime("Idle", true);
		}

		//// �n�b�L���O���ꂽ���m�F
		//_owner.HitCheckFrom();
		//if (_owner.GetActorState() != ActorState::Hucked)
		//{
		//	_owner._state->GoToState("Run");
		//	_owner._status = STATUS::CHASE;
		//}
		auto headPos = _owner.GetModelAnime().GetHeadPos("Character1_Head");
		Flag::FlagData::SetHeadPos(headPos);

		if (Flag::FlagData::GetHuckDamageFlag()) {

			//�_���[�W�t���O���I�t��
			Flag::FlagData::SetHuckDamageFlag(false);

			//���G�t���O���I����
			Flag::FlagData::SetHuckNoDamageFlag(true);

			_huckNoDamageTime = 120;

		}

		_huckNoDamageTime--;

		//���G���Ԃ��I������猳�ɖ߂�
		if (_huckNoDamageTime < 0 && Flag::FlagData::GetHuckNoDamageFlag()) {
			Flag::FlagData::SetHuckNoDamageFlag(false);
		}


		//�ړ����Ƀt���A�̕ǂƂ̔�������
		Math::Vector4 oldPos = _owner.GetPosition();


		_owner.HuckedMove(_lx, _ly);

		//�M�~�b�N�ƐG��Ă��邩�G��Ă�����߂�
		//_owner.CollisionGimmick();

		////�n�ʂƐG��Ă��邩�ǂ���
		_owner.CollisionFloor(oldPos, _owner.GetR());

		//���[�v���ォ
		if (!_warping) {

			auto dxPos = _owner.WarpFloor(_owner);

			//�t�F�[�h�p�ɕۑ�
			_fadePos = { dxPos.x, dxPos.y, dxPos.z };

			//���݈ʒu�̃X�e�[�W�ԍ��̃��[�v�i�r���b�V���ɓ��������ꍇ
			if (dxPos.x != 0.0f && dxPos.z != 0.0f) {

				Flag::FlagData::SetFadeOutFlag(true);
				//Math::Vector4 pos = { dxPos.x, dxPos.y, dxPos.z };

				//_position = pos;
				//_owner._position = _fadePos;

				//_camera->SetRefleshPosition(_position);
				//_camera->SetRefleshTarget(_position);

				if (!_warping) {

					_warping = true;
					_waitFrame = 5;

					//_fadeflag = true;

				}
				//else {
				//	_warping = false;
				//}

				//�����Ƀt�F�[�h�C������

			}


		}
		else {

			if (_waitFrame == 4) {
				_owner._position = _fadePos;
			}

			if (_waitFrame == 0) {
				Flag::FlagData::SetFadeInFlag(true);
			}

			if (!_owner.WarpingFloor() && _waitFrame < 0) {

				//_position = _fadePos;
				_warping = false;

			}


		}

		_waitFrame--;



		//�Q�[�W��0���ǂ���
		if (_owner.GetGaugeBase().IsGaugeZero(_owner)) {

			_owner._state->GoToState("Die");
			_owner._status = STATUS::DYING;
			//*se �j�󂳂��
			//_owner.GetGame().GetSoundComponent().Play("push");


			Flag::FlagData::SetHuckDamageFlag(false);
			Flag::FlagData::SetHuckNoDamageFlag(false);

			for (auto&& actor : _owner.GetActorServer().GetActors()) {

				if (actor->GetTypeId() != TypeId::Player) {
					continue;
				}
				else {

					actor->SetActorState(ActorState::Active);
				}

			}

		}

		//�n�b�L���O����Ă��邩�ǂ���
		if (!_owner.IsHucked())
		{
			_owner._state->GoToState("Die");
			_owner._status = STATUS::DYING;
		}


	}
}


