////////////////////////////////////////////////////////////////////////////////
//      
//      Kingsoft File for kiscomm
//      
//      File      : kis_singletem.h
//      Version   : 1.0
//      Comment   : ����һ���̰߳�ȫ�ĵ������������߳�ͬʱ��ʼ��
//      
//      Create at : 2008-3-5
//      Create by : liupeng
//      
////////////////////////////////////////////////////////////////////////////////
#pragma once

template<class T>
class KThreadSafeSigletem
{
public:
	_declspec(noinline) static T& Instance()
	{
		static T* _pInst = NULL;
		static volatile LONG _lock = 0;
		while (!_pInst)
		{
			if (::InterlockedIncrement(&_lock) == 1)
			{
				_pInst = CreateInstance();
				::InterlockedDecrement(&_lock);
			}
			else
			{
				::InterlockedDecrement(&_lock);
				::Sleep(10);
			}
		}
		return *_pInst;
	}

private:
	_declspec(noinline) static T* CreateInstance()
	{
		static T _inst;
		return &_inst;
	}
};