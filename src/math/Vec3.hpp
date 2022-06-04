#pragma once

class Vec3
{
public:
	float x, y, z;

	Vec3() : x(0.0f), y(0.0f), z(0.0f) {}

	Vec3(float x, float y, float z) : x(x), y(y), z(z) {}

	Vec3 operator+(Vec3 const& v) const
	{
		return Vec3(
			x + v.x,
			y + v.y,
			z + v.z);
	}

	Vec3 operator+=(Vec3 const& v)
	{
		x += v.x;
		y += v.y;
		z += v.z;
		return *this;
	}

	Vec3 operator-(Vec3 const& v) const
	{
		return Vec3(
			x - v.x,
			y - v.y,
			z - v.z);
	}

	Vec3 operator-=(Vec3 const& v)
	{
		x -= v.x;
		y -= v.y;
		z -= v.z;
		return *this;
	}

	Vec3 operator*(Vec3 const& v) const
	{
		return Vec3(
			x * v.x,
			y * v.y,
			z * v.z);
	}

	Vec3 operator*=(Vec3 const& v)
	{
		x *= v.x;
		y *= v.y;
		z *= v.z;
		return *this;
	}

	Vec3 operator*(float v) const
	{
		return Vec3(
			x * v,
			y * v,
			z * v);
	}

	Vec3 operator*=(float v)
	{
		x *= v;
		y *= v;
		z *= v;
		return *this;
	}
};