#pragma once
#include <cmath>
#include <Xinput.h>
#pragma comment(lib,"Xinput.lib")

namespace dae
{
	// --------- WINDOW STRUCTS/CLASSES ---------
	// SDL window size information (connected to service locator)
	struct SDLWindowInfo
	{
		friend class ServiceLocator;

	public:
		float GetWindowWidth() const
		{
			return _x;
		}
		float GetWindowHeight() const
		{
			return _y;
		}

	private:
		float _x, _y;
	};

	enum Button
	{
		ButtonLevel1,
		ButtonLevel2,
		ButtonLevel3,
		ButtonVersus,
		ButtonBack
	};
	
	// --------- FLOAT STRUCTS/CLASSES ---------
	// F2
	struct Float2
	{
		// Variables
		float _x{}, _y{};

		// Constructors
		Float2()
			: _x(0), _y(0)
		{
		}

		Float2(float x, float y)
			:_x(x), _y(y)
		{
		}

		// Functions 
		float Length() const
		{
			return (sqrt(_x * _x + _y * _y));
		}

		void Normalize()
		{
			_x /= Length();
			_y /= Length();
		}
	};

	// F3
	struct Float3
	{
		float _x{}, _y{}, _z{};

		Float3(float x, float y, float z)
			:_x(x), _y(y), _z(z)
		{
		}

		Float3()
			:_x(0), _y(0), _z(0)
		{
		}

		Float3 Normalize() const
		{
			const float l = sqrt((_x * _x) + (_y * _y) + (_z * _z));
			return Float3{ _x / l, _y / l, _z / l };
		}

		Float3 operator+(const Float3& vector) const
		{
			return Float3{ _x + vector._x, _y + vector._y, _z + vector._z };
		}

		Float3 operator-(const Float3& vector) const
		{
			return Float3{ _x - vector._x, _y - vector._y, _z - vector._z };
		}
		Float3 operator*(const Float3& vector) const
		{
			return Float3{ _x * vector._x, _y * vector._y, _z * vector._z };
		}
		Float3 operator/(const Float3& vector) const
		{
			return Float3{ _x / vector._x, _y / vector._y, _z / vector._z };
		}

		Float3 operator-(float const& num) const
		{
			return Float3{ _x - num, _y - num, _z - num };
		}
		Float3 operator+(float const& num) const
		{
			return Float3{ _x + num, _y + num, _z + num};
		}
		Float3 operator*(float const& num) const
		{
			return Float3{ _x * num, _y * num, _z * num };
		}

		Float3 operator/(float const& num) const
		{
			return Float3{ _x / num, _y / num, _z / num };
		}

		
	};

	// F4
	struct Float4
	{
		float _x{}, _y{}, _z{}, _w{};

		Float4(float x, float y, float z, float w)
			: _x(x), _y(y), _z(z), _w(w)
		{
		}
		Float4()
			:_x(0), _y(0), _z(0), _w(0)
		{
		}
	};
}