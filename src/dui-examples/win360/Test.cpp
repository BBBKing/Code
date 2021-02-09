
#include "stdafx.h"
#include "Test.h"
#include "BaseDialog.h"

using namespace DuiLib;

int APIENTRY _tWinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPTSTR lpCmdLine, int nCmdShow)
{
    //���ý���ʵ�����
    CPaintManagerUI::SetInstance(hInstance);
    //������Դ·��
    CPaintManagerUI::SetResourcePath(CPaintManagerUI::GetInstancePath() + L"\\Skin5");
    //����ZIPѹ����Դ Ĭ���ǵ�ǰ·����
    //�о�����Դ�м���Ƥ���ļ�
    //CPaintManagerUI::SetResourceZip(_T("skin.zip"));
    //��ʼ��COM
    HRESULT Hr = ::CoInitialize(NULL);

    if (FAILED(Hr)) return 0;

    //����һ���Ի���������� ������Ⱦ����
    BaseDialog* pFrame = new BaseDialog();

    //ʧ�ܷ���
    if (pFrame == NULL) return 0;

    //����һ��3D�߿� ���������ɼ��Ķ��㴰�� WS_OVERLAPPEDWINDOW
    pFrame->Create(NULL, _T("T9000"), UI_WNDSTYLE_FRAME, WS_EX_STATICEDGE | WS_EX_APPWINDOW);
    //����CENTER
    pFrame->CenterWindow();
    //��ʾ��ʾ����
    pFrame->ShowWindow(true);
    //��ʼ��Ϣѭ��
    CPaintManagerUI::MessageLoop();
    //�ͷ�COM
    ::CoUninitialize();
    return 0;
}
