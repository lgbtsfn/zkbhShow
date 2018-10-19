#include "StdAfx.h"
#include "Resource.h"
#include "mainFrame.h"

MainFrame::MainFrame()
{
	char cFullPath[MAX_PATH];
	GetModuleFileName(NULL,cFullPath,MAX_PATH);
	m_Path = cFullPath;
	int pos = m_Path.find_last_of('\\',m_Path.length());
	m_Path = m_Path.substr(0,pos);

	CreateHandle(&m_handle);
}

MainFrame::~MainFrame()
{
	if (m_Camera.isOpened())
	{
		m_Camera.release();
	}
	KillTimer(m_pm.GetPaintWindow(),12);
	DestroyHandle(&m_handle);
	PostQuitMessage(0);
}

LPCTSTR MainFrame::GetWindowClassName(void) const
{
	return _T("PWSHOW");
}

CDuiString MainFrame::GetSkinFile()
{
	return _T("mainSkin.xml");
}

LRESULT MainFrame::HandleMessage( UINT uMsg, WPARAM wParam, LPARAM lParam )
{
	LRESULT lRes = __super::HandleMessage(uMsg, wParam, lParam);
	BOOL bHandle = FALSE;
	switch(wParam){
	case WM_TIMER:
		OnTimer(uMsg, wParam, lParam,bHandle);
		break;
	}
	return lRes;
}

LRESULT MainFrame::OnTimer(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled)
{
	bHandled = TRUE;
	
	if (wParam==12)
	{
		if (m_Camera.isOpened())
		{
			if (!m_Camera.grab())
			{
				m_Camera.release();
				m_Camera.open(m_sVideoFile.c_str());
			}
			Mat iframe;
			if(!m_Camera.read(iframe))
			{
				return 0;
			}
			DetectMat(iframe);
		}
	}
	return 0;
}

void MainFrame::DetectMat(Mat mat)
{
	if (!m_flg)
	{
		m_flg=true;
		mat.copyTo(m_FrameTemp);
		return;
	}
	else
	{
		m_flg=false;
		mat.copyTo(m_Frame);
	}
	DetectOut out;
	int flg;
	flg = find_target(m_handle,m_FrameTemp.data,m_Frame.data,m_Frame.rows,m_Frame.cols,m_Frame.channels(),&out);
	
	Mat frame = m_Frame.clone();
	if (flg==0)
	{
		vector<vector<Point>>lines;
		cvtOut2Lines(out,lines);
		vector<vector<Point>>::iterator it;
		for (it=lines.begin();it!=lines.end();it++)
		{
			drawLine(frame,*it);
		}
		vector<Point>points;
		cvtOut2Points(out,points);
		vector<Point>::iterator it2;
		for (it2=points.begin();it2!=points.end();it2++)
		{
			circle(frame,*it2,8,Scalar(0,0,255),-1);
		}
	}
	OutputDestroy(&out);
	ShowImage(frame,m_hwnd1);
	ShowImage(mat,m_hwnd2);
}

void MainFrame::OnExit(TNotifyUI& msg)
{
	Close();
}

void MainFrame::Notify(TNotifyUI& msg)
{
	CDuiString name = msg.pSender->GetName();
	if (msg.sType == _T("windowinit"))
	{
		return;
	}
	else if (msg.sType == _T("click"))
	{
		if (name == _T("closeBtn"))
		{
			Close();
		}
		return;
	}
}

void MainFrame::InitWindow()
{
	SetIcon(IDI_SMALL);
	m_winShow1 = static_cast<CMownWndKitUI*>(m_pm.FindControl(_T("selfCtl1")));
	if (!m_winShow1)
	{
		return;
	}
	m_hwnd1 = m_winShow1->GetHWND();
	m_winShow2 = static_cast<CMownWndKitUI*>(m_pm.FindControl(_T("selfCtl2")));
	if (!m_winShow2)
	{
		return;
	}
	m_hwnd2 = m_winShow2->GetHWND();
	string sFilePath = m_Path;
	sFilePath += "\\IniFile.ini";
	char cVideo[32]="";
	char cLogo[32]="";
	GetPrivateProfileString(_T("ZKBH"),_T("VIDEO"),NULL,cVideo,MAX_PATH,sFilePath.c_str());
	GetPrivateProfileString(_T("ZKBH"),_T("LOGO"),NULL,cLogo,MAX_PATH,sFilePath.c_str());
	m_sVideoFile = m_Path + "\\" + cVideo;
	m_Camera.open(m_sVideoFile.c_str());
	if (!m_Camera.isOpened())
	{
		return;
	}
	string sLogoFile = m_Path + "\\" + cLogo;
	m_logo = imread(sLogoFile,-1);
	m_flg = false;
	SetTimer(m_pm.GetPaintWindow(),12,50,NULL);
}

void MainFrame::OnFinalMessage(HWND hWnd)
{
	WindowImplBase::OnFinalMessage(hWnd);
	delete this;
}

LRESULT MainFrame::OnGetMinMaxInfo(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled)
{
	bHandled = FALSE;
	return 0;
}

CControlUI* MainFrame::CreateControl(LPCTSTR pstrClassName)
{
	if (_tcsicmp(pstrClassName, _T("SelfCtl")) == 0)
	{
		return new CMownWndKitUI();
	}
	return NULL;
}

void MainFrame::ShowImage(Mat src,HWND hwnd)
{
	if (src.empty())	return;
	
	if (!::IsWindow(hwnd))
	{
		return;
	}
	ImageOverlay(m_logo,src);
	HDC hDC = GetDC(hwnd);				// 获取 HDC(设备句柄) 来进行绘图操作
	RECT rect;
	::GetClientRect(hwnd,&rect);		// 获取控件尺寸位置

	CvvImage cimg;
	IplImage cpy = src;
	cimg.CopyOf(&cpy);						// 复制图片
	cimg.DrawToHDC(hDC, &rect);				// 将图片绘制到显示控件的指定区域内
	cimg.Destroy();
	DeleteDC(hDC);
}

LRESULT MainFrame::HandleCustomMessage(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled)
{
	if(uMsg == WM_DESTROY)
	{
		::PostQuitMessage(0L);
		bHandled = TRUE;
		return 0;
	}
	LRESULT lRes = 0;
	switch (uMsg)
	{
		case WM_TIMER: lRes = OnTimer(uMsg, wParam, lParam, bHandled); break;
	}
	return 0;
}

void MainFrame::ImageOverlay(const cv::Mat &mask, cv::Mat &image)
{
	int nc = 3, alpha = 0;
	for (int j = 0; j < mask.rows; j++)
	{
		for (int i = 0; i < mask.cols * 3; i += 3)
		{
			alpha = mask.ptr<uchar>(j)[i / 3 * 4 + 3];//第4字节通道
			if (alpha == 255)//不透明
			{
				for (int k = 0; k < 3; k++)
				{
					if ((j < image.rows) && (j >= 0) && (i / 3 * 3 + k < image.cols * 3) && (i / 3 * 3 + k >= 0) &&
						(i / nc * 4 + k < mask.cols * 4) && (i / nc * 4 + k >= 0))
					{
						image.ptr<uchar>(j)[i / nc * nc + k] = mask.ptr<uchar>(j)[(i) / nc * 4 + k];
					}
				}
			}
			else if (alpha > 0 && alpha < 255)//按照比例半透明
			{
				double rate = alpha / 255.0;
				for (int k = 0; k < 3; k++)
				{
					if ((j < image.rows) && (j >= 0) && (i / 3 * 3 + k < image.cols * 3) && (i / 3 * 3 + k >= 0) &&
						(i / nc * 4 + k < mask.cols * 4) && (i / nc * 4 + k >= 0))
					{
						image.ptr<uchar>(j)[i / nc * nc + k] = (uchar)(mask.ptr<uchar>(j)[(i) / nc * 4 + k] * rate + image.ptr<uchar>(j)[i / nc * nc + k] * (1 - rate));
					}
				}
			}//alpha=0完全透明
		}
	}
}

void MainFrame::cvtOut2Lines(DetectOut result, vector<vector<cv::Point>>& lines) 
{
	for (int i = 0; i < result.num; i++){
		vector<cv::Point> line;
		for (int j = 0; j < result.lines[i].num; j++) {
			cv::Point pt(result.lines[i].points[2*j],     // x
				result.lines[i].points[2*j + 1]);//y
			line.push_back(pt);
		}
		lines.push_back(line);
	}
}

void MainFrame::cvtOut2Points(DetectOut result, vector<cv::Point>& pts) 
{
	for (int i = 0; i < result.num; i++) {
		int index = result.num - 1;
		cv::Point pt(result.lines[i].points[2*index],
			result.lines[i].points[2*index + 1]);
		pts.push_back(pt);
	}
}

void MainFrame::drawLine(Mat& img, const vector<cv::Point>& pts) 
{
	for(size_t i = 1; i < pts.size(); i++) {
		line(img, pts[i - 1], pts[i], Scalar(0, 0, 255), 2);
	}
}