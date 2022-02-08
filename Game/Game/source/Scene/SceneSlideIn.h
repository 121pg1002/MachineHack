/*****************************************************************//**
 * @file   SceneSlideIn.h
 * @brief  スライドインクラス
 * 
 * @author Kota Yamawaki, hikaru Goto
 * @date   February 2022
 *********************************************************************/
#pragma once
#include "AppFrame.h"
namespace MachineHuck::Scene {

	//スライドインクラス
	class SceneSlideIn : public AppFrame::Scene::Scene {
	public:
        /// @brief コンストラクタ
        /// @param game ゲームクラス参照
        SceneSlideIn(AppFrame::Game& game);

        virtual ~SceneSlideIn() = default;

        //入口
        void Enter() override;

        /// 初期化
        void Init() override;

        /// 更新
        void Update() override;
        /// 描画
        void Render() override;

        //int GetYSlideIn() { return _ySlideIn; }
    private:
        int _cgXSlideIn{ 0 };  //!< xの画像ハンドル
        int _cgYSlideIn{ 0 };  //!< ｙの画像ハンドル
        int _xSlideIn{ 1920 }; //!< x方向の移動量
        int _ySlideIn{ 0 };    //!< y方向の移動量


	};

}
