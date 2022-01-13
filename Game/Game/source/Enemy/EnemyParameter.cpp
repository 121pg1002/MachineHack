/*****************************************************************//**
 * @file   EnemyParameter.cpp
 * @brief  エネミーのパラメーターをjsonから読み込む
 * 
 * @author hikaru  Goto
 * @date   December 26 2021
 *********************************************************************/
#include"../Enemy/EnemyParameter.h"
#include "../nlohmann/json.hpp"
#include <filesystem>
#include <fstream> 
#include "../../../../AppFrame/source/Asset/AssetServer.h"


using Json = nlohmann::json;
namespace Math = AppFrame::Math;

namespace MachineHuck::Enemy {
    //コンストラクタ
    EnemyParameter::EnemyParameter()
    {
        _eType.clear();
        _eSMap.clear();
        /*_enemyStageParamMap.clear();*/
            //_enemyParamMap.clear();//EParam
            //_enemyParameterMap.clear();//double
        _vDoubleMap.clear();
    }
    //デストラクタ
    EnemyParameter::~EnemyParameter()
    {
        _eType.clear();
        _eSMap.clear();
        /*_enemyStageParamMap.clear();*/
        //_enemyParamMap.clear();
        //_enemyParameterMap.clear();
        _vDoubleMap.clear();
    }
    //エネミーのステージ配置情報をjsonから読み込む
    void EnemyParameter::LoadStageEnemyParam(const std::string& filePath)
    {
        //// Jsonファイルの読み込み
        std::ifstream jsonFile(filePath);
        auto jsRoot = Json::parse(jsonFile);
        auto j = jsRoot["stageenemy"];
        //敵の種類で読み込むjsonを変える
        //if (filePath.find("tackle")) {

        //	str = "tackle";
        //}
        //else if (filePath.find("grab")) {
        //	str = "grab";
        //}
        //else {
        //	printf("filepath is enemy name error");
        //	return;
        //}

        //// パラメータをjsonから取得
        /// 
        for (int i = 0; i < j.size(); i++) {
            const auto& stageNo = j.at(i)["stageNo"];
            const auto& handleName = j.at(i)["handlename"];
            const auto& type = j.at(i)["type"];
            auto& tx = j.at(i)["tx"];
            auto& ty = j.at(i)["ty"];
            auto& tz = j.at(i)["tz"];
            auto& rx = j.at(i)["rx"];
            auto& ry = j.at(i)["ry"];
            auto& rz = j.at(i)["rz"];
            auto& sx = j.at(i)["sx"];
            auto& sy = j.at(i)["sy"];
            auto& sz = j.at(i)["sz"];
            auto& level = j.at(i)["level"];
            Math::Vector4 pos = { tx, ty, tz };
            Math::Vector4 rot = { rx, ry, rz };
            Math::Vector4 scale = { sx, sy, sz };
            Parameter::EStageParam eSP;
            //eSP.SetName(handleName);
            eSP.SetPos(pos);
            eSP.SetRot(rot);
            eSP.SetScale(scale);
            eSP.SetLevel(level);
            std::unordered_map<std::string, Parameter::EStageParam>     enemyStageParamMap; //!< 敵のステージ配置を保存
            std::unordered_map<std::string, Type>            eType;              //!< 敵の種類をキーとした要素を保存
            enemyStageParamMap.emplace(handleName, eSP);
            eType.emplace(type, enemyStageParamMap);
            _eSMap.emplace(stageNo, eType);
        }
    }

    void EnemyParameter::LoadEnemyParam(const std::string& filePath)
    {
        ////////////////////ここで、タックルとグラブとアラートのjsonを読み込もう

        //// Jsonファイルの読み込み
        std::ifstream jsonFile(filePath);
        auto jsRoot = Json::parse(jsonFile);

        auto str = "";

        //敵の種類で読み込むjsonを変える
        if (filePath.find("tackle")) {

            str = "tackle";
        }
        else if (filePath.find("grab")) {
            str = "grab";
        }
        else {
            printf("filepath is enemy name error");
            return;
        }

        ////// パラメータをjsonから取得	
        /*const auto&  type = jsRoot["enemy"]["type"];*/

        //const auto& level = jsRoot["enemy"]["level"];

        //at()の中は、レベル-1を入れる

        for (int i = 0; i < jsRoot[str].size(); i++) {

            const auto& energy = jsRoot[str].at(i)["energy"];

#ifdef _DEBUG


            if (energy > 150.0)
            {
                printfDx("energy is over range");
                //return;
            }

#endif

            const auto& searchRange = jsRoot[str].at(i)["searchrange"];

#ifdef _DEBUG
            if (searchRange > 90)
            {
                printfDx("searchrange is over range");
                //return;
            }
#endif

            const auto& r = jsRoot[str].at(i)["r"];
            const auto& speed = jsRoot[str].at(i)["speed"];

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

        //パラメータがあったら返す
        if (_vDoubleMap[no].contains(paramName))
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



