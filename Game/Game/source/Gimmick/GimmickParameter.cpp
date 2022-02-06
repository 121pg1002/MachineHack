/*****************************************************************//**
 * @file   GimmickParameter.cpp
 * @brief  ギミックのjson情報管理クラス
 * 
 * @author hikaru  Goto
 * @date   January 20 2022
 *********************************************************************/
#include "GimmickParameter.h" 
#include <fstream>
//#include <memory>
#include <filesystem>
#include "../nlohmann/json.hpp"

namespace MachineHuck::Gimmick {
	using Json = nlohmann::json;

	namespace {
		constexpr double Differ = 3000.0; //!< 1フロアのサイズ
		constexpr double StartX = -5.0 * Differ;
		constexpr int BoardSize = 10;
	}

	GimmickParameter::GimmickParameter() {
		_gimmickStageParamV.clear();
		_gimmickStageNumMap.clear();
	
	}

	GimmickParameter::~GimmickParameter() {
		_gimmickStageParamV.clear();
		_gimmickStageNumMap.clear();
	}

	bool GimmickParameter::LoadGimmickStageParameter(const int stageNo, const std::string& filePath) {
	
		//// Jsonファイルの読み込み
		std::ifstream jsonFile(filePath);
		auto jsRoot = Json::parse(jsonFile);

		_gimmickStageParamV.clear();

		int numX = 0;
		int numZ = 0;

		if (0 <= stageNo && stageNo <= 9) {

			numX = stageNo;
			numZ = 0;
		}
		else {

			numX = stageNo % 10; //!< 一桁目
			numZ = stageNo / 10; //!< 二桁目

		}

		auto startX = StartX;
		auto startZ = 0.0;

		auto offsetX = startX;
		auto offsetZ = startZ;


		//読み込めなかったとき
		if (jsRoot["Gimmick"].size() == 0) {

			printf("jsRoot is not load");
			return false;
		}
		else {


			for (int i = 0; i < jsRoot["Gimmick"].size(); i++) {

				Parameter::GStageParam gSP;

				const std::string& fileName = jsRoot["Gimmick"].at(i)["filename"];
				//auto& handleName = jsRoot["Gimmick"].at(i)["handlename"];
				const double& tx = jsRoot["Gimmick"].at(i)["tx"];
				const double& ty = jsRoot["Gimmick"].at(i)["ty"];
				const double& tz = jsRoot["Gimmick"].at(i)["tz"];
				const double& rx = jsRoot["Gimmick"].at(i)["rx"];
				const double& ry = jsRoot["Gimmick"].at(i)["ry"];
				const double& rz = jsRoot["Gimmick"].at(i)["rz"];
				const double& sx = jsRoot["Gimmick"].at(i)["sx"];
				const double& sy = jsRoot["Gimmick"].at(i)["sy"];
				const double& sz = jsRoot["Gimmick"].at(i)["sz"];

				Math::Vector4 pos = { tx, ty, tz };
				Math::Vector4 rot = { rx, ry, rz };
				Math::Vector4 scale = { sx, sy, sz };

				Math::Vector4 dif = { offsetX + Differ / 2.0 + Differ * numX, 0.0, offsetZ + Differ / 2.0 + Differ * numZ };

				pos = pos + dif;

				gSP.SetName(fileName);
				gSP.SetPos(pos);
				gSP.SetRot(rot);
				gSP.SetScale(scale);

				//ギミック一つ一つを格納
				_gimmickStageParamV.emplace_back(gSP);

			}

			//フロア番号で1フロア分を格納
			_gimmickStageNumMap.emplace(stageNo, _gimmickStageParamV);
		}

		return true;

	}

}



