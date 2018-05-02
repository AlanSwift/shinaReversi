#pragma once
#ifndef SHINA_CONFIG_H
#define SHINA_CONFIG_H
#include <iostream>
#include <vector>
#include <utility>
#include <cmath>
#include <ctime>
#include <cstdlib>
#include <cstdio>
#include <algorithm>
#include <queue>
#include <cstring>

#ifdef _MSC_VER
#include <intrin.h>
#endif

#include <cassert>
#define NDEBUG
//#define FIXED_DEPTH
#define TIMELIMIT 3
#define STEPLIMIT 30

using namespace std;
using Board = unsigned long long;
using LL = unsigned long long;
using PLL = pair<LL, LL>;
using PID = pair<int, double>;
using PII = pair<int, int>;
extern const int RankofPos[10][10];
//extern const LL PIECE_HASH_VALUE[64][2];
extern clock_t start;

void debug(LL x);


typedef unsigned long long u64;

const int BOARD_WIDTH = 8;
const int BOARD_SIZE = 64;

const int DIR_N = -8;
const int DIR_S = +8;
const int DIR_W = -1;
const int DIR_E = +1;
const int DIR_NW = DIR_N + DIR_W;
const int DIR_NE = DIR_N + DIR_E;
const int DIR_SW = DIR_S + DIR_W;
const int DIR_SE = DIR_S + DIR_E;

const int MAX_MOVES = 32;

// Evaluation
typedef int Value;

const Value INF = 1e8;
const Value BND = 1e8 + 100;
const Value UNKNOWN_VALUE = 2e8;
const Value VALUE[BOARD_SIZE] = {
	20, -3, 11,  8,  8, 11, -3, 20,
	-3, -7, -4,  1,  1, -4, -7, -3,
	11, -4,  2,  2,  2,  2, -4, 11,
	8,  1,  2, -3, -3,  2,  1,  8,
	8,  1,  2, -3, -3,  2,  1,  8,
	11, -4,  2,  2,  2,  2, -4, 11,
	-3, -7, -4,  1,  1, -4, -7, -3,
	20, -3, 11,  8,  8, 11, -3, 20,
};

// Hash
typedef long long HashValue;

enum HashType {
	EXACT,
	ALPHA,                      // lower bound
	BETA                        // upper bound
};

const HashValue PIECE_HASH_VALUE[BOARD_SIZE][2] = {
	{ 4594751534691652102,1851944401440995956 },{ 2747968243137263198,2207742792711565793 },{ 3848004645121087451,3216815717814836416 },{ 1516548209265803966,2020642571208227878 },{ 2337722696409584694,3437059740345402271 },{ 2898258925230917030,1303855352451580365 },{ 6741448498992359,4377852815973168715 },{ 4372139272928371625,3315674304057407093 },
	{ 2878955577234187687,3310911488601986908 },{ 3582136329572115185,3886893032669033165 },{ 708434475528378106,1888811197289616306 },{ 1100757220377106200,2346419301461881836 },{ 1995470285667003037,3344903240187633289 },{ 379138142664434743,2911313461119289748 },{ 769900647706363980,4570344310535739107 },{ 3830265281089289793,3708897551051154464 },
	{ 3315091279816950970,273872670825111973 },{ 2041102417123238912,3112772639692668910 },{ 4299351587052741497,492310524505137784 },{ 4010522851494399473,362833556870927538 },{ 3744809366975419281,4226902705789150687 },{ 592324386571251539,1676350313352030418 },{ 297655183198752013,4509827100803281127 },{ 1403475634077929604,1892578936484963221 },
	{ 1715531292376832429,1613769283609259830 },{ 504753725576921797,2392422484281687273 },{ 1111776814178973127,1894484583724300455 },{ 1353368917078917269,980842078909767887 },{ 3122588916900066851,1904920763832515654 },{ 604593662070056141,4610439775266802671 },{ 3503933470494872029,465452319321546006 },{ 4524482860969100773,418483288981978408 },
	{ 2147108479613262724,402603979465422751 },{ 1068073449811579883,773275828138712383 },{ 313392534030852928,2844281495097492616 },{ 4421182344573758470,2690463909089054058 },{ 3564969729531244233,2153253714589235195 },{ 2048902308496474304,2035312525942884256 },{ 247110080496067937,460126216295236977 },{ 2910862077868453624,1236872844561888511 },
	{ 4434503285626937640,1788235057956326105 },{ 617585277383179775,3098146742097029318 },{ 544179776494490277,3070740981001682629 },{ 1133217526157530591,2597739258228835604 },{ 2291314423671849210,3285761339244847317 },{ 3210152689877290283,4256064628862687295 },{ 983114329860268105,669680476452377688 },{ 3546030145041577463,3617169695558622675 },
	{ 3355229619035115716,4340260948930533822 },{ 4157463891367309266,4259738129252256818 },{ 3868311963489900326,292106685109972994 },{ 3029152897729491494,443633747780305188 },{ 4438782935932979823,476344706333946286 },{ 225228141352298397,437312018862372058 },{ 3013545812034048651,1882826361476336167 },{ 1682028769400164518,490632862661383976 },
	{ 3045929461469737835,705051332461977505 },{ 3071896532965914314,4398387264278704174 },{ 2968653874300097863,2681664983844070838 },{ 2243007804517107923,2718365947100986101 },{ 3315433970204178064,2094902054428670605 },{ 3639206564310825114,495668310978194141 },{ 3266804706767133950,137318566489138708 },{ 847159218020085283,3988956296565724071 },
};

const int HASH_TABLE_SIZE = 1 << 23;
const int HASH_TABLE_MASK = HASH_TABLE_SIZE - 1;

// instead of std::pair<int, Value>
struct SVPair {
	int first;
	Value second;
	SVPair() { }
	SVPair(int x, Value y) : first(x), second(y) { }
};

const int MAX_DEPTH = 64;
const int MOVESORT_MIN_DEPTH = 3;
const int DEBUG_MAX_DEPTH = 12;

enum Player {
	black, white, draw
};

inline bool isTimeUp()
{
	return clock() - start > 0.98*TIMELIMIT * CLOCKS_PER_SEC;
}



#endif // !SHINA_CONFIG_H
