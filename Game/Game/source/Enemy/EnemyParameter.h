/**
 * @file    EnemyParameter.h
 * @brief  パラメーターをjsonから読み込む
 *
 *
 * @author Hikaru Goto
 * @date   2021/11/27
 */

#pragma once
#include<unordered_map>
#include<string>
#include<DxLib.h>
#include "AppFrame.h"

using EStageParam = std::unordered_map < std::string, math::Vector4>;
using EParam      = std::unordered_map < std::string, double>;

namespace Enemy {
	class EnemyParameter
	{
	public:

		/*
		* @brief コンストラクタ
		*/
		EnemyParameter();

		/*
		* @brief デストラクタ
		*/
		~EnemyParameter();

		/**
		 * @brief  エネミーのステージ配置パラメーターをjsonから読み込む
		 * @param  filePath
		 */
		void LoadStageEnemyParam(const std::string& filePath);

		/*
		* @brief  jsonから敵のパラメーターを読み込む
		* @param  filePath
		*/
		void LoadEnemyParam(const std::string& filePath);

		/*
		* @brief 読み込んだパラメーターを取得
		* @param  filePath
		* @return パラメーター
		*/
		double GetEnemyParam(const std::string& paramName);

	private:
		std::unordered_map<std::string, EStageParam>     _enemyStageMap; //!< 敵のステージ配置を保存
	 // std::unordered_map<std::string, double> _enemyParamMap; //!< 敵のパラメーターを保存
		//std::unordered_map<std::string, EnemyParameter> _enemyParamMap;
		std::unordered_map<std::string, EParam> _enemyParamMap;
		std::string _filename;
		std::string _handlename;
		math::Vector4 _position;
		math::Vector4 _rotation;
		math::Vector4 _scale;


		double _type{ 0.0 };  //!< 種類
		double _energy{ 0.0 }; //!< エナジー量
		double _searchRange{ 0.0 }; //!< 索敵範囲の角度
		double _r{ 0.0 }; //!< 索敵半径
		double _speed{ 0.0 }; //!< 速さ

	};
}