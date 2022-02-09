/*****************************************************************//**
 * @file   ModelComponent.h
 * @brief  �X�^�e�B�b�N���f���p�̃R���|�[�l���g
 *
 * @author yamawaki kota
 * @date   December 6 2021
 *********************************************************************/

#pragma once
#include <DxLib.h>
#include <string_view>
#include <unordered_map>

namespace MachineHuck::Actor {
	class Actor;
}


namespace MachineHuck::Model {
	///
/// @class   ModelComponent
/// @brief   �X�^�e�B�b�N���f���p�̃R���|�[�l���g�N���X�̐錾
///
	class ModelComponent {
	public:
		/// �R���X�g���N�^
		/// @param[in] filename ���f���̃t�@�C����
		ModelComponent(Actor::Actor& owner);
		/// �f�X�g���N�^
		virtual ~ModelComponent();

		/// ������
		virtual void Init();

		/// �X�V
		virtual void Update();

		/// �`��
		virtual void Draw();

		//���Ƃ����󂹂�ǂ̃R���W������`�悵�Ȃ�
		void BrokenDraw();

		/// @param collisionName �R���W�����̖��O
		void SetModelGimmick(std::string key, std::string collsionName, int no);

		std::unordered_map<int, int> GetModelGimmick() const { return _gimmickHandle; }

		///**
		// * @brief �`�� 
		// * @param pos
		// * @param rot
		// * @param scale
		// */
		//virtual void Draw(Math::Vector4 pos, Math::Vector4 rot, Math::Vector4 scale);

		/// ���f���̐ݒ�
		/// @param key AssetServer�ɓo�^�ς݂̃L�[
		/// @return ���ۂɓo�^�����ʂ��ԍ�
		virtual int SetModel(std::string_view key, int no = 0);

		/**
		 * @brief  �X�e�[�W���f���̐ݒ�       
		 * @param  key AssetServer�ɓo�^�ς݂̃L�[
		 * @return ���ۂɓo�^�����ʂ��ԍ�
		 */
		int SetMap(std::string key, int no = 0);


		/// ���W�̐ݒ�.
		/// @param[in] position ���Wx,y,z
		virtual void SetPosition(VECTOR position);


		void SetPosition(VECTOR position, float diameter);

		/// ��]�p�x�̐ݒ�.
		/// @param[in] rotation ��]�p�xx,y,z
		virtual void SetRotation(VECTOR rotation);

		/// �g�嗦�̐ݒ�.
		/// @param[in] scale �g�嗦
		virtual void SetScale(VECTOR scale);

		/// ���[���h�s��̐ݒ�
		/// @param world 
		virtual void SetMatrix(MATRIX& world);

		/**
		 * @brief  �X�e�[�W�ԍ����擾       
		 * @return _stageNum
		 */
		int GetStageNum() { return _stageNum; }

		/**
		 * @brief  �X�e�[�W�ԍ���ݒ�       
		 * @param  num
		 */
		void SetStageNum(int num) { _stageNum = num; }

		void SetHandle(const int handle) { _handle = handle; }
		int GetHandle() const { return _handle; }
		void SetColor(int index, float r, float g, float b);



	protected:
		Actor::Actor& _owner;
		int _handle{ -1 };
		bool _isLighting{ true };
		int _stageNum{-1};
		std::unordered_map<int, int> _gimmickHandle; //!< �L�[: �n���h�� �o�����[: �t���[���R���W����
	};
}


