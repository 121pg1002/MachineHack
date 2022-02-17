///
/// @file    SceneMap.cpp
/// @brief   マップ画面
/// @date    2021/01/19
/// @author tagawa kyoga
/// @copyright (C) Amusement Media Academy All rights Resved.
///

#include "SceneMap.h"
#include <algorithm>
#include "AppFrame.h"
#include "../Flag/FlagData.h"

namespace {
    constexpr double FloorSize = 166.0; //!< 1フロアのサイズ
    constexpr double LineSize = 1.0;  //!< 描画する線のサイズ
    constexpr double BoardSize = 5.0; //!< 行と列のサイズ
    constexpr double StartX = 1920/2 - FloorSize * BoardSize/2.0;
    constexpr double StartHeight = 220; //!< 上の開始高さ空ける分
    constexpr double StartY = 150.0;
    constexpr int    GoalNum = 21;      //!< ゴールのフロア番号
    constexpr int    Space = 10;        //!< 枠の間の間隔

}

namespace MachineHuck::Scene {
    /// コンストラクタ
    SceneMap::SceneMap(AppFrame::Game& game):Scene{ game }{
        _colorFrame = 0;
        _mapHandles.clear();
    }
    /// 初期化
    void  SceneMap::Init() {
        // 使用する画像のテーブル
        const AppFrame::Asset::AssetServer::TextureMap textureToUsed{
            {"MapBg",  {"Texture/SceneMap/mapUI.png",          1, 1, 1920, 1080}},
            {"Map0",   {"Texture/SceneMap/map0_small.png", 1, 1, 160, 160}},
            {"Map1",   {"Texture/SceneMap/map1_small.png", 1, 1, 160, 160}},
            {"Map2",   {"Texture/SceneMap/map2_small.png", 1, 1, 160, 160}},
            {"Map3",   {"Texture/SceneMap/map3_small.png", 1, 1, 160, 160}},
            {"Map4",   {"Texture/SceneMap/map4_small.png", 1, 1, 160, 160}},
            {"Player", {"Texture/SceneMap/player.png", 1, 1, 166, 166}},
            {"Goal",   {"Texture/SceneMap/goal.png", 1, 1, 166, 166}},
            {"BackTitle", {"Texture/SceneMap/title.png", 1, 1, 1920, 1080}},
            {"Yes", {"Texture/SceneMap/Yes.png", 1, 1, 1920, 1080}},
            {"No", {"Texture/SceneMap/No.png", 1, 1, 1920, 1080}}
          /*    {"GameTitleAMG",        {"GameTitle.png",        1, 1, 1553, 224}},
              {"LeftClickToStartAMG", {"LeftClickToStart.png", 1, 1, 1135, 107}},*/
        };
        // アセットサーバーの取得
        auto& as = GetAssetServer();
        // 画像の読み込み
        as.LoadTextures(textureToUsed);

        // 画像のハンドル取得
        _mapHandle = as.GetTexture("MapBg");
        _playerHandle = as.GetTexture("Player");
        _goalHandle = as.GetTexture("Goal");
        _titleHandle = as.GetTexture("BackTitle");
        _selectHandleYes = as.GetTexture("Yes");
        _selectHandleNo = as.GetTexture("No");

        for (int i = 0; i < 5; i++) {
        
            auto&& handle = as.GetTexture("Map" + std::to_string(i));
            _mapHandles.push_back(handle);
        }



        /*  _gameTitleHandle = as.GetTexture("GameTitle");
          _leftClickToStart = as.GetTexture("LeftClickToStart");*/

          // サウンドコンポーネントの取得
        AppFrame::Asset::AssetServer::SoundMap soundToUsed{
            {"close"  ,{"se/se_close.wav" ,false}}
        };

        GetAssetServer().LoadSounds(soundToUsed);

    }
    ///
    /// 入口
    /// 
    void  SceneMap::Enter() {
       // _alpha = 0;
        _colorFrame = 0;
        _no = 0;
        _alpha = 255;
        _titleSelectFlag = false;
    }
    ///
    /// 入力
    ///
    void  SceneMap::Input(AppFrame::Input::InputComponent& input) {

        //タイトルに戻る選択肢を出す
        if (input.GetJoypad().Button_Y()) {

            if (!_titleSelectFlag) {

                _titleSelectFlag = true;
                _alpha = 128;
            
            }
            else {
                _titleSelectFlag = false;
                _alpha = 255;
                _no = 0; //No
            }
        }

        //No = 1かYes = 0か
        if (_titleSelectFlag) {
        
            if (input.GetJoypad().LHorison() < 0.0) {
                _no = 1; //!< Yes
            }
            else if(input.GetJoypad().LHorison() > 0.0){
                _no = 0; //!< No
            }

            //AボタンかつYesを選択中ならタイトルに戻る
            if (input.GetJoypad().Button_A()) {
            
                if (_no == 0) {
                    _titleSelectFlag = false;
                    _alpha = 255;
                
                }
                else {

                    //GetSceneServer().GoToScene("Title");
                    Flag::FlagData::SetInGameExitFlag(true);
                    //Flag::FlagData::SetFadeOutFlag(true);
                    GetSceneServer().GoToScene("Loading", "FadeOut", false);
                  //Flag::FlagData::SetBlackOutFlag(true);
                    //GetSceneServer().PopBack();
                    //GetSceneServer().GoToScene("Title");

                    GetSoundComponent().PlayStopMusic();
                }
            
            }
        
        }

        //インゲームに戻る
        if (input.GetJoypad().Button_X()) {
            //*se マップ画面を閉じる
            GetSoundComponent().Play("close");

            // GetSceneServer().PopBack();
             //GetSceneServer().PushBack("InGame",1);

            GetSceneServer().GoToScene("InGame", false);
            //GetSceneServer().PopBack();
           // _alpha = 255;
        }

    }
    /// 更新
    void  SceneMap::Update() {
       // _alpha = (_alpha + 8) % 255;
        if (!_titleSelectFlag) {
            _colorFrame++;
        }
        
        //_playerV = Flag::FlagData::GetPlayerFloorVec(); //!< プレイヤーの行ったフロア番号配列を取得
    }

    ////フロア番号を登録する
    //void SceneMap::RegisterFloor() {
    //
    //    //これだとマップ画面を開いていないときに登録されない
    //    auto&& playerNum = Flag::FlagData::GetPlayerFloorNum();

    //    //ベクターの中から探す
    //    auto it = std::find(_playerV.begin(), _playerV.end(), playerNum);

    //    //存在しないならば
    //    if (it == _playerV.end()) {
    //        //追加
    //        _playerV.push_back(playerNum);
    //    }
    //
    //}

    ///
    /// 描画
    ///
    void  SceneMap::Render() {

        SetDrawBlendMode(DX_BLENDMODE_ALPHA, _alpha);

        DrawGraph(0, 0, _mapHandle, true);

        auto playerV = Flag::FlagData::GetPlayerFloorVec();
        //int StartY = 100.0;
        int offsetX = StartX;
        int offsetY = StartY;
        int red = 255; int green = 0; int blue = 0;

        //y方向
        for (int i = 0; i < BoardSize; i++) {
        
            offsetX = StartX;
            //x方向
            for (int j = 0; j < BoardSize; j++) {
            
                //unordered_mapでフロア番号と
                //ここの掛け算をフロア番号と一致した場合に色の処理を分断する
                auto value = std::find(playerV.begin(), playerV.end(), i * BoardSize + j);

                //主人公のいる番号のフロア枠を緑にする
                if (Flag::FlagData::GetPlayerFloorNum() == i * BoardSize + j && _colorFrame % 60 < 30) {
                    red = 0; green = 255; blue = 0;
                } //ゴールの色を赤色にする
                else if (GoalNum == i * BoardSize + j) {
                    red = 255; green = 0; blue = 0;
                }
                //その番号がいったことがある場合(白)
                else if (value != playerV.end()) {
                    red = 255; green = 255; blue = 255;
                }  //グレーにする
                else {
                    red = 125; green = 125; blue = 125;
                }

                //AppFrame::Math::Vector2 LeftUp    = { static_cast<double>(offsetX), FloorSize * BoardSize - static_cast<double>(offsetY) + FloorSize + StartHeight };
                //AppFrame::Math::Vector2 LeftDown  = { static_cast<double>(offsetX), FloorSize * BoardSize - static_cast<double>(offsetY) + StartHeight };
                //AppFrame::Math::Vector2 RightUp   = { static_cast<double>(offsetX) + FloorSize, FloorSize * BoardSize - static_cast<double>(offsetY) + FloorSize + StartHeight };
                //AppFrame::Math::Vector2 RightDown = { static_cast<double>(offsetX) + FloorSize, FloorSize * BoardSize - static_cast<double>(offsetY) + StartHeight };



                //枠の描画
                DrawBoxAA(offsetX, FloorSize * BoardSize - offsetY + FloorSize + StartHeight, offsetX + FloorSize, FloorSize * BoardSize - offsetY + StartHeight, GetColor(red, green, blue), false, Space - 3.0);

                //2変数を扱うだけなのでy座標をz座標で置き換えている
                //DrawLineAA(LeftUp.GetX(),    LeftUp.GetZ(),    LeftDown.GetX(),  LeftDown.GetZ(), GetColor(red, green, blue), Space - 2.0);
                //DrawLineAA(LeftDown.GetX(),  LeftDown.GetZ(),  RightDown.GetX(), RightDown.GetZ(), GetColor(red, green, blue), Space - 2.0);
                //DrawLineAA(RightDown.GetX(), RightDown.GetZ(), RightUp.GetX(),   RightUp.GetZ(), GetColor(red, green, blue), Space - 2.0);
                //DrawLineAA(RightUp.GetX(),   RightUp.GetZ(),   LeftUp.GetX(),    LeftUp.GetZ(), GetColor(red, green, blue), Space - 2.0);


                //if (i == 0 && j == 0) {

                //    for (auto k : _mapHandles) {

                if (i == 0) {

                    if (value != playerV.end()) {
                        //マップ画面の表示(仮)
                        DrawGraph(offsetX + 3, FloorSize * BoardSize - offsetY + StartHeight + 3, _mapHandles[i * BoardSize + j], false);

                    }
                
                }




                //プレイヤーがゴールにいないとき
                if (GoalNum == i * BoardSize + j && GoalNum != Flag::FlagData::GetPlayerFloorNum()) {
                
                    DrawGraph(offsetX, FloorSize * BoardSize - offsetY + StartHeight, _goalHandle, true);
                
                }

                //プレイヤーの位置座標に表示
                if (Flag::FlagData::GetPlayerFloorNum() == i * BoardSize + j) {
                
                    DrawGraph(offsetX + 1, FloorSize * BoardSize - offsetY + StartHeight + 1, _playerHandle, true);
                
                }

                

                //    }
                //
                //}

                //DrawBox(offsetX, offsetY, offsetX + FloorSize, offsetY + FloorSize, GetColor(red, green, blue), false); //!< 白
                //DrawBox(offsetX, offsetY, offsetX + FloorSize, offsetY + FloorSize, GetColor(red, green, blue), false); //!< 緑
                //DrawBox(offsetX, offsetY, offsetX + FloorSize, offsetY + FloorSize, GetColor(red, green, blue), false); //!< 赤
                //枠の間隔
                //if (j == 0) {
                    offsetX += FloorSize + Space;
                //}
                //else {
                //    offsetX += FloorSize;
                //}
                
            }

            offsetY += FloorSize + Space - 2;
        }

        SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);

        //タイトルフラグがオンか
        if (_titleSelectFlag) {
        
            DrawGraph(0, 0, _titleHandle, true);

            //Noを選択中なら
            if (_no == 0) {
                SetDrawBlendMode(DX_BLENDMODE_ALPHA, _alpha);
            }
                DrawGraph(0, 0, _selectHandleYes, true);

            if (_no == 0) {
                SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);
            }
            
            //Yesを選択中なら
            if (_no == 1) {
                SetDrawBlendMode(DX_BLENDMODE_ALPHA, _alpha);
            }
            DrawGraph(0, 0, _selectHandleNo, true);
            if (_no == 1) {
                SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);
            }
        
        }
        
        //SetDrawBlendMode(DX_BLENDMODE_ALPHA, _alpha);
        // DrawGraph(1920 / 2 - 1135 / 2, 700 - 107 / 2, _leftClickToStart, TRUE);

        // DrawGraph(0, 0, _gameAMGHandle, true);
    }
}
