#pragma once
#include "Minigin.h"

namespace dae
{
	class WorldGrid;

	class Game : public Minigin
	{
	public:
		Game();
		~Game() = default;
	protected:
		void Initialize() override;

		void SinglePlayer();
		void Coop();
		void Test();

	private:
		bool _isCoop = true;

		WorldGrid* m_world{nullptr};
	};
}