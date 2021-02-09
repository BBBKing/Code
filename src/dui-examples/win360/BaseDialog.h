#ifndef BaseDialog_H
#define BaseDialog_H

#include "UIlib.h"

#include <map>
using namespace DuiLib;

//�̳���CWindowWnd  INotifyUI
//ӵ�д������ںͽ��ܴ����¼�֪ͨ������
class BaseDialog : public CWindowWnd, public INotifyUI
{

public:
    BaseDialog() {};
protected:
    //�麯�� �������ô��ڵ�CLASS NAME
    virtual LPCTSTR GetWindowClassName() const
    {
        return _T("USHER TEST DLG");
    }
    //����ʱ��ͨ����Ϣ�ص�
    virtual void Notify(TNotifyUI& msg);
    //����
    virtual LRESULT HandleMessage(UINT uMsg, WPARAM wParam, LPARAM lParam);
    // �Զ�����Ϣӳ��
    typedef HRESULT(BaseDialog::*CustomMsgHandler)(WPARAM, LPARAM, BOOL&);
    typedef std::map<UINT, CustomMsgHandler> MessageMap;
    virtual MessageMap* InitMessageMap();
    // �Զ�����Ϣ���� �ڴ��ڴ�����ʱ��
    HRESULT OnCreate(WPARAM wParam, LPARAM lParam, BOOL& bHandled);
    //�ڴ������ٵ�ʱ��
    HRESULT OnDestory(WPARAM wParam, LPARAM lParam, BOOL& bHandled);
    //�������ڱ���
    HRESULT OnErasebkgnd(WPARAM wParam, LPARAM lParam, BOOL& bHandled);
    //�ߴ�ı��ʱ��
    HRESULT OnSize(WPARAM wParam, LPARAM lParam, BOOL& bHandled);
    //�ǿͻ����ػ�
    HRESULT OnNcPaint(WPARAM wParam, LPARAM lParam, BOOL& bHandled);
    //�ǿͻ�������
    HRESULT OnNcActive(WPARAM wParam, LPARAM lParam, BOOL& bHandled);
    //�ǿͻ��������С
    HRESULT OnNcCalSize(WPARAM wParam, LPARAM lParam, BOOL& bHandled);
    //�ǿͻ����������
    HRESULT OnNcHitTest(WPARAM wParam, LPARAM lParam, BOOL& bHandled);
    //ϵͳ�����
    LRESULT OnSysCommand(WPARAM wParam, LPARAM lParam, BOOL& bHandled);
    //�����С����Ϣ
    LRESULT OnGetMinMaxInfo(WPARAM wParam, LPARAM lParam, BOOL& bHandled);

private:
    CPaintManagerUI m_pm;
};
#endif // BaseDialog_H