#pragma once
#include "Scene.h"

namespace dae
{


	class Versus final : public dae::Scene
	{
	public:
		Versus();

		void Initialize() override;
		void Update() override;

	private:

	};

}