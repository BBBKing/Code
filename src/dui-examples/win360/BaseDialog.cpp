#include "StdAfx.h"
#include "BaseDialog.h"

#include <memory>


//��Ϣͨ��
void BaseDialog::Notify(TNotifyUI& msg)
{
    //����ǵ����Ϣ��ôͨ���ؼ������ж����ĸ��ؼ�
    if (msg.sType == _T("click")) {
        if (msg.pSender == static_cast<CButtonUI*>(m_pm.FindControl(_T("minbtn"))))
            SendMessage(WM_SYSCOMMAND, SC_MINIMIZE, 0);

        if (msg.pSender == static_cast<CButtonUI*>(m_pm.FindControl(_T("closebtn"))))
            PostQuitMessage(0);

        if (msg.pSender == static_cast<CButtonUI*>(m_pm.FindControl(_T("maxbtn"))))
            ::IsZoomed(*this) ? SendMessage(WM_SYSCOMMAND, SC_RESTORE, 0) : SendMessage(WM_SYSCOMMAND, SC_MAXIMIZE, 0);

        if (msg.pSender == static_cast<CButtonUI*>(m_pm.FindControl(_T("check_normal")))) {
            ::MessageBox(NULL, L"��ʼɨ��", L"��ʾ", MB_OK);
        }
    }
}

//����������Ϣѭ���������麯��������Ϣ����
LRESULT BaseDialog::HandleMessage(UINT uMsg, WPARAM wParam, LPARAM lParam)
{
    //��ʼ����Ϣӳ��MAP  ����auto_ptrά��ָ�� static��ֻ֤����һ��
    static std::auto_ptr<MessageMap> customMessageMap(InitMessageMap());
    BOOL bHandled = TRUE;
    LRESULT lRes = 0;

    //����Ϣ����Ϣӳ��map�н��в��� �ҵ���Ӧ����Ϣ������
    if (customMessageMap->find(uMsg) != customMessageMap->end()) {
        //typedef HRESULT (BaseDialog::*CustomMsgHandler)(WPARAM, LPARAM, BOOL&);
        //����ҵ� ������Ӧ����Ϣ��Ӧ����
        CustomMsgHandler handler = (*customMessageMap)[uMsg];
        //ͨ��this->(*handler)������Ϣ��Ӧ�����ĵ���
        lRes = (this->*handler)(wParam, lParam, bHandled);

        //��� bHandled����Trueû�б��޸���ô˵����Ϣ�Ѿ������� ����
        if (bHandled) return lRes;
    }

    //CPaintManagerUI����PaintManagerUI���д��� ��������� ��ô�᷵��True ���򷵻�false������
    if (m_pm.MessageHandler(uMsg, wParam, lParam, lRes)) return lRes;

    //��󶪸�Ĭ�ϵ�windows��Ϣ������
    return CWindowWnd::HandleMessage(uMsg, wParam, lParam);
}

//��ʼ����Ϣѭ����Ӧ����Ϣ��Ӧ����
BaseDialog::MessageMap* BaseDialog::InitMessageMap()
{
    MessageMap* map = new MessageMap;
    (*map)[WM_CREATE] = &BaseDialog::OnCreate;
    (*map)[WM_DESTROY] = &BaseDialog::OnDestory;
    (*map)[WM_ERASEBKGND] = &BaseDialog::OnErasebkgnd;
    (*map)[WM_SIZE] = &BaseDialog::OnSize;
    (*map)[WM_NCPAINT] = &BaseDialog::OnNcPaint;
    //����������Ϣ��������ϵͳ������
    (*map)[WM_NCACTIVATE] = &BaseDialog::OnNcActive;
    (*map)[WM_NCCALCSIZE] = &BaseDialog::OnNcCalSize;
    (*map)[WM_NCHITTEST] = &BaseDialog::OnNcHitTest;
    (*map)[WM_SYSCOMMAND] = &BaseDialog::OnSysCommand;
    (*map)[WM_GETMINMAXINFO] = &BaseDialog::OnGetMinMaxInfo;
    return map;
}

//���ڴ���ʱ��
HRESULT BaseDialog::OnCreate(WPARAM wParam, LPARAM lParam, BOOL& bHandled)
{
    //��ȡ��ǰ���ڷ��
    LONG styleValue = ::GetWindowLong(*this, GWL_STYLE);
    styleValue &= ~WS_CAPTION;
    //����STYLE
    ::SetWindowLong(*this, GWL_STYLE, styleValue | WS_CLIPSIBLINGS | WS_CLIPCHILDREN);
    //��ʼ��������Ⱦ��
    m_pm.Init(m_hWnd);
    //D
    CDialogBuilder builder;
    //ͨ��xml �Լ���Ⱦ����Ⱦ����UI
    CControlUI* pRoot = builder.Create(_T("main_dlg.xml"), (UINT)0, NULL, &m_pm);
    //���ӽ���UI���Ի�������
    m_pm.AttachDialog(pRoot);
    //������Ϣ����  ��Ϊʵ���� INotifyUI�ӿ�
    m_pm.AddNotifier(this);
    return 0;
}


HRESULT BaseDialog::OnDestory(WPARAM wParam, LPARAM lParam, BOOL& bHandled)
{
    //�����˳���Ϣ
    ::PostQuitMessage(0L);
    return 0;
}

//��������
HRESULT BaseDialog::OnErasebkgnd(WPARAM wParam, LPARAM lParam, BOOL& bHandled)
{
    return 1;
}

//�����ڵĳߴ緢���ı��ʱ��
HRESULT BaseDialog::OnSize(WPARAM wParam, LPARAM lParam, BOOL& bHandled)
{
    //�ڴ��ڴ�С�ı��ʱ������Բ��
    SIZE szRoundCorner = m_pm.GetRoundCorner();

    if (!::IsIconic(*this) && (szRoundCorner.cx != 0 || szRoundCorner.cy != 0)) {
        CDuiRect rcWnd;
        ::GetWindowRect(*this, &rcWnd);
        rcWnd.Offset(-rcWnd.left, -rcWnd.top);
        rcWnd.right++;
        rcWnd.bottom++;
        HRGN hRgn = ::CreateRoundRectRgn(rcWnd.left, rcWnd.top, rcWnd.right,
                                         rcWnd.bottom, szRoundCorner.cx, szRoundCorner.cy);
        ::SetWindowRgn(*this, hRgn, TRUE);
        ::DeleteObject(hRgn);
        return 0;
    }

    bHandled = FALSE;
    return 0;
}

HRESULT BaseDialog::OnNcPaint(WPARAM wParam, LPARAM lParam, BOOL& bHandled)
{
    return 0;
}

HRESULT BaseDialog::OnNcActive(WPARAM wParam, LPARAM lParam, BOOL& bHandled)
{
    if (::IsIconic(*this)) bHandled = FALSE;

    return (wParam == 0) ? TRUE : FALSE;
}


//�����������ô�ͻᵼ��DUILIB ��ͣ����ϵͳ��Ϣ���д���
// ����ϵͳ������ �ƺ�������һ���������
HRESULT BaseDialog::OnNcCalSize(WPARAM wParam, LPARAM lParam, BOOL& bHandled)
{
    return 0;
}

HRESULT BaseDialog::OnNcHitTest(WPARAM wParam, LPARAM lParam, BOOL& bHandled)
{
    //��ȡ�ͻ����������
    POINT pt;
    pt.x = GET_X_LPARAM(lParam);
    pt.y = GET_Y_LPARAM(lParam);
    ::ScreenToClient(*this, &pt);
    //��ȡ�ͻ�����
    RECT rcClient;
    ::GetClientRect(*this, &rcClient);

    //�������û�����
    if (!::IsZoomed(*this)) {
        //��ȡ�ǿͻ�����sizebox
        RECT rcSizeBox = m_pm.GetSizeBox();

        //���y<��������top+sizebox.top ���Ϸǿͻ���
        if (pt.y < rcClient.top + rcSizeBox.top) {
            //�ж��Ƿ������ϱ�
            if (pt.x < rcClient.left + rcSizeBox.left) return HTTOPLEFT;

            //�ж��Ƿ������ϱ�
            if (pt.x > rcClient.right - rcSizeBox.right) return HTTOPRIGHT;

            //���ض��˲���
            return HTTOP;
        }
        //������bottom
        else if (pt.y > rcClient.bottom - rcSizeBox.bottom) {
            //����
            if (pt.x < rcClient.left + rcSizeBox.left) return HTBOTTOMLEFT;

            //����
            if (pt.x > rcClient.right - rcSizeBox.right) return HTBOTTOMRIGHT;

            //Ĭ���±�
            return HTBOTTOM;
        }

        //������� top ����bottom ��ô��������� �ұߵķǿͻ���
        if (pt.x < rcClient.left + rcSizeBox.left) return HTLEFT;

        if (pt.x > rcClient.right - rcSizeBox.right) return HTRIGHT;
    }

    //��ȡ�������ľ�������
    //�����ж�����Ƿ��ڸ������� ����ڷ���
    RECT rcCaption = m_pm.GetCaptionRect();

    if (pt.x >= rcClient.left + rcCaption.left
        && pt.x < rcClient.right - rcCaption.right
        && pt.y >= rcCaption.top
        && pt.y < rcCaption.bottom) {
        //ButtonUI OptionUI ֻ�����������͵���������
        CControlUI* pControl = static_cast<CControlUI*>(m_pm.FindControl(pt));

        if (pControl
            && _tcscmp(pControl->GetClass(), _T("ButtonUI")) != 0
            && _tcscmp(pControl->GetClass(), _T("OptionUI")) != 0) {
            return HTCAPTION;
        }
    }

    //���ಿ���ǿͻ���
    return HTCLIENT;
}


//ϵͳ�����
LRESULT BaseDialog::OnSysCommand(WPARAM wParam, LPARAM lParam, BOOL& bHandled)
{
    if (wParam == SC_CLOSE) {
        ::PostQuitMessage(0L);
        bHandled = TRUE;
        return 0;
    }

    BOOL bZoomed = ::IsZoomed(*this);
    LRESULT lRes = CWindowWnd::HandleMessage(WM_SYSCOMMAND, wParam, lParam);
    return 1L;
}

LRESULT BaseDialog::OnGetMinMaxInfo(WPARAM wParam, LPARAM lParam, BOOL& bHandled)
{
    MONITORINFO oMonitor = {};
    oMonitor.cbSize = sizeof(oMonitor);
    ::GetMonitorInfo(::MonitorFromWindow(*this, MONITOR_DEFAULTTOPRIMARY), &oMonitor);
    CDuiRect rcWork = oMonitor.rcWork;
    rcWork.Offset(-rcWork.left, -rcWork.top);
    /// �������ʱ�ü���Ӱ��ռ����
    LPMINMAXINFO lpMMI = (LPMINMAXINFO) lParam;
    lpMMI->ptMaxPosition.x  = rcWork.left - 5;
    lpMMI->ptMaxPosition.y  = rcWork.top - 3;
    lpMMI->ptMaxSize.x      = rcWork.right + 10;
    lpMMI->ptMaxSize.y      = rcWork.bottom + 10;
    bHandled = FALSE;
    return 0;
}