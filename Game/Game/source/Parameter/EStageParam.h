
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
		 * @brief  生成回数
		 * @return
		 */
		int GetProgress() { _progress; }

	private:

		int _progress{ 0 }; //!< 生成回数
		std::string _type;
	};
}
