#pragma once
#include <vector>
#include <Windows.h>
#include <atlstr.h>
#include "KDosNames.h"
#include <map>

namespace pnpsub
{



class KPsapiDllFunction
{
public:
	KPsapiDllFunction();
	~KPsapiDllFunction();

	BOOL Init();
	void UnInit();

	BOOL EnumProcesses(DWORD* pProcessIds, DWORD cb,	DWORD* pBytesReturned);
	DWORD GetModuleBaseName(HANDLE hProcess, HMODULE hModule, LPWSTR lpBaseName,	DWORD nSize);
	BOOL EnumProcessModules(HANDLE hProcess, HMODULE* lphModule, DWORD cb, LPDWORD lpcbNeeded);
	DWORD GetModuleFileNameEx(HANDLE hProcess, HMODULE hModule, LPWSTR lpFilename,DWORD nSize);
	DWORD GetProcessImageFileName(	HANDLE hProcess, LPWSTR lpImageFileName, DWORD nSize);

protected:
	typedef BOOL (WINAPI *PEnumProcesses)(DWORD* pProcessIds, DWORD cb,	DWORD* pBytesReturned);
	typedef DWORD (WINAPI *PGetModuleBaseName)(HANDLE hProcess, HMODULE hModule, LPWSTR lpBaseName,	DWORD nSize);
	typedef BOOL (WINAPI *PEnumProcessModules)(HANDLE hProcess, HMODULE* lphModule, DWORD cb, LPDWORD lpcbNeeded);
	typedef DWORD (WINAPI *PGetModuleFileNameEx)(HANDLE hProcess, HMODULE hModule, LPWSTR lpFilename,DWORD nSize);
	typedef BOOL (WINAPI *PGetProcessImageFileName)(HANDLE hProcess,LPWSTR lpImageFileName, DWORD nSize);

	PEnumProcesses		m_pEnumProcesses;
	PGetModuleBaseName	m_pGetModuleBaseName;
	PEnumProcessModules  m_pEnumProcessModules;
	PGetModuleFileNameEx m_pGetModuleFileNameEx;
	PGetProcessImageFileName m_pGetProcessImageFileName;

private:
	BOOL m_bInited;
	HMODULE m_hPsapi;
};


class KSysProcess
{
public:
	KSysProcess(void);
	~KSysProcess(void);

	CStringW		GetProcessPath(int nPid);
	BOOL		GetAllProcess(std::vector<int>& vecPID);
	BOOL		GetProcessModules( int nPID, std::vector<CStringW> &vecModule );
	BOOL		GetDebugPrivilege(void);
	BOOL		IsWow64();
	int	GetParentProcessID(int nId);

protected:
	BOOL ConvertSysPath(CStringW& strPath);
	CStringW GetProcessPath64(HANDLE hProcess);
	CStringW GetProcessPath32(HANDLE hProcess);

private:
	KPsapiDllFunction m_psapi;
	KDosNames m_dosNames;
};

//-------------------------------------------------------------------------

typedef struct _S_PROC_INFO
{
    int                             nProcessId;         ///< ���� id
    std::wstring                    wstrExePath;        ///< ���� exe ȫ·��
    //std::vector<std::wstring>       vecModuleList;      ///< ����ģ���б�

    _S_PROC_INFO() : nProcessId(-1)
    {
    }
} S_PROC_INFO;

typedef std::map<DWORD, S_PROC_INFO> MAP_PROCID_2_INFO;

interface IKSysProcessObserver
{
    /**
    * @brief        :  ֪ͨ�۲��߽����б�仯
    * @remark_1     :  ��Ϊ��һ�λص����� mapNewProc �б����˵�ǰϵͳ�����б�
    *                  mapEndProc ��Ϊ��
    * @remark_2     :  �۲��߲�Ӧ���ڻص���ִ�к�ʱ�����Է�Ӱ�������۲���
    * @param[in]    :  mapNewProc �½������Ľ����б�
    * @param[in]    :  mapEndProc �½���ֹ�Ľ����б�
     * @return       :  S_OK �ɹ�������ΪHRESULT������
    */
    virtual HRESULT __stdcall NotifyProcessChange(
        /*[in]*/    const MAP_PROCID_2_INFO&    mapNewProc,
        /*[in]*/    const MAP_PROCID_2_INFO&    mapEndProc
        ) = 0;
};

interface IKSysProcessSubject
{
    virtual HRESULT __stdcall RegisterObserver(
        IKSysProcessObserver* pIObserver
        ) = 0;

    virtual HRESULT __stdcall UnregisterObserver(
        IKSysProcessObserver* pIObserver
        ) = 0;
};

/*
*@brief  : ��ǰϵͳ������Ϣ�ṩ��
*@remark : 1. �ڲ�ÿ2����ˢ��һ�Σ����ص�֪ͨ�۲��ߡ��������б��ޱ仯����ص���ȥ��
*             ����״̬�б�Ϊ��
*          2. ֻҪ�ⲿ����Ч�Ĺ۲���ע����������ڲ��������߳�����ؽ����б��ⲿ��
*             ���ֶ��������
*          3. ���۲����б�Ϊ��ʱ��ֹͣ���̼��
*          4. ��ʵ��Ϊ�̰߳�ȫ
*/
class KSysProcessMonitor : public IKSysProcessSubject
{
public:
    static KSysProcessMonitor& Instance();
    ~KSysProcessMonitor();

public:
    virtual HRESULT __stdcall RegisterObserver(
        IKSysProcessObserver* pIObserver
        );

    virtual HRESULT __stdcall UnregisterObserver(
        IKSysProcessObserver* pIObserver
        );

private:
    typedef std::map<IKSysProcessObserver*, bool>   MAP_OBSERVER_2_NOTIFIED;

private:
    KSysProcessMonitor();
    static DWORD WINAPI MonitorThread(LPVOID lParam);
    DWORD WINAPI MonitorThreadRun();
    HRESULT WaitStopMonitor(DWORD dwTimeout);
    BOOL RefreshCurProcList(
        /*[out]*/   MAP_PROCID_2_INFO& mapProcNew,  // �����Ľ����б�
        /*[out]*/   MAP_PROCID_2_INFO& mapProcEnd   // �����Ľ����б�
        );
    BOOL SleepWithVigilance();  // �������ʾ��Ҫ�˳��߳�
    void NotifyObservers(
        const MAP_PROCID_2_INFO& mapProcNew,
        const MAP_PROCID_2_INFO& mapProcEnd
        );

private:
    ATL::CComAutoCriticalSection        m_csMonitorThread;
    HANDLE                              m_hMonitorThread;

    ATL::CComAutoCriticalSection        m_csProcData;
    MAP_PROCID_2_INFO                   m_mapProcId2Info;

    ATL::CComAutoCriticalSection        m_csObserver;
    MAP_OBSERVER_2_NOTIFIED             m_mapObserver;

    bool                                m_bStop;

    KSysProcess                         m_sysProcess;
};

}