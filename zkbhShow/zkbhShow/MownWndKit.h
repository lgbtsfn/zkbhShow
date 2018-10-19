#pragma once

const char TM_TICKER1 = 1;

class CMownWndKitUI;
class CMownWndKit : public WindowImplBase
{
	friend class CMownWndKitUI;
public:
	CMownWndKit();
	~CMownWndKit();

	void Init(CMownWndKitUI* pOwner);
	LPCTSTR GetWindowClassName() const;
	virtual CDuiString GetSkinFolder() {return "";};
	virtual CDuiString GetSkinFile() {return "";};
	
	void OnFinalMessage(HWND hWnd);

	LRESULT HandleMessage(UINT uMsg, WPARAM wParam, LPARAM lParam);

	LRESULT OnDestroy(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled);
	LRESULT OnPaint(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled);
	LRESULT OnCreate(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled);
	LRESULT OnSize(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled);
	LRESULT OnMouseEvent(UINT uMsg, WPARAM wParam,LPARAM lParam, BOOL& bHandled); 
	LRESULT OnMouseWheel(UINT uMsg, WPARAM wParam,LPARAM lParam, BOOL& bHandled); 
	LRESULT OnKeyDown(UINT uMsg, WPARAM wParam,LPARAM lParam, BOOL& bHandled);
	LRESULT OnKeyUp(UINT uMsg, WPARAM wParam,LPARAM lParam, BOOL& bHandled);
	LRESULT OnChar(UINT uMsg, WPARAM wParam,LPARAM lParam, BOOL& bHandled);
	LRESULT OnImeStartComposition(UINT uMsg, WPARAM wParam,LPARAM lParam, BOOL& bHandled);
	LRESULT OnSetFocus(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled);	
	
	LRESULT OnTimer(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled);
	LRESULT OnContextMenu(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled);
	LRESULT OnLBttonDown(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled);
	LRESULT OnRBttonDown(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled);
	LRESULT OnKillFocus(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled);
	LRESULT OnDBLClick(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled);
	void setbFocus(){m_bfocus=true;}
	void releaseFocus(){m_bfocus=false;}
protected:
	enum { 
		DEFAULT_TIMERID = 20,
	};
	CMownWndKitUI* m_pOwner;
	wstring		 m_strUrl;	
	bool		 m_bInit;
	bool		 m_bfocus;

};


class CMownWndKitUI :public CControlUI
{
	friend class CMownWndKit;
public:
public:
	enum showStatus{
		SHWO_STATUS1 = 1,
		SHOW_STATUS2 = 2,
		SHOW_STATUS3 = 3,
	};
	CMownWndKitUI(void);
	~CMownWndKitUI(void);

	
	LPCTSTR	GetClass() const override;
	LPVOID	GetInterface(LPCTSTR pstrName) override;

	void	SetVisible(bool bVisible) override;
	void	SetInternVisible(bool bVisible = true) override;
	void	DoInit() override;
	void	SetPos(RECT rc, bool bNeedInvalidate = true) override;	// 有些库的SetPos函数和我的不一样，需要根据使用的库修改这个函数
	void	DoEvent(TEventUI& event) override;	
	void	SetAttribute(LPCTSTR pstrName, LPCTSTR pstrValue) override;
	HWND	GetHWND() const{ return m_pWindow->GetHWND();}
	virtual void PaintBkColor(HDC hDC);
	void	setCurFocus(){m_pWindow->setbFocus();}
	void	setPlay(bool b){m_playflg=b;}
	bool    isPlay(){return m_playflg;}


	void	setCnt(int cnt){m_cnt = cnt;}
	int		getCnt(){return m_cnt;}
	void	setShowStatus(showStatus s){m_showStatus=s;}
	showStatus getShowStatus(){return m_showStatus;}
	void	saveOldRc(RECT rc){m_oldRc=rc;}
	RECT    getOldRc(){return m_oldRc;}
	void	setScreenCnt(int cnt){m_screenCnt=cnt;}
	int		getScreenCnt(){return m_screenCnt;}
protected:
	showStatus m_showStatus;
	CMownWndKit *m_pWindow;
	bool m_playflg;
	int m_cnt;//记录当前是第几个窗口
	int m_screenCnt;
	RECT m_oldRc;
};

