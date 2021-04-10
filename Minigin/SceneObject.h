#pragma once
namespace dae
{
	class SceneObject
	{
	public:
		SceneObject() = default;
		virtual ~SceneObject() = default;

		SceneObject(const SceneObject & other) = delete;
		SceneObject(SceneObject && other) = delete;
		SceneObject& operator=(const SceneObject & other) = delete;
		SceneObject& operator=(SceneObject && other) = delete;
		
		virtual void Initialize() = 0;
		virtual void Update(float deltaTime) = 0;
		virtual void Render() const = 0;
	};
}
