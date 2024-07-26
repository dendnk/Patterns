// Problem:
// You are tasked with integrating a new AudioPlayer class into an existing media player system
// that only understands MediaPlayer interface.The AudioPlayer uses a different method to play audio files,
// and you need to adapt it to the MediaPlayer interface.

// Requirements :
// - Create a MediaPlayer interface with a method to play audio files.
// - Implement an existing VideoPlayer class that uses the MediaPlayer interface.
// - Create an AudioPlayer class with a different method to play audio files.
// - Implement an AudioPlayerAdapter class that adapts the AudioPlayer to the MediaPlayer interface.
// - Demonstrate the usage of the AudioPlayerAdapter to play audio files using the MediaPlayer interface.

#pragma once

#include <iostream>
#include <memory>
#include <string>

namespace Adapter
{

class MediaPlayer
{
public:
	virtual ~MediaPlayer() = default;
	virtual void Play(const std::string& MediaFile) = 0;
};

class VideoPlayer : public MediaPlayer
{
public:
	void Play(const std::string& MediaFile) override
	{
		std::cout << "Playing Video File : " << MediaFile << std::endl;
	}
};

class AudioPlayer
{
public:
	void PlayAudioFile(const std::string& AudioFile)
	{
		std::cout << "Playing Audio File : " << AudioFile << std::endl;
	}
};

class AudioPlayerAdapter : public MediaPlayer
{
public:
	AudioPlayerAdapter(std::shared_ptr<AudioPlayer> InAudioPlayer)
		: UsedAudioPlayer(InAudioPlayer)
	{}

	void Play(const std::string& MediaFile) override
	{
		if (UsedAudioPlayer != nullptr)
		{
			UsedAudioPlayer->PlayAudioFile(MediaFile);
		}
	}

protected:
	std::shared_ptr<AudioPlayer> UsedAudioPlayer;
};

void TestAdapterPattern()
{
	// Existing system using VideoPlayer
	std::shared_ptr<MediaPlayer> videoPlayer = std::make_shared<VideoPlayer>();
	videoPlayer->Play("video.mp4");

	// New system using AudioPlayer through AudioPlayerAdapter
	std::shared_ptr<AudioPlayer> audioPlayer = std::make_shared<AudioPlayer>();
	std::shared_ptr<MediaPlayer> audioPlayerAdapter = std::make_shared<AudioPlayerAdapter>(audioPlayer);
	audioPlayerAdapter->Play("audio.mp3");
}

} // namespace Adapter