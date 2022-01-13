/**
 * @file   EnemyBase.h
 * @brief  �G�l�~�[�̊��N���X
 *
 * @author Hikaru Goto
 * @date   2021/12/03
 */

#include "EnemyBase.h"
namespace MachineHuck::Enemy {
    //�R���X�g���N�^
    EnemyBase::EnemyBase(AppFrame::Game& game) : Actor::Actor{ game } {
    }
    //�f�X�g���N�^
    EnemyBase::~EnemyBase() {
    }
    //�n�b�N����
    bool IsHucked(const EnemyBase& enemy)
    {
        if (enemy.GetTypeId() != Actor::Actor::TypeId::Enemy)
        {
            return false;
        }
        else
        {
            if (enemy.isDead())
            {
                return false;
            }
            else
            {
                if (enemy.GetStatus() != EnemyBase::STATUS::ISHUCKED)
                {
                    return false;
                }
                else
                {
                    return true;
                }
            }
        }
    }
}