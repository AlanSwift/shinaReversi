#include <Windows.h>
#include <Wininet.h>
#pragma comment (lib, "Wininet.lib")

#include <iostream>
#include <sstream>
#include <string>
#include <map>
#include <atlstr.h>
#define STRSAFE_NO_DEPRECATE
#include <strsafe.h>            // for String... functions
#include <crtdbg.h>                // for _ASSERTE
#include "lib\reversiEnv.h"
#include "lib\mcts.h"
#include "lib\alphaBetaPron.h"
#include "lib\hashlib.h"
#include "lib\Kizina.h"

#define MAX_BUF 8192
#define MAX_PLAYER_LEN 16

using namespace std;

struct Match
{
	bool hasRequest;
	string lastRequest;
	bool hasResponse;
	string currResponse;
};

map<string, Match> matches;





Player ai_color;

HashLib chessHash;
clock_t start;
Kizina kizina;

bool gameStart = false;
int x, y;
char buffer[512];

namespace BotzoneAPI
{
	HINTERNET hInetRoot;
	char buf[MAX_BUF];
	int NO_TIMEOUT = ~0;

	void Init()
	{
		hInetRoot = InternetOpen(NULL, INTERNET_OPEN_TYPE_PRECONFIG, NULL, NULL, 0);

		if (!hInetRoot || !InternetSetOption(hInetRoot, INTERNET_OPTION_CONNECT_TIMEOUT, &NO_TIMEOUT, sizeof(NO_TIMEOUT)))
		{
			cerr << "Error starting internet session";
			exit(-1);
		}
	}

	void ProcessInput(istream &is)
	{
		int requestCount, resultCount, i;
		string matchid, garbage;
		is >> requestCount >> resultCount;
		getline(is, garbage);
		for (i = 0; i < requestCount; i++)
		{
			getline(is, matchid);
			auto &match = matches[matchid];
			getline(is, match.lastRequest);
			match.hasRequest = true;
			match.hasResponse = false;
			cout << "New request for [" << matchid << "]:" << match.lastRequest << endl;
		}
		for (i = 0; i < resultCount; i++)
		{
			int slot, len, j, score;
			is >> matchid >> slot >> len;
			if (len == 0) {
				cout << "Match [" << matchid << "] aborted:" << endl <<
					"I'm player " << slot << endl;
				gameStart = false;
			}
			else
			{
				cout << "Match [" << matchid << "] finished:" << endl <<
					"I'm player " << slot << ", and the scores are";
				for (j = 0; j < len; j++)
				{
					is >> score;
					cout << " " << score;
				}
				cout << endl;
				gameStart = false;
			}
			matches.erase(matchid);
			getline(is, garbage);
		}
	}

	void FetchNewRequest()
	{
		cout << "Waiting for new request..." << endl;
		string headers;
		for (auto &pair : matches)
			if (pair.second.hasResponse && pair.second.hasRequest && pair.second.currResponse.size() > 0)
			{
				pair.second.hasRequest = false;
				headers += "X-Match-" + pair.first + ": " + pair.second.currResponse + "\r\n";
			}
		// µÈ´ý¶Ô¾Ö
		while (true)
		{
			char* url = "https://www.botzone.org/api/5ac37ac5611cfd778a02ddf2/DEFAULT/localai";
			WCHAR w_url[256], w_buffer[MAX_BUF];
			memset(w_url, 0, sizeof(w_url));
			MultiByteToWideChar(CP_ACP, 0, url, strlen(url) + 1, w_url,
				sizeof(w_url) / sizeof(w_url[0]));

			memset(w_buffer, 0, sizeof(w_buffer));
			MultiByteToWideChar(CP_ACP, 0, headers.c_str(), strlen(headers.c_str()) + 1, w_buffer,
				sizeof(w_buffer) / sizeof(w_buffer[0]));

			auto hReq = InternetOpenUrl(
				hInetRoot, w_url,
				w_buffer, headers.size(), 0, NULL);
			if (!hReq)
			{
				cout << "Fail to connect, retrying 1 seconds later..." << endl;
				Sleep(1000);
				continue;
			}
			DWORD len;
			if (!InternetReadFile(hReq, buf, MAX_BUF, &len) || len == 0)
			{
				cerr << "Error reading from Botzone, retrying 5 seconds later..." << endl;
				Sleep(5000);
				continue;
			}
			buf[len] = '\0';
			istringstream iss(buf);
			ProcessInput(iss);
			break;
		}
	}
}

int main()
{
	kizina.render();

	BotzoneAPI::Init();
	while (true)
	{
		BotzoneAPI::FetchNewRequest();

		for (auto &pair : matches)
		{
			if (pair.second.hasRequest && !pair.second.hasResponse)
			{
				//cout << "Please enter the response for match [" << pair.first << "]:" << endl;
				sscanf(pair.second.lastRequest.c_str(), "{\"x\":%d,\"y\":%d}", &x, &y);
				cout << "&&&&&& " << y << " "<< x << endl;
				if (!gameStart) {
					//env.reset();
					if (y == -1)
						ai_color = Player::black;
					else
						ai_color = Player::white;
					gameStart = true;
				}
				kizina.step(x, y);
					
				int action;
				if (ai_color == black && kizina.getPlayer() == black) {
					cout << "^^^^^^^^^^" << endl;
					
					action = kizina.search();
					if (action == -1)
					{
						sprintf(buffer, "{\"x\":%d,\"y\":%d}", -1, -1);
						kizina.step(-1, -1);
					}
					else {
						sprintf(buffer, "{\"x\":%d,\"y\":%d}", action / 8, action % 8);
						kizina.step(action / 8, action % 8);
					}
					
					
					kizina.render();
				}
				else if (ai_color == white && kizina.getPlayer() == white) {
					cout << "$$$$$$$$$" << endl;
					
					action = kizina.search();
					if (action == -1)
					{
						sprintf(buffer, "{\"x\":%d,\"y\":%d}", -1, -1);
						kizina.step(-1, -1);
					}
					else {
						sprintf(buffer, "{\"x\":%d,\"y\":%d}", action / 8, action % 8);
						kizina.step(action / 8, action % 8);
					}


					kizina.render();
				}
				else
					sprintf(buffer, "{\"x\":%d,\"y\":%d}", -1, -1);
				//env.render();
				pair.second.currResponse = string(buffer);
				cout << "The response for match [" << pair.first << "]: " << pair.second.currResponse << endl;
				//getline(cin, pair.second.currResponse);
				pair.second.hasResponse = true;
			}
		}
	}
}