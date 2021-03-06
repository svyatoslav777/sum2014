/* FILENAME: ANIM.H
 * PROGRAMMER: SS3
 * PURPOSE: Animation system main declaration module.
 * LAST UPDATE: 07.06.2014
 */

#ifndef __ANIM_H_
#define __ANIM_H_

#include "image.h"

/* ������������ ���������� ��������� */
#define SS3_MAX_UNITS 3000

typedef struct tagss3UNIT ss3UNIT;

typedef struct tagss3ANIM
{
  HWND hWnd;
  INT W, H;
  HBITMAP hBmFrame;
  HDC hDC;

  ss3UNIT *Units[SS3_MAX_UNITS]; 
  INT NumOfUnits;

  DBL
    Time,            /* ����� � �������� �� ������ �������� */
    GlobalTime,      /* ����� -"-, �� ��� ����� */
    DeltaTime,       /* ����������� ����� � �������� */
    GlobalDeltaTime, /* ����������� ����� � �������� ��� ����� */
    FPS;             /* ���������� ������ � ������� */
  BOOL
    IsPause;

  BYTE
    Keys[256],
    KeysOld[256],
    KeysClick[256];
  INT
    MsDeltaX, MsDeltaY,
    MsX, MsY,
    MsWheel;
  BYTE
    JButs[32],
    JButsOld[32],
    JButsClick[32],
    JPOV;
  DBL
    JX, JY, JZ, JR, JU;
} ss3ANIM;

#define SS3_UNIT_BASE_FIELDS \
  INT Size;                                          \
  VOID (*Init)( ss3UNIT *Unit, ss3ANIM *Ani );       \
  VOID (*Close)( ss3UNIT *Unit, ss3ANIM *Ani );      \
  VOID (*Response)( ss3UNIT *Unit, ss3ANIM *Ani );   \
  VOID (*Render)( ss3UNIT *Unit, ss3ANIM *Ani )

struct tagss3UNIT
{
  SS3_UNIT_BASE_FIELDS;
};

/* ������� ������������� �������� */
VOID SS3_AnimInit( HWND hWnd );

/* ������� ��������������� �������� */
VOID SS3_AnimClose( VOID );

/* ������� ��������� ��������� ������� ������� ������ */
VOID SS3_AnimResize( INT W, INT H );

/* ������� ���������� ����� �������� */
VOID SS3_AnimRender( VOID );

/* ������� ������ ����� �������� */
VOID SS3_AnimCopyFrame( VOID );

VOID SS3_AnimFlipFullScreen( VOID );

/* ������� ��������� ����� �������� */
VOID SS3_AnimSetPause( BOOL NewPauseFlag );

/* ������� ���������� � ������� ������� �������� */
VOID SS3_AnimAddUnit( ss3UNIT *Unit );

/* ������� �������� ������� �������� */
ss3UNIT * SS3_AnimUnitCreate( INT Size );

#endif