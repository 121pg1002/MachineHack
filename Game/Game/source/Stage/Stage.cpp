/*****************************************************************//**
 * @file   Stage.cpp
 * @brief  ステージ
 *
 * @author yamawaki kota, hikaru goto
 * @date   December 6 2021
 *********************************************************************/


#include "Stage.h"
#include <DxLib.h>
#include "AppFrame.h"
#include "../Model/ModelComponent.h"
#include "../Actor/ActorServer.h"
#include "../Actor/ActorFactory.h"
#include "StageParameter.h"
#include "../Collision/CollisionComponent.h"


namespace MachineHuck::Stage {

	namespace {

		constexpr int StageAll = 10;        //!< 読み込むstagejsonの数
		constexpr double Differ = 3000.0; //!< 1フロアのサイズ
		constexpr double StartX = -5.0 * Differ;
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
		_ground = std::make_unique<Model::ModelComponent>(*this);
		//	_ground->SetMap("Dunge0");
			//VECTOR scale = { 1.0f, 0.1f, 1.0f };
			//_ground->SetScale(scale);
			//_ground->SetScale({1.f, 1.f, 1.f});

			//for (int i = 0; i < _boardH; i++) {

			//	for (int k = 0; k < _boardW; k++) {

			//		_board[i * _boardH + k] = 0;

			//	}
			//}
#ifdef _DEBUG

		_groundVertex.clear();
		_groundIndex.clear();


#endif

		_stageFloor.clear();
		//_boardStageNum.clear();
		//_allFloor.clear();
		_allFloorMap.clear();
		_secretV.clear();
		_secretVMap.clear();
		//_floor.clear();

		//////とりあえず、↓は仮
		for (int i = 0; i < StageAll; i++) {

			//ステージ番号をstringに変換
			auto no = std::to_string(i);
			//下の二つを起動すればjsonが読み込める
			//auto stageParameter = std::make_unique<StageParameter>();
			game.GetStageParameter().LoadStageParameter(i, "resource/json/stage/stage" + no + ".json");
		}

		game.GetStageParameter().LoadStageTable("resource/json/stagetable.json");
		// 地面のモデル
		//_ground = std::make_unique<ModelComponent>(*this);
		//_ground->SetModel("Ground");
		//_ground->SetScale({10.f, 10.f, 10.f});

		// ステージ番号, ハンドル名(SceneInGameで登録した名前), コリジョンメッシュ名, ワープ位置名, 表示するフロア番号
		CollisionMesh collMap{
			//{"Player",    "SDChar/SDChar.mv1"},
		//	{0,    {"Dunge0", "dungeon_collision", {"", ""}}},

		//	{1,    {"teste0", "floor_collision", {"C0_01_02", ""}}},
			{0,    {"stage0", "collision", {"A0_00_01"}, 0}},
			{1,    {"stage1", "collision", {"A0_00_00", "A1_00_02"}, 10}},
			{2,    {"stage2", "collision", {"A1_00_01", "A2_00_03"}, 20}},
			{3,    {"stage3", "collision", {"A2_00_02", "A3_00_04", "B1_01_03"}, 30}},
			{4,    {"stage4", "collision", {"A3_00_03", "B2_01_04"}, 40}},
			{5,    {"stage5", "collision", {"B1_00_03", "B2_01_02"}, 31}},
			{6,    {"stage6", "collision", {"B2_01_03", "B3_01_01"}, 21}},
			{7,    {"stage7", "collision", {"B3_01_02", "C1_02_01"}, 11}},
			{8,    {"stage8", "collision", {"C1_01_01", "C2_02_02_entry", "C3_02_02"}, 12}},
			{9,    {"stage9", "collision", {"C2", "C5_02_03", "D0_03_02"}, 22}}
		};

		//ステージのコリジョン情報を取得
		//_collisionFloorNameMap = game.GetStageParameter().LoadStageCollision("resource / json / stagecollision.json");
		_collisionFloorNameMap = collMap;

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
		//GetCollision().SetAllFloorMap(_allFloorMap);









#ifdef _DEBUG
		CreateGround();
#endif
		//自分のいるフロアのみ描画
		//_stageNo = 1;

		CreateStage(game);




		for (int i = 0; i < _allFloorMap.size(); i++) {

			for (auto&& floor : _allFloorMap[i]) {

				auto&& handle = floor->GetHandle();

				auto stageNum = GetCollision().GetFloorStageNum(i);



				auto [handleName, collName, warpName, floorNum] = _collisionFloorNameMap[stageNum];

				//ナビメッシュのコリジョン情報を構築
				GetCollision().SetMapCollision(handle, collName);

				std::vector<std::string> vecStr;

				for (int j = 0; j < warpName.size(); j++) {

					//メッシュの数回す
					auto str = warpName[j];

					if (str != "") {

						vecStr.push_back(str);
						//ワープ位置のコリジョン情報を設定
						GetCollision().SetWarpCollision(handle, str);

					}


				}
				//同一ハンドルのワープの名前配列をハンドルで設定
				GetCollision().SetWarpName(handle, vecStr);

				auto stageTable = game.GetStageParameter().GetStageTableVector();

				//int floorNum = -1;

				//if (stageNum == 0) {
				//	floorNum = 0;
				//}
				//else if (stageNum == 1) {

				//	floorNum = 10;
				//}
				//else {
				//	floorNum = 100;

				//}

				//番号をフロア番号にしなければいけない
				//ワープ先の名前を設定
				GetCollision().SetWarpNameFloor(floorNum, vecStr);


			}



		}



		//for (int i = 0; i < _allFloorMap.size(); i++) {

		//	for (auto&& floor : _allFloorMap[i]) {

		//		auto&& handle = floor->GetHandle();

		//		////ステージ番号順にハンドル名とナビメッシュ名をベクターでいれたものが入っている
		//		for (int i = 0; i < _collisionFloorNameMap.size(); i++) {

		//			auto [handleName, collName, warpName] = _collisionFloorNameMap[i];

		//			//	auto number = 0;

		//			//	//文字列のサイズが6以外
		//			//	if (handleName.size() != 6) {
		//			//		continue;
		//			//	}
		//			//	else if (handleName.size() == 7) {

		//			//		auto num = handleName.substr(5, 2);
		//			//		number = std::stoi(num);

		//			//	}
		//			//	else {

		//			//		auto num = handleName.substr(5, 1);
		//			//		number = std::stoi(num);

		//			//	}


		//			//	//フロアの名前を入れる
		//			//	//auto&& [handle, num] = game.GetAssetServer().GetModel(handleName);
		//			//	auto handle = game.GetAssetServer().GetMap(number);

		//			//	//メッシュの数を取得
		//			//	//int number = MV1GetMeshNum(handle);

		//			//	//フレームの数を取得
		//			//	//int number = MV1GetFrameNum(handle);

		//			//	//ナビメッシュのコリジョン情報を構築
		//			//	GetCollision().SetMapCollision(handle.first, collName);

		//			std::vector<std::string> vecStr;

		//			for (int j = 0; j < warpName.size(); j++) {

		//				//メッシュの数回す
		//				auto str = warpName[j];

		//				if (str != "") {

		//					vecStr.push_back(str);
		//					//ワープ位置のコリジョン情報を設定
		//					GetCollision().SetWarpCollision(handle, str);

		//				}


		//			}
		//			//同一ハンドルのワープの名前配列をハンドルで設定
		//			GetCollision().SetWarpName(handle, vecStr);

		//			//ワープ先の名前を設定
		//			GetCollision().SetWarpNameFloor(vecStr);

		//		}
		//	}
		//}


		GetCollision().SetAllFloorMap(_allFloorMap);

		// フォグの設定
		 //SetFogEnable(TRUE);
		 //SetFogColor(247, 188, 101);
		 //SetFogStartEnd(50.0f, 15000.0f);
	}

	Stage::~Stage() {
		//_allFloor.clear();
		_allFloorMap.clear();
		_drawFloorV.clear();
		_secretVMap.clear();
		_secretV.clear();
		_collisionFloorNameMap.clear();
		_floorStageNum.clear();
		//_floor.clear();
	}

	void Stage::Update() {

		//auto pos = GetActorServer().GetPosition("Player");
		// スカイスフィアをプレイヤと同じ位置にする
	   //_skySphere->SetPosition(ToDX(pos));

		_stageNo = PlayerOnStageNumber();

		//触れているフロア番号で回す
//		for (auto&& no : _drawFloorV) {
//
//
//			//主人公の触れているフロア番号と一致した場合
////					if (no == _stageNo) {
//
//			auto value = _allFloorMap[no];
//			//auto secret = _secretVMap[no];
//
//			////フロア内のブロックを描画
//			for (auto&& floor : value) {
//
//				floor->Update();
//			}
///**********************************ここでコリジョンの更新を試してみる
//
//		}

	}

	void Stage::Draw() {
		//_skySphere->Draw();   // スカイスフィア
		_ground->Draw();      // 地面

		//表示するステージ番号のみ表示
		//キーの数を取得
		//auto num = _allFloor.count(_stageNo);

		//if (num != 0) {


			////////////////////////移動中のみ2画面表示するように
			//if (IsMoving()) {
			//
			//
			//}
			//else {
		//_stageNo = 1;

					// equal_range 関数を使って、指定したキーの最初と終端の位置を示すイテレータを std::pair<> で取得します。
					//auto[start, end] = _allFloor.equal_range(_stageNo);


					//// 取得したイテレータの範囲をループで回します。(仮では10フロア分)
					//for (auto iterator = start; iterator != end; iterator++)
					//{
					//	//キーと値のセットを取得
					//	auto [key, value] = *iterator;

					//	for (auto j = 0; j < value.size(); j++) {

					//		//1ブロック分
					//		value[j]->Draw();
					//	}
					//}

		std::vector<int> nums;
		std::vector<int> floorNums;
		//描画するフロア番号で回す
		for (auto&& no : _drawFloorV) {


			//主人公の触れているフロア番号と一致した場合
//					if (no == _stageNo) {

			auto value = _allFloorMap[no];
			//auto secret = _secretVMap[no];

			////フロア内のブロックを描画
			for (auto&& floor : value) {

				floor->Draw();

				//MV1RefreshCollInfo(floor->GetHandle(), 2);

				//現在位置のステージ番号を保存
				nums.push_back(floor->GetStageNum());


			}

			floorNums.push_back(no);

			//隠し扉用の機構(試し)
			//for (auto i = 0; i != value.size(); i++) {
			//
			//	for (auto&& match : secret) {
			//	
			//		if (i != match) {

			//			value[i]->Draw();
			//		}
			//		
			//	}
			//	
			//}

		//}
		//else {
		//
		//}


		}

		GetCollision().SetCollStageNum(nums);
		GetCollision().SetFloorNum(floorNums);

#ifdef _DEBUG


		auto stageNo = std::to_string(_stageNo);
		//DrawFloor();
		DrawString(0, 50, stageNo.c_str(), GetColor(255, 0, 0));


#endif 
		//}


	//}





	//for (auto j = 0; j < _allFloor.size(); j++) {
	//	_allFloor[j]->Draw();
	//}

	//_allFloor[_stageNo][0]->Draw();


	}

#ifdef _DEBUG

	bool Stage::CreateGround() {
		// 地面全体の中心を原点にするオフセット
		constexpr auto groundPolygonSize = Differ;
		constexpr auto groundStartX = -groundPolygonSize * static_cast<float>(BoardSize) * 0.5;
		constexpr auto groundStartZ = 0.0;
		// 頂点用の固定情報
		constexpr VECTOR groundNormal = { 0.0f, 1.0f, 0.0f };
		constexpr COLOR_U8 groundDiffuse0 = { 0, 0, 0, 255 };
		constexpr COLOR_U8 groundDiffuse1 = { 255, 0, 0, 255 };
		constexpr COLOR_U8 groundDiffuse2 = { 0, 255, 0, 255 };
		constexpr COLOR_U8 groundDiffuse3 = { 0, 0, 255, 255 };
		constexpr std::array<COLOR_U8, 4> groundColorList = {
		groundDiffuse0, groundDiffuse1, groundDiffuse2, groundDiffuse3
		};
		constexpr COLOR_U8 groundSpecular = { 0, 0, 0, 0 };
		// 地面の基本の正方形用テーブル
		constexpr VECTOR groundPosition0 = { 0.0f, 0.0f, 0.0f };
		constexpr VECTOR groundPosition1 = { 0.0f, 0.0f, Differ };
		constexpr VECTOR groundPosition2 = { Differ, 0.0f, 0.0f };
		constexpr VECTOR groundPosition3 = { Differ, 0.0f, Differ };
		constexpr std::array<VECTOR, 4> groundPositionlist = {
			groundPosition0,groundPosition1, groundPosition2, groundPosition3
		};
		// uv のテーブル
		constexpr std::array<float, 4> uList = { 0.0f, 0.0f, 1.0f, 1.0f };
		constexpr std::array<float, 4> vList = { 0.0f, 1.0f, 0.0f, 1.0f };

		auto offsetX = groundStartX;
		auto offsetZ = groundStartZ;
		auto offsetIndex = 0;

		for (auto z = 0; z < BoardSize; ++z)
		{
			offsetX = groundStartX;

			for (auto x = 0; x < BoardSize; ++x)
			{
				// 正方形を形成する
				for (auto i = 0; i < 4; ++i)
				{
					VERTEX3D vertex;

					VECTOR base = groundPositionlist[i];

					base.x += static_cast<float>(offsetX);
					base.z += static_cast<float>(offsetZ);

					vertex.pos = base;
					vertex.norm = groundNormal;

					vertex.dif = groundColorList[i];


					vertex.spc = groundSpecular;
					vertex.u = uList[i];
					vertex.v = vList[i];

					_groundVertex.emplace_back(std::move(vertex));
				}

				auto index = offsetIndex;

				_groundIndex.emplace_back(index);
				_groundIndex.emplace_back(index + 1);
				_groundIndex.emplace_back(index + 2);

				_groundIndex.emplace_back(index + 2);
				_groundIndex.emplace_back(index + 1);
				_groundIndex.emplace_back(index + 3);

				offsetIndex += 4;

				offsetX += Differ;
			}

			offsetZ += Differ;
		}

		return true;
	}

	void Stage::DrawFloor() {


		auto vertexNum = static_cast<int>(_groundVertex.size());
		auto indexNum = static_cast<int>(_groundIndex.size());
		auto polygonNum = indexNum / 3;

		DrawPolygonIndexed3D(_groundVertex.data(), vertexNum, _groundIndex.data(), polygonNum, DX_NONE_GRAPH, FALSE);
	}

#endif 

	bool Stage::CreateStage(AppFrame::Game& game) {

		auto stageTableVector = game.GetStageParameter().GetStageTableVector();

		//ステージテーブルをアクターファクトリーに渡す
		GetGame().GetActorFactory().SetStageTable(stageTableVector);

		auto startX = StartX;
		auto startZ = 0.0;

		auto offsetX = startX;
		auto offsetZ = startZ;

		std::unordered_map<int, Math::Vector4> floorPoses;

		//フロア数
		for (auto i = 0; i < stageTableVector.size(); i++) {

			offsetX = startX;
			//1列分のフロア
			for (auto j = 0; j < stageTableVector[i].size(); j++) {

				//左からj番目の数値
				auto num = stageTableVector[i][j];

				//最後の一番上の列だけ除く
				if (i != stageTableVector.size() - 1) {

					AppFrame::Math::Vector4 min = { static_cast<double>(j) * Differ + startX, 0.0, static_cast<double>(i) * Differ };
					AppFrame::Math::Vector4 max = { (j + 1) * Differ + startX, 0.0, (i + 1) * Differ };

					auto stageFloor = std::make_tuple(min, max, num);

					//テーブルの配置位置をキーとした各ステージフロアのminおよびmax
					_stageFloor.emplace(i * BoardSize + j, stageFloor);
				}



				//_board[i * _boardH + j] = i * BoardSize + j;
				//_boardStageNum.push_back(num);

				//0は何もなし
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
				auto stageVector = stageNumMap[num - 1];

				Floor floor;
				floor.clear();

				//とりあえず、ここで数字を定義
				int number = -1;


				Math::Vector4 floorPos;

				//フロアの各ブロック
				for (int k = 0; k < stageVector.size(); k++) {

					auto sP = stageVector[k];
					auto pos = sP.GetPosition();
					Math::Vector4 dif = { offsetX + Differ / 2.0, 0.0, offsetZ + Differ / 2.0 };

					//位置にオフセット分足してずらす
					pos = pos + dif;

					auto rot = sP.GetRotation();
					auto scale = sP.GetScale();
					auto ground = std::make_unique<Model::ModelComponent>(*this);

					//ground->SetModel(sP.GetName(), 1000);


					ground->SetMap(sP.GetName(), 1000);

					//とりあえず、仮で隠しの壁およびタイルを隠しようのベクターに登録
					if (sP.GetName() == "secretwall" || sP.GetName() == "secretfloor") {
						_secretV.push_back(k);
					}

					//仮で数字を取り出す機構
					auto numStr = sP.GetName().substr(5, 1);
					number = std::stoi(numStr);

					ground->SetStageNum(number);

					//VECTOR zero = { 0.0f, 0.0f, 0.0f };
					ground->SetPosition(ToDX(pos));

					floorPos = pos;

					MV1SetupCollInfo(ground->GetHandle(), -1, 32, 32, 32);
					//ground->SetPosition(zero);
					//auto size = MV1GetFrameNum(ground->GetHandle());


					ground->SetRotation(ToDX(rot));
					ground->SetScale(ToDX(scale));

					floor.push_back(std::move(ground));

				}

				floorPoses.emplace(i * BoardSize + j, floorPos);

				//とりあえず、仮で隠しの壁およびタイルを隠しようのステージ番号に登録
				_secretVMap.emplace(num, _secretV);

				offsetX += Differ;

				//上は、ステージ番号で格納
				//_allFloor.emplace(num, std::move(floor));

				//フロア番号でステージ番号を格納
				_floorStageNum.emplace(i * BoardSize + j, number);

				//下は、フロア番号で格納
				_allFloorMap.emplace(i * BoardSize + j, std::move(floor));


				//_board[i * _boardH + j] = i * 10 + j;
				//_boardStageNum.push_back(num);
			}

			offsetZ += Differ;


		}

		//フロア番号をキーとしたステージフロア座標を保存
		GetCollision().SetFloorPos(floorPoses);

		//ここに仮でフロア番号によるステージ番号の連想配列を外部から取得できるように設定
		GetCollision().SetFloorStageNum(_floorStageNum);

		return true;
	}

	int Stage::PlayerOnStageNumber() {

		_drawFloorV.clear();
		int stageNo = 0;
		std::vector<int> stageNoV;

		for (auto i = GetActorServer().GetActors().begin(); i != GetActorServer().GetActors().end(); i++) {

			if ((*i)->GetTypeId() != TypeId::Player) {
				continue;
			}
			else {

				//std::vector<int> stageNo;

				for (auto&& map : _stageFloor) {

					auto [floorNum, tuple] = map;
					auto [min, max, stageNum] = tuple;



					//////////////////////だけど、全てフロアとの判定よりはそもそもminとmaxが離れすぎているやつを処理しないようにしたい
					//主人公と各フロアとの当たり判定を検証
					if (_collision->CircleToAABB(**i, min, max)) {

						stageNoV.push_back(floorNum);

						AppFrame::Math::Vector4 leftUp = { min.GetX(), 0.0, max.GetZ() };
						AppFrame::Math::Vector4 rightDown = { max.GetX(), 0.0, min.GetZ() };

						auto player = GetActorServer().GetPosition("Player");

						//円の中心が四角形の中にある場合
						auto leftTriangle = AppFrame::Math::Utility::InsideTrianglePoint(min, leftUp, rightDown, player);
						auto rightTriangle = AppFrame::Math::Utility::InsideTrianglePoint(rightDown, leftUp, max, player);


						if (leftTriangle || rightTriangle) {
							stageNo = floorNum;
						}

					}


				}



			}


		}



		_drawFloorV = stageNoV;

		//アクターファクトリーに敵のリスポーン情報を送る
		GetGame().GetActorFactory().SetStageNo(_drawFloorV);

		return stageNo;
	}

	//int Stage::GetBoard(int x, int z) {
	//	return _board[z * _boardH + x];
	//}


	//void Stage::SetBoard(int x, int z, int n) {
	//	_board[z * _boardH + x] = n;
	//}
}
