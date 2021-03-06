#include <application.hpp>
#include <utils.hpp>
#include <states/titlestate.hpp>
#include "../pause_state.hpp"
#include "../game_state.hpp"
#include "../win_state.hpp"

const sf::Time Application::TimePerFrame = sf::seconds(1.f/60.f);

Application::Application(unsigned int width, unsigned int height, const std::string &title) :
    mWindow(sf::VideoMode(width,height), title.c_str(), sf::Style::Close),
    mTextures(),
    mFonts(),
    mSounds(),
    mMusic(),
    mScripts(),
    mPlayer(),
    mStateStack(State::Context(mWindow, mTextures, mFonts, mSounds, mMusic, mScripts, mPlayer)),
    mStatisticsText(),
    mStatisticsUpdateTime(),
    mStatisticsNumFrames(0)
{
    mWindow.setKeyRepeatEnabled(false);

    // Resources
    mFonts.load(Fonts::Main, "assets/fonts/main.ttf");
    mFonts.load(Fonts::Title, "assets/fonts/alagard.ttf");

    mTextures.load(Textures::Particle, "assets/textures/particle.png");
    mTextures.load(Textures::ParticleStar, "assets/textures/particle-star.png");
    mTextures.load(Textures::Tiles, "assets/textures/tilemap.png");
    mTextures.load(Textures::TilesFull, "assets/textures/tiles-full.png");
    mTextures.load(Textures::Player, "assets/textures/player.png");
    mTextures.load(Textures::Ui, "assets/textures/ui.png");
    mTextures.load(Textures::MenuBackground, "assets/textures/background.png");
    mTextures.load(Textures::TitleBackground, "assets/textures/homescreen.png");
    mTextures.load(Textures::WaterCan, "assets/textures/can.png");
    mTextures.load(Textures::Star, "assets/textures/star.png");

    mTextures.get(Textures::Tiles).setSmooth(false);
    mTextures.get(Textures::TilesFull).setSmooth(false);
    mTextures.get(Textures::Player).setSmooth(false);
    mTextures.get(Textures::MenuBackground).setSmooth(false);
    mTextures.get(Textures::WaterCan).setSmooth(false);
    mTextures.get(Textures::Star).setSmooth(false);

//    mScripts.registerFile(Scripts::HelloWorld, "assets/scripts/helloworld.lua");
//    mScripts.play(Scripts::HelloWorld);

    mStatisticsText.setFont(mFonts.get(Fonts::Main));
    mStatisticsText.setPosition(5.f,5.f);
    mStatisticsText.setCharacterSize(10);

    registerStates();
    mStateStack.pushState(States::Game);
    mStateStack.pushState(States::Title);
}



void Application::run()
{
    sf::Clock clock;
    sf::Time timeSinceLastUpdate = sf::Time::Zero;
    while(mWindow.isOpen())
    {
        sf::Time elapsedTime = clock.restart();
        timeSinceLastUpdate += elapsedTime;
        while(timeSinceLastUpdate > TimePerFrame)
        {
            timeSinceLastUpdate -= TimePerFrame;

            processEvents();
            update(TimePerFrame);

            // Check inside this loop, because stack might be empty before update() call
            if (mStateStack.isEmpty())
                mWindow.close();
        }

        updateStatistics(elapsedTime);
        render();
    }
}

void Application::processEvents()
{
    sf::Event event;
    while(mWindow.pollEvent(event))
    {
        mStateStack.handleEvent(event);
        if(event.type == sf::Event::Closed)
            mWindow.close();
    }
}

void Application::update(sf::Time dt)
{
    mStateStack.update(dt);
}

void Application::render()
{
    mWindow.clear();
    mStateStack.draw();

    mWindow.setView(mWindow.getDefaultView());
//    mWindow.draw(mStatisticsText);
    mWindow.display();
}

void Application::registerStates()
{
    mStateStack.registerState<TitleState>(States::Title);
    mStateStack.registerState<GameState>(States::Game);
    mStateStack.registerState<PauseState>(States::Pause);
    mStateStack.registerState<WinState>(States::Win);
}

void Application::updateStatistics(sf::Time elapsedTime)
{
    return;
    mStatisticsUpdateTime += elapsedTime;
    mStatisticsNumFrames += 1;

    if(mStatisticsUpdateTime >= sf::seconds(1.f))
    {
        mStatisticsText.setString(
                    "Frames/sec = " + toString(mStatisticsNumFrames) + "\n" +
                    "Time/update = " + toString(mStatisticsUpdateTime.asMicroseconds() / mStatisticsNumFrames) + "us"
        );

        mStatisticsNumFrames = 0;
        mStatisticsUpdateTime -= sf::seconds(1.f);
    }
}
