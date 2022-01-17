///
/// @file    Player.cpp
/// @brief   プレイヤー
/// @date    2021/11/26
/// @author yamawaki kota
/// @copyright (C) Amusement Media Academy All rights Resved.
///
#include "AppFrame.h"
#include "Player.h"
#include "../Enemy/EnemyBase.h"
#include "../Actor/ActorServer.h"
#include "../Camera/CameraComponent.h"
#include "../Model/ModelAnimComponent.h"
#include "../Collision/CollisionComponent.h"
#include "../Enemy/TackleEnemy.h"

#include <numbers>


namespace MachineHuck::Player {
	//コンストラクタ
	Player::Player(AppFrame::Game& game) : Actor{ game } {
		_r = 100.0;
		_minXZ = { -100, -100 };
		_maxXZ = { 100, 100 };
		_isHit = false;
		_searchRange = 60.0;
		_huckingRange = 30.0;
	}

	//入力
	void Player::Input(AppFrame::Input::InputComponent& input) {
		_camera->Input(input);  // カメラの入力

		auto& joypad = input.GetJoypad();
		auto& key = input.GetKeyBoard();
		lx = 0.0, ly = 0.0;


		if (_status != STATUS::HUCKING && _status != STATUS::HUCKED)
		{   // 右移動と左移動
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
		}

		//***************//////////お試しで作ったハック用
		//でもおそらく、ブレンドするから没になる
		if (_huckcount <= 0)
		{

			if (joypad.Button_RT())
			{
				//HUCKINGとHUCKEDで無かったら
				if (_status != STATUS::HUCKING && _status != STATUS::HUCKED)
				{
					_status = STATUS::HUCKING;
					_huckcount = 200;
				}

				//if (_status == STATUS::HUCKED)//HUCKED中なら
				//{
				//	_status = STATUS::WAIT;
				//	_huckcount = 200;
				//}
			}
			else if (_huckcount == 0 && _status != STATUS::HUCKED)
			{
				_status = STATUS::WAIT;
			}

			if (joypad.Button_A() && _status == STATUS::HUCKED) {
					_status = STATUS::WAIT;
					_huckcount = 200;
			}

		}

		_huckcount--;
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
		//動かないときの処理に使用
		//auto oldMove = _move;


		Math::Vector4 oldPos = _position;

		Move();





		//// ステータスに合わせてアニメーションのアタッチ
		//switch (_status) {
		//case STATUS::WAIT:
		   // _model->ChangeAnime("Idle");
		   // break;
		//case STATUS::WALK:
		   // _model->ChangeAnime("Run");
		   // break;

		//case STATUS::HUCKING:
		   // _model->ChangeAnime("Attack");

		//case STATUS::HUCKED:
		   // _model->ChangeAnime("Idle");
		//}


		// モデルの更新
		_model->Update();

		// カメラの更新
		//_camera->SetTarget(_position, _move);
		//if (_move.GetX() != oldMove.GetX() && _move.GetZ() != oldMove.GetZ()) {
		//
		//	Math::Vector4 cameraDif = { 0.0, 500.0,  -200.0 };
		//	_camera->SetPosition(_position + cameraDif);
		//}

		  // アクターサーバーに位置を通知
		std::pair<Math::Vector4, Math::Vector4> pos_dir = { _position, _dir };
		GetActorServer().Register("Player", pos_dir);

		_state->Update();
		
		//if (_status != STATUS::HUCKED) {

			

		//地面に触れているかどうか
		if (!CollisionFloor(oldPos)) {

			Math::Vector4 zero = { 0.0, 0.0, 0.0 };
			_camera->Update(zero);
		}
		else {
			_camera->Update(_move);
		}
			


		//}
		//else {
		//	//ハッキング中は敵から移動量を取得
		//	_camera->Update(_huckedMove);
		//}

		for (auto i = GetActorServer().GetActors().begin(); i != GetActorServer().GetActors().end(); i++)
		{
			//!< プレイヤーではなかったら次へ
			if ((*i)->GetTypeId() != TypeId::Enemy)
			{
				continue;
			}
			else
			{   //円と円の当たり判定を調べる

				/// //////////////円と円の判定を行いたいならこっちを起動AABBToAABBなら下だけ起動

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

				//CircleとAABBの当たり判定を調べる
				if (_collision->CircleToFan(*this, **i))
				{
					_isHit = true;
				}
				else
				{
					_isHit = false;
				}

			}

		}

	}

	void Player::Draw() {
		_state->Draw();

#ifdef _DEBUG
		_model->Draw(*this, _isHit, _searchRange, true);
		_camera->Draw(_isHit);
#endif
	}

	void Player::ComputeWorldTransform() {
		auto world = MGetScale(ToDX(_scale));
		world = MMult(world, MGetRotZ(static_cast<float>(_rotation.GetZ())));
		world = MMult(world, MGetRotX(static_cast<float>(_rotation.GetX())));
		world = MMult(world, MGetRotY(static_cast<float>(_rotation.GetY()) + std::numbers::pi_v<float>));
		_worldTransform = MMult(world, MGetTranslate(ToDX(_position)));
	}

	///// 移動
	void Player::Move() {

		_move = { 0.0, 0.0, 0.0 };

		_oldPos = _position;
		//横方向の傾きと縦方向の傾きの大きさ
		double length = sqrt(lx * lx + ly * ly);

		if (length < _analogMin) {
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
		
		// ワールド行列の更新
		ComputeWorldTransform();

		if (_move.Length() > 0.0)
		{
			_dir = _move;
		}

		//主人公の角度を取得
		//auto angle = GetRotation();

		//y軸回転を出す
		auto yRot = atan2(_dir.GetX(), _dir.GetZ());
		Math::Vector4 rot = { 0.0, yRot, 0.0 };
		////z軸を0度とする
		//auto nine = std::numbers::pi / 180.0 * 90.0;
		//_y_rot += 90.0;
		//angle.Set(0.0, _y_rot, 0.0);
		//角度を更新
		SetRotation(rot);

	}

	/// 敵からの攻撃を確認
	void Player::HitCheckFromEnemy() {
		//auto& report = _collision->GetReport();
		//if (report.id == CollisionComponent::ReportId::HitFromEnemy) {
		//	_state->GoToState("KnockBack");
		//	_game.GetSoundComponent().Play("damage");

		//	auto backward = _position - report.position;
		//	_backDelta = backward.Normalize() * 20;
		//}
	}

	void Player::StateBase::Draw() {
		_owner._model->Draw();
	}
	/// 待機
	void Player::StateIdle::Enter() {
		_owner._model->ChangeAnime("Idle", true);
		//_status = STATUS::WAIT;
	}

	void Player::StateIdle::Input(AppFrame::Input::InputComponent& input) {

		//if (input.GetJoypad().Button_B()) {
		//	_owner._state->PushBack("Attack");
		//}

		if (Math::Vector4 v{ 0.0, 0.0, 0.0 }; v.GetX() != _owner.GetMove().GetX() || v.GetZ() != _owner.GetMove().GetZ()) {
			_owner._state->PushBack("Run");
		}

		if (input.GetJoypad().Button_RT())
		{
			_owner._state->PushBack("Hucking");
		}

	}


	void Player::StateIdle::Update() {
		_owner.HitCheckFromEnemy();

	}

	/// 走り
	void Player::StateRun::Enter() {
		_owner._model->ChangeAnime("Run", true);
		/*_status = STATUS::WALK;*/
	}


	void Player::StateRun::Input(AppFrame::Input::InputComponent& input) {

		//if (input.GetJoypad().Button_B()) {
		//	_owner._state->PushBack("Attack");
		//	return;
		//}
		if (Math::Vector4 v{ 0.0, 0.0, 0.0 }; v.GetX() != _owner.GetMove().GetX() || v.GetZ() != _owner.GetMove().GetZ()) {
			return;
		}
		_owner._state->PopBack();
	}



	void Player::StateRun::Update() {
		//_owner.HitCheckFromEnemy();

	}

	/// 攻撃
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

	///// ノックバック
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

	/// ハッキング中
	void Player::StateHucking::Enter() {

		_owner._model->ChangeAnime("Idle");
		/*_status = STATUS::HUCKING;*/
	}


	void Player::StateHucking::Update() {

		if (_owner._status != STATUS::HUCKING) {
			_owner._state->PopBack();
			return;
		}
		else
		{
			for (auto i = _owner.GetActorServer().GetActors().begin(); i != _owner.GetActorServer().GetActors().end(); i++)
			{
				//!< プレイヤーではなかったら次へ
				if ((*i)->GetTypeId() != TypeId::Enemy)
				{
					continue;
				}
				else
				{   //円と円の当たり判定を調べる

					/// //////////////円と円の判定を行いたいならこっちを起動AABBToAABBなら下だけ起動

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

					//CircleとAABBの当たり判定を調べる
					//敵の中心が入っているかどうか
					if (_owner._collision->CircleToFan(_owner, **i, true)) {

						////自分の中心が敵のハッキング範囲に入っているかどうか
						if (_owner._collision->CircleToFan(**i, _owner, false)) {

							if (_owner._status == STATUS::HUCKING)
							{

								(*i)->SetActorState(ActorState::Hucking);

								auto enem_pos = (*i)->GetPosition();

								if (enem_pos.GetX() - 1 < _owner._position.GetX() && _owner._position.GetX() < enem_pos.GetX() + 1 && enem_pos.GetZ() - 1 < _owner._position.GetZ() && _owner._position.GetZ() < enem_pos.GetZ() + 1) {
									_owner._status = STATUS::HUCKED;
									_owner._state->GoToState("Hucked");
								}
								else {
									//if (Math::Vector4 v{0.0, 0.0, 0.0}; _dif.GetX() == v.GetX() && _dif.GetZ() == v.GetZ())
									//{
									_dif = enem_pos - _owner._position;
									_length = _dif.Normalize();
									//}

									////横方向と縦方向の角度
									//float rad = atan2(_dif.GetZ(), _dif.GetX());

									////x軸方向の移動量
									//auto _move_x = cos(rad) * _length;

									////z軸方向の移動量
									//auto _move_z = sin(rad) * _length;

									//Math::Vector4 _move = { _move_x, 0.0f, _move_z };

									// 移動
									_owner._position = _owner._position + _length;
									//std::pair<Math::Vector4, Math::Vector4> pos_dir = {_owner._position, _owner.GetActorServer().GetDir("Player")};
									//_owner.GetActorServer().Register("Player", pos_dir);
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
						//if (_status != STATUS::HUCKING && _status != STATUS::HUCKED)



					}
					else
					{
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


	/// ハッキング
	void Player::StateHucked::Enter() {

		_owner._model->ChangeAnime("Idle");
		/*_status = STATUS::HUCKING;*/
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

	/// ハッキング
	void Player::StateHucked::Update() {

		for (auto i = _owner.GetActorServer().GetActors().begin(); i != _owner.GetActorServer().GetActors().end(); i++)
		{
				if ((*i)->GetActorState() != ActorState::Hucked)
				{
					continue;
				}
				else
				{
					//ハッキングした対象に追従
				    _owner._position = (*i)->GetPosition();
					_owner._rotation = (*i)->GetRotation();
					//_owner._huckedMove = (*i)->GetHuckedMove();
					_owner._move = (*i)->GetHuckedMove();
				}
		}

		if (_owner._status != STATUS::HUCKED)
		{
			for (auto i = _owner.GetActorServer().GetActors().begin(); i != _owner.GetActorServer().GetActors().end(); i++)
			{
				if ((*i)->GetActorState() != ActorState::Hucked)
				{
					continue;
				}
				else
				{
					(*i)->SetActorState(ActorState::Active);
					_owner._state->GoToState("Idle");
				}

			}

		}
	}
}


