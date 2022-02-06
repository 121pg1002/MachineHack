
/*****************************************************************//**
 * @file   GimmickParameter.h
 * @brief  ギミックのjson情報管理クラス
 * 
 * @author hikaru Goto
 * @date   January 2022
 *********************************************************************/
#pragma once
#include <string>
#include "../Parameter/GStageParam.h"

namespace MachineHuck::Gimmick {

	class GimmickParameter {
	public:

        using GSV = std::vector<Parameter::GStageParam>;
        //using StageV = std::vector<int>;

        /**
         * @brief 変数の初期化        
         */
        GimmickParameter();

        /**
         * @brief 変数の解放         
         */
        ~GimmickParameter();

		/**
        * @brief  jsonからギミックのステージ配置を読み込む
        * @param  stageNo      ステージ番号
        * @param  filePath ファイルパス
        * @return true  読み込み成功
        *         false 読み込み失敗
        */
		bool LoadGimmickStageParameter(const int stageNo, const std::string& filePath);

        /**
        * @brief   ベクター配列を取得する
        * @return  _gimickStageParamV
        */
        GSV GetStageVector() { return _gimmickStageParamV; }

        /**
         * @brief  フロア番号の情報を取得
         * @return _gimmickStageNumMap
         */
        std::unordered_map<int, GSV> GetFloorGimmickMap() { return _gimmickStageNumMap; }


    private:

        GSV _gimmickStageParamV; //!< 1フロア情報を格納

        std::unordered_map<int, GSV> _gimmickStageNumMap; //!< フロア番号ごとに格納

	};
}

