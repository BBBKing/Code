#ifndef time_h__
#define time_h__

#include <Windows.h>

namespace cactus
{

/**
 * @brief ʱ����ز���
 */
class ZLTime
{
public:
    /**
     * @brief __time64_t��FileTime��ת��
     * @param[in] tm __time64_t
     * @return �ɹ�����FILETIME
     */
    static FILETIME Time642FileTime(const __time64_t& tm);
    /**
     * @brief FileTime��__time64_t��ת��
     * @param[in] pft FILETIME�ṹ��ָ��
     * @return ����__time64_t
     */
    static __time64_t FileTime2Time64(const FILETIME& pft);

    static __time64_t SystemTime2Time64(const SYSTEMTIME& st);

    static BOOL SystemTime2FileTime(const SYSTEMTIME& syst, FILETIME& filet);

    static BOOL FileTime2SystemTime(const FILETIME& filet, SYSTEMTIME& syst);

    static SYSTEMTIME GetLocalTime();

    static SYSTEMTIME GetSystemTime();
    /**
     * @brief ����TimeInterval
     * @param[in]  llTimeBegin    ��ʼʱ��
     * @param[out] dfTimeInterval TimeInterval
     * @return �ɹ�����TRUE��ʧ�ܷ���FALSE
     */
    static BOOL Calc(LARGE_INTEGER& llTimeBegin, double& dfTimeInterval);

    static BOOL GetTime(LARGE_INTEGER& llCurrentTime);
};

void PrintSystemTime(PCHAR lpszBuf, DWORD cbBuf);


}


#endif // time_h__
