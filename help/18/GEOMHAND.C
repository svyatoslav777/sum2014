/* FILENAME: GEOMHAND.C
 * PROGRAMMER: VG4
 * PURPOSE: Geometry object handle functions.
 * LAST UPDATE: 14.06.2014
 */

#include <stdlib.h>

#include "anim.h"

/* ������� ���������� ��������� � �������.
 * ���������:
 *   - �������������� ������:
 *       vg4GEOM *G;
 *   - ����������� ��������:
 *       vg4MATERIAL *Mtl;
 * ������������ ��������:
 *   (INT) ����� ������������ ��������� ��� -1
 *         ��� ������.
 */
INT VG4_GeomAddMaterial( vg4GEOM *G, vg4MATERIAL *Mtl )
{
  INT i;
  vg4MATERIAL *M;

  /* ���� �������� � ���������� */
  for (i = 0; i < G->NumOfMtls; i++)
    if (strcmp(G->Mtls[i].Name, Mtl->Name)== 0)
    {
      G->Mtls[i] = *Mtl;
      return i;
    }

  if ((M = malloc(sizeof(vg4MATERIAL) * (G->NumOfMtls + 1))) == NULL)
    return -1;
  if (G->Mtls != NULL)
  {
    /* �������� ������ ������ */
    memcpy(M, G->Mtls, sizeof(vg4MATERIAL) * G->NumOfMtls);
    /* ����������� ������ */
    free(G->Mtls);
  }
  /* ��������� */
  G->Mtls = M;
  M[G->NumOfMtls] = *Mtl;
  return G->NumOfMtls++;
} /* End of 'VG4_GeomAddMaterial' function */

/* ������� ���������� ��������� � �������.
 * ���������:
 *   - �������������� ������:
 *       vg4GEOM *G;
 *   - ����������� ��������:
 *       vg4PRIM *Prim;
 * ������������ ��������:
 *   (INT) ����� ������������ ��������� ��� -1
 *         ��� ������.
 */
INT VG4_GeomAddPrim( vg4GEOM *G, vg4PRIM *Prim )
{
  vg4PRIM *P;

  if ((P = malloc(sizeof(vg4PRIM) * (G->NumOfPrims + 1))) == NULL)
    return -1;
  if (G->Prims != NULL)
  {
    /* �������� ������ ������ */
    memcpy(P, G->Prims, sizeof(vg4PRIM) * G->NumOfPrims);
    /* ����������� ������ */
    free(G->Prims);
  }
  /* ��������� */
  G->Prims = P;
  P[G->NumOfPrims] = *Prim;
  return G->NumOfPrims++;
} /* End of 'VG4_GeomAddPrim' function */

/* ������� ������������.
 * ���������:
 *   - �������������� ������:
 *       vg4GEOM *G;
 * ������������ ��������: ���.
 */
VOID VG4_GeomFree( vg4GEOM *G )
{
  INT i;

  for (i = 0; i < G->NumOfPrims; i++)
    VG4_PrimFree(G->Prims + i);
  free(G->Prims);
  for (i = 0; i < G->NumOfMtls; i++)
    glDeleteTextures(1, &G->Mtls[i].TexNo);
  free(G->Mtls);
  memset(G, 0, sizeof(vg4GEOM));
} /* End of 'VG4_GeomFree' function */

/* ������� ���������.
 * ���������:
 *   - �������������� ������:
 *       vg4GEOM *G;
 * ������������ ��������: ���.
 */
VOID VG4_GeomDraw( vg4GEOM *G )
{
  INT i, loc;
  MATR WVP, MatrWorldInvTrans;
  VEC V;

  /* ��������� ������� �������������� */
  WVP = MatrMulMatr(VG4_Anim.MatrWorld,
    MatrMulMatr(VG4_Anim.MatrView, VG4_Anim.MatrProjection));
  MatrWorldInvTrans = MatrTranspose(MatrInverse(VG4_Anim.MatrWorld));

  /* ����� ��������� �������� ������ ���������� */
  glUseProgram(VG4_ShaderProg);
  loc = glGetUniformLocation(VG4_ShaderProg, "MatrWVP");
  if (loc != -1)
    glUniformMatrix4fv(loc, 1, FALSE, WVP.A[0]);

  loc = glGetUniformLocation(VG4_ShaderProg, "MatrWorldInverseTranspose");
  if (loc != -1)
    glUniformMatrix4fv(loc, 1, FALSE, MatrWorldInvTrans.A[0]);

  loc = glGetUniformLocation(VG4_ShaderProg, "MatrWorld");
  if (loc != -1)
    glUniformMatrix4fv(loc, 1, FALSE, VG4_Anim.MatrWorld.A[0]);

  loc = glGetUniformLocation(VG4_ShaderProg, "MatrView");
  if (loc != -1)
    glUniformMatrix4fv(loc, 1, FALSE, VG4_Anim.MatrView.A[0]);

  loc = glGetUniformLocation(VG4_ShaderProg, "Time");
  if (loc != -1)
    glUniform1f(loc, VG4_Anim.Time);

  V = VecSet(-VG4_Anim.MatrView.A[0][2],
             -VG4_Anim.MatrView.A[1][2],
             -VG4_Anim.MatrView.A[2][2]);
  loc = glGetUniformLocation(VG4_ShaderProg, "ViewDir");
  if (loc != -1)
    glUniform3fv(loc, 1, &V.X);
  V = VecSet(VG4_Anim.MatrView.A[3][0],
             VG4_Anim.MatrView.A[3][1],
             VG4_Anim.MatrView.A[3][2]);
  loc = glGetUniformLocation(VG4_ShaderProg, "ViewPos");
  if (loc != -1)
    glUniform3fv(loc, 1, &V.X);


  loc = glGetUniformLocation(VG4_ShaderProg, "NumOfParts");
  if (loc != -1)
    glUniform1f(loc, G->NumOfPrims);
  for (i = 0; i < G->NumOfPrims; i++)
  {
    INT mtl = G->Prims[i].Mtl;

    loc = glGetUniformLocation(VG4_ShaderProg, "PartNo");
    if (loc != -1)
      glUniform1f(loc, i);

    /* �������������� �������� */
    if (G->Mtls != NULL && mtl >= 0 && mtl < G->NumOfMtls)
    {
      INT loc;

      if (G->Mtls[mtl].TexNo == 0 && G->Mtls[mtl].MapD[0] != 0)
      {
        INT j;
        IMAGE Img;
                       
        ImageLoad(&Img, G->Mtls[mtl].MapD);

        /* �������� ��������� ����� �������� */
        glGenTextures(1, &G->Mtls[mtl].TexNo);
        /* ������ �� �������� */
        glBindTexture(GL_TEXTURE_2D, G->Mtls[mtl].TexNo);
        for (j = 0; j < Img.W * Img.H; j++)
          Img.Bits[j] |= 0xFF000000;
        /* ���������� �������� � ����������� */
        gluBuild2DMipmaps(GL_TEXTURE_2D, 4, Img.W, Img.H,
          GL_BGRA_EXT, GL_UNSIGNED_BYTE, Img.Bits);

        /* ��������� ������ */
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

        glBindTexture(GL_TEXTURE_2D, 0);
      }
      /* �������� ��������� */
      if (G->Mtls[mtl].TexNo != 0)
      {
        loc = glGetUniformLocation(VG4_ShaderProg, "IsTextureUsed");
        if (loc != -1)
          glUniform1f(loc, 1);
        loc = glGetUniformLocation(VG4_ShaderProg, "DrawTexture");
        if (loc != -1)
          glUniform1i(loc, 0);
        //glEnable(GL_TEXTURE_2D);
        glActiveTexture(GL_TEXTURE0);
        glBindTexture(GL_TEXTURE_2D, G->Mtls[mtl].TexNo);
        //glActiveTexture(GL_TEXTURE1);
        //glBindTexture(GL_TEXTURE_2D, G->Mtls[mtl].TexNo);
      }
      else
      {
        loc = glGetUniformLocation(VG4_ShaderProg, "IsTextureUsed");
        if (loc != -1)
          glUniform1f(loc, 0);
      }
      loc = glGetUniformLocation(VG4_ShaderProg, "Ka");
      if (loc != -1)
        glUniform3fv(loc, 1, &G->Mtls[mtl].Ka.X);
      loc = glGetUniformLocation(VG4_ShaderProg, "Kd");
      if (loc != -1)
        glUniform3fv(loc, 1, &G->Mtls[mtl].Kd.X);
      loc = glGetUniformLocation(VG4_ShaderProg, "Ks");
      if (loc != -1)
        glUniform3fv(loc, 1, &G->Mtls[mtl].Ks.X);
      loc = glGetUniformLocation(VG4_ShaderProg, "Phong");
      if (loc != -1)
        glUniform1f(loc, G->Mtls[mtl].Phong);
      loc = glGetUniformLocation(VG4_ShaderProg, "Trans");
      if (loc != -1)
        glUniform1f(loc, G->Mtls[mtl].Trans);
    }
    VG4_PrimDraw(G->Prims + i);
    glDisable(GL_TEXTURE_2D);
    glBindTexture(GL_TEXTURE_2D, 0);
  }
} /* End of 'VG4_GeomDraw' function */

/* ������� �������������� ������.
 * ���������:
 *   - �������������� ������:
 *       vg4GEOM *G;
 *   - ������� ��������������:
 *       MATR M;
 * ������������ ��������: ���.
 */
VOID VG4_GeomTransform( vg4GEOM *G, MATR M )
{
  INT i, j;
  MATR InvM = MatrTranspose(MatrInverse(M));

  InvM.A[3][0] = InvM.A[3][1] = InvM.A[3][2] = 0;

  for (i = 0; i < G->NumOfPrims; i++)
    for (j = 0; j < G->Prims[i].NumOfV; j++)
    {
      G->Prims[i].V[j].P = VecMulMatr(G->Prims[i].V[j].P, M);
      G->Prims[i].V[j].N = VecMulMatr(G->Prims[i].V[j].N, InvM);
    }
} /* End of 'VG4_GeomTransform' function */

/* END OF 'GEOMHAND.C' FILE */
