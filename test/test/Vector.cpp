#include "Vector.h"

vec2::vec2()
{
}

vec2::vec2(float _x, float _y)
{
	x = _x;
	y = _y;
}

float vec2::GetMagnitude()
{
	return float(sqrt((x*x)+(y*y)));
}

void vec2::subtract(vec2 v1)
{
	this->x -= v1.x;
	this->y -= v1.y;
}

void vec2::multiplyscalar(float s)
{
	this->x *= s;
	this->y *= s;
}

void vec2::dividescalar(float s)
{
	this->x /= s;
	this->y /= s;
}

float vec2::dot(vec2 v2)
{
	return float(x*v2.x + y*v2.y);
}

vec2 vec2::normalise()
{
	vec2 norm = *this / GetMagnitude();

	return norm;
	
}

float vec2::GetmagnitudeSq()
{
	float mag = GetMagnitude();

	return (mag*mag);
}

vec2 vec2::Project(vec2 v2)
{
	vec2 a = *this;

	float num = a.dot(v2);

	float den = v2.GetmagnitudeSq();

	return (v2*(num/den));
}

float vec2::operator[](int i)
{
	return *hold[i];
}

vec2 vec2::operator-()
{
	return vec2(-x,-y);
}

vec2 vec2::operator+(vec2 v1)
{
	return vec2(this->x+v1.x, this->y + v1.y);
}

vec2 vec2::operator-(vec2 v1)
{
	return vec2(this->x - v1.x, this->y - v1.y);
}

vec2 vec2::operator*(float f)
{
	return vec2(this->x*f, this->y * f);
}

vec2 vec2::operator/(float s)
{
	return vec2(this->x / s, this->y / s);
}

vec3::vec3()
{
}

vec3::vec3(float _x, float _y, float _z)
{
	x = _x;
	y = _y;
	z = _z;	
}

float vec3::GetMagnitude()
{
	return float(sqrt((x * x) + (y * y)+ (z * z)));
}

float vec3::operator[](int i)
{
	return *hold[i];
}

vec3 vec3::operator-()
{
	return vec3(-x, -y,-z);
}

vec3 vec3::operator+(vec3 v2)
{
	return vec3(this->x + v2.x, this->y + v2.y, this->z + v2.z);
}

vec3 vec3::operator-(vec3 v2)
{
	return vec3(this->x - v2.x, this->y - v2.y, this->z - v2.z);
}

vec3 vec3::operator*(float f)
{
	return vec3(this->x * f, this->y * f, this->z * f);
}

vec3 vec3::operator/(float f)
{
	return vec3(this->x / f, this->y / f, this->z / f);
}

vec4::vec4()
{

}

vec4::vec4(float _x, float _y, float _z, float _w)
{
	x = _x;
	y = _y;
	z = _z;
	w = _w;
}

float vec4::GetMagnitude()
{
	return float(sqrt((x * x) + (y * y) + (z * z)+(w * w)));
}

float vec4::operator[](int i)
{
	return *hold[i];
}

vec5::vec5()
{
}

vec5::vec5(float _x, float _y,float _z,float _w,float _v)
{
	x = _x;
	y = _y;
	z = _z;
	w = _w;
	v = _v;
}

float vec5::GetMagnitude()
{
	return float(sqrt((x * x) + (y * y) + (z * z) + (w * w)+(v * v)));
}

float vec5::dot(vec5 v5)
{
 	return float(x * v5.x + y * v5.y+ z * v5.z + w * v5.w + v * v5.v);
}

vec5 vec5::normalise()
{
	vec5 norm = *this / GetMagnitude();

	return norm;
}

float vec5::GetmagnitudeSq()
{
	float mag = GetMagnitude();

	return (mag * mag);
}

vec5 vec5::operator+(vec5 v1)
{
	return vec5();
}

vec5 vec5::operator-(vec5 v2)
{
	return vec5(this->x - v2.x, this->y - v2.y, this->z - v2.z, this->w - v2.w, this->v - v2.v);
}

vec5 vec5::operator*(float f)
{
	return vec5(this->x * f, this->y * f, this->z * f, this->w * f, this->v * f);
}

vec5 vec5::operator/(float f)
{
	return vec5(this->x / f, this->y / f, this->z / f, this->w / f, this->v / f);
}
