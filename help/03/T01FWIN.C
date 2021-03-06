/* FILENAME: T01FWIN.C
 * PROGRAMMER: VG4
 * PURPOSE: First WinAPI application
 * LAST UPDATE: 02.06.2014
 */

#include <math.h>

#include <windows.h>

#pragma warning(disable: 4244)

#define SQR(X) ((X) * (X))

#define WND_CLASS_NAME "My Window Class Name"

/* ������ ������ */
LRESULT CALLBACK MyWindowFunc( HWND hWnd, UINT Msg,
                               WPARAM wParam, LPARAM lParam );

/* ������� ������� ���������.
 * ���������:
 *   - ���������� ���������� ����������:
 *       HINSTANCE hInstance;
 *   - ���������� ����������� ���������� ����������
 *     (�� ������������ � ������ ���� NULL):
 *       HINSTANCE hPrevInstance;
 *   - ��������� ������:
 *       CHAR *CmdLine;
 *   - ���� ������ ���� (��. SW_SHOWNORMAL, SW_SHOWMINIMIZED, SW_***):
 *       INT ShowCmd;
 * ������������ ��������:
 *   (INT) ��� �������� � ������������ �������.
 */
INT WINAPI WinMain( HINSTANCE hInstance, HINSTANCE hPrevInstance,
                    CHAR *CmdLine, INT ShowCmd )
{
  WNDCLASS wc;
  HWND hWnd;
  MSG msg;

  /* ����������� - �������� ������������ ������ ���� */
  wc.style = CS_HREDRAW | CS_VREDRAW;
  wc.cbClsExtra = 0; /* �������������� ���������� ���� ��� ������ */
  wc.cbWndExtra = 0; /* �������������� ���������� ���� ��� ���� */
  wc.hbrBackground = (HBRUSH)COLOR_WINDOW; /* ������� ���� - ��������� � ������� */
  wc.hCursor = LoadCursor(NULL, IDC_HAND);
  wc.hIcon = LoadIcon(NULL, IDI_ERROR);
  wc.lpszMenuName = NULL;
  wc.hInstance = hInstance;
  wc.lpfnWndProc = MyWindowFunc;
  wc.lpszClassName = WND_CLASS_NAME;

  /* ������������ ����� */
  if (!RegisterClass(&wc))
  {
    MessageBox(NULL, "Error register window class", "Error", MB_ICONERROR | MB_OK);
    return 0;
  }

  /* �������� ���� */
  hWnd = CreateWindow(WND_CLASS_NAME, "First Window Sample",
    WS_OVERLAPPEDWINDOW,
    CW_USEDEFAULT, CW_USEDEFAULT, /* ������� ���� (x, y) - �� ��������� */
    CW_USEDEFAULT, CW_USEDEFAULT, /* ������� ���� (w, h) - �� ��������� */
    NULL,                         /* ���������� ������������� ���� */
    NULL,                         /* ���������� ������������ ���� */
    hInstance,                    /* ���������� ���������� */
    NULL);                        /* ��������� �� �������������� ��������� */

  ShowWindow(hWnd, ShowCmd);
  UpdateWindow(hWnd);

  /* ������ ����� ��������� ��������� */
  while (GetMessage(&msg, NULL, 0, 0))
  {
    TranslateMessage(&msg);
    /* �������� ��������� � ������� ���� */
    DispatchMessage(&msg);
  }

  return msg.wParam;
} /* End of 'WinMain' function */

/* ������� ��������� ���������� ����� �� 0 �� 1.
 * ���������: ���.
 * ������������ ��������:
 *   (float) - ���������.
 */
float r0( void )
{
  return (float)rand() / RAND_MAX;
} /* End of 'r0' function */

/* ������� ��������� �����.
 * ���������:
 *   - �������� ���������:
 *       HDC hDC;
 *   - ������� ������� ����:
 *       INT Xm, Ym;
 *   - ������� ������ "�����":
 *       INT X�, Y�;
 *   - ������ ����� (������ � ������):
 *       INT W, H;
 *   - ������ "������":
 *       INT R;
 * ������������ ��������: ���.
 */
void DrawEye( HDC hDC, INT Xm, INT Ym, INT Xc, INT Yc, INT W, INT H, INT R )
{
  INT xx, yy;
  float
    len, si, co,
    ratio = (float)W / H;

  len = sqrt(SQR(Xc - Xm) + SQR((Yc - Ym) * ratio));

  if (len == 0)
    si = 0, co = 0;
  else
    co = (Xm - Xc) / len, si = (Ym - Yc) * ratio / len;

  SelectObject(hDC, GetStockObject(DC_PEN));
  SelectObject(hDC, GetStockObject(DC_BRUSH));
  SetDCPenColor(hDC, RGB(0, 0, 0));
  SetDCBrushColor(hDC, RGB(255, 255, 255));

  Ellipse(hDC, Xc - W / 2, Yc - H / 2, Xc + W / 2, Yc + H / 2);

  if (len > W / 2 - R)
    len = W / 2 - R;
  xx = Xc + co * len;
  yy = Yc + si * len / ratio;

  SetDCBrushColor(hDC, RGB(0, 0, 0));
  Ellipse(hDC, xx - R, yy - R / ratio, xx + R, yy + R / ratio);
} /* End of 'DrawEye' function */

/* ������� ��������� ��������� ����.
 * ���������:
 *   - ���������� ����:
 *       HWND hWnd;
 *   - ����� ���������:
 *       UINT Msg;
 *   - �������� ��������� ('word parameter'):
 *       WPARAM wParam;
 *   - �������� ��������� ('long parameter'):
 *       LPARAM lParam;
 * ������������ ��������:
 *   (LRESULT) - � ����������� �� ���������.
 */
LRESULT CALLBACK MyWindowFunc( HWND hWnd, UINT Msg,
                               WPARAM wParam, LPARAM lParam )
{
  INT n, x, y;
  HDC hDC, hMemDC, hMemDC1;
  PAINTSTRUCT ps;
  POINT pt;
  BITMAP bm;
  static HBITMAP hBm, hBmLogo, hBmLogoAnd, hBmLogoXor;
  static INT W, H;

  switch (Msg)
  {
  case WM_CHAR:
    if ((CHAR)wParam == 27)
      DestroyWindow(hWnd);
    return 0;
  case WM_CREATE:
    SetTimer(hWnd, 30, 50, NULL);
    hBmLogo = LoadImage(NULL, "M.BMP", IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE);
    hBmLogoAnd = LoadImage(NULL, "AND.BMP", IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE);
    hBmLogoXor = LoadImage(NULL, "XOR.BMP", IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE);
    return 0;
  case WM_SIZE:
    W = LOWORD(lParam);
    H = HIWORD(lParam);
    hDC = GetDC(hWnd);
    if (hBm != NULL)
      DeleteObject(hBm);
    hBm = CreateCompatibleBitmap(hDC, W, H);
    ReleaseDC(hWnd, hDC);
    return 0;
  case WM_TIMER:
    InvalidateRect(hWnd, NULL, FALSE);
    return 0;
  case WM_ERASEBKGND:
    return 1;
  case WM_PAINT:
    hDC = BeginPaint(hWnd, &ps);
    
    hMemDC = CreateCompatibleDC(hDC);
    SelectObject(hMemDC, hBm);

    GetCursorPos(&pt);
    ScreenToClient(hWnd, &pt);

    Rectangle(hMemDC, 0, 0, W, H);

    DrawEye(hMemDC, pt.x, pt.y, 300, 300, 100, 100, 15);

    DrawEye(hMemDC, pt.x, pt.y,
      W * 3 / 4, W / 2,
      W / 2, H,
      W / 16);

    n = 1000;
    srand(30);
    while (n-- > 0)
      DrawEye(hMemDC, pt.x, pt.y,
        r0() * W, r0() * H,
        15 + rand() % 130, 90, 30);

    hMemDC1 = CreateCompatibleDC(hDC);

    GetObject(hBmLogoAnd, sizeof(bm), &bm);

    n = 5;
    while (n-- > 0)
    {
      x = r0() * W;
      y = r0() * H;
      SelectObject(hMemDC1, hBmLogoAnd);
      BitBlt(hMemDC, x, y, bm.bmWidth, bm.bmHeight, hMemDC1, 0, 0, SRCAND);
      SelectObject(hMemDC1, hBmLogoXor);
      BitBlt(hMemDC, x, y, bm.bmWidth, bm.bmHeight, hMemDC1, 0, 0, SRCINVERT);
    }
    SelectObject(hMemDC1, hBmLogo);
    GetObject(hBmLogo, sizeof(bm), &bm);
    BitBlt(hMemDC, 0, 0, bm.bmWidth, bm.bmHeight, hMemDC1, 0, 0, SRCCOPY);

    BitBlt(hDC, 0, 0, W, H, hMemDC, 0, 0, SRCCOPY);
    DeleteDC(hMemDC);
    DeleteDC(hMemDC1);
    EndPaint(hWnd, &ps);
    return 0;
  case WM_DESTROY:
    DeleteObject(hBm);
    DeleteObject(hBmLogo);
    DeleteObject(hBmLogoAnd);
    DeleteObject(hBmLogoXor);
    PostQuitMessage(0);
    KillTimer(hWnd, 30);
    return 0;
  }
  return DefWindowProc(hWnd, Msg, wParam, lParam);
} /* End of 'MyWindowFunc' function */

