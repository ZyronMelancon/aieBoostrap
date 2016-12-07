#include "Application2D.h"
#include "Texture.h"
#include "Font.h"
#include "Input.h"


struct ShipControl
{
	int x = 500;
	int y = 500;
	float r = 0;
};

ShipControl ship;

Application2D::Application2D() {

}

Application2D::~Application2D() {

}

bool Application2D::startup() {
	
	m_2dRenderer = new aie::Renderer2D();
	m_shipTexture = new aie::Texture("./textures/ship.png");
	m_audio = new aie::Audio("./audio/powerup.wav");

	m_cameraX = 0;
	m_cameraY = 0;
	m_timer = 0;

	return true;
}

void Application2D::shutdown() {
	
	delete m_audio;
	delete m_shipTexture;
	delete m_2dRenderer;
}

void Application2D::update(float deltaTime) {

	m_timer += deltaTime;

	// input example
	aie::Input* input = aie::Input::getInstance();

	// use arrow keys to move camera
	if (input->isKeyDown(aie::INPUT_KEY_UP) && !input->isKeyDown(aie::INPUT_KEY_DOWN))
	{
		ship.y += cos(ship.r) * 500.0f * deltaTime;
		ship.x -= sin(ship.r) * 500.0f * deltaTime;
	}

	else if (input->isKeyDown(aie::INPUT_KEY_DOWN) && !input->isKeyDown(aie::INPUT_KEY_UP))
	{
		ship.y -= cos(ship.r) * 500.0f * deltaTime;
		ship.x += sin(ship.r) * 500.0f * deltaTime;
	}

	else if (input->isKeyDown(aie::INPUT_KEY_UP) && input->isKeyDown(aie::INPUT_KEY_DOWN))
	{
		
	}

	if (input->isKeyDown(aie::INPUT_KEY_LEFT))
		ship.r += 0.12f;

	if (input->isKeyDown(aie::INPUT_KEY_RIGHT))
		ship.r -= 0.12f;

	// exit the application
	if (input->isKeyDown(aie::INPUT_KEY_ESCAPE))
		quit();
}

void Application2D::draw() {

	// wipe the screen to the background colour
	clearScreen();

	// set the camera position before we begin rendering
	m_2dRenderer->setCameraPos(m_cameraX, m_cameraY);

	// begin drawing sprites
	m_2dRenderer->begin();

	// demonstrate spinning sprite
	m_2dRenderer->setUVRect(0,0,1,1);
	m_2dRenderer->drawSprite(m_shipTexture, ship.x, ship.y, 80, 80, ship.r, 2);

	// done drawing sprites
	m_2dRenderer->end();
}