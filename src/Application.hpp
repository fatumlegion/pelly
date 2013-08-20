#ifndef APPLICATION_HPP
#define APPLICATION_HPP
#include <SFML/Graphics.hpp>
#include "GameWorld.hpp"
#include <memory>
#include <stack>
class Application
{
private:
	static std::unique_ptr<Application> m_App;
	
	bool parseArguments(int argc, char **argv);
	
	sf::VideoMode videoMode;
	sf::RenderWindow rwin;
	bool fullscreen;
	
	float doForceFPS;
	int forceFPS;
	
	float dt, timeNow, timeFrame, timeActual, accumulator;
	sf::Clock gameClock;
	
	std::stack<GameWorld*> world;
public:
	static std::unique_ptr<Application> getSingleton();
	
	sf::VideoMode &getVideoMode() { return this->videoMode; }
	
	void pushWorld(GameWorld *world);
	
	void initialize();
	int run(int argc, char **argv);
};
#endif