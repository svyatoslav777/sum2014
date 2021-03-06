/* FILENAME: RENDER.H
 * PROGRAMMER: SS3
 * PURPOSE: 3D render declaration module.
 * LAST UPDATE: 10.06.2014
 */

#ifndef __RENDER_H_
#define __RENDER_H_

#include "vec.h"

typedef struct
{
  VEC
    Loc,
    Dir, Up, Right,
    At;
} ss3CAMERA;

typedef struct tagss3GOBJ
{
  VEC *V;
  INT NumOfV;
  INT (*F)[3];
  INT NumOfF;
} ss3GOBJ;

/* ���������� ������ */
extern ss3CAMERA SS3_RndCam;

/* ��������� ������������� */
extern DBL
  SS3_RndWs, SS3_RndHs,
  SS3_RndWp, SS3_RndHp,
  SS3_RndProjDist;

extern MATR
  SS3_RndMatrWorld,
  SS3_RndMatrView,
  SS3_RndMatrProjection,
  SS3_RndMatrWorldViewProj;

/* ������� �������������� �� ������� ������� ��������� � ���� */
POINT SS3_RndWorldToScreen( VEC P );

/* ������� �������� ��������������� ������� */
BOOL SS3_RndGObjLoad( ss3GOBJ *GObj, CHAR *FileName );

/* ������� ������������ ��������������� ������� */
VOID SS3_RndGObjFree( ss3GOBJ *GObj );

/* ������� ��������� ��������������� ������� */
VOID SS3_RndGObjDraw( ss3GOBJ *GObj, HDC hDC );

#endif