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

		std::vector<int> GetPlayerVector() { return _playerV; }

	private:
		int MapHandle{ -1 };  ///< �}�b�v�摜
		int _alpha{0};
		std::unordered_map<int, int> _floorMap;  //!< �t���A�}�b�v��
		std::vector<int> _playerV; //!< �v���C���[�̂��������Ƃ̂���}�b�v��ۑ�����x�N�^�[
	};






}