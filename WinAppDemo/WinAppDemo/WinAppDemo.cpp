//�Է��� �����鼭 ȭ�鿡 �޼����� �ʿ��� ����� ó���ϴ� ���α׷�.
//ť�� Ȱ���Ͽ� �޼����� ť�� �װ�, �����忡�� ť���� �����͸� 1���������� ó���ϴ� ���α׷����� �����.
//1. ť�� ���������� ���� ó���ϱ�.
//2. ť�� main�� ���������� ���� ������ ������ �����ϵ��� ó���ϱ�.


//���μ���: ���α׷��� ���� �⺻���� ó���� ����ϴ� �帧����(���η���), ū�帧����.
//������: ���μ��� ���ο� ó���� �ϴ� �帧����(�ݺ����� ���ÿ� ó������), ū�帧 ������ ���� �帧.
//������� ���α׷� ���ο��� ó���ϴ� ������ �����Ҽ� �־���ϹǷ�, 
//�� ���α׷� ���� �Լ��� ȣ���Ͽ� ����Ѵ�.
//�ݹ��Լ�: ���μ��������� ȣ�������ʰ�, �ܺο��� ȣ���ϵ��� �ϴ� �Լ�.

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

// arg�� ���� �ܺ��� �����Ͱ��� ���� �� �ִ�.
unsigned int WINAPI WndProc(void* arg)
{
	cout << "arg: " << arg << endl;
	
	queue <int>* n_que = (queue<int>*) arg;  // n_que ����

	//int* pData = (int*)arg;
	while (g_bLoop) // ���� �ݺ���
	{
		if (n_que->empty() == false) // ����ִ� ������ �ƴҶ�
		{
			int nData = n_que->front(); // ������ nData���� n_que�� �������� �̵� ���ʴ�� ����

			switch (nData) // ����ġ
			{

			case CREATE: // 0
				cout << "�ʱ�ȭ" << endl;
				nData = COMMOND;
				break;

			case COMMOND: // 1
				cout << "����� �Է��ϼ���." << endl;
				for (int i = 0; i < MAX; i++)
					cout << i << ":" << strMSG[i];
				cout << endl;
				break;

			case PAINT: // 2
				cout << "ȭ���� �׸��ϴ�." << endl;
				break;

			case DESTROY: // 3
				cout << "���α׷��� �����մϴ�." << endl;
				g_bLoop = false;
				break;

			default:
				break;
			}
			n_que->pop(); // ���������� ����
			Sleep(2000); // �������� ���� ���ð�
		}
	}
	return 0;
}

int main(void)
{
	// �ڵ鷯
	HANDLE hThread = NULL;
	DWORD dwThreadID = NULL;
	queue<int> queMsg; // ť ������ queMsg ����

	int nMSG = CREATE;
	cout << "Msg:" << &nMSG << endl;

	// ������
	hThread = (HANDLE)_beginthreadex(NULL, 0,
		WndProc,
		(void*)&queMsg, 0,
		(unsigned int*)dwThreadID);

	// ���� �ݺ� ����
	while (g_bLoop)
	{
		// �Էºκ�
		scanf("%d", &nMSG); 
		queMsg.push(nMSG);
	}

	return 0;
}