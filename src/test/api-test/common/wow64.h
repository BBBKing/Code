#ifndef wow64_h__
#define wow64_h__

#include <Windows.h>
#include <tchar.h>

namespace cactus
{

typedef
BOOL
WINAPI
Fn_Wow64DisableWow64FsRedirectionFunction(
    __out PVOID *OldValue
);

typedef
BOOL
WINAPI
Fn_Wow64RevertWow64FsRedirectionFunction(
    __in PVOID OlValue
);

typedef BOOL
WINAPI
Fn_IsWow64Process(
    __in  HANDLE hProcess,
    __out PBOOL Wow64Process
);
/**
 * @brief 32λ��64λ���ݴ���
 */
class ZLWow64
{
public:
    ZLWow64();
    ~ZLWow64();

public:
    /**
     * @brief �����Ƿ�������Wow64��
     * @param[in]  hProcess       ���̾��
     * @param[out] pbWow64Process BOOLָ��
     * @return �ɹ�����TRUE��ʧ�ܷ���FALSE
     * @see IsWow64Process
     */
    static BOOL CheckIsWow64Process(HANDLE hProcess, BOOL* pbWow64Process);
    /**
     * @brief ��ǰ�����Ƿ�������Wow64��
     * @param[out] pbWow64Process BOOLָ��
     * @return �ɹ�����TRUE��ʧ�ܷ���FALSE
     */
    static BOOL CheckCurrentProcessIsWow64Process(BOOL* pbWow64Process);
    /**
     * @brief �����ļ�ϵͳ�ض���Ϊ�����߳�
     * @param[out] ppVoidValue Wow64�ļ�ϵͳ�ض���ֵ
     * @return �ɹ�����TRUE��ʧ�ܷ���FALSE
     */
    static BOOL Wow64DisableWow64FsRedirection(PVOID* ppVoidValue);
    /**
     * @brief �ָ��ļ�ϵͳ�ض���Ϊ�����߳�
     * @param[in] ppVoidValue Wow64�ļ�ϵͳ�ض���ֵ
     * @return �ɹ�����TRUE��ʧ�ܷ���FALSE
     */
    static BOOL Wow64RevertWow64FsRedirection(PVOID pOldValue);
};

class ZLWow64Guard
{
public:
    ZLWow64Guard();

    ~ZLWow64Guard();

private:
    BOOL  bIsWow64_;
    PVOID pVoidValue_;
};

}

#endif // wow64_h__
