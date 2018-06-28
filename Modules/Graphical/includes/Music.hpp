/*
** EPITECH PROJECT, 2018
** student
** File description:
** 15/06/18
*/
#pragma once

#include <SFML/Audio.hpp>
#include <map>

namespace Graphical {
	class Music {
	public:
		enum audioType {
			SOUND,
			MUSIC,
			AUDIO,
		};

		enum audioActionType {
			CREATE,
			PLAY,
			STOP,
			ON,
			OFF,
			SWAP,
			//PAUSE,
		};
		typedef struct MusicEvent {
			audioType audio;
			audioActionType action;
			std::string index;
			float volume;
			MusicEvent() = default;
			MusicEvent(const audioType &audio_, const audioActionType &action_, const std::string &index_, const float &volume_)
					: audio(audio_), action(action_), index (index_), volume(volume_) {};
			~MusicEvent() = default;

		} MusicEvent;
		Music() : _audio(true) {};
		~Music()
		{
			destroySounds();
			destroyMusics();
		};

		void soundManager(const audioActionType &action, const MusicEvent &event)
		{
			switch (action) {
				case CREATE: createSound(event.index); break;
				case PLAY: playSound(event.index, event.volume); break;
				case STOP: stopSound(event.index); break;
			//	case PAUSE: break;
				default: break;
			}
		}

		void musicManager(const audioActionType &action, const MusicEvent &event)
		{
			switch (action) {
				case CREATE: createMusic(event.index); break;
				case PLAY: playMusic(event.index, event.volume); break;
				case STOP: stopMusic(event.index); break;
			//	case PAUSE: break;
				default: break;
			}
		}

		void audioStatus(const audioActionType &action, const MusicEvent &event)
		{
			(void) event;
			switch (action) {
				case ON: _audio = true; break;
				case OFF: _audio = false; break;
				case SWAP: _audio = !_audio; break;
				default: break;
			}
			if (!_audio) {
				for (auto &music : _musics)
					if (music.second->getStatus() == sf::Music::Playing)
						music.second->pause();
				for (auto &sound : _sounds)
					if (sound.second->getStatus() == sf::Sound::Playing)
						sound.second->pause();
			} else {
				for (auto &music : _musics)
					if (music.second->getStatus() == sf::Music::Paused)
						music.second->play();
				for (auto &sound : _sounds)
					if (sound.second->getStatus() == sf::Sound::Paused)
						sound.second->play();
			}
		}

		void audioManager()
		{
			for (auto &event : _events) {
				switch (event.audio) {
					case SOUND: soundManager(event.action, event); break;
					case MUSIC:	musicManager(event.action, event); break;
					case AUDIO: audioStatus(event.action, event); break;
					default: break;
				}
			}
			_events.clear();
		}

		void addSoundBuffer(const std::string &index, const std::string &path)
		{
			std::unique_ptr<sf::SoundBuffer> buffer(std::make_unique<sf::SoundBuffer>());

			if (!buffer->loadFromFile(path))
				throw std::logic_error("Audio file: \'" + path + "\' not found");
			_buffers[index] = std::move(buffer);
		}

		void addSound(const std::string &index)
		{
			std::unique_ptr<sf::Sound> sound(std::make_unique<sf::Sound>());

			if (!_buffers[index])
				throw std::logic_error("Audio add sound: \'" + index + "\' not found");
			sound->setBuffer(*_buffers[index]);
			_sounds[index] = std::move(sound);
		}

		void createSound(const std::string &path)
		{
			const std::string index = path.substr(0, path.find('.'));

			addSoundBuffer(index, _path + _sound + path);
			addSound(index);
		}

		void createMusic(const std::string &path)
		{
			const std::string index = path.substr(0, path.find('.'));
			std::unique_ptr<sf::Music> music = std::make_unique<sf::Music>();

			if (!music->openFromFile(_path + _music + path))
				throw std::logic_error("Audio create music: \'" + path + "\' not found");
			if (!_musics[index])
				_musics[index] = std::move(music);
		}

		void playSound(const std::string &index, const float &volume)
		{
			if (!_sounds[index])
				throw std::logic_error("Audio play sound: \'" + index + "\' not found");
			_sounds[index]->setVolume(volume);
			_sounds[index]->play();
		}


		void playMusic(const std::string &index, const float &volume)
		{
			if (!_musics[index])
				throw std::logic_error("Audio play music: \'" + index + "\' not found");
			_musics[index]->setVolume(volume);
			_musics[index]->play();
			_musics[index]->setLoop(true);
		}

		void stopSound(const std::string &index)
		{
			if (!_sounds[index])
				throw std::logic_error("Audio stop sound: \'" + index + "\' not found");
			_sounds[index]->stop();
		}

		void stopMusic(const std::string &index)
		{
			if (!_musics[index])
				throw std::logic_error("Audio stop music: \'" + index + "\' not found");
			_musics[index]->stop();
		}

		void destroyMusics()
		{
			for (auto &music : _musics) {
				if (music.second->getStatus() == sf::Music::Status::Playing)
					music.second->stop();
			}
		}

		void destroySounds()
		{
			for (auto &sound : _sounds) {
				if (sound.second->getStatus() == sf::Sound::Status::Playing)
					sound.second->stop();
			}
		}

		void addEvent(const audioType &audio, const audioActionType &action, const std::string &index, const std::size_t &volume = 100)
		{
			MusicEvent event(audio, action, index, volume);

			_events.emplace_back(event);
		}
		const bool &isMute() const { return _audio; };
	private:
		const std::string _path = "assets/audio/";
		const std::string _sound = "sounds/";
		const std::string _music = "musics/";
		std::map<std::string, std::unique_ptr<sf::SoundBuffer>> _buffers;
		std::map<std::string, std::unique_ptr<sf::Sound>> _sounds;
		std::map<std::string, std::unique_ptr<sf::Music>> _musics;
		std::vector<MusicEvent> _events;
		bool _audio;
	};
}