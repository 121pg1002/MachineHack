
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
        :Scene{ game }{

    }


    /// �X�V
    void SceneLoading::Update() {
        //_alpha = (_alpha + 8) % 255;
        //if (_alpha > 200) {

      if (Flag::FlagData::GetInGameExitFlag()) {
        GetSceneServer().GoToScene("InGame", "", false);
        Flag::FlagData::SetBlackOutFlag(true);
      }
      else {
        GetSceneServer().GoToScene("InGame", "", false);
      }
            
            GetSceneServer().PopBack();
            //GetSceneServer().PopFront();
        //    _alpha = 255;
            
           // GetSceneServer().PopBack();
       // }
    }



}
