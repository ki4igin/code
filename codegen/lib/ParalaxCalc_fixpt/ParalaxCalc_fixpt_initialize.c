/*
 * Academic License - for use in teaching, academic research, and meeting
 * course requirements at degree granting institutions only.  Not for
 * government, commercial, or other organizational use.
 * File: ParalaxCalc_fixpt_initialize.c
 *
 * MATLAB Coder version            : 5.1
 * C/C++ source code generated on  : 28-Feb-2021 17:26:06
 */

/* Include Files */
#include "ParalaxCalc_fixpt_initialize.h"
#include "atan2_fi_lut_private.h"
#include "cos.h"
#include "sin.h"

/* Function Definitions */
/*
 * Arguments    : void
 * Return Type  : void
 */
void ParalaxCalc_fixpt_initialize(void)
{
  cos_init();
  sin_init();
  atan2_fi_lut_private_init();
}

/*
 * File trailer for ParalaxCalc_fixpt_initialize.c
 *
 * [EOF]
 */
