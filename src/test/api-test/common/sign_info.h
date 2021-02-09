#ifndef sign_info_h__
#define sign_info_h__

/**
 * @file
 * @brief ����ǩ����Ϣ��ȡ
 * @see http://support.microsoft.com/kb/323809/zh-cn
 */


#include <Windows.h>
#include <wincrypt.h>
#include <wintrust.h>
#include <atlstr.h>

namespace cactus
{


/**
 * @brief ����ǩ����Ϣ��ȡ�ӿ�
 */
class ZLSignInfo
{
public:
    BOOL Load(LPCTSTR lpFilePath);

    ///> ǩ����
    CString GetNameOfSigner() const;
    ///> �䷢��
    CString GetNameOfIssuer() const;
    ///> ǩ��ʱ��
    SYSTEMTIME GetSigningTime() const;
    ///> ֤�����к�
    CString GetSerialNumber() const;

    ///> �ж�ǩ���Ƿ���ʱ���(��ʱ�����ָ��������)
    static BOOL IsDigitalSignatureHasTimestamp(LPCWSTR lpFilePath, WORD wMinYear = 2000, WORD wMaxYear = 2100);

private:
    void _Clear();
    static void              _GetFileSignerHandle(LPCTSTR lpFilePath, HCRYPTMSG& hCryptMsg, HCERTSTORE& hCertStore);
    static PCMSG_SIGNER_INFO _GetMsgSignerInfoOfFile(HCRYPTMSG hCryptMsg);
    static PCMSG_SIGNER_INFO _GetMsgSignerInfoOfTimestamp(PCMSG_SIGNER_INFO pMsgSignerInfoOfFile);
    static SYSTEMTIME        _ReadSigningTime(PCMSG_SIGNER_INFO pFileSignerInfo);
    static CString           _ReadSerialNumber(PCCERT_CONTEXT pCertContext);
    static CString           _ReadSignerName(PCCERT_CONTEXT pCertContext);
    static CString           _ReadIssuerName(PCCERT_CONTEXT pCertContext);
    static CString           _SimpleCertContextReader(PCCERT_CONTEXT pCertContext, DWORD dwType, DWORD dwFlags);
    static void              _ReleaseMsgSignerInfoPtr(PCMSG_SIGNER_INFO p);
    static PCCERT_CONTEXT    _ReadCertInfo(HCERTSTORE hCertStore, const PCMSG_SIGNER_INFO pMsgSignerInfoOfFile);

private:
    CString     m_sSignerName;    // ʹ����
    CString     m_sIssuerName;    // �䷢��
    SYSTEMTIME  m_tSigningTime;   // ǩ��ʱ��
    CString     m_sSerialNumber;  // ֤�����к�
};

// ������ʵ�ֲ���


} // end of namespace zl


#endif // sign_info_h__
