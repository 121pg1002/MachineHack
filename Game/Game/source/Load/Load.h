/**
 * @file   Load.h
 * @brief  jsonから読み込むクラス
 *
 * @author Hikaru Goto
 * @date   2021/11/30
 */


#pragma once
#include<unordered_map>
#include<string>
#include<DxLib.h>

/*
*@brief ステージ情報格納クラス
*/
struct stage_param 
{

	std::string filename;
	int _stageNo;

};

/*
*@brief 敵情報格納クラス
*/
struct enemy_param 
{
	std::string _name;
	VECTOR _position;
	VECTOR _rotation;
	VECTOR _scale;

};

/*
*@brief ギミック情報格納クラス
*/
struct gimmick_param 
{
	std::string _name;
	VECTOR _position;
	VECTOR _rotation;
	VECTOR _scale;

};
    /*
	*@brief json読み込み用のクラス
	*/
	class Load
	{
	public:
		/*
		*@brief コンストラクタ
		*/
		Load();

		/*
		*@brief デストラクタ
		*/
		~Load();

		/*
		* @brief ステージのパラメーターをjsonから読み込み
		* @param          key キー
		* @param asynchronous 非同期フラグ
		*/
		void LoadStageFromJson(std::string_view key, bool asynchronous);

		/*
		* @brief 敵のパラメーターをjsonから読み込み
		* @param          key キー
		* @param asynchronous 非同期フラグ
		*/
		void LoadEnemyFromJson(const std::string& path, bool asynchronous);

		/*
		* @brief ギミックのパラメーターをjsonから読み込み
		* @param          key キー
		* @param asynchronous 非同期フラグ
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


