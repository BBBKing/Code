#ifndef task_scheduler_h__
#define task_scheduler_h__

/**
 * @file
 * @brief windows�ƻ��������
 */

#include <Windows.h>
//#include <initguid.h>
#include <mstask.h>

namespace cactus
{


/**
 * @brief windows�ƻ�����ӿ�
 */
class ZLTaskScheduler
{
public:
    ///> �����򵥵Ŀ�����������
    static BOOL CreateSimpleLogonTaskScheduler(LPCTSTR lpTaskName, LPCTSTR lpAppFilePath);
    static BOOL CreateTaskScheduler(
        LPCTSTR lpTaskName,
        LPCTSTR lpAppFilePath,
        DWORD   dwTaskFlag,
        TASK_TRIGGER &stTrigger,
        LPCTSTR lpAccountName,
        LPCTSTR lpPassword
    );
    static BOOL DeleteTaskScheduler(LPCTSTR lpTaskName);

private:
    static void ZLTaskScheduler::_InitLogonTaskTrigger(TASK_TRIGGER &stTrigger);
};


// ������ʵ�ֲ���


} ///> end of namespace zl

#endif // task_scheduler_h__
