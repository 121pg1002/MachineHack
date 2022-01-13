
/*****************************************************************//**
 * @file   StageParameter.h
 * @brief  ステージの情報をjsonから読み込むクラス
 * 
 * @author hikaru Goto
 * @date   December 28 2021
 *********************************************************************/
#pragma once
#include <string>
#include <unordered_map>
#include "../Parameter/StageParam.h"

//using Level = std::unordered_map<std::string, StageParam>;
namespace MachineHuck::Stage {
	/**
	 * @class ステージ情報クラス
	 * @brief ステージ情報をjsonから読み込むクラス
	 */
	class StageParameter {

	public:

		using SMV = std::vector<Parameter::StageParam>;
		using StageV = std::vector<int>;

		/**
		 * @brief 変数の初期化
		 */
		StageParameter();

		/**
		 * @brief 変数の解放
		 */
		~StageParameter();

		/**
		* @brief  ステージの配置情報をjsonから読み込む
		* @param  num ステージ番号
		* @param  filePath
		*/
		void LoadStageParameter(const int num, const std::string& filePath);

        /**
         * @brief　ステージのテーブルをjsonから読み込む
         * @param filePath
         */
		void LoadStageTable(const std::string& filePath);

		/**
		 * @brief   コンテナを取得する
		 * @return  _stageParamMap
		 */
		 //StageMap GetStageMap() { return _stageParamMap; }

		 /**
		  * @brief   ベクター配列を取得する
		  * @return  _stageParamV
		  */
		std::vector<Parameter::StageParam> GetStageVector() { return _stageParamV; }

		/**
		 * @brief  フロア番号の情報を取得
		 * @return _stageNumMap
		 */
		std::unordered_map<int, SMV> GetFloorMap() { return _stageNumMap; }

		/**
		  * @brief   ステージテーブル配列を取得する
		  * @return  _stageTableV
		  */
		std::vector<StageV> GetStageTableVector() { return _stageTableV; }


	private:


		SMV _stageParamV; //!< 1フロア情報を格納

		std::unordered_map<int, SMV> _stageNumMap; //!< フロア番号ごとに格納

		std::vector<StageV> _stageTableV; //!< ステージテーブルを格納する配列



	};
}
