#ifndef CXX_FUNCTION_H
#define CXX_FUNCTION_H

#include <ntifs.h>
CHAR ChangePreMode(PETHREAD EThread);
VOID RecoverPreMode(PETHREAD EThread, CHAR PreMode);
VOID WPOFF();
VOID WPON();

typedef enum _MEMORY_INFORMATION_CLASS
{
	MemoryBasicInformation,     //�ڴ������Ϣ
	MemoryWorkingSetList,
	MemorySectionName           //�ڴ�ӳ���ļ�����Ϣ
}MEMORY_INFORMATION_CLASS;

#endif