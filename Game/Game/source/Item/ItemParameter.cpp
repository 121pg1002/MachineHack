/*****************************************************************//**
 * @file   ItemParameter.cpp
 * @brief  アイテムのパラメーターをjsonから読み込む
 *
 * @author kyoga Tagawa
 * @date   2022/02/01
 *********************************************************************/
#include "ItemParameter.h"
#include <fstream>
#include <memory>
#include <filesystem>
#include "../nlohmann/json.hpp"


namespace MachineHuck::Item {

	namespace {
		constexpr double Differ = 3000.0; //!< 1フロアのサイズ
		constexpr double StartX = -2.5 * Differ;
		constexpr int BoardSize = 5;
	}

	using Json = nlohmann::json;


	ItemParameter::ItemParameter() {
		_iStageParamV.clear();
		_iStageNumMap.clear();
		
	}

	ItemParameter::~ItemParameter() {
		_iStageParamV.clear();
		_iStageNumMap.clear();
		
	}

	void ItemParameter::LoadStageItemParam(const int num, const std::string& filePath) {

		//// Jsonファイルの読み込み
		std::ifstream jsonFile(filePath);
		auto jsRoot = Json::parse(jsonFile);

		_iStageParamV.clear();

		int numX = 0;
		int numZ = 0;

		if (0 <= num && num <= 4) {

			numX = num;
			numZ = 0;
		}
		else {

			numX = num % 5; //!< 一桁目
			numZ = num / 5; //!< 二桁目

		}

		auto startX = StartX;
		auto startZ = 0.0;

		auto offsetX = startX;
		auto offsetZ = startZ;

		//読み込めなかったとき
		if (jsRoot["StageItem"].size() == 0) {

			printf("jsRoot is not load");
		}
		else {


			for (int i = 0; i < jsRoot["StageItem"].size(); i++) {

				Parameter::IStageParam iSP;

				const std::string& fileName = jsRoot["StageItem"].at(i)["filename"];
				//auto& handleName = jsRoot["Stage"].at(i)["handlename"];
				const double& tx = jsRoot["StageItem"].at(i)["tx"];
				const double& ty = jsRoot["StageItem"].at(i)["ty"];
				const double& tz = jsRoot["StageItem"].at(i)["tz"];
				const double& rx = jsRoot["StageItem"].at(i)["rx"];
				const double& ry = jsRoot["StageItem"].at(i)["ry"];
				const double& rz = jsRoot["StageItem"].at(i)["rz"];
				const double& sx = jsRoot["StageItem"].at(i)["sx"];
				const double& sy = jsRoot["StageItem"].at(i)["sy"];
				const double& sz = jsRoot["StageItem"].at(i)["sz"];

				Math::Vector4 pos = { tx, ty, tz };
				Math::Vector4 rot = { rx, ry, rz };
				Math::Vector4 scale = { sx, sy, sz };

				Math::Vector4 dif = { offsetX + Differ / 2.0 + Differ * numX, 0.0, offsetZ + Differ / 2.0 + Differ * numZ };

				pos = pos + dif;

				iSP.SetName(fileName);
				iSP.SetPos(pos);
				iSP.SetRot(rot);
				iSP.SetScale(scale);

				//ブロック一つ一つを格納
				_iStageParamV.emplace_back(iSP);

			}

			//フロア番号で1フロア分を格納
			_iStageNumMap.emplace(num, _iStageParamV);
		}

		/////************************本番↓
		//if (jsRoot["stage"].size() == 0) {

		//	printf("jsRoot is not load");
		//}
		//else {

		//	for (int i = 0; i < jsRoot["stage"].size(); i++) {

		//		StageParam sP;

		//		auto& fileName = jsRoot["stage"].at(i)["filename"];
		//		auto& handleName = jsRoot["stage"].at(i)["handlename"];
		//		auto& tx = jsRoot["stage"].at(i)["tx"];
		//		auto& ty = jsRoot["stage"].at(i)["ty"];
		//		auto& tz = jsRoot["stage"].at(i)["tz"];
		//		auto& rx = jsRoot["stage"].at(i)["rx"];
		//		auto& ry = jsRoot["stage"].at(i)["ry"];
		//		auto& rz = jsRoot["stage"].at(i)["rz"];
		//		auto& sx = jsRoot["stage"].at(i)["sx"];
		//		auto& sy = jsRoot["stage"].at(i)["sy"];
		//		auto& sz = jsRoot["stage"].at(i)["sz"];

		//		Math::Vector4 pos = { tx, ty, tz };
		//		Math::Vector4 rot = { rx, ry, rz };
		//		Math::Vector4 scale = { sx, sy, sz };


		//		sP.SetName(fileName);
		//		sP.SetPos(pos);
		//		sP.SetRot(rot);
		//		sP.SetScale(scale);

		//		_stageParamMap.emplace(handleName, sP);
		//	}
		//}

	}

	void ItemParameter::LoadStageTable(const std::string& filePath) {

		//// Jsonファイルの読み込み
		std::ifstream jsonFile(filePath);
		auto jsRoot = Json::parse(jsonFile);

		//読み込めなかったとき
		if (jsRoot["StageTable"].size() == 0) {

			printf("jsRoot is not load");
		}
		else {

			for (int i = 0; i < jsRoot["StageTable"].size(); i++) {

				//Parameter::StageParam sP;
				StageV stageTable;
				stageTable.clear();

				for (int j = 0; j < jsRoot["StageTable"].at(i).size(); j++) {

					auto& num = jsRoot["StageTable"].at(i)[j];

					stageTable.push_back(num);

				}


				//_stageTableV.push_back(stageTable);

				//auto& fileName = jsRoot["StageTable"].at(i)["filename"];
				//auto& handleName = jsRoot["StageTable"].at(i)["handlename"];
				//for (int j = 0; j < jsRoot["StageTable"].at(i).size(); j++) {
				//
				//	_stageTableV.push_back(j);
				//}


			}
		}

	}
}

