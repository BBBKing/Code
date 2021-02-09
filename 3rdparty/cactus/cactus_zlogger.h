#ifndef _Z_LOGGER_H_
#define _Z_LOGGER_H_

#include <cactus/cactus.h>
#include <cactus/cactus_types.h>
#include <iostream>
#include <boost/thread/mutex.hpp>

typedef unsigned char BYTE;
//	static const char *LEVEL_STRING[] = {
//		"LEVEL_OFF",
//		"LEVEL_FATAL",
//		"LEVEL_ERROR",
//		"LEVEL_WARN",
//		"LEVEL_DEBUG",
//		"LEVEL_INFO",
//		"LEVLE_ALL"
//	};
/**
 * \brief Zebra��Ŀ����־�ࡣ
 * Ŀǰʵ��������д��־��ʽ��������̨�������ļ���
 * Ĭ����־������#DEBUG
 * ����Ϊ�̰߳�ȫ�ࡣ
 **/
class CACTUS_API zLogger
{
public:
	/**
 	 * \brief zLevel�����˼�����־�ȼ�
 	 * ������log4cxx�ṩ�ı�׼��־�ȼ���Ϊ��־�ȼ��⣬���Զ�������Ϸ��־�ȼ�.
 	 * ������־�ȼ���ϵΪ #OFF> #FATAL> #ERROR> #WARN> #DEBUG> #INFO> #ALL
 	 **/

	/**
 	 * \brief Zebra��Ŀ��֧����־�ȼ����ֶ���
 	 **/
	typedef enum
	{
		/**
 		 * \brief ��zLogger�ȼ�����ΪOFF�����򲻻�����κ���־
 		 **/
		LEVEL_OFF   = INT_MAX,

		/**
 		 * \brief ��zLogger�ȼ�����ΪFATAL��ֻ���FATAL�ȼ�����־
 		 * �������������Ѿ��޷��ṩ�����ķ����ܡ�
 		 **/
		LEVEL_FATAL = 50000,

		/**
 		 * \brief ��zLogger�ȼ�����ΪERROR��ֻ������ڵ��ڴ˵ȼ�����־
 		 * ���󣬿��ܲ����ṩĳ�ַ��񣬵����Ա�֤������ȷ���С�
 		 **/
		LEVEL_ERROR = 40000,

		/**
 		 * \brief ��zLogger�ȼ�����ΪWARN��ֻ������ڵ��ڴ˵ȼ�����־
 		 * ���棬ĳЩ�ط���Ҫ����ע�⣬����û�������ļ�����������Ĭ��ѡ�����ʹ�á�
 		 **/
		LEVEL_WARN  = 30000,

		/**
 		 * \brief ��zLogger�ȼ�����ΪDEBUG��������еȼ�����־
 		 **/
		LEVEL_DEBUG = 20000,

		/**
 		 * \brief ��zLogger�ȼ�����ΪINFO��ֻ������ڵ��ڴ˵ȼ�����־
 		 * ��Ϣ���ṩһ����Ϣ��¼��������һЩ����״̬�ļ�¼��
 		 **/
		LEVEL_INFO  = 10000,

		/**
 		 * \brief ��zLogger�ȼ�����ΪALL��������еȼ�����־
 		 **/
		LEVEL_ALL   = INT_MIN
	}zLevel;

	const wchar_t *getZLevelString(zLevel level)
	{
		switch(level)
		{
		case LEVEL_OFF:
			return _T("OFF");
		case LEVEL_FATAL:
			return _T("FATAL");
		case LEVEL_ERROR:
			return _T("ERROR");
		case LEVEL_WARN:
			return _T("WARN");
		case LEVEL_DEBUG:
			return _T("DEBUG");
		case LEVEL_INFO:
			return _T("INFO");
		case LEVEL_ALL:
			return _T("ALL");
		default:
			return _T("NO_LEVEL");
		}
	}
	zLogger(wchar_t *name = _T("Zebra") ,const wchar_t *file = _T("log"));
	~zLogger();

	void removeConsoleLog();
	void addLocalFileLog(const std::wstring &file);

    void setLogPath(const std::wstring &file);

	void setLevel(const zLevel level);
	void setLevel(const std::wstring &level);

	void logva(const zLevel level, const wchar_t* file, int line,
		const wchar_t * pattern,va_list vp);
	void log(const zLevel level, const wchar_t* file, int line, 
		const wchar_t * pattern, ...);
	void log16(const zLevel level, const wchar_t* file, int line, 
		const wchar_t* info, const BYTE* pData, int Datasize);

private:
	boost::mutex	msgMut;

	zLevel      	m_level;
	FILE*			fp_console;
	FILE*			fp_file;
	int         	m_day;
	std::wstring 	m_name;
	std::wstring 	m_file;
    bool            m_use_day;
};

namespace Zebra
{
	/**
 	 * \brief ��־ָ��
 	 **/
	extern zLogger CACTUS_API *logger;
};

#define ZLOG_FATAL(format, ...) \
Zebra::logger->log(zLogger::LEVEL_FATAL, _T(__FILE__), __LINE__, format, ##__VA_ARGS__)

#define ZLOG_ERROR(format, ...) \
Zebra::logger->log(zLogger::LEVEL_ERROR,  _T(__FILE__), __LINE__, format, ##__VA_ARGS__)

#define ZLOG_WARN(format, ...) \
Zebra::logger->log(zLogger::LEVEL_WARN,   _T(__FILE__), __LINE__, format, ##__VA_ARGS__)

#define ZLOG_DEBUG(format, ...) \
Zebra::logger->log(zLogger::LEVEL_DEBUG,  _T(__FILE__), __LINE__, format, ##__VA_ARGS__)

#define ZLOG_INFO(format, ...) \
Zebra::logger->log(zLogger::LEVEL_INFO,   _T(__FILE__), __LINE__, format, ##__VA_ARGS__)

#define ZLOG_DEBUG16(info, pData, Datasize) \
Zebra::logger->log16(zLogger::LEVEL_DEBUG,  _T(__FILE__), __LINE__, info, pData, Datasize)


#endif // _Z_LOGGER_H_
