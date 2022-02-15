
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
		//int GetLevel() { return _level; }

		/**
		 * @brief  敵のレベルを保存
		 * @param  level
		 */
		//void SetLevel(int level) { _level = level; }

		/**
		 * @brief  移動ルーチン番号を取得
		 * @return _routine
		 */
		int GetRoutine() { return _routine; }

		/**
		 * @brief 移動ルーチン番号を設定
		 * @param num
		 */
		void SetRoutine(int num) { _routine = num; }

		/** 
		 * @brief  移動量を取得
		 * @return 移動量
		 */
		int GetNumRange() { return _numRange; }

		/** 
		 * @brief  移動量を設定       
		 * @param  numRange
		 */
		void SetNumRange(int numRange) { _numRange = numRange; }

		/**
		 * @brief  生成回数
		 * @return
		 */
		int GetProgress() { _progress; }

	private:

		int _level; //!< 敵のレベル
		int _routine; //!< 移動ルーチン
		int _numRange; //!< 移動量
		int _progress{ 0 }; //!< 生成回数
		std::string _type;
	};
}
