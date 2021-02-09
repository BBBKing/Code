/*======================================================================
Copyright (c) 2010,�����񣵣�����@126.com
All rights reserved.

�ļ����ƣ�MsgThreadPool.h
ժ    Ҫ��һ��ģ���̳߳��࣬û��ʹ���źŵƣ��������ͬ������

��ǰ�汾��1.00
��    �ߣ������񣵣�����@126.com��ע��������ַ�����Ӣ���ַ���
������ڣ�2010��6��26��
����Blog��http://blog.csdn.net/zyq5945/
======================================================================*/

#pragma once
#include <Windows.h>
#include <process.h>
#include <vector>
#include <list>
#include <deque>

using namespace std;

#ifdef _DEBUG
    #define new DEBUG_NEW
#endif

#define ASSERT
#ifdef _DEBUG
    #include <atltrace.h>
    #define TRACE ATLTRACE
    #define VERIFY(f)          ASSERT(f)
    #define DEBUG_ONLY(f)      (f)
#else // _DEBUG
    #define TRACE              __noop
    #define VERIFY(f)          ((void)(f))
    #define DEBUG_ONLY(f)      ((void)0)
#endif


// Ĭ�ϵĿ��������̸߳����߳�
#define THREAD_NUM      10

// ������ʱ��ɾ�����е�δ���������
#define TM_DELETETASK       WM_USER
// ���ù����̵߳ĸ���
#define TM_SETTHREADNUM     WM_USER + 1
// �������
#define TM_ADDTASK          WM_USER + 2
// �ڹ����߳����Ǵ�������
// �ڹ����߳����Ǹ������̷߳�������
#define TM_DISPOSETASK      WM_USER + 3
// �����̸߳��߹����̸߳��߳��ǿ��е�
#define TM_KICKIDLE         WM_USER + 4


/*======================================================================
�ṹ�����ƣ�PoolStatus
�ṹ��˵�����̳߳ص�״̬�ṹ��
======================================================================*/
typedef struct _PoolStatus {
    unsigned int uiTotalThread;     //�ܵ��߳���
    unsigned int uiIdleThread;      //�����߳���
    unsigned int uiTask;            //���������е��������
} PoolStatus;


/*======================================================================
�����ƣ�template <typename T> class CMsgThreadPool
��˵����ģ�����������ʵ�ֲ��ֿܷ�,�����������Ӵ���
======================================================================*/
template <typename T>
class CMsgThreadPool
{
public:
    /*======================================================================
    �������ƣ�  CMsgThreadPool(void)
    ����������  ��
      ����ֵ��  ��
    ����˵����  ��ʼ�����Ա����
    ======================================================================*/
    CMsgThreadPool(void)
    {
        m_ManagerTID = 0;
        m_TaskList.resize(0);
        m_dwThreadId.resize(0);
        m_dwIdleTId.resize(0);
    }

    /*======================================================================
    �������ƣ�  virtual ~CMsgThreadPool(void)
    ����������  ��
      ����ֵ��  ��
    ����˵����  �̳߳��˳����������
    ======================================================================*/
    virtual ~CMsgThreadPool(void)
    {
        // ɾ������δ���������
        VERIFY(PostTM((DWORD)m_ManagerTID,
                      TM_DELETETASK, 0, 0));
        // ֪ͨ���еĹ����߳��˳�
        list<DWORD>::const_iterator it ;

        for (it = m_dwThreadId.begin();
             it != m_dwThreadId.end(); ++it) {
            VERIFY(PostTM(*it,
                          WM_QUIT, 0, 0));
        }

#if _MSC_VER >= 1500
        /*======================================================================
        MS VC++ 9.0 _MSC_VER = 1500
        MS VC++ 8.0 _MSC_VER = 1400
        MS VC++ 7.1 _MSC_VER = 1310
        MS VC++ 7.0 _MSC_VER = 1300
        MS VC++ 6.0 _MSC_VER = 1200
        MS VC++ 5.0 _MSC_VER = 1100
        ˵��:   ����������VS2008SP1�в���ͨ��,������Ҫ�������޸Ĳ���
        ======================================================================*/
        // ��ȡ���й����̵߳ľ��
        vector<HANDLE> hAllThread;

        while (m_dwThreadId.size() > 0) {
            DWORD dwTID = m_dwThreadId.front();
            m_dwThreadId.pop_front();
            HANDLE handle = OpenThread(THREAD_ALL_ACCESS,
                                       FALSE, dwTID);

            if (handle != NULL) {
                hAllThread.push_back(handle);
            }
        }

        // �ȴ����й����߳��˳�
        if (hAllThread.size() > 0) {
            WaitForMultipleObjects(hAllThread.size(),
                                   (const HANDLE *)&hAllThread[0], TRUE, INFINITE);

            for (DWORD i = 0; i < hAllThread.size(); i++) {
                CloseHandle(hAllThread[i]);
            }
        }

        hAllThread.clear();
#endif
        // ֪ͨ�����߳��˳�
        VERIFY(PostTM((DWORD)m_ManagerTID,
                      WM_QUIT, 0, 0));
#if _MSC_VER >= 1500
        /*======================================================================
        MS VC++ 9.0 _MSC_VER = 1500
        MS VC++ 8.0 _MSC_VER = 1400
        MS VC++ 7.1 _MSC_VER = 1310
        MS VC++ 7.0 _MSC_VER = 1300
        MS VC++ 6.0 _MSC_VER = 1200
        MS VC++ 5.0 _MSC_VER = 1100
        ˵��:   ����������VS2008SP1�в���ͨ��,������Ҫ�������޸Ĳ���
        ======================================================================*/
        // ��ȡ�����̵߳ľ��
        HANDLE handle = OpenThread(THREAD_ALL_ACCESS,
                                   FALSE, m_ManagerTID);

        // �ȴ������߳��˳�
        if (handle != NULL) {
            WaitForSingleObject(handle, INFINITE);
            CloseHandle(handle);
        }

#endif
    }

public:
    /*======================================================================
    �������ƣ�  virtual void DoWork(T& t) = 0
    ����������  T& t
                    һ����Ҫ��������������
      ����ֵ��  ��
    ����˵����  �ú�����Ҫ��������ʵ�־�������������
    ======================================================================*/
    virtual void DoWork(T& t) = 0;                  // ��������Ҫ���Ĺ���

public:
    /*======================================================================
    �������ƣ�  BOOL Init(DWORD dwThreadNum = THREAD_NUM)
    ����������  DWORD dwThreadNum = THREAD_NUM
                    ��ʼ���Ĺ����̸߳���,Ĭ����10
      ����ֵ��  �ú���ִ�гɹ�����TRUE,����FALSE
    ����˵����  �û��ӿں���,��ʼ���̳߳�
    ======================================================================*/
    BOOL Init(DWORD dwThreadNum = THREAD_NUM)
    {
        ASSERT(dwThreadNum >= 1);
        ASSERT(m_ManagerTID == 0);
        // ���������߳�
        HANDLE hManager = NULL;
        hManager = (HANDLE)_beginthreadex(NULL,
                                          0, &CMsgThreadPool::ManagerThread, this, 0, &m_ManagerTID);

        if (hManager == 0) {
            return FALSE;
        }

        CloseHandle(hManager);
        hManager = NULL;
        // ���ù����̸߳���
        SetThreadNum(dwThreadNum);
        return TRUE;
    }

    /*======================================================================
    �������ƣ�  void SetThreadNum(DWORD dwThreadNum = THREAD_NUM)
    ����������  DWORD dwThreadNum = THREAD_NUM
                    ��ʼ���Ĺ����̸߳���,Ĭ����10
      ����ֵ��  ��
    ����˵����  �û��ӿں���,���ù����̵߳ĸ���
    ======================================================================*/
    void SetThreadNum(DWORD dwThreadNum = THREAD_NUM)
    {
        ASSERT(dwThreadNum >= 1);
        ASSERT(m_ManagerTID != 0);
        VERIFY(PostTM((DWORD)m_ManagerTID,
                      TM_SETTHREADNUM, (WPARAM)dwThreadNum, 0));
        return ;
    }

    /*======================================================================
    �������ƣ�  void AddTask(T& t)
    ����������  T& t
                    һ��Ҫ��������������
      ����ֵ��  ��
    ����˵����  �û��ӿں���,��������̳߳���
    ======================================================================*/
    void AddTask(T& t)
    {
        T* pT = new T;
        *pT = t;
        VERIFY(PostTM((DWORD)m_ManagerTID,
                      TM_ADDTASK, (WPARAM)pT, 0));
    }

    /*======================================================================
    �������ƣ�  PoolStatus GetStatus() const
    ����������  ��
      ����ֵ��  PoolStatus
                    �̳߳ص�״̬�ṹ��
    ����˵����  �û��ӿں���,��ȡ�̳߳ص�״̬
    ======================================================================*/
    PoolStatus GetStatus() const
    {
        PoolStatus cStatus;
        cStatus.uiTotalThread   =       m_dwThreadId.size();
        cStatus.uiIdleThread        =       m_dwIdleTId.size();
        cStatus.uiTask          =       m_TaskList.size();
        return cStatus;
    }

public:
    /*======================================================================
    �������ƣ�  DWORD GetManager() const
    ����������  ��
      ����ֵ��  DWORD
                    ���ع����̵߳��߳�ID
    ����˵����  �ú�����Ȼ��һ��public���Ա����,�������û��ӿں���,
                ��Ҫ�������ڹ����߳��л�ȡ�����̵߳�ID
    ======================================================================*/
    DWORD GetManager() const
    {
        ASSERT((DWORD)m_ManagerTID != 0);
        return m_ManagerTID;
    }

private:
    /*======================================================================
    �������ƣ�  static unsigned int WINAPI ManagerThread(void* pParam)
    ����������  void* pParam
                    ģ���̳߳ص�ָ��
      ����ֵ��  unsigned int
    ����˵����  �����߳�,ά�������̶߳��к��������,��Э�������ǵĹ���
    ======================================================================*/
    static unsigned int WINAPI ManagerThread(void* pParam)      // �����߳�
    {
        ASSERT(pParam != NULL);
        CMsgThreadPool* pPool = (CMsgThreadPool*)pParam;
        T* t = NULL;
        MSG msg;

        // ѭ����ȡ��Ϣ,������ʱ����յ�WM_QUIT��Ϣ�˳�ѭ��
        while (GetMessage(&msg, NULL, 0, 0)) {
            // ������Ϣ
            pPool->DisposeMsg(msg.message, msg.wParam, msg.lParam);
        }

        _endthreadex(0);
        return 0;
    }

    /*======================================================================
    �������ƣ�  static unsigned int WINAPI OperatorThread(void* pParam)
    ����������  void* pParam
                    ģ���̳߳ص�ָ��
      ����ֵ��  unsigned int
    ����˵����  �����߳�,���ϵĻ�ȡ���񲢴���
                ������ʱ����յ�WM_QUIT��Ϣ�˳�ѭ��
    ======================================================================*/
    static unsigned int WINAPI OperatorThread(void* pParam)     // �����߳�
    {
        ASSERT(pParam != NULL);
        DWORD dwThreadId = GetCurrentThreadId();
        CMsgThreadPool* pPool = (CMsgThreadPool*)pParam;
        // ���߹����߳������ǿ��е�
        VERIFY(PostTM(pPool->GetManager(),
                      TM_KICKIDLE, (WPARAM)0, (LPARAM)dwThreadId));
        T* t = NULL;
        MSG msg;

        // ѭ����ȡ��Ϣ,������ʱ����յ�WM_QUIT��Ϣ�˳�ѭ��
        while (GetMessage(&msg, NULL, 0, 0)) {
            switch (msg.message) {
            case TM_DISPOSETASK:
                t = (T *)msg.wParam;
                ASSERT(t != NULL);
                // ��������������
                pPool->DoWork(*t);
                delete t;
                t = NULL;
                // ���߹����߳��Ѿ�������һ������,�����ǿ��е�
                VERIFY(PostTM(pPool->GetManager(),
                              TM_KICKIDLE, 0, (LPARAM)dwThreadId));
                break;

            default:
                break;
            }
        }

        _endthreadex(0);
        return dwThreadId;
    }

private:
    /*======================================================================
    �������ƣ�  BOOL CreateOperator(DWORD dwThreadNum)
    ����������  DWORD dwThreadNum
                    �����Ĺ����̸߳���,Ĭ����10
      ����ֵ��  �ú���ִ�гɹ�����TRUE,����FALSE
    ����˵����  ���������߳�
    ======================================================================*/
    BOOL CreateOperator(DWORD dwThreadNum)
    {
        HANDLE hOperator = NULL;
        unsigned int dwThreadId = 0;
        UINT i = 0;

        for (i = 0; i < dwThreadNum; i++) {
            // ���������߳�
            hOperator = (HANDLE)_beginthreadex(NULL,
                                               0, &CMsgThreadPool::OperatorThread, this, 0, &dwThreadId);

            if (hOperator == 0) {
                return FALSE;
            }

            // ��ӵ������߳�����
            m_dwThreadId.push_back(dwThreadId);
            CloseHandle(hOperator);
            hOperator = NULL;
        }

        return TRUE;
    }

    /*======================================================================
    �������ƣ�  void DestryOperator(DWORD dwThreadNum)
    ����������  DWORD dwThreadNum
                    ���ٵĹ����̸߳���
      ����ֵ��  ��
    ����˵����  ���ٹ����߳�.
                ע:��û�п����̵߳�ʱ�����ٹ����߳�
    ======================================================================*/
    void DestryOperator(DWORD dwThreadNum)
    {
        DWORD dwCount = dwThreadNum < m_dwIdleTId.size() ?
                        dwThreadNum : m_dwIdleTId.size();

        for (DWORD i = 0; i < dwCount; i++) {
            DWORD dwThreadID = m_dwIdleTId.front();
            // ֪ͨ�����߳��˳�
            VERIFY(PostTM(dwThreadID,
                          WM_QUIT, 0, 0));
            m_dwIdleTId.pop_front();
            // ɾ�����ڹ����߳������м�¼
            m_dwThreadId.remove(dwThreadID);
        }
    }

    /*======================================================================
    �������ƣ�  void DisposeMsg(UINT uMsg, WPARAM wParam, LPARAM lParam)
    ����������  UINT uMsg
                    ��Ϣ����
                WPARAM wParam
                LPARAM lParam
      ����ֵ��  ��
    ����˵����  �����߳�ͨ����Ϣά�������̶߳��к��������,
                ��Э�������ǵĹ���
    ======================================================================*/
    void DisposeMsg(UINT uMsg, WPARAM wParam, LPARAM lParam)
    {
        ASSERT((DWORD)m_ManagerTID != 0);

        switch (uMsg) {
        // �����߳̿���
        case TM_KICKIDLE:
            OnKickIdle(wParam, lParam);
            break;

        // ���������
        case TM_ADDTASK:
            OnAddTask(wParam, lParam);
            break;

        // ������������еĹ����߳�
        case TM_DISPOSETASK:
            OnTmDisposeTask(wParam, lParam);
            break;

        // ɾ�����е�δ���������
        case TM_DELETETASK:
            OnDeleteTask(wParam, lParam);
            break;

        // ���ù����̵߳ĸ���
        case TM_SETTHREADNUM:
            OnSetThreadNum(wParam, lParam);
            break;

        default:
            break;
        }
    }

private:
    /*======================================================================
    �������ƣ�  static BOOL PostTM(DWORD dwID, UINT uMsg, WPARAM wParam, LPARAM lParam)
    ����������  DWORD dwID
                    ��Ҫ���͵��߳�ID
                UINT uMsg
                    ��Ҫ���͵���Ϣ����
                WPARAM wParam
                LPARAM lParam
      ����ֵ��  �ú���ִ�гɹ�����TRUE,����FALSE
    ����˵����  �����Ƕ�PostThreadMessage����һ�η�װ,
                �ڱ������Ե�һ����PostThreadMessage���͵�ʱ���ʧ��
    ======================================================================*/
    static BOOL PostTM(DWORD dwID, UINT uMsg, WPARAM wParam, LPARAM lParam)
    {
#define TRY_COUNT       100
        UINT nCount = 0;

        while (nCount++ <= TRY_COUNT) {
            if (PostThreadMessage(dwID, uMsg, wParam, lParam)) {
                return TRUE;
            }

#ifdef _DEBUG
            static DWORD dwCount = 0;
            TRACE(_T("\t TRY_COUNT:%d Error:%d\n"), dwCount++, GetLastError());
#endif
            Sleep(200);
        }

        // ������Ϣʧ�ܣ��鷳���ˣ�����
        ASSERT(FALSE);
        return FALSE;
    }

    /*======================================================================
    �������ƣ�  void OnTmDisposeTask(WPARAM wParam, LPARAM lParam)
    ����������  WPARAM wParam
                LPARAM lParam
      ����ֵ��  ��
    ����˵����  �������̷߳�������
    ======================================================================*/
    void OnTmDisposeTask(WPARAM wParam, LPARAM lParam)
    {
        T* pT = NULL;
        DWORD dwThreadId = 0;

        while ((m_TaskList.size() != 0)
               && (m_dwIdleTId.size() != 0)) {
            // ������������ȡ������
            pT = m_TaskList.front();
            ASSERT(pT != NULL);
            // �ӿ��й����߳�������ȡ����ID
            dwThreadId = m_dwIdleTId.front();
            // �������͸������߳�
            VERIFY(PostTM(dwThreadId,
                          TM_DISPOSETASK, (WPARAM)pT, 0));
            m_TaskList.pop_front();
            m_dwIdleTId.pop_front();
        }
    }

    /*======================================================================
    �������ƣ�  void OnDeleteTask(WPARAM wParam, LPARAM lParam)
    ����������  WPARAM wParam
                LPARAM lParam
    ����ֵ��    ��
    ����˵����  ɾ�����е�δ���������
    ======================================================================*/
    void OnDeleteTask(WPARAM wParam, LPARAM lParam)
    {
        T* pT = NULL;

        while (m_TaskList.size() > 0) {
            pT = m_TaskList.front();
            ASSERT(pT != NULL);
            delete pT;
            m_TaskList.pop_front();
        }
    }

    /*======================================================================
    �������ƣ�  void OnKickIdle(WPARAM wParam, LPARAM lParam)
    ����������  WPARAM wParam
                LPARAM lParam
      ����ֵ��  ��
    ����˵����  �����̸߳��߹����̸߳��߳��ǿ��е�
    ======================================================================*/
    void OnKickIdle(WPARAM wParam, LPARAM lParam)
    {
        // ���̼߳�������̶߳���
        m_dwIdleTId.push_back((DWORD)lParam);
        VERIFY(PostTM((DWORD)m_ManagerTID,
                      TM_DISPOSETASK, 0, 0));
    }

    /*======================================================================
    �������ƣ�  void OnAddTask(WPARAM wParam, LPARAM lParam)
    ����������  WPARAM wParam
                LPARAM lParam
      ����ֵ��  ��
    ����˵����  �����������������
    ======================================================================*/
    void OnAddTask(WPARAM wParam, LPARAM lParam)
    {
        // �����������������
        ASSERT(wParam != 0);
        // ����������������
        m_TaskList.push_back((T*)wParam);
        VERIFY(PostTM((DWORD)m_ManagerTID,
                      TM_DISPOSETASK, 0, 0));
    }

    /*======================================================================
    �������ƣ�  void OnSetThreadNum(WPARAM wParam, LPARAM lParam)
    ����������  WPARAM wParam
                LPARAM lParam
      ����ֵ��  ��
    ����˵����  ���ù����̵߳ĸ���
    ======================================================================*/
    void OnSetThreadNum(WPARAM wParam, LPARAM lParam)
    {
        DWORD dwThreadNum = (DWORD)wParam;

        if (dwThreadNum > m_dwThreadId.size()) {
            VERIFY(CreateOperator(dwThreadNum - m_dwThreadId.size()));
        } else if (dwThreadNum < m_dwThreadId.size()) {
            DestryOperator(m_dwThreadId.size() - dwThreadNum);
        }
    }

private:
    unsigned int m_ManagerTID;                      // �������߳�ID
    list<DWORD> m_dwThreadId;                       // �����̵߳��߳�ID
    deque<T*> m_TaskList;                           // ������
    deque<DWORD> m_dwIdleTId;                       // �����߳�
};