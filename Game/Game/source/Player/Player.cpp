/*****************************************************************//**
 * @file   Player.cpp
 * @brief  �v���C���[�N���X
 * 
 * @author hikaru Goto
 * @date   December 2021
 *********************************************************************/
#include "AppFrame.h"
#include "Player.h"
#include "../Enemy/EnemyBase.h"
#include "../Actor/ActorServer.h"
#include "../Camera/CameraComponent.h"
#include "../Model/ModelAnimComponent.h"
#include "../Collision/CollisionComponent.h"
#include "../Enemy/TackleEnemy.h"
#include "../Gauge/GaugeBase.h"
#include "../UI/UIComponent.h"


//#include <numbers>
namespace {

	double measuredDistance = 500.0;
}

namespace MachineHuck::Player {
	//�R���X�g���N�^
	Player::Player(AppFrame::Game& game) : Actor{ game } {
		_r = 150.0;
		_minXZ = { -100, -100 };
		_maxXZ = { 100, 100 };
		_isHit = false;
		_searchRange = 60.0;
		//_huckingRange = 30.0;
		_gaugeBase->Init();
	}

	//����
	void Player::Input(AppFrame::Input::InputComponent& input) {
		_camera->Input(input);  // �J�����̓���

		auto& joypad = input.GetJoypad();
		auto& key = input.GetKeyBoard();
		lx = 0.0, ly = 0.0;


		if (_actorState != ActorState::Hucking && _actorState != ActorState::Hucked){   
			// �E�ړ��ƍ��ړ�
			if (joypad.LHorison() != 0.0){
				lx = input.GetJoypad().LHorison() / 1000.0;
			}
			else if (key.Button_D() != 0){
				lx = 1.0;
			}
			else if (key.Button_A() != 0){
				lx = -1.0;
			}

			// �O�i�ƌ��
			if (input.GetJoypad().LVertical() != 0.0){
				ly = input.GetJoypad().LVertical() / 1000.0;
			}
			else if (key.Button_W() != 0){
				ly = 1.0;
			}
			else if (key.Button_S() != 0){
				ly = -1.0;
			}
		}

		//***************//////////�������ō�����n�b�N�p
		//�ł������炭�A�u�����h���邩��v�ɂȂ�
		if (_huckCount <= 0){

			if (joypad.Button_RT()){
				//Hucking��Hucked�Ŗ���������
				if (_actorState != ActorState::Hucking && _actorState != ActorState::Hucked){
					_actorState= ActorState::Hucking;
					_huckCount = 100;
					lx = 0.0, ly = 0.0;
				}

				//if (_actorState== ActorState::Hucked)//Hucked���Ȃ�
				//{
				//	_actorState= ActorState::Active;
				//	_huckCount = 200;
				//}
			}
			else if (_huckCount == 0 && _actorState != ActorState::Hucked){
				_actorState= ActorState::Active;
			}

			if (joypad.Button_A() && _actorState == ActorState::Hucked) {
					_actorState= ActorState::Active;
					_huckCount = 200;
			}

		}

		
		/////********************//////////////////////////

	  //if (_key.Button_C() != 0) 
	  //{
	  //    ly = -1.0;
	  //}
	  //else if (_key.Button_E() != 0)
	  //{
		 // ly = 1.0;
	  //}
		_state->Input(input);
	}

	void Player::Update() {
		//�����Ȃ��Ƃ��̏����Ɏg�p
		//auto oldMove = _move;


		Math::Vector4 oldPos = _position;

		Move();

		//// �X�e�[�^�X�ɍ��킹�ăA�j���[�V�����̃A�^�b�`
		//switch (_status) {
		//case ActorState::Active:
		   // _model->ChangeAnime("Idle");
		   // break;
		//case ActorState::WALK:
		   // _model->ChangeAnime("Run");
		   // break;

		//case ActorState::Hucking:
		   // _model->ChangeAnime("Attack");

		//case ActorState::Hucked:
		   // _model->ChangeAnime("Idle");
		//}


		// ���f���̍X�V
		_model->Update();

		// �J�����̍X�V
		//_camera->SetTarget(_position, _move);
		//if (_move.GetX() != oldMove.GetX() && _move.GetZ() != oldMove.GetZ()) {
		//
		//	Math::Vector4 cameraDif = { 0.0, 500.0,  -200.0 };
		//	_camera->SetPosition(_position + cameraDif);
		//}

		  // �A�N�^�[�T�[�o�[�Ɉʒu��ʒm
		std::pair<Math::Vector4, Math::Vector4> pos_dir = { _position, _dir };
		GetActorServer().Register("Player", pos_dir);

		_state->Update();
		
		//if (_actorState!= ActorState::Hucked) {

			

		////�n�ʂ̃i�r���b�V���ɐG��Ă��邩�ǂ���
		//if (!CollisionFloor(oldPos)) {

		//	//�i�r���b�V������o�Ă��܂��ꍇ
		//	Math::Vector4 zero = { 0.0, 0.0, 0.0 };
		//	_camera->Update(zero);
		//}
		//else {

		//	//�i�r���b�V���Ɏ��܂��Ă���ꍇ
			_camera->Update(_move);
		//}
		
		    //�G�l���M�[�c�ʃQ�[�W�̐ݒ�
			GetGame().GetUiComponent().UpdatePlayerHp(_gaugeBase->GetGauge(), _gaugeBase->GetGaugeMax());

		for (auto i = GetActorServer().GetActors().begin(); i != GetActorServer().GetActors().end(); i++){
			auto targetPos = (*i)->GetPosition();
			auto dif = _position - targetPos;

			//���苗�����ɂ���ꍇ
			if (dif.Length_XZ() < measuredDistance) {

				//!< �G�l�~�[�ł͂Ȃ������玟��
				if ((*i)->GetTypeId() != TypeId::Enemy){
					//!< �M�~�b�N�ł͂Ȃ������玟��
					if ((*i)->GetTypeId() != TypeId::Gimmick) {
						continue;
					}
					else {

						//�����ƃM�~�b�N
						if (_collision->CircleToCircle(*this, **i)) {

							if (_noDamageTime < 0) {
								_gaugeBase->DownGauge(10);
								_noDamageTime = 60;
							}
						}
						else {
							_noDamageTime = 60;
						}

					}
				}
				else{

					//Circle(�v���C���[)�Ɛ�`(�G�l�~�[)�̓����蔻��𒲂ׂ�
					if (_collision->CircleToFan(*this, **i))	{
						_isHit = true;
					}
					else{
						_isHit = false;
					}

				}
			
			
			}




		}

		//if (_actorState != ActorState::Hucking) {
			_huckCount--;
		//}
	

		if (_huckCount < 0) {

			if (_actorState == ActorState::Hucking) {
			
				_actorState = ActorState::Active;
			
			}
		

		}

	}

	void Player::Draw() {
		_state->Draw();

#ifdef _DEBUG
		_model->Draw(*this, _isHit, _searchRange, true);
		_camera->Draw(_isHit);
		_gaugeBase->Draw();

		auto posXStr = std::to_string(_position.GetX());
		auto posYStr = std::to_string(_position.GetY());
		auto posZStr = std::to_string(_position.GetZ());
		std::string posStr = posXStr + "," + posYStr + "," + posZStr;
		auto pos = _position;
		auto v = ConvWorldPosToScreenPos(ToDX(pos));
		DrawString(static_cast<int>(v.x), static_cast<int>(v.y), posStr.c_str(), GetColor(255, 0, 0));
#endif
	}

	void Player::ComputeWorldTransform() {
		auto world = MGetScale(ToDX(_scale));
		world = MMult(world, MGetRotZ(static_cast<float>(_rotation.GetZ())));
		world = MMult(world, MGetRotX(static_cast<float>(_rotation.GetX())));
		world = MMult(world, MGetRotY(static_cast<float>(_rotation.GetY()) + DX_PI_F));
		_worldTransform = MMult(world, MGetTranslate(ToDX(_position)));
	}

	///// �ړ�
	void Player::Move() {

		_move = { 0.0, 0.0, 0.0 };

		_oldPos = _position;
		//�������̌X���Əc�����̌X���̑傫��
		double length = sqrt(lx * lx + ly * ly);

		if (length < _analogMin) {
			// ���͂������������瓮���Ȃ��������Ƃɂ���
			length = 0.0;
			_hp++;
		}
		else {
			length = 5.0;
			_hp -= 0.1f;//�G�l���M�[����
		}
		if (_hp < 0) {
			_hp = 0;
		}
		if (_hp > 100) {
			_hp = 100;
		}

		//�������Əc�����̊p�x
		double rad = atan2(ly, lx);

		//x�������̈ړ���
		auto moveX = cos(rad) * length;

		//z�������̈ړ���
		auto moveZ = sin(rad) * length;

		_move = { moveX, 0.0, moveZ };

		// �ړ�
		_position = _position + _move;
		
		// ���[���h�s��̍X�V
		ComputeWorldTransform();

		if (_move.Length() > 0.0){
			_dir = _move;
		}

		//��l���̊p�x���擾
		//auto angle = GetRotation();

		//y����]���o��
		auto yRot = atan2(_dir.GetX(), _dir.GetZ());
		Math::Vector4 rot = { 0.0, yRot, 0.0 };
		////z����0�x�Ƃ���
		//auto nine = DX_PI / 180.0 * 90.0;
		//_y_rot += 90.0;
		//angle.Set(0.0, _y_rot, 0.0);
		//�p�x���X�V
		SetRotation(rot);

	}

	/// �G����̍U�����m�F
	//void Player::HitCheckFromEnemy() {
	//	//auto& report = _collision->GetReport();
	//	//if (report.id == CollisionComponent::ReportId::HitFromEnemy) {
	//	//	_state->GoToState("KnockBack");
	//	//	_game.GetSoundComponent().Play("damage");

	//	//	auto backward = _position - report.position;
	//	//	_backDelta = backward.Normalize() * 20;
	//	//}
	//}

	void Player::StateBase::Draw() {
		_owner._model->Draw();
	}
	/// �ҋ@
	void Player::StateIdle::Enter() {
		_owner._model->ChangeAnime("Idle", true);
		//_actorState= ActorState::Active;
	}

	void Player::StateIdle::Input(AppFrame::Input::InputComponent& input) {

		//if (input.GetJoypad().Button_B()) {
		//	_owner._state->PushBack("Attack");
		//}



		if (input.GetJoypad().Button_RT()){
			_owner._state->PushBack("Hucking");
		}
		else if (Math::Vector4 v{ 0.0, 0.0, 0.0 }; v.GetX() != _owner.GetMove().GetX() || v.GetZ() != _owner.GetMove().GetZ()) {
			_owner._state->PushBack("Run");
		}
	}


	void Player::StateIdle::Update() {
		//_owner.HitCheckFromEnemy();
		//if (_owner.GetGaugeBase().GetGauge() < 0) {
		//	_owner._state->GoToState("Die");
		//}
		
	}

	/// ����
	void Player::StateRun::Enter() {
		_owner._model->ChangeAnime("Run", true);
		/*_actorState= ActorState::WALK;*/
	}


	void Player::StateRun::Input(AppFrame::Input::InputComponent& input) {

		//if (input.GetJoypad().Button_B()) {
		//	_owner._state->PushBack("Attack");
		//	return;
		//}
		if (input.GetJoypad().Button_RT()) {
			_owner._state->PopBack();
			_owner._state->PushBack("Hucking");
			return;
		}
		else if (Math::Vector4 v{ 0.0, 0.0, 0.0 }; v.GetX() != _owner.GetMove().GetX() || v.GetZ() != _owner.GetMove().GetZ()) {
			return;
		}
		_owner._state->PopBack();
	}



	void Player::StateRun::Update() {
		//_owner.HitCheckFromEnemy();

		if (_owner.GetGaugeBase().GetGauge() < 0) {

			_owner._state->GoToState("Die");
		}
		else {
		
			_owner.GetGaugeBase().Update(_owner);
		}

		

	}

	/// �U��
	void Player::StateAttack::Enter() {
		//_owner._model->ChangeAnime("Attack");
		//_attackcount = 30;
	}

	//void Player::StateAttack::Input(InputComponent& input) {
	//
	//	if (_attackcount < 0) 
	//	{
	//		_owner._state->PopBack();
	//	}
	//	else 
	//	{
	//		_attackcount--;
	//	}
	//}

	void Player::StateAttack::Update() {
		//auto cnt = _owner._model->GetRepeatedCount();
		//if (cnt > 0) {
		//	_owner._state->PopBack();
		//	return;
		//}
		//auto playTime = _owner._model->GetPlayTime();
		//if (playTime < 3.5f || playTime > 20.f) {
		//	_owner.HitCheckFromEnemy();
		//	return;
		//}
		//_owner._collision->EnemyFromPlayer();
	}
	void Player::StateAttack::Draw() {
		//	_owner._model->Draw();
		//#ifdef _DEBUG
		//	auto playTime = _owner._model->GetPlayTime();
		//	if (playTime < 3.5f || playTime > 20.f) {
		//	  return;
		//	}
		//
		//	auto handle = _owner._model->GetHandle();
		//	auto mat = MV1GetFrameLocalWorldMatrix(handle, 28);
		//	auto pos = VTransform({0, 0, 0}, mat);
		//	DrawSphere3D(pos, 20, 16, GetColor(255, 0, 0), GetColor(0, 0, 0), TRUE);
		//
		//#endif
	}

	///// �m�b�N�o�b�N
	//void Player::StateKnockBack::Enter() {
	//	freezeTime = 15;
	//}
	//void Player::StateKnockBack::Update() {
	//	if (freezeTime > 0) {
	//		--freezeTime;
	//		_owner._position = _owner._position + _owner._backDelta;
	//	}
	//	else {
	//		_owner._state->GoToState("Idle");
	//		_owner.GetCollision().SetReport({ CollisionComponent::ReportId::None, _owner.GetPosition() });
	//	}
	//}

	/// �n�b�L���O��
	void Player::StateHucking::Enter() {

		_owner._model->ChangeAnime("Attack");
		/*_actorState= ActorState::Hucking;*/
	}


	void Player::StateHucking::Update() {

		if (_owner.GetActorState() != ActorState::Hucking) {
			_owner._state->PopBack();
			return;
		}
		else
		{
			for (auto i = _owner.GetActorServer().GetActors().begin(); i != _owner.GetActorServer().GetActors().end(); i++)
			{
				//!< �v���C���[�ł͂Ȃ������玟��
				if ((*i)->GetTypeId() != TypeId::Enemy)
				{
					continue;
				}
				else
				{   //�~�Ɖ~�̓����蔻��𒲂ׂ�

					/// //////////////�~�Ɖ~�̔�����s�������Ȃ炱�������N��AABBToAABB�Ȃ牺�����N��

					//if (GetCollision().CircleToCircle(_owner, **i))
					//{
					   // (*i)->SetPosition((*i)->GetOld());

					   // auto _dif_vec = (*i)->GetPosition() - _position;
					   // auto _length = _dif_vec.Length_XZ();
					   // if (_length < GetR() + (*i)->GetR())
					   // {
						  //   auto _pos = (*i)->GetPosition() + _move;
						  //   (*i)->SetPosition(_pos);
					   // }
					//}

					//Circle��AABB�̓����蔻��𒲂ׂ�
					//�G�̒��S�������Ă��邩�ǂ���
					if (_owner._collision->CircleToFan(_owner, **i, true)) {

						////�����̒��S���G�̃n�b�L���O�͈͂ɓ����Ă��邩�ǂ���
						if (_owner._collision->CircleToFan(**i, _owner, false)) {

							if (_owner._actorState == ActorState::Hucking)
							{

								(*i)->SetActorState(ActorState::Hucking);

								auto enem_pos = (*i)->GetPosition();

								if (enem_pos.GetX() - 1 < _owner._position.GetX() && _owner._position.GetX() < enem_pos.GetX() + 1 && enem_pos.GetZ() - 1 < _owner._position.GetZ() && _owner._position.GetZ() < enem_pos.GetZ() + 1/* && _owner._position.GetY() - 1 < 200.0 && 200.0 < _owner._position.GetY() + 1*/) {
									_owner._actorState = ActorState::Hucked;
									_owner._state->GoToState("Hucked");
								}
								else {

									//_dif = enem_pos - _owner._position;

									////����y���W
									//_length = _dif.Normalize();



									// �ړ�
									//_owner._position = _owner._position + _length;

									if (_owner.GetHuckCount() < 2) {
										_owner._position = enem_pos;
									}

								}






								//auto enemy = GetActorServer().GetPosition("Tackle");
								//Math::Vector4 v = { 1.0, 0.0, 0.0 };
								//_position = enemy + v;
							}
							_owner._isHit = true;
							(*i)->SetIsHit(true);

						}
						else {

							_owner._isHit = false;
							(*i)->SetIsHit(false);

						}
						//if (_actorState!= ActorState::Hucking && _actorState!= ActorState::Hucked)



					}
					else{
						_owner._isHit = false;
						(*i)->SetIsHit(false);

					}

				}

			}

		}



	
		//if (freezeTime > 0) {
		//	--freezeTime;
		//}
		//else {
		//	_owner._state->GoToState("Idle");
		//	_owner.GetCollision().SetReport({ CollisionComponent::ReportId::None, _owner.GetPosition() });
		//}
	}


	/// �n�b�L���O
	void Player::StateHucked::Enter() {

		_owner._model->ChangeAnime("Idle");
		/*_actorState= ActorState::Hucking;*/
	}

	void Player::StateHucked::Input(AppFrame::Input::InputComponent& input) {
	
		//if (input.GetJoypad().Button_RT()) {
		//
		//	for (auto i = _owner.GetActorServer().GetActors().begin(); i != _owner.GetActorServer().GetActors().end(); i++)
		//	{
		//		if ((*i)->GetActorState() != ActorState::Hucked)
		//		{
		//			continue;
		//		}
		//		else
		//		{
		//		    _owner._position = (*i)->GetPosition();
		//			//_owner._state->GoToState("Idle");
		//		}
		//	}
		//}
	}

	/// �n�b�L���O
	void Player::StateHucked::Update() {

		for (auto i = _owner.GetActorServer().GetActors().begin(); i != _owner.GetActorServer().GetActors().end(); i++){

		//	if (!(*i)->IsDead()) {
			if ((*i)->GetTypeId() != TypeId::Player) {
			
				if (!(*i)->IsHucked()) {

					if ((*i)->GetGaugeBase().GetGauge() > 0) {
						continue;
					}
					else {
						_owner.SetActorState(ActorState::Active);
						_owner._state->GoToState("Idle");
					}


				}
				else {
					//�n�b�L���O�����ΏۂɒǏ]
					Math::Vector4 difY = { 0.0, 190.0, 0.0 };
					_owner._position = (*i)->GetPosition() + difY;
					_owner._rotation = (*i)->GetRotation();
					_owner._move = (*i)->GetHuckedMove();
				}
			
			}
			else {
			
				continue;
			}
		    //	}
			//else {

			//	_owner._actorState= ActorState::Active;
			//	_owner._state->GoToState("Idle");
			//}
		}

		//�v���C���[��������������ꍇ
		if (_owner._actorState!= ActorState::Hucked){
			
			for (auto i = _owner.GetActorServer().GetActors().begin(); i != _owner.GetActorServer().GetActors().end(); i++){
					//�n�b�L���O����Ă��邩
					if (!(*i)->IsHucked()){
						continue;
					}
					else {

						auto enemyGauge = (*i)->GetGaugeBase().GetGauge();

						if (enemyGauge > 0) {

							//�G�l�~�[�̃Q�[�W�ʂ����Z
							_owner.GetGaugeBase().PlusGauge(enemyGauge);
						}
						_owner._position = { _owner.GetPosition().GetX(), 0.0, _owner.GetPosition().GetZ() };
						(*i)->SetActorState(ActorState::Active);
						_owner._state->GoToState("Idle");

					}
				
				

					

				

			}

		}
	}

	void Player::StateDie::Enter() {

		_owner._model->ChangeAnime("Die");
	}

	void Player::StateDie::Update() {
		auto cnt = _owner._model->GetRepeatedCount();
		if (cnt > 0) {
			_owner.SetActorState(ActorState::Dead);
		}
		auto handle = _owner._model->GetHandle();
		auto progress = _owner._model->GetPlayProgress();
		auto num = MV1GetMeshNum(handle);
		for (auto i = 0; i < num; ++i) {
			MV1SetMeshOpacityRate(handle, i, 1.f - progress);
		}


	}
}


