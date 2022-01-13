
/*****************************************************************//**
 * @file   EStageParam.h
 * @brief  ステージの敵の情報クラス
 * 
 * @author hikaru Goto
 * @date   December 30 2021
 *********************************************************************/
#pragma once
#include "StageParameterBase.h"
#include <string>
namespace MachineHuck::Parameter {

	class EStageParam : public StageParameterBase {
	public:


		/**
		 * @biref 種類を保存
		 * @param _type
		 */
		std::string GetType() { return  _type; };


		/**
		 * @brief  敵のレベルを取得する
		 * @return _level
		 */
		int GetLevel() { return _level; }

		/**
		 * @brief  敵のレベルを保存
		 * @param  level
		 */
		void SetLevel(int level) { _level = level; }

	private:

		int _level; //!< 敵のレベル
		std::string _type;
	};
}
