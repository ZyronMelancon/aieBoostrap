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
	Circ				m_pinball = { 50, 80, 30 };
	Circ				m_startPoint = { 50, 80, 6 };
	Line				m_lines[255];

protected:

	aie::Renderer2D*	m_2dRenderer;
	aie::Texture*		m_texture;
	aie::Texture*		m_shipTexture;
	aie::Font*			m_font;
	aie::Audio*			m_audio;

	float m_cameraX, m_cameraY;
	float m_timer;
};