/*
 * Academic License - for use in teaching, academic research, and meeting
 * course requirements at degree granting institutions only.  Not for
 * government, commercial, or other organizational use.
 * File: _coder_ParalaxCalc_fixpt_api.c
 *
 * MATLAB Coder version            : 5.1
 * C/C++ source code generated on  : 01-Mar-2021 16:38:13
 */

/* Include Files */
#include "_coder_ParalaxCalc_fixpt_api.h"
#include "_coder_ParalaxCalc_fixpt_mex.h"

/* Variable Definitions */
emlrtCTX emlrtRootTLSGlobal = NULL;
static const mxArray *eml_mx;
static const mxArray *b_eml_mx;
static const mxArray *c_eml_mx;
static const mxArray *d_eml_mx;
static const mxArray *e_eml_mx;
emlrtContext emlrtContextGlobal = { true,/* bFirstTime */
  false,                               /* bInitialized */
  131595U,                             /* fVersionInfo */
  NULL,                                /* fErrorFunction */
  "ParalaxCalc_fixpt",                 /* fFunctionName */
  NULL,                                /* fRTCallStack */
  false,                               /* bDebugMode */
  { 2045744189U, 2170104910U, 2743257031U, 4284093946U },/* fSigWrd */
  NULL                                 /* fSigMem */
};

static emlrtMCInfo emlrtMCI = { -1,    /* lineNo */
  -1,                                  /* colNo */
  "",                                  /* fName */
  ""                                   /* pName */
};

/* Function Declarations */
static void ParalaxCalc_fixpt_once(const emlrtStack *sp);
static uint32_T b_emlrt_marshallIn(const emlrtStack *sp, const mxArray *u, const
  emlrtMsgIdentifier *parentId);
static const mxArray *b_emlrt_marshallOut(const emlrtStack *sp, const int32_T u);
static const mxArray *b_numerictype(const emlrtStack *sp, const char_T *b,
  boolean_T c, const char_T *d, const char_T *e, const char_T *f, real_T g,
  emlrtMCInfo *location);
static int32_T c_emlrt_marshallIn(const emlrtStack *sp, const mxArray *el_in,
  const char_T *identifier);
static const mxArray *c_emlrt_marshallOut(const emlrtStack *sp, const uint32_T u);
static const mxArray *c_numerictype(const emlrtStack *sp, const char_T *b,
  real_T c, const char_T *d, real_T e, const char_T *f, real_T g, const char_T
  *h, real_T i, const char_T *j, real_T k, emlrtMCInfo *location);
static int32_T d_emlrt_marshallIn(const emlrtStack *sp, const mxArray *u, const
  emlrtMsgIdentifier *parentId);
static uint32_T e_emlrt_marshallIn(const emlrtStack *sp, const mxArray *r_in,
  const char_T *identifier);
static uint32_T emlrt_marshallIn(const emlrtStack *sp, const mxArray *az_in,
  const char_T *identifier);
static const mxArray *emlrt_marshallOut(const emlrtStack *sp, const uint32_T u);
static uint32_T f_emlrt_marshallIn(const emlrtStack *sp, const mxArray *u, const
  emlrtMsgIdentifier *parentId);
static const mxArray *fimath(const emlrtStack *sp, const char_T *b, const char_T
  *c, const char_T *d, const char_T *e, const char_T *f, const char_T *g, const
  char_T *h, const char_T *i, const char_T *j, const char_T *k, const char_T *l,
  const char_T *m, const char_T *n, real_T o, const char_T *p, real_T q, const
  char_T *r, real_T s, const char_T *t, real_T u, const char_T *v, real_T w,
  const char_T *x, real_T y, const char_T *ab, real_T bb, const char_T *cb,
  real_T db, const char_T *eb, real_T fb, const char_T *gb, real_T hb, const
  char_T *ib, real_T jb, const char_T *kb, real_T lb, const char_T *mb,
  boolean_T nb, const char_T *ob, real_T pb, const char_T *qb, real_T rb,
  emlrtMCInfo *location);
static uint32_T g_emlrt_marshallIn(const mxArray *src);
static int32_T h_emlrt_marshallIn(const mxArray *src);
static const mxArray *numerictype(const emlrtStack *sp, const char_T *b,
  boolean_T c, const char_T *d, const char_T *e, const char_T *f, real_T g,
  const char_T *h, real_T i, const char_T *j, real_T k, const char_T *l, real_T
  m, const char_T *n, real_T o, emlrtMCInfo *location);

/* Function Definitions */
/*
 * Arguments    : const emlrtStack *sp
 * Return Type  : void
 */
static void ParalaxCalc_fixpt_once(const emlrtStack *sp)
{
  emlrtAssignP(&e_eml_mx, NULL);
  emlrtAssignP(&d_eml_mx, NULL);
  emlrtAssignP(&c_eml_mx, NULL);
  emlrtAssignP(&b_eml_mx, NULL);
  emlrtAssignP(&eml_mx, NULL);
  emlrtAssignP(&e_eml_mx, numerictype(sp, "SignednessBool", false, "Signedness",
    "Unsigned", "WordLength", 32.0, "FractionLength", 14.0, "BinaryPoint", 14.0,
    "Slope", 6.103515625E-5, "FixedExponent", -14.0, &emlrtMCI));
  emlrtAssignP(&d_eml_mx, b_numerictype(sp, "SignednessBool", false,
    "Signedness", "Unsigned", "WordLength", 32.0, &emlrtMCI));
  emlrtAssignP(&c_eml_mx, c_numerictype(sp, "WordLength", 32.0, "FractionLength",
    18.0, "BinaryPoint", 18.0, "Slope", 3.814697265625E-6, "FixedExponent",
    -18.0, &emlrtMCI));
  emlrtAssignP(&b_eml_mx, numerictype(sp, "SignednessBool", false, "Signedness",
    "Unsigned", "WordLength", 32.0, "FractionLength", 17.0, "BinaryPoint", 17.0,
    "Slope", 7.62939453125E-6, "FixedExponent", -17.0, &emlrtMCI));
  emlrtAssignP(&eml_mx, fimath(sp, "RoundMode", "floor", "RoundingMethod",
    "Floor", "OverflowMode", "wrap", "OverflowAction", "Wrap", "ProductMode",
    "KeepMSB", "SumMode", "KeepMSB", "ProductWordLength", 64.0, "SumWordLength",
    64.0, "MaxProductWordLength", 65535.0, "MaxSumWordLength", 65535.0,
    "ProductFractionLength", 30.0, "ProductFixedExponent", -30.0,
    "SumFractionLength", 30.0, "SumFixedExponent", -30.0,
    "SumSlopeAdjustmentFactor", 1.0, "SumBias", 0.0,
    "ProductSlopeAdjustmentFactor", 1.0, "ProductBias", 0.0, "CastBeforeSum",
    true, "SumSlope", 9.3132257461547852E-10, "ProductSlope",
    9.3132257461547852E-10, &emlrtMCI));
}

/*
 * Arguments    : const emlrtStack *sp
 *                const mxArray *u
 *                const emlrtMsgIdentifier *parentId
 * Return Type  : uint32_T
 */
static uint32_T b_emlrt_marshallIn(const emlrtStack *sp, const mxArray *u, const
  emlrtMsgIdentifier *parentId)
{
  static const int32_T dims = 0;
  uint32_T y;
  emlrtCheckFiR2012b(sp, parentId, u, false, 0U, &dims, eml_mx, b_eml_mx);
  y = g_emlrt_marshallIn(emlrtAlias(u));
  emlrtDestroyArray(&u);
  return y;
}

/*
 * Arguments    : const emlrtStack *sp
 *                const int32_T u
 * Return Type  : const mxArray *
 */
static const mxArray *b_emlrt_marshallOut(const emlrtStack *sp, const int32_T u)
{
  const mxArray *b_y;
  const mxArray *m;
  const mxArray *y;
  y = NULL;
  b_y = NULL;
  m = emlrtCreateNumericMatrix(1, 1, (int32_T)mxINT32_CLASS, (int32_T)mxREAL);
  *((int32_T *)emlrtMxGetData(m)) = u;
  emlrtAssign(&b_y, m);
  emlrtAssign(&y, emlrtCreateFIR2013b(sp, eml_mx, c_eml_mx, "simulinkarray", b_y,
    true, false));
  return y;
}

/*
 * Arguments    : const emlrtStack *sp
 *                const char_T *b
 *                boolean_T c
 *                const char_T *d
 *                const char_T *e
 *                const char_T *f
 *                real_T g
 *                emlrtMCInfo *location
 * Return Type  : const mxArray *
 */
static const mxArray *b_numerictype(const emlrtStack *sp, const char_T *b,
  boolean_T c, const char_T *d, const char_T *e, const char_T *f, real_T g,
  emlrtMCInfo *location)
{
  const mxArray *pArrays[6];
  const mxArray *m;
  pArrays[0] = emlrtCreateString(b);
  pArrays[1] = emlrtCreateLogicalScalar(c);
  pArrays[2] = emlrtCreateString(d);
  pArrays[3] = emlrtCreateString(e);
  pArrays[4] = emlrtCreateString(f);
  pArrays[5] = emlrtCreateDoubleScalar(g);
  return emlrtCallMATLABR2012b(sp, 1, &m, 6, pArrays, "numerictype", true,
    location);
}

/*
 * Arguments    : const emlrtStack *sp
 *                const mxArray *el_in
 *                const char_T *identifier
 * Return Type  : int32_T
 */
static int32_T c_emlrt_marshallIn(const emlrtStack *sp, const mxArray *el_in,
  const char_T *identifier)
{
  emlrtMsgIdentifier thisId;
  int32_T y;
  thisId.fIdentifier = (const char_T *)identifier;
  thisId.fParent = NULL;
  thisId.bParentIsCell = false;
  y = d_emlrt_marshallIn(sp, emlrtAlias(el_in), &thisId);
  emlrtDestroyArray(&el_in);
  return y;
}

/*
 * Arguments    : const emlrtStack *sp
 *                const uint32_T u
 * Return Type  : const mxArray *
 */
static const mxArray *c_emlrt_marshallOut(const emlrtStack *sp, const uint32_T u)
{
  const mxArray *b_y;
  const mxArray *m;
  const mxArray *y;
  y = NULL;
  b_y = NULL;
  m = emlrtCreateNumericMatrix(1, 1, (int32_T)mxUINT32_CLASS, (int32_T)mxREAL);
  *((uint32_T *)emlrtMxGetData(m)) = u;
  emlrtAssign(&b_y, m);
  emlrtAssign(&y, emlrtCreateFIR2013b(sp, eml_mx, e_eml_mx, "simulinkarray", b_y,
    true, false));
  return y;
}

/*
 * Arguments    : const emlrtStack *sp
 *                const char_T *b
 *                real_T c
 *                const char_T *d
 *                real_T e
 *                const char_T *f
 *                real_T g
 *                const char_T *h
 *                real_T i
 *                const char_T *j
 *                real_T k
 *                emlrtMCInfo *location
 * Return Type  : const mxArray *
 */
static const mxArray *c_numerictype(const emlrtStack *sp, const char_T *b,
  real_T c, const char_T *d, real_T e, const char_T *f, real_T g, const char_T
  *h, real_T i, const char_T *j, real_T k, emlrtMCInfo *location)
{
  const mxArray *pArrays[10];
  const mxArray *m;
  pArrays[0] = emlrtCreateString(b);
  pArrays[1] = emlrtCreateDoubleScalar(c);
  pArrays[2] = emlrtCreateString(d);
  pArrays[3] = emlrtCreateDoubleScalar(e);
  pArrays[4] = emlrtCreateString(f);
  pArrays[5] = emlrtCreateDoubleScalar(g);
  pArrays[6] = emlrtCreateString(h);
  pArrays[7] = emlrtCreateDoubleScalar(i);
  pArrays[8] = emlrtCreateString(j);
  pArrays[9] = emlrtCreateDoubleScalar(k);
  return emlrtCallMATLABR2012b(sp, 1, &m, 10, pArrays, "numerictype", true,
    location);
}

/*
 * Arguments    : const emlrtStack *sp
 *                const mxArray *u
 *                const emlrtMsgIdentifier *parentId
 * Return Type  : int32_T
 */
static int32_T d_emlrt_marshallIn(const emlrtStack *sp, const mxArray *u, const
  emlrtMsgIdentifier *parentId)
{
  static const int32_T dims = 0;
  int32_T y;
  emlrtCheckFiR2012b(sp, parentId, u, false, 0U, &dims, eml_mx, c_eml_mx);
  y = h_emlrt_marshallIn(emlrtAlias(u));
  emlrtDestroyArray(&u);
  return y;
}

/*
 * Arguments    : const emlrtStack *sp
 *                const mxArray *r_in
 *                const char_T *identifier
 * Return Type  : uint32_T
 */
static uint32_T e_emlrt_marshallIn(const emlrtStack *sp, const mxArray *r_in,
  const char_T *identifier)
{
  emlrtMsgIdentifier thisId;
  uint32_T y;
  thisId.fIdentifier = (const char_T *)identifier;
  thisId.fParent = NULL;
  thisId.bParentIsCell = false;
  y = f_emlrt_marshallIn(sp, emlrtAlias(r_in), &thisId);
  emlrtDestroyArray(&r_in);
  return y;
}

/*
 * Arguments    : const emlrtStack *sp
 *                const mxArray *az_in
 *                const char_T *identifier
 * Return Type  : uint32_T
 */
static uint32_T emlrt_marshallIn(const emlrtStack *sp, const mxArray *az_in,
  const char_T *identifier)
{
  emlrtMsgIdentifier thisId;
  uint32_T y;
  thisId.fIdentifier = (const char_T *)identifier;
  thisId.fParent = NULL;
  thisId.bParentIsCell = false;
  y = b_emlrt_marshallIn(sp, emlrtAlias(az_in), &thisId);
  emlrtDestroyArray(&az_in);
  return y;
}

/*
 * Arguments    : const emlrtStack *sp
 *                const uint32_T u
 * Return Type  : const mxArray *
 */
static const mxArray *emlrt_marshallOut(const emlrtStack *sp, const uint32_T u)
{
  const mxArray *b_y;
  const mxArray *m;
  const mxArray *y;
  y = NULL;
  b_y = NULL;
  m = emlrtCreateNumericMatrix(1, 1, (int32_T)mxUINT32_CLASS, (int32_T)mxREAL);
  *((uint32_T *)emlrtMxGetData(m)) = u;
  emlrtAssign(&b_y, m);
  emlrtAssign(&y, emlrtCreateFIR2013b(sp, eml_mx, b_eml_mx, "simulinkarray", b_y,
    true, false));
  return y;
}

/*
 * Arguments    : const emlrtStack *sp
 *                const mxArray *u
 *                const emlrtMsgIdentifier *parentId
 * Return Type  : uint32_T
 */
static uint32_T f_emlrt_marshallIn(const emlrtStack *sp, const mxArray *u, const
  emlrtMsgIdentifier *parentId)
{
  static const int32_T dims = 0;
  uint32_T y;
  emlrtCheckFiR2012b(sp, parentId, u, false, 0U, &dims, eml_mx, d_eml_mx);
  y = g_emlrt_marshallIn(emlrtAlias(u));
  emlrtDestroyArray(&u);
  return y;
}

/*
 * Arguments    : const emlrtStack *sp
 *                const char_T *b
 *                const char_T *c
 *                const char_T *d
 *                const char_T *e
 *                const char_T *f
 *                const char_T *g
 *                const char_T *h
 *                const char_T *i
 *                const char_T *j
 *                const char_T *k
 *                const char_T *l
 *                const char_T *m
 *                const char_T *n
 *                real_T o
 *                const char_T *p
 *                real_T q
 *                const char_T *r
 *                real_T s
 *                const char_T *t
 *                real_T u
 *                const char_T *v
 *                real_T w
 *                const char_T *x
 *                real_T y
 *                const char_T *ab
 *                real_T bb
 *                const char_T *cb
 *                real_T db
 *                const char_T *eb
 *                real_T fb
 *                const char_T *gb
 *                real_T hb
 *                const char_T *ib
 *                real_T jb
 *                const char_T *kb
 *                real_T lb
 *                const char_T *mb
 *                boolean_T nb
 *                const char_T *ob
 *                real_T pb
 *                const char_T *qb
 *                real_T rb
 *                emlrtMCInfo *location
 * Return Type  : const mxArray *
 */
static const mxArray *fimath(const emlrtStack *sp, const char_T *b, const char_T
  *c, const char_T *d, const char_T *e, const char_T *f, const char_T *g, const
  char_T *h, const char_T *i, const char_T *j, const char_T *k, const char_T *l,
  const char_T *m, const char_T *n, real_T o, const char_T *p, real_T q, const
  char_T *r, real_T s, const char_T *t, real_T u, const char_T *v, real_T w,
  const char_T *x, real_T y, const char_T *ab, real_T bb, const char_T *cb,
  real_T db, const char_T *eb, real_T fb, const char_T *gb, real_T hb, const
  char_T *ib, real_T jb, const char_T *kb, real_T lb, const char_T *mb,
  boolean_T nb, const char_T *ob, real_T pb, const char_T *qb, real_T rb,
  emlrtMCInfo *location)
{
  static const mxArray *pArrays[42];
  const mxArray *b_m;
  pArrays[0] = emlrtCreateString(b);
  pArrays[1] = emlrtCreateString(c);
  pArrays[2] = emlrtCreateString(d);
  pArrays[3] = emlrtCreateString(e);
  pArrays[4] = emlrtCreateString(f);
  pArrays[5] = emlrtCreateString(g);
  pArrays[6] = emlrtCreateString(h);
  pArrays[7] = emlrtCreateString(i);
  pArrays[8] = emlrtCreateString(j);
  pArrays[9] = emlrtCreateString(k);
  pArrays[10] = emlrtCreateString(l);
  pArrays[11] = emlrtCreateString(m);
  pArrays[12] = emlrtCreateString(n);
  pArrays[13] = emlrtCreateDoubleScalar(o);
  pArrays[14] = emlrtCreateString(p);
  pArrays[15] = emlrtCreateDoubleScalar(q);
  pArrays[16] = emlrtCreateString(r);
  pArrays[17] = emlrtCreateDoubleScalar(s);
  pArrays[18] = emlrtCreateString(t);
  pArrays[19] = emlrtCreateDoubleScalar(u);
  pArrays[20] = emlrtCreateString(v);
  pArrays[21] = emlrtCreateDoubleScalar(w);
  pArrays[22] = emlrtCreateString(x);
  pArrays[23] = emlrtCreateDoubleScalar(y);
  pArrays[24] = emlrtCreateString(ab);
  pArrays[25] = emlrtCreateDoubleScalar(bb);
  pArrays[26] = emlrtCreateString(cb);
  pArrays[27] = emlrtCreateDoubleScalar(db);
  pArrays[28] = emlrtCreateString(eb);
  pArrays[29] = emlrtCreateDoubleScalar(fb);
  pArrays[30] = emlrtCreateString(gb);
  pArrays[31] = emlrtCreateDoubleScalar(hb);
  pArrays[32] = emlrtCreateString(ib);
  pArrays[33] = emlrtCreateDoubleScalar(jb);
  pArrays[34] = emlrtCreateString(kb);
  pArrays[35] = emlrtCreateDoubleScalar(lb);
  pArrays[36] = emlrtCreateString(mb);
  pArrays[37] = emlrtCreateLogicalScalar(nb);
  pArrays[38] = emlrtCreateString(ob);
  pArrays[39] = emlrtCreateDoubleScalar(pb);
  pArrays[40] = emlrtCreateString(qb);
  pArrays[41] = emlrtCreateDoubleScalar(rb);
  return emlrtCallMATLABR2012b(sp, 1, &b_m, 42, pArrays, "fimath", true,
    location);
}

/*
 * Arguments    : const mxArray *src
 * Return Type  : uint32_T
 */
static uint32_T g_emlrt_marshallIn(const mxArray *src)
{
  const mxArray *mxInt;
  uint32_T ret;
  mxInt = emlrtImportFiIntArrayR2008b(src);
  ret = *((uint32_T *)emlrtMxGetData(mxInt));
  emlrtDestroyArray(&mxInt);
  emlrtDestroyArray(&src);
  return ret;
}

/*
 * Arguments    : const mxArray *src
 * Return Type  : int32_T
 */
static int32_T h_emlrt_marshallIn(const mxArray *src)
{
  const mxArray *mxInt;
  int32_T ret;
  mxInt = emlrtImportFiIntArrayR2008b(src);
  ret = *((int32_T *)emlrtMxGetData(mxInt));
  emlrtDestroyArray(&mxInt);
  emlrtDestroyArray(&src);
  return ret;
}

/*
 * Arguments    : const emlrtStack *sp
 *                const char_T *b
 *                boolean_T c
 *                const char_T *d
 *                const char_T *e
 *                const char_T *f
 *                real_T g
 *                const char_T *h
 *                real_T i
 *                const char_T *j
 *                real_T k
 *                const char_T *l
 *                real_T m
 *                const char_T *n
 *                real_T o
 *                emlrtMCInfo *location
 * Return Type  : const mxArray *
 */
static const mxArray *numerictype(const emlrtStack *sp, const char_T *b,
  boolean_T c, const char_T *d, const char_T *e, const char_T *f, real_T g,
  const char_T *h, real_T i, const char_T *j, real_T k, const char_T *l, real_T
  m, const char_T *n, real_T o, emlrtMCInfo *location)
{
  const mxArray *pArrays[14];
  const mxArray *b_m;
  pArrays[0] = emlrtCreateString(b);
  pArrays[1] = emlrtCreateLogicalScalar(c);
  pArrays[2] = emlrtCreateString(d);
  pArrays[3] = emlrtCreateString(e);
  pArrays[4] = emlrtCreateString(f);
  pArrays[5] = emlrtCreateDoubleScalar(g);
  pArrays[6] = emlrtCreateString(h);
  pArrays[7] = emlrtCreateDoubleScalar(i);
  pArrays[8] = emlrtCreateString(j);
  pArrays[9] = emlrtCreateDoubleScalar(k);
  pArrays[10] = emlrtCreateString(l);
  pArrays[11] = emlrtCreateDoubleScalar(m);
  pArrays[12] = emlrtCreateString(n);
  pArrays[13] = emlrtCreateDoubleScalar(o);
  return emlrtCallMATLABR2012b(sp, 1, &b_m, 14, pArrays, "numerictype", true,
    location);
}

/*
 * Arguments    : const mxArray * const prhs[3]
 *                int32_T nlhs
 *                const mxArray *plhs[3]
 * Return Type  : void
 */
void ParalaxCalc_fixpt_api(const mxArray * const prhs[3], int32_T nlhs, const
  mxArray *plhs[3])
{
  emlrtStack st = { NULL,              /* site */
    NULL,                              /* tls */
    NULL                               /* prev */
  };

  int32_T el_in;
  int32_T el_out;
  uint32_T az_in;
  uint32_T az_out;
  uint32_T r_in;
  uint32_T r_out;
  st.tls = emlrtRootTLSGlobal;

  /* Marshall function inputs */
  az_in = emlrt_marshallIn(&st, emlrtAliasP(prhs[0]), "az_in");
  el_in = c_emlrt_marshallIn(&st, emlrtAliasP(prhs[1]), "el_in");
  r_in = e_emlrt_marshallIn(&st, emlrtAliasP(prhs[2]), "r_in");

  /* Invoke the target function */
  ParalaxCalc_fixpt(az_in, el_in, r_in, &az_out, &el_out, &r_out);

  /* Marshall function outputs */
  plhs[0] = emlrt_marshallOut(&st, az_out);
  if (nlhs > 1) {
    plhs[1] = b_emlrt_marshallOut(&st, el_out);
  }

  if (nlhs > 2) {
    plhs[2] = c_emlrt_marshallOut(&st, r_out);
  }
}

/*
 * Arguments    : void
 * Return Type  : void
 */
void ParalaxCalc_fixpt_atexit(void)
{
  emlrtStack st = { NULL,              /* site */
    NULL,                              /* tls */
    NULL                               /* prev */
  };

  mexFunctionCreateRootTLS();
  st.tls = emlrtRootTLSGlobal;
  emlrtEnterRtStackR2012b(&st);
  emlrtLeaveRtStackR2012b(&st);
  emlrtDestroyRootTLS(&emlrtRootTLSGlobal);
  ParalaxCalc_fixpt_xil_terminate();
  ParalaxCalc_fixpt_xil_shutdown();
  emlrtExitTimeCleanup(&emlrtContextGlobal);
  emlrtDestroyArray(&eml_mx);
  emlrtDestroyArray(&b_eml_mx);
  emlrtDestroyArray(&c_eml_mx);
  emlrtDestroyArray(&d_eml_mx);
  emlrtDestroyArray(&e_eml_mx);
}

/*
 * Arguments    : void
 * Return Type  : void
 */
void ParalaxCalc_fixpt_initialize(void)
{
  emlrtStack st = { NULL,              /* site */
    NULL,                              /* tls */
    NULL                               /* prev */
  };

  mexFunctionCreateRootTLS();
  st.tls = emlrtRootTLSGlobal;
  emlrtClearAllocCountR2012b(&st, false, 3U, "ForceOff");
  emlrtEnterRtStackR2012b(&st);
  if (emlrtFirstTimeR2012b(emlrtRootTLSGlobal)) {
    ParalaxCalc_fixpt_once(&st);
  }
}

/*
 * Arguments    : void
 * Return Type  : void
 */
void ParalaxCalc_fixpt_terminate(void)
{
  emlrtStack st = { NULL,              /* site */
    NULL,                              /* tls */
    NULL                               /* prev */
  };

  st.tls = emlrtRootTLSGlobal;
  emlrtLeaveRtStackR2012b(&st);
  emlrtDestroyRootTLS(&emlrtRootTLSGlobal);
}

/*
 * File trailer for _coder_ParalaxCalc_fixpt_api.c
 *
 * [EOF]
 */
