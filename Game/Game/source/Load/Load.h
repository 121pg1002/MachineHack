/**
 * @file   Load.h
 * @brief  json����ǂݍ��ރN���X
 *
 * @author Hikaru Goto
 * @date   2021/11/30
 */


#pragma once
#include<unordered_map>
#include<string>
#include<DxLib.h>

/*
*@brief �X�e�[�W���i�[�N���X
*/
struct stage_param 
{

	std::string filename;
	int _stageNo;

};

/*
*@brief �G���i�[�N���X
*/
struct enemy_param 
{
	std::string _name;
	VECTOR _position;
	VECTOR _rotation;
	VECTOR _scale;

};

/*
*@brief �M�~�b�N���i�[�N���X
*/
struct gimmick_param 
{
	std::string _name;
	VECTOR _position;
	VECTOR _rotation;
	VECTOR _scale;

};
    /*
	*@brief json�ǂݍ��ݗp�̃N���X
	*/
	class Load
	{
	public:
		/*
		*@brief �R���X�g���N�^
		*/
		Load();

		/*
		*@brief �f�X�g���N�^
		*/
		~Load();

		/*
		* @brief �X�e�[�W�̃p�����[�^�[��json����ǂݍ���
		* @param          key �L�[
		* @param asynchronous �񓯊��t���O
		*/
		void LoadStageFromJson(std::string_view key, bool asynchronous);

		/*
		* @brief �G�̃p�����[�^�[��json����ǂݍ���
		* @param          key �L�[
		* @param asynchronous �񓯊��t���O
		*/
		void LoadEnemyFromJson(const std::string& path, bool asynchronous);

		/*
		* @brief �M�~�b�N�̃p�����[�^�[��json����ǂݍ���
		* @param          key �L�[
		* @param asynchronous �񓯊��t���O
		*/
		void LoadGimmickFromJson(std::string& path, bool asynchronous);

		std::unordered_map<std::string, stage_param>   GetStageParamMap()   const { return _stageParamMap; }
		std::unordered_map<std::string, enemy_param>   GetEnemyParamMap()   const { return _enemyParamMap; }
		std::unordered_map<std::string, gimmick_param> GetGimmickParamMap() const { return _gimmickParamMap; }

	private:

		std::unordered_map<std::string, stage_param>   _stageParamMap;
		std::unordered_map<std::string, enemy_param>   _enemyParamMap;
		std::unordered_map<std::string, gimmick_param> _gimmickParamMap;
	};


