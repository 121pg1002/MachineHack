
/*****************************************************************//**
 * @file   StageParameterBase.h
 * @brief  jsonから読み込むパラメーターの基底クラス
 * 
 * @author hikaru Goto
 * @date   December 30 2021
 *********************************************************************/
#pragma once
#include "AppFrame.h"
namespace Math = AppFrame::Math;

namespace MachineHuck::Parameter {
	class StageParameterBase {
	public:

		/**
		 * @brief 変数の初期化
		 */
		StageParameterBase();

		/**
		 * @brief 変数の解放
		 */
		~StageParameterBase() = default;


		/**
		 * @brief  ファイル名を取得する
		 * @return _fileName
		 */
		std::string GetName() { return _fileName; }

		/**
		 * @biref 位置情報を保存
		 * @param pos 位置
		 */
		Math::Vector4 GetPosition() { return _pos; };

		/**
		 * @biref 回転情報を保存
		 * @param rot 回転
		 */
		Math::Vector4 GetRotation() { return _rot; };

		/**
		 * @biref スケール情報を保存
		 * @param scale スケール
		 */
		Math::Vector4 GetScale() { return  _scale; };






		/**
		* @brief  ファイル名を保存
		* @param  fileName
		*/
		void SetName(std::string fileName) { _fileName = fileName; }


		/**
		 * @biref 位置情報を保存
		 * @param pos 位置
		 */
		void SetPos(Math::Vector4 pos) { _pos = pos; };

		/**
		 * @biref 回転情報を保存
		 * @param rot 回転
		 */
		void SetRot(Math::Vector4 rot) { _rot = rot; };

		/**
		 * @biref スケール情報を保存
		 * @param scale スケール
		 */
		void SetScale(Math::Vector4 scale) { _scale = scale; };

	protected:

		std::string _fileName{ "" };      //!< ハンドル名
		Math::Vector4 _pos{ 0.0, 0.0, 0.0 };           //!< 並行移動 
		Math::Vector4 _rot{ 0.0, 0.0, 0.0 };           //!< 回転
		Math::Vector4 _scale{ 0.0, 0.0, 0.0 };         //!< スケール
		std::string _type{ "" };            //!< 種類

	};
}


