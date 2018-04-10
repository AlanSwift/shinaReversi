#pragma once
#ifndef SHINA_CONFIG_H
#define SHINA_CONFIG_H
#include <iostream>
#include <vector>
#include <utility>
#include <cmath>
#include <ctime>
#include <cstdlib>
#include <queue>
using namespace std;
using Board = unsigned long long;
using LL = unsigned long long;
using Position = short;
using PLL = pair<LL, LL>;

void debug(LL x);

enum Player{
	black,white,draw
};

#endif // !SHINA_CONFIG_H
