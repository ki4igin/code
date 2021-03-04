/*
 * Academic License - for use in teaching, academic research, and meeting
 * course requirements at degree granting institutions only.  Not for
 * government, commercial, or other organizational use.
 * File: _coder_ParalaxCalc_fixpt_mex.c
 *
 * MATLAB Coder version            : 5.1
 * C/C++ source code generated on  : 01-Mar-2021 16:38:13
 */

/* Include Files */
#include "_coder_ParalaxCalc_fixpt_mex.h"
#include "_coder_ParalaxCalc_fixpt_api.h"

/* Function Definitions */
/*
 * Arguments    : int32_T nlhs
 *                mxArray *plhs[3]
 *                int32_T nrhs
 *                const mxArray *prhs[3]
 * Return Type  : void
 */
void ParalaxCalc_fixpt_mexFunction(int32_T nlhs, mxArray *plhs[3], int32_T nrhs,
  const mxArray *prhs[3])
{
  emlrtStack st = { NULL,              /* site */
    NULL,                              /* tls */
    NULL                               /* prev */
  };

  const mxArray *outputs[3];
  int32_T b_nlhs;
  st.tls = emlrtRootTLSGlobal;

  /* Check for proper number of arguments. */
  if (nrhs != 3) {
    emlrtErrMsgIdAndTxt(&st, "EMLRT:runTime:WrongNumberOfInputs", 5, 12, 3, 4,
                        17, "ParalaxCalc_fixpt");
  }

  if (nlhs > 3) {
    emlrtErrMsgIdAndTxt(&st, "EMLRT:runTime:TooManyOutputArguments", 3, 4, 17,
                        "ParalaxCalc_fixpt");
  }

  /* Call the function. */
  ParalaxCalc_fixpt_api(prhs, nlhs, outputs);

  /* Copy over outputs to the caller. */
  if (nlhs < 1) {
    b_nlhs = 1;
  } else {
    b_nlhs = nlhs;
  }

  emlrtReturnArrays(b_nlhs, plhs, outputs);
}

/*
 * Arguments    : int32_T nlhs
 *                mxArray *plhs[]
 *                int32_T nrhs
 *                const mxArray *prhs[]
 * Return Type  : void
 */
void mexFunction(int32_T nlhs, mxArray *plhs[], int32_T nrhs, const mxArray
                 *prhs[])
{
  mexAtExit(&ParalaxCalc_fixpt_atexit);

  /* Module initialization. */
  ParalaxCalc_fixpt_initialize();

  /* Dispatch the entry-point. */
  ParalaxCalc_fixpt_mexFunction(nlhs, plhs, nrhs, prhs);

  /* Module termination. */
  ParalaxCalc_fixpt_terminate();
}

/*
 * Arguments    : void
 * Return Type  : emlrtCTX
 */
emlrtCTX mexFunctionCreateRootTLS(void)
{
  emlrtCreateRootTLS(&emlrtRootTLSGlobal, &emlrtContextGlobal, NULL, 1);
  return emlrtRootTLSGlobal;
}

/*
 * File trailer for _coder_ParalaxCalc_fixpt_mex.c
 *
 * [EOF]
 */
