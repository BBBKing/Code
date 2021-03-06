// IOCTLS.H -- IOCTL code definitions for fileio driver

#ifndef IOCTLS_H
#define IOCTLS_H

#ifndef CTL_CODE
	#pragma message("CTL_CODE undefined. Include winioctl.h or wdm.h")
#endif

#define IOCTL_PROCESSDRIVER_PSPCIDTABLE_GETPROCESSNUMBER CTL_CODE(\
			FILE_DEVICE_UNKNOWN, \
			0x800, \
			METHOD_BUFFERED, \
			FILE_ANY_ACCESS)

#define IOCTL_PROCESSDRIVER_PSPCIDTABLE_GETPROCESSINFO CTL_CODE(\
			FILE_DEVICE_UNKNOWN, \
			0x801, \
			METHOD_BUFFERED, \
			FILE_ANY_ACCESS)

#define IOCTL_PROCESSDRIVER_TERMINATEPROCESS CTL_CODE(\
			FILE_DEVICE_UNKNOWN, \
			0x802, \
			METHOD_BUFFERED, \
			FILE_ANY_ACCESS)

#define IOCTL_PROCESSDRIVER_ACTIVEPROCESSLINKS CTL_CODE(\
			FILE_DEVICE_UNKNOWN, \
			0x803, \
			METHOD_BUFFERED, \
			FILE_ANY_ACCESS)

#define IOCTL_PROCESSDRIVER_OBJECTTABLE CTL_CODE(\
			FILE_DEVICE_UNKNOWN, \
			0x804, \
			METHOD_BUFFERED, \
			FILE_ANY_ACCESS)


#define IOCTL_SSDTDRIVER_GETSSDT CTL_CODE(\
			FILE_DEVICE_UNKNOWN, \
			0x810, \
			METHOD_BUFFERED, \
			FILE_ANY_ACCESS)

#define IOCTL_SSDTDRIVER_GETFUNADDRBYINDEX CTL_CODE(\
	       FILE_DEVICE_UNKNOWN, \
	       0x811, \
	       METHOD_BUFFERED, \
	       FILE_ANY_ACCESS)

#define IOCTL_SSDTDRIVER_RESTOREFUNADDR CTL_CODE(\
	       FILE_DEVICE_UNKNOWN, \
	       0x812, \
	       METHOD_BUFFERED, \
	       FILE_ANY_ACCESS)

#define IOCTL_PROCESS_MONITORDRIVER_ON CTL_CODE(\
			FILE_DEVICE_UNKNOWN, \
			0x820, \
			METHOD_BUFFERED, \
			FILE_ANY_ACCESS)

#define IOCTL_PROCESS_MONITORDRIVER_OFF CTL_CODE(\
			FILE_DEVICE_UNKNOWN, \
			0x821, \
			METHOD_BUFFERED, \
			FILE_ANY_ACCESS)


#endif
