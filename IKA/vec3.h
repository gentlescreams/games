#ifndef _VEC3_H_
#define _VEC3_H_

class vec3
{
public:
	vec3();
	vec3(float _x, float _y, float _z);
	~vec3();
	float x, y, z;

	vec3 operator + (const vec3 &_v){
		vec3 v;  v.x = this->x + _v.x;
		v.y = this->y + _v.y;
		v.z = this->z + _v.z;
		return v;
	}
	vec3 operator * (float _f){ vec3 v; v.x = this->x * _f; v.y = this->y * _f; v.z = this->z * _f; return v; }
	vec3 operator - (const vec3 &_v){ vec3 m;  m.x = this->x - _v.x; m.y = this->y - _v.y; m.z = this->z - _v.z; return m; }
	vec3 operator / (float _f){ vec3 v;  v.x = this->x / _f; v.y = this->y / _f; v.z = this->z / _f; return v; }
	vec3 & operator +=(vec3 _v){ x += _v.x; y += _v.y; z += _v.z; return *this; }
	vec3 & operator -=(vec3 _v){ x -= _v.x; y -= _v.y; z -= _v.z; return *this; }
	vec3 & operator *=(float _f){ x *= _f; y *= _f; z *= _f; return *this; }
private:
};





#endif