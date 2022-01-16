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

	void TackleEnemy::Input(AppFrame::Input::InputComponent& input) {
		_state->Input(input);
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

		//索敵中ではない
		if (_status != STATUS::SEARCH) {

			//ハッキングされたまたはハッキング中ではない
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
				std::pair<Math::Vector4, Math::Vector4> posDir = { _position, rot };
				GetActorServer().Register("TackleEnemy", posDir);


				// ワールド行列の計算
				//ComputeWorldTransform();
			} //ハッキング中ではない
			else if (_status != STATUS::ISHUCKING) {
				//auto playermove = GetActorServer().GetPosition("Player");
				//_position = playermove;
				//// Y軸の回転角度を求める※時計回りz⇔x
				//auto dir = GetActorServer().GetDir("Player");
				//auto rotY = std::atan2(dir.GetX(), dir.GetZ());
				//Math::Vector4 rot = { 0.0, rotY, 0.0 };
				//SetRotation(rot);
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

		//CollisionFloor(_oldPos);

	}

	//ハッキングされたときの移動
	void TackleEnemy::HuckedMove(double lx, double ly) {
	
		_move = { 0.0, 0.0, 0.0 };

		//_oldPos = _position;
		//横方向の傾きと縦方向の傾きの大きさ
		double length = sqrt(lx * lx + ly * ly);
		if (length < 0.3) {
			// 入力が小さかったら動かなかったことにする
			length = 0.0;
		}
		else {
			length = 5.0;
		}

		//横方向と縦方向の角度
		double rad = atan2(ly, lx);

		//x軸方向の移動量
		auto moveX = cos(rad) * length;

		//z軸方向の移動量
		auto moveZ = sin(rad) * length;

		_move = { moveX, 0.0, moveZ };
		// 移動
		_position = _position + _move;

		if (_move.Length() > 0.0)
		{
		   auto dir = _move;
		   auto yRot = std::atan2(dir.GetX(), dir.GetZ());

		   Math::Vector4 rot = { 0.0, yRot, 0.0 };
		   SetRotation(rot);
		}

		//主人公のカメラに移動量を送る
		SetHuckedMove(_move);

		// ワールド行列の更新
		//ComputeWorldTransform();

		// Y軸の回転角度を求める※時計回りz⇔x
		//auto dir = GetActorServer().GetDir("Player");
		
		//Math::Vector4 rot = { 0.0, rad, 0.0 };
			
		//rot.Set(0.0, rad, 0.0);
		//SetRotation(rot);
		//LockOn();


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

	void TackleEnemy::StateBase::CollisionFloor(AppFrame::Math::Vector4 oldPos) {
	
		//Actorの方に移動した方がいいどのみち全部判定するから

		// 移動した先でコリジョン判定
		MV1_COLL_RESULT_POLY hitPoly;

		auto handle = _owner.GetGame().GetAssetServer().GetModel("Dungeon");

		for (auto i = _owner.GetActorServer().GetActors().begin(); i != _owner.GetActorServer().GetActors().end(); i++) {

			if ((*i)->GetTypeId() != TypeId::Stage) {
				continue;
			}
			else {

				auto frameMapCollision = (*i)->GetCollision().GetMapCollision();

				Math::Vector4 dif = { 0.0, 40.0, 0.0 };
				Math::Vector4 under = { 0.0, -99999.0, 0.0 };
				auto startPos = _owner.GetPosition() + dif;
				auto endPos = _owner.GetPosition() + under;
				// 主人公の腰位置から下方向への直線
				hitPoly = MV1CollCheck_Line(handle.first, frameMapCollision, ToDX(startPos), ToDX(endPos));

				if (hitPoly.HitFlag) {
					// 当たった
					// 当たったY位置をキャラ座標にする
					_owner._position = { _owner.GetPosition().GetX(), hitPoly.HitPosition.y, _owner.GetPosition().GetZ() };

					// カメラも移動する
					//_cam._vPos = VAdd(_cam._vPos, v);
					//_cam._vTarget = VAdd(_cam._vTarget, v);
				}
				else {
					// 当たらなかった。元の座標に戻す
					_owner._position = oldPos;
				}

			}

		}

	
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
			Math::Vector4 pos = { _owner.GetPosition().GetX(), 0.0, _owner.GetPosition().GetZ() };
			_owner._position = pos;
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
		Math::Vector4 oldPos = _owner.GetPosition();
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

		//ハッキングされている場合
		if (_owner.GetStatus() == STATUS::ISHUCKED) {

			//auto player = _owner.GetActorServer().GetDir("Player");
			
			auto rot = _owner.GetRotation();
			
			//z軸を0度とする
			auto nine = std::numbers::pi * 90.0 / 180.0;

			//仕様書より6m/s
			auto length = 600.0;

			//主人公の回転方向は反対向きのためマイナス
			Math::Vector4 move = { std::cos(-rot.GetY() + nine), 0.0, std::sin(-rot.GetY() + nine) };
			
			//目線の先に目標をつくる
			auto forward = move * length;

			
			_norm = forward.Normalize();

		}
		else {

			//追跡中
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
			_norm = dif.Normalize();

		}

		
		_owner._model->ChangeAnime("Attack", true);
	}

	void TackleEnemy::StateTackle::Update() {

		if (_tackleTime < 0) {
			_owner._state->GoToState("TackleAfter");
		}
		else {

			//地面のコリジョンから出ないなら
			Math::Vector4 oldPos = _owner.GetPosition();

			_owner._position = _owner.GetPosition() + _norm * _speed;

			//地面から出たかどうか
			CollisionFloor(oldPos);

			if (_owner.IsHucked()) {

				for (auto i = _owner.GetActorServer().GetActors().begin(); i != _owner.GetActorServer().GetActors().end(); i++) {

					//!< 敵ではなかったら次へ
					if ((*i)->GetTypeId() != TypeId::Enemy) {
						continue;
					}
					else {
						//ハッキングされていたら次へ	
						if ((*i)->IsHucked()) {

							continue;
						}
						else {

							//相手の円と自分のAABB
							if (_owner._collision->CicrleToOrientedAABB(**i, _owner)) {

								//int x = 0;
								(*i)->SetActorState(ActorState::Dead);
								//_owner._state->GoToState("Run");
								//_owner._status = STATUS::CHASE;
							}

						}



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


		if (_owner.GetStatus() == STATUS::ISHUCKING){
			_owner._state->GoToState("IsHucking");
			//_loseSightTime = 60;
		}
		else if (_owner.GetStatus() == STATUS::ISHUCKED) {
		
			_owner._state->GoToState("IsHucked");
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


	void TackleEnemy::StateHucked::Enter(){
		_owner._model->ChangeAnime("Attack");
	}

	void TackleEnemy::StateHucked::Input(AppFrame::Input::InputComponent& input) {
	
		auto& joypad = input.GetJoypad();
		auto& key = input.GetKeyBoard();
		auto lx = 0.0, ly = 0.0;

		   // 右移動と左移動
			if (joypad.LHorison() != 0.0)
			{
				lx = input.GetJoypad().LHorison() / 1000.0;
			}
			else if (key.Button_D() != 0)
			{
				lx = 1.0;
			}
			else if (key.Button_A() != 0)
			{
				lx = -1.0;
			}

			// 前進と後退
			if (input.GetJoypad().LVertical() != 0.0)
			{
				ly = input.GetJoypad().LVertical() / 1000.0;
			}
			else if (key.Button_W() != 0)
			{
				ly = 1.0;
			}
			else if (key.Button_S() != 0)
			{
				ly = -1.0;
			}
		
		if (input.GetJoypad().Button_RT()) {
			
			_owner._state->GoToState("Tackle");

		}
		else {
			_owner.HuckedMove(lx, ly);
		}
		
	}

	void TackleEnemy::StateHucked::Update(){
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


