#pragma once

#include "Application.h"
#include "Renderer2D.h"
#include "Audio.h"
#include "Physics2D.h"

class Application2D : public aie::Application {
public:

	Application2D();
	virtual ~Application2D();

	virtual bool startup();
	virtual void shutdown();

	virtual void update(float deltaTime);
	virtual void draw();

	PhysManager			m_physics;
	Circ				m_pinball = { 400, 300, 30 };
	Line				m_floor = { 100, 100, 800, 400 };
	Line				m_wall = { 100, 100, 100, 700 };

protected:

	aie::Renderer2D*	m_2dRenderer;
	aie::Texture*		m_texture;
	aie::Texture*		m_shipTexture;
	aie::Font*			m_font;
	aie::Audio*			m_audio;

	float m_cameraX, m_cameraY;
	float m_timer;
};