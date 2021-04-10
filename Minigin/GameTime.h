#pragma once
#include "Singleton.h"

namespace dae
{
	class GameTime final : public Singleton<GameTime>
	{
	public:
		GameTime() = default;
		~GameTime() = default;

		GameTime(const GameTime& other) = delete;
		GameTime(GameTime&& other) noexcept = delete;
		GameTime& operator=(const GameTime& other) = delete;
		GameTime& operator=(GameTime&& other) noexcept = delete;

		void Update(float deltaTime);

		float GetDeltaTime() const;
		float GetFPS() const;
		int GetMsPerFrame() const;

	protected:
	private:
		float m_DeltaTime{ 0 }, m_ElapsedTime{ 0 };
		const int msPerFrame = 16; //16 for 60 fps, 33 for 30 fps
	};
}