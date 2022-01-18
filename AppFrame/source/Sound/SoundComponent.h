/*****************************************************************//**
 * @file  SoundComponent.h
 * @brief 音入力コンポーネント
 *
 * @author Kota Yamawaki
 * @date   November 26 2021
*********************************************************************/
#pragma once

#include <string>

class Game;

namespace AppFrame::Sound{

	class SoundComponent {
	public:
		SoundComponent(Game& game) : _game{ game } {};
		virtual ~SoundComponent();

		void Play(std::string_view key);
		void PlayLoop(std::string_view key);

		void SetVolume(std::string_view key, int volume);
		void SetMute(bool isMute) { _isMute = isMute; }
	protected:
		void Play(std::string_view key, int playType);

	private:
		Game& _game;
		bool _isMute{ false };
	};
}



