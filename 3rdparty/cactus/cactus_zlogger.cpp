
/**
 * \brief Zebra��Ŀ��־ϵͳ�����ļ�
 **/

#include <cactus/cactus_zlogger.h>
#include <cactus/cactus_file.h>
#include <vector>
#include <stdarg.h>
#include <Windows.h>

//#include "drivergenius/utils/utils.h"
using namespace cactus;

namespace Zebra
{
	zLogger *logger = NULL;
};

/**
 * \brief ����һ��zLogger 
 * \param  name zLogger�����֣�����������������־�е�ÿһ��
 **/
zLogger::zLogger(wchar_t *name, const wchar_t *file)
  :	m_level(LEVEL_DEBUG)
  ,	fp_console(stdout)
  ,	fp_file(NULL)
  ,	m_day(0)
  , m_use_day(false)
  ,	m_name(name)
//  , m_file(file)
{
    m_file = Path::GetAppDir();
	m_file = m_file + std::wstring(_T("log\\")) + file;
}

/**
 * \brief ��������
 **/
zLogger::~zLogger()
{
	if (NULL != fp_file)
	{
		fclose(fp_file);
		fp_file = NULL;
	}
}

/**
 * \brief �Ƴ�����̨Log���
 **/
void zLogger::removeConsoleLog()
{
	msgMut.lock();
	fp_console = NULL;
	msgMut.unlock();
}

void zLogger::setLogPath(const std::wstring &file)
{
	m_file = file;
}

/**
 * \brief ��һ�������ļ�Log���
 * \param file Ҫ������ļ�����Logger���Զ������ʱ���׺ 
 * \return ��
 **/
void zLogger::addLocalFileLog(const std::wstring &file)
{
	msgMut.lock();
	m_day  = 0;
	//m_file = file;
	m_file = std::wstring(_T("log\\")) + file;
	msgMut.unlock();
}

/**
 * \brief ����д��־�ȼ�
 * \param  zLevelPtr ��־�ȼ�.�μ� #zLogger::zLevel
 **/
void zLogger::setLevel(const zLevel level)
{
	msgMut.lock();
	m_level = level;
	msgMut.unlock();
}

/**
 * \brief ����д��־�ȼ�
 * \param  level ��־�ȼ�
 **/
void zLogger::setLevel(const std::wstring &level)
{
	if (_T("off") == level) 		setLevel(LEVEL_OFF);
	else if (_T("fatal") == level) 	setLevel(LEVEL_FATAL);
	else if (_T("error") == level) 	setLevel(LEVEL_ERROR);
	else if (_T("warn") == level) 	setLevel(LEVEL_WARN);
	else if (_T("debug") == level) 	setLevel(LEVEL_DEBUG);
	else if (_T("info") == level) 	setLevel(LEVEL_INFO);
	else if (_T("all") == level) 	setLevel(LEVEL_ALL);
	else
	{
		assert(0);
	}
}

void zLogger::logva(const zLevel level, const wchar_t* file, int line,
	const wchar_t * pattern,va_list vp)
{
	if (m_level > level) return;

    std::wstring strDir = Path::GetAppDir();
	CreateDirectoryW((strDir + _T("log")).c_str(),NULL);

	std::wstring strFile(file);
	std::wstring::size_type pos = strFile.find_last_of(_T('\\'));
	if(pos == std::wstring::npos) 
		pos = 0;
	else
		++ pos;

	SYSTEMTIME sysTime;
	GetLocalTime(&sysTime);		
	TCHAR szName[255] = {0};

	msgMut.lock();

	if (!m_file.empty())
	{
		if(m_day != sysTime.wDay)
		{
			if (NULL != fp_file)
				fclose(fp_file);

            m_day = sysTime.wDay;
            if (m_use_day)
            {
                swprintf_s(szName, sizeof(szName)/sizeof(wchar_t), _T("%s%04d%02d%02d.txt"),m_file.c_str(),
                    sysTime.wYear, sysTime.wMonth, sysTime.wDay);
                fp_file = _wfopen(szName,_T("at"));
            } 
            else 
            {
			    fp_file = _wfopen(m_file.c_str(), _T("w+"));
            }
		}
	}

	std::vector<FILE*> v_ptrFile;
	//v_ptrFile.push_back(fp_console);
	v_ptrFile.push_back(fp_file);

	for(std::vector<FILE*>::iterator beg = v_ptrFile.begin();
		beg != v_ptrFile.end(); ++beg)
	{
		if (NULL != *beg)
		{
			fwprintf(*beg,_T("[%s][%ld] "),m_name.c_str(), GetCurrentThreadId());
			fwprintf(*beg, _T("%04d/%02d/%02d "), sysTime.wYear,
				sysTime.wMonth, sysTime.wDay);
			fwprintf(*beg, _T("%02d:%02d:%02d.%03ld "), sysTime.wHour,
				sysTime.wMinute, sysTime.wSecond, sysTime.wMilliseconds);
			fwprintf(*beg,_T("{%s}(%d) "), strFile.substr(pos).c_str(), line);
			fwprintf(*beg, _T("[%s] "), zLogger::getZLevelString(level));
			vfwprintf(*beg, pattern, vp);
			fwprintf(*beg, _T("\n"));
			fflush(*beg);
		}
	}

	msgMut.unlock();
}

/**
 * \brief д��־
 * \param  zLevelPtr ��־�ȼ��μ� #zLogger::zLevel
 * \param  pattern �����ʽ��������printfһ��
 * \return ��
 **/
void zLogger::log(const zLevel level, const wchar_t* file, int line,
	const wchar_t * pattern,...)
{
	va_list vp;

	if (m_level > level) return;
	va_start(vp,pattern);
	logva(level, file, line, pattern, vp);
	va_end(vp);
}

void zLogger::log16(const zLevel level, const wchar_t* file, int line,
	const wchar_t* info, const BYTE* pData, int Datasize)
{	
	if (m_level > level) return;

    std::wstring strDir = Path::GetAppDir();
	CreateDirectoryW((strDir + _T("log")).c_str(),NULL);

	std::wstring strFile(file);
	std::wstring::size_type pos = strFile.find_last_of(_T('\\'));

	if(pos == std::wstring::npos)
		pos = 0;
	else
		++ pos;

	SYSTEMTIME sysTime;
	GetLocalTime(&sysTime);		
	TCHAR szName[255];


	msgMut.lock();

	if (!m_file.empty())
	{
		if(m_day != sysTime.wDay)
		{
			if (NULL != fp_file)
				fclose(fp_file);

            m_day = sysTime.wDay;
            if (m_use_day)
            {
                swprintf_s(szName, sizeof(szName)/sizeof(wchar_t), _T("%s%04d%02d%02d.txt"),m_file.c_str(),
                    sysTime.wYear, sysTime.wMonth, sysTime.wDay);
                fp_file = _wfopen(szName,_T("at"));
            } 
            else 
            {
                fp_file = _wfopen(m_file.c_str(), _T("w+"));
            }
		}
	}

	std::vector<FILE*> v_ptrFile;
	//v_ptrFile.push_back(fp_console);
	v_ptrFile.push_back(fp_file);

	for(std::vector<FILE*>::iterator beg = v_ptrFile.begin();
		beg != v_ptrFile.end(); ++beg)
	{
		if (NULL != *beg)
		{
			fwprintf(*beg,_T("[%s][%ld] "),m_name.c_str(), GetCurrentThreadId());

			fwprintf(*beg, _T("%04d/%02d/%02d "), sysTime.wYear,
				sysTime.wMonth, sysTime.wDay);
			fwprintf(*beg, _T("%02d:%02d:%02d.%03ld "), sysTime.wHour,
				sysTime.wMinute, sysTime.wSecond, sysTime.wMilliseconds);

			fwprintf(*beg,_T("{%s}(%d) "), strFile.substr(pos).c_str(), line);
			fwprintf(*beg, _T("[%s] "), zLogger::getZLevelString(level));
			fwprintf(*beg, _T("%s ���� = %u:\n"),info, Datasize );
			for(int i = 0; i < Datasize; i ++)
				fwprintf(*beg, _T("%2.2X "), pData[i]);
			fwprintf(*beg, _T("\n\n"));
			fflush(*beg);
		}
	}
	msgMut.unlock();

}
