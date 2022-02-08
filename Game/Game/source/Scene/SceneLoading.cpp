
/*****************************************************************//**
 * @file   SceneLoading.cpp
 * @brief  InGameとのつなぎ目のクラス
 * 
 * @author hikaru Goto
 * @date   January 2022
 *********************************************************************/
#include "SceneLoading.h"
#include "../Flag/FlagData.h"

namespace MachineHuck::Scene{

    SceneLoading::SceneLoading(AppFrame::Game& game)
        :Scene{ game }
    {

    }


    /// 更新
    void SceneLoading::Update() {
        //_alpha = (_alpha + 8) % 255;
        //if (_alpha > 200) {


            GetSceneServer().GoToScene("InGame", "", false);
        //    _alpha = 255;
            GetSceneServer().PopBack();
           // GetSceneServer().PopBack();
       // }
    }



}
