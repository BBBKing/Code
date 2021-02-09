#include "Function.h"

KIRQL Irql;

CHAR ChangePreMode(PETHREAD EThread)
{
	ULONG_PTR PreviousModeOffsetOf_KTHREAD = 0x140;

	CHAR PreMode = *(PCHAR)((ULONG_PTR)EThread + PreviousModeOffsetOf_KTHREAD);

	*(PCHAR)((ULONG_PTR)EThread + PreviousModeOffsetOf_KTHREAD) = KernelMode;

	return PreMode;
}

VOID RecoverPreMode(PETHREAD EThread, CHAR PreMode)
{
	ULONG_PTR PreviousModeOffsetOf_KTHREAD = 0x140;

	*(PCHAR)((ULONG_PTR)EThread + PreviousModeOffsetOf_KTHREAD) = PreMode;
}


VOID WPOFF()
{
	ULONG_PTR cr0 = 0;
	Irql = KeRaiseIrqlToDpcLevel();
	cr0 =__readcr0();
	cr0 &= 0xfffffffffffeffff;
	__writecr0(cr0);
	//	_disable();                      //��仰 ����Ҳûɶ

}

VOID WPON()
{

	ULONG_PTR cr0=__readcr0();
	cr0 |= 0x10000;
	//	_enable();                       //��仰 ����Ҳûɶ
	__writecr0(cr0);
	KeLowerIrql(Irql);
}