/*****************************************************************//**
 * @file   TackleEnemy.h
 * @brief  タックルする敵
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

	//静的なメンバ―変数を実体化させる
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
		_gaugeEnemy->Init(*this);//エネミーのエネルギーゲージの初期化
	}

	void TackleEnemy::LoadJson(const std::string& filePath)
	{
		auto eParam = std::make_unique<EnemyParameter>();
		eParam->LoadEnemyParam(filePath);

		//auto eParam = std::make_unique<EnemyParameter>();
		//eParam->LoadEnemyParam("resource/json/tackle.json");
		////2つめの値がレベル
		//_r = eParam->GetEnemyParam("r", 0);
		_r = 150.0;
		//_huckR = eParam->GetEnemyParam("r", 0);
		_huckR = 200.0;

		_searchRange = eParam->GetEnemyParam("searchrange", 1);
		_huckingRange = eParam->GetEnemyParam("searchrange", 0);////////←とりあえず、仮



	}

	//各種パラメーターを読み込む
	//void TackleEnemy::ParameterLoad() {


	//	
	//}


	void TackleEnemy::Update() {

		EnemyBase::Update();
		//ゲージ
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

		//// ワールド行列の計算
		ComputeWorldTransform();

		// モデルの更新
		_modelAnime->Update();

	}

	void TackleEnemy::Input(AppFrame::Input::InputComponent& input) {
		_state->Input(input);
	}

	void TackleEnemy::Draw() {
		// 足のトゲの為のアルファテスト設定
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
	//	//// プレイヤーに向かう単位ベクトル
	//	//auto forward = GetForward();
	//	//// プレイヤーに向かう移動量ベクトル
	//	//auto delta = forward * _forwardSpeed;
	//	//// プレイヤーに向かって移動
	//	//_position = _position + delta;

	//	_oldPos = _position;

	//	//索敵中ではない
	//	if (_status != STATUS::SEARCH) {

	//		//ハッキングされたまたはハッキング中ではない
	//		if (_status != STATUS::ISHUCKED && _status != STATUS::ISHUCKING) {
	//			auto player = GetActorServer().GetPosition("Player");
	//			// プレイヤーに向かうベクトル
	//			player = { player.GetX(), 0.0, player.GetZ() };
	//			auto forward = player - _position;
	//			// プレイヤーに向かう単位ベクトル
	//			if (Math::Vector4 v{ 0.0, 0.0, 0.0 }; forward.GetX() != v.GetX() && forward.GetZ() != v.GetZ())
	//			{
	//				forward = forward.Normalize();
	//			}
	//			// プレイヤーに向かう移動量ベクトル
	//			auto delta = forward * _forwardSpeed;
	//			// プレイヤーに向かって移動
	//			_position = _position + delta;

	//			// Y軸の回転角度を求める※時計回りz⇔x
	//			auto rotY = std::atan2(forward.GetX(), forward.GetZ());
	//			Math::Vector4 rot = { 0.0, rotY, 0.0 };
	//			SetRotation(rot);

	//			// アクターサーバーに位置を通知
	//			std::pair<Math::Vector4, Math::Vector4> posDir = { _position, rot };
	//			GetActorServer().Register("TackleEnemy", posDir);


	//			// ワールド行列の計算
	//			//ComputeWorldTransform();
	//		} //ハッキング中ではない
	//		else if (_status != STATUS::ISHUCKING) {
	//			//auto playermove = GetActorServer().GetPosition("Player");
	//			//_position = playermove;
	//			//// Y軸の回転角度を求める※時計回りz⇔x
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
	//		///仮の動き(左右)
	//		/// </summary>
	//		if (_numberTimes < 100)
	//		{
	//			Math::Vector4 move = { 2.0, 0.0, 0.0 };
	//			_position = _position + move;
	//			// Y軸の回転角度を求める※時計回りz⇔x
	//			auto rotY = std::atan2(move.GetX(), move.GetZ());
	//			Math::Vector4 rot = { 0.0, rotY, 0.0 };
	//			SetRotation(rot);

	//		}
	//		else
	//		{
	//			Math::Vector4 move = { -2.0, 0.0, 0.0 };
	//			_position = _position + move;
	//			// Y軸の回転角度を求める※時計回りz⇔x
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

	//ハッキングされたときの移動
	//void TackleEnemy::HuckedMove(double lx, double ly) {
	//
	//	_move = { 0.0, 0.0, 0.0 };

	//	//_oldPos = _position;
	//	//横方向の傾きと縦方向の傾きの大きさ
	//	double length = sqrt(lx * lx + ly * ly);
	//	if (length < 0.3) {
	//		// 入力が小さかったら動かなかったことにする
	//		length = 0.0;
	//	}
	//	else {
	//		length = 5.0;
	//	}

	//	//横方向と縦方向の角度
	//	double rad = atan2(ly, lx);

	//	//x軸方向の移動量
	//	auto moveX = cos(rad) * length;

	//	//z軸方向の移動量
	//	auto moveZ = sin(rad) * length;

	//	_move = { moveX, 0.0, moveZ };
	//	// 移動
	//	_position = _position + _move;

		   //移動していたら減らす
		//   _gaugeBase->Update(*this);

		//}

	//	   Math::Vector4 rot = { 0.0, yRot, 0.0 };
	//	   SetRotation(rot);

	//	   //移動していたら減らす
	//	   _gaugeBase->Update(*this);
	//	}

	//	//主人公のカメラに移動量を送る
	//	SetHuckedMove(_move);



	//	// ワールド行列の更新
	//	//ComputeWorldTransform();

	//	// Y軸の回転角度を求める※時計回りz⇔x
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
	//	// プレイヤーに向かうベクトル
	//	auto forward = player - _position;
	//	// プレイヤーに向かう単位ベクトル
	//	forward = forward.Normalize();
	//	// Y軸の回転角度を求める※時計回りz⇔x
	//	auto rotY = std::atan2(forward.GetX(), forward.GetZ());
	//	Math::Vector4 rot = { 0.0, rotY, 0.0 };
	//	SetRotation(rot);
	//}

	//void TackleEnemy::Tackle(Math::Vector4 target) {

	//	//すでに決まった道筋までタックルする機構を書く

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

	// 待機
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

	//待機
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
			//!< プレイヤーではなかったら次へ
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
					//*se プレイヤー発見
					_owner.GetGame().GetSoundComponent().Play("contact");

				}

			}
		}
	}

	// 走り
	void TackleEnemy::StateRun::Enter() {
		_tacklePreTime = 60;
		_owner.GetModelAnime().ChangeAnime("Walk", true);
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
		//_owner.Move("TackleEnemy");
		_owner.Direction();


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
			if (_tacklePreTime < 0) {

				_owner._state->GoToState("Tackle");
				//*se 攻撃(タックル）
				_owner.GetGame().GetSoundComponent().Play("tackle");

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

	//ハッキング中のダメージ
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

		//ハッキングされている場合
		if (_owner.GetStatus() == STATUS::ISHUCKED) {

			//ゲージ減少
			_owner.GetGaugeBase().DownGauge(30);
			_owner.GetGaugeEnemy().DownGauge(30);
			//auto player = _owner.GetActorServer().GetDir("Player");

			auto rot = _owner.GetRotation();

			//z軸を0度とする
			auto nine = DX_PI * 90.0 / 180.0;

			//仕様書より6m/s
			auto length = 9900.0;

			//主人公の回転方向は反対向きのためマイナス
			Math::Vector4 move = { std::cos(-rot.GetY() + nine), 0.0, std::sin(-rot.GetY() + nine) };


			//目線の先に目標をつくる
			auto forward = move * length;


			_norm = forward.Normalize();



		}
		else {

			//追跡中
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





		//前フレームの位置を保存
		Math::Vector4 oldPos = _owner.GetPosition();

		_owner._position = _owner.GetPosition() + _norm * _speed;

		//床から出たらタックル終了
		if (!_owner.CollisionFloor()) {
			_owner._state->GoToState("TackleAfter");
			_owner._position = oldPos;
		}

		////地面と触れているかどうか
		//_owner.CollisionFloor(oldPos, _owner.GetR());

		//主人公のカメラに移動量を送る
		//_owner.SetHuckedMove(_norm * _speed);


		//}
		//else {
		//
		//	Math::Vector4 zero = { 0.0, 0.0, 0.0 };
		//	//主人公のカメラに移動量を送る
		//	_owner.SetHuckedMove(zero);
		//}

		////ハッキングされているか(追跡時のタックルを省く)
		if (_owner.IsHucked()) {

			for (auto i = _owner.GetActorServer().GetActors().begin(); i != _owner.GetActorServer().GetActors().end(); i++) {

				//!< 敵ではなかったら次へ
				if ((*i)->GetTypeId() != TypeId::Enemy) {

					//ギミックではなかったら次へ
					if ((*i)->GetTypeId() != TypeId::Gimmick) {

						continue;
					
					}


					//壊せる壁と当たったか
					if (_owner.CollisionWall(**i, _norm)) {
						//当たった壁を死亡状態に変更
						(*i)->SetActorState(ActorState::Dead);

						//スライドアウトフラグをオンに
						//Flag::FlagData::SetSlideOut(true);

						//*se 壁が壊れる(未実装)
						_owner.GetGame().GetSoundComponent().Play("broken");

					}


				}//敵だった
				else {

					//ハッキングされていたら次へ	
					if ((*i)->IsHucked()) {
						continue;
					}
					else {

						//相手エネミーの円と自分のAABB
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

			//プレイヤー無敵時間中とプレイヤーダメージフラグがオンのときは、通さない
			if (Flag::FlagData::GetNoDamageFlag() == false && Flag::FlagData::GetDamageFlag() == false) {

				//ハッキング中の無敵時間中とハッキングダメージフラグがオンのときは、通さない
				if (Flag::FlagData::GetHuckDamageFlag() == false && Flag::FlagData::GetHuckNoDamageFlag() == false) {

					for (auto i = _owner.GetActorServer().GetActors().begin(); i != _owner.GetActorServer().GetActors().end(); i++) {

						//エネミーではなかったら次へ
						if ((*i)->GetTypeId() != TypeId::Enemy) {

							//プレイヤーではなかったら次へ
							if ((*i)->GetTypeId() != TypeId::Player) {
								continue;
							}
							else {

								if ((*i)->IsHucked()) {

									continue;

								}
								else {

									//プレイヤーが円で敵のAABBとの当たり判定
									if (_owner._collision->CircleToOrientedAABB(**i, _owner)) {

										//*se ダメージ
										_owner.GetGame().GetSoundComponent().Play("damage");

										//プレイヤーのゲージを減少させる
										(*i)->GetGaugeBase().DownGauge(15);
										(*i)->GetGaugePlayer().DownGauge(15);

										//プレイヤーを無敵時間にする
										//_invincibleTime = true;

										//プレイヤーのダメージフラグを設定
										Flag::FlagData::SetDamageFlag(true);

										//プレイヤーをダメージ状態に変更
										(*i)->GetState().GoToState("Damage");

									}

								}


							}

						}
						else {


							//ハッキングされているか
							if ((*i)->IsHucked()) {

								//ハッキングされている敵が円で敵のAABBとの当たり判定
								if (_owner._collision->CircleToOrientedAABB(**i, _owner)) {

									//ハッキングされている敵のゲージを減少させる
									(*i)->GetGaugeBase().DownGauge(15);
									(*i)->GetGaugeEnemy().DownGauge(15);

									//ハッキングされている敵をダメージ状態に変更
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
		////プレイヤーの無敵時間をリセット
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
		//// ハッキングされたか確認
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

		// 右移動と左移動
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

		// 前進と後退
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
			_owner.GetModelAnime().ChangeAnime("Walk", true);//頭取れたときに移動する
		}
		else {
			_owner.GetModelAnime().ChangeAnime("Idle", true);
		}

		//// ハッキングされたか確認
		//_owner.HitCheckFrom();
		//if (_owner.GetActorState() != ActorState::Hucked)
		//{
		//	_owner._state->GoToState("Run");
		//	_owner._status = STATUS::CHASE;
		//}
		auto headPos = _owner.GetModelAnime().GetHeadPos("Character1_Head");
		Flag::FlagData::SetHeadPos(headPos);

		if (Flag::FlagData::GetHuckDamageFlag()) {

			//ダメージフラグをオフに
			Flag::FlagData::SetHuckDamageFlag(false);

			//無敵フラグをオンに
			Flag::FlagData::SetHuckNoDamageFlag(true);

			_huckNoDamageTime = 120;

		}

		_huckNoDamageTime--;

		//無敵時間が終わったら元に戻す
		if (_huckNoDamageTime < 0 && Flag::FlagData::GetHuckNoDamageFlag()) {
			Flag::FlagData::SetHuckNoDamageFlag(false);
		}


		//移動時にフロアの壁との判定を取る
		Math::Vector4 oldPos = _owner.GetPosition();


		_owner.HuckedMove(_lx, _ly);

		//ギミックと触れているか触れていたら戻す
		//_owner.CollisionGimmick();

		////地面と触れているかどうか
		_owner.CollisionFloor(oldPos, _owner.GetR());

		//ワープ直後か
		if (!_warping) {

			auto dxPos = _owner.WarpFloor(_owner);

			//フェード用に保存
			_fadePos = { dxPos.x, dxPos.y, dxPos.z };

			//現在位置のステージ番号のワープナビメッシュに当たった場合
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

				//ここにフェードイン処理

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



		//ゲージが0かどうか
		if (_owner.GetGaugeBase().IsGaugeZero(_owner)) {

			_owner._state->GoToState("Die");
			_owner._status = STATUS::DYING;
			//*se 破壊される
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

		//ハッキングされているかどうか
		if (!_owner.IsHucked())
		{
			_owner._state->GoToState("Die");
			_owner._status = STATUS::DYING;
		}


	}
}


