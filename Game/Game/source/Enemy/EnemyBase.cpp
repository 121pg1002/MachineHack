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

    void EnemyBase::Move(std::string_view enemyName) {
    
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
			if (Math::Vector4 v{ 0.0, 0.0, 0.0 }; forward.GetX() != v.GetX() && forward.GetZ() != v.GetZ()){
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
		/// <summary>
		///仮の動き(左右)
		/// </summary>
		//if (_numberTimes < 100)
		//{
		//	Math::Vector4 move = { 2.0, 0.0, 0.0 };
		//	_position = _position + move;
		//	// Y軸の回転角度を求める※時計回りz⇔x
		//	auto rotY = std::atan2(move.GetX(), move.GetZ());
		//	Math::Vector4 rot = { 0.0, rotY, 0.0 };
		//	SetRotation(rot);

		//}
		//else
		//{
		//	Math::Vector4 move = { -2.0, 0.0, 0.0 };
		//	_position = _position + move;
		//	// Y軸の回転角度を求める※時計回りz⇔x
		//	auto rotY = std::atan2(move.GetX(), move.GetZ());
		//	Math::Vector4 rot = { 0.0, rotY, 0.0 };
		//	SetRotation(rot);
		//}

		//if (_numberTimes > 200)
		//{
		//	_numberTimes = 0;
		//}
		//else
		//{
		//	_numberTimes++;
		//}

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
}