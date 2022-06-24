
/*
 * Include Files
 *
 */
#if defined(MATLAB_MEX_FILE)
#include "tmwtypes.h"
#include "simstruc_types.h"
#else
#include "rtwtypes.h"
#endif



/* %%%-SFUNWIZ_wrapper_includes_Changes_BEGIN --- EDIT HERE TO _END */
#include <math.h>
#include <windows.h>
#include <iostream>
#include <string>

#ifdef _WIN32
    #define LOAD(path) LoadLibrary(path)
    #define GetProc(handle,str) GetProcAddress(handle,str)
    #define path_str "C:\\Users\\xzhao\\Desktop\\Docker_test\\src\\Control_dll_Gen.dll"
#else 
    #define LOAD(path) dlopen(path)
    #define GetProc(handle,str) dlsym(handle,str)
    #define path_str "/usr/src/Control_dll_Gen.dll"
#endif
/* %%%-SFUNWIZ_wrapper_includes_Changes_END --- EDIT HERE TO _BEGIN */
#define u_width 1
#define y_width 1

/*
 * Create external references here.  
 *
 */
/* %%%-SFUNWIZ_wrapper_externs_Changes_BEGIN --- EDIT HERE TO _END */
/* extern double func(double a); */
/* %%%-SFUNWIZ_wrapper_externs_Changes_END --- EDIT HERE TO _BEGIN */

/*
 * Output function
 *
 */
void Linux_NoInput_Outputs_wrapper(const real_T *xm,
			const real_T *dxm,
			const real_T *ddxm,
			const real_T *xs,
			const real_T *dxs,
			const real_T *ddxs,
			const real_T *mms,
			const real_T *kms,
			const real_T *bms,
			const real_T *um,
			const real_T *us,
			const real_T *mm,
			const real_T *ms,
			const real_T *bit_length,
			const real_T *rho,
			const real_T *rho_,
			const real_T *delta,
			real_T *tau_m,
			real_T *tau_s,
			void **pW,
			const real_T *p0, const int_T p_width0)
{
/* %%%-SFUNWIZ_wrapper_Outputs_Changes_BEGIN --- EDIT HERE TO _END */
/* This sample sets the output equal to the input
      y0[0] = u0[0]; 
 For complex signals use: y0[0].re = u0[0].re; 
      y0[0].im = u0[0].im;
      y1[0].re = u1[0].re;
      y1[0].im = u1[0].im;
 */

    typedef void (__stdcall *f_check)(double,double,double,double,double,
                                        double,double,double,double,double,
                                        double,double,double,int,int,int,double,
                                                    double[]);
    //HINSTANCE hGetProcIDDLL = LoadLibrary("test/Control_dll_Gen.dll");
    //C:\\Users\\xzhao\\Desktop\\Docker_test\\src
    //f_check apply = (f_check)GetProcAddress(hGetProcIDDLL, "control");
    HINSTANCE hGetProcIDDLL = LOAD(path_str);
    f_check apply = (f_check)GetProc(hGetProcIDDLL, "control");

    int bit_length_IN = bit_length[0];
    int rhoIN = rho[0];
    int rho_IN = rho_[0];
    double arr[2];
    double tau_s_in = 0;
    apply(xm[0], dxm[0], ddxm[0], xs[0], dxs[0], 
                 ddxs[0], mms[0], kms[0], bms[0], um[0],
                 us[0], mm[0], ms[0], bit_length_IN, rhoIN, rho_IN, delta[0],
         arr);
    tau_m[0] = arr[0];
    tau_s[0] = arr[1];
/* %%%-SFUNWIZ_wrapper_Outputs_Changes_END --- EDIT HERE TO _BEGIN */
}


