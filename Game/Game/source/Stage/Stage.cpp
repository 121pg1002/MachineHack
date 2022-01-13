///
/// @file    Stage.cpp
/// @brief   ステージ
/// @date    2021/12/06
/// @author yamawaki kota
/// @copyright (C) Amusement Media Academy All rights Resved.
///

#include "Stage.h"
#include "AppFrame.h"
#include "../Model/ModelComponent.h"
#include "../Actor/ActorServer.h"
#include "StageParameter.h"
#include "../Collision/CollisionComponent.h"


namespace MachineHuck::Stage {
	namespace {

		constexpr int StageAll = 2;        //!< 読み込むstagejsonの数
		constexpr double Differ   = 500.0; //!< 1フロアのサイズ
		constexpr double StartX   = -5.0 * Differ;
		constexpr int BoardSize = 10;

		//constexpr double HalfSize = 0.5 * Differ;
		//constexpr int StartZ = -5.0 * Differ;
	}

	Stage::Stage(AppFrame::Game& game) : Actor::Actor{ game } {
		// スカイスフィアのモデル
		//_skySphere = std::make_unique<ModelComponent>(*this);
		//_skySphere->SetModel("SkySphere");
		//_skySphere->SetScale({ 80.f,  80.f, 80.f });
		//// 地面のモデル
		//_ground = std::make_unique<ModelComponent>(*this);
		//_ground->SetModel("Ground");
		//_ground->SetScale({10.f, 10.f, 10.f});

		//for (int i = 0; i < _boardH; i++) {

		//	for (int k = 0; k < _boardW; k++) {

		//		_board[i * _boardH + k] = 0;

		//	}
		//}

		_stageFloor.clear();
		//_boardStageNum.clear();
		_allFloor.clear();
		//_floor.clear();

		//////とりあえず、↓は仮
		for (int i = 0; i < StageAll; i++) {

			//ステージ番号をstringに変換
			auto no = std::to_string(i);
			//下の二つを起動すればjsonが読み込める
			//auto stageParameter = std::make_unique<StageParameter>();
			game.GetStageParameter().LoadStageParameter(i, "resource/json/stage" + no + ".json");
		}

		game.GetStageParameter().LoadStageTable("resource/json/stagetable.json");
		// 地面のモデル
		//_ground = std::make_unique<ModelComponent>(*this);
		//_ground->SetModel("Ground");
		//_ground->SetScale({10.f, 10.f, 10.f});

		//const auto& stageVector = game.GetStageParameter().GetStageVector();

		//for (int i = 0; i < stageVector.size(); i++) {

		//	auto sP = stageVector[i];
		//	auto pos = sP.GetPosition();
		//	auto rot = sP.GetRotation();
		//	auto scale = sP.GetScale();


		//	auto ground = std::make_unique<Model::ModelComponent>(*this);
		//	ground->SetModel(sP.GetName(), 100);

		//	ground->SetPosition(ToDX(pos));
		//	ground->SetRotation(ToDX(rot));
		//	ground->SetScale(ToDX(scale));

		//	_floor.push_back(std::move(ground));
		//}


		//自分のいるフロアのみ描画
		_stageNo = 1;

		CreateStage(game);

		// フォグの設定
		 //SetFogEnable(TRUE);
		 //SetFogColor(247, 188, 101);
		 //SetFogStartEnd(50.0f, 15000.0f);
	}

	Stage::~Stage() {
		_allFloor.clear();
		//_floor.clear();
	}

	void Stage::Update() {

		auto pos = GetActorServer().GetPosition("Player");
		// スカイスフィアをプレイヤと同じ位置にする
	   //_skySphere->SetPosition(ToDX(pos));

	}

	void Stage::Draw() {
		//_skySphere->Draw();   // スカイスフィア
		//_ground->Draw();      // 地面

		//表示するステージ番号のみ表示
		//キーの数を取得
		auto num = _allFloor.count(_stageNo);

		//if (num != 0) {


			////////////////////////移動中のみ2画面表示するように
			//if (IsMoving()) {
			//
			//
			//}
			//else {


					// equal_range 関数を使って、指定したキーの最初と終端の位置を示すイテレータを std::pair<> で取得します。
					auto[start, end] = _allFloor.equal_range(_stageNo);


					// 取得したイテレータの範囲をループで回します。(仮では10フロア分)
					for (auto iterator = start; iterator != end; iterator++)
					{
						//キーと値のセットを取得
						auto [key, value] = *iterator;

						for (auto j = 0; j < value.size(); j++) {

							//1ブロック分
							value[j]->Draw();
						}
					}
				
			
			//}

		
		//}





		//for (auto j = 0; j < _allFloor.size(); j++) {
		//	_allFloor[j]->Draw();
		//}

		//_allFloor[_stageNo][0]->Draw();
		

	}

	bool Stage::CreateStage(AppFrame::Game& game) {

		auto stageTableVector = game.GetStageParameter().GetStageTableVector();
	
		auto startX = StartX;
		auto startZ = 0.0;

		auto offsetX = startX;
		auto offsetZ = startZ;

		//フロア数
		for (auto i = 0; i < stageTableVector.size(); i++) {
		
			offsetX = startX;
			//1列分のフロア
			for (auto j = 0; j < stageTableVector[i].size(); j++) {
			
				//1列分のj番目の数値
				auto num = stageTableVector[i][j];

				//縦の列が最後の列だけ除く
				if (i != stageTableVector.size() - 1) {
				
					AppFrame::Math::Vector2 min = { static_cast<double>(j) * Differ, static_cast<double>(i) * Differ };
					AppFrame::Math::Vector2 max = { (j + 1) * Differ, (i + 1) * Differ };

					auto stageFloor = std::make_tuple(min, max, num);

					//テーブルの配置位置をキーとした各ステージフロアの
					_stageFloor.emplace(i * BoardSize + j, stageFloor);
				}


				
				//_board[i * _boardH + j] = i * BoardSize + j;
				//_boardStageNum.push_back(num);

				if (num == 0) {
				offsetX += Differ;

				continue;
				}
				//else if (num != ) {
				//
				//}

				//フロア番号と情報を取得
				auto stageNumMap = game.GetStageParameter().GetFloorMap();
				
				//_floor.clear();
				

				//読み込むフロア
				auto stageVector = stageNumMap[num-1];

				Floor floor;
				floor.clear();
				
				//フロアの各ブロック
				for (int i = 0; i < stageVector.size(); i++) {

					auto sP = stageVector[i];
					auto pos = sP.GetPosition();
					Math::Vector4 dif = { offsetX, 0.0, offsetZ };

					//位置にオフセット分足してずらす
					pos = pos + dif;

					auto rot = sP.GetRotation();
					auto scale = sP.GetScale();
					auto ground = std::make_unique<Model::ModelComponent>(*this);
					ground->SetModel(sP.GetName(), 1000);

					ground->SetPosition(ToDX(pos));
					ground->SetRotation(ToDX(rot));
					ground->SetScale(ToDX(scale));

					floor.push_back(std::move(ground));

				}

				offsetX += Differ;
				_allFloor.emplace(num, std::move(floor));
				//_board[i * _boardH + j] = i * 10 + j;
				//_boardStageNum.push_back(num);
			}

			offsetZ += Differ * 2;
			

		}

		return true;
	}

	int Stage::PlayerOnStageNumber() {

		int stageNo = 0;
		std::vector<int> stageNoV;
	
		for (auto i = GetActorServer().GetActors().begin(); i != GetActorServer().GetActors().end(); i++) {
		
			if ((*i)->GetTypeId() != TypeId::Player) {
				continue;
			}
			else {

				//std::vector<int> stageNo;

				for (auto map : _stageFloor) {

					auto [floorNum, tuple] = map;
					auto [min, max, stageNum] = tuple;


					//////////////////////だけど、全てフロアとの判定よりはそもそもminとmaxが離れすぎているやつを処理しないようにしたい
					//主人公と各フロアとの当たり判定を検証
					if (_collision->CircleToAABB((**i), min, max)) {

						stageNoV.push_back(stageNum);

						//if (_collision->LineToAABB(**i, min, max)) {
						//
						//}
					}


				}

			
				
			}


		}




		return stageNo;
	}

	//int Stage::GetBoard(int x, int z) {
	//	return _board[z * _boardH + x];
	//}


	//void Stage::SetBoard(int x, int z, int n) {
	//	_board[z * _boardH + x] = n;
	//}
}
