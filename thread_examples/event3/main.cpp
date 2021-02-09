// console_template.cpp : Defines the entry point for the console application.
//

#include <SDKDDKVer.h>
#include <Windows.h>
#include <process.h>
#include <stdio.h>
#include <tchar.h>
#include <locale.h>
#include <iostream>

using namespace std;

void thread0(void * pparams)
{
    string paramlocal = *(string *)pparams;
    std::cout << "thread0: " << paramlocal.c_str() << endl;
    _endthread();
}

typedef struct {
    std::string strParam;
    HANDLE handleParam;
} PARAM;

void thread1(void * pparams)
{
    PARAM temp = *(PARAM *)pparams;
    WaitForSingleObject(temp.handleParam, INFINITE);    // infinite
    std::cout << "Thread1: " << temp.strParam.c_str() << endl;
}


int _tmain(int argc, TCHAR* argv[], TCHAR* envp[])
{
    _tsetlocale(LC_ALL, _T(""));
    cout << " ����һ���߳� 0: \n";
    string param = " �������̴߳����߳� 0 ������ ";
    _beginthread(thread0, 0, &param);
    HANDLE hEvent = CreateEvent(NULL, false, false, NULL);
    string strparam = " �������̴߳����¼��߳� 1 ������ ";
    PARAM P = {strparam, hEvent};
    _beginthread(thread1, 0, &P);
    Sleep(2000);
    SetEvent(hEvent);
    Sleep(20);
    return 0;
}

