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

	m_pinball.velocity.m_y = 0;
	m_pinball.velocity.m_x = 0.3;

	m_font = new aie::Font("./font/consolas.ttf", 100);

	setBackgroundColour(0.2f, 0.2f, 0.2f);

	m_lines[0] = { 0, 10, 500, 10 };
	m_lines[0].active = true;

	return true;
}

void Application2D::shutdown() {
	
	delete m_audio;
	delete m_2dRenderer;
}
bool cando = false;
float w;
float h;
int linenum = 1;

void Application2D::update(float deltaTime) {
	w = getWindowWidth();
	h = getWindowHeight();

	m_timer += deltaTime;

	m_cameraX = m_pinball.x - w/2;
	m_cameraY = m_pinball.y - h/2;

	if (cando) {
		m_physics.updateGravity(m_pinball);
		m_pinball.updatePos();
		for (int i = 0; i < linenum; i++)
			if (m_lines[i].active)
				m_physics.updateCollision(m_lines[i], m_pinball);
	}

	aie::Input* input = aie::Input::getInstance();
	if (input->wasKeyPressed(aie::INPUT_KEY_S))
	{
		m_pinball.x = m_startPoint.x;
		m_pinball.y = m_startPoint.y;
		m_pinball.velocity = Vector2D(0, 0.3);
	}

	if (input->wasKeyPressed(aie::INPUT_KEY_A))
	{
		m_startPoint.x = m_pinball.x;
		m_startPoint.y = m_pinball.y;
	}

	if (!cando)
	{
		if (input->isMouseButtonDown(aie::INPUT_MOUSE_BUTTON_LEFT))
		{
			m_lines[linenum].active = true;
			m_lines[linenum].x = input->getMouseX() + m_cameraX;
			m_lines[linenum].y = input->getMouseY() + m_cameraY;
		}

		m_lines[linenum].xo = input->getMouseX() + m_cameraX;
		m_lines[linenum].yo = input->getMouseY() + m_cameraY;

		if (input->wasMouseButtonPressed(aie::INPUT_MOUSE_BUTTON_RIGHT) && m_lines[linenum].active)
		{
			m_lines[linenum].xo = input->getMouseX() + m_cameraX;
			m_lines[linenum].yo = input->getMouseY() + m_cameraY;
			linenum++;
		}
	}

	// use arrow keys to apply force to ball

	if (input->isKeyDown(aie::INPUT_KEY_UP) && !input->isKeyDown(aie::INPUT_KEY_DOWN))
		m_physics.applyForce(m_pinball, Vector2D(0, 1));

	else if (input->isKeyDown(aie::INPUT_KEY_DOWN) && !input->isKeyDown(aie::INPUT_KEY_UP))
		m_physics.applyForce(m_pinball, Vector2D(0, -1));

	else if (input->isKeyDown(aie::INPUT_KEY_UP) && input->isKeyDown(aie::INPUT_KEY_DOWN))
	{
	}

	if (input->isKeyDown(aie::INPUT_KEY_LEFT))
		m_physics.applyForce(m_pinball, Vector2D(-1, 0));


	if (input->isKeyDown(aie::INPUT_KEY_RIGHT))
		m_physics.applyForce(m_pinball, Vector2D(1, 0));

	if (input->wasKeyPressed(aie::INPUT_KEY_SPACE))
		cando = !cando;

	if (input->wasKeyPressed(aie::INPUT_KEY_Z) && linenum > 0)
	{
		m_lines[linenum-1].active = false;
		linenum--;
	}

	if (input->wasKeyPressed(aie::INPUT_KEY_X) && linenum < 20)
	{
		m_lines[linenum + 1].active = true;
		linenum++;
	}

	// exit the application
	if (input->isKeyDown(aie::INPUT_KEY_ESCAPE))
		quit();
}

void Application2D::draw() {

	// wipe the screen to the background colour
	clearScreen();

	// set the camera position before we begin rendering
	m_2dRenderer->setCameraPos(m_cameraX, m_cameraY);
	m_2dRenderer->setRenderColour(0.5f, 0.5f, 0, 1.0f);
	// begin drawing sprites
	m_2dRenderer->begin();
	m_2dRenderer->drawCircle(m_pinball.x, m_pinball.y, m_pinball.r, 0);

	for (int i = 0; i < linenum + 1; i++)
		if (m_lines[i].active)
		{
			m_2dRenderer->setRenderColour(0.1f, 0.1f, 0.1f);
			m_2dRenderer->drawLine(m_lines[i].x, m_lines[i].y, m_lines[i].xo, m_lines[i].yo, 5, 0);
			m_2dRenderer->setRenderColour(1, 1, 1);
		}

	if (!cando)
		m_2dRenderer->drawText(m_font, "Draw", m_cameraX + 50, m_cameraY + 50, 1);
	else
		m_2dRenderer->drawText(m_font, "Play", m_cameraX + 50, m_cameraY + 50, 1);

	m_2dRenderer->setRenderColour(0.8f, 0, 0);
	m_2dRenderer->drawCircle(m_startPoint.x, m_startPoint.y, m_startPoint.r, 0);

	m_2dRenderer->end();
}