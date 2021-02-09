#ifndef __CACTUS_CACTUS_WMI_H__
#define __CACTUS_CACTUS_WMI_H__

#include <Windows.h>
#include <comdef.h>
#include <wbemidl.h>
#include <string>
#include <atlstr.h>

namespace cactus
{
class CWmiUtilities
{
public:
    CWmiUtilities();
    virtual ~CWmiUtilities();

private:
    //���ÿ�������
    CWmiUtilities(CWmiUtilities& objWmiUtilities);
    //���á�=����
    CWmiUtilities& operator=(CWmiUtilities& objWmiUtilities);

private:
    BOOL PutInstance();

public:
    //���ӵ�WMI
    BOOL ConnectWmi(const wchar_t* csWmiNameSpace);

    //ִ��WQL���
    BOOL ExecQuery(const wchar_t* csWQL);

    BOOL BeginEnumClassObject(const wchar_t* className);

    //ö����һ��IWbemClassObjectʵ��,��һ�ε��õõ���һ��ʵ��
    BOOL Next();

    //����ö����һ��IWbemClassObjectʵ��,��Next()��ͬ���չ��Լ���RecordSet��̾���
    //һ������ֻ����һ��ʵ����¼�����
    BOOL IsEof();


    template <typename T>
    T GetInt(std::wstring item)
    {
        VARIANT prop;
        VariantInit(&prop);
        pls_->Get(bstr_t(item.c_str()), 0, &prop, 0, 0);
        T value = prop.intVal;
        VariantClear(&prop);
        return value;
    }

    template <typename T>
    T GetUInt(std::wstring item)
    {
        VARIANT prop;
        VariantInit(&prop);
        pls_->Get(bstr_t(item.c_str()), 0, &prop, 0, 0);
        T value = prop.uintVal;
        VariantClear(&prop);
        return value;
    }


	HRESULT GetValue(const wchar_t* name, CComVariant* value);
	HRESULT GetValue(const wchar_t* name, CString* value);
	HRESULT GetValue(const wchar_t* name, bool* value);
	HRESULT GetValue(const wchar_t* name, int* value);
	HRESULT GetValue(const wchar_t* name, UINT32* value);


    std::wstring GetString(std::wstring);

    //��WMIʵ�������û��ȡһ��string����
    BOOL GetStringProperty(const wchar_t* csName, std::wstring& csValue);
    BOOL PutStringProperty(const wchar_t* csName, const wchar_t* csValue);

    //��WMIʵ�������û��ȡһ��uint32����
    BOOL GetUINT32Property(const wchar_t* csName, UINT32& uInt32Value);
    BOOL PutUINT32Property(const wchar_t* csName, UINT32 uInt32Value);

    //��WMIʵ�������û��ȡһ��boolean����
    BOOL GetBOOLProperty(const wchar_t* csName, BOOL& bValue);
    BOOL PutBOOLProperty(const wchar_t* csName, BOOL bValue);

private:
    HRESULT _hResult;
    IWbemLocator* loc_;
    IWbemServices* svc_;
    IEnumWbemClassObject* pEnum_;
    IWbemClassObject* pls_;

};
} // namespace cactus

#endif // __CACTUS_CACTUS_WMI_H__
