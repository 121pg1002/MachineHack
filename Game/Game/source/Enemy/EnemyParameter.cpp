
/*****************************************************************//**
 * @file   EnemyParameter.cpp
 * @brief  エネミーのパラメーターをjsonから読み込む
 * 
 * @author hikaru  Goto
 * @date   December 22 2021
 *********************************************************************/
#include"../Enemy/EnemyParameter.h"
#include "../nlohmann/json.hpp"
#include <filesystem>
#include <fstream> 
#include "../../../../AppFrame/source/Asset/AssetServer.h"

using json = nlohmann::json;

namespace Enemy {
	EnemyParameter::EnemyParameter()
	{
		_enemyStageMap.clear();
		_enemyParamMap.clear();
	}

	EnemyParameter::~EnemyParameter()
	{
		_enemyStageMap.clear();
		_enemyParamMap.clear();
	}


	void EnemyParameter::LoadStageEnemyParam(const std::string& filepath)
	{
		std::filesystem::path fs = filepath;
		std::string filename = fs.parent_path().string() + "/";

		//// Jsonファイルの読み込み
		std::ifstream jsonFile(filepath);
		auto jsRoot = json::parse(jsonFile);

		//// パラメータをjsonから取得
		_handlename = jsRoot["handle"];

		_position = { jsRoot["px"], jsRoot["py"], jsRoot["pz"] };
		_rotation = { jsRoot["rx"], jsRoot["ry"], jsRoot["rz"] };
		_scale = { jsRoot["sx"], jsRoot["sy"], jsRoot["sz"] };

		EStageParam eSP;
		eSP.clear();
		eSP["position"] = _position;
		eSP["rotation"] = _rotation;
		eSP["scale"] = _scale;

		_enemyStageMap.emplace(_filename, eSP);

	}

	void EnemyParameter::LoadEnemyParam(const std::string& filepath)
	{

		std::filesystem::path fs = filepath;
		std::string filename = fs.parent_path().string() + "/";

		//// Jsonファイルの読み込み
		std::ifstream jsonFile(filepath);
		auto jsRoot = json::parse(jsonFile);

		////// パラメータをjsonから取得	
		_type = jsRoot["type"];
		_energy = jsRoot["energy"];

		if (_energy > 100.0)
		{
			printfDx("energy is over range");
			return;
		}

		_searchRange = jsRoot["searchrange"];
		if (_searchRange > 90)
		{
			printfDx("searchrange is over range");
			return;
		}

		_r = jsRoot["r"];
		_speed = jsRoot["speed"];

		EParam eP;
		eP.clear();
		eP["type"] = _type;
		eP["energy"] = _energy;
		eP["searchrange"] = _searchRange;
		eP["r"] = _r;
		eP["speed"] = _speed;

		//_enemyParamMap.emplace(_filename, _type);
		//_enemyParamMap.emplace(_filename, _energy);
		//_enemyParamMap.emplace(_filename, _searchRange);
		//_enemyParamMap.emplace(_filename, _r);
		//_enemyParamMap.emplace(_filename, _speed);
		_enemyParamMap.emplace(filepath, eP);
	}

	//double EnemyParameter::GetEnemyParam(const std::string& paramName)
	//{
	//	auto ite = _enemyParamMap.find(paramName);

	//	//パラメータがあったら返す
	//	if (ite != _enemyParamMap.end())
	//	{
	//		return ite->second;
	//	}
	//	else 
	//	{
	//		printfDx("enemy parameter is not");
	//	
	//	}
	//}

	double EnemyParameter::GetEnemyParam(const std::string& paramName)
	{
		auto ite = _enemyParamMap.find(paramName);

		//パラメータがあったら返す
		if (ite != _enemyParamMap.end())
		{
			return ite->second[paramName];
		}
		else
		{
			printfDx("enemy parameter is not");
			return 0;
		}
		return 0;
	}
}

