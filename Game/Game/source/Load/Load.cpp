/**
 * @file   Load.h
 * @brief  json����ǂݍ��ރN���X
 *
 * @author Hikaru Goto
 * @date   2021/11/30
 */

#include"Load.h"
#include <filesystem>

Load::Load() 
{
    _stageParamMap.clear();
    _enemyParamMap.clear();
    _gimmickParamMap.clear();
}

Load::~Load() 
{
    _stageParamMap.clear();
    _enemyParamMap.clear();
    _gimmickParamMap.clear();
}

void Load::LoadStageFromJson(std::string_view key, bool asynchronous) 
{


}

void Load::LoadEnemyFromJson(const std::string& path, bool asynchronous)
{
//	std::filesystem::path fs = path;
//std::string filename = fs.parent_path().string() + "/";
//
//// Json�t�@�C���̓ǂݍ���
//std::ifstream jsonFile(path);
//auto jsRoot = nlohmann::json::parse(jsonFile);
//
//// �p�����[�^��json����擾
//_name = jsRoot["handle"];
//_position.x = jsRoot["px"];
//_position.y = jsRoot["py"];
//_position.z = jsRoot["pz"];
//
//_rotation.x = jsRoot["rx"];
//_rotation.y = jsRoot["ry"];
//_rotation.z = jsRoot["rz"];
//
//_scale.x    = jsRoot["sx"];
//_scale.y    = jsRoot["sy"];
//_scale.z    = jsRoot["sz"];
//
//_width      = jsRoot["width"];
//_depth      = jsRoot["depth"];
//
///////////////////////////////////�������y�̂�܂�����
////ResourceServer�Ƀn���h����ۑ�
//AssetServer::RegisterModel("Enemy", "enemy", param.handlename_, _async_flag);
//
////���f���̏����p�����[�^�����ꂼ��Z�b�g
//int model_handle = AssetServer::GetModel(_handlename);
//
//int model_handle = 
//MV1SetPosition(model_handle, param.position_);
//MV1SetRotationXYZ(model_handle, param.rotation_);
//MV1SetScale(model_handle, param.scale_);
//
//_enemy_param_map.emplace(param._handlename);

}
