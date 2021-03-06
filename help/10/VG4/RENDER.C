/* FILENAME: RENDER.C
 * PROGRAMMER: VG4
 * PURPOSE: 3D render handle module.
 * LAST UPDATE: 10.06.2014
 */

#include "render.h"

/* ���������� ������ */
vg4CAMERA VG4_RndCam;

/* ��������� ������������� */
DBL
  VG4_RndWs = 30, VG4_RndHs = 30,   /* ������� ����� � ������ */
  VG4_RndWp = 4, VG4_RndHp = 3,     /* ������� ������� ������������� */
  VG4_RndProjDist = 5;              /* ���������� �� ��������� �������� */

/* ������� */
MATR
  VG4_RndMatrWorld = VG4_UNIT_MATR, /* ������� �������������� ������� �� */
  VG4_RndMatrView = VG4_UNIT_MATR;  /* ������� �������������� ������� �� */

/* ������� �������������� �� ������� ������� ��������� � ����.
 * ���������:
 *   - �������� �����:
 *       VEC P;
 * ������������ ��������:
 *   (POINT) ���������� � �����.
 */
POINT VG4_RndWorldToScreen( VEC P )
{
  POINT Ps;
  VEC Pp;

  /* �������������� �� */
  Pp = VecMulMatr(P, MatrMulMatr(VG4_RndMatrWorld, VG4_RndMatrView));
  
  /* ������������� */
  Ps.x = ( Pp.X + VG4_RndWp / 2) / VG4_RndWp * (VG4_RndWs - 1);
  Ps.y = (-Pp.Y + VG4_RndHp / 2) / VG4_RndHp * (VG4_RndHs - 1);
  return Ps;
} /* End of 'VG4_RndWorldToScreen' function */

/* END OF 'RENDER.C' FILE */
