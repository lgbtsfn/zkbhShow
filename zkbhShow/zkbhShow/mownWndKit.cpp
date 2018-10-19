#include "stdafx.h"
#include "MownWndKit.h"


CMownWndKit::CMownWndKit() : m_pOwner(NULL), m_bInit(false)
{
	m_bfocus = false;
}

CMownWndKit::~CMownWndKit()
{

}

void CMownWndKit::Init(CMownWndKitUI* pOwner)
{
	m_pOwner = pOwner;
	m_bInit = true;
	if (m_hWnd == NULL)
	{
		RECT rcPos = m_pOwner->GetPos();
		UINT uStyle = UI_WNDSTYLE_CHILD|WS_BORDER ;

		Create(m_pOwner->GetManager()->GetPaintWindow(), NULL, uStyle, 0, rcPos);
	}
}


LPCTSTR CMownWndKit::GetWindowClassName() const
{
	return _T("WkeWebkit");
}

void CMownWndKit::OnFinalMessage(HWND /*hWnd*/)
{
	m_pOwner->Invalidate();
	m_pOwner->m_pWindow = NULL;
	delete this;
}

 LRESULT CMownWndKit::OnDestroy(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled)
 {
 	KillTimer(m_hWnd, DEFAULT_TIMERID);
 	bHandled = TRUE;
 	return 0;
 }
 
 LRESULT CMownWndKit::OnPaint(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled)
 {
 	PAINTSTRUCT ps = { 0 };
 	HDC hDcPaint = ::BeginPaint(m_hWnd, &ps);
 
 	RECT rcClip;	
 	::GetClipBox(hDcPaint,&rcClip);	
 
 	RECT rcClient;
 	::GetClientRect(m_hWnd, &rcClient);
 	
 	RECT rcInvalid;
 	::IntersectRect(&rcInvalid, &rcClip,&rcClient);
         

	HBRUSH hBrush = ::CreateSolidBrush(RGB(255,255,255));
	::FillRect(hDcPaint, &rcInvalid, hBrush);
	::DeleteObject(hBrush);
	if (m_bfocus)
	{
		HBRUSH hBrushred = ::CreateSolidBrush(RGB(255,0,0));
		::FrameRect(hDcPaint,&rcInvalid,hBrushred);       	
		::DeleteObject(hBrushred);
	}
	
 	::EndPaint(m_hWnd, &ps);
 	return 0;
 }
 
 
 
 
 LRESULT CMownWndKit::OnCreate(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled)
 {
 
 	m_pOwner->GetManager()->AddNativeWindow(m_pOwner, m_hWnd);
 	if( m_pOwner->GetManager()->IsLayered() ) {
 		::SetTimer(m_hWnd, DEFAULT_TIMERID, ::GetCaretBlinkTime(), NULL);
 	}
 	bHandled = FALSE;
 
 	return 0;
 }
 
 LRESULT CMownWndKit::OnSize(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled)
 {
 	CDuiRect rcWnd;
 	::GetWindowRect(*this, &rcWnd);
 
  	
 	::InvalidateRect(m_hWnd, NULL, FALSE);
 	return 0;
 }
 
 LRESULT CMownWndKit::OnMouseEvent(UINT uMsg, WPARAM wParam,LPARAM lParam, BOOL& bHandled)
 {
 	if (uMsg == WM_LBUTTONDOWN || uMsg == WM_MBUTTONDOWN || uMsg == WM_RBUTTONDOWN)
 	{
 		SetFocus(m_hWnd);
 		SetCapture(m_hWnd);
 	}
 	else if (uMsg == WM_LBUTTONUP || uMsg == WM_MBUTTONUP || uMsg == WM_RBUTTONUP)
 	{
 		ReleaseCapture();
 	}
 
 	RECT rcClient;
 	GetClientRect(m_hWnd, &rcClient);
 
 	int x = GET_X_LPARAM(lParam)-rcClient.left;
 	int y = GET_Y_LPARAM(lParam)-rcClient.top;
 
 	unsigned int flags = 0;
 

 	return 0;
 }
 
 LRESULT CMownWndKit::OnMouseWheel(UINT uMsg, WPARAM wParam,LPARAM lParam, BOOL& bHandled)
 {
 	POINT pt;
 	pt.x = GET_X_LPARAM(lParam);
 	pt.y = GET_Y_LPARAM(lParam);
 	ScreenToClient(m_hWnd, &pt);
 
 	int delta = GET_WHEEL_DELTA_WPARAM(wParam);
 
 	unsigned int flags = 0;
 

 	return 0;
 }
 
 LRESULT CMownWndKit::OnKeyDown(UINT uMsg, WPARAM wParam,LPARAM lParam, BOOL& bHandled)
 {
 	unsigned int flags = 0;

 	return 0;
 }
 LRESULT CMownWndKit::OnKeyUp(UINT uMsg, WPARAM wParam,LPARAM lParam, BOOL& bHandled)
 {
 	unsigned int flags = 0;

 	return 0;
 }
 
 LRESULT CMownWndKit::OnChar(UINT uMsg, WPARAM wParam,LPARAM lParam, BOOL& bHandled)
 {
 	unsigned int charCode = wParam;
 	unsigned int flags = 0;

 	return 0;
 }
 
 LRESULT CMownWndKit::OnImeStartComposition(UINT uMsg, WPARAM wParam,LPARAM lParam, BOOL& bHandled)
 {
 	
 	return 0;
 }
 
 LRESULT CMownWndKit::OnSetFocus(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled)
  {
	 PAINTSTRUCT ps = { 0 };
	 HDC hDcPaint = ::BeginPaint(m_hWnd, &ps);

	 RECT rcClient;
	 ::GetClientRect(m_hWnd, &rcClient);

	 InvalidateRect(m_hWnd,&rcClient,TRUE);
	 m_bfocus = true;
	 if (m_bfocus)
	 {
		 HBRUSH hBrushred = ::CreateSolidBrush(RGB(255,0,0));
		 ::FrameRect(hDcPaint,&rcClient,hBrushred);       	
		 ::DeleteObject(hBrushred);
	 }

	 ::EndPaint(m_hWnd, &ps);

 	bHandled = TRUE;
 	return 0;
 }
 
 LRESULT CMownWndKit::OnKillFocus(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled)
 {

	 PAINTSTRUCT ps = { 0 };
	 HDC hDcPaint = ::BeginPaint(m_hWnd, &ps);

	 RECT rcClient;
	 ::GetClientRect(m_hWnd, &rcClient);

	 InvalidateRect(m_hWnd,&rcClient,TRUE);
	 m_bfocus = false;
	// if (m_bfocus)
	 {
		 HBRUSH hBrushred = ::CreateSolidBrush(RGB(255,255,255));
		 ::FrameRect(hDcPaint,&rcClient,hBrushred);       	
		 ::DeleteObject(hBrushred);
	 }

	 ::EndPaint(m_hWnd, &ps);
 	return 0;
 }
 
 LRESULT CMownWndKit::OnContextMenu(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled)
 {
 	POINT pt;
 	pt.x = GET_X_LPARAM(lParam);
 	pt.y = GET_Y_LPARAM(lParam);
 
 	if (pt.x != -1 && pt.y != -1)
 		ScreenToClient(m_hWnd, &pt);
 
 	unsigned int flags = 0;
 
 	return 0;
 }
 
 LRESULT CMownWndKit::OnTimer(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled)
 {
 	if (wParam == DEFAULT_TIMERID) {
 		RECT rcClient;
 		::GetClientRect(m_hWnd, &rcClient);
 		::InvalidateRect(m_hWnd, &rcClient, FALSE);
 		return 0;
 	}
 	bHandled = FALSE;
 	return 0;
 }

LRESULT CMownWndKit::HandleMessage(UINT uMsg, WPARAM wParam, LPARAM lParam)
{
 	LRESULT lRes = 0;
 	BOOL bHandled = TRUE;
 	switch (uMsg)
 	{
 	case WM_PAINT:			lRes = OnPaint(uMsg, wParam, lParam, bHandled); break;
 	case WM_CREATE:			lRes = OnCreate(uMsg, wParam, lParam, bHandled); break;
 	case WM_DESTROY:		lRes = OnDestroy(uMsg, wParam, lParam, bHandled); break;
 	case WM_MOUSEWHEEL:		lRes = OnMouseWheel(uMsg, wParam, lParam, bHandled); break;
 	case WM_SIZE:			lRes = OnSize(uMsg, wParam, lParam, bHandled); break;
 	case WM_CHAR:			lRes = OnChar(uMsg, wParam, lParam, bHandled); break;
 	case WM_KEYDOWN:		lRes = OnKeyDown(uMsg, wParam, lParam, bHandled); break;
 	case WM_KEYUP:			lRes = OnKeyUp(uMsg, wParam, lParam, bHandled); break;
 	case WM_KILLFOCUS:		lRes = OnKillFocus(uMsg, wParam, lParam, bHandled); break;
 	case WM_SETFOCUS:		lRes = OnSetFocus(uMsg, wParam, lParam, bHandled); break;
 	case WM_TIMER:			lRes = OnTimer(uMsg, wParam, lParam, bHandled); break;
 	case WM_IME_STARTCOMPOSITION: lRes = OnImeStartComposition(uMsg, wParam, lParam, bHandled); break;	
 	case WM_CONTEXTMENU:	lRes= OnContextMenu(uMsg, wParam, lParam, bHandled); break;	
 	case WM_LBUTTONDOWN:	lRes = OnLBttonDown(uMsg, wParam, lParam, bHandled); break;
 	case WM_LBUTTONDBLCLK:  lRes = OnDBLClick(uMsg, wParam, lParam, bHandled); break;
	case WM_RBUTTONDOWN:	lRes = OnRBttonDown(uMsg, wParam, lParam, bHandled); break;
	case WM_MBUTTONDOWN:
 	case WM_LBUTTONUP:
 	
 	case WM_MBUTTONUP:
 	case WM_RBUTTONUP:
	case WM_MBUTTONDBLCLK:
	case WM_RBUTTONDBLCLK:
	case WM_MOUSEMOVE:
	case WM_MOUSELEAVE:
 		lRes = OnMouseEvent(uMsg, wParam, lParam, bHandled); break;
 	default:				bHandled = FALSE; break;
 	}
 	if (bHandled) return lRes;

	return CWindowWnd::HandleMessage(uMsg, wParam, lParam);
}

LRESULT CMownWndKit::OnRBttonDown(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled)
{
	::SetFocus(m_hWnd);
	CControlUI*pControl = m_pOwner->m_pManager->GetNativeWindowControl(m_hWnd);

	if( pControl == NULL ) return 0;
	if( pControl->GetManager() != m_pOwner->GetManager() ) return 0;

	POINT pt = { GET_X_LPARAM(lParam), GET_Y_LPARAM(lParam) };

	TEventUI event = { 0 };
	event.Type = UIEVENT_RBUTTONDOWN;
	event.pSender = pControl;
	event.ptMouse = pt;
	event.wKeyState = (WORD)wParam;
	event.dwTimestamp = ::GetTickCount();
	pControl->Event(event);
	bHandled = TRUE;
	return 0;
}

LRESULT CMownWndKit::OnLBttonDown(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled)
{
	::SetFocus(m_hWnd);
//	m_pOwner->SetBkColor(0xffFF0000);
	CControlUI*pControl = m_pOwner->m_pManager->GetNativeWindowControl(m_hWnd);

	if( pControl == NULL ) return 0;
	if( pControl->GetManager() != m_pOwner->GetManager() ) return 0;

	POINT pt = { GET_X_LPARAM(lParam), GET_Y_LPARAM(lParam) };

	TEventUI event = { 0 };
	event.Type = UIEVENT_BUTTONDOWN;
	event.pSender = pControl;
	event.ptMouse = pt;
	event.wKeyState = (WORD)wParam;
	event.dwTimestamp = ::GetTickCount();
	pControl->Event(event);
	bHandled = TRUE;
	return 0;
}

LRESULT CMownWndKit::OnDBLClick(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled)
{
	::SetFocus(m_hWnd);
	CControlUI*pControl = m_pOwner->m_pManager->GetNativeWindowControl(m_hWnd);

	if( pControl == NULL ) return 0;
	if( pControl->GetManager() != m_pOwner->GetManager() ) return 0;

	POINT pt = { GET_X_LPARAM(lParam), GET_Y_LPARAM(lParam) };

	bHandled = TRUE;
	return 0;
}

///////////////////////////////////////////////////////////////////////////////
//////////////
//////////////

CMownWndKitUI::CMownWndKitUI(void):
m_pWindow(NULL)
{
	m_playflg=false;
	m_cnt = 1;
	m_showStatus = SHOW_STATUS2;
}


CMownWndKitUI::~CMownWndKitUI(void)
{	
	if (m_pWindow != NULL)
	{
		m_pWindow->Close();
	}
}


void CMownWndKitUI::SetVisible(bool bVisible)
{
	CControlUI::SetVisible(bVisible);
	SetInternVisible(bVisible);
}

void CMownWndKitUI::SetInternVisible(bool bVisible)
{
	CControlUI::SetInternVisible(bVisible);
	if (m_pWindow != NULL)
		::ShowWindow(m_pWindow->GetHWND(), bVisible?SW_SHOW:SW_HIDE); 
}

void CMownWndKitUI::DoInit()
{
	m_pWindow = new CMownWndKit();
	if(m_pWindow)
	{
		m_pWindow->Init(this);
		m_pWindow->ShowWindow();
	}	
	Invalidate();
//	SetBkColor(0xFF1C86EE);
}

LPCTSTR CMownWndKitUI::GetClass() const
{
	return _T("MownWndKitUI");
}

LPVOID CMownWndKitUI::GetInterface(LPCTSTR pstrName)
{
	if( _tcscmp(pstrName, _T("MownWndKit")) == 0 ) return static_cast<CMownWndKitUI*>(this);
	return CControlUI::GetInterface(pstrName);
}

void CMownWndKitUI::DoEvent(TEventUI& event)
{
	if( !IsMouseEnabled() && event.Type > UIEVENT__MOUSEBEGIN && event.Type < UIEVENT__MOUSEEND ) {
		if( m_pParent != NULL ) m_pParent->DoEvent(event);
		else CControlUI::DoEvent(event);
		return;
	}
	if( event.Type == UIEVENT_SETFOCUS && IsEnabled() ) 
	{
		if( m_pWindow ) return;
	}
	if( event.Type == UIEVENT_KILLFOCUS && IsEnabled() ) 
	{
		Invalidate();
	}
	if( event.Type == UIEVENT_SETCURSOR )
	{
		::SetCursor(::LoadCursor(NULL, MAKEINTRESOURCE(IDC_ARROW)));
		return;
	}
	if( event.Type == UIEVENT_BUTTONDOWN) 
	{
		if( IsEnabled() ) {
			GetManager()->ReleaseCapture();
			printf("%s-%s-%d=%s\n",__FILE__,__FUNCTION__,__LINE__,this->GetName());
		}
		return;
	}
	if (event.Type == UIEVENT_DBLCLICK)
	{
		if( IsEnabled() ) {
			GetManager()->ReleaseCapture();
			printf("%s-%s-%d=%s\n",__FILE__,__FUNCTION__,__LINE__,this->GetName());
		}
	}
	if (event.Type == UIEVENT_RBUTTONDOWN)
	{
		if( IsEnabled() ) {
			GetManager()->ReleaseCapture();
			printf("%s-%s-%d=%s\n",__FILE__,__FUNCTION__,__LINE__,this->GetName());
		}
	}
	if( event.Type == UIEVENT_KILLFOCUS && IsEnabled() ) 
	{
		Invalidate();
	}
	CControlUI::DoEvent(event);
}

void CMownWndKitUI::SetPos(RECT rc, bool bNeedInvalidate)
{
	CControlUI::SetPos(rc,bNeedInvalidate);	
// 	::SetWindowPos(m_pWindow->GetHWND(), NULL, rc.left+4, rc.top+4, rc.right - rc.left-4, 
// 		rc.bottom - rc.top-4, SWP_NOZORDER | SWP_NOACTIVATE);  
	::SetWindowPos(m_pWindow->GetHWND(), NULL, rc.left, rc.top, rc.right - rc.left, 
		rc.bottom - rc.top, SWP_NOZORDER | SWP_NOACTIVATE); 
}

void CMownWndKitUI::SetAttribute(LPCTSTR pstrName, LPCTSTR pstrValue)
{
	CControlUI::SetAttribute(pstrName,pstrValue);
}

void CMownWndKitUI::PaintBkColor(HDC hDC)
{
	if( m_dwBackColor != 0 ) {
		
				CRenderEngine::DrawGradient(hDC, m_rcItem, GetAdjustColor(m_dwBackColor), GetAdjustColor(m_dwBackColor2), true, 16);
		}
		else if( m_dwBackColor >= 0xFF000000 ) CRenderEngine::DrawColor(hDC, m_rcPaint, GetAdjustColor(m_dwBackColor));
		else CRenderEngine::DrawColor(hDC, m_rcItem, GetAdjustColor(m_dwBackColor));
	
}
