
#include "lib\reversiEnv.h"


reversiEnv::reversiEnv()
{
	board[0] = (1ull << toSquare(3, 4)) | (1ull << toSquare(4, 3));
	board[1] = (1ull << toSquare(3, 3)) | (1ull << toSquare(4, 4));
	player = 0;
	nullMoveCount = 0;
	basicEval = 0;
	hashValue = PIECE_HASH_VALUE[toSquare(3, 3)][1]
		^ PIECE_HASH_VALUE[toSquare(3, 4)][0]
		^ PIECE_HASH_VALUE[toSquare(4, 3)][0]
		^ PIECE_HASH_VALUE[toSquare(4, 4)][1];
}

int reversiEnv::generateMoves(int moves[]) const
{
	u64 movesBB = findCorrectMoves(board[player], board[player ^ 1]);
	int tot = 0;
	while (movesBB) {
		moves[tot++] = getlsbid(movesBB);
		movesBB ^= getlsb(movesBB);
	}
	assert(tot <= MAX_MOVES);
	return tot;
}

LL reversiEnv::generateMovesLL()
{
	return findCorrectMoves(board[player], board[player ^ 1]);
}

void reversiEnv::applyMove(int sq)
{
	place(sq);
	LL flip=calcFlip(sq, board[player], board[player ^ 1]);
	board[player] ^= flip;

	board[player ^ 1] ^= flip;
	while (flip)
	{
		int bitpos = getlsbid(flip);
		basicEval += RankofPos[bitpos / 8][bitpos % 8]*2;
		hashValue ^= PIECE_HASH_VALUE[bitpos][player];
		hashValue ^= PIECE_HASH_VALUE[bitpos][player ^ 1];
		flip ^= (1ull << bitpos);
	}

	//getFlipped(sq, player, board[player], board[player ^ 1], basicEval, hashValue);
	nullMoveCount = 0;
	changePlayer();
}

void reversiEnv::applyNullMove()
{
	assert(nullMoveCount <= 1);

	++nullMoveCount;
	changePlayer();
}

Value reversiEnv::getEval() const
{
	int my_tiles = 0, opp_tiles = 0, my_front_tiles = 0, opp_front_tiles = 0;
	double p = 0, c = 0, l = 0, m = 0, f = 0, d = 0;

	d = basicEval;

	// Piece difference, frontier disks and disk squares
	//debug(board[player]);
	u64 frontier = getFrontier(board[player], board[player ^ 1]);
	my_tiles = countMyPieces();
	opp_tiles = countOppPieces();
	my_front_tiles = popcount(frontier & board[player]);
	opp_front_tiles = popcount(frontier & board[player ^ 1]);
	if (my_tiles > opp_tiles)
		p = (100.0 * my_tiles) / (my_tiles + opp_tiles);
	else if (my_tiles < opp_tiles)
		p = -(100.0 * opp_tiles) / (my_tiles + opp_tiles);
	if (my_front_tiles > opp_front_tiles)
		f = -(100.0 * my_front_tiles) / (my_front_tiles + opp_front_tiles);
	else if (my_front_tiles < opp_front_tiles)
		f = (100.0 * opp_front_tiles) / (my_front_tiles + opp_front_tiles);

	// Corner occupancy
	my_tiles = opp_tiles = 0;
	my_tiles += isMyPiece(toSquare(0, 0));
	opp_tiles += isOppPiece(toSquare(0, 0));
	my_tiles += isMyPiece(toSquare(0, 7));
	opp_tiles += isOppPiece(toSquare(0, 7));
	my_tiles += isMyPiece(toSquare(7, 0));
	opp_tiles += isOppPiece(toSquare(7, 0));
	my_tiles += isMyPiece(toSquare(7, 7));
	opp_tiles += isOppPiece(toSquare(7, 7));
	c = 25 * (my_tiles - opp_tiles);

	// Corner closeness
	my_tiles = opp_tiles = 0;
	if (isEmpty(toSquare(0, 0))) {
		my_tiles += isMyPiece(toSquare(0, 1));
		opp_tiles += isOppPiece(toSquare(0, 1));
		my_tiles += isMyPiece(toSquare(1, 0));
		opp_tiles += isOppPiece(toSquare(1, 0));
		my_tiles += isMyPiece(toSquare(1, 1));
		opp_tiles += isOppPiece(toSquare(1, 1));
	}
	if (isEmpty(toSquare(0, 7))) {
		my_tiles += isMyPiece(toSquare(0, 6));
		opp_tiles += isOppPiece(toSquare(0, 6));
		my_tiles += isMyPiece(toSquare(1, 6));
		opp_tiles += isOppPiece(toSquare(1, 6));
		my_tiles += isMyPiece(toSquare(1, 7));
		opp_tiles += isOppPiece(toSquare(1, 7));
	}
	if (isEmpty(toSquare(7, 0))) {
		my_tiles += isMyPiece(toSquare(6, 0));
		opp_tiles += isOppPiece(toSquare(6, 0));
		my_tiles += isMyPiece(toSquare(6, 1));
		opp_tiles += isOppPiece(toSquare(6, 1));
		my_tiles += isMyPiece(toSquare(7, 1));
		opp_tiles += isOppPiece(toSquare(7, 1));
	}
	if (isEmpty(toSquare(7, 7))) {
		my_tiles += isMyPiece(toSquare(6, 6));
		opp_tiles += isOppPiece(toSquare(6, 6));
		my_tiles += isMyPiece(toSquare(6, 7));
		opp_tiles += isOppPiece(toSquare(6, 7));
		my_tiles += isMyPiece(toSquare(7, 6));
		opp_tiles += isOppPiece(toSquare(7, 6));
	}
	l = -12.5 * (my_tiles - opp_tiles);

	// Mobility
	my_tiles = popcount(findCorrectMoves(board[player], board[player ^ 1]));
	opp_tiles = popcount(findCorrectMoves(board[player ^ 1], board[player]));
	if (my_tiles > opp_tiles)
		m = (100.0 * my_tiles) / (my_tiles + opp_tiles);
	else if (my_tiles < opp_tiles)
		m = -(100.0 * opp_tiles) / (my_tiles + opp_tiles);

	// final weighted score
	double score = ((10 * p) + (801.724 * c) + (382.026 * l) + (78.922 * m) + (74.396 * f) + (10 * d)) * 100;

	return (Value)score;
}

void reversiEnv::print() const
{
	printf("Round #%d\n", countAllPieces() - 4 + 1);
	printf("Black: %d   White: %d\n", countBlackPieces(), countWhitePieces());
	if (isBlackPlayer())
		printf("Now BLACK\n");
	else
		printf("Now WHITE\n");
	printf("Hash Value: %lld\n", getHashValue());
	printf("Evaluation: %d\n", getEval());

	printf("  ");
	for (int i = 0; i < BOARD_WIDTH; ++i) {
		printf("%c ", 'a' + i);
	}
	printf("\n");
	for (int i = 0; i < BOARD_WIDTH; ++i) {
		printf("%d ", i + 1);
		for (int j = 0; j < BOARD_WIDTH; ++j) {
			int sq = toSquare(i, j);
			if (isEmpty(sq))
				printf(". ");
			else if (isBlackPiece(sq))
				printf("b ");
			else {
				assert(isWhitePiece(sq));
				printf("w ");
			}
		}
		printf("\n");
	}
}

bool reversiEnv::isValidMove(int x, int y)
{
	if (x < 0 || x>7 || y < 0 || y>7)
	{
		return false;
	}
	LL validMoves = generateMovesLL();
	int move = x * 8 + y;
	if (validMoves&(1ull << move))
	{
		return true;
	}
	else {
		return false;
	}
}
