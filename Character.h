#pragma once
#ifndef _CHARACTER_H_INCLUDED_ //ヘッダが読み込まれてなかったら通る
#define _CHARACTER_H_INCLUDED_ //ヘッダを読み込んだら定義する⇒次にヘッダが読み込まれてもifndefに入らず無視できる

#include "Main.h"

class Character
{
private:
public:
	int handle;
	Pos pos;
	Character();
	void Draw(Pos p, int handle);
};

#endif