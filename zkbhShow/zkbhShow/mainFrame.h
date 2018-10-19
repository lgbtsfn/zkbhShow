#ifndef MAINFRAME_H
#define MAINFRAME_H
#include "MownWndKit.h"

class MainFrame:public WindowImplBase
{
public:
	MainFrame();
	~MainFrame();
public:
	virtual void InitWindow();
	virtual void OnFinalMessage(HWND hWnd);
	virtual CControlUI* CreateControl(LPCTSTR pstrClass);
	virtual LRESULT HandleMessage( UINT uMsg, WPARAM wParam, LPARAM lParam );
	virtual LRESULT OnGetMinMaxInfo(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled);
	virtual LRESULT OnTimer(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled);
	virtual LRESULT HandleCustomMessage(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled);
protected:
	virtual CDuiString GetSkinFile();
	virtual LPCTSTR GetWindowClassName(void) const;
	void OnExit(TNotifyUI& msg);
	void Notify(TNotifyUI& msg);
	void ShowImage(Mat src,HWND hwnd);
	void ImageOverlay(const Mat &mask, Mat &image);
	void DetectMat(Mat mat);
	void cvtOut2Lines(DetectOut result, vector<vector<cv::Point>>& lines);
	void cvtOut2Points(DetectOut result, vector<cv::Point>& pts) ;
	void drawLine(Mat& img, const vector<cv::Point>& pts) ;
private:
	CMownWndKitUI *m_winShow1;
	HWND m_hwnd1;
	CMownWndKitUI *m_winShow2;
	HWND m_hwnd2;
	VideoCapture m_Camera;
	string m_Path;
	string m_sVideoFile;
	Mat m_logo;
	bool m_flg;
	FALL_HANDLE m_handle;
	Mat m_FrameTemp;
	Mat m_Frame;
};
#endif