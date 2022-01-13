#include "EffectServer.h"

std::unordered_map<std::string, std::pair<int, std::string >> EffectServer::_effects;
std::unordered_map<std::string, int>  EffectServer::_playing_effects;


int  EffectServer::LoadEffect(std::string keyname, std::string filename, float size) {
	auto ite = _effects.find(keyname);
	if (ite != _effects.end()) {
		return -1;  //既にキーがあったら失敗
	}
	int handle = LoadEffekseerEffect(filename.data(), size);

	std::pair<int, std::string > a(handle, filename);

	_effects.emplace(keyname, a);

	return _effects[keyname].first;
}


int EffectServer::GetEffect(std::string keyname) 
{
	auto ite = _effects.find(keyname);
	if (ite == _effects.end()) {
		return -1;  //キーがなかったら失敗
	}
	else
	{
		return _effects[keyname].first;
	}


}

int EffectServer::PlayEffect(std::string keyname) {
	auto ite = _effects.find(keyname);
	if (ite == _effects.end()) {
		return -1;   //キーがなかったら失敗
	}
	std::string playkeyname = "Play";
	playkeyname += keyname;

	int playhandle = PlayEffekseer3DEffect(_effects[keyname].first);

	auto ite2 = _playing_effects.find(playkeyname);
	if (ite2 == _playing_effects.end()) {
		_playing_effects.emplace(playkeyname, playhandle);//キーがなかった 新たに登録
		//_playing_effectsのkeyはPlay＋LoadEffect()で登録したキーの名前になる（例　Play光線　など）
	}

	if(ite2 != _playing_effects.end())
	{
		_playing_effects[playkeyname] = playhandle; //キーがあった　ハンドルの更新
	}
	

	return playhandle;
}

int EffectServer::GetPlayingEffect(std::string keyname) {
	auto ite = _playing_effects.find(keyname);
	if (ite == _playing_effects.end()) {
		return -1;   //キーがなかったら失敗
	}
	else
	{
		return _playing_effects[keyname];
	}
}

void EffectServer::SetPositionEffects(VECTOR _pos, std::string playeffectname) {
	// 再生中のエフェクトを移動する。
	 SetPosPlayingEffekseer3DEffect(GetPlayingEffect(playeffectname), _pos.x, _pos.y, _pos.z);
}


void EffectServer::Clear() {

	for (auto&& key : _effects) {
		DeleteEffekseerEffect(key.second.first); // エフェクトリソースを削除する。
	}
	
	_effects.clear();
	_playing_effects.clear();
}



int  EffectServer::EffekseerInit() {  //Effekseerの初期化と、Effekseerを使うために必要な事前処理

	SetUseDirect3DVersion(DX_DIRECT3D_11);

	if (Effekseer_Init(8000) == -1) {
		DxLib_End();
		return -1;
	}

	SetChangeScreenModeGraphicsSystemResetFlag(FALSE);

	Effekseer_SetGraphicsDeviceLostCallbackFunctions();

	SetUseZBuffer3D(TRUE);

	SetWriteZBuffer3D(TRUE);

	return 0;

}


void   EffectServer::SyncCamEffekseer() {
	Effekseer_Sync3DSetting(); // DXライブラリのカメラとEffekseerのカメラを同期する。
}

void EffectServer::UpdateEffect() {
	UpdateEffekseer3D(); // Effekseerにより再生中のエフェクトを更新する。
 }

void EffectServer::EffectRender() {
	DrawEffekseer3D(); // Effekseerにより再生中のエフェクトを描画する。

}

void EffectServer::EndEffekseer() {
	EffectServer::Clear();
	Effkseer_End(); // Effekseerを終了する。
}