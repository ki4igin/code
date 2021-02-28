/*
 * Academic License - for use in teaching, academic research, and meeting
 * course requirements at degree granting institutions only.  Not for
 * government, commercial, or other organizational use.
 * File: _coder_ParalaxCalc_fixpt_api.h
 *
 * MATLAB Coder version            : 5.1
 * C/C++ source code generated on  : 28-Feb-2021 17:26:06
 */

#ifndef _CODER_PARALAXCALC_FIXPT_API_H
#define _CODER_PARALAXCALC_FIXPT_API_H

/* Include Files */
#include "emlrt.h"
#include "tmwtypes.h"
#include <string.h>

/* Variable Declarations */
extern emlrtCTX emlrtRootTLSGlobal;
extern emlrtContext emlrtContextGlobal;

#ifdef __cplusplus

extern "C" {

#endif

  /* Function Declarations */
  void ParalaxCalc_fixpt(uint32_T az_in, uint32_T el_in, uint32_T r_in, uint32_T
    *az_out, uint32_T *el_out, uint32_T *r_out);
  void ParalaxCalc_fixpt_api(const mxArray * const prhs[3], int32_T nlhs, const
    mxArray *plhs[3]);
  void ParalaxCalc_fixpt_atexit(void);
  void ParalaxCalc_fixpt_initialize(void);
  void ParalaxCalc_fixpt_terminate(void);
  void ParalaxCalc_fixpt_xil_shutdown(void);
  void ParalaxCalc_fixpt_xil_terminate(void);

#ifdef __cplusplus

}
#endif
#endif

/*
 * File trailer for _coder_ParalaxCalc_fixpt_api.h
 *
 * [EOF]
 */
