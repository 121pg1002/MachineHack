///
/// @file    Enemy.cpp
/// @brief  �G�l�~�[
/// @date    2021/11/26
/// @author yamawaki kota
/// @copyright (C) Amusement Media Academy All rights Resved.
///
#include "AppFrame.h"
#include "TackleEnemy.h"
#include "../Actor/ActorServer.h"
#include "../Model/ModelAnimComponent.h"

#include "../Collision/CollisionComponent.h"


#include <cmath>
#include <numbers>
#include <random>
#include "EnemyParameter.h"
namespace Enemy {
	TackleEnemy::TackleEnemy(Game& game) : EnemyBase{ game } {

		_r = 50;
		_minXZ = { -10, -20 };
		_maxXZ = { 10, 20 };
		_lmin = { 0.0, -100.0, 0.0 };
		_lmax = { 0.0, 100.0, 0.0 };
		_status = STATUS::WAIT;
		_searchRange = 30.0;
	}

	//void LoadJson(const std::string& filepath) 
	//{
	//	auto eParam = std::unique_ptr<EnemyParameter>();
	//	eParam->LoadEnemyParam(filepath);
	//}

	void TackleEnemy::Update() {


		if (GetActorState() == ActorState::Hucking)
		{
			_status = STATUS::ISHUCKING;
		}
		else if (GetActorState() == ActorState::Hucked)
		{
			_status = STATUS::ISHUCKED;
		}
		else if (GetActorState() == ActorState::Active)
		{
			if (_status != STATUS::CHASE)
			{
				_status = STATUS::SEARCH;
			}

			//if (_status != STATUS::WAIT) 
			//{
			 // _status = STATUS::WALK;
			//}
		}


		Move();


		_state->Update();



		//// ���[���h�s��̌v�Z
		ComputeWorldTransform();



		// ���f���̍X�V
		_model->Update();

	}

	void TackleEnemy::Draw() {
		// ���̃g�Q�ׂ̈̃A���t�@�e�X�g�ݒ�
		MV1SetMaterialDrawAlphaTest(_model->GetHandle(), 3, TRUE, DX_CMP_LESS, 200);
#ifdef _DEBUG
		//auto pos = _position;
		//pos.y += 40;
		//DrawSphere3D(pos, 50, 16, GetColor(255, 0, 0), GetColor(0, 0, 0), TRUE);
		_model->Draw(*this, _isHit, _searchRange);
#endif
		_state->Draw();
	}

	void TackleEnemy::Move() {
		//// �v���C���[�Ɍ������P�ʃx�N�g��
		//auto forward = GetForward();
		//// �v���C���[�Ɍ������ړ��ʃx�N�g��
		//auto delta = forward * _forwardSpeed;
		//// �v���C���[�Ɍ������Ĉړ�
		//_position = _position + delta;

		_oldPos = _position;
		if (_status != STATUS::SEARCH) {

			if (_status != STATUS::ISHUCKED && _status != STATUS::ISHUCKING) {
				auto player = GetActorServer().GetPosition("Player");
				// �v���C���[�Ɍ������x�N�g��
				auto forward = player - _position;
				// �v���C���[�Ɍ������P�ʃx�N�g��
				if (math::Vector4 v{ 0.0, 0.0, 0.0 }; forward.GetX() != v.GetX() && forward.GetZ() != v.GetZ())
				{
					forward = forward.Normalize();
				}
				// �v���C���[�Ɍ������ړ��ʃx�N�g��
				auto delta = forward * _forwardSpeed;
				// �v���C���[�Ɍ������Ĉړ�
				_position = _position + delta;

				// Y���̉�]�p�x�����߂遦���v���z��x
				auto _rot_y = std::atan2(forward.GetX(), forward.GetZ());
				math::Vector4 _rot = { 0.0, _rot_y, 0.0 };
				SetRotation(_rot);

				// �A�N�^�[�T�[�o�[�Ɉʒu��ʒm
				std::pair<math::Vector4, math::Vector4> pos_dir = { _position, _rot };
				GetActorServer().Register("TackleEnemy", pos_dir);

				// ���[���h�s��̌v�Z
				//ComputeWorldTransform();
			}
			else if (_status != STATUS::ISHUCKING) {
				auto playermove = GetActorServer().GetPosition("Player");
				_position = playermove;
				// Y���̉�]�p�x�����߂遦���v���z��x
				auto dir = GetActorServer().GetDir("Player");
				auto _rot_y = std::atan2(dir.GetX(), dir.GetZ());
				math::Vector4 _rot = { 0.0, _rot_y, 0.0 };
				SetRotation(_rot);
				//LockOn();

				//ComputeWorldTransform();
			}



		}
		else
		{

			if (_numberTimes < 100)
			{
				math::Vector4 move = { 2.0, 0.0, 0.0 };
				_position = _position + move;
				// Y���̉�]�p�x�����߂遦���v���z��x
				auto rotY = std::atan2(move.GetX(), move.GetZ());
				math::Vector4 rot = { 0.0, rotY, 0.0 };
				SetRotation(rot);
			}
			else
			{
				math::Vector4 move = { -2.0, 0.0, 0.0 };
				_position = _position + move;
				// Y���̉�]�p�x�����߂遦���v���z��x
				auto rotY = std::atan2(move.GetX(), move.GetZ());
				math::Vector4 rot = { 0.0, rotY, 0.0 };
				SetRotation(rot);
			}

			if (_numberTimes > 200)
			{
				_numberTimes = 0;
			}
			else
			{
				_numberTimes++;
			}


		}

	}

	void TackleEnemy::LockOn() {
		auto player = GetActorServer().GetPosition("Player");
		// �v���C���[�Ɍ������x�N�g��
		auto forward = player - _position;
		// �v���C���[�Ɍ������P�ʃx�N�g��
		forward = forward.Normalize();
		// Y���̉�]�p�x�����߂遦���v���z��x
		auto _rot_y = std::atan2(forward.GetX(), forward.GetZ());
		math::Vector4 _rot = { 0.0, _rot_y, 0.0 };
		SetRotation(_rot);
	}

	void TackleEnemy::HitCheckFrom() {
		//auto& report = _collision->GetReport();
		//if (report.id == CollisionComponent::ReportId::HitFromPlayer) {
		//	_state->GoToState("Die");
		//	GetGame().GetSoundComponent().Play("damage");
		//}
		//else if (report.id == CollisionComponent::ReportId::HuckedFromPlayer) 
		//{
		//	_state->GoToState("Idle");
		//}
	}


	void TackleEnemy::StateBase::Draw() {
		_owner._model->Draw();
	}

	// �ҋ@
	void TackleEnemy::StateFall::Enter() {
		_owner._model->ChangeAnime("Fall", true);
	}

	void TackleEnemy::StateFall::Update() {

		//_owner.LockOn();
		if (_owner._position.GetY() > 0)
		{
			auto posY = _owner._position.GetY() - 5;
			//math::Vector4 _pos = { 0.0, _pos_y, 0.0 };
			_owner._position = { _owner.GetPosition().GetX(), posY, _owner.GetPosition().GetZ() };
		}
		else
		{
			math::Vector4 _pos = { _owner._position.GetX(), 0.0, _owner._position.GetZ() };
			_owner._position = _pos;
			_owner._state->GoToState("Idle");
		}
	}

	//�ҋ@
	void TackleEnemy::StateIdle::Enter() {
		_owner._model->ChangeAnime("Fall", true);
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

				if (_owner._collision->CircleToFan(_owner, **i)) {
					_owner._state->GoToState("Run");
					_owner._status = STATUS::CHASE;
				}

			}
		}
	}

	// ����
	void TackleEnemy::StateRun::Enter() {
		_owner._model->ChangeAnime("RunAniVor", true);
	}

	void TackleEnemy::StateRun::Update() {
		//auto player = _owner.GetActorServer().GetPosition("Player");
		//// �v���C���[�Ɍ������x�N�g��
		//auto forward = player  - _owner._position;
		//auto distSq = std::pow(forward.Length(), 2.0);

		if (_owner.GetStatus() == STATUS::ISHUCKING)
		{
			_owner._state->GoToState("IsHucking");
			_loseSightTime = 60;
		}
		//if (distSq < 130 * 130) {
		//	_owner._state->PushBack("Attack");
		//	return;
		//}
		/*_owner.LockOn();*/
		_owner.Move();

		//�ǐՏ�Ԃ�
		if (_owner._status == STATUS::CHASE)
		{
			//���G�͈͂���O��Ă��邩
			if (IsLoseSight())
			{
				_loseSightTime--;
			}
			else
			{
				_loseSightTime = 60;
			}

			//���G�P�\���Ԃ�0��؂�����
			if (_loseSightTime < 0)
			{
				//�{����Ԃɖ߂�
				_owner._status = STATUS::SEARCH;
				_owner._state->GoToState("Idle");
				_loseSightTime = 60;
			}
		}
		/*_owner.HitCheckFrom();*/
	}

	bool TackleEnemy::StateRun::IsLoseSight() {

		auto player = _owner.GetActorServer().GetPosition("Player");
		auto range = player - _owner.GetPosition();
		auto length = range.Length();

		//player�Ǝ����̈ʒu�̍������G�͈͂��z���Ă�����
		if (length > _owner.Get_r()) {
			return true;
		}
		else {
			return false;
		}
	}

	//���S
	void TackleEnemy::StateDie::Enter() {
		_owner._model->ChangeAnime("Die");
	}

	void TackleEnemy::StateDie::Update() {
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

	////�U��
	//void Enemy::StateAttack::Enter() {
	//	_owner._model->ChangeAnime("Attack");
	//}
	//void Enemy::StateAttack::Update() {
	//	// �U�����󂯂����m�F
	//	_owner.HitCheckFrom();
	//
	//	// �U�����[�V�����̏I���m�F
	//	auto cnt = _owner._model->GetRepeatedCount();
	//	if (cnt > 0) {
	//		_owner._state->PopBack();
	//		return;
	//	}
	//	// �U�����[�V������15�`20�̊ԁA�U�����肠��
	//	auto playTime = _owner._model->GetPlayTime();
	//	if (playTime < 15.f || playTime > 20.f) {
	//		//�@�U������Ȃ�
	//		return;
	//	}
	//
	//	_owner._collision->PlayerFromEnemy();
	//
	//}
	//void Enemy::StateAttack::Draw() {
	//	_owner._model->Draw();
	//#ifdef _DEBUG
	//	//// �U�����[�V������15�`20�̊ԁA�U�����肠��
	//	auto playTime = _owner._model->GetPlayTime();
	//	if (playTime < 15.f || playTime > 20.f) {
	//	  //�@�U������Ȃ�
	//	  return;
	//	}
	//	auto handle = _owner._model->GetHandle();
	//	auto mat = MV1GetFrameLocalWorldMatrix(handle, 28);
	//	auto pos = VTransform({0, 0, 0}, mat);
	//	DrawSphere3D(pos, 20, 16, GetColor(255, 0, 0), GetColor(0, 0, 0), TRUE);
	//
	//
	//
	//#endif
	//}

	void TackleEnemy::StateHucking::Enter()
	{
		_owner._model->ChangeAnime("Attack", true);
	}

	void TackleEnemy::StateHucking::Update()
	{
		//// �n�b�L���O���ꂽ���m�F
		//_owner.HitCheckFrom();


		if (_owner.GetStatus() == STATUS::ISHUCKING)
		{
			auto player = _owner.GetActorServer().GetPosition("Player");
			if (player.GetX() - 1 < _owner._position.GetX() && _owner._position.GetX() < player.GetX() + 1 && player.GetZ() - 1 < _owner._position.GetZ() && _owner._position.GetZ() < player.GetZ() + 1)
			{
				_owner.SetActorState(ActorState::Hucked);
				_owner._state->GoToState("IsHucked");
			}
		}



	}


	void TackleEnemy::StateHucked::Enter()
	{
		_owner._model->ChangeAnime("Attack");
	}

	void TackleEnemy::StateHucked::Update()
	{
		//// �n�b�L���O���ꂽ���m�F
		//_owner.HitCheckFrom();
		if (_owner.GetActorState() != ActorState::Hucked)
		{
			_owner._state->GoToState("Run");
			_owner._status = STATUS::CHASE;
		}
	}
}
