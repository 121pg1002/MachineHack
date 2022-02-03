/*****************************************************************//**
 * @file   EnemyBase.h
 * @brief  エネミーの基底クラス
 *
 * @author hikaru Goto
 * @date   December 19 2021
 *********************************************************************/

#include "EnemyBase.h"
#include "../Actor/ActorServer.h"
#include "../Gauge/GaugeBase.h"
#include "../Gauge/GaugeEnemy.h"

namespace MachineHuck::Enemy {
	//コンストラクタ
	EnemyBase::EnemyBase(AppFrame::Game& game) : Actor::Actor{ game } {
	}
	//デストラクタ
	EnemyBase::~EnemyBase() {
	}

	void EnemyBase::Move(std::string_view enemyName, int num) {

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
				player = { player.GetX(), 0.0, player.GetZ() };
				auto forward = player - _position;
				// プレイヤーに向かう単位ベクトル
				if (Math::Vector4 v{ 0.0, 0.0, 0.0 }; forward.GetX() != v.GetX() && forward.GetZ() != v.GetZ()) {
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
				GetActorServer().Register(enemyName, posDir);


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
		else {


			//索敵中の移動ルーチン
			//RoutineMove(num, 2.0);

		}

		//if (CollisionFloor(_oldPos)) {
		//
		//	int x = 0;
		//}
		CollisionFloor(_oldPos, GetR());

	}
	//ハックした
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


		//ハッキングされたときの移動
	const void EnemyBase::HuckedMove(const double lx, const double ly) {

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
		auto moveX = std::cos(rad) * length;

		//z軸方向の移動量
		auto moveZ = std::sin(rad) * length;

		_move = { moveX, 0.0, moveZ };
		// 移動
		_position = _position + _move;

		if (_move.Length() > 0.0)
		{
			auto dir = _move;
			auto yRot = std::atan2(dir.GetX(), dir.GetZ());

			Math::Vector4 rot = { 0.0, yRot, 0.0 };
			SetRotation(rot);

			//移動していたら減らす
			GetGaugeBase().Update(*this);
			GetGaugeEnemy().Update(*this);
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

	void EnemyBase::RoutineMove(int num, double speed, int numRange) {

		Math::Vector4 move = { 0.0, 0.0, 0.0 };
		double rotY = 0.0;

		//左右移動
		if (num == 1) {

			if (_numberTimes < numRange/2) {
				 move = { speed, 0.0, 0.0 };

			}
			else {
				 move = { -speed, 0.0, 0.0 };


			}


		} //上下移動
		else if (num == 2) {

			if (_numberTimes < numRange/2) {
				 move = { 0.0, 0.0, speed };
			}
			else {
				 move = { 0.0, 0.0, -speed };
			}



		}//回転移動(右回転)
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
		// Y軸の回転角度を求める(時計回りz⇔x)
		rotY = std::atan2(move.GetX(), move.GetZ());

		Math::Vector4 rot = { 0.0, rotY, 0.0 };
		SetRotation(rot);

		//回数をリセット
		if (_numberTimes < 0) {
			_numberTimes = numRange;
		}
		else {
			_numberTimes--;
		}

	}
}