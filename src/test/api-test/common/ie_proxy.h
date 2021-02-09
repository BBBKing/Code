#ifndef ie_proxy_h__
#define ie_proxy_h__

#include <string>
#include <windows.h>
#include <Winhttp.h>



namespace cactus
{
typedef enum E_proxy_type {
    eProxyType_all = 0,
    eProxyType_http,
    eProxyType_https,
    eProxyType_ftp,
    eProxyType_socks,
};

class CIEProxy
{
public:
    std::wstring GetIEProxy(const std::wstring& strHostName, const E_proxy_type& eProxyType);

private:
    /**
    @brief ��������ȷ���Ƿ�ʹ��proxy
    */
    BOOL CheckByPass(const std::wstring& strHostName, const std::wstring& strPassBy);
    /**
    @brief �Ӷ��proxy���л�ȡĳ��proxy��
    */
    std::wstring GetProxyFromString(const E_proxy_type& eProxyType, const std::wstring& strProxys);
};
}

#endif // ie_proxy_h__
