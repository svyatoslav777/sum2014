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

BOOL SS3_RndGObjLoad( ss3GOBJ *GObj, CHAR *FileName );

VOID SS3_RndGObjFree( ss3GOBJ *GObj );

VOID SS3_RndGObjDraw( ss3GOBJ *GObj, HDC hDC );

typedef struct tagss3UV
{
  FLT U, V; /* ���������� ���������� ��������� */
} ss3UV;

/* ������� ������������� ���������� ��������� */
__inline ss3UV SS3_UVSet( FLT U, FLT V )
{
  ss3UV uv;

  uv.U = U;
  uv.V = V;
  return uv;
}

/* ��� ������������� ������� */
typedef struct tagss3VERTEX
{
  VEC P;    /* ���������� */
  ss3UV T;  /* ���������� ���������� */
  VEC N;    /* ������� */
  COLOR C;  /* ���� */
} ss3VERTEX;


/* ��� ��������� - ����� ������������� ��� ���������� ����� ������ */
typedef enum tagss3PRIM_TYPE
{
  SS3_PRIM_TRIMESH, SS3_PRIM_GRID
} ss3PRIM_TYPE;

/* ��� �������� ��������� */
typedef struct tagss3PRIM
{
  ss3PRIM_TYPE Type; /* ��� ��������� */
  INT
    NumOfV,     /* ���������� ������ */
    NumOfI,     /* ���������� �������� */
    GW, GH,     /* ������ ����� */
    Mtl,        /* ����� ��������� */
    Size;       /* ������ ���������� ������ � ������ */
  ss3VERTEX *V; /* ������ ������ */
  INT *I;       /* ������ �������� */

  /* ������ ��� ������ � OpenGL */
  INT
    Buffers[2],    /* ����� ������ � �������� */
    VertexBuffer;  /* ����� �������� ������ */
} ss3PRIM;

/* ���� ��-��������� */
extern COLOR SS3_DefaultColor;

/* ������� �������� ��������� */
BOOL SS3_PrimCreate( ss3PRIM *P, ss3PRIM_TYPE Type,
       INT NumOfV_GW, INT NumOfI_GH );

/* ������� �������� ����� */
BOOL SS3_PrimCreateSphere( ss3PRIM *P,
       VEC C, FLT R, INT M, INT N );

/* ������� �������� ��������� */
VOID SS3_PrimFree( ss3PRIM *P );

/* ������� ��������� ��������� */
VOID SS3_PrimDraw( ss3PRIM *P );

/* ������������ ����� ����� */
#define MAX_STR 300

/* ��� ������������� ��������� */
typedef struct tagss3MATERIAL
{
  VEC Ka, Kd, Ks;  /* ������������ ��������� */
  FLT Phong;       /* ����������� ����� */
  FLT Trans;       /* ����������� ������������ */
  CHAR
    Name[MAX_STR], /* ��� ��������� */
    MapD[MAX_STR]; /* ��� �������� */
  INT TexNo;       /* ������������� �������� � OpenGL */
} ss3MATERIAL;

/* �������������� ������ - ����� ���������� */
typedef struct tagss3GEOM
{
  INT NumOfPrims, NumOfMtls; /* ������� �������� */
  ss3MATERIAL *Mtls;         /* ������� ���������� */
  ss3PRIM *Prims;            /* ������ ���������� */
} ss3GEOM;

/* ������� ���������� ��������� � ������� */
INT SS3_GeomAddMaterial( ss3GEOM *G,
                         ss3MATERIAL *Mtl );

/* ������� ���������� ��������� � ������� */
INT SS3_GeomAddPrim( ss3GEOM *G, ss3PRIM *Prim );

/* ������� ������������ ��������������� ������� */
VOID SS3_GeomFree( ss3GEOM *G );

/* ������� ��������� */
VOID SS3_GeomDraw( ss3GEOM *G );

BOOL SS3_GeomLoad( ss3GEOM *G, CHAR *FileName );

#endif