
/*****************************************************************//**
 * @file   GParam.cpp
 * @brief  ギミックの情報クラス
 * 
 * @author hikaru Goto
 * @date   December 30 2021
 *********************************************************************/
#include "GParam.h"
#include <DxLib.h>

namespace MachineHuck::Parameter {
	void GParam::SetCollisionFrame(int handle) {

		// マップ
		//_handleMap = MV1LoadModel("res/Dungeon/Dungeon.mv1");
		// コリジョン情報の生成
		//_collisionFrame = MV1SearchFrame(handle, "dungeon_collision");
		//MV1SetupCollInfo(handle, _collisionFrame, 16, 16, 16);

		//// コリジョンのフレームを描画しない設定
		//MV1SetFrameVisible(handle, _collisionFrame, false);
		//// 腰位置の設定
		////_colSubY = 40.f;

		////// 移動した先でコリジョン判定
		//MV1_COLL_RESULT_POLY hitPoly;
		////// 主人公の腰位置から下方向への直線
		//hitPoly = MV1CollCheck_Line(handle, _collisionFrame,
		//	VAdd(_vPos, VGet(0, _colSubY, 0)), VAdd(_vPos, VGet(0, -99999.f, 0)));
		//if (hitPoly.HitFlag) {
		//  //当たった
		//}
		//else {
		//  //当たらなかった
		//}
	}
}


