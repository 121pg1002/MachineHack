
/*****************************************************************//**
 * @file   SceneLoading.cpp
 * @brief  InGame�Ƃ̂Ȃ��ڂ̃N���X
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


    /// �X�V
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
