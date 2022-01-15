
/*****************************************************************//**
 * @file   StageParameter.cpp
 * @brief  �X�e�[�W�̏���json����ǂݍ��ރN���X
 *         
 * @author hikaru Goto
 * @date   December 28 2021
 *********************************************************************/

#include "StageParameter.h"
#include <fstream>
#include <memory>
#include <filesystem>
#include "../nlohmann/json.hpp"


namespace MachineHuck::Stage {
	using Json = nlohmann::json;


	StageParameter::StageParameter() {
		_stageParamV.clear();
		_stageNumMap.clear();
		_stageTableV.clear();
	}

	StageParameter::~StageParameter() {
		_stageParamV.clear();
		_stageNumMap.clear();
		_stageTableV.clear();
	}

	void StageParameter::LoadStageParameter(const int num, const std::string& filePath) {

		//// Json�t�@�C���̓ǂݍ���
		std::ifstream jsonFile(filePath);
		auto jsRoot = Json::parse(jsonFile);

		//�ǂݍ��߂Ȃ������Ƃ�
		if (jsRoot["Stage"].size() == 0) {

			printf("jsRoot is not load");
		}
		else {


			for (int i = 0; i < jsRoot["Stage"].size(); i++) {

				Parameter::StageParam sP;

				auto& fileName   = jsRoot["Stage"].at(i)["filename"];
				//auto& handleName = jsRoot["Stage"].at(i)["handlename"];
				auto& tx = jsRoot["Stage"].at(i)["tx"];
				auto& ty = jsRoot["Stage"].at(i)["ty"];
				auto& tz = jsRoot["Stage"].at(i)["tz"];
				auto& rx = jsRoot["Stage"].at(i)["rx"];
				auto& ry = jsRoot["Stage"].at(i)["ry"];
				auto& rz = jsRoot["Stage"].at(i)["rz"];
				auto& sx = jsRoot["Stage"].at(i)["sx"];
				auto& sy = jsRoot["Stage"].at(i)["sy"];
				auto& sz = jsRoot["Stage"].at(i)["sz"];

				Math::Vector4 pos = { tx, ty, tz };
				Math::Vector4 rot = { rx, ry, rz };
				Math::Vector4 scale = { sx, sy, sz };


				sP.SetName(fileName);
				sP.SetPos(pos);
				sP.SetRot(rot);
				sP.SetScale(scale);

				//�u���b�N�����i�[
				_stageParamV.emplace_back(sP);

			}

			//�t���A�ԍ���1�t���A�����i�[
			_stageNumMap.emplace(num, _stageParamV);
		}

		/////************************�{�ԁ�
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

	void StageParameter::LoadStageTable(const std::string& filePath) {
	
		//// Json�t�@�C���̓ǂݍ���
		std::ifstream jsonFile(filePath);
		auto jsRoot = Json::parse(jsonFile);

		//�ǂݍ��߂Ȃ������Ƃ�
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


				_stageTableV.push_back(stageTable);
				
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

