/*****************************************************************//**
 * @file   GimmickBase.cpp
 * @brief  ギミックの基底クラス
 *
 * @author hikaru Goto
 * @date   December 15 2021
 *********************************************************************/

#include "GimmickBase.h"
#include "../Actor/Actor.h"
#include "GimmickParameter.h"
#include "../Collision/CollisionComponent.h"



namespace MachineHuck::Gimmick {


	namespace {

		constexpr int StageAll = 1;        //!< 読み込むgimmickstagejsonの数
		//constexpr double Differ = 500.0; //!< 1フロアのサイズ
		//constexpr double StartX = -5.0 * Differ;
		//constexpr int BoardSize = 10;

		//constexpr double HalfSize = 0.5 * Differ;
		//constexpr int StartZ = -5.0 * Differ;

	}


	GimmickBase::GimmickBase(AppFrame::Game& game) : Actor::Actor(game){



		////////とりあえず、↓は仮
		//for (int i = 0; i < StageAll; i++) {

		//	//ステージ番号をstringに変換
		//	auto no = std::to_string(i);
		//	//下の二つを起動すればjsonが読み込める
		//	//auto stageParameter = std::make_unique<StageParameter>();
		//	if (game.GetGimmickParameter().LoadGimmickStageParameter(i, "resource/json/gimmick" + no + ".json")) {
		//	
		//	}
		//	else {
		//		printfDx("ギミック読み込み失敗");
		//	}
		//}



	}



}


