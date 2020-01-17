#ifndef __VECTOR_H__
#define __VECTOR_H__
#include <math.h>


class vec2
{
public:
	//Empty constructor
	vec2();
	//Creates vec2 with x and y
	vec2(float _x, float _y);

	//Defaults to zero
	float x, y = 0.f;
	//Used for indexing using [] operator
	float* hold[2] = { &x, &y };

	float GetMagnitude();

	void subtract(vec2);

	void multiplyscalar(float);
	void dividescalar(float);
	
	float dot(vec2 v2);
	vec2 normalise();
	float GetmagnitudeSq();

	vec2 Project(vec2 v2);
	
	//Operator overload for indexing using []
	float operator[](int i);
	vec2 operator-();
	vec2 operator+(vec2 v1);
	vec2 operator-(vec2 v1);

	vec2 operator*(float f);

	vec2 operator/(float);

};

class vec3
{
public:
	//Empty constructor
	vec3();
	//Creates vec3 with x, y, and z
	vec3(float _x, float _y, float _z);
	
	//Defaults to zero
	float x, y, z = 0.f;
	//Used for indexing using [] operator
	float* hold[3] = { &x, &y, &z };

	float GetMagnitude();

	//Operator overload for indexing using []
	float operator[](int i);
	//Negation operator for creating a negative version of the vector
	vec3 operator-();
	vec3 operator+(vec3 v2);
	vec3 operator-(vec3 v2);

	vec3 operator*(float f);
	vec3 operator/(float f);
};

class vec4
{
public:
	//empty constructor
	vec4();
	//Creates vec4 with x,y,z and w
	vec4(float _x, float _y, float _z, float _w);

	//Defaults to zero
	float x, y, z, w = 0.f;
	//Used for indexing using [] operator
	float* hold[4] = { &x, &y, &z, &w };

	float GetMagnitude();

	//Operator overload for indexing using []
	float operator[](int i);
};

class vec5 {
public:
	//Empty constructor
	vec5();
	//Creates vec2 with x and y
	vec5(float _x, float _y, float _z, float _w, float _v);

	//Defaults to zero
	float x, y,z,w,v = 0.f;
	//Used for indexing using [] operator
	float* hold[5] = { &x, &y ,&z,&w,&v};

	float GetMagnitude();

	float dot(vec5 v5);
	vec5 normalise();
	float GetmagnitudeSq();

	//Operator overload for indexing using []
	
	vec5 operator+(vec5 v2);
	vec5 operator-(vec5 v2);

	vec5 operator*(float f);

	vec5 operator/(float f);

};

#endif // !__VECTOR_H__
