//#include <Windows.h>
//#include <Wininet.h>
//#pragma comment (lib, "Wininet.lib")
//
//#include <iostream>
//#include <sstream>
//#include <string>
//#include <map>
//
//#define MAX_BUF 8192
//#define MAX_PLAYER_LEN 16
//
//using namespace std;
//
//struct Match
//{
//	bool hasRequest;
//	string lastRequest;
//	bool hasResponse;
//	string currResponse;
//};
//
//map<string, Match> matches;
//
//namespace BotzoneAPI
//{
//	HINTERNET hInetRoot;
//	char buf[MAX_BUF];
//	int NO_TIMEOUT = ~0;
//
//	void Init()
//	{
//		hInetRoot = InternetOpen(NULL, INTERNET_OPEN_TYPE_PRECONFIG, NULL, NULL, 0);
//
//		if (!hInetRoot || !InternetSetOption(hInetRoot, INTERNET_OPTION_CONNECT_TIMEOUT, &NO_TIMEOUT, sizeof(NO_TIMEOUT)))
//		{
//			cerr << "Error starting internet session";
//			exit(-1);
//		}
//	}
//
//	void ProcessInput(istream &is)
//	{
//		int requestCount, resultCount, i;
//		string matchid, garbage;
//		is >> requestCount >> resultCount;
//		getline(is, garbage);
//		for (i = 0; i < requestCount; i++)
//		{
//			getline(is, matchid);
//			auto &match = matches[matchid];
//			getline(is, match.lastRequest);
//			match.hasRequest = true;
//			match.hasResponse = false;
//			cout << "New request for [" << matchid << "]:" << match.lastRequest << endl;
//		}
//		for (i = 0; i < resultCount; i++)
//		{
//			int slot, len, j, score;
//			is >> matchid >> slot >> len;
//			if (len == 0)
//				cout << "Match [" << matchid << "] aborted:" << endl <<
//				"I'm player " << slot << endl;
//			else
//			{
//				cout << "Match [" << matchid << "] finished:" << endl <<
//					"I'm player " << slot << ", and the scores are";
//				for (j = 0; j < len; j++)
//				{
//					is >> score;
//					cout << " " << score;
//				}
//				cout << endl;
//			}
//			matches.erase(matchid);
//			getline(is, garbage);
//		}
//	}
//
//	void FetchNewRequest()
//	{
//		cout << "Waiting for new request..." << endl;
//		string headers;
//		for (auto &pair : matches)
//			if (pair.second.hasResponse && pair.second.hasRequest && pair.second.currResponse.size() > 0)
//			{
//				pair.second.hasRequest = false;
//				headers += "X-Match-" + pair.first + ": " + pair.second.currResponse + "\r\n";
//			}
//		// 等待对局
//		while (true)
//		{
//			auto hReq = InternetOpenUrl(
//				hInetRoot, "https://www.botzone.org/api/5ac37ac5611cfd778a02ddf2/DEFAULT/localai",
//				headers.c_str(), headers.size(), 0, NULL);
//			if (!hReq)
//			{
//				// 此时可能是长时间没有新的 request 导致连接超时，再试即可
//				cout << "fff" << endl;
//				continue;
//			}
//			DWORD len;
//			if (!InternetReadFile(hReq, buf, MAX_BUF, &len) || len == 0)
//			{
//				cerr << "Error reading from Botzone, retrying 5 seconds later..." << endl;
//				Sleep(5000);
//				continue;
//			}
//			
//			buf[len] = '\0';
//			istringstream iss(buf);
//			ProcessInput(iss);
//			break;
//		}
//	}
//}
//
//int main()
//{
//	BotzoneAPI::Init();
//	while (true)
//	{
//		BotzoneAPI::FetchNewRequest();
//		cout << "fffooo" << endl;
//		for (auto &pair : matches)
//		{
//			if (pair.second.hasRequest && !pair.second.hasResponse)
//			{
//				cout << "Please enter the response for match [" << pair.first << "]:" << endl;
//				getline(cin, pair.second.currResponse);
//				pair.second.hasResponse = true;
//			}
//		}
//	}
//}