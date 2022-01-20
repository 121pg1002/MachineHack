
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

        using GStegeParamV = std::vector<Parameter::GStageParam>;
        using StageV = std::vector<int>;

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
        * @param  num      ステージ番号
        * @param  filePath ファイルパス
        * @return true  読み込み成功
        *         false 読み込み失敗
        */
		bool LoadGimmickStageParameter(const int num, const std::string& filePath);

        /**
        * @brief   ベクター配列を取得する
        * @return  _gimickStageParamV
        */
        std::vector<Parameter::GStageParam> GetStageVector() { return _gimmickStageParamV; }

        /**
         * @brief  フロア番号の情報を取得
         * @return _gimmickStageNumMap
         */
        std::unordered_map<int, GStegeParamV> GetFloorMap() { return _gimmickStageNumMap; }


    private:

        GStegeParamV _gimmickStageParamV; //!< 1フロア情報を格納

        std::unordered_map<int, GStegeParamV> _gimmickStageNumMap; //!< フロア番号ごとに格納

	};
}

