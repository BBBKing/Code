// test_filesystem.cpp : �������̨Ӧ�ó������ڵ㡣
//

#include "stdafx.h"
#include "test_filesystem.h"

#include <iostream>
#include <fstream>


#ifdef _DEBUG
    #define new DEBUG_NEW
#endif

int test_mfc_c_stduio_file();
int test_mfc_c_stduio_file_append();
int test_ostream_file();
int test_ostream_file_overide_begin();
int test_ostream_file_append();
int test_wfopen_file();
int test_wfopen_file_append();

int test_wfopen_s_file();
int test_wfopen_s_file_buffer();


// Ψһ��Ӧ�ó������

CWinApp theApp;

using namespace std;

int _tmain(int argc, TCHAR* argv[], TCHAR* envp[])
{
    int nRetCode = 0;

    // ��ʼ�� MFC ����ʧ��ʱ��ʾ����
    if (!AfxWinInit(::GetModuleHandle(NULL), NULL, ::GetCommandLine(), 0)) {
        // TODO: ���Ĵ�������Է���������Ҫ
        _tprintf(_T("����: MFC ��ʼ��ʧ��\n"));
        nRetCode = 1;
    } else {
        test_mfc_c_stduio_file();
        test_mfc_c_stduio_file_append();
        test_ostream_file();
        test_ostream_file_overide_begin();
        test_ostream_file_append();
        test_wfopen_file();
        test_wfopen_file_append();
        test_wfopen_s_file();
        test_wfopen_s_file_buffer();

        system("pause");
    }    

    return nRetCode;
}




int test_mfc_c_stduio_file()
{
    // �½�д
    CStdioFile file;
    CString filename = L"mfc_file.txt";
    CString info = L"hello world3!";

    if (file.Open((LPCTSTR)filename, CFile::modeCreate | CFile::modeWrite)) {
        file.SeekToEnd();
        file.WriteString(info);
        file.Close();
    }

    return 0;
}

int test_mfc_c_stduio_file_overide_begin()
{
    // ����д�ļ���ͷ
    CStdioFile file;
    CString filename = L"mfc_file_append.txt";
    CString info = L"hello world5!";

    if (file.Open((LPCTSTR)filename, CFile::modeCreate | CFile::modeWrite | CFile::modeNoTruncate)) {
        //file.SeekToEnd();
        file.WriteString(info);
        file.Close();
    }

    return 0;
}

int test_mfc_c_stduio_file_append()
{
    // ׷��д
    CStdioFile file;
    CString filename = L"mfc_file_append.txt";
    CString info = L"hello world5!";

    if (file.Open((LPCTSTR)filename, CFile::modeCreate | CFile::modeWrite | CFile::modeNoTruncate)) {
        file.SeekToEnd();
        file.WriteString(info);
        file.Close();
    }

    return 0;
}

int test_ostream_file()
{
    // �½�д
    std::string filenmae = "ostream_file.txt";
    CStringA info = "���磬���2!";
    std::ofstream file(filenmae.c_str(), std::ios::binary | std::ios::trunc);

    if (file.is_open()) {
        file.write((LPCSTR)info, info.GetLength());
        file.close();
    }

    return 0;
}

// ������
int test_ostream_file_overide_begin()
{
    // ����д
    std::string filenmae = "ostream_file_overide_begin.txt";
    CStringA info = "���磬���4!";
    std::fstream file(filenmae.c_str(), std::ios::binary | std::ios::app);

    if (file.is_open()) {
        file.seekp(0, std::ios::beg);
        file.write((LPCSTR)info, info.GetLength());
        file.close();
    }

    return 0;
}

int test_ostream_file_append()
{
    // ׷��д
    std::string filenmae = "ostream_file_append.txt";
    CStringA info = "���磬���3!";
    std::ofstream file(filenmae.c_str(), std::ios::binary | std::ios::app);

    if (file.is_open()) {
        file.write((LPCSTR)info, info.GetLength());
        file.close();
    }

    return 0;
}


int test_wfopen_file()
{
    // �½�д
    CString filename = L"_wfopen_file.txt";
    CStringA info = "���磬���3!";
    FILE* fp_file = _wfopen((LPCWSTR)filename, L"w+b");

    if (fp_file) {
        fwrite((LPCSTR)info, 1, info.GetLength(), fp_file);
        // ʹ�� fwprintf �ַ���������
        //fwprintf(fp_file, L"%s", L"���磬���3!");
        fflush(fp_file);
        fclose(fp_file);
    }

    return 0;
}

int test_wfopen_file_append()
{
    // �½�д
    CString filename = L"_wfopen_file_append.txt";
    CStringA info = "���磬���3!";
    FILE* fp_file = _wfopen((LPCWSTR)filename, L"a+b");

    if (fp_file) {
        fwrite((LPCSTR)info, 1, info.GetLength(), fp_file);
        // ʹ�� fwprintf �ַ���������
        //fwprintf(fp_file, L"%s", L"���磬���3!");
        fflush(fp_file);
        fclose(fp_file);
    }

    return 0;
}


int test_wfopen_file_read()
{
    // �½�д
    CString filename = L"_wfopen_file_append.txt";
    CStringA info = "���磬���3!";
    FILE* fp_file = _wfopen((LPCWSTR)filename, L"a+b");

    if (fp_file) {
        fwrite((LPCSTR)info, 1, info.GetLength(), fp_file);
        // ʹ�� fwprintf �ַ���������
        //fwprintf(fp_file, L"%s", L"���磬���3!");
        fflush(fp_file);
        fclose(fp_file);
    }

    return 0;
}

int test_wfopen_s_file()
{
    FILE *fp;
    CString filename = L"_wfopen_s_file.txt";
    CStringA info = "���磬���3!";
    if (_wfopen_s(&fp, (LPCWSTR)filename, L"wb") == 0)
    {
        fwrite((LPCSTR)info, 1, info.GetLength(), fp);
        fflush(fp);
        fclose(fp);
    }

    return 0;
}

int test_wfopen_s_file_buffer()
{
    FILE *fp;
    CString filename = L"_wfopen_s_file.txt";
    std::string data;
    char szBuf[1024];
    if (_wfopen_s(&fp, (LPCWSTR)filename, L"rb") == 0)
    {
        // ��λ�� 2
        fseek(fp, 2, SEEK_SET);
        while (!feof(fp)) {
            size_t n = fread(szBuf, 1, sizeof(szBuf), fp);
            data.append(szBuf, n);
        }        
        fclose(fp);
    }

    std::cout << data.c_str() << std::endl;
    

    return 0;
}