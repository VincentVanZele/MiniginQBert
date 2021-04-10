#pragma once
#include "Singleton.h"

namespace dae
{
	class Texture2D;
	class Font;
	class ResourceManager final : public Singleton<ResourceManager>
	{
		
	public:
		ResourceManager() = default;
		~ResourceManager() = default;

		ResourceManager(const ResourceManager& other) = delete;
		ResourceManager(ResourceManager&& other) noexcept = delete;
		ResourceManager& operator=(const ResourceManager& other) = delete;
		ResourceManager& operator=(ResourceManager&& other) noexcept = delete;

		void Initialize(std::string&& data);

		std::shared_ptr<Texture2D> LoadTexture(const std::string& file) const;
		std::shared_ptr<Font> LoadFont(const std::string& file, unsigned int size) const;

	private:
		std::string m_dataPath{};
	};

}
