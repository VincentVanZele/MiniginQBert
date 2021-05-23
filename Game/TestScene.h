#pragma once
#include "Scene.h"

namespace dae
{

	class TestScene final : public dae::Scene
	{
	public:
		TestScene();

		void Initialize() override;
		void Update() override;

	private:
	};

}