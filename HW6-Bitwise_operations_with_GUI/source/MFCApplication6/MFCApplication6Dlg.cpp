
// MFCApplication6Dlg.cpp : implementation file

#include "stdafx.h"
#include "MFCApplication6.h"
#include "MFCApplication6Dlg.h"
#include "afxdialogex.h"


#ifdef _DEBUG
#define new DEBUG_NEW
#endif

// CAboutDlg dialog used for App About

class CAboutDlg : public CDialogEx
{
public:
	CAboutDlg();

// Dialog Data
	enum { IDD = IDD_ABOUTBOX };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

// Implementation
protected:
	DECLARE_MESSAGE_MAP()
};

CAboutDlg::CAboutDlg() : CDialogEx(CAboutDlg::IDD)
{
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialogEx)
END_MESSAGE_MAP()


// CMFCApplication6Dlg dialog



CMFCApplication6Dlg::CMFCApplication6Dlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(CMFCApplication6Dlg::IDD, pParent)
	, radiobuttons(0)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CMFCApplication6Dlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_EDIT1, op1);
	DDX_Control(pDX, IDC_EDIT2, op2);
	DDX_Control(pDX, IDC_EDIT3, op3);
	DDX_Control(pDX, IDC_CHECK1, shift);
	DDX_Control(pDX, IDC_COMBO1, shiftype);
	DDX_Control(pDX, IDC_BUTTON1, compute);
	DDX_Control(pDX, IDC_LIST1, list);
	DDX_Radio(pDX, IDC_RADIO1, radiobuttons);
}

BEGIN_MESSAGE_MAP(CMFCApplication6Dlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDC_BUTTON1, &CMFCApplication6Dlg::OnBnClickedButton1)
	ON_BN_CLICKED(IDC_CHECK1, &CMFCApplication6Dlg::OnBnClickedCheck1)
END_MESSAGE_MAP()


// CMFCApplication6Dlg message handlers

BOOL CMFCApplication6Dlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// Add "About..." menu item to system menu.

	// IDM_ABOUTBOX must be in the system command range.
	ASSERT((IDM_ABOUTBOX & 0xFFF0) == IDM_ABOUTBOX);
	ASSERT(IDM_ABOUTBOX < 0xF000);

	CMenu* pSysMenu = GetSystemMenu(FALSE);
	if (pSysMenu != NULL)
	{
		BOOL bNameValid;
		CString strAboutMenu;
		bNameValid = strAboutMenu.LoadString(IDS_ABOUTBOX);
		ASSERT(bNameValid);
		if (!strAboutMenu.IsEmpty())
		{
			pSysMenu->AppendMenu(MF_SEPARATOR);
			pSysMenu->AppendMenu(MF_STRING, IDM_ABOUTBOX, strAboutMenu);
		}
	}

	// Set the icon for this dialog.  The framework does this automatically
	//  when the application's main window is not a dialog
	SetIcon(m_hIcon, TRUE);			// Set big icon
	SetIcon(m_hIcon, FALSE);		// Set small icon

	// TODO: Add extra initialization here
	shiftype.SetCurSel(0); //sets the shiftype to be Left initially
	return TRUE;  // return TRUE  unless you set the focus to a control
}

void CMFCApplication6Dlg::OnSysCommand(UINT nID, LPARAM lParam)
{
	if ((nID & 0xFFF0) == IDM_ABOUTBOX)
	{
		CAboutDlg dlgAbout;
		dlgAbout.DoModal();
	}
	else
	{
		CDialogEx::OnSysCommand(nID, lParam);
	}
}

// If you add a minimize button to your dialog, you will need the code below
//  to draw the icon.  For MFC applications using the document/view model,
//  this is automatically done for you by the framework.

void CMFCApplication6Dlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // device context for painting

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// Center icon in client rectangle
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// Draw the icon
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialogEx::OnPaint();
	}
}

// The system calls this function to obtain the cursor to display while the user drags
//  the minimized window.
HCURSOR CMFCApplication6Dlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}

int maxSize = 0;

void CMFCApplication6Dlg::OnBnClickedButton1()
{
	// TODO: Add your control notification handler code here
	CDC *pDC = GetDC();
	CSize cz;
	CString input1, input2, result, direction, input3, operationType;
	
	UpdateData(TRUE); //to get most recent values

	op1.GetWindowText(input1);
	op2.GetWindowText(input2);
	
	if (input1.IsEmpty()  || input2.IsEmpty()) //if one of the operands were not entered
		result = _T("At least 1 operand was not entered");
	else
	{
		unsigned int num1 = _tcstoul(input1,nullptr,10);
	    unsigned int num2 = _tcstoul(input2,nullptr,10);
	    unsigned int res, amount;
		bool flag = true;

		if (shift.GetCheck()) //if shift box is checked
		{
			shiftype.GetWindowText(direction);
			op3.GetWindowText(input3);

			if (! input3.IsEmpty()) //if "bits to shift" is not empty
			{
				amount = _tcstoul(input3,nullptr,10);

				if (direction == _T("Left")) //shift numbers to the left
				{
					num1 = num1 << amount;
					num2 = num2 << amount;
				}
				else if ( direction == _T("Right")) //shift them to the right
				{
					num1 = num1 >> amount;
					num2 = num2 >> amount;
				}
				flag = true;
			}
			else
			{
				flag = false;
			}
			
		}
		if (flag) //if the inputs are entered, do the bit operations
		{
				if (radiobuttons == 0)
			    {
					res = num1 & num2;
					operationType = _T(" AND ");
				}
				else if (radiobuttons == 1)
				{
					res = num1 | num2;
					operationType = _T(" OR ");
				}
				else
				{
					res = num1 ^ num2;
					operationType = _T(" XOR ");
				}

				input1.Format(_T("%u"),num1); //convert num1 into cstring
				input2.Format(_T("%u"),num2); //convert num2 into cstring
				input3.Format(_T("%u"),res); //convert the result into cstring

				result =  input1 + operationType + input2 + _T(" = ") + input3; //create the result string
		}
		else
		{
			result = _T("Specify how many bits you want to shift");
		}
	}

	list.AddString(result); //add the result or the error message to the list

	cz = pDC->GetTextExtent(result); //set the horizontal bar
	if (cz.cx >maxSize)
	{
		maxSize = cz.cx;
	}

	list.SetHorizontalExtent(maxSize);
}


void CMFCApplication6Dlg::OnBnClickedCheck1() //if shift is checked, enables the type and bits to shift; if it is unchecked, disables them
{
	// TODO: Add your control notification handler code here
	if (shift.GetCheck()) 
	{
		shiftype.EnableWindow(TRUE);
		op3.EnableWindow(TRUE);
	}
	else
	{
		shiftype.EnableWindow(FALSE);
		op3.EnableWindow(FALSE);
	}
}


