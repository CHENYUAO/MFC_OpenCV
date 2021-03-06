
// MFCOpenCVDlg.h: 头文件
//

#pragma once
#include <opencv2/core/core.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/highgui/highgui_c.h>
#include <string>
#include "opencv.h"

// CMFCOpenCVDlg 对话框
class CMFCOpenCVDlg : public CDialogEx
{
// 构造
public:
	CMFCOpenCVDlg(CWnd* pParent = nullptr);	// 标准构造函数

// 对话框数据
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_MFCOPENCV_DIALOG };
#endif

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV 支持


// 实现
protected:
	HICON m_hIcon;

	// 生成的消息映射函数
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedButton1();
	afx_msg void OnBnClickedOk();
	afx_msg void OnBnClickedMainframe();
	afx_msg void OnBnClickedCancel();
	afx_msg void OnBnClickedButton2();

public:
	cv::Mat image;
	void showPic(cv::Mat& image) const;
	void showHis(cv::Mat& image) const;

	afx_msg void OnBnClickedButton3();
};
