/*****************************************************************//**
 * @file   Actor.cpp
 * @brief  アクタークラス
 *
 * @author yamawaki kota
 * @date   December 19 2021
 *********************************************************************/

#include "AppFrame.h"
#include "Actor.h"
#include "ActorServer.h"
#include "../Camera/CameraComponent.h"
#include "../Model/ModelAnimComponent.h"
#include "../State/StateComponent.h"
#include "../Collision/CollisionComponent.h"
#include "../Gauge/GaugeBase.h"

namespace MachineHuck::Actor {

	Actor::Actor(AppFrame::Game& game) : _game{ game }
	{
		_collision = std::make_unique<Collision::CollisionComponent>(*this);
		_gaugeBase = std::make_unique<Gauge::GaugeBase>(*this);
	}

	Actor::~Actor() {

	}

	//CollisionComponent& Actor::GetCollision() 
	//{
	//	return *_collision;
	//}

	void Actor::ComputeWorldTransform() {
		auto world = MGetScale(ToDX(_scale));
		world = MMult(world, MGetRotZ(static_cast<float>(_rotation.GetZ())));
		world = MMult(world, MGetRotX(static_cast<float>(_rotation.GetX())));
		world = MMult(world, MGetRotY(static_cast<float>(_rotation.GetY())));
		_worldTransform = MMult(world, MGetTranslate(ToDX(_position)));
	}

	//bool Actor::CollisionFloor(AppFrame::Math::Vector4 oldPos, int num) {


	//	// 移動した先でコリジョン判定
	//	MV1_COLL_RESULT_POLY hitPoly;

	//	//auto handle = GetGame().GetAssetServer().GetModel("Dungeon");

	//	//AssetServerの方に数字でハンドルを取得できるようにする
	//	//ここのハンドルをステージのみ番号で取得できるようにする
	//	auto handle = GetGame().GetAssetServer().GetMap(num);
	//	//↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑ここに書く

	//	//auto handle = GetGame().GetAssetServer().GetModel(handleName);

	//	for (auto i = GetActorServer().GetActors().begin(); i != GetActorServer().GetActors().end(); i++) {

	//		if ((*i)->GetTypeId() != TypeId::Stage) {
	//			continue;
	//		}
	//		else {

	//			

	//			//auto frameMapCollision = (*i)->GetCollision().GetMapCollision();
	//			//ハンドルのコリジョン情報を取得
	//			auto frameMapCollision = (*i)->GetCollision().GetMapCollision(handle.first);
	//			//auto frameMapCollision = (*i)->GetCollision().GetMapCollision(handle.first);

	//			Math::Vector4 dif = { 0.0, 50.0, 0.0 };
	//			Math::Vector4 under = { 0.0, -99999.0, 0.0 };
	//			auto startPos = _position + dif;
	//			auto endPos = _position + under;
	//			// 主人公の腰位置から下方向への直線
	//			
	//			hitPoly = MV1CollCheck_Line(handle.first, frameMapCollision, ToDX(startPos), ToDX(endPos));

	//			if (hitPoly.HitFlag) {
	//				// 当たった
	//				// 当たったY位置をキャラ座標にする
	//				_position = { _position.GetX(), hitPoly.HitPosition.y, _position.GetZ() };

	//				return true;
	//			}
	//			else {
	//				// 当たらなかった。元の座標に戻す
	//				_position = oldPos;


	//				return false;
	//			}

	//		}

	//	}

	//	return false;

	//}

	//bool Actor::WarpFloor(int num) {

	//	//// 移動した先でコリジョン判定
	//	MV1_COLL_RESULT_POLY hitPoly;

	//	//auto handle = GetGame().GetAssetServer().GetModel("Dungeon");

	//	//AssetServerの方に数字でハンドルを取得できるようにする
	//	//ここのハンドルをステージのみ番号で取得できるようにする
	//	auto handle = GetGame().GetAssetServer().GetMap(num);
	//	//↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑ここに書く

	//	//auto handle = GetGame().GetAssetServer().GetModel(handleName);

	//	for (auto i = GetActorServer().GetActors().begin(); i != GetActorServer().GetActors().end(); i++) {

	//		if ((*i)->GetTypeId() != TypeId::Stage) {
	//			continue;
	//		}
	//		else {

	//			auto keys = (*i)->GetCollision().GetWarpName(handle.first);

	//			//auto frameMapCollision = (*i)->GetCollision().GetMapCollision();
	//			for (auto keyStr : keys){
	//			
	//				//ハンドルのコリジョン情報を取得
	//				auto frameMapCollision = (*i)->GetCollision().GetWarpCollision(keyStr, handle.first);
	//				//auto frameMapCollision = (*i)->GetCollision().GetMapCollision(handle.first);

	//				Math::Vector4 dif = { 0.0, 50.0, 0.0 };
	//				Math::Vector4 under = { 0.0, -99999.0, 0.0 };
	//				auto startPos = _position + dif;
	//				auto endPos = _position + under;
	//				// 主人公の腰位置から下方向への直線
	//				hitPoly = MV1CollCheck_Line(handle.first, frameMapCollision.second, ToDX(startPos), ToDX(endPos));

	//				if (hitPoly.HitFlag) {
	//					//// 当たった
	//					//// 当たったY位置をキャラ座標にする
	//					//_position = { _position.GetX(), hitPoly.HitPosition.y, _position.GetZ() };

	//					//当たったフレームインデックス
	//					auto frameIndex = hitPoly.FrameIndex;

	//					//ワープ前の触れたフレーム名を取得
	//					std::string name = MV1GetFrameName(handle.first, frameIndex);


	//	                //ワープメッシュ名にあるハイフンを飛ばした数字
	//					auto x = name.substr(3, 2);

	//					auto xStr = x;
	//					xStr.substr(0, 1);

	//					if (xStr != "0") {
	//						x = x.substr(1, 1);
	//					}

	//					int xNum = std::atoi(x.c_str());

	//					//ワープメッシュ名にあるハイフンを飛ばした数字
	//					auto y = name.substr(5, 2);
	//					auto yStr = y;
	//					yStr.substr(0, 1);


	//					if (yStr != "0") {
	//						y = y.substr(1, 1);
	//					}

	//					int yNum = std::atoi(y.c_str());

	//					//フロア番号計算
	//					auto floorNum = yNum * 10 + xNum;

	//					//ワープ先のフレーム名
	//					auto toWarpName  = (*i)->GetCollision().GetWarpNameFloor(floorNum, name);

	//					//ワープ先のステージ番号
	//					auto warpStageNum = (*i)->GetCollision().GetFloorStageNum(floorNum);
	//					
	//					//ワープ先のハンドル
	//					auto toWarpHandle = GetGame().GetAssetServer().GetMap(warpStageNum);

	//					//ワープ先のフレームインデックス
	//					int toWarpFrameIndex = MV1SearchFrame(toWarpHandle.first, toWarpName.c_str());
	//					
	//					//ワープ先の位置を取得
	//					auto pos = MV1GetFramePosition(toWarpHandle.first, toWarpFrameIndex);

	//					//_position = { static_cast<double>(pos.x),  static_cast<double>(pos.y) , static_cast<double>(pos.z) };
	//					_position = {0.0, 0.0, 0.0};

	//					return true;
	//				}
	//				else {

	//					return false;
	//				}
	//			
	//			}

	//		}

	//	}


	//	return false;
	//}

	bool Actor::CollisionFloor(AppFrame::Math::Vector4 oldPos) {


		// 移動した先でコリジョン判定
		MV1_COLL_RESULT_POLY hitPoly;

		//auto handle = GetGame().GetAssetServer().GetModel("Dungeon");

		//AssetServerの方に数字でハンドルを取得できるようにする
		//ここのハンドルをステージのみ番号で取得できるようにする
		//auto handle = GetGame().GetAssetServer().GetMap(num);




		for (auto i = GetActorServer().GetActors().begin(); i != GetActorServer().GetActors().end(); i++) {

			if ((*i)->GetTypeId() != TypeId::Stage) {
				continue;
			}
			else {

				//全フロアマップを取得
				auto allFloorMap = (*i)->GetCollision().GetAllFloorMap();

				//触れているフロア番号を取得
				auto floorNums = (*i)->GetCollision().GetFloorNum();


				for (auto&& floorNum : floorNums) {



					for (auto&& floor : allFloorMap[floorNum]) {

						auto&& handle = floor->GetHandle();



						//auto frameMapCollision = (*i)->GetCollision().GetMapCollision();
						//ハンドルのコリジョン情報を取得
						auto frameMapCollision = (*i)->GetCollision().GetMapCollision(handle);
						//auto frameMapCollision = (*i)->GetCollision().GetMapCollision(handle.first);

						Math::Vector4 dif = { 0.0, 50.0, 0.0 };
						Math::Vector4 under = { 0.0, -99999.0, 0.0 };
						auto startPos = _position + dif;
						auto endPos = _position + under;
						// 主人公の腰位置から下方向への直線

						hitPoly = MV1CollCheck_Line(handle, frameMapCollision, ToDX(startPos), ToDX(endPos));

						if (hitPoly.HitFlag) {
							// 当たった
							// 当たったY位置をキャラ座標にする
							_position = { _position.GetX(), hitPoly.HitPosition.y, _position.GetZ() };

							return true;
						}
						else {
							// 当たらなかった。元の座標に戻す
							_position = oldPos;


							return false;
						}
					}
				}

			}

		}

		return false;



	}

	VECTOR Actor::WarpFloor() {

		//// 移動した先でコリジョン判定
		MV1_COLL_RESULT_POLY hitPoly;


		for (auto i = GetActorServer().GetActors().begin(); i != GetActorServer().GetActors().end(); i++) {

			if ((*i)->GetTypeId() != TypeId::Stage) {
				continue;
			}
			else {

				//全フロアマップを取得
				auto allFloorMap = (*i)->GetCollision().GetAllFloorMap();

				//触れているフロア番号を取得
				auto floorNums = (*i)->GetCollision().GetFloorNum();


				for (auto&& floorNum : floorNums) {



					for (auto&& floor : allFloorMap[floorNum]) {

						auto&& handle = floor->GetHandle();

						auto keys = (*i)->GetCollision().GetWarpName(handle);

						//auto frameMapCollision = (*i)->GetCollision().GetMapCollision();
						for (auto keyStr : keys) {

							//ハンドルのコリジョン情報を取得
							auto frameMapCollision = (*i)->GetCollision().GetWarpCollision(keyStr, handle);
							//auto frameMapCollision = (*i)->GetCollision().GetMapCollision(handle.first);

							Math::Vector4 dif = { 0.0, 50.0, 0.0 };
							Math::Vector4 under = { 0.0, -99999.0, 0.0 };
							auto startPos = _position + dif;
							auto endPos = _position + under;
							// 主人公の腰位置から下方向への直線
							hitPoly = MV1CollCheck_Line(handle, frameMapCollision.second, ToDX(startPos), ToDX(endPos));

							if (hitPoly.HitFlag) {
								//// 当たった
								//// 当たったY位置をキャラ座標にする
								//_position = { _position.GetX(), hitPoly.HitPosition.y, _position.GetZ() };


									//当たったフレームインデックス
								auto frameIndex = hitPoly.FrameIndex;

								//ワープ前の触れたフレーム名を取得
								std::string name = MV1GetFrameName(handle, frameIndex);


								//ワープメッシュ名にあるハイフンを飛ばした数字
								auto x = name.substr(3, 2);

								auto xStr = x;
								xStr.substr(0, 1);

								if (xStr != "0") {
									x = x.substr(1, 1);
								}

								int xNum = std::atoi(x.c_str());

								//ワープメッシュ名にあるハイフンを飛ばした数字
								auto y = name.substr(6, 2);
								auto yStr = y;
								yStr.substr(0, 1);


								if (yStr != "0") {
									y = y.substr(1, 1);
								}

								int yNum = std::atoi(y.c_str());

								//フロア番号計算
								auto floorNum = yNum * 10 + xNum;

								//ワープ先のフレーム名
								auto toWarpName = (*i)->GetCollision().GetWarpNameFloor(floorNum, name);

								////ワープメッシュ名にあるハイフンを飛ばした数字
								//x = toWarpName.substr(3, 2);

								//xStr = x;
								//xStr.substr(0, 1);

								//if (xStr != "0") {
								//	x = x.substr(1, 1);
								//}

								//xNum = std::atoi(x.c_str());

								////ワープメッシュ名にあるハイフンを飛ばした数字
								//y = toWarpName.substr(6, 2);
								//yStr = y;
								//yStr.substr(0, 1);


								//if (yStr != "0") {
								//	y = y.substr(1, 1);
								//}

								//yNum = std::atoi(y.c_str());

								////フロア番号計算
								//auto warpFloorNum = yNum * 10 + xNum;


								////ワープ先のステージ番号
								//auto warpStageNum = (*i)->GetCollision().GetFloorStageNum(floorNum);

								////ワープ先のハンドル
								//auto toWarpHandle = GetGame().GetAssetServer().GetMap(warpStageNum);

								//ワープ先のフロア番号のポインタ配列を取得
								auto warpFloor = allFloorMap[floorNum];


								if (warpFloor.empty()) {

									printfDx("ワープフロアポインタが存在しない");
									return VGet(0.0f, 0.0f, 0.0f);

								}

								//ワープ先のポインタを取得
								auto warp = warpFloor[0];

								//ワープ先のハンドルを取得
								auto warpHandle = warp->GetHandle();

								//ワープ先のフレームインデックス
								int toWarpFrameIndex = MV1SearchFrame(warpHandle, toWarpName.c_str());


								//ワープ先の位置を取得
								auto pos = MV1GetFramePosition(warpHandle, toWarpFrameIndex);

								//_position = { static_cast<double>(pos.x),  static_cast<double>(pos.y) , static_cast<double>(pos.z) };

								return pos;

							}

						}

						return VGet(0.0f, 0.0f, 0.0f);
					}
				}


			}

		}


		return VGet(0.0f, 0.0f, 0.0f);
	}

	//ワープ中の当たり判定
	bool Actor::WarpingFloor() {

		//// 移動した先でコリジョン判定
		MV1_COLL_RESULT_POLY hitPoly;


		for (auto i = GetActorServer().GetActors().begin(); i != GetActorServer().GetActors().end(); i++) {

			if ((*i)->GetTypeId() != TypeId::Stage) {
				continue;
			}
			else {

				//全フロアマップを取得
				auto allFloorMap = (*i)->GetCollision().GetAllFloorMap();

				//触れているフロア番号を取得
				auto floorNums = (*i)->GetCollision().GetFloorNum();


				for (auto&& floorNum : floorNums) {



					for (auto&& floor : allFloorMap[floorNum]) {

						auto&& handle = floor->GetHandle();

						auto keys = (*i)->GetCollision().GetWarpName(handle);

						//auto frameMapCollision = (*i)->GetCollision().GetMapCollision();
						for (auto keyStr : keys) {

							//ハンドルのコリジョン情報を取得
							auto frameMapCollision = (*i)->GetCollision().GetWarpCollision(keyStr, handle);
							//auto frameMapCollision = (*i)->GetCollision().GetMapCollision(handle.first);

							Math::Vector4 dif = { 0.0, 50.0, 0.0 };
							Math::Vector4 under = { 0.0, -99999.0, 0.0 };
							auto startPos = _position + dif;
							auto endPos = _position + under;
							// 主人公の腰位置から下方向への直線
							hitPoly = MV1CollCheck_Line(handle, frameMapCollision.second, ToDX(startPos), ToDX(endPos));

							if (hitPoly.HitFlag) {
								//// 当たった
								return true;

							}
							else {

								return false;
							}

						}
					}
				}


			}

		}


		return false;
	}

	ActorServer& Actor::GetActorServer() {
		return _game.GetActorServer();
	}

	void Actor::SetStateComponent(std::unique_ptr<State::StateComponent> state) {
		_state = std::move(state);
	}

	void Actor::SetModelComponent(std::unique_ptr<Model::ModelAnimeComponent> model) {
		_model = std::move(model);
	}

	void Actor::SetCameraComponent(std::shared_ptr<Camera::CameraComponent> camera) {
		_camera = camera;
	}
}

