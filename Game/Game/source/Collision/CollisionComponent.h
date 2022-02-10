
/*****************************************************************//**
 * @file   CollisionComponent.h
 * @brief  �Փ˔���N���X
 * 
 * @author hikaru Goto
 * @date   December 19 2021
 *********************************************************************/

#include <memory>
#include <tuple>
#include <DxLib.h>
#include "AppFrame.h"


namespace Math = AppFrame::Math;


//struct Sphere {
//  Sphere(const Math::Vector4& center, float radius);
//  bool Contains(const Math::Vector4& point) const;
//
//  Math::Vector4 center;
//  float radius;
//};

//bool Intersect(const Sphere& a, const Sphere& b);
namespace MachineHuck::Actor {
	class Actor;
}

namespace MachineHuck::Model {
	class ModelComponent;
}

namespace MachineHuck::Collision {
	class CollisionComponent {
	public:
		//enum class ReportId {
		//  None,
		//  HitFromPlayer,
		//  HitFromEnemy,
		//  HuckedFromPlayer,
		//};

		//struct Report {
		//  ReportId id{ReportId::None};
		//  Math::Vector4 position{0, 0, 0};
		//};
		using AABB = std::tuple<double, double, double, double>;
		using WarpMap = std::unordered_map<std::string, std::pair<std::pair<int, int>, int>>;
		using WarpName = std::unordered_multimap<int, std::unordered_multimap<std::string, std::string>>;
		using Floor = std::vector<std::shared_ptr<Model::ModelComponent>>;


		CollisionComponent(Actor::Actor& owner);
		~CollisionComponent();

		//void EnemyFromPlayer();
		//void PlayerFromEnemy();

		//void SetReport(Report report) { *_report = report; }
		//Report& GetReport() const { return *_report; }

		/**
		 * @brief  �~�Ɖ~�̓����蔻����s��
		 * @param  act1 ����
		 * @param  act2 ����
		 * @return ����
		 */
		bool CircleToCircle(const Actor::Actor& act1, const Actor::Actor& act2);

		/**
		 * @brief  ��`�Ƌ�`�̓����蔻����s��
		 * @param  act1 ����
		 * @param  act2 ����
		 * @return ����
		 */
		bool AABBToAABB(const Actor::Actor& act1, const Actor::Actor& act2);

		/**
		 * @brief �ӂ̎l�p�`�̕ӂ̈�ӂ𓾂� 
		 * @param center
		 * @param halfExtends
		 * @param rot
		 * @param point
		 * @return �n�_�ƏI�_�̃y�A�^
		 */
		//std::pair<Math::Vector2, Math::Vector2 > GetOrientedRectangleEdge(Math::Vector4 center, Math::Vector2 halfExtends, double rot, int point);

		///**
		// * @brief �t�x�N�g����Ԃ�
		// * @param vec
		// * @return �����̋t�x�N�g��
		// */
		//Math::Vector2 GetNeGateVector(Math::Vector2 vec);

		///**
		// * @brief �x�N�g������]������
		// * @param vec    xz�x�N�g��
		// * @param radian ���W�A��
		// * @return ��]�����x�N�g��
		// */
		//Math::Vector2 GetRotateVector(Math::Vector2 vec, double radian);
		



		/**
		 * @brief  �~�Ƌ�`�̓����蔻����s��
		 * @param  act1 ����(�~)
		 * @param  act2 ����(��`)
		 * @return ����
		 */
		bool CircleToAABB(const Actor::Actor& act1, const Actor::Actor& act2);


		///**
		// * @brief  �~�Ƌ�`�̓����蔻����s��
		// * @param  act1 ����(�~)
		// * @param  act2 ����(��`)
		// * @return ����
		// */
		//bool CollisionCircleToAABB(const Actor::Actor& act1, const Actor::Actor& act2);

	
		/**
		 * @brief  �~�Ƌ�`�̓����蔻����s��       
		 * @param  act  �v���C���[
		 * @param  min  �ŏ����W
		 * @param  max  �ő���W
		 * @return ����
		 */
		bool CircleToAABB(const Actor::Actor& act, const AppFrame::Math::Vector4 min, const AppFrame::Math::Vector4 max);


		/**
		 * @brief  �~�Ɖ�]������`�̓����蔻����s��
		 * @param  act1 ����(�~)
		 * @param  act2 ����(��]������`)
		 * @return
		 */
		bool CircleToOrientedAABB(const Actor::Actor& act1, const Actor::Actor& act2);

		/**
		 * @brief ��`�Ɖ�]������`�̓����蔻����s�� 
		 * @param own (��`)
		 * @param target(��]������`)
		 * @return true  ��������
		 *         false �������Ă��Ȃ�
		 */
		bool AABBToOrientedAABB(const Actor::Actor& own, const Actor::Actor& target);

		/**
		 * @brief  �~�Ɛ����̓����蔻����s��
		 * @param  act1 ����
		 * @param  act2 ����
		 * @return ����
		 */
		//bool CircleToLine(const Actor::Actor& act1, const Actor::Actor& act2);

		/**
		 * @brief  �~�Ɛ����̓����蔻����s��
		 * @param  act1 ����
		 * @param  start �n�_
		 * @param  end �I�_ 
		 * @return ����
		 */
		bool CircleToLine(const Actor::Actor& act1, const Math::Vector4 start, const Math::Vector4 end);




		/*
		*@brief �~�Ɛ�`�̓����蔻����s��
		*/
		bool FanToPoint(const Actor::Actor& act1, const Actor::Actor& act2);

		/**
		 * @brief  �~�Ɛ�`�̓����蔻����s��
		 * @param  act1  ����
		 * @param  act2  ����
		 * @param  select true�͍��G�͈� false�̓n�b�L���O�͈͂̔���
		 * @return ����
		 */
		bool FanToPoint(const Actor::Actor& act1, const Actor::Actor& act2, bool select);


		
		/**
		 * 
		 * @brief  �L���b�`�G�l�~�[�p�̓����蔻��         
		 * @param  act1         ����
		 * @param  act2�@�@�@�@ ����
		 * @param  catchR       ���a
		 * @param  catchRange   �͈͊p�x
		 * @return true  ��������
		 *         false �������Ă��Ȃ�
		 */
		bool FanToPoint(const Actor::Actor& act1, const Actor::Actor& act2, double r, double range);


		

		/**
		 * @brief  ������AABB�̓����蔻����s��
		 * @param  act1
		 * @param  act2
		 * @return ����
		 */
		bool LineToAABB(const Actor::Actor& act1, const Actor::Actor& act2, const AABB box);

		/**
		 * @brief ������AABB�̓����蔻����s��
		 * @param startPos
		 * @param endPos
		 * @param target
		 * @return ����
		 */
		bool LineToAABB(Math::Vector2 startPos, Math::Vector2 endPos, const Actor::Actor& target);
		///**
		// * @brief  ������AABB�̓����蔻����s��
		// * @param  act
		// * @param  min
		// * @param  max
		// * @return ����
		// */
		//bool LineToAABB(const Actor::Actor& act1, const Math::Vector2 min, const Math::Vector2 max);

		/**
		 * @brief ���̃i�r���b�V���Ƃ̓����蔻��
		 * @param act
		 * @return true  �������Ă���
		 *         false �������Ă��Ȃ�
		 */
		//bool CollisionFloor(const Actor::Actor& act);

		/**
		 * @brief  ���ʂƂ̌����e�X�g
		 * @param  start
		 * @param  end
		 * @param  negd
		 * @param  out
		 * @return ����
		 */
		bool TestSidePlane(const double start, const double end, const double negd, std::vector<double>& out);

		/** 
		 * @brief  ������̍��W���v�Z  
		 * @param  start
		 * @param  end     
		 * @param  t
		 * @return ���W
		 */
		const Math::Vector4 PointOnSegment(const Math::Vector4 start, const Math::Vector4 end, const double t);

		/** 
		 * @brief  ������̍��W���v�Z  
		 * @param  start
		 * @param  end     
		 * @param  t
		 * @return ���W
		 */
		const Math::Vector2 PointOnSegment(const Math::Vector2 start, const Math::Vector2 end, const double t);

		/**
		 * @brief  �󂹂�ǂƓ������Ă��邩       
		 * @param  own
		 * @return ����
		 */
		bool CollisionBrokenWall(const Actor::Actor& own);

		///**
		// * @brief  �}�b�v�R���W���������擾       
		// * @return _frameMapCollision
		// */
		//const int GetMapCollision() const  { return _frameMapCollision; };

		/**
		 * @brief  �}�b�v�̃R���W�������z����擾
		 * @return _frameMapCollisions
		 */
		//const std::vector<int> GetMapCollision() const { return _frameMapCollisions; }

		/**
		 * @brief  �}�b�v�R���W���������擾       
		 * @return _frameMapCollision
		 */
		const int GetMapCollision(int handle) { return _frameMap[handle]; };

		/**
		 * @brief  �M�~�b�N�̃R���W���������擾       
		 * @param  handle
		 * @return _frameGimmickCollision
		 */
		const int GetGimmickCollision(int handle) { return _frameGimmick[handle]; };


		/**
		 * @brief  �}�b�v�̃i�r���b�V�����̍\�z
		 * @param  handle
		 * @param  key
		 */
		void SetMapCollision(int handle, std::string key);

		/**
		 * @brief  �}�b�v�̃i�r���b�V�����̑S�t���[���\�z
		 * @param  handle
		 */
		void SetMapCollision(int handle);

		/**
		 * @brief  �M�~�b�N�̃i�r���b�V�����̍\�z       
		 * @param  handle
		 * @param  key
		 */
		void SetGimmickCollision(int handle, std::string key);


		/**
		 * @brief  ���[�v�ʒu�����擾
		 * @param  handle �n���h��
		 * @return _frameMapCollision
		 */
		const std::pair<std::pair<int, int>, int> GetWarpCollision(std::string key, int handle);

		/**
		 * @brief  �}�b�v�̃��[�v�ʒu���̐ݒ�
		 * @param  handle
		 * @param  key
		 */
		void SetWarpCollision(int handle, std::string key);

		/**
		 * @brief  ���[�v�ʒu�̖��O�z����擾
		 * @param  handle �n���h��
		 * @return _warpName
		 */
		const std::vector<std::string> GetWarpName(int handle);

		/**
		 * @brief  ���[�v�ʒu�̖��O�z���ݒ�
		 * @param  handle �n���h��
		 * @param  keyV   �L�[�̔z��
		 */
		void SetWarpName(int handle, std::vector<std::string> keyV);

		/**
		 * @brief  ���[�v��̖��O���擾
		 * @param  floorNum �t���A�ԍ�
		 * @param  warpKey  ���[�v�O�̃t���[����
		 * @return ���[�v��̖��O
		 */
		const std::string GetWarpNameFloor(int floorNum, std::string warpKey);

		///**
		// * @brief  ���[�v�ʒu�̖��O�z���ݒ�      
		// * @param  num         �z�u����t���A�ԍ�
		// * @param  keys        ���[�v�ʒu�̖��O�z��
		// */
		void SetWarpNameFloor(int num, std::vector<std::string> keys);

		/**
		 * @brief  ��l���̐G��Ă���X�e�[�W�ԍ��z����擾
		 * @return _stageNums
		 */
		std::vector<int> GetCollStageNum() { return _stageNums; }

		/**
		 * @brief  ��l���̐G��Ă���X�e�[�W�ԍ��z���ݒ�
		 * @param  stageNums
		 */
		void SetCollStageNum(std::vector<int> stageNums) { _stageNums = stageNums; }

		/**
		 * @brief  ��l���̐G��Ă���t���A�ԍ��z����擾
		 * @return _floorNums
		 */
		std::vector<int> GetFloorNum() { return _floorNums; }

		/**
		 * @brief  �J�����ɑ��邽�߂̃t���A�ԍ��ɂ��X�e�[�W�̈ʒu���擾
		 * @param  floorNum
		 * @return �X�e�[�W���W
		 */
		Math::Vector4 GetFloorPos(int floorNum) { return _floorPoses[floorNum]; }

		/**
		 * @brief  �t���A�ԍ��ɂ��X�e�[�W�ʒu�̐ݒ�
		 * @param  floorPoses
		 */
		void SetFloorPos(std::unordered_map<int, Math::Vector4> floorPoses) { _floorPoses = floorPoses; }


		/**
		 * @brief  ��l���̐G��Ă���t���A�ԍ��z���ݒ�
		 * @param  floorNums
		 */
		void SetFloorNum(std::vector<int> floorNums) { _floorNums = floorNums; }

		/**
		 * @brief  �t���A�ԍ����L�[�Ƃ��ăX�e�[�W�ԍ����擾
		 * @param  floorNum �t���A�ԍ�
		 * @return �X�e�[�W�ԍ�
		 */
		int GetFloorStageNum(int floorNum) { return _floorStageNum[floorNum]; }

		/**
		 * @brief  �t���A�ԍ����L�[�Ƃ��āA�v�f���X�e�[�W�ԍ��Ƃ����A�z�z���ݒ�
		 * @param  floorStage �L�[ :�@�t���A�ԍ�,  �v�f : �X�e�[�W�ԍ�
		 */
		void SetFloorStageNum(std::unordered_map<int, int> floorStage) { _floorStageNum = floorStage; }

		std::unordered_map<int, Floor> GetAllFloorMap() { return _allFloorMap; }

		void SetAllFloorMap(std::unordered_map<int, Floor> allFloorMap) { _allFloorMap = allFloorMap; }
	private:
		Actor::Actor& _owner;
		/*std::unique_ptr<Report> _report;*/
		double _r1{ 0.0 }, _r2{ 0.0 }; //!< �~�̔��a

		Math::Vector4 _interSection;          //!< �����Ɖ�]�����l�p�`�Ƃ̌�_
		int _frameMapCollision;               //!< �}�b�v�̃R���W�������
		int _frameGimmickCollision;           //!< �M�~�b�N�̃R���W�������
		//std::vector<int> _frameMapCollisions; //!< �}�b�v�̃R���W�������̃x�N�^�[
		std::unordered_map<int, int> _frameMap; //!< �n���h�����L�[�Ƃ����R���W�������
		std::unordered_map<int, int> _frameGimmick; //!< �n���h�����L�[�Ƃ����M�~�b�N�̃R���W�������
		std::unordered_map<int, std::vector<std::string>> _warpNameMap;   //!< �n���h�����L�[�Ƃ������[�v�̖��O�z��
		WarpMap _warpMap;                                                 //!< �L�[�̓��[�v�R���W�����t���[������ �o�����[�́A���[�v��̈ʒu���ƃR���W�������
		WarpName _warpNameFloor; //!< �t���A�ԍ������L�[�Ƃ����A�z�z��́A���[�v�ʒu�̓�����2�������L�[�Ƃ��� ���[�v���̖��O���o�����[�Ƃ��Ă���
		std::vector<int> _stageNums; //!< ��l�����G��Ă���X�e�[�W�ԍ��z��
		std::unordered_map<int, int> _floorStageNum; //�t���A�ԍ����L�[�Ƃ��ăX�e�[�W�ԍ����擾����A�z�z��
		//std::unordered_map<int, int> _stageFloorNum; //�X�e�[�W�ԍ����L�[�Ƃ��ăt���A�ԍ����擾����A�z�z��
		std::vector<int> _floorNums;  // �t���A�ԍ��z��
		std::unordered_map<int, Floor> _allFloorMap; //�S�t���A�}�b�v�̘A�z�z��

		std::unordered_map<int, Math::Vector4> _floorPoses; //!< �t���A�ԍ����L�[�Ƃ����X�e�[�W�ʒu���W
	};
}

