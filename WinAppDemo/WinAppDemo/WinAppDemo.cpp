//입력을 받으면서 화면에 메세지에 필요한 출력을 처리하는 프로그램.
//큐를 활용하여 메세지를 큐에 쌓고, 쓰레드에서 큐에서 데이터를 1개씩꺼내서 처리하는 프로그램으로 만들기.
//1. 큐를 전역변수로 만들어서 처리하기.
//2. 큐를 main의 지역변수로 만들어서 동일한 과정이 가능하도록 처리하기.


//프로세스: 프로그램의 가장 기본적인 처리를 당담하는 흐름단위(메인루프), 큰흐름단위.
//스레드: 프로세스 내부에 처리를 하는 흐름단위(반복문을 동시에 처리가능), 큰흐름 하위의 작은 흐름.
//스레드는 프로그램 내부에서 처리하는 내용을 변경할수 있어야하므로, 
//그 프로그램 내의 함수를 호출하여 사용한다.
//콜백함수: 프로세스내에서 호출하지않고, 외부에서 호출하도록 하는 함수.

#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <Windows.h>
#include <process.h>
#include <queue>
#include <string>

using namespace std;

enum WM_MSG {CREATE, COMMOND, PAINT, DESTROY, MAX}; // 0, 1, 2, 3, 4
string strMSG[MAX] = { "CREATE","COMMOND","PAINT","DESTROY" };

bool g_bLoop = true;

// arg를 통해 외부의 데이터값을 받을 수 있다.
unsigned int WINAPI WndProc(void* arg)
{
	cout << "arg: " << arg << endl;
	
	queue <int>* n_que = (queue<int>*) arg;  // n_que 선언

	//int* pData = (int*)arg;
	while (g_bLoop) // 루프 반복문
	{
		if (n_que->empty() == false) // 비어있는 공간이 아닐때
		{
			int nData = n_que->front(); // 정수형 nData선언 n_que는 앞쪽으로 이동 차례대로 실행

			switch (nData) // 스위치
			{

			case CREATE: // 0
				cout << "초기화" << endl;
				nData = COMMOND;
				break;

			case COMMOND: // 1
				cout << "명령을 입력하세요." << endl;
				for (int i = 0; i < MAX; i++)
					cout << i << ":" << strMSG[i];
				cout << endl;
				break;

			case PAINT: // 2
				cout << "화면을 그립니다." << endl;
				break;

			case DESTROY: // 3
				cout << "프로그램을 종료합니다." << endl;
				g_bLoop = false;
				break;

			default:
				break;
			}
			n_que->pop(); // 순차적으로 삭제
			Sleep(2000); // 루프도는 과정 대기시간
		}
	}
	return 0;
}

int main(void)
{
	// 핸들러
	HANDLE hThread = NULL;
	DWORD dwThreadID = NULL;
	queue<int> queMsg; // 큐 정수형 queMsg 선언

	int nMSG = CREATE;
	cout << "Msg:" << &nMSG << endl;

	// 스레드
	hThread = (HANDLE)_beginthreadex(NULL, 0,
		WndProc,
		(void*)&queMsg, 0,
		(unsigned int*)dwThreadID);

	// 무한 반복 루프
	while (g_bLoop)
	{
		// 입력부분
		scanf("%d", &nMSG); 
		queMsg.push(nMSG);
	}

	return 0;
}