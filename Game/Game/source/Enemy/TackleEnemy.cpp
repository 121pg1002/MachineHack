///
/// @file    Enemy.cpp
/// @brief  エネミー
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

//namespace Math = AppFrame::Math;

namespace MachineHuck::Enemy {
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
	}

	void TackleEnemy::LoadJson(const std::string& filepath)
	{
		auto eParam = std::make_unique<EnemyParameter>();
		eParam->LoadEnemyParam(filepath);

		//2つめの値がレベル
		_r = eParam->GetEnemyParam("r", 0);
		//_huckR = eParam->GetEnemyParam("r", 1);
		_huckR = 100.0;

		_searchRange = eParam->GetEnemyParam("searchrange", 1);
		_huckingRange = eParam->GetEnemyParam("searchrange", 0);////////←とりあえず、仮

	}

	void TackleEnemy::Update() {

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
			Move();
		}


		_state->Update();



		//// ワールド行列の計算
		ComputeWorldTransform();



		// モデルの更新
		_model->Update();

	}

	void TackleEnemy::Draw() {
		// 足のトゲの為のアルファテスト設定
		MV1SetMaterialDrawAlphaTest(_model->GetHandle(), 3, TRUE, DX_CMP_LESS, 200);
#ifdef _DEBUG
		//auto pos = _position;
		//pos.y += 40;
		//DrawSphere3D(pos, 50, 16, GetColor(255, 0, 0), GetColor(0, 0, 0), TRUE);
		_model->Draw(*this, _isHit, _searchRange, true);
		_model->Draw(*this, _isHit, _huckingRange, false);
		_model->Draw(*this, GetActorServer().GetPosition("Player"));
#endif
		_state->Draw();
	}

	void TackleEnemy::Move() {
		//// プレイヤーに向かう単位ベクトル
		//auto forward = GetForward();
		//// プレイヤーに向かう移動量ベクトル
		//auto delta = forward * _forwardSpeed;
		//// プレイヤーに向かって移動
		//_position = _position + delta;

		_oldPos = _position;
		if (_status != STATUS::SEARCH) {

			if (_status != STATUS::ISHUCKED && _status != STATUS::ISHUCKING) {
				auto player = GetActorServer().GetPosition("Player");
				// プレイヤーに向かうベクトル
				auto forward = player - _position;
				// プレイヤーに向かう単位ベクトル
				if (Math::Vector4 v{ 0.0, 0.0, 0.0 }; forward.GetX() != v.GetX() && forward.GetZ() != v.GetZ())
				{
					forward = forward.Normalize();
				}
				// プレイヤーに向かう移動量ベクトル
				auto delta = forward * _forwardSpeed;
				// プレイヤーに向かって移動
				_position = _position + delta;

				// Y軸の回転角度を求める※時計回りz⇔x
				auto rotY = std::atan2(forward.GetX(), forward.GetZ());
				Math::Vector4 rot = { 0.0, rotY, 0.0 };
				SetRotation(rot);

				// アクターサーバーに位置を通知
				std::pair<Math::Vector4, Math::Vector4> pos_dir = { _position, rot };
				GetActorServer().Register("TackleEnemy", pos_dir);

				// ワールド行列の計算
				//ComputeWorldTransform();
			}
			else if (_status != STATUS::ISHUCKING) {
				auto playermove = GetActorServer().GetPosition("Player");
				_position = playermove;
				// Y軸の回転角度を求める※時計回りz⇔x
				auto dir = GetActorServer().GetDir("Player");
				auto rotY = std::atan2(dir.GetX(), dir.GetZ());
				Math::Vector4 rot = { 0.0, rotY, 0.0 };
				SetRotation(rot);
				//LockOn();

				//ComputeWorldTransform();
			}



		}
		else
		{
			/// <summary>
			///仮の動き(左右)
			/// </summary>
			if (_numberTimes < 100)
			{
				Math::Vector4 move = { 2.0, 0.0, 0.0 };
				_position = _position + move;
				// Y軸の回転角度を求める※時計回りz⇔x
				auto rotY = std::atan2(move.GetX(), move.GetZ());
				Math::Vector4 rot = { 0.0, rotY, 0.0 };
				SetRotation(rot);


			}
			else
			{
				Math::Vector4 move = { -2.0, 0.0, 0.0 };
				_position = _position + move;
				// Y軸の回転角度を求める※時計回りz⇔x
				auto rotY = std::atan2(move.GetX(), move.GetZ());
				Math::Vector4 rot = { 0.0, rotY, 0.0 };
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
		// プレイヤーに向かうベクトル
		auto forward = player - _position;
		// プレイヤーに向かう単位ベクトル
		forward = forward.Normalize();
		// Y軸の回転角度を求める※時計回りz⇔x
		auto rotY = std::atan2(forward.GetX(), forward.GetZ());
		Math::Vector4 rot = { 0.0, rotY, 0.0 };
		SetRotation(rot);
	}

	void TackleEnemy::Tackle(Math::Vector4 target) {

		//すでに決まった道筋までタックルする機構を書く

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

	// 待機
	void TackleEnemy::StateFall::Enter() {
		_owner._model->ChangeAnime("Fall", true);
	}

	void TackleEnemy::StateFall::Update() {

		//_owner.LockOn();
		if (_owner._position.GetY() > 0)
		{
			auto posY = _owner._position.GetY() - 5;
			//Math::Vector4 _pos = { 0.0, _pos_y, 0.0 };
			_owner._position = { _owner.GetPosition().GetX(), posY, _owner.GetPosition().GetZ() };
		}
		else
		{
			Math::Vector4 _pos = { _owner.GetPosition().GetX(), 0.0, _owner.GetPosition().GetZ() };
			_owner._position = _pos;
			_owner._state->GoToState("Idle");
		}
	}

	//待機
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
			//!< プレイヤーではなかったら次へ
			if ((*i)->GetTypeId() != TypeId::Player) {
				continue;
			}
			else {

				//if (_owner._collision->CircleToFan(_owner, **i)){
				//	_owner._state->GoToState("Run");
				//	_owner._status = STATUS::CHASE;
				//}

				if (_owner._collision->CircleToFan(_owner, **i, true)) {
					_owner._state->GoToState("Run");
					_owner._status = STATUS::CHASE;
				}

			}
		}
	}

	// 走り
	void TackleEnemy::StateRun::Enter() {
		_tacklePreTime = 60;
		_owner._model->ChangeAnime("RunAniVor", true);
	}

	void TackleEnemy::StateRun::Update() {
		//auto player = _owner.GetActorServer().GetPosition("Player");
		//// プレイヤーに向かうベクトル
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

		_owner.Move();


		//追跡状態か
		if (_owner._status == STATUS::CHASE)
		{
			////索敵範囲から外れているか
			//if (IsLoseSight())
			//{
			//	_loseSightTime--;
			//}
			//else 
			//{
			//	_loseSightTime = 60;
			//}
			_dif = _owner.GetActorServer().GetPosition("Player") - _owner.GetPosition();
			//索敵猶予時間が0を切ったら
			//if (_loseSightTime < 0)
			//{
			//	//捜索状態に戻る
			//	_owner._status = STATUS::SEARCH;
			//	_owner._state->GoToState("Idle");
			//	_loseSightTime = 60;
			//}

			//タックル準備時間が0
			if (_tacklePreTime < 0 && _dif.Length_XZ() < 600.0) {

				_owner._state->GoToState("Tackle");

			}
			else {//タックル準備中
				_tacklePreTime--;
			}

		}
	}

	bool TackleEnemy::StateRun::IsLoseSight() {

		auto player = _owner.GetActorServer().GetPosition("Player");
		auto range = player - _owner.GetPosition();
		auto length = range.Length();

		//playerと自分の位置の差が索敵範囲を越えていたら
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

	//死亡
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

	////攻撃
	//void Enemy::StateAttack::Enter() {
	//	_owner._model->ChangeAnime("Attack");
	//}
	//void Enemy::StateAttack::Update() {
	//	// 攻撃を受けたか確認
	//	_owner.HitCheckFrom();
	//
	//	// 攻撃モーションの終了確認
	//	auto cnt = _owner._model->GetRepeatedCount();
	//	if (cnt > 0) {
	//		_owner._state->PopBack();
	//		return;
	//	}
	//	// 攻撃モーションの15～20の間、攻撃判定あり
	//	auto playTime = _owner._model->GetPlayTime();
	//	if (playTime < 15.f || playTime > 20.f) {
	//		//　攻撃判定なし
	//		return;
	//	}
	//
	//	_owner._collision->PlayerFromEnemy();
	//
	//}
	//void Enemy::StateAttack::Draw() {
	//	_owner._model->Draw();
	//#ifdef _DEBUG
	//	//// 攻撃モーションの15～20の間、攻撃判定あり
	//	auto playTime = _owner._model->GetPlayTime();
	//	if (playTime < 15.f || playTime > 20.f) {
	//	  //　攻撃判定なし
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
	TackleEnemy::StateTackle::StateTackle(TackleEnemy& owner) :StateBase{ owner } {

		_tackleTime = 60;
		_speed = 5.0;
	}

	void TackleEnemy::StateTackle::Enter() {
		_tackleTime = 60;

		auto player = _owner.GetActorServer().GetPosition("Player");
		auto dif = player - _owner.GetPosition();
		auto length = dif.Length_XZ();


		auto rotY = std::atan2(dif.GetX(), dif.GetZ());
		Math::Vector4 rot = { 0.0, rotY, 0.0 };
		_owner.SetRotation(rot);

		if (length < 600.0) {

			auto mat = length / 600.0;
			dif = dif / mat;
		}

		//auto div = dif.Length_XZ();

		////長さを600で割る
		//div = div / 600.0;

		////差分を60分割した値
		//_norm = dif / div;
		_norm = dif.Normalize();

		_owner._model->ChangeAnime("Attack", true);
	}

	void TackleEnemy::StateTackle::Update() {

		if (_tackleTime < 0) {

			_owner._state->GoToState("TackleAfter");

		}
		else {
			_owner._position = _owner.GetPosition() + _norm * _speed;

			// Y軸の回転角度を求める※時計回りz⇔x
			//auto _rot_y = std::atan2(forward.GetX(), forward.GetZ());
			//auto rot = std::atan2(_norm.GetX(), _norm.GetZ());
			//Math::Vector4 rotY = { 0.0, rot, 0.0 };
			//_owner.SetRotation(rotY);

			// Y軸の回転角度を求める※時計回りz⇔x
			//auto dir = _owner.GetActorServer().GetDir("Player");
			//auto rotY = std::atan2(dir.GetX(), dir.GetZ());
			//Math::Vector4 rot = { 0.0, rotY, 0.0 };
			//_owner.SetRotation(rot);

			for (auto i = _owner.GetActorServer().GetActors().begin(); i != _owner.GetActorServer().GetActors().end(); i++) {

				//!< プレイヤーではなかったら次へ
				if ((*i)->GetTypeId() != TypeId::Player) {
					continue;
				}
				else {

					//プレイヤーが円で自分がAABB
					if (_owner._collision->CicrleToOrientedAABB(**i, _owner)) {

						int x = 0;
						//_owner._state->GoToState("Run");
						//_owner._status = STATUS::CHASE;
					}

				}
			}



			_tackleTime--;
		}
	}

	void TackleEnemy::StateTackleAfter::Enter() {
		_owner._model->ChangeAnime("Fall", true);
		_tackleAfterTime = 120;
	}

	void TackleEnemy::StateTackleAfter::Update() {


		if (_owner.GetStatus() == STATUS::ISHUCKING)
		{
			_owner._state->GoToState("IsHucking");
			//_loseSightTime = 60;
		}


		if (_tackleAfterTime < 0) {

			_owner._state->GoToState("Run");

		}
		else {
			_tackleAfterTime--;
		}

	}


	void TackleEnemy::StateHucking::Enter()
	{
		_owner._model->ChangeAnime("Attack", true);
	}

	void TackleEnemy::StateHucking::Update()
	{
		//// ハッキングされたか確認
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
		//// ハッキングされたか確認
		//_owner.HitCheckFrom();
		//if (_owner.GetActorState() != ActorState::Hucked)
		//{
		//	_owner._state->GoToState("Run");
		//	_owner._status = STATUS::CHASE;
		//}

		if (_owner.GetActorState() != ActorState::Hucked)
		{
			_owner._state->GoToState("Die");
			_owner._status = STATUS::DYING;
		}


	}
}


