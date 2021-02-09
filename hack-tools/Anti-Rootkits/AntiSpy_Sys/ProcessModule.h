#ifndef CXX_PROCESS_MODULE_H
#define CXX_PROCESS_MODULE_H

#include <ntifs.h>
#include"Function.h"
#include"SSDT.h"


#define _MAX_OBJECT_NAME   1024/sizeof(WCHAR) 
#define  MEM_IMAGE         0x01000000     // winnt




typedef struct _MEMORY_BASIC_INFORMATION {  
	PVOID       BaseAddress;           //��ѯ�ڴ����ռ�ĵ�һ��ҳ�����ַ
	PVOID       AllocationBase;        //�ڴ����ռ�ĵ�һ���������ַ��С�ڵ���BaseAddress��
	ULONG       AllocationProtect;     //���򱻳��α���ʱ����ı�������
	SIZE_T      RegionSize;            //��BaseAddress��ʼ��������ͬ���Ե�ҳ��Ĵ�С��
	ULONG       State;                 //ҳ���״̬�������ֿ���ֵMEM_COMMIT��MEM_FREE��MEM_RESERVE
	ULONG       Protect;               //ҳ������ԣ�����ܵ�ȡֵ��AllocationProtect��ͬ
	ULONG       Type;                  //���ڴ������ͣ������ֿ���ֵ��MEM_IMAGE��MEM_MAPPED��MEM_PRIVATE
} MEMORY_BASIC_INFORMATION, *PMEMORY_BASIC_INFORMATION;

typedef struct _MEMORY_SECTION_NAME  {  
	UNICODE_STRING Name;  
	WCHAR     Buffer[_MAX_OBJECT_NAME];  
}MEMORY_SECTION_NAME,*PMEMORY_SECTION_NAME;

typedef 
	NTSTATUS (*pfnNtQueryVirtualMemory)(
	__in HANDLE ProcessHandle,
	__in PVOID BaseAddress,
	__in MEMORY_INFORMATION_CLASS MemoryInformationClass,
	__out_bcount(MemoryInformationLength) PVOID MemoryInformation,
	__in SIZE_T MemoryInformationLength,
	__out_opt PSIZE_T ReturnLength
	);

//����Ring3����Ϣ

typedef struct _PROCESS_MODULE_ENTRY_INFOR_
{
	ULONG_PTR ModuleBase;
	ULONG     ModuleSize;
	WCHAR     ModulePath[260];
}PROCESS_MODULE_ENTRY_INFOR, *PPROCESS_MODULE_ENTRY_INFOR;

typedef struct _PROCESS_MODULE_INFORMATION
{
	ULONG_PTR    NumberOfModule;
	PROCESS_MODULE_ENTRY_INFOR Module[1];
}PROCESS_MODULE_INFORMATION, *PPROCESS_MODULE_INFORMATION;

NTSTATUS EnumMoudleByNtQueryVirtualMemory(ULONG ProcessId,PPROCESS_MODULE_INFORMATION OutBuffer,ULONG_PTR ulOutSize);


#endif