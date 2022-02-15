#include "CatchEnemy.h"
#include "AppFrame.h"
#include "../Actor/ActorServer.h"
#include "../Model/ModelAnimComponent.h"
#include "../Collision/CollisionComponent.h"
#include "../Gauge/GaugeBase.h"
#include "../Gauge/GaugePlayer.h"
#include "../Gauge/GaugeEnemy.h"
#include "../Flag/FlagData.h"
#include "EnemyParameter.h"


namespace MachineHuck::Enemy {

	//静的なメンバ―変数を実体化させる
	int CatchEnemy::StateBase::_huckNoDamageTime;

	CatchEnemy::CatchEnemy(AppFrame::Game& game) : EnemyBase{ game } {

		_r = 0.0;
		_huckR = 0.0;
		_catchR = 0.0;
		//_minXZ = { -200.0, -100.0 };
		//_maxXZ = { 200.0, 100.0 };
		//_lmin = { 0.0, -100.0, 0.0 };
		//_lmax = { 0.0, 100.0, 0.0 };
		_status = STATUS::WAIT;
		_searchRange = 0.0;
		_huckingRange = 0.0;
		_catchRange = 0.0;
		//_gaugeBase->Init();
		//_gaugeEnemy->Init(*this);


	}

	void CatchEnemy::LoadJson(const std::string& filePath) {

		auto eParam = std::make_unique<EnemyParameter>();
		eParam->LoadEnemyParam(filePath);

		//2つめの値がレベル
		_r = eParam->GetEnemyParam("r", 0);
		_r = 150.0;
		//_huckR = eParam->GetEnemyParam("r", 1);
		_huckR = 200.0;

		_catchR = 300.0;

		_collisionR = 50.0;

		_catchRange = eParam->GetEnemyParam("searchrange", 1);
		_searchRange = eParam->GetEnemyParam("searchrange", 1);
		_huckingRange = eParam->GetEnemyParam("searchrange", 0);////////←とりあえず、仮

	}

	void CatchEnemy::Update() {

		//死亡中ではない
		if (_status != STATUS::DYING) {


			if (GetActorState() == ActorState::Hucking) {
				_status = STATUS::ISHUCKING;
			}
			else if (IsHucked()) {
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
			Move("CatchEnemy", _routine, 2.0, _numRange);
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

	void CatchEnemy::HuckedRotation(double lx, double ly) {


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
		auto dirX = std::cos(rad) * length;

		//z軸方向の移動量
		auto dirZ = std::sin(rad) * length;

		Math::Vector2 direction = { dirX, dirZ };


		if (direction.Length() > 0.0) {

			auto yRot = std::atan2(direction.GetX(), direction.GetZ());

			Math::Vector4 rot = { 0.1, yRot, 0.0 };
			SetRotation(rot);

			//移動していたら減らす
			//GetGaugeBase().Update(*this);
			//GetGaugeEnemy().Update(*this);
			GetGame().GetGaugeBaseUI().Update();
			GetGame().GetGaugeEnemyUI().Update();

		}



	}

	void CatchEnemy::Input(AppFrame::Input::InputComponent& input) {
		_state->Input(input);
	}

	void CatchEnemy::Draw() {
		// 足のトゲの為のアルファテスト設定
		MV1SetMaterialDrawAlphaTest(_modelAnime->GetHandle(), 3, TRUE, DX_CMP_LESS, 200);
#ifdef _DEBUG
		//auto pos = _position;
		//pos.y += 40;
		//DrawSphere3D(pos, 50, 16, GetColor(255, 0, 0), GetColor(0, 0, 0), TRUE);
		_modelAnime->Draw(*this, _isHit, _searchRange, true);
		_modelAnime->Draw(*this, _isHit, _huckingRange, false);
		_modelAnime->Draw(*this, _catchR, _catchRange);
		_modelAnime->DrawCircle(*this, _collisionR);
		_modelAnime->Draw(*this, GetActorServer().GetPosition("Player"));

		//_gaugeBase->Draw(*this);
#endif
		_state->Draw();

		//_gaugeEnemy->Draw(*this);
	}

	void CatchEnemy::StateBase::Draw() {

		if (_owner.GetStatus() != STATUS::ISHUCKED) {
			_owner.GetModelAnime().Draw();
		}
		else {
			_owner.GetModelAnime().SpecificDraw(); //!<	ハッキング中の頭を描画停止する
		}
	}

	// 待機
	void CatchEnemy::StateSearch::Enter() {
		_owner.GetModelAnime().ChangeAnime("Idle", true);
	}

	void CatchEnemy::StateSearch::Update() {

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
	void CatchEnemy::StateIdle::Enter() {
		_owner.GetModelAnime().ChangeAnime("Idle", true);
	}

	void CatchEnemy::StateIdle::Update() {


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

				//敵が扇形でプレイヤーが点
				if (_owner._collision->FanToPoint(_owner, **i, _owner.GetR(), _owner.GetSearchRange())) {
					_owner._state->GoToState("CatchPre");
					_owner._status = STATUS::CHASE;
				}

			}
		}
	}

	//プレイヤーを見つけた後の攻撃前
	void CatchEnemy::StateCatchPre::Enter() {
		_owner.GetModelAnime().ChangeAnime("Idle", true);
	}

	//void CatchEnemy::StateCatchPre::Input(AppFrame::Input::InputComponent& input) {
	//
	//	//if(input.)

	//}

	void CatchEnemy::StateCatchPre::Update() {

		//ハッキングされているか
		if (_owner.IsHucked()) {

			auto rot = _owner.GetRotation();

			//z軸を0度とする
			auto nine = DX_PI * 90.0 / 180.0;

			//主人公の回転方向は反対向きのためマイナス
			Math::Vector4 move = { std::cos(-rot.GetY() + nine), 0.0, std::sin(-rot.GetY() + nine) };


		}
		else {//通常時

			//向きのみプレイヤーの方に向く
			auto player = _owner.GetActorServer().GetPosition("Player");
			auto dif = player - _owner.GetPosition();

			auto rotY = std::atan2(dif.GetX(), dif.GetZ());
			Math::Vector4 rot = { 0.5, rotY, 0.0 };
			_owner.SetRotation(rot);

			auto length = dif.Length_XZ();

			//キャッチの範囲内プレイヤーがいるなら攻撃待機時間を減らす
			if (length < _owner._catchR) {
				_catchPreTime--;
			}
			else {
				_catchPreTime = 20;
			}

			//攻撃待機時間が0になったか
			if (_catchPreTime < 0) {

				_owner._state->GoToState("Catch");

			}



		}



	}


	bool CatchEnemy::StateCatchPre::IsLoseSight() {

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

	void CatchEnemy::StateCatch::Enter() {


		_catchTime = 60;

		//ハッキングされている場合
		if (_owner.GetStatus() == STATUS::ISHUCKED) {

			//ゲージ減少
	/*		_owner.GetGaugeBase().DownGauge(20);
			_owner.GetGaugeEnemy().DownGauge(20);*/
			_owner.GetGame().GetGaugeBaseUI().DownGauge(20);
			_owner.GetGame().GetGaugeEnemyUI().DownGauge(20);

			//auto player = _owner.GetActorServer().GetDir("Player");

			//auto rot = _owner.GetRotation();

			////z軸を0度とする
			//auto nine = DX_PI * 90.0 / 180.0;

			//仕様書より6m/s
			//auto length = 600.0;

			////主人公の回転方向は反対向きのためマイナス
			//Math::Vector4 move = { std::cos(-rot.GetY() + nine), 0.0, std::sin(-rot.GetY() + nine) };

			////向きを設定
			//_owner.SetRotation(rot);

			////目線の先に目標をつくる
			//auto forward = move * length;


			//_norm = forward.Normalize();



		}
		//else {

		//	//追跡中
		//	auto player = _owner.GetActorServer().GetPosition("Player");
		//	player = { player.GetX(), 0.0, player.GetZ() };
		//	auto dif = player - _owner.GetPosition();
		//	//auto length = dif.Length_XZ();

		//	auto rotY = std::atan2(dif.GetX(), dif.GetZ());
		//	Math::Vector4 rot = { 0.0, rotY, 0.0 };
		//	_owner.SetRotation(rot);


		//}

		_owner.GetModelAnime().ChangeAnime("Catch", true);
	}

	void CatchEnemy::StateCatch::Update() {

		if (_catchTime < 0) {
			_owner._state->GoToState("CatchAfter");
		}
		else {

			////ハッキングされているか(追跡時の行動を省く)
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

							//自分(ハッキング中のキャッチ)の扇形と相手エネミーの点
							if (_owner._collision->FanToPoint(_owner, **i, _owner._catchR, _owner._catchRange)) {

								(*i)->SetActorState(ActorState::Dead);

							}

						}

					}
				}


			}//自分が追跡状態のとき
			else {

				//無敵時間中とダメージフラグがオンのときは、通さない
				if (Flag::FlagData::GetNoDamageFlag() == false && Flag::FlagData::GetDamageFlag() == false) {

					//ハッキングの無敵時間中とハッキングダメージフラグがオンのときは通さない
					if (Flag::FlagData::GetHuckDamageFlag() == false && Flag::FlagData::GetHuckNoDamageFlag() == false) {

						for (auto i = _owner.GetActorServer().GetActors().begin(); i != _owner.GetActorServer().GetActors().end(); i++) {

							if ((*i)->GetTypeId() != TypeId::Enemy) {

								//プレイヤーではなかったら次へ
								if ((*i)->GetTypeId() != TypeId::Player) {
									continue;
								}
								else {
									//プレイヤーがハッキング状態か
									if ((*i)->IsHucked()) {

										continue;
									}
									else {

										//プレイヤーが点で敵の扇形の当たり判定
										if (_owner._collision->FanToPoint(_owner, **i, _owner._catchR, _owner._catchRange)) {

											//プレイヤーのゲージを減少させる
										//	(*i)->GetGaugeBase().DownGauge(15);
										//	(*i)->GetGaugePlayer().DownGauge(15);
											(*i)->GetGame().GetGaugeBaseUI().DownGauge(15);
											(*i)->GetGame().GetGaugePlayerUI().DownGauge(15);

											//プレイヤーを無敵時間にする
											//_invincibleTime = true;

											//プレイヤーのダメージフラグを設定
											Flag::FlagData::SetDamageFlag(true);

											////プレイヤーをダメージ状態に変更
											(*i)->GetState().GoToState("Damage");

										}

									}


								}
							}
							else {


								//if (!Flag::FlagData::GetHuckNoDamageFlag()) {

									//敵エネミーがハッキングされているか
								if ((*i)->IsHucked()) {

									//ハッキングされている敵が点で敵の扇形との当たり判定
									if (_owner._collision->FanToPoint(_owner, **i, _owner._catchR, _owner._catchRange)) {

										//ハッキングされている敵のゲージを減少させる
										//(*i)->GetGaugeBase().DownGauge(15);
										//(*i)->GetGaugeEnemy().DownGauge(15);
										(*i)->GetGame().GetGaugeBaseUI().DownGauge(15);
										(*i)->GetGame().GetGaugeEnemyUI().DownGauge(15);

										//ハッキングされている敵をダメージ状態に変更
										(*i)->GetState().PushBack("Damage");

										Flag::FlagData::SetHuckDamageFlag(true);
									}


								}
								else {
									continue;
								}

								//}


							}


						}

					}


				}



			}



		}

		_catchTime--;

	}

	void CatchEnemy::StateCatchAfter::Enter() {
		_owner.GetModelAnime().ChangeAnime("Idle", true);
		_catchAfterTime = 120;
	}

	void CatchEnemy::StateCatchAfter::Update() {

		//ハッキング中に体力が0になったか
		//if (_owner.GetGaugeBase().IsGaugeZero(_owner)) {
		if (_owner.GetGame().GetGaugeBaseUI().IsGaugeZero(_owner)) {
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

		if (_catchAfterTime < 0) {

			_owner._state->GoToState("CatchPre");

		}
		else {
			_catchAfterTime--;
		}

	}

	void CatchEnemy::StateFallPre::Enter() {



	}

	void CatchEnemy::StateFallPre::Update() {

		auto holePos = _owner.GetHolePos();
		//Math::Vector4 holePos = { holePos.GetX, static_cast<double>(holePosVECTOR.y), static_cast<double>(holePosVECTOR.z) };
		auto dif = holePos - _owner.GetPosition();

		_norm = dif.Normalize() * 5;

		if (_owner.IsHucked()) {

			auto headPos = _owner.GetModelAnime().GetHeadPos("Character1_Head");
			Flag::FlagData::SetHeadPos(headPos);
			//_owner.SetHuckedMove(_norm);

		}

		_owner._position = _owner.GetPosition() + _norm;

		// ワールド行列の更新
		_owner.ComputeWorldTransform();


		if (holePos.GetX() - 3.0 < _owner.GetPosition().GetX() && _owner._position.GetX() < holePos.GetX() + 3.0 && holePos.GetZ() - 3.0 < _owner.GetPosition().GetZ() && _owner._position.GetZ() < holePos.GetZ() + 3.0) {

			_owner.GetState().GoToState("Fall");

		}

	}

	void CatchEnemy::StateFall::Enter() {

		_owner.GetModelAnime().ChangeAnime("Fall");
	}

	void CatchEnemy::StateFall::Update() {

		if (_owner.GetModelAnime().GetRepeatedCount() > 0) {

			//床との当たり判定を消す
			_owner.SetFallFlag(true);

		}

		if (_owner.GetFallFlag()) {

			//穴に落とす
			Math::Vector4 difY = { 0.0, -10.0, 0.0 };
			_owner._position = _owner.GetPosition() + difY;
			auto headPos = _owner.GetModelAnime().GetHeadPos("Character1_Head");
			Flag::FlagData::SetHeadPos(headPos);

		}

		//_fallCount--;

		if (_owner.GetPosition().GetY() < -500.0) {


			//ハッキング状態か
			if (_owner.IsHucked()) {

				//ここに入ってきた場所の位置を設定
				auto warpAfterPos = Flag::FlagData::GetWarpAfterPos();

				Math::Vector4 pos = { static_cast<double>(warpAfterPos.x), static_cast<double>(warpAfterPos.y), static_cast<double>(warpAfterPos.z) };



				for (auto&& actor : _owner.GetActorServer().GetActors()) {

					if (actor->GetTypeId() != TypeId::Player) {
						continue;
					}
					else {

						actor->SetActorState(ActorState::Active);

						actor->GetState().GoToState("Idle");
						//auto warpAfterPos = Flag::FlagData::GetWarpAfterPos();
						actor->SetPosition(pos);
					}

				}

			}

			_owner.SetActorState(ActorState::Dead);


		}

	}

	//bool CatchEnemy::StateRun::IsViewPlayer() {
	//
	//	_owner.GetPosition();
	//
	//}

	//死亡
	void CatchEnemy::StateDie::Enter() {
		_owner.GetModelAnime().ChangeAnime("Die");
	}

	void CatchEnemy::StateDie::Update() {
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

	//ダメージ
	void CatchEnemy::StateDamage::Enter() {
		_owner.GetModelAnime().ChangeAnime("Damage", true);
	}

	void CatchEnemy::StateDamage::Update() {

		if (_owner.GetModelAnime().GetRepeatedCount() > 0) {

			_owner._state->PopBack();

		}

	}


	void CatchEnemy::StateHucking::Enter()
	{
		_owner.GetModelAnime().ChangeAnime("Hucking", false);
	}

	void CatchEnemy::StateHucking::Update()
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

				auto headPos = _owner.GetModelAnime().GetHeadPos("Character1_Head"); //!< 本当のキャッチの頭のフレームを入れる(仮)
				Flag::FlagData::SetHeadPos(headPos);
			}
		}



	}


	void CatchEnemy::StateHucked::Enter() {
		_owner.GetModelAnime().ChangeAnime("Attack");
	}

	void CatchEnemy::StateHucked::Input(AppFrame::Input::InputComponent& input) {

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

		if (input.GetJoypad().Button_RT()) {

			_owner._state->GoToState("Catch");
		}

	}

	void CatchEnemy::StateHucked::Update() {
		//// ハッキングされたか確認
		//_owner.HitCheckFrom();
		//if (_owner.GetActorState() != ActorState::Hucked)
		//{
		//	_owner._state->GoToState("Run");
		//	_owner._status = STATUS::CHASE;
		//}
		if (_lx != 0.0 || _ly != 0.0) {
			_owner.GetModelAnime().ChangeAnime("Walk", true);//頭取れたときに移動する
		}
		else {
			_owner.GetModelAnime().ChangeAnime("Idle", true);
		}


		auto headPos = _owner.GetModelAnime().GetHeadPos("Character1_Head"); //!< 本当のキャッチの頭のフレームを入れる(仮)
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
		//Math::Vector4 oldPos = _owner.GetPosition();

		//ハッキング中の向き設定
		//_owner.HuckedRotation(_lx, _ly);

		//前フレームの座標を保存
		auto oldPos = _owner.GetPosition();

		//ハッキング中の移動を設定
		_owner.HuckedMove(_lx, _ly);


		
		//壊せる壁と当たっているか
		if (_owner.GetCollision().CollisionBrokenWall(_owner)) {
			_owner._position = oldPos;
		}

		//穴と当たっているか
		if (_owner.GetCollision().CollisionHole(_owner)) {
			_owner.GetState().GoToState("FallPre");
		}

		////地面と触れているかどうか
		if (!_owner.GetFallFlag()) {

			////地面と触れているかどうか
			_owner.CollisionFloor(oldPos, _owner.GetR());
		}
		//	Math::Vector4 zero = { 0.0, 0.0, 0.0 };
		//	//主人公のカメラに移動量を送る
		//	_owner.SetHuckedMove(zero);
		//}
		//else {
		//}

				//ワープ直後か
		if (!_warping) {

			auto dxPos = _owner.WarpFloor(_owner);

			//フェード用に保存
			_fadePos = { dxPos.x, dxPos.y, dxPos.z };

			//現在位置のステージ番号のワープナビメッシュに当たった場合
			if (dxPos.x != 0.0f && dxPos.z != 0.0f) {

				//スライドフラグがオンか
				if (!Flag::FlagData::GetSlideFlag()) {

					Flag::FlagData::SetFadeOutFlag(true);

				}
				else {
					Flag::FlagData::SetSlideOut(true);
				}

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
				if (!Flag::FlagData::GetSlideFlag()) {

					Flag::FlagData::SetFadeInFlag(true);
				}
				else {
					Flag::FlagData::SetSlideIn(true);
					Flag::FlagData::SetSlideFlag(false);
				}

			}

			if (!_owner.WarpingFloor() && _waitFrame < 0) {

				//_position = _fadePos;
				_warping = false;
				auto position = _owner.GetPosition();
				Flag::FlagData::SetWarpAfterPos(ToDX(position));

			}


		}

		_waitFrame--;

		//ゲージが0かどうか
		if (_owner.GetGame().GetGaugeBaseUI().IsGaugeZero(_owner)) {

			_owner._state->GoToState("Die");
			_owner._status = STATUS::DYING;

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
