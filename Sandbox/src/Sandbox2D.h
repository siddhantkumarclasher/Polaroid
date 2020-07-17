#pragma once

#include "Polaroid.h"

class Sandbox2D : public Polaroid::Layer
{
public:
	Sandbox2D();
	virtual ~Sandbox2D() = default;

	virtual void OnAttach() override;
	virtual void OnDetach() override;

	Polaroid::Ref <Polaroid::Texture2D> m_CheckerboardTexture;

	void OnUpdate(Polaroid::Timestep ts) override;
	virtual void OnImGuiRender() override;
	void OnEvent(Polaroid::Event& e) override;
private:
	Polaroid::OrthographicCameraController m_CameraController;

	// Temp
	Polaroid::Ref<Polaroid::VertexArray> m_SquareVA;
	Polaroid::Ref<Polaroid::Shader> m_FlatColorShader;

	glm::vec4 m_SquareColor = { 0.2f, 0.3f, 0.8f, 1.0f };
};