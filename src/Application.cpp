#include "Application.hpp"
#include "LevelWorld.hpp"
#include <stdio.h>
#include <string.h>

std::unique_ptr<Application> Application::m_App = nullptr;

std::unique_ptr<Application> Application::getSingleton()
{
	if (m_App == nullptr)
		m_App = std::unique_ptr<Application>(new Application());
	return std::move(m_App);
}

void Application::initialize()
{
	videoMode.width = 1280;
	videoMode.height = 720;
	videoMode.bitsPerPixel = 32;
	
	fullscreen = false;
	
	dt = 1.0f / 60.0f;
	timeNow = gameClock.getElapsedTime().asSeconds();
	timeFrame = 0.0f;
	timeActual = 0.0f;
	accumulator = 0.0f;
	
	doForceFPS = false;
	forceFPS = 60;
	
	pushWorld(new LevelWorld());
}

void Application::pushWorld(GameWorld *world)
{
	this->world.push(world);
}

bool Application::parseArguments(int argc, char **argv)
{
	for (int i = 0; i < argc; i++)
	{
		if ((strcmp(argv[i], "-v") == 0) || (strcmp(argv[i], "--version")) == 0)
		{
			//there's truth behind this and not just for kicks
			//this is the 4th re-write of the game
			printf("Version: 4.20 blaze it faget\n");
			return false;
		}
		
		if (strcmp(argv[i], "--force-fps") == 0)
		{
			doForceFPS = true;
			forceFPS = atoi(argv[i + 1]);
		}
	}
	return true;
}

int Application::run(int argc, char **argv)
{
	if (!parseArguments(argc, argv)) return 0;
	
	rwin.create(videoMode, "Pelly Version 4.20 - Blaze it Edition", !sf::Style::Resize | sf::Style::Close);
	
	if (doForceFPS) rwin.setFramerateLimit(forceFPS);
	
	while (rwin.isOpen())
	{
		sf::Event event;
		while (rwin.pollEvent(event))
		{
			world.top()->input(event);
			switch (event.type)
			{
				case sf::Event::Closed:
					rwin.close();
				break;
			}
		}
		
		timeNow = gameClock.getElapsedTime().asSeconds();
		timeFrame = timeNow - timeActual;
		
		if (timeFrame > 0.25f)
			timeFrame = 0.25f;
		
		timeActual = timeNow;
		accumulator += timeFrame;
		
		while (accumulator >= dt)
		{
			world.top()->update(dt);
			accumulator -= dt;
		}
		
		const float interpolation = accumulator / dt;
		
		rwin.clear();
		world.top()->draw(rwin, interpolation);
		rwin.display();
	}
	return 0;
}
