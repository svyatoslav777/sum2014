/* FILENAME: IMAGE.H
 * PROGRAMMER: SS3
 * PURPOSE: Image handle declaration module.
 * LAST UPDATE: 07.06.2014
 */

#ifndef __IMAGE_H_
#define __IMAGE_H_

#include "def.h"

/* ��������� �������� ����������� */
typedef struct tagIMAGE
{
  INT W, H;
  HBITMAP hBm;
  HDC hDC;
  DWORD *Bits;
} IMAGE;

/* ������� �������� ����������� */
BOOL ImageLoad( IMAGE *Img, CHAR *FileName );

/* ������� ������������ ������ ��-��� ����������� */
VOID ImageFree( IMAGE *Img );

/* ������� ��������� ����� ����� ����������� */
DWORD ImageGetP( IMAGE *Img, INT X, INT Y );

/* ������� ��������� ����������� */
VOID ImageDraw( IMAGE *Img, HDC hDC, INT X, INT Y, INT LogOp );

#endif