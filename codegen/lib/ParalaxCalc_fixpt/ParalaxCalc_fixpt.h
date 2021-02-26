/*
 * Academic License - for use in teaching, academic research, and meeting
 * course requirements at degree granting institutions only.  Not for
 * government, commercial, or other organizational use.
 * File: ParalaxCalc_fixpt.h
 *
 * MATLAB Coder version            : 5.1
 * C/C++ source code generated on  : 24-Feb-2021 21:34:46
 */

#ifndef PARALAXCALC_FIXPT_H
#define PARALAXCALC_FIXPT_H

/* Include Files */
#include "rtwtypes.h"
#include <stddef.h>
#include <stdlib.h>
#ifdef __cplusplus

extern "C" {

#endif

  /* Function Declarations */
  extern void ParalaxCalc_fixpt(unsigned short az_in, unsigned short el_in,
    unsigned short r_in_1, unsigned short *az_out, unsigned short *el_out,
    unsigned short *r_out);
  extern void ParalaxCalc_fixpt_initialize(void);
  extern void ParalaxCalc_fixpt_terminate(void);

#ifdef __cplusplus

}
#endif
#endif

/*
 * File trailer for ParalaxCalc_fixpt.h
 *
 * [EOF]
 */
