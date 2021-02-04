// D3D Sprite toturial
//
////////////////////////////////////////////////////////////////////////////////

#pragma warning(disable : 4996)

#include <windows.h>

TCHAR		m_sCls[128]	= "rev12star Window";
HINSTANCE	m_hInst		= NULL;
HWND		m_hWnd		= NULL;
DWORD		m_dWinStyle	= WS_OVERLAPPEDWINDOW| WS_VISIBLE;
DWORD		m_dScnX		= 800;			// Screen Width
DWORD		m_dScnY		= 600;			// Screen Height
bool		m_bShowCusor= true;			// Show Cusor

INT		Create(HINSTANCE hInst);
INT		Run();
void	Cleanup();
LRESULT MsgProc( HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam );
LRESULT WINAPI WndProc( HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam );

INT Create( HINSTANCE hInst)
{
	char* leak_ptr = new char[40000]{};
	m_hInst	= hInst;
	WNDCLASS wc
	{
		CS_CLASSDC
		, WndProc
		, 0L
		, 0L
		, m_hInst
		, NULL
		, LoadCursor(NULL,IDC_ARROW)
		, (HBRUSH)GetStockObject(LTGRAY_BRUSH)
		, NULL
		, m_sCls
	};
	RegisterClass( &wc );
	RECT rc{};
	SetRect( &rc, 0, 0, m_dScnX, m_dScnY);
	AdjustWindowRect( &rc, m_dWinStyle, FALSE );
	int iScnSysW = ::GetSystemMetrics(SM_CXSCREEN);
	int iScnSysH = ::GetSystemMetrics(SM_CYSCREEN);
	m_hWnd = CreateWindow( m_sCls
		, m_sCls
		, m_dWinStyle
		, (iScnSysW - (rc.right-rc.left))/2
		, (iScnSysH - (rc.bottom-rc.top))/2
		, (rc.right-rc.left)
		, (rc.bottom-rc.top)
		, NULL
		, NULL
		, m_hInst
		, NULL );
	ShowWindow( m_hWnd, SW_SHOW );
	UpdateWindow( m_hWnd );
	::ShowCursor(m_bShowCusor);
	return S_OK;
}

void Cleanup()
{
	if(m_hInst)
		UnregisterClass( m_sCls, m_hInst);
}

LRESULT MsgProc( HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam )
{
	switch( msg ) {
		case WM_KEYDOWN: {
			switch(wParam) {
				case VK_ESCAPE: {
					SendMessage(hWnd, WM_DESTROY, 0,0);
					break;
				}
			}
			return 0;
		}
		case WM_DESTROY: {
			Cleanup();
			PostQuitMessage( 0 );
			return 0;
		}
		case WM_PAINT: {
			HDC hdc;
			PAINTSTRUCT ps;
			char tst_msg[] = "Hello world";
			hdc = BeginPaint(hWnd, &ps);
			TextOutA(hdc, 100, 50, tst_msg, lstrlen(tst_msg));
			EndPaint(hWnd, &ps);
			return 0;
		}
	}
	return DefWindowProc( hWnd, msg, wParam, lParam );
}

INT Run()
{
	MSG msg{};
	while( msg.message!=WM_QUIT ) {
		if( PeekMessage( &msg, NULL, 0U, 0U, PM_REMOVE ) ) {
			TranslateMessage( &msg );
			DispatchMessage( &msg );
		} else {
		}
	}
	UnregisterClass( m_sCls, m_hInst);
	return 0;
}

LRESULT WINAPI WndProc( HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam )
{
	return MsgProc(hWnd, msg, wParam, lParam);
}

int WINAPI WinMain( HINSTANCE hInst, HINSTANCE, LPSTR, int )
{
	if(FAILED(Create(hInst)))
		return -1;
	return Run();
}
