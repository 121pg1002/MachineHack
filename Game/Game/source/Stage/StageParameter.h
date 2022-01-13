
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

		using StageMap = std::unordered_map<std::string, Parameter::StageParam>;

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
		* @param  filePath
		*/
		void LoadStageParameter(const std::string& filePath);

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


	private:
		//std::vector<StageP>  _stageParamV; //!<ステージ情報を格納するvector
		StageMap _stageParamMap;//!<ステージ情報を格納するmap
		std::vector<Parameter::StageParam> _stageParamV;

	};
}
