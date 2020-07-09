#pragma once

#include "Polaroid/Layer.h"

#include "Polaroid/Events/ApplicationEvent.h"
#include "Polaroid/Events/KeyEvent.h"
#include "Polaroid/Events/MouseEvent.h"

namespace Polaroid {

	class POLAROID_API ImGuiLayer : public Layer
	{
	public:
		ImGuiLayer();
		~ImGuiLayer();

		virtual void OnAttach() override;
		virtual void OnDetach() override;
		virtual void OnImGuiRender() override;

		void Begin();
		void End();
	private:
		float m_Time = 0.0f;
	};
}