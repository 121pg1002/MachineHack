
/*****************************************************************//**
 * @file   GParam.cpp
 * @brief  �M�~�b�N�̏��N���X
 * 
 * @author hikaru Goto
 * @date   December 30 2021
 *********************************************************************/
#include "GParam.h"
#include <DxLib.h>

namespace MachineHuck::Parameter {
	void GParam::SetCollisionFrame(int handle) {

		// �}�b�v
		//_handleMap = MV1LoadModel("res/Dungeon/Dungeon.mv1");
		// �R���W�������̐���
		//_collisionFrame = MV1SearchFrame(handle, "dungeon_collision");
		//MV1SetupCollInfo(handle, _collisionFrame, 16, 16, 16);

		//// �R���W�����̃t���[����`�悵�Ȃ��ݒ�
		//MV1SetFrameVisible(handle, _collisionFrame, false);
		//// ���ʒu�̐ݒ�
		////_colSubY = 40.f;

		////// �ړ�������ŃR���W��������
		//MV1_COLL_RESULT_POLY hitPoly;
		////// ��l���̍��ʒu���牺�����ւ̒���
		//hitPoly = MV1CollCheck_Line(handle, _collisionFrame,
		//	VAdd(_vPos, VGet(0, _colSubY, 0)), VAdd(_vPos, VGet(0, -99999.f, 0)));
		//if (hitPoly.HitFlag) {
		//  //��������
		//}
		//else {
		//  //������Ȃ�����
		//}
	}
}


