/* FILENAME: RENDER.H
 * PROGRAMMER: VG4
 * PURPOSE: 3D render declaration module.
 * LAST UPDATE: 10.06.2014
 */

#ifndef __RENDER_H_
#define __RENDER_H_

#include "vec.h"

/* ��� ������������� ������ � ������������ */
typedef struct
{
  VEC
    Loc,             /* ����� ������������ */
    Dir, Up, Right,  /* �������������� ������� */
    At;              /* ����� ���������� */
} CAMERA;

/* ���������� ������ */
extern CAMERA VG4_RndCam;

/* ��������� ������������� */
extern DBL
  VG4_RndWs, VG4_RndHs, /* ������� ����� � ������ */
  VG4_RndWp, VG4_RndHp, /* ������� ������� ������������� */
  VG4_RndProjDist;      /* ���������� �� ��������� �������� */

/* ������� */
extern MATR
  VG4_RndMatrWorld, /* ������� �������������� ������� �� */
  VG4_RndMatrView;  /* ������� �������������� ������� �� */

/* ������� �������������� �� ������� ������� ��������� � ���� */
POINT VG4_RndWorldToScreen( VEC P );

#endif /* __RENDER_H_ */

/* END OF 'RENDER.H' FILE */
