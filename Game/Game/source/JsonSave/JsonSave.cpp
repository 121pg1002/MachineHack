/*****************************************************************//**
 * @file   JsonSave.cpp
 * @brief  jsonに書き出しを行うクラス
 * 
 * @author hikaru Goto
 * @date   December 26 2021
 *********************************************************************/

#include "JsonSave.h"
#include "../nlohmann/json.hpp"

namespace JsonSave {

	using json = nlohmann::json;

	JsonSave::JsonSave(ProgressParam pp) {



	};

	bool SaveParam(const MachineHuck::Parameter::EParam ep) {

		//if (!ep.size() > 0) {
		//	printf("epfile is not content");
		//	return false;
		//}

		//json j;

		//j.push_back(ep.at(0));
		//for (auto&& count : ep) 
		//{
		//  j["type"]        = ep.find("type")->second;
		//  j["energy"]      = ep.find("energy")->second;
		//  j["searchrange"] = ep.find("searchrange")->second;
		//  j["r"]           = ep.find("r")->second;
		//  j["speed"]       = ep.find("speed")->second;

		//}

		return true;
	}

	bool SaveParam(const ProgressParam pp) {

		return false;
	}

}


