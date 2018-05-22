// DetailInfoWnd.cpp : 구현 파일입니다.
//

#include "stdafx.h"
#include "TeilUndAlles.h"
#include "DetailInfoWnd.h"
#include "afxdialogex.h"
#include "TeilUndAllesDoc.h"


// CDetailInfoWnd 대화 상자입니다.

IMPLEMENT_DYNAMIC(CDetailInfoWnd, CDialogEx)

CDetailInfoWnd::CDetailInfoWnd(CWnd* pParent /*=NULL*/)
	: CDialogEx(IDD_DETIALINFORMATIONVIEW, pParent)
	, m_id(0)
	, m_strnodename(_T(""))
	, m_strnodedesc(_T(""))
	, m_datedue(COleDateTime::GetCurrentTime())
	, m_checkcomplete(FALSE)
{

}

CDetailInfoWnd::~CDetailInfoWnd()
{
}

void CDetailInfoWnd::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_EDIT1, m_id);
	DDX_Text(pDX, IDC_EDIT2, m_strnodename);
	DDX_Text(pDX, IDC_EDIT3, m_strnodedesc);
	DDX_DateTimeCtrl(pDX, IDC_DATETIMEPICKER1, m_datedue);
	DDX_Check(pDX, IDC_CHECK1, m_checkcomplete);
}


BEGIN_MESSAGE_MAP(CDetailInfoWnd, CDialogEx)
END_MESSAGE_MAP()


// CDetailInfoWnd 메시지 처리기입니다.

void CDetailInfoWnd::select_node(CTeilUndAllesDoc* _pDoc, Node* _selected_node)
{
	pDoc = _pDoc;
	selected_node = _selected_node;

	m_id = selected_node->getid();
	m_strnodename = CString(selected_node->getnodename().c_str());

	std::wstring nodedesc = selected_node->general_data.get(L"problem_text", std::wstring(L"아직 지정되지 않음"));
	m_strnodedesc = CString(nodedesc.c_str());

	COleDateTime crttime = COleDateTime::GetCurrentTime();
	std::wstring defaulttime = std::wstring(crttime.Format(L"%Y-%m-%d"));
	m_datedue.ParseDateTime(selected_node->general_data.get(L"due_date", defaulttime).c_str());

	m_checkcomplete = selected_node->general_data.get(L"completed", false);

	UpdateData(FALSE);
}


BOOL CDetailInfoWnd::PreTranslateMessage(MSG* pMsg)
{
	// TODO: 여기에 특수화된 코드를 추가 및/또는 기본 클래스를 호출합니다.

	if (pMsg->message == WM_KEYDOWN)
	{
		if (pMsg->wParam == VK_RETURN)
		{
			if (selected_node != NULL)
			{
				UpdateData(TRUE);
				selected_node->setnodename(std::wstring(m_strnodename));
				selected_node->general_data.write(L"problem_text", std::wstring(m_strnodedesc));
				selected_node->general_data.write(L"due_date", std::wstring(m_datedue.Format(L"%Y-%m-%d")));
				selected_node->general_data.write(L"completed", (bool)m_checkcomplete);

				pDoc->UpdateAllViews(NULL);
			}
			return FALSE;
		}
		if(pMsg->wParam == VK_ESCAPE)
			return FALSE;
	}

	return CDialogEx::PreTranslateMessage(pMsg);
}
