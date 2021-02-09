/*======================================================================
Copyright (c) 2010,�����񣵣�����@126.com
All rights reserved.

�ļ����ƣ�MyThreadPool.h
ժ    Ҫ���������ģ��ʵ�����̳߳���Ķ���

��ǰ�汾��1.00
��    �ߣ������񣵣�����@126.com��ע��������ַ�����Ӣ���ַ���
������ڣ�2010��6��26��
����Blog��http://blog.csdn.net/zyq5945/
======================================================================*/

#pragma once
#include "msg_thread_pool.h"

/*======================================================================
�����ƣ�    CTask
��˵����    �Զ���Ĳ���������
            ���������ָ�������������Ļ�(�����ǳ����),
            û�а�������ǲ�Ҫ�ñ������ṩ��Ĭ�Ͽ������캯���͵ȺŲ�����
======================================================================*/
class CTask
{
public:
    CTask();
    CTask(const CTask& rTask);
    CTask& operator =(const CTask& rTask);

public:
    int m_nIndex;
    SYSTEMTIME m_cTime;

};

/*======================================================================
�����ƣ�    class CMyThreadPool : public CMsgThreadPool<CTask>
��˵����    �������̳߳���
            ��Ҫ���������麯��DoWork��ʵ��Ҫ���ľ��幤��
            Ҳ������˼̳�
            typedef CMsgThreadPool<CTask> CCTaskThreadPool;
            class CMyThreadPool : public CCTaskThreadPool
======================================================================*/
class CMyThreadPool : public CMsgThreadPool<CTask>
{
public:
    CMyThreadPool(void);
    ~CMyThreadPool(void);

protected:
    virtual void DoWork(CTask& rTask);
};
