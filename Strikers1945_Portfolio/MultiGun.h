#pragma once

#include "Gun.h"
class MultiGun
	: public Gun
{
public:
	MultiGun();
	~MultiGun();
public:
	bool Init(float x, float y);
	void Render(HDC hdc);
	void Release();
public:
	void BulletFire(float x, float y);
	void BulletMove();
};