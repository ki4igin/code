/*
 * Academic License - for use in teaching, academic research, and meeting
 * course requirements at degree granting institutions only.  Not for
 * government, commercial, or other organizational use.
 * File: ParalaxCalc_fixpt.c
 *
 * MATLAB Coder version            : 5.1
 * C/C++ source code generated on  : 28-Feb-2021 17:26:06
 */

/* Include Files */
#include "ParalaxCalc_fixpt.h"
#include "ParalaxCalc_fixpt_data.h"
#include "ParalaxCalc_fixpt_types.h"
#include <string.h>

/* Function Declarations */
static int32_T MultiWord2sLong(const uint32_T u[]);
static uint32_T MultiWord2uLong(const uint32_T u[]);
static void MultiWordAdd(const uint32_T u1[], const uint32_T u2[], uint32_T y[],
  int32_T n);
static void MultiWordUnsignedWrap(const uint32_T u1[], int32_T n1, uint32_T n2,
  uint32_T y[]);
static int32_T asr_s32(int32_T u, uint32_T n);
static uint32_T div_nzp_repeat_u32_sat(uint32_T numerator, uint32_T denominator,
  uint32_T nRepeatSub);
static int32_T div_repeat_s32_sat(int32_T numerator, int32_T denominator,
  uint32_T nRepeatSub);
static uint32_T div_repeat_u32(uint32_T numerator, uint32_T denominator,
  uint32_T nRepeatSub);
static int32_T mul_ssu32_loSR(int32_T a, uint32_T b, uint32_T aShift);
static uint32_T mul_u32_loSR(uint32_T a, uint32_T b, uint32_T aShift);
static void mul_wide_su32(int32_T in0, uint32_T in1, uint32_T *ptrOutBitsHi,
  uint32_T *ptrOutBitsLo);
static void mul_wide_u32(uint32_T in0, uint32_T in1, uint32_T *ptrOutBitsHi,
  uint32_T *ptrOutBitsLo);
static void sLong2MultiWord(int32_T u, uint32_T y[], int32_T n);
static void sMultiWord2MultiWord(const uint32_T u1[], int32_T n1, uint32_T y[],
  int32_T n);
static void sMultiWordMul(const uint32_T u1[], int32_T n1, const uint32_T u2[],
  int32_T n2, uint32_T y[], int32_T n);
static void sMultiWordShr(const uint32_T u1[], int32_T n1, uint32_T n2, uint32_T
  y[], int32_T n);
static void ssuMultiWordMul(const uint32_T u1[], int32_T n1, const uint32_T u2[],
  int32_T n2, uint32_T y[], int32_T n);
static void uLong2MultiWord(uint32_T u, uint32_T y[], int32_T n);
static void uMultiWord2MultiWord(const uint32_T u1[], int32_T n1, uint32_T y[],
  int32_T n);
static int32_T uMultiWordCmp(const uint32_T u1[], const uint32_T u2[], int32_T n);
static boolean_T uMultiWordLe(const uint32_T u1[], const uint32_T u2[], int32_T
  n);
static void uMultiWordMul(const uint32_T u1[], int32_T n1, const uint32_T u2[],
  int32_T n2, uint32_T y[], int32_T n);
static void uMultiWordShl(const uint32_T u1[], int32_T n1, uint32_T n2, uint32_T
  y[], int32_T n);
static void uMultiWordShr(const uint32_T u1[], int32_T n1, uint32_T n2, uint32_T
  y[], int32_T n);

/* Function Definitions */
/*
 * Arguments    : const uint32_T u[]
 * Return Type  : int32_T
 */
static int32_T MultiWord2sLong(const uint32_T u[])
{
  return (int32_T)u[0];
}

/*
 * Arguments    : const uint32_T u[]
 * Return Type  : uint32_T
 */
static uint32_T MultiWord2uLong(const uint32_T u[])
{
  return u[0];
}

/*
 * Arguments    : const uint32_T u1[]
 *                const uint32_T u2[]
 *                uint32_T y[]
 *                int32_T n
 * Return Type  : void
 */
static void MultiWordAdd(const uint32_T u1[], const uint32_T u2[], uint32_T y[],
  int32_T n)
{
  int32_T carry = 0;
  int32_T i;
  uint32_T u1i;
  uint32_T yi;
  for (i = 0; i < n; i++) {
    u1i = u1[i];
    yi = (u1i + u2[i]) + ((uint32_T)carry);
    y[i] = yi;
    if (((uint32_T)carry) != 0U) {
      carry = (int32_T)((yi <= u1i) ? 1 : 0);
    } else {
      carry = (int32_T)((yi < u1i) ? 1 : 0);
    }
  }
}

/*
 * Arguments    : const uint32_T u1[]
 *                int32_T n1
 *                uint32_T n2
 *                uint32_T y[]
 * Return Type  : void
 */
static void MultiWordUnsignedWrap(const uint32_T u1[], int32_T n1, uint32_T n2,
  uint32_T y[])
{
  int32_T n1m1;
  n1m1 = n1 - 1;
  if (0 <= (n1m1 - 1)) {
    memcpy(&y[0], &u1[0], ((uint32_T)n1m1) * (sizeof(uint32_T)));
  }

  y[n1 - 1] = u1[n1 - 1] & ((1U << (32U - n2)) - 1U);
}

/*
 * Arguments    : int32_T u
 *                uint32_T n
 * Return Type  : int32_T
 */
static int32_T asr_s32(int32_T u, uint32_T n)
{
  int32_T y;
  if (u >= 0) {
    y = (int32_T)((uint32_T)(((uint32_T)u) >> n));
  } else {
    y = (-((int32_T)((uint32_T)(((uint32_T)((int32_T)(-1 - u))) >> n)))) - 1;
  }

  return y;
}

/*
 * Arguments    : uint32_T numerator
 *                uint32_T denominator
 *                uint32_T nRepeatSub
 * Return Type  : uint32_T
 */
static uint32_T div_nzp_repeat_u32_sat(uint32_T numerator, uint32_T denominator,
  uint32_T nRepeatSub)
{
  uint32_T iRepeatSub;
  uint32_T quotient;
  boolean_T numeratorExtraBit;
  boolean_T overflow;
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
 * Arguments    : int32_T numerator
 *                int32_T denominator
 *                uint32_T nRepeatSub
 * Return Type  : int32_T
 */
static int32_T div_repeat_s32_sat(int32_T numerator, int32_T denominator,
  uint32_T nRepeatSub)
{
  int32_T quotient;
  uint32_T b_denominator;
  uint32_T b_numerator;
  if (denominator == 0) {
    if (numerator >= 0) {
      quotient = MAX_int32_T;
    } else {
      quotient = MIN_int32_T;
    }
  } else {
    if (numerator < 0) {
      b_numerator = (~((uint32_T)numerator)) + 1U;
    } else {
      b_numerator = (uint32_T)numerator;
    }

    if (denominator < 0) {
      b_denominator = (~((uint32_T)denominator)) + 1U;
    } else {
      b_denominator = (uint32_T)denominator;
    }

    b_numerator = div_nzp_repeat_u32_sat(b_numerator, b_denominator, nRepeatSub);
    if ((numerator < 0) != (denominator < 0)) {
      if (b_numerator <= 2147483647U) {
        quotient = -((int32_T)b_numerator);
      } else {
        quotient = MIN_int32_T;
      }
    } else if (b_numerator <= 2147483647U) {
      quotient = (int32_T)b_numerator;
    } else {
      quotient = MAX_int32_T;
    }
  }

  return quotient;
}

/*
 * Arguments    : uint32_T numerator
 *                uint32_T denominator
 *                uint32_T nRepeatSub
 * Return Type  : uint32_T
 */
static uint32_T div_repeat_u32(uint32_T numerator, uint32_T denominator,
  uint32_T nRepeatSub)
{
  uint32_T iRepeatSub;
  uint32_T quotient;
  boolean_T numeratorExtraBit;
  if (denominator == 0U) {
    quotient = MAX_uint32_T;
  } else {
    quotient = numerator / denominator;
    numerator %= denominator;
    for (iRepeatSub = 0U; iRepeatSub < nRepeatSub; iRepeatSub++) {
      numeratorExtraBit = (numerator >= 2147483648U);
      numerator <<= 1U;
      quotient <<= 1U;
      if (numeratorExtraBit || (numerator >= denominator)) {
        quotient++;
        numerator -= denominator;
      }
    }
  }

  return quotient;
}

/*
 * Arguments    : int32_T a
 *                uint32_T b
 *                uint32_T aShift
 * Return Type  : int32_T
 */
static int32_T mul_ssu32_loSR(int32_T a, uint32_T b, uint32_T aShift)
{
  uint32_T u32_chi;
  uint32_T u32_clo;
  mul_wide_su32(a, b, &u32_chi, &u32_clo);
  u32_clo = (u32_chi << (32U - aShift)) | (u32_clo >> aShift);
  return (int32_T)u32_clo;
}

/*
 * Arguments    : uint32_T a
 *                uint32_T b
 *                uint32_T aShift
 * Return Type  : uint32_T
 */
static uint32_T mul_u32_loSR(uint32_T a, uint32_T b, uint32_T aShift)
{
  uint32_T result;
  uint32_T u32_chi;
  mul_wide_u32(a, b, &u32_chi, &result);
  return (u32_chi << (32U - aShift)) | (result >> aShift);
}

/*
 * Arguments    : int32_T in0
 *                uint32_T in1
 *                uint32_T *ptrOutBitsHi
 *                uint32_T *ptrOutBitsLo
 * Return Type  : void
 */
static void mul_wide_su32(int32_T in0, uint32_T in1, uint32_T *ptrOutBitsHi,
  uint32_T *ptrOutBitsLo)
{
  int32_T in0Hi;
  int32_T in0Lo;
  int32_T in1Hi;
  int32_T in1Lo;
  uint32_T absIn0;
  uint32_T outBitsLo;
  uint32_T productLoHi;
  uint32_T productLoLo;
  if (in0 < 0) {
    absIn0 = (~((uint32_T)in0)) + 1U;
  } else {
    absIn0 = (uint32_T)in0;
  }

  in0Hi = (int32_T)((uint32_T)(absIn0 >> 16U));
  in0Lo = (int32_T)((uint32_T)(absIn0 & 65535U));
  in1Hi = (int32_T)((uint32_T)(in1 >> 16U));
  in1Lo = (int32_T)((uint32_T)(in1 & 65535U));
  absIn0 = ((uint32_T)in0Hi) * ((uint32_T)in1Lo);
  productLoHi = ((uint32_T)in0Lo) * ((uint32_T)in1Hi);
  productLoLo = ((uint32_T)in0Lo) * ((uint32_T)in1Lo);
  in0Lo = 0;
  outBitsLo = productLoLo + (productLoHi << 16U);
  if (outBitsLo < productLoLo) {
    in0Lo = 1;
  }

  productLoLo = outBitsLo;
  outBitsLo += (absIn0 << 16U);
  if (outBitsLo < productLoLo) {
    in0Lo = (int32_T)((uint32_T)(((uint32_T)in0Lo) + 1U));
  }

  absIn0 = ((((uint32_T)in0Lo) + (((uint32_T)in0Hi) * ((uint32_T)in1Hi))) +
            (productLoHi >> 16U)) + (absIn0 >> 16U);
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
 * Arguments    : uint32_T in0
 *                uint32_T in1
 *                uint32_T *ptrOutBitsHi
 *                uint32_T *ptrOutBitsLo
 * Return Type  : void
 */
static void mul_wide_u32(uint32_T in0, uint32_T in1, uint32_T *ptrOutBitsHi,
  uint32_T *ptrOutBitsLo)
{
  int32_T in0Hi;
  int32_T in0Lo;
  int32_T in1Hi;
  int32_T in1Lo;
  uint32_T outBitsLo;
  uint32_T productHiLo;
  uint32_T productLoHi;
  uint32_T productLoLo;
  in0Hi = (int32_T)((uint32_T)(in0 >> 16U));
  in0Lo = (int32_T)((uint32_T)(in0 & 65535U));
  in1Hi = (int32_T)((uint32_T)(in1 >> 16U));
  in1Lo = (int32_T)((uint32_T)(in1 & 65535U));
  productHiLo = ((uint32_T)in0Hi) * ((uint32_T)in1Lo);
  productLoHi = ((uint32_T)in0Lo) * ((uint32_T)in1Hi);
  productLoLo = ((uint32_T)in0Lo) * ((uint32_T)in1Lo);
  in0Lo = 0;
  outBitsLo = productLoLo + (productLoHi << 16U);
  if (outBitsLo < productLoLo) {
    in0Lo = 1;
  }

  productLoLo = outBitsLo;
  outBitsLo += (productHiLo << 16U);
  if (outBitsLo < productLoLo) {
    in0Lo = (int32_T)((uint32_T)(((uint32_T)in0Lo) + 1U));
  }

  *ptrOutBitsHi = ((((uint32_T)in0Lo) + (((uint32_T)in0Hi) * ((uint32_T)in1Hi)))
                   + (productLoHi >> 16U)) + (productHiLo >> 16U);
  *ptrOutBitsLo = outBitsLo;
}

/*
 * Arguments    : int32_T u
 *                uint32_T y[]
 *                int32_T n
 * Return Type  : void
 */
static void sLong2MultiWord(int32_T u, uint32_T y[], int32_T n)
{
  int32_T i;
  uint32_T yi;
  y[0] = (uint32_T)u;
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
 * Arguments    : const uint32_T u1[]
 *                int32_T n1
 *                uint32_T y[]
 *                int32_T n
 * Return Type  : void
 */
static void sMultiWord2MultiWord(const uint32_T u1[], int32_T n1, uint32_T y[],
  int32_T n)
{
  int32_T i;
  int32_T nm;
  uint32_T u1i;
  if (n1 < n) {
    nm = n1;
  } else {
    nm = n;
  }

  if (0 <= (nm - 1)) {
    memcpy(&y[0], &u1[0], ((uint32_T)nm) * (sizeof(uint32_T)));
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
 * Arguments    : const uint32_T u1[]
 *                int32_T n1
 *                const uint32_T u2[]
 *                int32_T n2
 *                uint32_T y[]
 *                int32_T n
 * Return Type  : void
 */
static void sMultiWordMul(const uint32_T u1[], int32_T n1, const uint32_T u2[],
  int32_T n2, uint32_T y[], int32_T n)
{
  int32_T a0;
  int32_T a1;
  int32_T b0;
  int32_T b1;
  int32_T cb1;
  int32_T cb2;
  int32_T i;
  int32_T j;
  int32_T k;
  int32_T ni;
  uint32_T cb;
  uint32_T t;
  uint32_T u1i;
  uint32_T w01;
  uint32_T yk;
  boolean_T isNegative1;
  boolean_T isNegative2;
  isNegative1 = ((u1[n1 - 1] & 2147483648U) != 0U);
  isNegative2 = ((u2[n2 - 1] & 2147483648U) != 0U);
  cb1 = 1;

  /* Initialize output to zero */
  if (0 <= (n - 1)) {
    memset(&y[0], 0, ((uint32_T)n) * (sizeof(uint32_T)));
  }

  for (i = 0; i < n1; i++) {
    cb = 0U;
    u1i = u1[i];
    if (isNegative1) {
      u1i = (~u1i) + ((uint32_T)cb1);
      cb1 = (int32_T)((u1i < ((uint32_T)cb1)) ? 1 : 0);
    }

    a1 = (int32_T)((uint32_T)(u1i >> 16U));
    a0 = (int32_T)((uint32_T)(u1i & 65535U));
    cb2 = 1;
    ni = n - i;
    if (n2 <= ni) {
      ni = n2;
    }

    k = i;
    for (j = 0; j < ni; j++) {
      u1i = u2[j];
      if (isNegative2) {
        u1i = (~u1i) + ((uint32_T)cb2);
        cb2 = (int32_T)((u1i < ((uint32_T)cb2)) ? 1 : 0);
      }

      b1 = (int32_T)((uint32_T)(u1i >> 16U));
      b0 = (int32_T)((uint32_T)(u1i & 65535U));
      u1i = ((uint32_T)a1) * ((uint32_T)b0);
      w01 = ((uint32_T)a0) * ((uint32_T)b1);
      yk = y[k] + cb;
      cb = (uint32_T)((yk < cb) ? 1 : 0);
      t = ((uint32_T)a0) * ((uint32_T)b0);
      yk += t;
      cb += (uint32_T)((yk < t) ? 1 : 0);
      t = (u1i << 16U);
      yk += t;
      cb += (uint32_T)((yk < t) ? 1 : 0);
      t = (w01 << 16U);
      yk += t;
      cb += (uint32_T)((yk < t) ? 1 : 0);
      y[k] = yk;
      cb += (u1i >> 16U);
      cb += (w01 >> 16U);
      cb += ((uint32_T)a1) * ((uint32_T)b1);
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
      yk = (~y[k]) + cb;
      y[k] = yk;
      cb = (uint32_T)((yk < cb) ? 1 : 0);
    }
  }
}

/*
 * Arguments    : const uint32_T u1[]
 *                int32_T n1
 *                uint32_T n2
 *                uint32_T y[]
 *                int32_T n
 * Return Type  : void
 */
static void sMultiWordShr(const uint32_T u1[], int32_T n1, uint32_T n2, uint32_T
  y[], int32_T n)
{
  int32_T i;
  int32_T i1;
  int32_T nb;
  int32_T nc;
  uint32_T nr;
  uint32_T u1i;
  uint32_T yi;
  uint32_T ys;
  nb = ((int32_T)n2) / 32;
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

    nr = n2 - (((uint32_T)nb) * 32U);
    if (nr > 0U) {
      u1i = u1[nb];
      for (i1 = nb + 1; i1 < nc; i1++) {
        yi = (u1i >> nr);
        u1i = u1[i1];
        y[i] = yi | (u1i << (32U - nr));
        i++;
      }

      if (nc < n1) {
        yi = u1[nc];
      } else {
        yi = ys;
      }

      y[i] = (u1i >> nr) | (yi << (32U - nr));
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
 * Arguments    : const uint32_T u1[]
 *                int32_T n1
 *                const uint32_T u2[]
 *                int32_T n2
 *                uint32_T y[]
 *                int32_T n
 * Return Type  : void
 */
static void ssuMultiWordMul(const uint32_T u1[], int32_T n1, const uint32_T u2[],
  int32_T n2, uint32_T y[], int32_T n)
{
  int32_T a0;
  int32_T a1;
  int32_T b0;
  int32_T b1;
  int32_T cb1;
  int32_T i;
  int32_T j;
  int32_T k;
  int32_T ni;
  uint32_T cb;
  uint32_T t;
  uint32_T u1i;
  uint32_T w01;
  uint32_T yk;
  boolean_T isNegative1;
  isNegative1 = ((u1[n1 - 1] & 2147483648U) != 0U);
  cb1 = 1;

  /* Initialize output to zero */
  if (0 <= (n - 1)) {
    memset(&y[0], 0, ((uint32_T)n) * (sizeof(uint32_T)));
  }

  for (i = 0; i < n1; i++) {
    cb = 0U;
    u1i = u1[i];
    if (isNegative1) {
      u1i = (~u1i) + ((uint32_T)cb1);
      cb1 = (int32_T)((u1i < ((uint32_T)cb1)) ? 1 : 0);
    }

    a1 = (int32_T)((uint32_T)(u1i >> 16U));
    a0 = (int32_T)((uint32_T)(u1i & 65535U));
    ni = n - i;
    if (n2 <= ni) {
      ni = n2;
    }

    k = i;
    for (j = 0; j < ni; j++) {
      u1i = u2[j];
      b1 = (int32_T)((uint32_T)(u1i >> 16U));
      b0 = (int32_T)((uint32_T)(u1i & 65535U));
      u1i = ((uint32_T)a1) * ((uint32_T)b0);
      w01 = ((uint32_T)a0) * ((uint32_T)b1);
      yk = y[k] + cb;
      cb = (uint32_T)((yk < cb) ? 1 : 0);
      t = ((uint32_T)a0) * ((uint32_T)b0);
      yk += t;
      cb += (uint32_T)((yk < t) ? 1 : 0);
      t = (u1i << 16U);
      yk += t;
      cb += (uint32_T)((yk < t) ? 1 : 0);
      t = (w01 << 16U);
      yk += t;
      cb += (uint32_T)((yk < t) ? 1 : 0);
      y[k] = yk;
      cb += (u1i >> 16U);
      cb += (w01 >> 16U);
      cb += ((uint32_T)a1) * ((uint32_T)b1);
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
      yk = (~y[k]) + cb;
      y[k] = yk;
      cb = (uint32_T)((yk < cb) ? 1 : 0);
    }
  }
}

/*
 * Arguments    : uint32_T u
 *                uint32_T y[]
 *                int32_T n
 * Return Type  : void
 */
static void uLong2MultiWord(uint32_T u, uint32_T y[], int32_T n)
{
  y[0] = u;
  if (1 <= (n - 1)) {
    memset(&y[1], 0, ((uint32_T)((int32_T)(n + -1))) * (sizeof(uint32_T)));
  }
}

/*
 * Arguments    : const uint32_T u1[]
 *                int32_T n1
 *                uint32_T y[]
 *                int32_T n
 * Return Type  : void
 */
static void uMultiWord2MultiWord(const uint32_T u1[], int32_T n1, uint32_T y[],
  int32_T n)
{
  int32_T nm;
  if (n1 < n) {
    nm = n1;
  } else {
    nm = n;
  }

  if (0 <= (nm - 1)) {
    memcpy(&y[0], &u1[0], ((uint32_T)nm) * (sizeof(uint32_T)));
  }

  if ((n > n1) && (nm <= (n - 1))) {
    memset(&y[nm], 0, ((uint32_T)((int32_T)(n - nm))) * (sizeof(uint32_T)));
  }
}

/*
 * Arguments    : const uint32_T u1[]
 *                const uint32_T u2[]
 *                int32_T n
 * Return Type  : int32_T
 */
static int32_T uMultiWordCmp(const uint32_T u1[], const uint32_T u2[], int32_T n)
{
  int32_T i;
  int32_T y;
  uint32_T u1i;
  uint32_T u2i;
  y = 0;
  i = n;
  while ((y == 0) && (i > 0)) {
    i--;
    u1i = u1[i];
    u2i = u2[i];
    if (u1i != u2i) {
      if (u1i > u2i) {
        y = 1;
      } else {
        y = -1;
      }
    }
  }

  return y;
}

/*
 * Arguments    : const uint32_T u1[]
 *                const uint32_T u2[]
 *                int32_T n
 * Return Type  : boolean_T
 */
static boolean_T uMultiWordLe(const uint32_T u1[], const uint32_T u2[], int32_T
  n)
{
  return uMultiWordCmp(u1, u2, n) <= 0;
}

/*
 * Arguments    : const uint32_T u1[]
 *                int32_T n1
 *                const uint32_T u2[]
 *                int32_T n2
 *                uint32_T y[]
 *                int32_T n
 * Return Type  : void
 */
static void uMultiWordMul(const uint32_T u1[], int32_T n1, const uint32_T u2[],
  int32_T n2, uint32_T y[], int32_T n)
{
  int32_T a0;
  int32_T a1;
  int32_T b0;
  int32_T b1;
  int32_T i;
  int32_T j;
  int32_T k;
  int32_T ni;
  uint32_T cb;
  uint32_T t;
  uint32_T u1i;
  uint32_T w01;
  uint32_T yk;

  /* Initialize output to zero */
  if (0 <= (n - 1)) {
    memset(&y[0], 0, ((uint32_T)n) * (sizeof(uint32_T)));
  }

  for (i = 0; i < n1; i++) {
    cb = 0U;
    u1i = u1[i];
    a1 = (int32_T)((uint32_T)(u1i >> 16U));
    a0 = (int32_T)((uint32_T)(u1i & 65535U));
    ni = n - i;
    if (n2 <= ni) {
      ni = n2;
    }

    k = i;
    for (j = 0; j < ni; j++) {
      u1i = u2[j];
      b1 = (int32_T)((uint32_T)(u1i >> 16U));
      b0 = (int32_T)((uint32_T)(u1i & 65535U));
      u1i = ((uint32_T)a1) * ((uint32_T)b0);
      w01 = ((uint32_T)a0) * ((uint32_T)b1);
      yk = y[k] + cb;
      cb = (uint32_T)((yk < cb) ? 1 : 0);
      t = ((uint32_T)a0) * ((uint32_T)b0);
      yk += t;
      cb += (uint32_T)((yk < t) ? 1 : 0);
      t = (u1i << 16U);
      yk += t;
      cb += (uint32_T)((yk < t) ? 1 : 0);
      t = (w01 << 16U);
      yk += t;
      cb += (uint32_T)((yk < t) ? 1 : 0);
      y[k] = yk;
      cb += (u1i >> 16U);
      cb += (w01 >> 16U);
      cb += ((uint32_T)a1) * ((uint32_T)b1);
      k++;
    }

    if (k < n) {
      y[k] = cb;
    }
  }
}

/*
 * Arguments    : const uint32_T u1[]
 *                int32_T n1
 *                uint32_T n2
 *                uint32_T y[]
 *                int32_T n
 * Return Type  : void
 */
static void uMultiWordShl(const uint32_T u1[], int32_T n1, uint32_T n2, uint32_T
  y[], int32_T n)
{
  int32_T i;
  int32_T nb;
  int32_T nc;
  uint32_T nl;
  uint32_T u1i;
  uint32_T yi;
  uint32_T ys;
  nb = ((int32_T)n2) / 32;
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
  if (0 <= (nc - 1)) {
    memset(&y[0], 0, ((uint32_T)nc) * (sizeof(uint32_T)));
  }

  for (i = 0; i < nc; i++) {
  }

  if (nb < n) {
    nl = n2 - (((uint32_T)nb) * 32U);
    nb += n1;
    if (nb > n) {
      nb = n;
    }

    nb -= i;
    if (nl > 0U) {
      for (nc = 0; nc < nb; nc++) {
        yi = (u1i >> (32U - nl));
        u1i = u1[nc];
        y[i] = yi | (u1i << nl);
        i++;
      }

      if (i < n) {
        y[i] = (u1i >> (32U - nl)) | (ys << nl);
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
 * Arguments    : const uint32_T u1[]
 *                int32_T n1
 *                uint32_T n2
 *                uint32_T y[]
 *                int32_T n
 * Return Type  : void
 */
static void uMultiWordShr(const uint32_T u1[], int32_T n1, uint32_T n2, uint32_T
  y[], int32_T n)
{
  int32_T i;
  int32_T i1;
  int32_T nb;
  int32_T nc;
  uint32_T nr;
  uint32_T u1i;
  uint32_T yi;
  nb = ((int32_T)n2) / 32;
  i = 0;
  if (nb < n1) {
    nc = n + nb;
    if (nc > n1) {
      nc = n1;
    }

    nr = n2 - (((uint32_T)nb) * 32U);
    if (nr > 0U) {
      u1i = u1[nb];
      for (i1 = nb + 1; i1 < nc; i1++) {
        yi = (u1i >> nr);
        u1i = u1[i1];
        y[i] = yi | (u1i << (32U - nr));
        i++;
      }

      yi = (u1i >> nr);
      if (nc < n1) {
        yi |= (u1[nc] << (32U - nr));
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
 * Arguments    : uint32_T az_in
 *                uint32_T el_in
 *                uint32_T r_in
 *                uint32_T *az_out
 *                uint32_T *el_out
 *                uint32_T *r_out
 * Return Type  : void
 */
void ParalaxCalc_fixpt(uint32_T az_in, uint32_T el_in, uint32_T r_in, uint32_T
  *az_out, uint32_T *el_out, uint32_T *r_out)
{
  static const int64m_T r15 = { { 0U, 950272U }/* chunks */
  };

  static const int64m_T r20 = { { 0U, 557056U }/* chunks */
  };

  static const int64m_T r30 = { { 1073741824U, 421657428U }/* chunks */
  };

  static int64m_T r11;
  static int64m_T r12;
  static int64m_T r13;
  static int64m_T r14;
  static int64m_T r16;
  static int64m_T r17;
  static int64m_T r18;
  static int64m_T r19;
  static int64m_T r7;
  static int64m_T r8;
  static int96m_T r10;
  static int96m_T r9;
  static const uint64m_T r23 = { { 0U, 1441792U }/* chunks */
  };

  static const uint64m_T r27 = { { 0U, 0U }/* chunks */
  };

  static uint64m_T r;
  static uint64m_T r21;
  static uint64m_T r22;
  static uint64m_T r24;
  static uint64m_T r25;
  static uint96m_T r1;
  static uint96m_T r2;
  static uint96m_T r3;
  static uint96m_T r4;
  static uint96m_T r5;
  static uint96m_T r6;
  int64m_T r28;
  int64m_T r29;
  uint64m_T b_c;
  uint64m_T c;
  uint64m_T r26;
  uint64m_T r31;
  uint64m_T r32;
  int32_T i;
  int32_T negThisX;
  int32_T negThisY;
  int32_T x_out;
  int32_T y_out;
  uint32_T az_in_rad;
  uint32_T el_in_rad;
  uint32_T u;
  uint32_T x_out2;
  uint32_T y;
  uint32_T z_out;
  int16_T b_thPreCorr;
  uint16_T b_idxUFIX16;
  uint16_T c_idxUFIX16;
  uint16_T d_idxUFIX16;
  uint16_T idxUFIX16;
  uint16_T thPreCorr;
  uint8_T b_slice_temp;
  uint8_T c_slice_temp;
  uint8_T d_slice_temp;
  uint8_T e_slice_temp;
  uint8_T slice_temp;
  boolean_T guard1 = false;
  boolean_T guard2 = false;

  /* %%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%% */
  /*                                                                           % */
  /*            Generated by MATLAB 9.9 and Fixed-Point Designer 7.1           % */
  /*                                                                           % */
  /* %%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%% */
  /* u32 Az град = 180 * 2 ^-14 * az_in */
  /* i32 At град = 180 * 2 ^-14 * el_in */
  /* u32 r м     = r_in */
  /*      x_base = 0; */
  /*      y_base = 0; */
  /*      z_base = 0; */
  u = 3373259426U;
  uMultiWordMul((uint32_T *)(&az_in), 1, (uint32_T *)(&u), 1, (uint32_T *)
                (&r.chunks[0U]), 2);
  uMultiWord2MultiWord((uint32_T *)(&r.chunks[0U]), 2, (uint32_T *)(&r1.chunks
    [0U]), 3);
  uMultiWordShl((uint32_T *)(&r1.chunks[0U]), 3, 14U, (uint32_T *)(&r2.chunks[0U]),
                3);
  MultiWordUnsignedWrap((uint32_T *)(&r2.chunks[0U]), 3, 18U, (uint32_T *)
                        (&r3.chunks[0U]));
  uMultiWordShr((uint32_T *)(&r3.chunks[0U]), 3, 14U, (uint32_T *)(&r4.chunks[0U]),
                3);
  uMultiWordShr((uint32_T *)(&r4.chunks[0U]), 3, 32U, (uint32_T *)(&r5.chunks[0U]),
                3);
  az_in_rad = MultiWord2uLong((uint32_T *)(&r5.chunks[0U]));
  uMultiWordMul((uint32_T *)(&el_in), 1, (uint32_T *)(&u), 1, (uint32_T *)
                (&r.chunks[0U]), 2);
  uMultiWord2MultiWord((uint32_T *)(&r.chunks[0U]), 2, (uint32_T *)(&r6.chunks
    [0U]), 3);
  uMultiWordShl((uint32_T *)(&r6.chunks[0U]), 3, 14U, (uint32_T *)(&r1.chunks[0U]),
                3);
  MultiWordUnsignedWrap((uint32_T *)(&r1.chunks[0U]), 3, 18U, (uint32_T *)
                        (&r2.chunks[0U]));
  uMultiWordShr((uint32_T *)(&r2.chunks[0U]), 3, 14U, (uint32_T *)(&r3.chunks[0U]),
                3);
  uMultiWordShr((uint32_T *)(&r3.chunks[0U]), 3, 32U, (uint32_T *)(&r4.chunks[0U]),
                3);
  el_in_rad = MultiWord2uLong((uint32_T *)(&r4.chunks[0U]));
  thPreCorr = (uint16_T)(mul_u32_loSR(683563337U, el_in_rad >> 18U, 13U) >> 16U);
  slice_temp = (uint8_T)(((uint32_T)thPreCorr) >> 8U);
  idxUFIX16 = (uint16_T)(mul_u32_loSR(683563337U, (az_in_rad - ((az_in_rad /
    3373259426U) * 3373259426U)) >> 16U, 13U) >> 16U);
  b_slice_temp = (uint8_T)(((uint32_T)idxUFIX16) >> 8U);
  b_idxUFIX16 = (uint16_T)(mul_u32_loSR(683563337U, el_in_rad >> 18U, 13U) >>
    16U);
  c_slice_temp = (uint8_T)(((uint32_T)b_idxUFIX16) >> 8U);
  c_idxUFIX16 = (uint16_T)(mul_u32_loSR(683563337U, (az_in_rad - ((az_in_rad /
    3373259426U) * 3373259426U)) >> 16U, 13U) >> 16U);
  d_slice_temp = (uint8_T)(((uint32_T)c_idxUFIX16) >> 8U);
  d_idxUFIX16 = (uint16_T)(mul_u32_loSR(683563337U, el_in_rad >> 18U, 13U) >>
    16U);
  e_slice_temp = (uint8_T)(((uint32_T)d_idxUFIX16) >> 8U);
  i = ((int32_T)FI_SIN_COS_LUT[slice_temp]) * 32768;
  el_in_rad = (uint32_T)((int16_T)asr_s32(i + (((int32_T)((int16_T)asr_s32
    (mul_ssu32_loSR((((int32_T)FI_SIN_COS_LUT[(uint8_T)(((uint32_T)slice_temp) +
    1U)]) * 32768) - i, (uint32_T)((int32_T)(((int32_T)thPreCorr) & ((uint16_T)
    255))), 8U), 15U))) * 32768), 15U));
  ssuMultiWordMul((uint32_T *)(&el_in_rad), 1, (uint32_T *)(&r_in), 1, (uint32_T
    *)(&r7.chunks[0U]), 2);
  uMultiWordShl((uint32_T *)(&r7.chunks[0U]), 2, 16U, (uint32_T *)(&r8.chunks[0U]),
                2);
  i = ((int32_T)FI_SIN_COS_LUT[b_slice_temp]) * 32768;
  el_in_rad = (uint32_T)((int16_T)asr_s32(i + (((int32_T)((int16_T)asr_s32
    (mul_ssu32_loSR((((int32_T)FI_SIN_COS_LUT[(uint8_T)(((uint32_T)b_slice_temp)
    + 1U)]) * 32768) - i, (uint32_T)((int32_T)(((int32_T)idxUFIX16) & ((uint16_T)
    255))), 8U), 15U))) * 32768), 15U));
  sMultiWordMul((uint32_T *)(&r8.chunks[0U]), 2, (uint32_T *)(&el_in_rad), 1,
                (uint32_T *)(&r9.chunks[0U]), 3);
  sMultiWordShr((uint32_T *)(&r9.chunks[0U]), 3, 16U, (uint32_T *)(&r10.chunks
    [0U]), 3);
  sMultiWord2MultiWord((uint32_T *)(&r10.chunks[0U]), 3, (uint32_T *)
                       (&r11.chunks[0U]), 2);
  sMultiWordShr((uint32_T *)(&r11.chunks[0U]), 2, 31U, (uint32_T *)(&r12.chunks
    [0U]), 2);
  sLong2MultiWord(MultiWord2sLong((uint32_T *)(&r12.chunks[0U])), (uint32_T *)
                  (&r13.chunks[0U]), 2);
  uMultiWordShl((uint32_T *)(&r13.chunks[0U]), 2, 30U, (uint32_T *)(&r14.chunks
    [0U]), 2);
  r13 = r15;
  MultiWordAdd((uint32_T *)(&r14.chunks[0U]), (uint32_T *)(&r15.chunks[0U]),
               (uint32_T *)(&r16.chunks[0U]), 2);
  sMultiWordShr((uint32_T *)(&r16.chunks[0U]), 2, 30U, (uint32_T *)(&r17.chunks
    [0U]), 2);
  x_out = MultiWord2sLong((uint32_T *)(&r17.chunks[0U]));
  i = ((int32_T)FI_SIN_COS_LUT[c_slice_temp]) * 32768;
  el_in_rad = (uint32_T)((int16_T)asr_s32(i + (((int32_T)((int16_T)asr_s32
    (mul_ssu32_loSR((((int32_T)FI_SIN_COS_LUT[(uint8_T)(((uint32_T)c_slice_temp)
    + 1U)]) * 32768) - i, (uint32_T)((int32_T)(((int32_T)b_idxUFIX16) &
    ((uint16_T)255))), 8U), 15U))) * 32768), 15U));
  ssuMultiWordMul((uint32_T *)(&el_in_rad), 1, (uint32_T *)(&r_in), 1, (uint32_T
    *)(&r18.chunks[0U]), 2);
  uMultiWordShl((uint32_T *)(&r18.chunks[0U]), 2, 16U, (uint32_T *)(&r19.chunks
    [0U]), 2);
  i = ((int32_T)b_FI_SIN_COS_LUT[d_slice_temp]) * 32768;
  el_in_rad = (uint32_T)((int16_T)asr_s32(i + (((int32_T)((int16_T)asr_s32
    (mul_ssu32_loSR((((int32_T)b_FI_SIN_COS_LUT[(uint8_T)(((uint32_T)
    d_slice_temp) + 1U)]) * 32768) - i, (uint32_T)((int32_T)(((int32_T)
    c_idxUFIX16) & ((uint16_T)255))), 8U), 15U))) * 32768), 15U));
  sMultiWordMul((uint32_T *)(&r19.chunks[0U]), 2, (uint32_T *)(&el_in_rad), 1,
                (uint32_T *)(&r9.chunks[0U]), 3);
  sMultiWordShr((uint32_T *)(&r9.chunks[0U]), 3, 16U, (uint32_T *)(&r10.chunks
    [0U]), 3);
  sMultiWord2MultiWord((uint32_T *)(&r10.chunks[0U]), 3, (uint32_T *)
                       (&r7.chunks[0U]), 2);
  sMultiWordShr((uint32_T *)(&r7.chunks[0U]), 2, 31U, (uint32_T *)(&r8.chunks[0U]),
                2);
  sLong2MultiWord(MultiWord2sLong((uint32_T *)(&r8.chunks[0U])), (uint32_T *)
                  (&r11.chunks[0U]), 2);
  uMultiWordShl((uint32_T *)(&r11.chunks[0U]), 2, 30U, (uint32_T *)(&r13.chunks
    [0U]), 2);
  r11 = r20;
  MultiWordAdd((uint32_T *)(&r13.chunks[0U]), (uint32_T *)(&r20.chunks[0U]),
               (uint32_T *)(&r14.chunks[0U]), 2);
  sMultiWordShr((uint32_T *)(&r14.chunks[0U]), 2, 30U, (uint32_T *)(&r16.chunks
    [0U]), 2);
  y_out = MultiWord2sLong((uint32_T *)(&r16.chunks[0U]));
  i = ((int32_T)b_FI_SIN_COS_LUT[e_slice_temp]) * 32768;
  el_in_rad = (uint32_T)((int16_T)asr_s32(i + (((int32_T)((int16_T)asr_s32
    (mul_ssu32_loSR((((int32_T)b_FI_SIN_COS_LUT[(uint8_T)(((uint32_T)
    e_slice_temp) + 1U)]) * 32768) - i, (uint32_T)((int32_T)(((int32_T)
    d_idxUFIX16) & ((uint16_T)255))), 8U), 15U))) * 32768), 15U));
  ssuMultiWordMul((uint32_T *)(&el_in_rad), 1, (uint32_T *)(&r_in), 1, (uint32_T
    *)(&r11.chunks[0U]), 2);
  uMultiWordShl((uint32_T *)(&r11.chunks[0U]), 2, 16U, (uint32_T *)(&r13.chunks
    [0U]), 2);
  sMultiWordShr((uint32_T *)(&r13.chunks[0U]), 2, 31U, (uint32_T *)(&r14.chunks
    [0U]), 2);
  uLong2MultiWord(MultiWord2uLong((uint32_T *)(&r14.chunks[0U])), (uint32_T *)
                  (&r21.chunks[0U]), 2);
  uMultiWordShl((uint32_T *)(&r21.chunks[0U]), 2, 31U, (uint32_T *)(&r22.chunks
    [0U]), 2);
  r21 = r23;
  MultiWordAdd((uint32_T *)(&r22.chunks[0U]), (uint32_T *)(&r23.chunks[0U]),
               (uint32_T *)(&r24.chunks[0U]), 2);
  uMultiWordShr((uint32_T *)(&r24.chunks[0U]), 2, 31U, (uint32_T *)(&r.chunks[0U]),
                2);
  z_out = MultiWord2uLong((uint32_T *)(&r.chunks[0U]));
  el_in_rad = (uint32_T)x_out;
  u = (uint32_T)x_out;
  sMultiWordMul((uint32_T *)(&el_in_rad), 1, (uint32_T *)(&u), 1, (uint32_T *)
                (&r11.chunks[0U]), 2);
  sMultiWordShr((uint32_T *)(&r11.chunks[0U]), 2, 29U, (uint32_T *)(&r13.chunks
    [0U]), 2);
  x_out2 = MultiWord2uLong((uint32_T *)(&r13.chunks[0U]));
  el_in_rad = (uint32_T)y_out;
  u = (uint32_T)y_out;
  sMultiWordMul((uint32_T *)(&el_in_rad), 1, (uint32_T *)(&u), 1, (uint32_T *)
                (&r7.chunks[0U]), 2);
  sMultiWordShr((uint32_T *)(&r7.chunks[0U]), 2, 29U, (uint32_T *)(&r11.chunks
    [0U]), 2);
  el_in_rad = MultiWord2uLong((uint32_T *)(&r11.chunks[0U]));
  uLong2MultiWord(x_out2, (uint32_T *)(&r25.chunks[0U]), 2);
  uMultiWordShl((uint32_T *)(&r25.chunks[0U]), 2, 31U, (uint32_T *)(&r21.chunks
    [0U]), 2);
  uLong2MultiWord(el_in_rad, (uint32_T *)(&r26.chunks[0U]), 2);
  uMultiWordShl((uint32_T *)(&r26.chunks[0U]), 2, 31U, (uint32_T *)(&r25.chunks
    [0U]), 2);
  MultiWordAdd((uint32_T *)(&r21.chunks[0U]), (uint32_T *)(&r25.chunks[0U]),
               (uint32_T *)(&r22.chunks[0U]), 2);
  uMultiWordShr((uint32_T *)(&r22.chunks[0U]), 2, 1U, (uint32_T *)(&r24.chunks
    [0U]), 2);
  uMultiWordMul((uint32_T *)(&z_out), 1, (uint32_T *)(&z_out), 1, (uint32_T *)
                (&r21.chunks[0U]), 2);
  uMultiWordShr((uint32_T *)(&r21.chunks[0U]), 2, 1U, (uint32_T *)(&r22.chunks
    [0U]), 2);
  MultiWordAdd((uint32_T *)(&r24.chunks[0U]), (uint32_T *)(&r22.chunks[0U]),
               (uint32_T *)(&c.chunks[0U]), 2);
  y = 0U;
  if (!uMultiWordLe((uint32_T *)(&c.chunks[0U]), (uint32_T *)(&r27.chunks[0U]),
                    2)) {
    for (negThisY = 31; negThisY >= 0; negThisY--) {
      az_in_rad = y | (1U << ((uint32_T)negThisY));
      uMultiWordMul((uint32_T *)(&az_in_rad), 1, (uint32_T *)(&az_in_rad), 1,
                    (uint32_T *)(&r22.chunks[0U]), 2);
      uMultiWord2MultiWord((uint32_T *)(&r22.chunks[0U]), 2, (uint32_T *)
                           (&r2.chunks[0U]), 3);
      uMultiWordShl((uint32_T *)(&r2.chunks[0U]), 3, 1U, (uint32_T *)
                    (&r3.chunks[0U]), 3);
      uMultiWord2MultiWord((uint32_T *)(&c.chunks[0U]), 2, (uint32_T *)
                           (&r2.chunks[0U]), 3);
      if (uMultiWordLe((uint32_T *)(&r3.chunks[0U]), (uint32_T *)(&r2.chunks[0U]),
                       3)) {
        y = az_in_rad;
      }
    }
  }

  uLong2MultiWord(x_out2, (uint32_T *)(&r21.chunks[0U]), 2);
  uMultiWordShl((uint32_T *)(&r21.chunks[0U]), 2, 31U, (uint32_T *)(&r22.chunks
    [0U]), 2);
  uLong2MultiWord(el_in_rad, (uint32_T *)(&r25.chunks[0U]), 2);
  uMultiWordShl((uint32_T *)(&r25.chunks[0U]), 2, 31U, (uint32_T *)(&r21.chunks
    [0U]), 2);
  MultiWordAdd((uint32_T *)(&r22.chunks[0U]), (uint32_T *)(&r21.chunks[0U]),
               (uint32_T *)(&b_c.chunks[0U]), 2);
  el_in_rad = 0U;
  if (!uMultiWordLe((uint32_T *)(&b_c.chunks[0U]), (uint32_T *)(&r27.chunks[0U]),
                    2)) {
    for (negThisY = 31; negThisY >= 0; negThisY--) {
      az_in_rad = el_in_rad | (1U << ((uint32_T)negThisY));
      uMultiWordMul((uint32_T *)(&az_in_rad), 1, (uint32_T *)(&az_in_rad), 1,
                    (uint32_T *)(&r21.chunks[0U]), 2);
      if (uMultiWordLe((uint32_T *)(&r21.chunks[0U]), (uint32_T *)(&b_c.chunks
            [0U]), 2)) {
        el_in_rad = az_in_rad;
      }
    }
  }

  if (z_out == 0U) {
    idxUFIX16 = 0U;
  } else if (el_in_rad == z_out) {
    idxUFIX16 = 25736U;
  } else {
    if (z_out < el_in_rad) {
      thPreCorr = (uint16_T)div_repeat_u32(z_out, el_in_rad, 16U);
    } else {
      thPreCorr = (uint16_T)div_repeat_u32(el_in_rad, z_out, 16U);
    }

    slice_temp = (uint8_T)(((uint32_T)thPreCorr) >> 8U);
    thPreCorr = (uint16_T)(((uint32_T)((uint16_T)(((((uint32_T)
      ATAN_UFRAC_LUT[slice_temp]) << 14U) + (((uint32_T)((uint16_T)(mul_u32_loSR
      ((uint32_T)((int32_T)(((int32_T)thPreCorr) & ((uint16_T)255))),
       (((uint32_T)ATAN_UFRAC_LUT[((int32_T)slice_temp) + 1]) << 14U) -
       (((uint32_T)ATAN_UFRAC_LUT[(int32_T)((uint32_T)(((uint32_T)thPreCorr) >>
      8U))]) << 14U), 8U) >> 14U))) << 14U)) >> 14U))) >> 1U);
    if (el_in_rad < z_out) {
      idxUFIX16 = (uint16_T)(51471U - ((uint32_T)thPreCorr));
    } else {
      idxUFIX16 = thPreCorr;
    }
  }

  guard1 = false;
  guard2 = false;
  if (y_out > 0) {
    if (x_out == y_out) {
      b_thPreCorr = 6434;
    } else if (x_out >= 0) {
      if (y_out <= x_out) {
        i = div_repeat_s32_sat(y_out, x_out, 16U);
        if (i < 0) {
          i = 0;
        } else {
          if (i > 65535) {
            i = 65535;
          }
        }

        thPreCorr = (uint16_T)i;
      } else {
        i = div_repeat_s32_sat(x_out, y_out, 16U);
        if (i < 0) {
          i = 0;
        } else {
          if (i > 65535) {
            i = 65535;
          }
        }

        thPreCorr = (uint16_T)i;
      }

      guard2 = true;
    } else {
      if (x_out <= MIN_int32_T) {
        negThisX = MAX_int32_T;
      } else {
        negThisX = -x_out;
      }

      if (y_out == negThisX) {
        b_thPreCorr = 19302;
      } else {
        if (y_out < negThisX) {
          i = div_repeat_s32_sat(y_out, negThisX, 16U);
          if (i < 0) {
            i = 0;
          } else {
            if (i > 65535) {
              i = 65535;
            }
          }

          thPreCorr = (uint16_T)i;
        } else {
          i = div_repeat_s32_sat(negThisX, y_out, 16U);
          if (i < 0) {
            i = 0;
          } else {
            if (i > 65535) {
              i = 65535;
            }
          }

          thPreCorr = (uint16_T)i;
        }

        guard2 = true;
      }
    }
  } else if (y_out < 0) {
    if (x_out == y_out) {
      b_thPreCorr = -19302;
    } else if (x_out >= 0) {
      if (y_out <= MIN_int32_T) {
        negThisY = MAX_int32_T;
      } else {
        negThisY = -y_out;
      }

      if (negThisY == x_out) {
        b_thPreCorr = -6434;
      } else {
        if (negThisY < x_out) {
          i = div_repeat_s32_sat(negThisY, x_out, 16U);
          if (i < 0) {
            i = 0;
          } else {
            if (i > 65535) {
              i = 65535;
            }
          }

          thPreCorr = (uint16_T)i;
        } else {
          i = div_repeat_s32_sat(x_out, negThisY, 16U);
          if (i < 0) {
            i = 0;
          } else {
            if (i > 65535) {
              i = 65535;
            }
          }

          thPreCorr = (uint16_T)i;
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
        i = div_repeat_s32_sat(negThisY, negThisX, 16U);
        if (i < 0) {
          i = 0;
        } else {
          if (i > 65535) {
            i = 65535;
          }
        }

        thPreCorr = (uint16_T)i;
      } else {
        i = div_repeat_s32_sat(negThisX, negThisY, 16U);
        if (i < 0) {
          i = 0;
        } else {
          if (i > 65535) {
            i = 65535;
          }
        }

        thPreCorr = (uint16_T)i;
      }

      guard1 = true;
    }
  } else if (x_out >= 0) {
    b_thPreCorr = 0;
  } else {
    b_thPreCorr = 25736;
  }

  if (guard2) {
    slice_temp = (uint8_T)(((uint32_T)thPreCorr) >> 8U);
    b_thPreCorr = (int16_T)((uint32_T)(((uint32_T)((uint16_T)(((((uint32_T)
      ATAN_UFRAC_LUT[slice_temp]) << 14U) + (((uint32_T)((uint16_T)(mul_u32_loSR
      ((uint32_T)((int32_T)(((int32_T)thPreCorr) & ((uint16_T)255))),
       (((uint32_T)ATAN_UFRAC_LUT[((int32_T)slice_temp) + 1]) << 14U) -
       (((uint32_T)ATAN_UFRAC_LUT[(int32_T)((uint32_T)(((uint32_T)thPreCorr) >>
      8U))]) << 14U), 8U) >> 14U))) << 14U)) >> 14U))) >> 3U));
    if (x_out >= 0) {
      if (x_out < y_out) {
        b_thPreCorr = (int16_T)(12867 - b_thPreCorr);
      }
    } else if (y_out > negThisX) {
      b_thPreCorr = (int16_T)(b_thPreCorr + 12867);
    } else {
      b_thPreCorr = (int16_T)(25735 - b_thPreCorr);
    }
  }

  if (guard1) {
    slice_temp = (uint8_T)(((uint32_T)thPreCorr) >> 8U);
    b_thPreCorr = (int16_T)((uint32_T)(((uint32_T)((uint16_T)(((((uint32_T)
      ATAN_UFRAC_LUT[slice_temp]) << 14U) + (((uint32_T)((uint16_T)(mul_u32_loSR
      ((uint32_T)((int32_T)(((int32_T)thPreCorr) & ((uint16_T)255))),
       (((uint32_T)ATAN_UFRAC_LUT[((int32_T)slice_temp) + 1]) << 14U) -
       (((uint32_T)ATAN_UFRAC_LUT[(int32_T)((uint32_T)(((uint32_T)thPreCorr) >>
      8U))]) << 14U), 8U) >> 14U))) << 14U)) >> 14U))) >> 3U));
    if (x_out >= 0) {
      if (negThisY <= x_out) {
        b_thPreCorr = (int16_T)(-b_thPreCorr);
      } else {
        b_thPreCorr = (int16_T)((((int32_T)b_thPreCorr) - 12867) | -65536);
      }
    } else if (negThisY > negThisX) {
      if (((-(((int32_T)b_thPreCorr) + 12867)) & 65536) != 0) {
        b_thPreCorr = (int16_T)((-(((int32_T)b_thPreCorr) + 12867)) | -65536);
      } else {
        b_thPreCorr = (int16_T)((-(((int32_T)b_thPreCorr) + 12867)) & 65535);
      }
    } else {
      b_thPreCorr = (int16_T)((((int32_T)b_thPreCorr) - 25735) | -65536);
    }
  }

  negThisY = ((int32_T)b_thPreCorr) * 32768;
  if (negThisY < 0) {
    sLong2MultiWord(negThisY, (uint32_T *)(&r28.chunks[0U]), 2);
    uMultiWordShl((uint32_T *)(&r28.chunks[0U]), 2, 30U, (uint32_T *)
                  (&r18.chunks[0U]), 2);
    r28 = r30;
    MultiWordAdd((uint32_T *)(&r18.chunks[0U]), (uint32_T *)(&r30.chunks[0U]),
                 (uint32_T *)(&r19.chunks[0U]), 2);
    sMultiWordShr((uint32_T *)(&r19.chunks[0U]), 2, 30U, (uint32_T *)
                  (&r7.chunks[0U]), 2);
    negThisY = MultiWord2sLong((uint32_T *)(&r7.chunks[0U]));
  }

  sLong2MultiWord(negThisY, (uint32_T *)(&r29.chunks[0U]), 2);
  uMultiWordShl((uint32_T *)(&r29.chunks[0U]), 2, 31U, (uint32_T *)(&r28.chunks
    [0U]), 2);
  el_in_rad = 1367130551U;
  ssuMultiWordMul((uint32_T *)(&r28.chunks[0U]), 2, (uint32_T *)(&el_in_rad), 1,
                  (uint32_T *)(&r9.chunks[0U]), 3);
  sMultiWordShr((uint32_T *)(&r9.chunks[0U]), 3, 31U, (uint32_T *)(&r10.chunks
    [0U]), 3);
  sMultiWord2MultiWord((uint32_T *)(&r10.chunks[0U]), 3, (uint32_T *)
                       (&r18.chunks[0U]), 2);
  sMultiWordShr((uint32_T *)(&r18.chunks[0U]), 2, 29U, (uint32_T *)(&r19.chunks
    [0U]), 2);
  u = MultiWord2uLong((uint32_T *)(&r19.chunks[0U]));
  *az_out = (((u >> 17U) + ((uint32_T)(((u & 65536U) != 0U) ? 1 : 0))) << 16U);
  uLong2MultiWord(((uint32_T)idxUFIX16) << 16U, (uint32_T *)(&r31.chunks[0U]), 2);
  uMultiWordShl((uint32_T *)(&r31.chunks[0U]), 2, 31U, (uint32_T *)(&r32.chunks
    [0U]), 2);
  uMultiWordMul((uint32_T *)(&r32.chunks[0U]), 2, (uint32_T *)(&el_in_rad), 1,
                (uint32_T *)(&r6.chunks[0U]), 3);
  uMultiWordShr((uint32_T *)(&r6.chunks[0U]), 3, 31U, (uint32_T *)(&r1.chunks[0U]),
                3);
  uMultiWord2MultiWord((uint32_T *)(&r1.chunks[0U]), 3, (uint32_T *)
                       (&r26.chunks[0U]), 2);
  uMultiWordShr((uint32_T *)(&r26.chunks[0U]), 2, 30U, (uint32_T *)(&r25.chunks
    [0U]), 2);
  u = MultiWord2uLong((uint32_T *)(&r25.chunks[0U]));
  *el_out = (((u >> 19U) + ((uint32_T)(((u & 262144U) != 0U) ? 1 : 0))) << 19U);
  u = (y << 1U);
  *r_out = (((u >> 18U) + ((uint32_T)(((u & 131072U) != 0U) ? 1 : 0))) << 18U);
}

/*
 * File trailer for ParalaxCalc_fixpt.c
 *
 * [EOF]
 */
