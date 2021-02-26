/*
 * Academic License - for use in teaching, academic research, and meeting
 * course requirements at degree granting institutions only.  Not for
 * government, commercial, or other organizational use.
 * File: main.c
 *
 * MATLAB Coder version            : 5.1
 * C/C++ source code generated on  : 24-Feb-2021 21:34:46
 */

/*************************************************************************/
/* This automatically generated example C main file shows how to call    */
/* entry-point functions that MATLAB Coder generated. You must customize */
/* this file for your application. Do not modify this file directly.     */
/* Instead, make a copy of this file, modify it, and integrate it into   */
/* your development environment.                                         */
/*                                                                       */
/* This file initializes entry-point function arguments to a default     */
/* size and value before calling the entry-point functions. It does      */
/* not store or use any values returned from the entry-point functions.  */
/* If necessary, it does pre-allocate memory for returned values.        */
/* You can use this file as a starting point for a main function that    */
/* you can deploy in your application.                                   */
/*                                                                       */
/* After you copy the file, and before you deploy it, you must make the  */
/* following changes:                                                    */
/* * For variable-size function arguments, change the example sizes to   */
/* the sizes that your application requires.                             */
/* * Change the example values of function arguments to the values that  */
/* your application requires.                                            */
/* * If the entry-point functions return values, store these values or   */
/* otherwise use them as required by your application.                   */
/*                                                                       */
/*************************************************************************/

/* Include Files */
#include "main.h"
#include "ParalaxCalc_fixpt.h"

/* Function Declarations */
static unsigned short argInit_ufix15(void);
static void main_ParalaxCalc_fixpt(void);

/* Function Definitions */
/*
 * Arguments    : void
 * Return Type  : unsigned short
 */
static unsigned short argInit_ufix15(void)
{
  return 0U;
}

/*
 * Arguments    : void
 * Return Type  : void
 */
static void main_ParalaxCalc_fixpt(void)
{
  unsigned short az_out;
  unsigned short el_out;
  unsigned short r_out;

  /* Initialize function 'ParalaxCalc_fixpt' input arguments. */
  /* Call the entry-point 'ParalaxCalc_fixpt'. */
  ParalaxCalc_fixpt(argInit_ufix15(), argInit_ufix15(), argInit_ufix15(),
                    &az_out, &el_out, &r_out);
}

/*
 * Arguments    : int argc
 *                const char * const argv[]
 * Return Type  : int
 */
int main(int argc, const char * const argv[])
{
  (void)argc;
  (void)argv;

  /* The initialize function is being called automatically from your entry-point function. So, a call to initialize is not included here. */
  /* Invoke the entry-point functions.
     You can call entry-point functions multiple times. */
  main_ParalaxCalc_fixpt();

  /* Terminate the application.
     You do not need to do this more than one time. */
  ParalaxCalc_fixpt_terminate();
  return 0;
}

/*
 * File trailer for main.c
 *
 * [EOF]
 */
