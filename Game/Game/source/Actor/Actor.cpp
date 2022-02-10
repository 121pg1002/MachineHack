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
#include "../Gauge/GaugeEnemy.h"
#include "../Gauge/GaugePlayer.h"
#include "../Gimmick/GimmickBase.h"
#include "../Flag/FlagData.h"

namespace MachineHuck::Actor {

	Actor::Actor(AppFrame::Game& game) : _game{ game }
	{
		_collision = std::make_unique<Collision::CollisionComponent>(*this);
		_gaugeBase = std::make_unique<Gauge::GaugeBase>(*this);
		_gaugeEnemy = std::make_unique<Gauge::GaugeEnemy>(*this);
		_gaugePlayer = std::make_unique<Gauge::GaugePlayer>(*this);
		//_gimmickBase = std::make_unique<Gimmick::GimmickBase>(*this);

	}

	Actor::~Actor() {

	}

	void Actor::Draw() {
		DrawLine3D(ToDX(_startPos), ToDX(_endPos), GetColor(0, 255, 255));
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

	bool Actor::CollisionFloor() {

		// 移動した先でコリジョン判定
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

						//auto frameMapCollision = (*i)->GetCollision().GetMapCollision();
						//ハンドルのコリジョン情報を取得
						auto frameMapCollision = (*i)->GetCollision().GetMapCollision(handle);
						//auto frameMapCollision = (*i)->GetCollision().GetMapCollision(handle.first);

						Math::Vector4 up = { 0.0, 99.0, 0.0 };
						Math::Vector4 under = { 0.0, -99999.0, 0.0 };
						auto startPos = _position + up;
						auto endPos = _position + under;
						// 主人公の腰位置から下方向への直線
						hitPoly = MV1CollCheck_Line(handle, frameMapCollision, ToDX(startPos), ToDX(endPos));



						if (hitPoly.HitFlag) {
							_position = { _position.GetX(), hitPoly.HitPosition.y, _position.GetZ() };

							return true;
						}
						else {

							return false;
						}
					}
				}

			}

		}


		return false;
	}

	bool Actor::CollisionFloor(AppFrame::Math::Vector4 oldPos, double r) {


		// 移動した先でコリジョン判定
		MV1_COLL_RESULT_POLY hitPoly;

		//MV1_COLL_RESULT_POLY hitPolyX;
		//MV1_COLL_RESULT_POLY hitPolyZ;
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

						Math::Vector4 up = { 0.0, 99.0, 0.0 };
						Math::Vector4 under = { 0.0, -99999.0, 0.0 };
						auto startPos = _position + up;
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

							//// 当たらなかった。元の座標に戻す
							_position = oldPos;


							return false;
						}
					}
				}

			}

		}

		return false;



	}

	bool Actor::CollisionGimmick() {

		// 移動した先でコリジョン判定
		MV1_COLL_RESULT_POLY hitPoly;

		for (auto i = GetActorServer().GetActors().begin(); i != GetActorServer().GetActors().end(); i++) {

			if ((*i)->GetTypeId() != TypeId::Gimmick) {
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
						auto frameGimmickCollision = (*i)->GetCollision().GetGimmickCollision(handle);
						//auto frameMapCollision = (*i)->GetCollision().GetMapCollision(handle.first);

						Math::Vector4 up = { 0.0, 99.0, 0.0 };
						Math::Vector4 under = { 0.0, -99999.0, 0.0 };
						auto startPos = _position + up;
						auto endPos = _position + under;
						// 主人公の腰位置から下方向への直線
						hitPoly = MV1CollCheck_Line(handle, frameGimmickCollision, ToDX(startPos), ToDX(endPos));



						if (hitPoly.HitFlag) {
							_position = { _position.GetX(), hitPoly.HitPosition.y, _position.GetZ() };

							return true;
						}
						else {

							return false;
						}
					}
				}

			}

		}


		return false;
	}

	//壊せる壁と当たっているか
	bool Actor::CollisionWall(Actor& gimmick, Math::Vector4 move) {

		//// 移動した先でコリジョン判定
		MV1_COLL_RESULT_POLY hitPoly;

		for (auto i = GetActorServer().GetActors().begin(); i != GetActorServer().GetActors().end(); i++) {

			if ((*i)->GetTypeId() != TypeId::Stage) {
				continue;
			}
			else {
				//壊せる壁のハンドル
				auto handle = gimmick.GetModel().GetHandle();

				//壊せる壁のハンドルを取得
				//auto&&[handle, actNo] = gimmick.GetGame().GetAssetServer().GetModel("BrokenWall");
				//(*i)->GetGame().GetAssetServer().
				//ギミックのコリジョンフレームを取得
				//auto gimmickFrameCollision = (*i)->GetCollision().GetGimmickCollision(handle);

				
				//auto frameGimmick = gimmick.GetActorServer().GetGimmickCollision(handle);
				auto frameGimmick = GetGame().GetActorServer().GetGimmickCollision(handle);
				//auto gimmickMap = gimmick.GetModel().GetModelGimmick();

				//auto frameGimmick = gimmickMap[handle];
				Math::Vector4 yDif = { 0.0, 10.0, 0.0 };

				auto startPos = _position + move * 100 + yDif;
				auto endPos = _position + yDif;
				// 主人公の腰位置から前方向への直線
				hitPoly = MV1CollCheck_Line(handle, frameGimmick, ToDX(startPos), ToDX(endPos));

#ifdef _DEBUG
				_startPos = startPos;
				_endPos = endPos;
#endif 

				if (hitPoly.HitFlag) {
					//// 当たった
					_judge = true;
					return true;

				}
				else {
					_judge = false;
					return false;
				}

			}
		}

		return false;
	}

	VECTOR Actor::WarpFloor(Actor& act) {

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

								//ブロックとコリジョンを除く
								if (frameIndex != 0 && frameIndex != 1) {

									//ワープ前の触れたフレーム名を取得
									std::string name = MV1GetFrameName(handle, frameIndex);



									//ダクトかどうか
									if (name.size() > 8) {

										std::string::size_type nameParts = name.find("entry");

										//存在した
										if (nameParts != std::string::npos) {

											//ハッキング状態か
											if (act.IsHucked()) {
												return VGet(0.0f, 0.0f, 0.0f);
											}
											else {
												//ダクトフラグを設定
												Flag::FlagData::SetDuctWarp(true);
											}

										}


									}

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

									return pos;
								
								
								}



								//_position = { static_cast<double>(pos.x),  static_cast<double>(pos.y) , static_cast<double>(pos.z) };

								

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

								//文字列の数がダクトの出口サイズ(2文字)ではないか
								if (keyStr.size() > 3) {
								
									//// 当たった
									return true;
								}
								else {

									if (Flag::FlagData::GetDuctWarp()) {
										return true;
									}
									continue;
								}


							}
							else {

								continue;
							}

						}

						return false;
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

	void Actor::SetModelAnimeComponent(std::unique_ptr<Model::ModelAnimeComponent> model) {
		_modelAnime = std::move(model);
	}

	void Actor::SetModelComponent(std::unique_ptr<Model::ModelComponent> model) {
		_model = std::move(model);
	}

	void Actor::SetCameraComponent(std::shared_ptr<Camera::CameraComponent> camera) {
		_camera = camera;
	}
}

