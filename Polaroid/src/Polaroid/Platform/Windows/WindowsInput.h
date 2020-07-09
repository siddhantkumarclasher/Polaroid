#pragma once

#include "Polaroid/Input.h"

namespace Polaroid {

	class WindowsInput : public Input
	{
	protected:
		virtual bool IsKeyPressedImpl(int kycdode) override;

		virtual bool IsMouseButtonPressedImpl(int button) override;
		virtual std::pair<float, float> GetMousePositionImpl() override;
		virtual float GetMouseXImpl() override;
		virtual float GetMouseYImpl() override;
	};

}