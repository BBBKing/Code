#ifndef memory_h__
#define memory_h__

#include <Windows.h>

namespace cactus
{

/**
 * @brief ��ȡ�ڴ��С
 */
class ZLMemory
{
public:
    /**
     * @brief ��ȡ�ڴ��С����MBΪ��λ
     * @return �ɹ������ڴ��С(MB)
     */
    static ULONG GetMemorySize();

    /**
     * @brief ��ȡ��ʹ���ڴ��С����MBΪ��λ
     * @return �ɹ������ڴ��С(MB)
     */
    static ULONGLONG GetUsedMem();
};


}

#endif // memory_h__
