/*****************************************************************//**
 * @file   EnemyParameter.h
 * @brief  エネミーパラメーターを読み込むクラス
 * 
 * @author hikaru Goto
 * @date   December 26 2021
 *********************************************************************/
#pragma once
#include<unordered_map>
#include<string>
#include<DxLib.h>
#include "../Parameter/EStageParam.h"
#include "../Parameter/EParam.h"




namespace MachineHuck::Enemy {


	using Type = std::unordered_map<std::string, Parameter::EStageParam>;
	using StageMap = std::unordered_map<std::string, Type>;
	using DoubleMap = std::unordered_map<std::string, double>;

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
		 * @brief  エネミーのステージ配置情報をjsonから読み込む
		 * @param  filePath
		 */
		void LoadStageEnemyParam(const std::string& filePath);

		/*
		* @brief  jsonから敵の情報を読み込む
		* @param  filePath
		*/
		void LoadEnemyParam(const std::string& filePath);

		/*
		* @brief 読み込んだパラメーターを取得
		* @param  filePath
		* @return パラメーター
		*/
		double GetEnemyParam(const std::string& paramName, int no);

		/**
		 * @brief  ステージの敵配置マップを取得
		 * @return _enemyStageParamMap
		 */
		std::unordered_map<std::string, Parameter::EStageParam>GetStageEnemyParameter() { return _enemyStageParamMap; }

	private:
		std::unordered_map<std::string, Parameter::EStageParam>     _enemyStageParamMap; //!< 敵のステージ配置を保存
		std::unordered_map<std::string, Type>            _eType;              //!< 敵の種類をキーとした要素を保存
		std::unordered_map<std::string, StageMap>        _eSMap;              //!< ステージ番号をキーとして要素を保存


	   // std::unordered_map<std::string, double> _enemyParamMap; //!< 敵のパラメーターを保存
		//std::unordered_map<std::string, EnemyParameter> _enemyParamMap;

		std::vector<DoubleMap> _vDoubleMap;
		std::unordered_map<std::string, Parameter::EParam> _enemyParamMap;//!< 敵のパラメーターを保存
		//std::unordered_map<std::string, double> _enemyParameterMap;//!< 敵のパラメーターを保存

	};
}

