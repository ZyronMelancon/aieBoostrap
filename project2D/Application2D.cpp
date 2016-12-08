#include "Application2D.h"
#include "Texture.h"
#include "Font.h"
#include "Input.h"
#include "Physics2D.h"

Application2D::Application2D() {

}

Application2D::~Application2D() {

}

bool Application2D::startup() {
	
	m_2dRenderer = new aie::Renderer2D();
	m_audio = new aie::Audio("./audio/powerup.wav");

	m_cameraX = 0;
	m_cameraY = 0;
	m_timer = 0;

	m_pinball.velocity.m_y = -2;
	m_pinball.velocity.m_x = 0;

	return true;
}

void Application2D::shutdown() {
	
	delete m_audio;
	delete m_2dRenderer;
}
bool cando = false;
void Application2D::update(float deltaTime) {

	m_timer += deltaTime;

	
	if (cando) {
		//m_physics.updateGravity(m_pinball);
		m_pinball.updatePos();
		m_physics.updateCollision(m_floor, m_pinball);
		m_physics.updateCollision(m_wall, m_pinball);
		//line is x,y ; x,y
		float w = getWindowWidth();
		float h = getWindowHeight();
	}

	aie::Input* input = aie::Input::getInstance();
	if (input->wasKeyPressed(aie::INPUT_KEY_SPACE))
		cando = !cando;
	// use arrow keys to move camera
	//if (input->isKeyDown(aie::INPUT_KEY_UP) && !input->isKeyDown(aie::INPUT_KEY_DOWN))
	//{

	//}

	//else if (input->isKeyDown(aie::INPUT_KEY_DOWN) && !input->isKeyDown(aie::INPUT_KEY_UP))
	//{
	//	ship.y -= cos(ship.r) * 500.0f * deltaTime;
	//	ship.x += sin(ship.r) * 500.0f * deltaTime;
	//}

	//else if (input->isKeyDown(aie::INPUT_KEY_UP) && input->isKeyDown(aie::INPUT_KEY_DOWN))
	//{
	//	
	//}

	//if (input->isKeyDown(aie::INPUT_KEY_LEFT))
	//	ship.r += 0.12f;

	//if (input->isKeyDown(aie::INPUT_KEY_RIGHT))
	//	ship.r -= 0.12f;



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

	m_2dRenderer->drawCircle(m_pinball.x, m_pinball.y, m_pinball.r, 0);
	m_2dRenderer->drawLine(m_floor.x, m_floor.y, m_floor.xo, m_floor.yo, 3, 0);
	m_2dRenderer->drawLine(m_wall.x, m_wall.y, m_wall.xo, m_wall.yo, 3, 0);

	m_2dRenderer->end();
}