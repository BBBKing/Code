/*======================================================================
Copyright (c) 2010,�����񣵣�����@126.com
All rights reserved.

�ļ����ƣ�MyThreadPool.cpp
ժ    Ҫ���������ģ��ʵ�����̳߳���ĺ���ʵ��

��ǰ�汾��1.00
��    �ߣ������񣵣�����@126.com��ע��������ַ�����Ӣ���ַ���
������ڣ�2010��6��26��
����Blog��http://blog.csdn.net/zyq5945/
======================================================================*/




#include "my_thread_pool.h"
#include <atlstr.h>

/*======================================================================
�������ƣ�  CTask::CTask()
����������  ��
  ����ֵ��  ��
����˵����  ���캯��
======================================================================*/
CTask::CTask()
{
    m_nIndex = 0;
    RtlZeroMemory(&m_cTime, sizeof(SYSTEMTIME));
}

/*======================================================================
�������ƣ�  CTask::CTask(const CTask& rTask)
����������  ��
  ����ֵ��  ��
����˵����  �������캯��
======================================================================*/
CTask::CTask(const CTask& rTask)
{
    m_nIndex    =   rTask.m_nIndex;
    m_cTime     =   rTask.m_cTime;
}

/*======================================================================
�������ƣ�  CTask& CTask::operator =(const CTask& rTask)
����������  ��
  ����ֵ��  ��
����˵����  �ȺŲ�����
======================================================================*/
CTask& CTask::operator =(const CTask& rTask)
{
    m_nIndex    =   rTask.m_nIndex;
    m_cTime     =   rTask.m_cTime;
    return *this;
}



/*======================================================================
�������ƣ�  CMyThreadPool::CMyThreadPool(void)
����������  ��
  ����ֵ��  ��
����˵����  ģ��ʵ�����̳߳ع��캯��
======================================================================*/
CMyThreadPool::CMyThreadPool(void)
{
}

/*======================================================================
�������ƣ�  CMyThreadPool::~CMyThreadPool(void)
����������  ��
  ����ֵ��  ��
����˵����  ģ��ʵ�����̳߳���������
======================================================================*/
CMyThreadPool::~CMyThreadPool(void)
{
}

/*======================================================================
�������ƣ�  void CMyThreadPool::DoWork(CTask& rTask)
����������  T& t
                һ����Ҫ��������������
����ֵ��    ��
����˵����  ��������������
            ע:���𱣴洫�ݹ����Ĳ���ָ��
======================================================================*/
void CMyThreadPool::DoWork(CTask& rTask)
{
    CString strMsg;
    SYSTEMTIME st;
    st = rTask.m_cTime;
    strMsg.Format(_T("\tIndex:%08d\t%02d:%02d:%02d.%03d\t\tTID:%08x\n"),
                  rTask.m_nIndex, st.wHour, st.wMinute, st.wSecond, st.wMilliseconds, GetCurrentThreadId());
    // �ڵ��Դ���������������
    OutputDebugString(strMsg);
    // ģ���̴߳�������ʱ��
    DWORD dwSleep = st.wMilliseconds > 500 ? st.wMilliseconds : 500;
    Sleep(dwSleep);
}
