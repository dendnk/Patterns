// Task:
// You are tasked with designing a subsystem for a Home Theater system that involves various components such as
// an Amplifier, Tuner, DVD Player, Projector, Screen, and Lights.
// The goal is to provide a simplified interface to control these components using a Facade.
// The Facade should allow users to easily start and stop a movie.

// Requirements :
// - Implement the components of the Home Theater system (Amplifier, Tuner, DVD Player, Projector, Screen, Lights).
// - Create a HomeTheaterFacade class that provides a simplified interface to control these components.
// - Implement methods to start and stop a movie using the HomeTheaterFacade.

#pragma once

#include <iostream>
#include <memory>
#include <string>

namespace Facade
{

class Amplifier
{
public:
    void SetEnabled(bool IsEnabled)
    {
        auto State = IsEnabled ? "on" : "off";
        std::cout << "Amplifier " << State << std::endl;
    }

    void SetVolume(int level)
    {
        std::cout << "Setting volume to " << level << std::endl;
    }
};

class Tuner
{
public:
    void SetEnabled(bool IsEnabled)
    {
        auto State = IsEnabled ? "on" : "off";
        std::cout << "Tuner " << State << std::endl;
    }
};


class DvdPlayer
{
public:
    void SetEnabled(bool IsEnabled)
    {
        auto State = IsEnabled ? "on" : "off";
        std::cout << "DvdPlayer " << State << std::endl;
    }

    void Play(const std::string& Movie)
    {
        std::cout << "Playing \"" << Movie << "\"\n";
    }

    void Stop()
    {
        std::cout << "DVD Player stopped\n";
    }
};

class Projector
{
public:
    void SetEnabled(bool IsEnabled)
    {
        auto State = IsEnabled ? "on" : "off";
        std::cout << "Projector " << State << std::endl;
    }
};


class Screen
{
public:
    void SetEnabled(bool IsEnabled)
    {
        auto State = IsEnabled ? "Down" : "Up";
        std::cout << "Screen " << State << std::endl;
    }
};

class Lights
{
public:
    void Dim(int level)
    {
        std::cout << "Dimming lights to " << level << "%\n";
    }
};

class HomeTheaterFacade
{
public:
    HomeTheaterFacade(std::shared_ptr<Amplifier> InAmplifier,
                        std::shared_ptr<Tuner> InTuner,
                        std::shared_ptr<DvdPlayer> InDVD,
                        std::shared_ptr<Projector> InProjector,
                        std::shared_ptr<Screen> InScreen,
                        std::shared_ptr<Lights> InLights)
        : AmplifierHT(InAmplifier)
        , TunerHT(InTuner)
        , DvdPlayerHT(InDVD)
        , ProjectorHT(InProjector)
        , ScreenHT(InScreen)
        , LightsHT(InLights)
    {}

    void WatchMovie(const std::string& Movie)
    {
        std::cout << "Get ready to watch a movie...\n";
        LightsHT->Dim(10);
        ScreenHT->SetEnabled(true);
        ProjectorHT->SetEnabled(true);
        AmplifierHT->SetEnabled(true);
        AmplifierHT->SetVolume(5);
        DvdPlayerHT->SetEnabled(true);
        DvdPlayerHT->Play(Movie);
    }

    void EndMovie()
    {
        std::cout << "Shutting movie theater down...\n";
        LightsHT->Dim(100);
        ScreenHT->SetEnabled(false);
        ProjectorHT->SetEnabled(false);
        AmplifierHT->SetEnabled(false);
        DvdPlayerHT->Stop();
        DvdPlayerHT->SetEnabled(false);
    }

private:
    std::shared_ptr<Amplifier> AmplifierHT;
    std::shared_ptr<Tuner> TunerHT;
    std::shared_ptr<DvdPlayer> DvdPlayerHT;
    std::shared_ptr<Projector> ProjectorHT;
    std::shared_ptr<Screen> ScreenHT;
    std::shared_ptr<Lights> LightsHT;
};



void TestFacadePattern()
{
    auto amplifier = std::make_shared<Amplifier>();
    auto tuner = std::make_shared<Tuner>();
    auto dvdPlayer = std::make_shared<DvdPlayer>();
    auto projector = std::make_shared<Projector>();
    auto screen = std::make_shared<Screen>();
    auto lights = std::make_shared<Lights>();

    HomeTheaterFacade homeTheater(amplifier, tuner, dvdPlayer, projector, screen, lights);

    homeTheater.WatchMovie("Interstellar");
    std::cout << "\n";
    homeTheater.EndMovie();
}

} // namespace Facade