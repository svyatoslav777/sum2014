/* FILENAME: UNITINFO.C
 * PROGRAMMER: VG4
 * PURPOSE: Animation unit samples handle module.
 * LAST UPDATE: 13.06.2014
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

#include "anim.h"

/* ��������� �������� ������� �������� */
typedef struct tagvg4UNIT_INFO
{
  VG4_UNIT_BASE_FIELDS; /* ��������� ������� ����� */
} vg4UNIT_INFO;

/* ������� ������������� ��������������� ������� ��������.
 * ���������:
 *   - ��������� �� "����" - ��� ������ ��������:
 *       vg4UNIT_INFO *Unit;
 *   - ��������� �� �������� ��������:
 *       vg4ANIM *Ani;
 * ������������ ��������: ���.
 */
static VOID InfoUnitInit( vg4UNIT_INFO *Unit, vg4ANIM *Ani )
{
} /* End of 'InfoUnitInit' function */

/* ������� ��������������� ��������������� ������� ��������.
 * ���������:
 *   - ��������� �� "����" - ��� ������ ��������:
 *       vg4UNIT_INFO *Unit;
 *   - ��������� �� �������� ��������:
 *       vg4ANIM *Ani;
 * ������������ ��������: ���.
 */
static VOID InfoUnitClose( vg4UNIT_INFO *Unit, vg4ANIM *Ani )
{
} /* End of 'InfoUnitClose' function */

/* ������� ���������� ����������� ���������� ���������������
 * ������� ��������.
 * ���������:
 *   - ��������� �� "����" - ��� ������ ��������:
 *       vg4UNIT_INFO *Unit;
 *   - ��������� �� �������� ��������:
 *       vg4ANIM *Ani;
 * ������������ ��������: ���.
 */
static VOID InfoUnitResponse( vg4UNIT_INFO *Unit, vg4ANIM *Ani )
{
  if (Ani->Keys[VK_LMENU] && Ani->KeysClick[VK_RETURN])
    VG4_AnimFlipFullScreen();
  if (Ani->KeysClick['P'])
    VG4_AnimSetPause(!Ani->IsPause);
  if (Ani->Keys[VK_ESCAPE])
    DestroyWindow(Ani->hWnd);
} /* End of 'InfoUnitResponse' function */

/* ������� ���������� ��������������� ������� ��������.
 * ���������:
 *   - ��������� �� "����" - ��� ������ ��������:
 *       vg4UNIT *Unit;
 *   - ��������� �� �������� ��������:
 *       vg4UNIT_INFO *Ani;
 * ������������ ��������: ���.
 */
static VOID InfoUnitRender( vg4UNIT_INFO *Unit, vg4ANIM *Ani )
{
  INT x, y;
  static CHAR Buf[1000];

  sprintf(Buf, "FPS: %.3f", Ani->FPS);
  SetWindowText(Ani->hWnd, Buf);
} /* End of 'InfoUnitRender' function */

/* ������� �������� ��������������� ������� ��������.
 * ���������: ���.
 * ������������ ��������:
 *   (vg4UNIT_INFO *) ��������� �� ��������� ������ ��������.
 */
vg4UNIT * VG4_InfoUnitCreate( VOID )
{
  vg4UNIT_INFO *Unit;

  if ((Unit = (vg4UNIT_INFO *)VG4_AnimUnitCreate(sizeof(vg4UNIT_INFO))) == NULL)
    return NULL;
  /* ��������� ���� ��-��������� */
  Unit->Init = (VOID *)InfoUnitInit;
  Unit->Close = (VOID *)InfoUnitClose;
  Unit->Render = (VOID *)InfoUnitRender;
  Unit->Response = (VOID *)InfoUnitResponse;
  return (vg4UNIT *)Unit;
} /* End of 'VG4_InfoUnitCreate' function */

/* END OF 'UNITINFO.C' FILE */
