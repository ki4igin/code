/*
 * Academic License - for use in teaching, academic research, and meeting
 * course requirements at degree granting institutions only.  Not for
 * government, commercial, or other organizational use.
 * File: ParalaxCalc_fixpt.c
 *
 * MATLAB Coder version            : 5.1
 * C/C++ source code generated on  : 24-Feb-2021 21:34:46
 */

/* Include Files */
#include "ParalaxCalc_fixpt.h"
#include "ParalaxCalc_fixpt_types.h"
#include <string.h>

/* Variable Definitions */
static short FI_SIN_COS_LUT[256];
static short b_FI_SIN_COS_LUT[256];
static unsigned short ATAN_UFRAC_LUT[257];
static bool isInitialized_ParalaxCalc = false;

/* Function Declarations */
static bool MultiWord2Bool(const unsigned int u[], int n);
static int MultiWord2sLong(const unsigned int u[]);
static unsigned int MultiWord2uLong(const unsigned int u[]);
static void MultiWordAdd(const unsigned int u1[], const unsigned int u2[],
  unsigned int y[], int n);
static void MultiWordIor(const unsigned int u1[], const unsigned int u2[],
  unsigned int y[], int n);
static void MultiWordNeg(const unsigned int u1[], unsigned int y[], int n);
static void MultiWordSetSignedMax(unsigned int y[], int n);
static void MultiWordSetSignedMin(unsigned int y[], int n);
static void MultiWordSignedWrap(const unsigned int u1[], int n1, unsigned int n2,
  unsigned int y[]);
static void MultiWordUnsignedWrap(const unsigned int u1[], int n1, unsigned int
  n2, unsigned int y[]);
static void atan2_fi_lut_private_init(void);
static short b_atan2(unsigned int y, const int64m_T x);
static void cos_init(void);
static unsigned int div_nzp_repeat_u32_sat(unsigned int numerator, unsigned int
  denominator, unsigned int nRepeatSub);
static int div_repeat_s32_sat(int numerator, int denominator, unsigned int
  nRepeatSub);
static int mul_ssu32_loSR(int a, unsigned int b, unsigned int aShift);
static unsigned int mul_u32_loSR(unsigned int a, unsigned int b, unsigned int
  aShift);
static void mul_wide_su32(int in0, unsigned int in1, unsigned int *ptrOutBitsHi,
  unsigned int *ptrOutBitsLo);
static void mul_wide_u32(unsigned int in0, unsigned int in1, unsigned int
  *ptrOutBitsHi, unsigned int *ptrOutBitsLo);
static void sLong2MultiWord(int u, unsigned int y[], int n);
static void sMultiWord2MultiWord(const unsigned int u1[], int n1, unsigned int
  y[], int n);
static void sMultiWord2sMultiWordSat(const unsigned int u1[], int n1, unsigned
  int y[], int n);
static unsigned int sMultiWord2uLongSat(const unsigned int u1[], int n1);
static void sMultiWord2uMultiWordSat(const unsigned int u1[], int n1, unsigned
  int y[], int n);
static int sMultiWordCmp(const unsigned int u1[], const unsigned int u2[], int n);
static void sMultiWordDivFloor(const unsigned int u1[], int n1, const unsigned
  int u2[], int n2, unsigned int b_y1[], int m1, unsigned int y2[], int m2,
  unsigned int t1[], int l1, unsigned int t2[], int l2);
static bool sMultiWordEq(const unsigned int u1[], const unsigned int u2[], int n);
static bool sMultiWordGe(const unsigned int u1[], const unsigned int u2[], int n);
static bool sMultiWordGt(const unsigned int u1[], const unsigned int u2[], int n);
static bool sMultiWordLe(const unsigned int u1[], const unsigned int u2[], int n);
static bool sMultiWordLt(const unsigned int u1[], const unsigned int u2[], int n);
static void sMultiWordMul(const unsigned int u1[], int n1, const unsigned int
  u2[], int n2, unsigned int y[], int n);
static void sMultiWordShr(const unsigned int u1[], int n1, unsigned int n2,
  unsigned int y[], int n);
static void sin_init(void);
static void ssuMultiWordMul(const unsigned int u1[], int n1, const unsigned int
  u2[], int n2, unsigned int y[], int n);
static void uLong2MultiWord(unsigned int u, unsigned int y[], int n);
static void uMultiWord2MultiWord(const unsigned int u1[], int n1, unsigned int
  y[], int n);
static int uMultiWordDiv(unsigned int a[], int na, unsigned int b[], int nb,
  unsigned int q[], int nq, unsigned int r[], int nr);
static void uMultiWordInc(unsigned int y[], int n);
static void uMultiWordMul(const unsigned int u1[], int n1, const unsigned int
  u2[], int n2, unsigned int y[], int n);
static void uMultiWordShl(const unsigned int u1[], int n1, unsigned int n2,
  unsigned int y[], int n);
static void uMultiWordShr(const unsigned int u1[], int n1, unsigned int n2,
  unsigned int y[], int n);

/* Function Definitions */
/*
 * Arguments    : const unsigned int u[]
 *                int n
 * Return Type  : bool
 */
static bool MultiWord2Bool(const unsigned int u[], int n)
{
  int i;
  bool y;
  y = false;
  i = 0;
  while ((i < n) && (!y)) {
    if (u[i] != 0U) {
      y = true;
    }

    i++;
  }

  return y;
}

/*
 * Arguments    : const unsigned int u[]
 * Return Type  : int
 */
static int MultiWord2sLong(const unsigned int u[])
{
  return (int)u[0];
}

/*
 * Arguments    : const unsigned int u[]
 * Return Type  : unsigned int
 */
static unsigned int MultiWord2uLong(const unsigned int u[])
{
  return u[0];
}

/*
 * Arguments    : const unsigned int u1[]
 *                const unsigned int u2[]
 *                unsigned int y[]
 *                int n
 * Return Type  : void
 */
static void MultiWordAdd(const unsigned int u1[], const unsigned int u2[],
  unsigned int y[], int n)
{
  int carry = 0;
  int i;
  unsigned int u1i;
  unsigned int yi;
  for (i = 0; i < n; i++) {
    u1i = u1[i];
    yi = (u1i + u2[i]) + carry;
    y[i] = yi;
    if ((unsigned int)carry != 0U) {
      carry = (yi <= u1i);
    } else {
      carry = (yi < u1i);
    }
  }
}

/*
 * Arguments    : const unsigned int u1[]
 *                const unsigned int u2[]
 *                unsigned int y[]
 *                int n
 * Return Type  : void
 */
static void MultiWordIor(const unsigned int u1[], const unsigned int u2[],
  unsigned int y[], int n)
{
  int i;
  for (i = 0; i < n; i++) {
    y[i] = u1[i] | u2[i];
  }
}

/*
 * Arguments    : const unsigned int u1[]
 *                unsigned int y[]
 *                int n
 * Return Type  : void
 */
static void MultiWordNeg(const unsigned int u1[], unsigned int y[], int n)
{
  int carry = 1;
  int i;
  unsigned int yi;
  for (i = 0; i < n; i++) {
    yi = ~u1[i] + carry;
    y[i] = yi;
    carry = (yi < (unsigned int)carry);
  }
}

/*
 * Arguments    : unsigned int y[]
 *                int n
 * Return Type  : void
 */
static void MultiWordSetSignedMax(unsigned int y[], int n)
{
  int i;
  int n1;
  n1 = n - 1;
  for (i = 0; i < n1; i++) {
    y[i] = MAX_uint32_T;
  }

  y[n - 1] = 2147483647U;
}

/*
 * Arguments    : unsigned int y[]
 *                int n
 * Return Type  : void
 */
static void MultiWordSetSignedMin(unsigned int y[], int n)
{
  int n1;
  n1 = n - 1;
  if (0 <= n1 - 1) {
    memset(&y[0], 0, n1 * sizeof(unsigned int));
  }

  y[n - 1] = 2147483648U;
}

/*
 * Arguments    : const unsigned int u1[]
 *                int n1
 *                unsigned int n2
 *                unsigned int y[]
 * Return Type  : void
 */
static void MultiWordSignedWrap(const unsigned int u1[], int n1, unsigned int n2,
  unsigned int y[])
{
  unsigned int mask;
  int n1m1;
  unsigned int ys;
  n1m1 = n1 - 1;
  if (0 <= n1m1 - 1) {
    memcpy(&y[0], &u1[0], n1m1 * sizeof(unsigned int));
  }

  mask = 1U << (31U - n2);
  if ((u1[n1 - 1] & mask) != 0U) {
    ys = MAX_uint32_T;
  } else {
    ys = 0U;
  }

  mask = (mask << 1U) - 1U;
  y[n1 - 1] = (u1[n1 - 1] & mask) | (~mask & ys);
}

/*
 * Arguments    : const unsigned int u1[]
 *                int n1
 *                unsigned int n2
 *                unsigned int y[]
 * Return Type  : void
 */
static void MultiWordUnsignedWrap(const unsigned int u1[], int n1, unsigned int
  n2, unsigned int y[])
{
  int n1m1;
  n1m1 = n1 - 1;
  if (0 <= n1m1 - 1) {
    memcpy(&y[0], &u1[0], n1m1 * sizeof(unsigned int));
  }

  y[n1 - 1] = u1[n1 - 1] & ((1U << (32U - n2)) - 1U);
}

/*
 * Arguments    : void
 * Return Type  : void
 */
static void atan2_fi_lut_private_init(void)
{
  static const unsigned short uv[257] = { 0U, 256U, 512U, 768U, 1024U, 1280U,
    1536U, 1792U, 2047U, 2303U, 2559U, 2814U, 3070U, 3325U, 3580U, 3836U, 4091U,
    4346U, 4600U, 4855U, 5110U, 5364U, 5618U, 5872U, 6126U, 6380U, 6633U, 6887U,
    7140U, 7392U, 7645U, 7898U, 8150U, 8402U, 8653U, 8905U, 9156U, 9407U, 9657U,
    9908U, 10158U, 10408U, 10657U, 10906U, 11155U, 11403U, 11652U, 11899U,
    12147U, 12394U, 12641U, 12887U, 13133U, 13379U, 13624U, 13869U, 14114U,
    14358U, 14601U, 14845U, 15088U, 15330U, 15572U, 15814U, 16055U, 16296U,
    16536U, 16776U, 17015U, 17254U, 17492U, 17730U, 17968U, 18205U, 18441U,
    18677U, 18913U, 19148U, 19382U, 19616U, 19850U, 20083U, 20315U, 20547U,
    20779U, 21009U, 21240U, 21469U, 21699U, 21927U, 22156U, 22383U, 22610U,
    22836U, 23062U, 23288U, 23512U, 23737U, 23960U, 24183U, 24406U, 24627U,
    24849U, 25069U, 25289U, 25509U, 25727U, 25946U, 26163U, 26380U, 26597U,
    26813U, 27028U, 27242U, 27456U, 27670U, 27882U, 28094U, 28306U, 28517U,
    28727U, 28936U, 29145U, 29354U, 29561U, 29768U, 29975U, 30180U, 30386U,
    30590U, 30794U, 30997U, 31200U, 31402U, 31603U, 31803U, 32003U, 32203U,
    32401U, 32600U, 32797U, 32994U, 33190U, 33385U, 33580U, 33774U, 33968U,
    34160U, 34353U, 34544U, 34735U, 34925U, 35115U, 35304U, 35492U, 35680U,
    35867U, 36053U, 36239U, 36424U, 36608U, 36792U, 36975U, 37158U, 37340U,
    37521U, 37701U, 37881U, 38060U, 38239U, 38417U, 38594U, 38771U, 38947U,
    39123U, 39297U, 39472U, 39645U, 39818U, 39990U, 40162U, 40333U, 40503U,
    40673U, 40842U, 41010U, 41178U, 41346U, 41512U, 41678U, 41844U, 42008U,
    42172U, 42336U, 42499U, 42661U, 42823U, 42984U, 43145U, 43304U, 43464U,
    43622U, 43780U, 43938U, 44095U, 44251U, 44407U, 44562U, 44716U, 44870U,
    45024U, 45176U, 45328U, 45480U, 45631U, 45781U, 45931U, 46080U, 46229U,
    46377U, 46525U, 46672U, 46818U, 46964U, 47109U, 47254U, 47398U, 47542U,
    47685U, 47827U, 47969U, 48111U, 48251U, 48392U, 48531U, 48671U, 48809U,
    48947U, 49085U, 49222U, 49359U, 49495U, 49630U, 49765U, 49899U, 50033U,
    50167U, 50299U, 50432U, 50563U, 50695U, 50826U, 50956U, 51086U, 51215U,
    51344U, 51472U };

  memcpy(&ATAN_UFRAC_LUT[0], &uv[0], 257U * sizeof(unsigned short));
}

/*
 * Arguments    : unsigned int y
 *                const int64m_T x
 * Return Type  : short
 */
static short b_atan2(unsigned int y, const int64m_T x)
{
  static const int64m_T r = { { 0U, 0U }/* chunks */
  };

  int64m_T negThisX;
  int64m_T r1;
  int64m_T r10;
  int64m_T r13;
  int64m_T r14;
  int64m_T r15;
  int64m_T r16;
  int64m_T r17;
  int64m_T r2;
  int64m_T r3;
  int64m_T r4;
  int64m_T r5;
  int64m_T r7;
  int64m_T r9;
  int96m_T r6;
  int96m_T r8;
  uint64m_T r11;
  uint64m_T r12;
  unsigned int u;
  short theta;
  unsigned short xfi;
  unsigned char slice_temp;
  bool guard1 = false;
  if (y > 0U) {
    r1 = x;
    uMultiWordShl((unsigned int *)&x.chunks[0U], 2, 1U, (unsigned int *)
                  &r2.chunks[0U], 2);
    uLong2MultiWord(y, (unsigned int *)&r1.chunks[0U], 2);
    if (sMultiWordEq((unsigned int *)&r2.chunks[0U], (unsigned int *)&r1.chunks
                     [0U], 2)) {
      theta = 6434;
    } else {
      guard1 = false;
      if (sMultiWordGe((unsigned int *)&x.chunks[0U], (unsigned int *)&r.chunks
                       [0U], 2)) {
        uLong2MultiWord(y, (unsigned int *)&r3.chunks[0U], 2);
        r5 = x;
        uMultiWordShl((unsigned int *)&x.chunks[0U], 2, 1U, (unsigned int *)
                      &r7.chunks[0U], 2);
        if (sMultiWordLe((unsigned int *)&r3.chunks[0U], (unsigned int *)
                         &r7.chunks[0U], 2)) {
          if (sMultiWordEq((unsigned int *)&x.chunks[0U], (unsigned int *)
                           &r.chunks[0U], 2)) {
            xfi = MAX_uint16_T;
          } else {
            uLong2MultiWord(y, (unsigned int *)&r11.chunks[0U], 2);
            uMultiWordShl((unsigned int *)&r11.chunks[0U], 2, 15U, (unsigned int
              *)&r12.chunks[0U], 2);
            uMultiWord2MultiWord((unsigned int *)&r12.chunks[0U], 2, (unsigned
              int *)&r13.chunks[0U], 2);
            sMultiWordDivFloor((unsigned int *)&r13.chunks[0U], 2, (unsigned int
              *)&x.chunks[0U], 2, (unsigned int *)&r6.chunks[0U], 3, (unsigned
              int *)&r14.chunks[0U], 2, (unsigned int *)&r4.chunks[0U], 2,
                               (unsigned int *)&r15.chunks[0U], 2);
            u = sMultiWord2uLongSat((unsigned int *)&r6.chunks[0U], 3);
            if (u > 65535U) {
              u = 65535U;
            }

            xfi = (unsigned short)u;
          }
        } else {
          r10 = x;
          uMultiWordShl((unsigned int *)&x.chunks[0U], 2, 17U, (unsigned int *)
                        &r5.chunks[0U], 2);
          uLong2MultiWord(y, (unsigned int *)&r10.chunks[0U], 2);
          sMultiWordDivFloor((unsigned int *)&r5.chunks[0U], 2, (unsigned int *)
                             &r10.chunks[0U], 2, (unsigned int *)&r6.chunks[0U],
                             3, (unsigned int *)&r4.chunks[0U], 2, (unsigned int
            *)&r9.chunks[0U], 2, (unsigned int *)&r13.chunks[0U], 2);
          u = sMultiWord2uLongSat((unsigned int *)&r6.chunks[0U], 3);
          if (u > 65535U) {
            u = 65535U;
          }

          xfi = (unsigned short)u;
        }

        guard1 = true;
      } else {
        r1 = x;
        MultiWordNeg((unsigned int *)&x.chunks[0U], (unsigned int *)&r4.chunks
                     [0U], 2);
        sMultiWord2MultiWord((unsigned int *)&r4.chunks[0U], 2, (unsigned int *)
                             &r6.chunks[0U], 3);
        uMultiWordShl((unsigned int *)&r6.chunks[0U], 3, 31U, (unsigned int *)
                      &r8.chunks[0U], 3);
        sMultiWord2sMultiWordSat((unsigned int *)&r8.chunks[0U], 3, (unsigned
          int *)&r9.chunks[0U], 2);
        sMultiWordShr((unsigned int *)&r9.chunks[0U], 2, 31U, (unsigned int *)
                      &negThisX.chunks[0U], 2);
        uLong2MultiWord(y, (unsigned int *)&r9.chunks[0U], 2);
        uMultiWordShl((unsigned int *)&negThisX.chunks[0U], 2, 1U, (unsigned int
          *)&r4.chunks[0U], 2);
        if (sMultiWordEq((unsigned int *)&r9.chunks[0U], (unsigned int *)
                         &r4.chunks[0U], 2)) {
          theta = 19302;
        } else {
          uLong2MultiWord(y, (unsigned int *)&r1.chunks[0U], 2);
          uMultiWordShl((unsigned int *)&negThisX.chunks[0U], 2, 1U, (unsigned
            int *)&r13.chunks[0U], 2);
          if (sMultiWordLt((unsigned int *)&r1.chunks[0U], (unsigned int *)
                           &r13.chunks[0U], 2)) {
            if (sMultiWordEq((unsigned int *)&negThisX.chunks[0U], (unsigned int
                  *)&r.chunks[0U], 2)) {
              xfi = MAX_uint16_T;
            } else {
              uLong2MultiWord(y, (unsigned int *)&r11.chunks[0U], 2);
              uMultiWordShl((unsigned int *)&r11.chunks[0U], 2, 15U, (unsigned
                int *)&r12.chunks[0U], 2);
              uMultiWord2MultiWord((unsigned int *)&r12.chunks[0U], 2, (unsigned
                int *)&r3.chunks[0U], 2);
              sMultiWordDivFloor((unsigned int *)&r3.chunks[0U], 2, (unsigned
                int *)&negThisX.chunks[0U], 2, (unsigned int *)&r6.chunks[0U], 3,
                                 (unsigned int *)&r7.chunks[0U], 2, (unsigned
                int *)&r5.chunks[0U], 2, (unsigned int *)&r10.chunks[0U], 2);
              u = sMultiWord2uLongSat((unsigned int *)&r6.chunks[0U], 3);
              if (u > 65535U) {
                u = 65535U;
              }

              xfi = (unsigned short)u;
            }
          } else {
            uMultiWordShl((unsigned int *)&negThisX.chunks[0U], 2, 17U,
                          (unsigned int *)&r10.chunks[0U], 2);
            uLong2MultiWord(y, (unsigned int *)&r16.chunks[0U], 2);
            sMultiWordDivFloor((unsigned int *)&r10.chunks[0U], 2, (unsigned int
              *)&r16.chunks[0U], 2, (unsigned int *)&r8.chunks[0U], 3, (unsigned
              int *)&r3.chunks[0U], 2, (unsigned int *)&r7.chunks[0U], 2,
                               (unsigned int *)&r5.chunks[0U], 2);
            u = sMultiWord2uLongSat((unsigned int *)&r8.chunks[0U], 3);
            if (u > 65535U) {
              u = 65535U;
            }

            xfi = (unsigned short)u;
          }

          guard1 = true;
        }
      }

      if (guard1) {
        slice_temp = (unsigned char)((unsigned int)xfi >> 8);
        theta = (short)((unsigned int)(unsigned short)((((unsigned int)
          ATAN_UFRAC_LUT[slice_temp] << 14) + ((unsigned int)(unsigned short)
          (mul_u32_loSR((unsigned int)(xfi & 255), ((unsigned int)
          ATAN_UFRAC_LUT[slice_temp + 1] << 14) - ((unsigned int)ATAN_UFRAC_LUT
          [(int)((unsigned int)xfi >> 8)] << 14), 8U) >> 14) << 14)) >> 14) >> 3);
        r4 = x;
        uMultiWordShl((unsigned int *)&x.chunks[0U], 2, 1U, (unsigned int *)
                      &r14.chunks[0U], 2);
        uLong2MultiWord(y, (unsigned int *)&r4.chunks[0U], 2);
        uLong2MultiWord(y, (unsigned int *)&r15.chunks[0U], 2);
        uMultiWordShl((unsigned int *)&negThisX.chunks[0U], 2, 1U, (unsigned int
          *)&r17.chunks[0U], 2);
        if (sMultiWordGe((unsigned int *)&x.chunks[0U], (unsigned int *)
                         &r.chunks[0U], 2)) {
          if (sMultiWordLt((unsigned int *)&r14.chunks[0U], (unsigned int *)
                           &r4.chunks[0U], 2)) {
            theta = (short)(12867 - theta);
          }
        } else if (sMultiWordGt((unsigned int *)&r15.chunks[0U], (unsigned int *)
                                &r17.chunks[0U], 2)) {
          theta = (short)(theta + 12867);
        } else {
          theta = (short)(25735 - theta);
        }
      }
    }
  } else if (sMultiWordGe((unsigned int *)&x.chunks[0U], (unsigned int *)
                          &r.chunks[0U], 2)) {
    theta = 0;
  } else {
    theta = 25736;
  }

  return theta;
}

/*
 * Arguments    : void
 * Return Type  : void
 */
static void cos_init(void)
{
  static const short iv[256] = { MAX_int16_T, 32758, 32729, 32679, 32610, 32522,
    32413, 32286, 32138, 31972, 31786, 31581, 31357, 31114, 30853, 30572, 30274,
    29957, 29622, 29269, 28899, 28511, 28106, 27684, 27246, 26791, 26320, 25833,
    25330, 24812, 24279, 23732, 23170, 22595, 22006, 21403, 20788, 20160, 19520,
    18868, 18205, 17531, 16846, 16151, 15447, 14733, 14010, 13279, 12540, 11793,
    11039, 10279, 9512, 8740, 7962, 7180, 6393, 5602, 4808, 4011, 3212, 2411,
    1608, 804, 0, -804, -1608, -2411, -3212, -4011, -4808, -5602, -6393, -7180,
    -7962, -8740, -9512, -10279, -11039, -11793, -12540, -13279, -14010, -14733,
    -15447, -16151, -16846, -17531, -18205, -18868, -19520, -20160, -20788,
    -21403, -22006, -22595, -23170, -23732, -24279, -24812, -25330, -25833,
    -26320, -26791, -27246, -27684, -28106, -28511, -28899, -29269, -29622,
    -29957, -30274, -30572, -30853, -31114, -31357, -31581, -31786, -31972,
    -32138, -32286, -32413, -32522, -32610, -32679, -32729, -32758, -32767,
    -32758, -32729, -32679, -32610, -32522, -32413, -32286, -32138, -31972,
    -31786, -31581, -31357, -31114, -30853, -30572, -30274, -29957, -29622,
    -29269, -28899, -28511, -28106, -27684, -27246, -26791, -26320, -25833,
    -25330, -24812, -24279, -23732, -23170, -22595, -22006, -21403, -20788,
    -20160, -19520, -18868, -18205, -17531, -16846, -16151, -15447, -14733,
    -14010, -13279, -12540, -11793, -11039, -10279, -9512, -8740, -7962, -7180,
    -6393, -5602, -4808, -4011, -3212, -2411, -1608, -804, 0, 804, 1608, 2411,
    3212, 4011, 4808, 5602, 6393, 7180, 7962, 8740, 9512, 10279, 11039, 11793,
    12540, 13279, 14010, 14733, 15447, 16151, 16846, 17531, 18205, 18868, 19520,
    20160, 20788, 21403, 22006, 22595, 23170, 23732, 24279, 24812, 25330, 25833,
    26320, 26791, 27246, 27684, 28106, 28511, 28899, 29269, 29622, 29957, 30274,
    30572, 30853, 31114, 31357, 31581, 31786, 31972, 32138, 32286, 32413, 32522,
    32610, 32679, 32729, 32758 };

  memcpy(&FI_SIN_COS_LUT[0], &iv[0], 256U * sizeof(short));
}

/*
 * Arguments    : unsigned int numerator
 *                unsigned int denominator
 *                unsigned int nRepeatSub
 * Return Type  : unsigned int
 */
static unsigned int div_nzp_repeat_u32_sat(unsigned int numerator, unsigned int
  denominator, unsigned int nRepeatSub)
{
  unsigned int iRepeatSub;
  unsigned int quotient;
  bool numeratorExtraBit;
  bool overflow;
  overflow = false;
  quotient = numerator / denominator;
  numerator %= denominator;
  for (iRepeatSub = 0U; iRepeatSub < nRepeatSub; iRepeatSub++) {
    numeratorExtraBit = (numerator >= 2147483648U);
    numerator <<= 1U;
    overflow = (overflow || (quotient >= 2147483648U));
    quotient <<= 1U;
    if (numeratorExtraBit || (numerator >= denominator)) {
      quotient++;
      numerator -= denominator;
    }
  }

  if (overflow) {
    quotient = MAX_uint32_T;
  }

  return quotient;
}

/*
 * Arguments    : int numerator
 *                int denominator
 *                unsigned int nRepeatSub
 * Return Type  : int
 */
static int div_repeat_s32_sat(int numerator, int denominator, unsigned int
  nRepeatSub)
{
  unsigned int b_denominator;
  unsigned int b_numerator;
  int quotient;
  if (denominator == 0) {
    if (numerator >= 0) {
      quotient = MAX_int32_T;
    } else {
      quotient = MIN_int32_T;
    }
  } else {
    if (numerator < 0) {
      b_numerator = ~(unsigned int)numerator + 1U;
    } else {
      b_numerator = (unsigned int)numerator;
    }

    if (denominator < 0) {
      b_denominator = ~(unsigned int)denominator + 1U;
    } else {
      b_denominator = (unsigned int)denominator;
    }

    b_numerator = div_nzp_repeat_u32_sat(b_numerator, b_denominator, nRepeatSub);
    if ((numerator < 0) != (denominator < 0)) {
      if (b_numerator <= 2147483647U) {
        quotient = -(int)b_numerator;
      } else {
        quotient = MIN_int32_T;
      }
    } else if (b_numerator <= 2147483647U) {
      quotient = (int)b_numerator;
    } else {
      quotient = MAX_int32_T;
    }
  }

  return quotient;
}

/*
 * Arguments    : int a
 *                unsigned int b
 *                unsigned int aShift
 * Return Type  : int
 */
static int mul_ssu32_loSR(int a, unsigned int b, unsigned int aShift)
{
  unsigned int u32_chi;
  unsigned int u32_clo;
  mul_wide_su32(a, b, &u32_chi, &u32_clo);
  u32_clo = u32_chi << (32U - aShift) | u32_clo >> aShift;
  return (int)u32_clo;
}

/*
 * Arguments    : unsigned int a
 *                unsigned int b
 *                unsigned int aShift
 * Return Type  : unsigned int
 */
static unsigned int mul_u32_loSR(unsigned int a, unsigned int b, unsigned int
  aShift)
{
  unsigned int result;
  unsigned int u32_chi;
  mul_wide_u32(a, b, &u32_chi, &result);
  return u32_chi << (32U - aShift) | result >> aShift;
}

/*
 * Arguments    : int in0
 *                unsigned int in1
 *                unsigned int *ptrOutBitsHi
 *                unsigned int *ptrOutBitsLo
 * Return Type  : void
 */
static void mul_wide_su32(int in0, unsigned int in1, unsigned int *ptrOutBitsHi,
  unsigned int *ptrOutBitsLo)
{
  unsigned int absIn0;
  int in0Hi;
  int in0Lo;
  int in1Hi;
  int in1Lo;
  unsigned int outBitsLo;
  unsigned int productLoHi;
  unsigned int productLoLo;
  if (in0 < 0) {
    absIn0 = ~(unsigned int)in0 + 1U;
  } else {
    absIn0 = (unsigned int)in0;
  }

  in0Hi = (int)(absIn0 >> 16U);
  in0Lo = (int)(absIn0 & 65535U);
  in1Hi = (int)(in1 >> 16U);
  in1Lo = (int)(in1 & 65535U);
  absIn0 = (unsigned int)in0Hi * in1Lo;
  productLoHi = (unsigned int)in0Lo * in1Hi;
  productLoLo = (unsigned int)in0Lo * in1Lo;
  in0Lo = 0;
  outBitsLo = productLoLo + (productLoHi << 16U);
  if (outBitsLo < productLoLo) {
    in0Lo = 1;
  }

  productLoLo = outBitsLo;
  outBitsLo += absIn0 << 16U;
  if (outBitsLo < productLoLo) {
    in0Lo++;
  }

  absIn0 = ((in0Lo + (unsigned int)in0Hi * in1Hi) + (productLoHi >> 16U)) +
    (absIn0 >> 16U);
  if ((in1 != 0U) && (in0 < 0)) {
    absIn0 = ~absIn0;
    outBitsLo = ~outBitsLo;
    outBitsLo++;
    if (outBitsLo == 0U) {
      absIn0++;
    }
  }

  *ptrOutBitsHi = absIn0;
  *ptrOutBitsLo = outBitsLo;
}

/*
 * Arguments    : unsigned int in0
 *                unsigned int in1
 *                unsigned int *ptrOutBitsHi
 *                unsigned int *ptrOutBitsLo
 * Return Type  : void
 */
static void mul_wide_u32(unsigned int in0, unsigned int in1, unsigned int
  *ptrOutBitsHi, unsigned int *ptrOutBitsLo)
{
  int in0Hi;
  int in0Lo;
  int in1Hi;
  int in1Lo;
  unsigned int outBitsLo;
  unsigned int productHiLo;
  unsigned int productLoHi;
  unsigned int productLoLo;
  in0Hi = (int)(in0 >> 16U);
  in0Lo = (int)(in0 & 65535U);
  in1Hi = (int)(in1 >> 16U);
  in1Lo = (int)(in1 & 65535U);
  productHiLo = (unsigned int)in0Hi * in1Lo;
  productLoHi = (unsigned int)in0Lo * in1Hi;
  productLoLo = (unsigned int)in0Lo * in1Lo;
  in0Lo = 0;
  outBitsLo = productLoLo + (productLoHi << 16U);
  if (outBitsLo < productLoLo) {
    in0Lo = 1;
  }

  productLoLo = outBitsLo;
  outBitsLo += productHiLo << 16U;
  if (outBitsLo < productLoLo) {
    in0Lo++;
  }

  *ptrOutBitsHi = ((in0Lo + (unsigned int)in0Hi * in1Hi) + (productLoHi >> 16U))
    + (productHiLo >> 16U);
  *ptrOutBitsLo = outBitsLo;
}

/*
 * Arguments    : int u
 *                unsigned int y[]
 *                int n
 * Return Type  : void
 */
static void sLong2MultiWord(int u, unsigned int y[], int n)
{
  int i;
  unsigned int yi;
  y[0] = (unsigned int)u;
  if (u < 0) {
    yi = MAX_uint32_T;
  } else {
    yi = 0U;
  }

  for (i = 1; i < n; i++) {
    y[i] = yi;
  }
}

/*
 * Arguments    : const unsigned int u1[]
 *                int n1
 *                unsigned int y[]
 *                int n
 * Return Type  : void
 */
static void sMultiWord2MultiWord(const unsigned int u1[], int n1, unsigned int
  y[], int n)
{
  int i;
  int nm;
  unsigned int u1i;
  if (n1 < n) {
    nm = n1;
  } else {
    nm = n;
  }

  if (0 <= nm - 1) {
    memcpy(&y[0], &u1[0], nm * sizeof(unsigned int));
  }

  if (n > n1) {
    if ((u1[n1 - 1] & 2147483648U) != 0U) {
      u1i = MAX_uint32_T;
    } else {
      u1i = 0U;
    }

    for (i = nm; i < n; i++) {
      y[i] = u1i;
    }
  }
}

/*
 * Arguments    : const unsigned int u1[]
 *                int n1
 *                unsigned int y[]
 *                int n
 * Return Type  : void
 */
static void sMultiWord2sMultiWordSat(const unsigned int u1[], int n1, unsigned
  int y[], int n)
{
  int i;
  int nm1;
  unsigned int ys;
  bool doSaturation = false;
  nm1 = n - 1;
  if ((u1[n1 - 1] & 2147483648U) != 0U) {
    ys = MAX_uint32_T;
  } else {
    ys = 0U;
  }

  if (n1 > n) {
    doSaturation = (((u1[n1 - 1] ^ u1[n - 1]) & 2147483648U) != 0U);
    i = n1 - 1;
    while ((!doSaturation) && (i >= n)) {
      doSaturation = (u1[i] != ys);
      i--;
    }
  }

  if (doSaturation) {
    ys = ~ys;
    for (i = 0; i < nm1; i++) {
      y[i] = ys;
    }

    y[i] = ys ^ 2147483648U;
  } else {
    if (n1 < n) {
      nm1 = n1;
    } else {
      nm1 = n;
    }

    if (0 <= nm1 - 1) {
      memcpy(&y[0], &u1[0], nm1 * sizeof(unsigned int));
    }

    for (i = 0; i < nm1; i++) {
    }

    while (i < n) {
      y[i] = ys;
      i++;
    }
  }
}

/*
 * Arguments    : const unsigned int u1[]
 *                int n1
 * Return Type  : unsigned int
 */
static unsigned int sMultiWord2uLongSat(const unsigned int u1[], int n1)
{
  unsigned int ret;
  sMultiWord2uMultiWordSat(u1, n1, (unsigned int *)&ret, 1);
  return ret;
}

/*
 * Arguments    : const unsigned int u1[]
 *                int n1
 *                unsigned int y[]
 *                int n
 * Return Type  : void
 */
static void sMultiWord2uMultiWordSat(const unsigned int u1[], int n1, unsigned
  int y[], int n)
{
  int i;
  int nc;
  unsigned int ys;
  bool doSaturation;
  if ((u1[n1 - 1] & 2147483648U) != 0U) {
    ys = MAX_uint32_T;
  } else {
    ys = 0U;
  }

  doSaturation = (ys != 0U);
  i = n1 - 1;
  while ((!doSaturation) && (i >= n)) {
    doSaturation = (u1[i] != 0U);
    i--;
  }

  if (doSaturation) {
    ys = ~ys;
    for (i = 0; i < n; i++) {
      y[i] = ys;
    }
  } else {
    if (n1 < n) {
      nc = n1;
    } else {
      nc = n;
    }

    if (0 <= nc - 1) {
      memcpy(&y[0], &u1[0], nc * sizeof(unsigned int));
    }

    for (i = 0; i < nc; i++) {
    }

    while (i < n) {
      y[i] = ys;
      i++;
    }
  }
}

/*
 * Arguments    : const unsigned int u1[]
 *                const unsigned int u2[]
 *                int n
 * Return Type  : int
 */
static int sMultiWordCmp(const unsigned int u1[], const unsigned int u2[], int n)
{
  int i;
  unsigned int su1;
  unsigned int u2i;
  int y;
  su1 = u1[n - 1] & 2147483648U;
  if (su1 != (u2[n - 1] & 2147483648U)) {
    if (su1 != 0U) {
      y = -1;
    } else {
      y = 1;
    }
  } else {
    y = 0;
    i = n;
    while ((y == 0) && (i > 0)) {
      i--;
      su1 = u1[i];
      u2i = u2[i];
      if (su1 != u2i) {
        if (su1 > u2i) {
          y = 1;
        } else {
          y = -1;
        }
      }
    }
  }

  return y;
}

/*
 * Arguments    : const unsigned int u1[]
 *                int n1
 *                const unsigned int u2[]
 *                int n2
 *                unsigned int b_y1[]
 *                int m1
 *                unsigned int y2[]
 *                int m2
 *                unsigned int t1[]
 *                int l1
 *                unsigned int t2[]
 *                int l2
 * Return Type  : void
 */
static void sMultiWordDivFloor(const unsigned int u1[], int n1, const unsigned
  int u2[], int n2, unsigned int b_y1[], int m1, unsigned int y2[], int m2,
  unsigned int t1[], int l1, unsigned int t2[], int l2)
{
  bool denNeg;
  bool numNeg;
  numNeg = ((u1[n1 - 1] & 2147483648U) != 0U);
  denNeg = ((u2[n2 - 1] & 2147483648U) != 0U);
  if (numNeg) {
    MultiWordNeg(u1, t1, n1);
  } else {
    sMultiWord2MultiWord(u1, n1, t1, l1);
  }

  if (denNeg) {
    MultiWordNeg(u2, t2, n2);
  } else {
    sMultiWord2MultiWord(u2, n2, t2, l2);
  }

  if (uMultiWordDiv(t1, l1, t2, l2, b_y1, m1, y2, m2) < 0) {
    if (numNeg) {
      MultiWordSetSignedMin(b_y1, m1);
    } else {
      MultiWordSetSignedMax(b_y1, m1);
    }
  } else {
    if ((bool)(numNeg ^ denNeg)) {
      if (MultiWord2Bool(y2, m2)) {
        uMultiWordInc(b_y1, m1);
      }

      MultiWordNeg(b_y1, b_y1, m1);
    }
  }
}

/*
 * Arguments    : const unsigned int u1[]
 *                const unsigned int u2[]
 *                int n
 * Return Type  : bool
 */
static bool sMultiWordEq(const unsigned int u1[], const unsigned int u2[], int n)
{
  return sMultiWordCmp(u1, u2, n) == 0;
}

/*
 * Arguments    : const unsigned int u1[]
 *                const unsigned int u2[]
 *                int n
 * Return Type  : bool
 */
static bool sMultiWordGe(const unsigned int u1[], const unsigned int u2[], int n)
{
  return sMultiWordCmp(u1, u2, n) >= 0;
}

/*
 * Arguments    : const unsigned int u1[]
 *                const unsigned int u2[]
 *                int n
 * Return Type  : bool
 */
static bool sMultiWordGt(const unsigned int u1[], const unsigned int u2[], int n)
{
  return sMultiWordCmp(u1, u2, n) > 0;
}

/*
 * Arguments    : const unsigned int u1[]
 *                const unsigned int u2[]
 *                int n
 * Return Type  : bool
 */
static bool sMultiWordLe(const unsigned int u1[], const unsigned int u2[], int n)
{
  return sMultiWordCmp(u1, u2, n) <= 0;
}

/*
 * Arguments    : const unsigned int u1[]
 *                const unsigned int u2[]
 *                int n
 * Return Type  : bool
 */
static bool sMultiWordLt(const unsigned int u1[], const unsigned int u2[], int n)
{
  return sMultiWordCmp(u1, u2, n) < 0;
}

/*
 * Arguments    : const unsigned int u1[]
 *                int n1
 *                const unsigned int u2[]
 *                int n2
 *                unsigned int y[]
 *                int n
 * Return Type  : void
 */
static void sMultiWordMul(const unsigned int u1[], int n1, const unsigned int
  u2[], int n2, unsigned int y[], int n)
{
  int a0;
  int a1;
  int b0;
  int b1;
  unsigned int cb;
  int cb1;
  int cb2;
  int i;
  int j;
  int k;
  int ni;
  unsigned int t;
  unsigned int u1i;
  unsigned int w01;
  unsigned int yk;
  bool isNegative1;
  bool isNegative2;
  isNegative1 = ((u1[n1 - 1] & 2147483648U) != 0U);
  isNegative2 = ((u2[n2 - 1] & 2147483648U) != 0U);
  cb1 = 1;

  /* Initialize output to zero */
  if (0 <= n - 1) {
    memset(&y[0], 0, n * sizeof(unsigned int));
  }

  for (i = 0; i < n1; i++) {
    cb = 0U;
    u1i = u1[i];
    if (isNegative1) {
      u1i = ~u1i + cb1;
      cb1 = (u1i < (unsigned int)cb1);
    }

    a1 = (int)(u1i >> 16U);
    a0 = (int)(u1i & 65535U);
    cb2 = 1;
    ni = n - i;
    if (n2 <= ni) {
      ni = n2;
    }

    k = i;
    for (j = 0; j < ni; j++) {
      u1i = u2[j];
      if (isNegative2) {
        u1i = ~u1i + cb2;
        cb2 = (u1i < (unsigned int)cb2);
      }

      b1 = (int)(u1i >> 16U);
      b0 = (int)(u1i & 65535U);
      u1i = (unsigned int)a1 * b0;
      w01 = (unsigned int)a0 * b1;
      yk = y[k] + cb;
      cb = (unsigned int)(yk < cb);
      t = (unsigned int)a0 * b0;
      yk += t;
      cb += (yk < t);
      t = u1i << 16U;
      yk += t;
      cb += (yk < t);
      t = w01 << 16U;
      yk += t;
      cb += (yk < t);
      y[k] = yk;
      cb += u1i >> 16U;
      cb += w01 >> 16U;
      cb += (unsigned int)a1 * b1;
      k++;
    }

    if (k < n) {
      y[k] = cb;
    }
  }

  /* Apply sign */
  if (isNegative1 != isNegative2) {
    cb = 1U;
    for (k = 0; k < n; k++) {
      yk = ~y[k] + cb;
      y[k] = yk;
      cb = (unsigned int)(yk < cb);
    }
  }
}

/*
 * Arguments    : const unsigned int u1[]
 *                int n1
 *                unsigned int n2
 *                unsigned int y[]
 *                int n
 * Return Type  : void
 */
static void sMultiWordShr(const unsigned int u1[], int n1, unsigned int n2,
  unsigned int y[], int n)
{
  int i;
  int i1;
  int nb;
  int nc;
  unsigned int nr;
  unsigned int u1i;
  unsigned int yi;
  unsigned int ys;
  nb = (int)n2 / 32;
  i = 0;
  if ((u1[n1 - 1] & 2147483648U) != 0U) {
    ys = MAX_uint32_T;
  } else {
    ys = 0U;
  }

  if (nb < n1) {
    nc = n + nb;
    if (nc > n1) {
      nc = n1;
    }

    nr = n2 - nb * 32U;
    if (nr > 0U) {
      u1i = u1[nb];
      for (i1 = nb + 1; i1 < nc; i1++) {
        yi = u1i >> nr;
        u1i = u1[i1];
        y[i] = yi | u1i << (32U - nr);
        i++;
      }

      if (nc < n1) {
        yi = u1[nc];
      } else {
        yi = ys;
      }

      y[i] = u1i >> nr | yi << (32U - nr);
      i++;
    } else {
      for (i1 = nb; i1 < nc; i1++) {
        y[i] = u1[i1];
        i++;
      }
    }
  }

  while (i < n) {
    y[i] = ys;
    i++;
  }
}

/*
 * Arguments    : void
 * Return Type  : void
 */
static void sin_init(void)
{
  static const short iv[256] = { 0, 804, 1608, 2411, 3212, 4011, 4808, 5602,
    6393, 7180, 7962, 8740, 9512, 10279, 11039, 11793, 12540, 13279, 14010,
    14733, 15447, 16151, 16846, 17531, 18205, 18868, 19520, 20160, 20788, 21403,
    22006, 22595, 23170, 23732, 24279, 24812, 25330, 25833, 26320, 26791, 27246,
    27684, 28106, 28511, 28899, 29269, 29622, 29957, 30274, 30572, 30853, 31114,
    31357, 31581, 31786, 31972, 32138, 32286, 32413, 32522, 32610, 32679, 32729,
    32758, MAX_int16_T, 32758, 32729, 32679, 32610, 32522, 32413, 32286, 32138,
    31972, 31786, 31581, 31357, 31114, 30853, 30572, 30274, 29957, 29622, 29269,
    28899, 28511, 28106, 27684, 27246, 26791, 26320, 25833, 25330, 24812, 24279,
    23732, 23170, 22595, 22006, 21403, 20788, 20160, 19520, 18868, 18205, 17531,
    16846, 16151, 15447, 14733, 14010, 13279, 12540, 11793, 11039, 10279, 9512,
    8740, 7962, 7180, 6393, 5602, 4808, 4011, 3212, 2411, 1608, 804, 0, -804,
    -1608, -2411, -3212, -4011, -4808, -5602, -6393, -7180, -7962, -8740, -9512,
    -10279, -11039, -11793, -12540, -13279, -14010, -14733, -15447, -16151,
    -16846, -17531, -18205, -18868, -19520, -20160, -20788, -21403, -22006,
    -22595, -23170, -23732, -24279, -24812, -25330, -25833, -26320, -26791,
    -27246, -27684, -28106, -28511, -28899, -29269, -29622, -29957, -30274,
    -30572, -30853, -31114, -31357, -31581, -31786, -31972, -32138, -32286,
    -32413, -32522, -32610, -32679, -32729, -32758, -32767, -32758, -32729,
    -32679, -32610, -32522, -32413, -32286, -32138, -31972, -31786, -31581,
    -31357, -31114, -30853, -30572, -30274, -29957, -29622, -29269, -28899,
    -28511, -28106, -27684, -27246, -26791, -26320, -25833, -25330, -24812,
    -24279, -23732, -23170, -22595, -22006, -21403, -20788, -20160, -19520,
    -18868, -18205, -17531, -16846, -16151, -15447, -14733, -14010, -13279,
    -12540, -11793, -11039, -10279, -9512, -8740, -7962, -7180, -6393, -5602,
    -4808, -4011, -3212, -2411, -1608, -804 };

  memcpy(&b_FI_SIN_COS_LUT[0], &iv[0], 256U * sizeof(short));
}

/*
 * Arguments    : const unsigned int u1[]
 *                int n1
 *                const unsigned int u2[]
 *                int n2
 *                unsigned int y[]
 *                int n
 * Return Type  : void
 */
static void ssuMultiWordMul(const unsigned int u1[], int n1, const unsigned int
  u2[], int n2, unsigned int y[], int n)
{
  int a0;
  int a1;
  int b0;
  int b1;
  unsigned int cb;
  int cb1;
  int i;
  int j;
  int k;
  int ni;
  unsigned int t;
  unsigned int u1i;
  unsigned int w01;
  unsigned int yk;
  bool isNegative1;
  isNegative1 = ((u1[n1 - 1] & 2147483648U) != 0U);
  cb1 = 1;

  /* Initialize output to zero */
  if (0 <= n - 1) {
    memset(&y[0], 0, n * sizeof(unsigned int));
  }

  for (i = 0; i < n1; i++) {
    cb = 0U;
    u1i = u1[i];
    if (isNegative1) {
      u1i = ~u1i + cb1;
      cb1 = (u1i < (unsigned int)cb1);
    }

    a1 = (int)(u1i >> 16U);
    a0 = (int)(u1i & 65535U);
    ni = n - i;
    if (n2 <= ni) {
      ni = n2;
    }

    k = i;
    for (j = 0; j < ni; j++) {
      u1i = u2[j];
      b1 = (int)(u1i >> 16U);
      b0 = (int)(u1i & 65535U);
      u1i = (unsigned int)a1 * b0;
      w01 = (unsigned int)a0 * b1;
      yk = y[k] + cb;
      cb = (unsigned int)(yk < cb);
      t = (unsigned int)a0 * b0;
      yk += t;
      cb += (yk < t);
      t = u1i << 16U;
      yk += t;
      cb += (yk < t);
      t = w01 << 16U;
      yk += t;
      cb += (yk < t);
      y[k] = yk;
      cb += u1i >> 16U;
      cb += w01 >> 16U;
      cb += (unsigned int)a1 * b1;
      k++;
    }

    if (k < n) {
      y[k] = cb;
    }
  }

  /* Apply sign */
  if (isNegative1) {
    cb = 1U;
    for (k = 0; k < n; k++) {
      yk = ~y[k] + cb;
      y[k] = yk;
      cb = (unsigned int)(yk < cb);
    }
  }
}

/*
 * Arguments    : unsigned int u
 *                unsigned int y[]
 *                int n
 * Return Type  : void
 */
static void uLong2MultiWord(unsigned int u, unsigned int y[], int n)
{
  y[0] = u;
  if (1 <= n - 1) {
    memset(&y[1], 0, (n + -1) * sizeof(unsigned int));
  }
}

/*
 * Arguments    : const unsigned int u1[]
 *                int n1
 *                unsigned int y[]
 *                int n
 * Return Type  : void
 */
static void uMultiWord2MultiWord(const unsigned int u1[], int n1, unsigned int
  y[], int n)
{
  int nm;
  if (n1 < n) {
    nm = n1;
  } else {
    nm = n;
  }

  if (0 <= nm - 1) {
    memcpy(&y[0], &u1[0], nm * sizeof(unsigned int));
  }

  if ((n > n1) && (nm <= n - 1)) {
    memset(&y[nm], 0, (n - nm) * sizeof(unsigned int));
  }
}

/*
 * Arguments    : unsigned int a[]
 *                int na
 *                unsigned int b[]
 *                int nb
 *                unsigned int q[]
 *                int nq
 *                unsigned int r[]
 *                int nr
 * Return Type  : int
 */
static int uMultiWordDiv(unsigned int a[], int na, unsigned int b[], int nb,
  unsigned int q[], int nq, unsigned int r[], int nr)
{
  unsigned int ak;
  unsigned int bk;
  int ka;
  int kb;
  unsigned int kba;
  unsigned int kbb;
  unsigned int mask;
  int na1;
  int nb1;
  unsigned int nba;
  unsigned int nbb;
  unsigned int nbq;
  int nza;
  int nzb;
  unsigned int t;
  unsigned int tnb;
  int tpi;
  int y;
  nzb = nb;
  tpi = nb - 1;
  while ((nzb > 0) && (b[tpi] == 0U)) {
    nzb--;
    tpi--;
  }

  if (nzb > 0) {
    nza = na;
    if (0 <= nq - 1) {
      memset(&q[0], 0, nq * sizeof(unsigned int));
    }

    tpi = na - 1;
    while ((nza > 0) && (a[tpi] == 0U)) {
      nza--;
      tpi--;
    }

    if ((nza > 0) && (nza >= nzb)) {
      nb1 = nzb - 1;
      na1 = nza - 1;
      if (0 <= nr - 1) {
        memset(&r[0], 0, nr * sizeof(unsigned int));
      }

      /* Quick return if dividend and divisor fit into single word. */
      if (nza == 1) {
        ak = a[0];
        bk = b[0];
        nbq = ak / bk;
        q[0] = nbq;
        r[0] = ak - nbq * bk;
        y = 7;
      } else {
        /* Remove leading zeros from both, dividend and divisor. */
        kbb = 1U;
        t = b[nzb - 1] >> 1U;
        while (t != 0U) {
          kbb++;
          t >>= 1U;
        }

        kba = 1U;
        t = a[nza - 1] >> 1U;
        while (t != 0U) {
          kba++;
          t >>= 1U;
        }

        /* Quick return if quotient is zero. */
        if ((nza > nzb) || (kba >= kbb)) {
          nba = (nza - 1) * 32U + kba;
          nbb = (nzb - 1) * 32U + kbb;

          /* Normalize b. */
          if (kbb != 32U) {
            bk = b[nzb - 1];
            for (kb = nzb - 1; kb > 0; kb--) {
              t = bk << (32U - kbb);
              bk = b[kb - 1];
              t |= bk >> kbb;
              b[kb] = t;
            }

            b[0] = bk << (32U - kbb);
            mask = ~((1U << (32U - kbb)) - 1U);
          } else {
            mask = MAX_uint32_T;
          }

          /* Initialize quotient to zero. */
          tnb = 0U;
          y = 0;

          /* Until exit conditions have been met, do */
          do {
            /* Normalize a */
            if (kba != 32U) {
              tnb = (tnb - kba) + 32U;
              ak = a[na1];
              for (ka = na1; ka > 0; ka--) {
                t = ak << (32U - kba);
                ak = a[ka - 1];
                t |= ak >> kba;
                a[ka] = t;
              }

              a[0] = ak << (32U - kba);
            }

            /* Compare b against the a. */
            ak = a[na1];
            bk = b[nzb - 1];
            if (nzb - 1 == 0) {
              t = mask;
            } else {
              t = MAX_uint32_T;
            }

            if ((ak & t) == bk) {
              tpi = 0;
              ka = na1;
              kb = nzb - 1;
              while ((tpi == 0) && (kb > 0)) {
                ka--;
                ak = a[ka];
                kb--;
                bk = b[kb];
                if (kb == 0) {
                  t = mask;
                } else {
                  t = MAX_uint32_T;
                }

                if ((ak & t) != bk) {
                  if (ak > bk) {
                    tpi = 1;
                  } else {
                    tpi = -1;
                  }
                }
              }
            } else if (ak > bk) {
              tpi = 1;
            } else {
              tpi = -1;
            }

            /* If the remainder in a is still greater or equal to b, subtract normalized divisor from a. */
            if ((tpi >= 0) || (nba > nbb)) {
              nbq = nba - nbb;

              /* If the remainder and the divisor are equal, set remainder to zero. */
              if (tpi == 0) {
                ka = na1;
                for (kb = nzb - 1; kb > 0; kb--) {
                  a[ka] = 0U;
                  ka--;
                }

                a[ka] -= b[0];
              } else {
                /* Otherwise, subtract the divisor from the remainder */
                if (tpi < 0) {
                  ak = a[na1];
                  kba = 31U;
                  for (ka = na1; ka > 0; ka--) {
                    t = ak << 1U;
                    ak = a[ka - 1];
                    t |= ak >> 31U;
                    a[ka] = t;
                  }

                  a[0] = ak << 1U;
                  tnb++;
                  nbq--;
                }

                tpi = 0;
                ka = (na1 - nzb) + 1;
                for (kb = 0; kb < nzb; kb++) {
                  t = a[ka];
                  ak = (t - b[kb]) - tpi;
                  if ((unsigned int)tpi != 0U) {
                    tpi = (ak >= t);
                  } else {
                    tpi = (ak > t);
                  }

                  a[ka] = ak;
                  ka++;
                }
              }

              /* Update the quotient. */
              tpi = (int)nbq / 32;
              q[tpi] |= 1U << (nbq - tpi * 32U);

              /* Remove leading zeros from the remainder and check whether the exit conditions have been met. */
              tpi = na1;
              while ((nza > 0) && (a[tpi] == 0U)) {
                nza--;
                tpi--;
              }

              if (nza >= nzb) {
                na1 = nza - 1;
                kba = 1U;
                t = a[nza - 1] >> 1U;
                while (t != 0U) {
                  kba++;
                  t >>= 1U;
                }

                nba = ((nza - 1) * 32U + kba) - tnb;
                if (nba < nbb) {
                  y = 2;
                }
              } else if (nza == 0) {
                y = 1;
              } else {
                na1 = nza - 1;
                y = 4;
              }
            } else {
              y = 3;
            }
          } while (y == 0);

          /* Return the remainder. */
          if (y == 1) {
            r[0] = a[0];
          } else {
            tpi = (int)tnb / 32;
            nbq = tnb - tpi * 32U;
            if (nbq == 0U) {
              ka = tpi;
              for (nzb = 0; nzb <= nb1; nzb++) {
                r[nzb] = a[ka];
                ka++;
              }
            } else {
              ak = a[tpi];
              nzb = 0;
              for (ka = tpi + 1; ka <= na1; ka++) {
                t = ak >> nbq;
                ak = a[ka];
                t |= ak << (32U - nbq);
                r[nzb] = t;
                nzb++;
              }

              r[nzb] = ak >> nbq;
            }
          }

          /* Restore b. */
          if (kbb != 32U) {
            bk = b[0];
            for (kb = 0; kb < nb1; kb++) {
              t = bk >> (32U - kbb);
              bk = b[kb + 1];
              t |= bk << kbb;
              b[kb] = t;
            }

            b[kb] = bk >> (32U - kbb);
          }
        } else {
          if (0 <= nr - 1) {
            memcpy(&r[0], &a[0], nr * sizeof(unsigned int));
          }

          y = 6;
        }
      }
    } else {
      if (0 <= nr - 1) {
        memcpy(&r[0], &a[0], nr * sizeof(unsigned int));
      }

      y = 5;
    }
  } else {
    y = -1;
  }

  return y;
}

/*
 * Arguments    : unsigned int y[]
 *                int n
 * Return Type  : void
 */
static void uMultiWordInc(unsigned int y[], int n)
{
  int carry = 1;
  int i;
  unsigned int yi;
  for (i = 0; i < n; i++) {
    yi = y[i] + carry;
    y[i] = yi;
    carry = (yi < (unsigned int)carry);
  }
}

/*
 * Arguments    : const unsigned int u1[]
 *                int n1
 *                const unsigned int u2[]
 *                int n2
 *                unsigned int y[]
 *                int n
 * Return Type  : void
 */
static void uMultiWordMul(const unsigned int u1[], int n1, const unsigned int
  u2[], int n2, unsigned int y[], int n)
{
  int a0;
  int a1;
  int b0;
  int b1;
  unsigned int cb;
  int i;
  int j;
  int k;
  int ni;
  unsigned int t;
  unsigned int u1i;
  unsigned int w01;
  unsigned int yk;

  /* Initialize output to zero */
  if (0 <= n - 1) {
    memset(&y[0], 0, n * sizeof(unsigned int));
  }

  for (i = 0; i < n1; i++) {
    cb = 0U;
    u1i = u1[i];
    a1 = (int)(u1i >> 16U);
    a0 = (int)(u1i & 65535U);
    ni = n - i;
    if (n2 <= ni) {
      ni = n2;
    }

    k = i;
    for (j = 0; j < ni; j++) {
      u1i = u2[j];
      b1 = (int)(u1i >> 16U);
      b0 = (int)(u1i & 65535U);
      u1i = (unsigned int)a1 * b0;
      w01 = (unsigned int)a0 * b1;
      yk = y[k] + cb;
      cb = (unsigned int)(yk < cb);
      t = (unsigned int)a0 * b0;
      yk += t;
      cb += (yk < t);
      t = u1i << 16U;
      yk += t;
      cb += (yk < t);
      t = w01 << 16U;
      yk += t;
      cb += (yk < t);
      y[k] = yk;
      cb += u1i >> 16U;
      cb += w01 >> 16U;
      cb += (unsigned int)a1 * b1;
      k++;
    }

    if (k < n) {
      y[k] = cb;
    }
  }
}

/*
 * Arguments    : const unsigned int u1[]
 *                int n1
 *                unsigned int n2
 *                unsigned int y[]
 *                int n
 * Return Type  : void
 */
static void uMultiWordShl(const unsigned int u1[], int n1, unsigned int n2,
  unsigned int y[], int n)
{
  int i;
  int nb;
  int nc;
  unsigned int nl;
  unsigned int u1i;
  unsigned int yi;
  unsigned int ys;
  nb = (int)n2 / 32;
  if ((u1[n1 - 1] & 2147483648U) != 0U) {
    ys = MAX_uint32_T;
  } else {
    ys = 0U;
  }

  if (nb > n) {
    nc = n;
  } else {
    nc = nb;
  }

  u1i = 0U;
  if (0 <= nc - 1) {
    memset(&y[0], 0, nc * sizeof(unsigned int));
  }

  for (i = 0; i < nc; i++) {
  }

  if (nb < n) {
    nl = n2 - nb * 32U;
    nb += n1;
    if (nb > n) {
      nb = n;
    }

    nb -= i;
    if (nl > 0U) {
      for (nc = 0; nc < nb; nc++) {
        yi = u1i >> (32U - nl);
        u1i = u1[nc];
        y[i] = yi | u1i << nl;
        i++;
      }

      if (i < n) {
        y[i] = u1i >> (32U - nl) | ys << nl;
        i++;
      }
    } else {
      for (nc = 0; nc < nb; nc++) {
        y[i] = u1[nc];
        i++;
      }
    }
  }

  while (i < n) {
    y[i] = ys;
    i++;
  }
}

/*
 * Arguments    : const unsigned int u1[]
 *                int n1
 *                unsigned int n2
 *                unsigned int y[]
 *                int n
 * Return Type  : void
 */
static void uMultiWordShr(const unsigned int u1[], int n1, unsigned int n2,
  unsigned int y[], int n)
{
  int i;
  int i1;
  int nb;
  int nc;
  unsigned int nr;
  unsigned int u1i;
  unsigned int yi;
  nb = (int)n2 / 32;
  i = 0;
  if (nb < n1) {
    nc = n + nb;
    if (nc > n1) {
      nc = n1;
    }

    nr = n2 - nb * 32U;
    if (nr > 0U) {
      u1i = u1[nb];
      for (i1 = nb + 1; i1 < nc; i1++) {
        yi = u1i >> nr;
        u1i = u1[i1];
        y[i] = yi | u1i << (32U - nr);
        i++;
      }

      yi = u1i >> nr;
      if (nc < n1) {
        yi |= u1[nc] << (32U - nr);
      }

      y[i] = yi;
      i++;
    } else {
      for (i1 = nb; i1 < nc; i1++) {
        y[i] = u1[i1];
        i++;
      }
    }
  }

  while (i < n) {
    y[i] = 0U;
    i++;
  }
}

/*
 * function [az_out, el_out, r_out] = ParalaxCalc_fixpt(az_in, el_in, r_in_1)
 * Arguments    : unsigned short az_in
 *                unsigned short el_in
 *                unsigned short r_in_1
 *                unsigned short *az_out
 *                unsigned short *el_out
 *                unsigned short *r_out
 * Return Type  : void
 */
void ParalaxCalc_fixpt(unsigned short az_in, unsigned short el_in, unsigned
  short r_in_1, unsigned short *az_out, unsigned short *el_out, unsigned short
  *r_out)
{
  static const int64m_T r14 = { { 2228224U, 0U }/* chunks */
  };

  static const int64m_T r20 = { { 0U, 0U }/* chunks */
  };

  static const int64m_T r22 = { { 1U, 0U }/* chunks */
  };

  static const int64m_T r31 = { { 3373259426U, 0U }/* chunks */
  };

  static const int64m_T r9 = { { 3801088U, 0U }/* chunks */
  };

  static const int96m_T r21 = { { 0U, 0U, 0U }/* chunks */
  };

  static const uint64m_T r15 = { { 2883584U, 0U }/* chunks */
  };

  int64m_T b_ytemp;
  int64m_T r10;
  int64m_T r11;
  int64m_T r12;
  int64m_T r13;
  int64m_T r29;
  int64m_T r30;
  int64m_T r6;
  int64m_T r7;
  int64m_T r8;
  int64m_T y;
  int64m_T ytemp;
  int96m_T b_c;
  int96m_T c;
  int96m_T r16;
  int96m_T r17;
  int96m_T r18;
  int96m_T r19;
  int96m_T r23;
  int96m_T r24;
  int96m_T r25;
  int96m_T r26;
  int96m_T r27;
  int96m_T r28;
  uint64m_T r;
  uint64m_T r1;
  uint64m_T r2;
  uint64m_T r3;
  uint64m_T r4;
  uint64m_T r5;
  uint96m_T r32;
  uint96m_T r33;
  unsigned int az_in_rad;
  int az_out_rad;
  unsigned int el_in_rad;
  int negThisX;
  int negThisY;
  unsigned int u;
  unsigned int u1;
  int x_out;
  int y_out;
  unsigned short b_idxUFIX16;
  unsigned short c_idxUFIX16;
  unsigned short d_idxUFIX16;
  unsigned short e_idxUFIX16;
  unsigned short idxUFIX16;
  short thPreCorr;
  unsigned char b_slice_temp;
  unsigned char c_slice_temp;
  unsigned char d_slice_temp;
  unsigned char e_slice_temp;
  unsigned char slice_temp;
  bool guard1 = false;
  bool guard2 = false;
  if (!isInitialized_ParalaxCalc) {
    ParalaxCalc_fixpt_initialize();
  }

  /* %%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%% */
  /*                                                                           % */
  /*            Generated by MATLAB 9.9 and Fixed-Point Designer 7.1           % */
  /*                                                                           % */
  /* %%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%% */
  /* u32 Az град = 180 * 2 ^-14 * az_in */
  /* i32 At град = 180 * 2 ^-14 * el_in */
  /* u32 r м     = r_in */
  /* 'ParalaxCalc_fixpt:11' fm = get_fimath(); */
  /* 'ParalaxCalc_fixpt:12' r_in = fi(r_in_1, 0, 14, 0, fm); */
  /* 'ParalaxCalc_fixpt:14' x_base = fi(29, 0, 5, 0, fm); */
  /* 'ParalaxCalc_fixpt:15' y_base = fi(17, 0, 5, 0, fm); */
  /* 'ParalaxCalc_fixpt:16' z_base = fi(11, 0, 4, 0, fm); */
  /*      x_base = 0; */
  /*      y_base = 0; */
  /*      z_base = 0; */
  /* 'ParalaxCalc_fixpt:24' az_in_rad = fi(fi_div_by_shift(az_in * fi(pi, 0, 32, 30, fm), 14), 0, 32, 29, fm); */
  /* 'ParalaxCalc_fixpt:55' coder.inline( 'always' ); */
  /* 'ParalaxCalc_fixpt:56' if isfi( a ) */
  /* 'ParalaxCalc_fixpt:57' nt = numerictype( a ); */
  /* 'ParalaxCalc_fixpt:58' fm = fimath( a ); */
  /* 'ParalaxCalc_fixpt:59' nt_bs = numerictype( nt.Signed, nt.WordLength + shift_len, nt.FractionLength + shift_len ); */
  /* 'ParalaxCalc_fixpt:60' y = bitsra( fi( a, nt_bs, fm ), shift_len ); */
  u = az_in;
  u1 = 3373259426U;
  uMultiWordMul((unsigned int *)&u, 1, (unsigned int *)&u1, 1, (unsigned int *)
                &r.chunks[0U], 2);
  uMultiWordShl((unsigned int *)&r.chunks[0U], 2, 14U, (unsigned int *)
                &r1.chunks[0U], 2);
  MultiWordUnsignedWrap((unsigned int *)&r1.chunks[0U], 2, 3U, (unsigned int *)
                        &r2.chunks[0U]);
  uMultiWordShr((unsigned int *)&r2.chunks[0U], 2, 14U, (unsigned int *)
                &r3.chunks[0U], 2);
  uMultiWordShr((unsigned int *)&r3.chunks[0U], 2, 15U, (unsigned int *)
                &r4.chunks[0U], 2);
  az_in_rad = MultiWord2uLong((unsigned int *)&r4.chunks[0U]);

  /* 'ParalaxCalc_fixpt:25' el_in_rad = fi(fi_div_by_shift(el_in * fi(pi, 0, 32, 30, fm), 14), 0, 32, 31, fm); */
  /* 'ParalaxCalc_fixpt:55' coder.inline( 'always' ); */
  /* 'ParalaxCalc_fixpt:56' if isfi( a ) */
  /* 'ParalaxCalc_fixpt:57' nt = numerictype( a ); */
  /* 'ParalaxCalc_fixpt:58' fm = fimath( a ); */
  /* 'ParalaxCalc_fixpt:59' nt_bs = numerictype( nt.Signed, nt.WordLength + shift_len, nt.FractionLength + shift_len ); */
  /* 'ParalaxCalc_fixpt:60' y = bitsra( fi( a, nt_bs, fm ), shift_len ); */
  u = el_in;
  uMultiWordMul((unsigned int *)&u, 1, (unsigned int *)&u1, 1, (unsigned int *)
                &r5.chunks[0U], 2);
  uMultiWordShl((unsigned int *)&r5.chunks[0U], 2, 14U, (unsigned int *)
                &r.chunks[0U], 2);
  MultiWordUnsignedWrap((unsigned int *)&r.chunks[0U], 2, 5U, (unsigned int *)
                        &r1.chunks[0U]);
  uMultiWordShr((unsigned int *)&r1.chunks[0U], 2, 14U, (unsigned int *)
                &r2.chunks[0U], 2);
  uMultiWordShr((unsigned int *)&r2.chunks[0U], 2, 13U, (unsigned int *)
                &r3.chunks[0U], 2);
  el_in_rad = MultiWord2uLong((unsigned int *)&r3.chunks[0U]);

  /* 'ParalaxCalc_fixpt:26' r_in = fi(r_in, 0, 14, 0, fm); */
  /* 'ParalaxCalc_fixpt:28' x_in = fi(r_in .* cos(el_in_rad) .* cos(az_in_rad), 1, 32, 17, fm); */
  idxUFIX16 = (unsigned short)(mul_u32_loSR(683563337U, el_in_rad >> 18, 13U) >>
    16);
  slice_temp = (unsigned char)((unsigned int)idxUFIX16 >> 8);
  b_idxUFIX16 = (unsigned short)(mul_u32_loSR(683563337U, (az_in_rad - az_in_rad
    / 3373259426U * 3373259426U) >> 16, 13U) >> 16);
  b_slice_temp = (unsigned char)((unsigned int)b_idxUFIX16 >> 8);

  /* 'ParalaxCalc_fixpt:29' y_in = fi(r_in .* cos(el_in_rad) .* sin(az_in_rad), 1, 32, 17, fm); */
  c_idxUFIX16 = (unsigned short)(mul_u32_loSR(683563337U, el_in_rad >> 18, 13U) >>
    16);
  c_slice_temp = (unsigned char)((unsigned int)c_idxUFIX16 >> 8);
  d_idxUFIX16 = (unsigned short)(mul_u32_loSR(683563337U, (az_in_rad - az_in_rad
    / 3373259426U * 3373259426U) >> 16, 13U) >> 16);
  d_slice_temp = (unsigned char)((unsigned int)d_idxUFIX16 >> 8);

  /* 'ParalaxCalc_fixpt:30' z_in = fi(r_in .* sin(el_in_rad), 0, 32, 18, fm); */
  e_idxUFIX16 = (unsigned short)(mul_u32_loSR(683563337U, el_in_rad >> 18, 13U) >>
    16);
  e_slice_temp = (unsigned char)((unsigned int)e_idxUFIX16 >> 8);

  /* 'ParalaxCalc_fixpt:32' x_out = fi(x_in + x_base, 1, 32, 17, fm); */
  az_out_rad = FI_SIN_COS_LUT[slice_temp] << 15;
  u = (unsigned int)(r_in_1 * (short)((az_out_rad + ((short)(mul_ssu32_loSR
    ((FI_SIN_COS_LUT[(unsigned char)(slice_temp + 1U)] << 15) - az_out_rad,
     (unsigned int)(idxUFIX16 & 255), 8U) >> 15) << 15)) >> 15));
  az_out_rad = FI_SIN_COS_LUT[b_slice_temp] << 15;
  u1 = (unsigned int)(short)((az_out_rad + ((short)(mul_ssu32_loSR
    ((FI_SIN_COS_LUT[(unsigned char)(b_slice_temp + 1U)] << 15) - az_out_rad,
     (unsigned int)(b_idxUFIX16 & 255), 8U) >> 15) << 15)) >> 15);
  sMultiWordMul((unsigned int *)&u, 1, (unsigned int *)&u1, 1, (unsigned int *)
                &r6.chunks[0U], 2);
  sMultiWordShr((unsigned int *)&r6.chunks[0U], 2, 13U, (unsigned int *)
                &y.chunks[0U], 2);
  sLong2MultiWord(MultiWord2sLong((unsigned int *)&y.chunks[0U]), (unsigned int *)
                  &r7.chunks[0U], 2);
  MultiWordSignedWrap((unsigned int *)&r7.chunks[0U], 2, 30U, (unsigned int *)
                      &r8.chunks[0U]);
  r7 = r9;
  MultiWordAdd((unsigned int *)&r8.chunks[0U], (unsigned int *)&r9.chunks[0U],
               (unsigned int *)&r10.chunks[0U], 2);
  MultiWordSignedWrap((unsigned int *)&r10.chunks[0U], 2, 30U, (unsigned int *)
                      &r11.chunks[0U]);
  x_out = MultiWord2sLong((unsigned int *)&r11.chunks[0U]);

  /* 'ParalaxCalc_fixpt:33' y_out = fi(y_in + y_base, 1, 32, 17, fm); */
  az_out_rad = FI_SIN_COS_LUT[c_slice_temp] << 15;
  u = (unsigned int)(r_in_1 * (short)((az_out_rad + ((short)(mul_ssu32_loSR
    ((FI_SIN_COS_LUT[(unsigned char)(c_slice_temp + 1U)] << 15) - az_out_rad,
     (unsigned int)(c_idxUFIX16 & 255), 8U) >> 15) << 15)) >> 15));
  az_out_rad = b_FI_SIN_COS_LUT[d_slice_temp] << 15;
  u1 = (unsigned int)(short)((az_out_rad + ((short)(mul_ssu32_loSR
    ((b_FI_SIN_COS_LUT[(unsigned char)(d_slice_temp + 1U)] << 15) - az_out_rad,
     (unsigned int)(d_idxUFIX16 & 255), 8U) >> 15) << 15)) >> 15);
  sMultiWordMul((unsigned int *)&u, 1, (unsigned int *)&u1, 1, (unsigned int *)
                &r12.chunks[0U], 2);
  sMultiWordShr((unsigned int *)&r12.chunks[0U], 2, 13U, (unsigned int *)
                &r13.chunks[0U], 2);
  sLong2MultiWord(MultiWord2sLong((unsigned int *)&r13.chunks[0U]), (unsigned
    int *)&r6.chunks[0U], 2);
  MultiWordSignedWrap((unsigned int *)&r6.chunks[0U], 2, 30U, (unsigned int *)
                      &r7.chunks[0U]);
  r6 = r14;
  MultiWordAdd((unsigned int *)&r7.chunks[0U], (unsigned int *)&r14.chunks[0U],
               (unsigned int *)&r8.chunks[0U], 2);
  MultiWordSignedWrap((unsigned int *)&r8.chunks[0U], 2, 30U, (unsigned int *)
                      &r10.chunks[0U]);
  y_out = MultiWord2sLong((unsigned int *)&r10.chunks[0U]);

  /* 'ParalaxCalc_fixpt:34' z_out = fi(z_in + z_base, 0, 32, 18, fm); */
  az_out_rad = b_FI_SIN_COS_LUT[e_slice_temp] << 15;
  uLong2MultiWord((unsigned int)(r_in_1 * (short)((az_out_rad + ((short)
    (mul_ssu32_loSR((b_FI_SIN_COS_LUT[(unsigned char)(e_slice_temp + 1U)] << 15)
                    - az_out_rad, (unsigned int)(e_idxUFIX16 & 255), 8U) >> 15) <<
    15)) >> 15)) << 3, (unsigned int *)&r5.chunks[0U], 2);
  MultiWordUnsignedWrap((unsigned int *)&r5.chunks[0U], 2, 31U, (unsigned int *)
                        &r.chunks[0U]);
  r5 = r15;
  MultiWordAdd((unsigned int *)&r.chunks[0U], (unsigned int *)&r15.chunks[0U],
               (unsigned int *)&r1.chunks[0U], 2);
  MultiWordUnsignedWrap((unsigned int *)&r1.chunks[0U], 2, 31U, (unsigned int *)
                        &r2.chunks[0U]);
  el_in_rad = MultiWord2uLong((unsigned int *)&r2.chunks[0U]);

  /* 'ParalaxCalc_fixpt:36' az_out_rad = fi(atan2(y_out, x_out), 1, 32, 28, fm); */
  guard1 = false;
  guard2 = false;
  if (y_out > 0) {
    if (x_out == y_out) {
      thPreCorr = 6434;
    } else if (x_out >= 0) {
      if (y_out <= x_out) {
        az_out_rad = div_repeat_s32_sat(y_out, x_out, 16U);
        if (az_out_rad < 0) {
          az_out_rad = 0;
        } else {
          if (az_out_rad > 65535) {
            az_out_rad = 65535;
          }
        }

        idxUFIX16 = (unsigned short)az_out_rad;
      } else {
        az_out_rad = div_repeat_s32_sat(x_out, y_out, 16U);
        if (az_out_rad < 0) {
          az_out_rad = 0;
        } else {
          if (az_out_rad > 65535) {
            az_out_rad = 65535;
          }
        }

        idxUFIX16 = (unsigned short)az_out_rad;
      }

      guard2 = true;
    } else {
      if (x_out <= MIN_int32_T) {
        negThisX = MAX_int32_T;
      } else {
        negThisX = -x_out;
      }

      if (y_out == negThisX) {
        thPreCorr = 19302;
      } else {
        if (y_out < negThisX) {
          az_out_rad = div_repeat_s32_sat(y_out, negThisX, 16U);
          if (az_out_rad < 0) {
            az_out_rad = 0;
          } else {
            if (az_out_rad > 65535) {
              az_out_rad = 65535;
            }
          }

          idxUFIX16 = (unsigned short)az_out_rad;
        } else {
          az_out_rad = div_repeat_s32_sat(negThisX, y_out, 16U);
          if (az_out_rad < 0) {
            az_out_rad = 0;
          } else {
            if (az_out_rad > 65535) {
              az_out_rad = 65535;
            }
          }

          idxUFIX16 = (unsigned short)az_out_rad;
        }

        guard2 = true;
      }
    }
  } else if (y_out < 0) {
    if (x_out == y_out) {
      thPreCorr = -19302;
    } else if (x_out >= 0) {
      if (y_out <= MIN_int32_T) {
        negThisY = MAX_int32_T;
      } else {
        negThisY = -y_out;
      }

      if (negThisY == x_out) {
        thPreCorr = -6434;
      } else {
        if (negThisY < x_out) {
          az_out_rad = div_repeat_s32_sat(negThisY, x_out, 16U);
          if (az_out_rad < 0) {
            az_out_rad = 0;
          } else {
            if (az_out_rad > 65535) {
              az_out_rad = 65535;
            }
          }

          idxUFIX16 = (unsigned short)az_out_rad;
        } else {
          az_out_rad = div_repeat_s32_sat(x_out, negThisY, 16U);
          if (az_out_rad < 0) {
            az_out_rad = 0;
          } else {
            if (az_out_rad > 65535) {
              az_out_rad = 65535;
            }
          }

          idxUFIX16 = (unsigned short)az_out_rad;
        }

        guard1 = true;
      }
    } else {
      if (x_out <= MIN_int32_T) {
        negThisX = MAX_int32_T;
      } else {
        negThisX = -x_out;
      }

      if (y_out <= MIN_int32_T) {
        negThisY = MAX_int32_T;
      } else {
        negThisY = -y_out;
      }

      if (negThisY <= negThisX) {
        az_out_rad = div_repeat_s32_sat(negThisY, negThisX, 16U);
        if (az_out_rad < 0) {
          az_out_rad = 0;
        } else {
          if (az_out_rad > 65535) {
            az_out_rad = 65535;
          }
        }

        idxUFIX16 = (unsigned short)az_out_rad;
      } else {
        az_out_rad = div_repeat_s32_sat(negThisX, negThisY, 16U);
        if (az_out_rad < 0) {
          az_out_rad = 0;
        } else {
          if (az_out_rad > 65535) {
            az_out_rad = 65535;
          }
        }

        idxUFIX16 = (unsigned short)az_out_rad;
      }

      guard1 = true;
    }
  } else if (x_out >= 0) {
    thPreCorr = 0;
  } else {
    thPreCorr = 25736;
  }

  if (guard2) {
    slice_temp = (unsigned char)((unsigned int)idxUFIX16 >> 8);
    thPreCorr = (short)((unsigned int)(unsigned short)((((unsigned int)
      ATAN_UFRAC_LUT[slice_temp] << 14) + ((unsigned int)(unsigned short)
      (mul_u32_loSR((unsigned int)(idxUFIX16 & 255), ((unsigned int)
      ATAN_UFRAC_LUT[slice_temp + 1] << 14) - ((unsigned int)ATAN_UFRAC_LUT[(int)
      ((unsigned int)idxUFIX16 >> 8)] << 14), 8U) >> 14) << 14)) >> 14) >> 3);
    if (x_out >= 0) {
      if (x_out < y_out) {
        thPreCorr = (short)(12867 - thPreCorr);
      }
    } else if (y_out > negThisX) {
      thPreCorr = (short)(thPreCorr + 12867);
    } else {
      thPreCorr = (short)(25735 - thPreCorr);
    }
  }

  if (guard1) {
    slice_temp = (unsigned char)((unsigned int)idxUFIX16 >> 8);
    thPreCorr = (short)((unsigned int)(unsigned short)((((unsigned int)
      ATAN_UFRAC_LUT[slice_temp] << 14) + ((unsigned int)(unsigned short)
      (mul_u32_loSR((unsigned int)(idxUFIX16 & 255), ((unsigned int)
      ATAN_UFRAC_LUT[slice_temp + 1] << 14) - ((unsigned int)ATAN_UFRAC_LUT[(int)
      ((unsigned int)idxUFIX16 >> 8)] << 14), 8U) >> 14) << 14)) >> 14) >> 3);
    if (x_out >= 0) {
      if (negThisY <= x_out) {
        thPreCorr = (short)-thPreCorr;
      } else {
        thPreCorr = (short)((thPreCorr - 12867) | -65536);
      }
    } else if (negThisY > negThisX) {
      if ((-(thPreCorr + 12867) & 65536) != 0) {
        thPreCorr = (short)(-(thPreCorr + 12867) | -65536);
      } else {
        thPreCorr = (short)(-(thPreCorr + 12867) & 65535);
      }
    } else {
      thPreCorr = (short)((thPreCorr - 25735) | -65536);
    }
  }

  az_out_rad = thPreCorr << 15;

  /* 'ParalaxCalc_fixpt:37' el_out_rad = fi(atan2(z_out, sqrt(x_out.^2 + y_out.^2)), 0, 32, 31, fm); */
  u = (unsigned int)x_out;
  u1 = (unsigned int)x_out;
  sMultiWordMul((unsigned int *)&u, 1, (unsigned int *)&u1, 1, (unsigned int *)
                &r8.chunks[0U], 2);
  sMultiWord2MultiWord((unsigned int *)&r8.chunks[0U], 2, (unsigned int *)
                       &r16.chunks[0U], 3);
  MultiWordSignedWrap((unsigned int *)&r16.chunks[0U], 3, 31U, (unsigned int *)
                      &r17.chunks[0U]);
  u = (unsigned int)y_out;
  u1 = (unsigned int)y_out;
  sMultiWordMul((unsigned int *)&u, 1, (unsigned int *)&u1, 1, (unsigned int *)
                &r8.chunks[0U], 2);
  sMultiWord2MultiWord((unsigned int *)&r8.chunks[0U], 2, (unsigned int *)
                       &r18.chunks[0U], 3);
  MultiWordSignedWrap((unsigned int *)&r18.chunks[0U], 3, 31U, (unsigned int *)
                      &r16.chunks[0U]);
  MultiWordAdd((unsigned int *)&r17.chunks[0U], (unsigned int *)&r16.chunks[0U],
               (unsigned int *)&r19.chunks[0U], 3);
  MultiWordSignedWrap((unsigned int *)&r19.chunks[0U], 3, 31U, (unsigned int *)
                      &c.chunks[0U]);
  y = r20;
  if (!sMultiWordLe((unsigned int *)&c.chunks[0U], (unsigned int *)&r21.chunks
                    [0U], 3)) {
    r12 = r22;
    for (negThisY = 31; negThisY >= 0; negThisY--) {
      uMultiWordShl((unsigned int *)&r22.chunks[0U], 2, (unsigned int)negThisY,
                    (unsigned int *)&r6.chunks[0U], 2);
      MultiWordSignedWrap((unsigned int *)&r6.chunks[0U], 2, 31U, (unsigned int *)
                          &r7.chunks[0U]);
      MultiWordIor((unsigned int *)&y.chunks[0U], (unsigned int *)&r7.chunks[0U],
                   (unsigned int *)&r8.chunks[0U], 2);
      MultiWordSignedWrap((unsigned int *)&r8.chunks[0U], 2, 31U, (unsigned int *)
                          &ytemp.chunks[0U]);
      sMultiWordMul((unsigned int *)&ytemp.chunks[0U], 2, (unsigned int *)
                    &ytemp.chunks[0U], 2, (unsigned int *)&r17.chunks[0U], 3);
      if (sMultiWordLe((unsigned int *)&r17.chunks[0U], (unsigned int *)
                       &c.chunks[0U], 3)) {
        y = ytemp;
      }
    }
  }

  thPreCorr = b_atan2(el_in_rad, y);

  /* 'ParalaxCalc_fixpt:38' r_out = fi(sqrt(x_out.^2 + y_out.^2 + z_out.^2), 0, 32, 18, fm); */
  u = (unsigned int)x_out;
  u1 = (unsigned int)x_out;
  sMultiWordMul((unsigned int *)&u, 1, (unsigned int *)&u1, 1, (unsigned int *)
                &r8.chunks[0U], 2);
  sMultiWord2MultiWord((unsigned int *)&r8.chunks[0U], 2, (unsigned int *)
                       &r23.chunks[0U], 3);
  MultiWordSignedWrap((unsigned int *)&r23.chunks[0U], 3, 31U, (unsigned int *)
                      &r24.chunks[0U]);
  u = (unsigned int)y_out;
  u1 = (unsigned int)y_out;
  sMultiWordMul((unsigned int *)&u, 1, (unsigned int *)&u1, 1, (unsigned int *)
                &r8.chunks[0U], 2);
  sMultiWord2MultiWord((unsigned int *)&r8.chunks[0U], 2, (unsigned int *)
                       &r25.chunks[0U], 3);
  MultiWordSignedWrap((unsigned int *)&r25.chunks[0U], 3, 31U, (unsigned int *)
                      &r23.chunks[0U]);
  MultiWordAdd((unsigned int *)&r24.chunks[0U], (unsigned int *)&r23.chunks[0U],
               (unsigned int *)&r26.chunks[0U], 3);
  MultiWordSignedWrap((unsigned int *)&r26.chunks[0U], 3, 31U, (unsigned int *)
                      &r27.chunks[0U]);
  uMultiWordShl((unsigned int *)&r27.chunks[0U], 3, 2U, (unsigned int *)
                &r28.chunks[0U], 3);
  MultiWordSignedWrap((unsigned int *)&r28.chunks[0U], 3, 27U, (unsigned int *)
                      &r18.chunks[0U]);
  uMultiWordMul((unsigned int *)&el_in_rad, 1, (unsigned int *)&el_in_rad, 1,
                (unsigned int *)&r1.chunks[0U], 2);
  uMultiWord2MultiWord((unsigned int *)&r1.chunks[0U], 2, (unsigned int *)
                       &r27.chunks[0U], 3);
  MultiWordSignedWrap((unsigned int *)&r27.chunks[0U], 3, 27U, (unsigned int *)
                      &r28.chunks[0U]);
  MultiWordAdd((unsigned int *)&r18.chunks[0U], (unsigned int *)&r28.chunks[0U],
               (unsigned int *)&r16.chunks[0U], 3);
  MultiWordSignedWrap((unsigned int *)&r16.chunks[0U], 3, 27U, (unsigned int *)
                      &b_c.chunks[0U]);
  y = r20;
  if (!sMultiWordLe((unsigned int *)&b_c.chunks[0U], (unsigned int *)
                    &r21.chunks[0U], 3)) {
    r12 = r22;
    for (negThisY = 33; negThisY >= 0; negThisY--) {
      uMultiWordShl((unsigned int *)&r22.chunks[0U], 2, (unsigned int)negThisY,
                    (unsigned int *)&r6.chunks[0U], 2);
      MultiWordSignedWrap((unsigned int *)&r6.chunks[0U], 2, 29U, (unsigned int *)
                          &r7.chunks[0U]);
      MultiWordIor((unsigned int *)&y.chunks[0U], (unsigned int *)&r7.chunks[0U],
                   (unsigned int *)&r8.chunks[0U], 2);
      MultiWordSignedWrap((unsigned int *)&r8.chunks[0U], 2, 29U, (unsigned int *)
                          &b_ytemp.chunks[0U]);
      sMultiWordMul((unsigned int *)&b_ytemp.chunks[0U], 2, (unsigned int *)
                    &b_ytemp.chunks[0U], 2, (unsigned int *)&r18.chunks[0U], 3);
      if (sMultiWordLe((unsigned int *)&r18.chunks[0U], (unsigned int *)
                       &b_c.chunks[0U], 3)) {
        y = b_ytemp;
      }
    }
  }

  /* 'ParalaxCalc_fixpt:40' if az_out_rad < fi(0, 0, 1, 0, fm) */
  if (az_out_rad < 0) {
    /* 'ParalaxCalc_fixpt:41' az_out_rad(:) = az_out_rad + fi(2 * pi, 0, 32, 29, fm); */
    sLong2MultiWord(az_out_rad, (unsigned int *)&r29.chunks[0U], 2);
    uMultiWordShl((unsigned int *)&r29.chunks[0U], 2, 1U, (unsigned int *)
                  &r30.chunks[0U], 2);
    MultiWordSignedWrap((unsigned int *)&r30.chunks[0U], 2, 29U, (unsigned int *)
                        &r12.chunks[0U]);
    MultiWordAdd((unsigned int *)&r12.chunks[0U], (unsigned int *)&r31.chunks[0U],
                 (unsigned int *)&r6.chunks[0U], 2);
    MultiWordSignedWrap((unsigned int *)&r6.chunks[0U], 2, 29U, (unsigned int *)
                        &r7.chunks[0U]);
    sMultiWordShr((unsigned int *)&r7.chunks[0U], 2, 1U, (unsigned int *)
                  &r8.chunks[0U], 2);
    az_out_rad = MultiWord2sLong((unsigned int *)&r8.chunks[0U]);
  }

  /* 'ParalaxCalc_fixpt:44' az_out = fi(az_out_rad * fi(2^14, 0, 15, 0, fm)*fi(1/pi, 0, 32, 33, fm), 0, 32, 17, fm); */
  /* 'ParalaxCalc_fixpt:45' el_out = fi(el_out_rad * fi(2^14, 0, 15, 0, fm)*fi(1/pi, 0, 32, 33, fm), 0, 32, 19, fm); */
  /* 'ParalaxCalc_fixpt:47' az_out = fi(uint32(az_out), 0, 15, 0, fm); */
  sLong2MultiWord(az_out_rad, (unsigned int *)&r12.chunks[0U], 2);
  uMultiWordShl((unsigned int *)&r12.chunks[0U], 2, 14U, (unsigned int *)
                &r6.chunks[0U], 2);
  MultiWordSignedWrap((unsigned int *)&r6.chunks[0U], 2, 17U, (unsigned int *)
                      &r7.chunks[0U]);
  u = 2734261102U;
  ssuMultiWordMul((unsigned int *)&r7.chunks[0U], 2, (unsigned int *)&u, 1,
                  (unsigned int *)&r27.chunks[0U], 3);
  sMultiWordShr((unsigned int *)&r27.chunks[0U], 3, 44U, (unsigned int *)
                &r28.chunks[0U], 3);
  u1 = MultiWord2uLong((unsigned int *)&r28.chunks[0U]);
  *az_out = (unsigned short)((int)((u1 >> 17) + ((u1 & 65536U) != 0U)) & 32767);

  /* 'ParalaxCalc_fixpt:48' el_out = fi(int32(el_out), 0, 13, 0, fm); */
  uLong2MultiWord((unsigned int)thPreCorr << 18, (unsigned int *)&r5.chunks[0U],
                  2);
  uMultiWordShl((unsigned int *)&r5.chunks[0U], 2, 14U, (unsigned int *)
                &r.chunks[0U], 2);
  MultiWordUnsignedWrap((unsigned int *)&r.chunks[0U], 2, 17U, (unsigned int *)
                        &r1.chunks[0U]);
  uMultiWordMul((unsigned int *)&r1.chunks[0U], 2, (unsigned int *)&u, 1,
                (unsigned int *)&r32.chunks[0U], 3);
  uMultiWordShr((unsigned int *)&r32.chunks[0U], 3, 45U, (unsigned int *)
                &r33.chunks[0U], 3);
  u = MultiWord2uLong((unsigned int *)&r33.chunks[0U]);
  *el_out = (unsigned short)((int)((u >> 19) + ((u & 262144U) != 0U)) & 8191);

  /* 'ParalaxCalc_fixpt:49' r_out = fi(uint32(r_out), 0, 14, 0, fm); */
  u = MultiWord2uLong((unsigned int *)&y.chunks[0U]);
  *r_out = (unsigned short)((int)((u >> 18) + ((u & 131072U) != 0U)) & 16383);
}

/*
 * Arguments    : void
 * Return Type  : void
 */
void ParalaxCalc_fixpt_initialize(void)
{
  cos_init();
  sin_init();
  atan2_fi_lut_private_init();
  isInitialized_ParalaxCalc = true;
}

/*
 * Arguments    : void
 * Return Type  : void
 */
void ParalaxCalc_fixpt_terminate(void)
{
  /* (no terminate code required) */
  isInitialized_ParalaxCalc = false;
}

/*
 * File trailer for ParalaxCalc_fixpt.c
 *
 * [EOF]
 */
