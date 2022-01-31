/*****************************************************************//**
 * @file   Stage.h
 * @brief  �X�e�[�W
 *
 * @author yamawaki kota, hikaru goto
 * @date   December 6 2021
 *********************************************************************/

#pragma once
#include <memory>
#include <vector>
#include <tuple>
#include "../Actor/Actor.h"

namespace MachineHuck::Model {
	class ModelComponent;
}

namespace MachineHuck::Stage {

	using Floor = std::vector<std::shared_ptr<Model::ModelComponent>>;
	using StageFloor = std::unordered_map<int, std::tuple<AppFrame::Math::Vector4, AppFrame::Math::Vector4, int>>;
	//using Collision = std::vector<std::pair<std::string, std::vector<std::string>>>;

	//                                       �t���A�ԍ�      �n���h����, �R���W�������b�V����, ���[�v���b�V�����̔z��,  �t���A�ԍ� 
	using CollisionMesh = std::unordered_map<int, std::tuple<std::string, std::string, std::vector<std::string>, int>>;

	/**
	 * @class �X�e�[�W�N���X
	 * @brief �X�e�[�W�Ɋւ���N���X
	 */
	class Stage : public Actor::Actor {
	public:
		Stage(AppFrame::Game& game);
		~Stage();

		virtual void Update() override;
		void Draw() override;

#ifdef _DEBUG

		/**
		 * @brief  �t���A�ʒu��`��
		 */
		void DrawFloor();

		/**
		 * @brief  �|���S���ɂ��t���A�쐬
		 * @return true  ����
		 *         false ���s
		 */
		bool CreateGround();
#endif 


		TypeId GetTypeId() const override { return TypeId::Stage; };

		/**
		 * @brief �X�e�[�W�̔z�u�����
		 * @return true  ����
		 *         false ���s
		 */
		bool CreateStage(AppFrame::Game& game);

		/**
		 * @brief  �v���C���[�̂���X�e�[�W�ԍ���Ԃ�
		 * @return �X�e�[�W�ԍ�
		 */
		int PlayerOnStageNumber();

		///**
		// * @brief  �}�b�v�R���W���������擾       
		// * @return _frameMapCollision
		// */
		//const int GetMapCollision() const  { return _frameMapCollision; };

		/**
		 * @brief  �}�b�v�R���W�����̃R���e�i���擾
		 * @return _collsionFloorNameMap
		 */
		CollisionMesh GetCollMap() const { return _collisionFloorNameMap; }


		/**
		 * @brief �`��t���A���擾
		 * @return _drawFloorV
		 */
		const std::vector<int> GetDrawFloorV() { return _drawFloorV; }

	private:
		//std::unique_ptr<Model::ModelComponent> _skySphere;
		std::unique_ptr<Model::ModelComponent> _ground;
		//static const int _boardW = 10;     //!< �{�[�h�̕�
		//static const int _boardH = 10;     //!< �{�[�h�̍���
		//int _board[_boardW * _boardH];     //!< �{�[�h
		//std::vector<int> _boardStageNum;   //!< �L�[���t���A�ԍ��A�o�����[���X�e�[�W�ԍ�


		StageFloor _stageFloor;                        //!< �e�X�e�[�W�t���A�ԍ����L�[�Ƃ���min�����max�̍��W����уX�e�[�W�ԍ����i�[
		//Floor _floor;                                //!< 1�t���A���i�[��
		//std::unordered_multimap<int, Floor> _allFloor; //!< �S�t���A�̏��
		std::unordered_map<int, Floor>      _allFloorMap;//!< �S�t���A�̏��
		std::vector<int>                    _drawFloorV; //!< �`�悷��t���A�ԍ����i�[

		std::unordered_map<int, std::vector<int>>  _secretVMap; //!< �B���Ă���t���A�z��𕔉��ԍ��Ŋi�[����}�b�v      
		std::vector<int>                    _secretV;           //!< �B���Ă���t���A�̔ԍ����i�[
		CollisionMesh _collisionFloorNameMap;                   //!< �R���W�����̖��O�t���[���̔z�� �L�[: �n���h���� �o�����[: �R���W�������b�V����
		std::unordered_map<int, int>        _floorStageNum; //!< �t���A�ԍ��ŃX�e�[�W�ԍ����i�[
		//std::vector<std::string> _handleV;                //�n���h�����̔z��
		int _stageNo;  //!< ���݂̃t���A�ԍ�

#ifdef _DEBUG

		static const int _boardW = 10;             //!< �{�[�h�̕�
		static const int _boardH = 10;             //!< �{�[�h�̍���
		int _board[_boardW * _boardH];
		std::vector<VERTEX3D> _groundVertex;
		std::vector<unsigned short> _groundIndex;

#endif
		//int _frameMapCollision; //!< �}�b�v�̃R���W�������

	};
}


