///
/// @file    AssetServer.h
///   �A�Z�b�g�T�[�o�[
/// @date    2021/11/26
/// @author yamawaki kota
/// @copyright (C) Amusement Media Academy All rights Resved.
///
#pragma once
#include <filesystem>
#include <unordered_map>
#include <string>
#include <memory>

namespace AppFrame {
	class Game;
}

namespace AppFrame {

	namespace Asset {
		// �摜�t�@�C���p
		struct Texture {
			std::string filename;
			int xNum;
			int yNum;
			int xSize;
			int ySize;
		};

		// ���\�[�X�Ǘ��T�[�o
		class AssetServer {
		public:
			/// �C�ӂ̕�������L�[�Ƃ���DivGraph���Ǘ�
			using TextureMap = std::unordered_map<std::string, Texture>;

			/// �C�ӂ̕�������L�[�ɂ��ĉ��t�@�C�����Ǝ��O�ǂݍ��݂̗L�����Ǘ�
			using SoundMap = std::unordered_map<std::string, std::pair<std::string, bool>>;

			/// �C�ӂ̕�������L�[�ɂ��ă��f���t�@�C�������Ǘ�
			using ModelMap = std::unordered_map<std::string, std::string>;

			/// �R���X�g���N�^
			/// @param game Game�N���X�ւ̎Q��
			AssetServer(Game& game);
			/// �f�X�g���N�^ 
			virtual ~AssetServer() = default;

			/// ������
			virtual void	Init();

			/// �N���A
			/// �摜�A���f���A���̑S�Ă��N���A����
			virtual void	Clear();

			/// �摜�̓ǂݍ���
			/// @param key �L�[�ƂȂ�C�ӂ̕�����
			/// @param divGraph 
			virtual void LoadTexture(std::string_view key, const Texture& texture);

			/// �摜�̈ꊇ�ǂݍ���
			/// @param[in] textureMap �摜�̃e�[�u��
			virtual void LoadTextures(const TextureMap& textureMap);

			/// �ǂݍ��ݎ��̃J�����g�t�H���_�̕ύX
		  /// �J�����g�t�H���_�����̃t�@�C����ǂݍ���
		  /// @param[in] path �J�����g�t�H���_
			virtual void ChangeCurrentPath(std::string_view path);


			/// �摜�n���h���̎擾
			/// @param[in] key �o�^�ς݂̃L�[
			/// @param[in] no  �������̔ԍ�
			/// @return �摜�̃n���h��
			virtual int GetTexture(std::string_view key, int no = 0);

			/// �摜�n���h���̕������̎擾
			/// @param[in] key �o�^�ς݂̃L�[
			/// @return ��������
			virtual int GetTextureCount(std::string_view& key);

			/// �摜���̎擾
			/// @param[in] key �o�^�ς݂̃L�[
			/// @return	Texture �摜���
			virtual Texture GetTextureInfo(std::string_view& key);

			/// �摜�̍폜
			/// @param[in] key �o�^�ς݂̃L�[
			virtual void	ClearTextures();

			/// ���f���̓ǂݍ���
			/// @param key �L�[�ƂȂ�C�ӂ̕�����
			/// @param[in] filename mv1�t�@�C����
			/// @return ���f���̃n���h��
			virtual int LoadModel(std::string_view key, const std::string_view filename);

			/// ���f���̈ꊇ�ǂݍ���
			/// @param modelMap ���f���̃e�[�u��
			virtual void LoadModels(const ModelMap& modelMap);

			/// ���f���̃n���h���̎擾
			/// ���ǂ̏ꍇ�͕�������
			/// @param key �o�^�ς݂̃L�[
			/// @param no ���ꃂ�f���̒ʂ��ԍ�
			/// @return ���f���̃n���h���Ǝ��{�̓o�^�ԍ�
			virtual std::pair<int, int> GetModel(std::string_view key, int no = 0);

			/// �S�Ẵ��f�����폜���ăN���A����
			virtual void ClearModels();
			/// Duplicate�������f�������폜���ăN���A����
			virtual void DeleteDuplicateModels();

			/// ���t�@�C���̓ǂݍ���
		  /// @param[in] key �L�[�ƂȂ�C�ӂ̕�����
		  /// @param[in] filename_isLoad �t�@�C�����Ǝ��O�ǂݍ��ݗL���̃y�A 
			virtual void LoadSound(std::string_view key, std::pair<std::string, bool> filename_isLoad);


			/// ���t�@�C���̈ꊇ�ǂݍ���
			/// @param[in] soundMap ���t�@�C���̃e�[�u��
			virtual void LoadSounds(const SoundMap& soundMap);

			/// ���t�@�C�����̎擾
			/// @param[in] key �o�^�ς݂̃L�[
			/// @return ���t�@�C����, �n���h��
			virtual std::pair<std::string, int> GetSoundInfo(std::string_view key);

		private:
			Game& _game;

			/// �i�[�t�H���_�ւ̑��΃p�X
			std::filesystem::path _currentPath;

			/// �C�ӂ̕�������L�[�ɂ���DivGraph�Ɖ摜�n���h���̃y�A���Ǘ�
			std::unordered_map<std::string, std::pair<Texture, std::vector<int>>> _textures;
			/// �C�ӂ̕�������L�[�ɂ��ĉ��t�@�C�����ƃn���h���̃y�A���Ǘ�
			std::unordered_map<std::string, std::pair<std::string, int>> _sounds;
			/// �C�ӂ̕�������L�[�ɂ��ă��f���t�@�C�����ƃn���h���̃y�A���Ǘ�
			std::unordered_map<std::string, std::pair<std::string, std::vector<int>>> _models;
		};
	}

}






