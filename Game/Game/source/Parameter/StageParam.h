
/*****************************************************************//**
 * @file   StageParam.h
 * @brief  ステージの情報クラス
 * 
 * @author hikaru Goto
 * @date   December 30 2021
 *********************************************************************/
#pragma once
#include "StageParameterBase.h"

namespace MachineHuck::Parameter {
	class StageParam : public StageParameterBase {
	public:


		/**
		 * @brief  コンストラクタ
		 */
		StageParam();

		///**
		// * @brief  ハンドルネームを保存     
		// * @param  handleName
		// */
		//void SetName(std::string fileName) { _fileName = fileName; }


		///**
		// * @biref 位置情報を保存
		// * @param pos 位置
		// */
		//void SetPos(Math::Vector4 pos) { _pos = pos; };

		///**
		// * @biref 回転情報を保存
		// * @param rot 回転
		// */
		//void SetRot(Math::Vector4 rot) { _rot = rot; };

		///**
		// * @biref スケール情報を保存
		// * @param scale スケール
		// */
		//void SetScale(Math::Vector4 scale) { _scale = scale; };

	private:

	};
}

