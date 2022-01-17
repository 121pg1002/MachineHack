/*****************************************************************//**
 * @file   EffectServer.cpp
 * @brief  エフェクトサーバー
 *
 * @author yamawaki kota
 * @date   December 28 2021
 *********************************************************************/
#pragma once
#include <unordered_map>
#include <string>
#include <memory>
#include "appframe.h"
namespace MachineHuck::Effect {
	class EffectServer {
	public:


		EffectServer() {};
		~EffectServer() {};

		//キーとファイルネーム、エフェクトのサイズを指定してエフェクトの読み込み＋_effectsへの登録
		//戻り値　ハンドル 成功　 -1 失敗 : 引数(左から）任意のキーの名前、ファイルへのパス名、エフェクトのサイズ指定
		static int LoadEffect(std::string keyname, std::string filename, float size);

		//エフェクトハンドルの取得（戻り値_ハンドル： 引数_Load effectで指定した任意のキー）
		static int GetEffect(std::string keyname);

		//エフェクトの再生＋_playing_effectsへの登録　
		//戻り値  ハンドル 成功　-1 失敗 ： 引数　LoadEffect()で読み込んだキーの名前
		static int PlayEffect3D(std::string keyname);

		//エフェクトの再生＋_playing_effectsへの登録　
		//戻り値  ハンドル 成功　-1 失敗 ： 引数　LoadEffect()で読み込んだキーの名前
		static int PlayEffect2D(std::string keyname);

		//再生中エフェクトのハンドルの取得
		//戻り値　ハンドル 成功　-1 失敗：引数 _playing_effectsに登録されているキー名（Play＋引数_PlayEffect()で指定した任意のキー名）
		static int GetPlayingEffect(std::string playingkeyname);

		//エフェクトの位置を決定する 引数(左から）エフェクトの位置、_playing_effectsに登録されているキー名（Play＋引数_PlayEffect()で指定した任意のキー名）
		static void SetPositionEffect3D(VECTOR _pos, std::string playeffectname);

		//エフェクトの位置を決定する 引数(左から）エフェクトの位置、_playing_effectsに登録されているキー名（Play＋引数_PlayEffect()で指定した任意のキー名）
		static void SetPositionEffect2D(std::pair<int, int>_pos2D, std::string playeffectname);

		//マップに登録されているすべての要素の削除、エフェクトリソースの解放
		static void Clear();


		//メンバに関連しないEffekseerの関数

		//Effekseerの初期化とEffekseerを使うために必要な事前処理
		static int EffekseerInit();
		// Effekseerの終了処理
		static void EndEffekseer();

		//1フレームに一回呼び出し
		// 3D関係
		// DXライブラリのカメラとEffekseerのカメラを同期する。（3D時）
		static void SyncCamEffekseer();
		// Effekseerにより再生中のエフェクトを更新する。
		static void UpdateEffect3D();
		// Effekseerにより再生中のエフェクトを描画する。
		static void RenderEffect3D();
		//2D関係
		// Effekseerにより再生中のエフェクトを更新する。
		static void UpdateEffect2D();
		// Effekseerにより再生中のエフェクトを描画する。
		static void RenderEffect2D();


	private:
		//エフェクトのハンドルを管理するマップ　（キー（任意の文字列)：値 (ハンドルとファイル名のペア））
		static std::unordered_map<std::string, std::pair<int, std::string >> _effects;
		//再生中エフェクトのハンドルを管理するマップ　（キー（任意の文字列)：値 (再生中エフェクトのハンドル））
		static std::unordered_map<std::string, int>  _playing_effects;



	};
}