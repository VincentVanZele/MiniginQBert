#pragma once
#include "Minigin.h"

namespace dae
{
	class Game : public Minigin
	{
	public:
		Game();
		~Game() = default;
	protected:
		void Initialize() override;

		void SinglePlayer();
		void Coop();

	private:
		bool _isCoop = true;
	};
}