/*****************************************************************//**
 * @file   SceneSlideOut.h
 * @brief  スライドアウトクラス
 * 
 * @author Kota Yamawaki, hikaru Goto
 * @date   February 2022
 *********************************************************************/
#pragma once
#include "AppFrame.h"
namespace MachineHuck::Scene {

	class SceneSlideOut :public AppFrame::Scene::Scene {
	public:
        /// @brief コンストラクタ
        /// @param game ゲームクラス参照
        SceneSlideOut(AppFrame::Game& game);

        virtual ~SceneSlideOut() = default;
        /// 初期化
        void Init() override;

        //入口
        void Enter() override;
        /// 更新
        void Update() override;
        /// 描画
        void Render() override;



        //int GetYSlideOut() { return _ySlideOut; }
    private:
        int _cgXSlideOut{ 0 };  //!< xの画像ハンドル
        int _cgYSlideOut{ 0 };  //!< ｙの画像ハンドル
        int _xSlideOut{ 1920 }; //!< x方向の移動量
        int _ySlideOut{ 0 };    //!< y方向の移動量


	};

}

