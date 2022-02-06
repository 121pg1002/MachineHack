/*****************************************************************//**
 * @file   Player.cpp
 * @brief  プレイヤークラス
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
#include "../Gauge/GaugePlayer.h"
#include "../UI/UIComponent.h"
#include "../Flag/FlagData.h"


 //#include <numbers>
namespace {

	double measuredDistance = 500.0;
}

namespace MachineHuck::Player {

	//静的なメンバ―変数を実体化させる
	int Player::StateBase::_noDamageTime;

	//コンストラクタ
	Player::Player(AppFrame::Game& game) : Actor{ game } {
		_r = 150.0;
		_minXZ = { -100, -100 };
		_maxXZ = { 100, 100 };
		_isHit = false;
		_searchRange = 60.0;
		//_huckingRange = 30.0;
		_gaugeBase->Init();
		_gaugePlayer->Init(*this);
	}

	//入力
	void Player::Input(AppFrame::Input::InputComponent& input) {
		_camera->Input(input);  // カメラの入力

		auto& joypad = input.GetJoypad();
		auto& key = input.GetKeyBoard();
		lx = 0.0, ly = 0.0;


		if (_actorState != ActorState::Hucking && _actorState != ActorState::Hucked) {
			// 右移動と左移動
			if (joypad.LHorison() != 0.0) {
				lx = input.GetJoypad().LHorison() / 1000.0;
			}
			else if (key.Button_D() != 0) {
				lx = 1.0;
			}
			else if (key.Button_A() != 0) {
				lx = -1.0;
			}

			// 前進と後退
			if (input.GetJoypad().LVertical() != 0.0) {
				ly = input.GetJoypad().LVertical() / 1000.0;
			}
			else if (key.Button_W() != 0) {
				ly = 1.0;
			}
			else if (key.Button_S() != 0) {
				ly = -1.0;
			}
		}

		//***************//////////お試しで作ったハック用
		//ハッキングカウンタが0未満か
		if (_huckCount <= 0) {

			//判定中に変更
			_huckFailureFlag = 2;

			if (joypad.Button_RT() || key.Button_Space()) {

				//HuckingとHuckedで無かったら
				if (_actorState != ActorState::Hucking && _actorState != ActorState::Hucked) {

					//*se ハッキング(溜め)
					//_game.GetSoundComponent().Play("push");

					//状態をハッキング中に変更
					_actorState = ActorState::Hucking;


					_huckCount = 100;

					lx = 0.0, ly = 0.0;
				}

				//if (_actorState== ActorState::Hucked)//Hucked中なら
				//{
				//	_actorState= ActorState::Active;
				//	_huckCount = 200;
				//}

			}//ハッキングカウンタが0かつハッキング状態ではない
			else if (_huckCount == 0 && _actorState != ActorState::Hucked) {
				_actorState = ActorState::Active;
			}

			//ハッキングの解除
			if (joypad.Button_A() && _actorState == ActorState::Hucked) {
				//*se ハッキング(乗り捨て)
				_game.GetSoundComponent().Play("dropoff");

				_actorState = ActorState::Active;
				_huckCount = 200;
			}
			if (key.Button_LShift() && _actorState == ActorState::Hucked) {
				_actorState = ActorState::Active;
				_huckCount = 200;
			}
		}

		//ハッキング成功していない
		if (_huckFailureFlag != 1) {

			//ハックカウンタが10フレーム経過したか
			if (_huckCount < 90) {
				_huckFailureFlag = 0;
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
		//ゲージ
		_gaugePlayer->Update();

		//動かないときの処理に使用
		//auto oldMove = _move;

		////ダメージフラグが経っているかつ無敵時間が0未満なら
		//if (Flag::FlagData::GetDamageFlag() && Flag::FlagData::GetNoDamageTime() < 0) {
		//	_noDamageTime = 30;
		//}

	/*_noDamageTime*/


		Math::Vector4 oldPos = _position;

		//無敵時間が終了したとき
		if (Flag::FlagData::GetDamageFlag() == false) {
			Move();
		}
		else {
			_move = { 0.0, 0.0, 0.0 };
		}
		//else {
		//	int x = 0;
		//}

		//// ステータスに合わせてアニメーションのアタッチ
		//switch (_status) {
		//case ActorState::Active:
		   // _modelAnime->ChangeAnime("Idle");
		   // break;
		//case ActorState::WALK:
		   // _modelAnime->ChangeAnime("Run");
		   // break;

		//case ActorState::Hucking:
		   // _modelAnime->ChangeAnime("Attack");

		//case ActorState::Hucked:
		   // _modelAnime->ChangeAnime("Idle");
		//}




		// モデルの更新
		_modelAnime->Update();

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

		//if (_actorState!= ActorState::Hucked) {

		//_camera->Update(_move);

		for (auto&& i : GetActorServer().GetActors()) {

			if (i->GetTypeId() != TypeId::Stage) {
				continue;
			}

			auto floorNum = i->GetCollision().GetFloorNum();

			auto pos = i->GetCollision().GetFloorPos(floorNum[0]);
			_camera->FloorPos(pos);

		}

		//ステージ番号をここにもってくる[1]の部分に当てはめる
		 //地面のナビメッシュに触れているかどうか

		if (!IsHucked()) {
			CollisionFloor(oldPos, _r);


			//仮
			//ステージの中にある連想配列にアクセス



			//_camera->FloorPos(_move);

			//ワープ直後か
			if (!_warping) {

				auto dxPos = WarpFloor();

				//フェード用に保存
				_fadePos = { dxPos.x, dxPos.y, dxPos.z };

				//現在位置のステージ番号のワープナビメッシュに当たった場合
				if (dxPos.x != 0.0f && dxPos.z != 0.0f) {

					Flag::FlagData::SetFadeOutFlag(true);
					//Math::Vector4 pos = { dxPos.x, dxPos.y, dxPos.z };

					//_position = pos;
					//_position = _fadePos;

					//_camera->SetRefleshPosition(_position);
					//_camera->SetRefleshTarget(_position);

					if (!_warping) {

						_warping = true;
						_waitframe = 5;

						//_fadeflag = true;

					}
					//else {
					//	_warping = false;
					//}

					//ここにフェードイン処理

				}


			}
			else {

				//描画を1フレーム回す
				if (_waitframe == 4) {
					_position = _fadePos;
				}

				if (_waitframe == 0) {
					Flag::FlagData::SetFadeInFlag(true);
				}

				if (!WarpingFloor() && _waitframe < 0) {

					//_position = _fadePos;
					_warping = false;

				}

			}

			_waitframe--;

		}

		//エネルギー残量ゲージの設定
		GetGame().GetUiComponent().UpdatePlayerHp(_gaugeBase->GetGauge(), _gaugeBase->GetGaugeMax());
		//	GetGame().GetUiComponent().UpdatePlayerHp(_gauge->GetGauge(), _gauge->GetGaugeMax());

		for (auto i = GetActorServer().GetActors().begin(); i != GetActorServer().GetActors().end(); i++) {
			auto targetPos = (*i)->GetPosition();
			auto dif = _position - targetPos;

			//測定距離内にいる場合
			if (dif.Length_XZ() < measuredDistance) {

				//!< エネミーではなかったら次へ
				if ((*i)->GetTypeId() != TypeId::Enemy) {
					//!< ギミックではなかったら次へ
					//if ((*i)->GetTypeId() != TypeId::Gimmick) {
					//	continue;
					//}
					//else {

					//	////自分とギミック
					//	//if (_collision->CircleToCircle(*this, **i)) {

					//	//	if (_noDamageTime < 0) {
					//	//		_gaugeBase->DownGauge(10);
					//	//		_noDamageTime = 60;
					//	//	}
					//	//}
					//	//else {
					//	//	_noDamageTime = 60;
					//	//}

					//}
				}
				else {

					//Circle(プレイヤー)と扇形(エネミー)の当たり判定を調べる
					if (_collision->FanToPoint(*this, **i)) {
						_isHit = true;
					}
					else {
						_isHit = false;
					}

				}


			}

		}

		//if (_actorState != ActorState::Hucking) {
			//毎フレームハッキングカウンタを減らす
		_huckCount--;
		//}


		//ハッキングカウンタが0未満か
		if (_huckCount < 0) {

			if (_actorState == ActorState::Hucking) {

				_actorState = ActorState::Active;

			}


		}

		//if (_fadeflag) {

		//	_game.GetSceneServer().PopBack(1);
		//	_game.GetSceneServer().PushBack("Item", 1);
		//
		//}

	}

	void Player::Draw() {
		//ハッキングされた状態のアクターがあるか
		bool IsHack = FALSE;
		for (auto&& actors : GetActorServer().GetActors()) {

			IsHack = actors->IsHucked();
			if (IsHack) {
				break;

			}

		}
		//ハッキングされているときはシャドウマップへの描画を行わない
		if (!GetShadowMapflg() || IsHack == FALSE) {
			_state->Draw();
		}
		//エネルギーゲージのシャドウマップへの描画を行わない
		if (!GetShadowMapflg() == TRUE) {
			_gaugePlayer->Draw(*this);
		}
		_state->Draw();
#ifdef _DEBUG
		_modelAnime->Draw(*this, _isHit, _searchRange, true);
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

	///// 移動
	void Player::Move() {

		_move = { 0.0, 0.0, 0.0 };

		_oldPos = _position;
		//横方向の傾きと縦方向の傾きの大きさ
		double length = sqrt(lx * lx + ly * ly);

		if (length < _analogMin) {
			// 入力が小さかったら動かなかったことにする
			length = 0.0;
			_hp++;
		}
		else {
			length = 10.0;
			_hp -= 0.1f;//エネルギー現象
		}
		if (_hp < 0) {
			_hp = 0;
		}
		if (_hp > 100) {
			_hp = 100;
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

		if (_move.Length() > 0.0) {
			_dir = _move;
		}

		//主人公の角度を取得
		//auto angle = GetRotation();

		//y軸回転を出す
		auto yRot = atan2(_dir.GetX(), _dir.GetZ());
		Math::Vector4 rot = { 0.5, yRot, 0.0 };
		////z軸を0度とする
		//auto nine = DX_PI / 180.0 * 90.0;
		//_y_rot += 90.0;
		//angle.Set(0.0, _y_rot, 0.0);
		//角度を更新
		SetRotation(rot);

	}

	/// 敵からの攻撃を確認
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
		_owner.GetModelAnime().Draw();
	}
	/// 待機
	void Player::StateIdle::Enter() {
		_owner.GetModelAnime().ChangeAnime("Idle", true);

		////無敵フラグがオンなら120フレーム無敵時間を作る
		//if (Flag::FlagData::GetNoDamageFlag()) {
		//	_noDamageTime = 120;
		//}
		//_actorState= ActorState::Active;
	}

	void Player::StateIdle::Input(AppFrame::Input::InputComponent& input) {

		//if (input.GetJoypad().Button_B()) {
		//	_owner._state->PushBack("Attack");
		//}



		if (input.GetJoypad().Button_RT() || input.GetKeyBoard().Button_Space()) {
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
		if (Flag::FlagData::GetDamageFlag()) {

			//ダメージフラグをオフに
			Flag::FlagData::SetDamageFlag(false);

			//無敵フラグをオンに
			Flag::FlagData::SetNoDamageFlag(true);

			_noDamageTime = 120;

		}

		//if (Flag::FlagData::GetNoDamageTime() > 0) {
		//	_owner._state->GoToState("Damage");
		//}
		_noDamageTime--;

		//無敵時間が終わったら元に戻す
		if (_noDamageTime < 0 && Flag::FlagData::GetNoDamageFlag()) {
			Flag::FlagData::SetNoDamageFlag(false);
		}

	}

	/// 走り
	void Player::StateRun::Enter() {
		_owner.GetModelAnime().ChangeAnime("Run", true);
		/*_actorState= ActorState::WALK;*/
	}


	void Player::StateRun::Input(AppFrame::Input::InputComponent& input) {

		//if (input.GetJoypad().Button_B()) {
		//	_owner._state->PushBack("Attack");
		//	return;
		//}


			//無敵時間中は移動のみ可能
		if ((input.GetJoypad().Button_RT() || input.GetKeyBoard().Button_Space()) && !Flag::FlagData::GetNoDamageFlag()) {
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
		if (_owner.GetGaugePlayer().GetGauge() < 0) {
			_owner._state->GoToState("Die");
		}
		//else if (Flag::FlagData::GetNoDamageTime() > 0) {

		//	_owner._state->GoToState("Damage");

		//}
		else {

			_owner.GetGaugeBase().Update(_owner);
			_owner.GetGaugePlayer().Update(_owner);
		}

		if (_noDamageTime < 0 && Flag::FlagData::GetNoDamageFlag()) {

			Flag::FlagData::SetNoDamageFlag(false);
		}

		_noDamageTime--;

	}

	//ダメージ状態
	void Player::StateDamage::Enter() {

		_owner.GetModelAnime().ChangeAnime("Damage", true);
	}

	//ダメージ
	void Player::StateDamage::Update() {


		if (_owner.GetModelAnime().GetRepeatedCount() > 0) {

			_owner._state->GoToState("Idle");

			//_owner._state->PopBack();

			//プレイヤーを移動可能にする
			//Flag::FlagData::SetDamageFlag(false);

		}

	}




	/// 攻撃
	void Player::StateAttack::Enter() {
		//_owner.GetModelAnime().ChangeAnime("Attack");
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
		//auto cnt = _owner.GetModelAnime().GetRepeatedCount();
		//if (cnt > 0) {
		//	_owner._state->PopBack();
		//	return;
		//}
		//auto playTime = _owner.GetModelAnime().GetPlayTime();
		//if (playTime < 3.5f || playTime > 20.f) {
		//	_owner.HitCheckFromEnemy();
		//	return;
		//}
		//_owner._collision->EnemyFromPlayer();
	}
	void Player::StateAttack::Draw() {
		//	_owner.GetModelAnime().Draw();
		//#ifdef _DEBUG
		//	auto playTime = _owner.GetModelAnime().GetPlayTime();
		//	if (playTime < 3.5f || playTime > 20.f) {
		//	  return;
		//	}
		//
		//	auto handle = _owner.GetModelAnime().GetHandle();
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

		_owner.GetModelAnime().ChangeAnime("Attack");
		_huckingTime = 10;
		/*_actorState= ActorState::Hucking;*/
	}


	void Player::StateHucking::Update() {

		if (_owner.GetActorState() != ActorState::Hucking) {
			_owner._state->PopBack();
			return;
		}
		else
		{
			//ハッキング失敗フラグか立っているかどうか
			if (_owner.GetHuckFailureFlag() != 0) {

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
						if (_owner._collision->FanToPoint(_owner, **i, true)) {

							////自分の中心が敵のハッキング範囲に入っているかどうか
							if (_owner._collision->FanToPoint(**i, _owner, false)) {

								if (_owner._actorState == ActorState::Hucking)
								{

									(*i)->SetActorState(ActorState::Hucking);

									//成功した
									_owner.SetHuckFailureFlag(1);

									auto enem_pos = (*i)->GetPosition();

									if (enem_pos.GetX() - 1 < _owner._position.GetX() && _owner._position.GetX() < enem_pos.GetX() + 1 && enem_pos.GetZ() - 1 < _owner._position.GetZ() && _owner._position.GetZ() < enem_pos.GetZ() + 1/* && _owner._position.GetY() - 1 < 200.0 && 200.0 < _owner._position.GetY() + 1*/) {
										_owner._actorState = ActorState::Hucked;
										_owner._state->GoToState("Hucked");
										//*se ハッキング(成功)
										_owner.GetGame().GetSoundComponent().Play("hacking");

									}
									else {

										//_dif = enem_pos - _owner._position;

										////仮のy座標
										//_length = _dif.Normalize();

										// 移動
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
						else {
							_owner._isHit = false;
							(*i)->SetIsHit(false);

						}

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

		_owner.GetModelAnime().ChangeAnime("Idle");
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

	/// ハッキング
	void Player::StateHucked::Update() {

		for (auto i = _owner.GetActorServer().GetActors().begin(); i != _owner.GetActorServer().GetActors().end(); i++) {

			//	if (!(*i)->IsDead()) {
			if ((*i)->GetTypeId() != TypeId::Player) {

				if (!(*i)->IsHucked()) {

					if ((*i)->GetGaugeBase().GetGauge() > 0) {
						continue;
					}
					if ((*i)->GetGaugePlayer().GetGauge() > 0) {
						continue;
					}
					else {
						_owner.SetActorState(ActorState::Active);
						_owner._state->GoToState("Idle");
					}


				}
				else {
					//ハッキングした対象に追従
					//Math::Vector4 difY = { 0.0, 150.0, 0.0 };
					//Math::Vector4 difRot = { 0.2, 0.0, 0.0 };
					auto headPos = Flag::FlagData::GetHeadPos();

					Math::Vector4 headPosition = { headPos.x, headPos.y, headPos.z };

					//_owner._position = (*i)->GetPosition() + headPosition;
					_owner._position = headPosition;
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

		//プレイヤー側から解除した場合
		if (_owner._actorState != ActorState::Hucked) {

			for (auto i = _owner.GetActorServer().GetActors().begin(); i != _owner.GetActorServer().GetActors().end(); i++) {
				//ハッキングされているか
				if (!(*i)->IsHucked()) {
					continue;
				}
				else {

					auto enemyGauge = (*i)->GetGaugeBase().GetGauge();

					//エネミーのゲージが0以上なら
					if (enemyGauge > 0) {

						//エネミーのゲージ量を加算
						_owner.GetGaugeBase().PlusGauge(enemyGauge);
					}
					auto enemyGaugePlayer = (*i)->GetGaugePlayer().GetGauge();
					if (enemyGaugePlayer > 0) {
						//エネミーのゲージ量を加算
						_owner.GetGaugePlayer().PlusGauge(enemyGauge);
					}
					_owner._position = { _owner.GetPosition().GetX(), 0.0, _owner.GetPosition().GetZ() };
					(*i)->SetActorState(ActorState::Active);
					_owner._state->GoToState("Idle");

				}







			}

		}
	}

	void Player::StateDie::Enter() {

		_owner.GetModelAnime().ChangeAnime("Die");
	}

	void Player::StateDie::Update() {
		auto cnt = _owner.GetModelAnime().GetRepeatedCount();
		if (cnt > 0) {
			_owner.SetActorState(ActorState::Dead);
			Flag::FlagData::SetPlayerDead(true);
		}
		auto handle = _owner.GetModelAnime().GetHandle();
		auto progress = _owner.GetModelAnime().GetPlayProgress();
		auto num = MV1GetMeshNum(handle);
		for (auto i = 0; i < num; ++i) {
			MV1SetMeshOpacityRate(handle, i, 1.f - progress);
		}


	}
}


