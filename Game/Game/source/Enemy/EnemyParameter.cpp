/*****************************************************************//**
 * @file   EnemyParameter.cpp
 * @brief  �G�l�~�[�̃p�����[�^�[��json����ǂݍ���
 *
 * @author hikaru Goto
 * @date   December 26 2021
 *********************************************************************/
#include"../Enemy/EnemyParameter.h"
#include "../nlohmann/json.hpp"
#include <filesystem>
#include <fstream> 
#include "../../../../AppFrame/source/Asset/AssetServer.h"
//#include "../Parameter/EStageParam.h"



namespace MachineHuck::Enemy {

    using Json = nlohmann::json;
    namespace Math = AppFrame::Math;

    namespace {
        constexpr double Differ = 3000.0; //!< 1�t���A�̃T�C�Y
        constexpr double BoardSize = 5.0;
        constexpr double StartX = -BoardSize/2 * Differ;

    }


    //�R���X�g���N�^
    EnemyParameter::EnemyParameter()
    {
        _eStageParamV.clear();
        _eStageNumMap.clear();
        // _eType.clear();
        // _eSMap.clear();
         /*_enemyStageParamMap.clear();*/
             //_enemyParamMap.clear();//EParam
             //_enemyParameterMap.clear();//double
        _vDoubleMap.clear();
    }
    //�f�X�g���N�^
    EnemyParameter::~EnemyParameter()
    {
        _eStageParamV.clear();
        _eStageNumMap.clear();

        _vDoubleMap.clear();
    }
    //�G�l�~�[�̃X�e�[�W�z�u����json����ǂݍ���
    void EnemyParameter::LoadStageEnemyParam(const int stageNo, const std::string& filePath)
    {
        //// Json�t�@�C���̓ǂݍ���
        std::ifstream jsonFile(filePath);
        auto jsRoot = Json::parse(jsonFile);
        auto j = jsRoot["StageEnemy"];
        _eStageParamV.clear();
        //_vLevelRoutine.clear();
        //�G�̎�ނœǂݍ���json��ς���
        //if (filePath.find("tackle")) {

        int numX = 0;
        int numZ = 0;

        if (0 <= stageNo && stageNo <= 4) {

            numX = stageNo;
            numZ = 0;
        }
        else {

            numX = stageNo % 5; //!< �ꌅ��
            numZ = stageNo / 5; //!< �񌅖�

        }

        auto startX = StartX;
        auto startZ = 0.0;

        auto offsetX = startX;
        auto offsetZ = startZ;



        //�ǂݍ��߂Ȃ������Ƃ�
        if (jsRoot["StageEnemy"].size() == 0) {

            printf("jsRoot is not load");
        }
        else {


            for (int i = 0; i < jsRoot["StageEnemy"].size(); i++) {

                Parameter::EStageParam eSP;

                const std::string& fileName = jsRoot["StageEnemy"].at(i)["filename"];
                //auto& handleName = jsRoot["Stage"].at(i)["handlename"];
                const double& tx = jsRoot["StageEnemy"].at(i)["tx"];
                const double& ty = jsRoot["StageEnemy"].at(i)["ty"];
                const double& tz = jsRoot["StageEnemy"].at(i)["tz"];
                const double& rx = jsRoot["StageEnemy"].at(i)["rx"];
                const double& ry = jsRoot["StageEnemy"].at(i)["ry"];
                const double& rz = jsRoot["StageEnemy"].at(i)["rz"];
                const double& sx = jsRoot["StageEnemy"].at(i)["sx"];
                const double& sy = jsRoot["StageEnemy"].at(i)["sy"];
                const double& sz = jsRoot["StageEnemy"].at(i)["sz"];
                const int& numRange = jsRoot["StageEnemy"].at(i)["numrange"];  //!< ���G�̈ړ���
                const int& routine = jsRoot["StageEnemy"].at(i)["routine"];//!< ���G�̈ړ����[�`��

                Math::Vector4 pos = { tx, ty, tz };
                Math::Vector4 rot = { rx, ry, rz };
                Math::Vector4 scale = { sx, sy, sz };

                Math::Vector4 dif = { offsetX + Differ / 2.0 + Differ * numX, 0.0, offsetZ + Differ / 2.0 + Differ * numZ };

                pos = pos + dif;

                eSP.SetName(fileName);
                eSP.SetPos(pos);
                eSP.SetRot(rot);
                eSP.SetScale(scale);
                eSP.SetNumRange(numRange);
                eSP.SetRoutine(routine);

               // _vLevelRoutine.emplace_back(std::make_pair(level, routine));


                //�G�l�~�[��̈�̂��i�[
                _eStageParamV.emplace_back(eSP);

            }

            //�t���A�ԍ���1�t���A�����i�[
            _eStageNumMap.emplace(stageNo, _eStageParamV);

            //�t���A�ԍ���1�t���A�����i�[
           // _vLevelRoutineMap.emplace(stageNo, _vLevelRoutine);

        }
        //    auto sP = stageVector[k];
        //    auto pos = sP.GetPosition();
        //    Math::Vector4 dif = { offsetX + Differ / 2.0, 0.0, offsetZ + Differ / 2.0 };

//	str = "tackle";
//}
//else if (filePath.find("grab")) {
//	str = "grab";
//}
//else {
//	printf("filepath is enemy name error");
//	return;
//}


//// �p�����[�^��json����擾
/// 
//for (int i = 0; i < j.size(); i++) {
//    const auto& stageNo = j.at(i)["stageNo"];
//    const auto& handleName = j.at(i)["handlename"];
//    const auto& type = j.at(i)["type"];
//    auto& tx = j.at(i)["tx"];
//    auto& ty = j.at(i)["ty"];
//    auto& tz = j.at(i)["tz"];
//    auto& rx = j.at(i)["rx"];
//    auto& ry = j.at(i)["ry"];
//    auto& rz = j.at(i)["rz"];
//    auto& sx = j.at(i)["sx"];
//    auto& sy = j.at(i)["sy"];
//    auto& sz = j.at(i)["sz"];
//    auto& level = j.at(i)["level"];
//    Math::Vector4 pos = { tx, ty, tz };
//    Math::Vector4 rot = { rx, ry, rz };
//    Math::Vector4 scale = { sx, sy, sz };
//    Parameter::EStageParam eSP;
//    //eSP.SetName(handleName);
//    eSP.SetPos(pos);
//    eSP.SetRot(rot);
//    eSP.SetScale(scale);
//    eSP.SetLevel(level);
//    std::unordered_map<std::string, Parameter::EStageParam>     enemyStageParamMap; //!< �G�̃X�e�[�W�z�u��ۑ�
//    std::unordered_map<std::string, Type>            eType;              //!< �G�̎�ނ��L�[�Ƃ����v�f��ۑ�
//    enemyStageParamMap.emplace(handleName, eSP);
//    eType.emplace(type, enemyStageParamMap);
//    _eSMap.emplace(stageNo, eType);
//}
    }

    void EnemyParameter::LoadEnemyParam(const std::string& filePath)
    {
        ////////////////////�����ŁA�^�b�N���ƃO���u�ƃA���[�g��json��ǂݍ�����

        //// Json�t�@�C���̓ǂݍ���
        std::ifstream jsonFile(filePath);
        auto jsRoot = Json::parse(jsonFile);

        std::string fileName = filePath;

        //../resource/json/catch.json
        fileName = fileName.substr(14, 6);

        //�Ō�̕������h�b�g���ǂ���
        if (fileName.find_last_of(".") != -1) {
            fileName = fileName.substr(0, 5);
        }

        //std::string str = "";

        //�G�̎�ނœǂݍ���json��ς���
        //if (filePath.find("tackle")) {

        //    str = "tackle";
        //}
        //else if (filePath.find("catch")) {
        //    str = "catch";
        //}
        //else {
        //    printf("filepath is enemy name error");
        //    return;
        //}

        ////// �p�����[�^��json����擾	
        /*const auto&  type = jsRoot["enemy"]["type"];*/

        //const auto& level = jsRoot["enemy"]["level"];

        //at()�̒��́A���x��-1������

        for (int i = 0; i < jsRoot[fileName].size(); i++) {

            const auto& energy = jsRoot[fileName].at(i)["energy"];

#ifdef _DEBUG


            if (energy > 150.0)
            {
                printfDx("energy is over range");
                //return;
            }

#endif

            const auto& searchRange = jsRoot[fileName].at(i)["searchrange"];

#ifdef _DEBUG
            if (searchRange > 90)
            {
                printfDx("searchrange is over range");
                //return;
            }
#endif

            const auto& r = jsRoot[fileName].at(i)["r"];
            const auto& speed = jsRoot[fileName].at(i)["speed"];

            //EParam eParam;

            //eParam.SetEnergy(energy);
            //eParam.SetSearchRange(searchRange);
            //eParam.SetR(r);
            //eParam.SetSpeed(speed);

            //_enemyParamMap.emplace(type, energy);
            std::unordered_map<std::string, double> enemyParameterMap;
            //_enemyParamMap.emplace("level", level);
            enemyParameterMap.emplace("energy", energy);
            enemyParameterMap.emplace("searchrange", searchRange);
            enemyParameterMap.emplace("r", r);
            enemyParameterMap.emplace("speed", speed);

            _vDoubleMap.emplace_back(enemyParameterMap);

        }


    }


    double EnemyParameter::GetEnemyParam(const std::string& paramName, int no)
    {

        //�p�����[�^����������Ԃ�
        if (_vDoubleMap[no].count(paramName) != 0)
        {
            return _vDoubleMap[no].find(paramName)->second;
        }
        else
        {
            printfDx("enemy parameter is not");
            return 0;
        }
        return 0;
    }
}



