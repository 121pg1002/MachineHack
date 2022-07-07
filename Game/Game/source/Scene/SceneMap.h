#pragma once
#include <AppFrame.h>
#include <unordered_map>

/// @file    SceneMap.h
/// @brief   �A�C�e�����
/// @date    2021/01/19
/// @author tagawa kyoga
/// @copyright (C) Amusement Media Academy All rights Resved.



namespace MachineHuck::Scene {
	class SceneMap : public AppFrame::Scene::Scene {
	public:
		/// �R���X�g���N�^
		/// @param[in] game Game�N���X�̎Q��
		SceneMap(AppFrame::Game& game);
		/// �f�X�g���N�^
		~SceneMap() = default;
		/// ������
		void Init() override;
		/// ����
		virtual void Enter() override;
		/// ����
		void Input(AppFrame::Input::InputComponent& input) override;
		/// �X�V
		void Update() override;
		/// �`��
		void Render() override;

		/**
		 * @brief �t���A�ԍ���o�^����       
		 */
		/*void RegisterFloor();*/

		//std::vector<int> GetPlayerVector() { return _playerV; }

	private:
		int _mapHandle{ -1 };   ///< �}�b�v�摜
		int _playerHandle{ -1 };//!< �v���C���[�摜
		int _goalHandle{ -1 };  //!< �S�[���摜
		int _titleHandle{-1};   //!< �^�C�g���摜
		int _selectHandleYes{-1};  //!< �I�����摜(Yes)
		int _selectHandleNo{ -1 };  //!< �I�����摜(No)


		std::vector<int> _mapHandles; //!< �~�j�}�b�v�̉摜
		int _alpha{0};
		std::unordered_map<int, int> _floorMap;  //!< �t���A�}�b�v��
		//std::vector<int> _playerV; //!< �v���C���[�̂��������Ƃ̂���}�b�v��ۑ�����x�N�^�[
		int _colorFrame; //!< �_�ł̃t���[���p
		bool _titleSelectFlag; //!< �^�C�g���ɖ߂�t���O���o��
		int _no;               //!< No = 0, Yes = 1
	};






}