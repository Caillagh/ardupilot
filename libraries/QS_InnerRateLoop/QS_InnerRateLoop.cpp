//
// Sponsored License - for use in support of a program or activity
// sponsored by MathWorks.  Not for government, commercial or other
// non-sponsored organizational use.
//
// File: QS_InnerRateLoop.cpp
//
// Code generated for Simulink model 'QS_InnerRateLoop'.
//
// Model version                  : 1.526
// Simulink Coder version         : 9.1 (R2019a) 23-Nov-2018
// C/C++ source code generated on : Fri Nov 22 11:47:45 2019
//
// Target selection: ert.tlc
// Embedded hardware selection: ARM Compatible->ARM Cortex
// Code generation objectives:
//    1. Execution efficiency
//    2. RAM efficiency
//    3. ROM efficiency
// Validation result: Not run
//
#include "QS_InnerRateLoop.h"
#include "QS_InnerRateLoop_private.h"

uint32_T plook_u32ff_evencg(real32_T u, real32_T bp0, real32_T bpSpace, uint32_T
  maxIndex, real32_T *fraction)
{
  uint32_T bpIndex;
  real32_T invSpc;
  real32_T fbpIndex;

  // Prelookup - Index and Fraction
  // Index Search method: 'even'
  // Use previous index: 'off'
  // Use last breakpoint for index at or above upper limit: 'off'
  // Remove protection against out-of-range input in generated code: 'on'

  invSpc = 1.0F / bpSpace;
  fbpIndex = (u - bp0) * invSpc;
  if (fbpIndex < maxIndex) {
    bpIndex = static_cast<uint32_T>(fbpIndex);
    *fraction = (u - (static_cast<real32_T>(bpIndex) * bpSpace + bp0)) * invSpc;
  } else {
    bpIndex = maxIndex - 1U;
    *fraction = 1.0F;
  }

  return bpIndex;
}

real32_T intrp1d_fu32fl_pw(uint32_T bpIndex, real32_T frac, const real32_T
  table[])
{
  // Column-major Interpolation 1-D
  // Interpolation method: 'Linear point-slope'
  // Use last breakpoint for index at or above upper limit: 'off'
  // Overflow mode: 'portable wrapping'

  return (table[bpIndex + 1U] - table[bpIndex]) * frac + table[bpIndex];
}

uint32_T plook_u32ff_evenca(real32_T u, real32_T bp0, real32_T bpSpace, uint32_T
  maxIndex, real32_T *fraction)
{
  uint32_T bpIndex;
  real32_T invSpc;
  real32_T fbpIndex;

  // Prelookup - Index and Fraction
  // Index Search method: 'even'
  // Extrapolation method: 'Clip'
  // Use previous index: 'off'
  // Use last breakpoint for index at or above upper limit: 'on'
  // Remove protection against out-of-range input in generated code: 'off'

  if (u <= bp0) {
    bpIndex = 0U;
    *fraction = 0.0F;
  } else {
    invSpc = 1.0F / bpSpace;
    fbpIndex = (u - bp0) * invSpc;
    if (fbpIndex < maxIndex) {
      bpIndex = static_cast<uint32_T>(fbpIndex);
      *fraction = (u - (static_cast<real32_T>(bpIndex) * bpSpace + bp0)) *
        invSpc;
    } else {
      bpIndex = maxIndex;
      *fraction = 0.0F;
    }
  }

  return bpIndex;
}

real32_T intrp1d_fu32fla_pw(uint32_T bpIndex, real32_T frac, const real32_T
  table[], uint32_T maxIndex)
{
  real32_T y;

  // Column-major Interpolation 1-D
  // Interpolation method: 'Linear point-slope'
  // Use last breakpoint for index at or above upper limit: 'on'
  // Overflow mode: 'portable wrapping'

  if (bpIndex == maxIndex) {
    y = table[bpIndex];
  } else {
    y = (table[bpIndex + 1U] - table[bpIndex]) * frac + table[bpIndex];
  }

  return y;
}

uint32_T plook_u32ff_evenxg(real32_T u, real32_T bp0, real32_T bpSpace, uint32_T
  maxIndex, real32_T *fraction)
{
  uint32_T bpIndex;
  real32_T invSpc;
  real32_T fbpIndex;

  // Prelookup - Index and Fraction
  // Index Search method: 'even'
  // Use previous index: 'off'
  // Use last breakpoint for index at or above upper limit: 'off'
  // Remove protection against out-of-range input in generated code: 'on'

  invSpc = 1.0F / bpSpace;
  fbpIndex = (u - bp0) * invSpc;
  if (fbpIndex < maxIndex) {
    bpIndex = static_cast<uint32_T>(fbpIndex);
    *fraction = (u - (static_cast<real32_T>(bpIndex) * bpSpace + bp0)) * invSpc;
  } else {
    bpIndex = maxIndex - 1U;
    *fraction = (u - (static_cast<real32_T>((maxIndex - 1U)) * bpSpace + bp0)) *
      invSpc;
  }

  return bpIndex;
}

uint32_T plook_u32ff_bincg(real32_T u, const real32_T bp[], uint32_T maxIndex,
  real32_T *fraction)
{
  uint32_T bpIndex;
  uint32_T iRght;
  uint32_T bpIdx;

  // Prelookup - Index and Fraction
  // Index Search method: 'binary'
  // Use previous index: 'off'
  // Use last breakpoint for index at or above upper limit: 'off'
  // Remove protection against out-of-range input in generated code: 'on'

  // Binary Search
  bpIdx = maxIndex >> 1U;
  bpIndex = 0U;
  iRght = maxIndex;
  while (iRght - bpIndex > 1U) {
    if (u < bp[bpIdx]) {
      iRght = bpIdx;
    } else {
      bpIndex = bpIdx;
    }

    bpIdx = (iRght + bpIndex) >> 1U;
  }

  *fraction = (u - bp[bpIndex]) / (bp[bpIndex + 1U] - bp[bpIndex]);
  return bpIndex;
}

real32_T intrp2d_fu32fl_pw(const uint32_T bpIndex[], const real32_T frac[],
  const real32_T table[], const uint32_T stride)
{
  real32_T yL_1d;
  uint32_T offset_1d;

  // Column-major Interpolation 2-D
  // Interpolation method: 'Linear point-slope'
  // Use last breakpoint for index at or above upper limit: 'off'
  // Overflow mode: 'portable wrapping'

  offset_1d = bpIndex[1U] * stride + bpIndex[0U];
  yL_1d = (table[offset_1d + 1U] - table[offset_1d]) * frac[0U] +
    table[offset_1d];
  offset_1d += stride;
  return (((table[offset_1d + 1U] - table[offset_1d]) * frac[0U] +
           table[offset_1d]) - yL_1d) * frac[1U] + yL_1d;
}

// Model step function
void untitledModelClass::step()
{
  int32_T iU;
  uint32_T bpIdx;
  uint32_T bpIdx_0;
  uint32_T bpIndices[2];
  real32_T fractions[2];
  uint32_T bpIndices_0[2];
  real32_T fractions_0[2];
  real32_T rtb_Saturation1_p;
  real32_T rtb_uDLookupTable_cs;
  real32_T rtb_Saturation_h;
  real32_T rtb_Saturation8;
  real32_T rtb_Add5_e;
  real32_T rtb_Add6_i;
  real32_T rtb_TrigonometricFunction6;
  real32_T rtb_TrigonometricFunction3;
  real32_T rtb_TmpSignalConversionAtProduc[9];
  boolean_T rtb_LogicalOperator2_g;
  real_T rtb_Sum2_h;
  boolean_T rtb_LogicalOperator1_n;
  real32_T rtb_Product;
  real32_T rtb_Product_ng;
  real32_T rtb_Saturation2_h;
  real32_T rtb_Product_ee;
  real32_T rtb_Switch2_cz;
  real32_T rtb_Product2;
  real32_T rtb_Gain2;
  real32_T rtb_Sum4_a;
  real32_T rtb_uDLookupTable3;
  real32_T rtb_Sum3_f;
  real32_T rtb_derivativecutofffrequency_b;
  real32_T rtb_Sum4_b;
  real32_T rtb_Add5_ky;
  real32_T rtb_Add7_d;
  real32_T rtb_Sum2_k;
  real32_T rtb_Saturation2_o;
  real32_T rtb_Add6_a;
  real32_T rtb_Switch_ep;
  real32_T rtb_Product_of;
  real32_T rtb_Gain1;
  real32_T rtb_DiscreteTimeIntegrator1;
  boolean_T rtb_LogicalOperator2_e;
  boolean_T rtb_RelationalOperator4_e;
  real_T rtb_Gain_e;
  real32_T rtb_Saturation5_k;
  real32_T rtb_Sum1_c0;
  real32_T rtb_Product_ib;
  real32_T rtb_uDLookupTable1;
  real32_T rtb_DiscreteTimeIntegrator_hs;
  real32_T rtb_Sum1_fe;
  real32_T rtb_Product_jr;
  real32_T rtb_uDLookupTable;
  real32_T rtb_uDLookupTable1_p;
  real32_T rtb_DiscreteTimeIntegrator_cv;
  real32_T rtb_Saturation_k;
  real32_T rtb_uDLookupTable2_bw;
  real32_T rtb_Product_n;
  real32_T rtb_uDLookupTable1_l;
  real32_T rtb_DiscreteTimeIntegrator_nt;
  real32_T rtb_Product_ear;
  real32_T rtb_DiscreteTimeIntegrator_ia;
  real32_T rtb_Product_hg[4];
  real32_T rtb_DeadZone3;
  real32_T rtb_DiscreteTimeIntegrator_fi;
  real32_T rtb_uDLookupTable_a;
  real32_T rtb_DiscreteTimeIntegrator_k1;
  real32_T rtb_Sum1_lq;
  real32_T rtb_DiscreteTimeIntegrator_h;
  real32_T rtb_Sum1_gg;
  real32_T rtb_DiscreteTimeIntegrator_n;
  boolean_T rtb_RelationalOperator_b1;
  real_T rtb_Sum;
  real32_T rtb_DeadZone;
  real32_T rtb_Abs;
  real32_T rtb_Product_cw;
  real32_T rtb_Sum1_gw;
  real32_T rtb_uDLookupTable2[36];
  real32_T rtb_uDLookupTable2_k5[16];
  real32_T rtb_Sum1_f[4];
  real32_T rtb_Product_b[4];
  int32_T i;
  real32_T tmp;
  real32_T rtb_Sum1_j_idx_0;
  real32_T rtb_Sum1_j_idx_1;
  real32_T rtb_Sum1_j_idx_2;
  real32_T rtb_Sum1_j_idx_3;
  int32_T tmp_0;
  real32_T rtb_uDLookupTable_l_tmp;
  real32_T rtb_Saturation_fr_tmp;
  real32_T rtb_TrigonometricFunction3_tmp;
  real32_T rtb_TrigonometricFunction6_tmp;
  real32_T rtb_Product_b_tmp;
  real32_T rtb_derivativecutofffrequency_0;
  real32_T rtb_Product_b_tmp_0;

  // Trigonometry: '<S8>/Trigonometric Function3' incorporates:
  //   Inport: '<Root>/psi_rad'
  //   Trigonometry: '<S67>/Trigonometric Function3'

  rtb_Gain1 = static_cast<real32_T>(cos((real_T)QS_InnerRateLoop_U.psi_rad));

  // Trigonometry: '<S8>/Trigonometric Function6' incorporates:
  //   Inport: '<Root>/psi_rad'
  //   Trigonometry: '<S67>/Trigonometric Function6'

  rtb_uDLookupTable_l_tmp = static_cast<real32_T>(sin((real_T)
    QS_InnerRateLoop_U.psi_rad));

  // Sum: '<S8>/Add5' incorporates:
  //   Inport: '<Root>/vD_fps (KF)'
  //   Inport: '<Root>/vE_fps (KF)'
  //   Inport: '<Root>/vN_fps (KF)'
  //   Product: '<S8>/Divide'
  //   Product: '<S8>/Divide2'
  //   Product: '<S8>/Divide6'
  //   Trigonometry: '<S8>/Trigonometric Function3'
  //   Trigonometry: '<S8>/Trigonometric Function6'

  rtb_Add5_e = (QS_InnerRateLoop_ConstB.TrigonometricFunction2 * rtb_Gain1 *
                QS_InnerRateLoop_U.vN_fpsKF +
                QS_InnerRateLoop_ConstB.TrigonometricFunction2 *
                rtb_uDLookupTable_l_tmp * QS_InnerRateLoop_U.vE_fpsKF) +
    -QS_InnerRateLoop_ConstB.TrigonometricFunction5 *
    QS_InnerRateLoop_U.vD_fpsKF;

  // Product: '<S8>/Divide1' incorporates:
  //   Product: '<S8>/Divide7'

  rtb_Add6_i = QS_InnerRateLoop_ConstB.TrigonometricFunction4 *
    QS_InnerRateLoop_ConstB.TrigonometricFunction5;

  // Sum: '<S8>/Add6' incorporates:
  //   Inport: '<Root>/vD_fps (KF)'
  //   Inport: '<Root>/vE_fps (KF)'
  //   Inport: '<Root>/vN_fps (KF)'
  //   Product: '<S8>/Divide1'
  //   Product: '<S8>/Divide11'
  //   Product: '<S8>/Divide13'
  //   Product: '<S8>/Divide15'
  //   Product: '<S8>/Divide3'
  //   Product: '<S8>/Divide7'
  //   Product: '<S8>/Divide8'
  //   Sum: '<S8>/Add1'
  //   Sum: '<S8>/Add3'
  //   Trigonometry: '<S8>/Trigonometric Function3'
  //   Trigonometry: '<S8>/Trigonometric Function6'

  rtb_Add6_i = ((rtb_Add6_i * rtb_Gain1 -
                 QS_InnerRateLoop_ConstB.TrigonometricFunction1 *
                 rtb_uDLookupTable_l_tmp) * QS_InnerRateLoop_U.vN_fpsKF +
                (rtb_Add6_i * rtb_uDLookupTable_l_tmp +
                 QS_InnerRateLoop_ConstB.TrigonometricFunction1 * rtb_Gain1) *
                QS_InnerRateLoop_U.vE_fpsKF) +
    QS_InnerRateLoop_ConstB.TrigonometricFunction4 *
    QS_InnerRateLoop_ConstB.TrigonometricFunction2 * QS_InnerRateLoop_U.vD_fpsKF;

  // Sqrt: '<Root>/Sqrt1' incorporates:
  //   Math: '<Root>/Math Function3'
  //   Math: '<Root>/Math Function4'
  //   Sum: '<Root>/Add1'
  //
  //  About '<Root>/Math Function3':
  //   Operator: magnitude^2
  //
  //  About '<Root>/Math Function4':
  //   Operator: magnitude^2

  rtb_Saturation8 = static_cast<real32_T>(sqrt((real_T)(rtb_Add5_e * rtb_Add5_e
    + rtb_Add6_i * rtb_Add6_i)));

  // Saturate: '<Root>/Saturation8'
  if (rtb_Saturation8 > 6.5F) {
    rtb_Saturation8 = 6.5F;
  } else {
    if (rtb_Saturation8 < 0.0F) {
      rtb_Saturation8 = 0.0F;
    }
  }

  // End of Saturate: '<Root>/Saturation8'

  // Lookup_n-D: '<S59>/1-D Lookup Table2' incorporates:
  //   Constant: '<S59>/Constant'
  //   Delay: '<S12>/Delay1'
  //   Lookup_n-D: '<S58>/1-D Lookup Table2'

  bpIndices[0U] = plook_u32ff_bincg(rtb_Saturation8,
    QS_InnerRateLoop_ConstP.pooled7, 4U, &rtb_Saturation5_k);
  fractions[0U] = rtb_Saturation5_k;
  for (iU = 0; iU < 36; iU++) {
    bpIndices[1U] = plook_u32ff_bincg(QS_InnerRateLoop_ConstP.pooled16[iU],
      QS_InnerRateLoop_ConstP.pooled16, 35U, &rtb_Saturation5_k);
    fractions[1U] = rtb_Saturation5_k;
    rtb_uDLookupTable2[iU] = intrp2d_fu32fl_pw(bpIndices, fractions,
      QS_InnerRateLoop_ConstP.uDLookupTable2_tableData_g, 5U);
  }

  // Lookup_n-D: '<S58>/1-D Lookup Table2' incorporates:
  //   Constant: '<S58>/Constant'
  //   Delay: '<S12>/Delay1'
  //   Lookup_n-D: '<S59>/1-D Lookup Table2'

  bpIndices_0[0U] = plook_u32ff_evencg(rtb_Saturation8, 0.0F, 1.75F, 4U,
    &rtb_Saturation5_k);
  fractions_0[0U] = rtb_Saturation5_k;
  for (iU = 0; iU < 16; iU++) {
    bpIndices_0[1U] = plook_u32ff_evencg(QS_InnerRateLoop_ConstP.pooled17[iU],
      1.0F, 1.0F, 15U, &rtb_Saturation5_k);
    fractions_0[1U] = rtb_Saturation5_k;
    rtb_uDLookupTable2_k5[iU] = intrp2d_fu32fl_pw(bpIndices_0, fractions_0,
      QS_InnerRateLoop_ConstP.uDLookupTable2_tableData_b, 5U);
  }

  // Trigonometry: '<S7>/Trigonometric Function2' incorporates:
  //   Inport: '<Root>/theta_rad'
  //   Trigonometry: '<S6>/Trigonometric Function2'

  rtb_Saturation_fr_tmp = static_cast<real32_T>(cos((real_T)
    QS_InnerRateLoop_U.theta_rad));

  // Product: '<S8>/Divide4' incorporates:
  //   Product: '<S8>/Divide9'

  rtb_uDLookupTable_cs = QS_InnerRateLoop_ConstB.TrigonometricFunction1 *
    QS_InnerRateLoop_ConstB.TrigonometricFunction5;

  // Sum: '<S8>/Add7' incorporates:
  //   Inport: '<Root>/vD_fps (KF)'
  //   Inport: '<Root>/vE_fps (KF)'
  //   Inport: '<Root>/vN_fps (KF)'
  //   Product: '<S8>/Divide10'
  //   Product: '<S8>/Divide12'
  //   Product: '<S8>/Divide14'
  //   Product: '<S8>/Divide16'
  //   Product: '<S8>/Divide4'
  //   Product: '<S8>/Divide5'
  //   Product: '<S8>/Divide9'
  //   Sum: '<S8>/Add2'
  //   Sum: '<S8>/Add4'
  //   Trigonometry: '<S8>/Trigonometric Function3'
  //   Trigonometry: '<S8>/Trigonometric Function6'

  rtb_uDLookupTable_cs = ((rtb_uDLookupTable_cs * rtb_Gain1 +
    QS_InnerRateLoop_ConstB.TrigonometricFunction4 * rtb_uDLookupTable_l_tmp) *
    QS_InnerRateLoop_U.vN_fpsKF + (rtb_uDLookupTable_cs *
    rtb_uDLookupTable_l_tmp - QS_InnerRateLoop_ConstB.TrigonometricFunction4 *
    rtb_Gain1) * QS_InnerRateLoop_U.vE_fpsKF) +
    QS_InnerRateLoop_ConstB.TrigonometricFunction1 *
    QS_InnerRateLoop_ConstB.TrigonometricFunction2 * QS_InnerRateLoop_U.vD_fpsKF;

  // Trigonometry: '<S7>/Trigonometric Function5' incorporates:
  //   Inport: '<Root>/theta_rad'

  rtb_Saturation1_p = static_cast<real32_T>(sin((real_T)
    QS_InnerRateLoop_U.theta_rad));

  // Trigonometry: '<S7>/Trigonometric Function4' incorporates:
  //   Inport: '<Root>/phi_rad'
  //   Trigonometry: '<S6>/Trigonometric Function4'

  rtb_TrigonometricFunction6_tmp = static_cast<real32_T>(sin((real_T)
    QS_InnerRateLoop_U.phi_rad));

  // Trigonometry: '<S7>/Trigonometric Function1' incorporates:
  //   Inport: '<Root>/phi_rad'
  //   Trigonometry: '<S6>/Trigonometric Function1'

  rtb_TrigonometricFunction3_tmp = static_cast<real32_T>(cos((real_T)
    QS_InnerRateLoop_U.phi_rad));

  // SignalConversion: '<S59>/TmpSignal ConversionAtProductInport2' incorporates:
  //   Product: '<S7>/Divide'
  //   Product: '<S7>/Divide2'
  //   Product: '<S7>/Divide6'
  //   Sum: '<S7>/Add5'
  //   Trigonometry: '<S7>/Trigonometric Function2'

  rtb_TmpSignalConversionAtProduc[0] = (rtb_Saturation_fr_tmp *
    QS_InnerRateLoop_ConstB.TrigonometricFunction3 * rtb_Add5_e +
    rtb_Saturation_fr_tmp * QS_InnerRateLoop_ConstB.TrigonometricFunction6 *
    rtb_Add6_i) + -rtb_Saturation1_p * rtb_uDLookupTable_cs;

  // Product: '<S7>/Divide1' incorporates:
  //   Product: '<S7>/Divide7'
  //   Trigonometry: '<S7>/Trigonometric Function4'

  rtb_Saturation_h = rtb_TrigonometricFunction6_tmp * rtb_Saturation1_p;

  // SignalConversion: '<S59>/TmpSignal ConversionAtProductInport2' incorporates:
  //   Product: '<S7>/Divide1'
  //   Product: '<S7>/Divide11'
  //   Product: '<S7>/Divide13'
  //   Product: '<S7>/Divide15'
  //   Product: '<S7>/Divide3'
  //   Product: '<S7>/Divide7'
  //   Product: '<S7>/Divide8'
  //   Sum: '<S7>/Add1'
  //   Sum: '<S7>/Add3'
  //   Sum: '<S7>/Add6'
  //   Trigonometry: '<S7>/Trigonometric Function1'
  //   Trigonometry: '<S7>/Trigonometric Function2'
  //   Trigonometry: '<S7>/Trigonometric Function4'

  rtb_TmpSignalConversionAtProduc[1] = ((rtb_Saturation_h *
    QS_InnerRateLoop_ConstB.TrigonometricFunction3 -
    rtb_TrigonometricFunction3_tmp *
    QS_InnerRateLoop_ConstB.TrigonometricFunction6) * rtb_Add5_e +
    (rtb_Saturation_h * QS_InnerRateLoop_ConstB.TrigonometricFunction6 +
     rtb_TrigonometricFunction3_tmp *
     QS_InnerRateLoop_ConstB.TrigonometricFunction3) * rtb_Add6_i) +
    rtb_TrigonometricFunction6_tmp * rtb_Saturation_fr_tmp *
    rtb_uDLookupTable_cs;

  // Product: '<S7>/Divide4' incorporates:
  //   Product: '<S7>/Divide9'
  //   Trigonometry: '<S7>/Trigonometric Function1'

  rtb_Saturation_h = rtb_TrigonometricFunction3_tmp * rtb_Saturation1_p;

  // SignalConversion: '<S59>/TmpSignal ConversionAtProductInport2' incorporates:
  //   Inport: '<Root>/p_rps'
  //   Inport: '<Root>/phi_rad'
  //   Inport: '<Root>/psi_rad'
  //   Inport: '<Root>/q_rps'
  //   Inport: '<Root>/r_rps'
  //   Inport: '<Root>/theta_rad'
  //   Product: '<S7>/Divide10'
  //   Product: '<S7>/Divide12'
  //   Product: '<S7>/Divide14'
  //   Product: '<S7>/Divide16'
  //   Product: '<S7>/Divide4'
  //   Product: '<S7>/Divide5'
  //   Product: '<S7>/Divide9'
  //   Sum: '<S7>/Add2'
  //   Sum: '<S7>/Add4'
  //   Sum: '<S7>/Add7'
  //   Trigonometry: '<S7>/Trigonometric Function1'
  //   Trigonometry: '<S7>/Trigonometric Function2'
  //   Trigonometry: '<S7>/Trigonometric Function4'

  rtb_TmpSignalConversionAtProduc[2] = ((rtb_Saturation_h *
    QS_InnerRateLoop_ConstB.TrigonometricFunction3 +
    rtb_TrigonometricFunction6_tmp *
    QS_InnerRateLoop_ConstB.TrigonometricFunction6) * rtb_Add5_e +
    (rtb_Saturation_h * QS_InnerRateLoop_ConstB.TrigonometricFunction6 -
     rtb_TrigonometricFunction6_tmp *
     QS_InnerRateLoop_ConstB.TrigonometricFunction3) * rtb_Add6_i) +
    rtb_TrigonometricFunction3_tmp * rtb_Saturation_fr_tmp *
    rtb_uDLookupTable_cs;
  rtb_TmpSignalConversionAtProduc[3] = QS_InnerRateLoop_U.p_rps;
  rtb_TmpSignalConversionAtProduc[4] = QS_InnerRateLoop_U.q_rps;
  rtb_TmpSignalConversionAtProduc[5] = QS_InnerRateLoop_U.r_rps;
  rtb_TmpSignalConversionAtProduc[6] = QS_InnerRateLoop_U.phi_rad;
  rtb_TmpSignalConversionAtProduc[7] = QS_InnerRateLoop_U.theta_rad;
  rtb_TmpSignalConversionAtProduc[8] = QS_InnerRateLoop_U.psi_rad;

  // Sum: '<S90>/Sum2' incorporates:
  //   Delay: '<S90>/Delay1'
  //   Delay: '<S90>/Delay2'
  //   Inport: '<Root>/CH8_flag'
  //   RelationalOperator: '<S90>/Relational Operator2'

  rtb_Sum2_h = static_cast<real_T>((QS_InnerRateLoop_U.CH8_flag >
    QS_InnerRateLoop_DWork.Delay1_DSTATE)) +
    QS_InnerRateLoop_DWork.Delay2_DSTATE;

  // Outputs for Enabled SubSystem: '<S10>/Enabled Subsystem1' incorporates:
  //   EnablePort: '<S92>/Enable'

  // Logic: '<S10>/Logical Operator3' incorporates:
  //   Inport: '<Root>/CH8_flag'
  //   Inport: '<Root>/input_col'
  //   Inport: '<Root>/input_lat'
  //   Inport: '<Root>/input_lon'
  //   Inport: '<Root>/input_ped'
  //   Inport: '<S92>/col'
  //   Inport: '<S92>/lat'
  //   Inport: '<S92>/lon'
  //   Inport: '<S92>/ped'

  if (is_zero(QS_InnerRateLoop_U.CH8_flag)) {
    QS_InnerRateLoop_B.lon = QS_InnerRateLoop_U.input_lon;
    QS_InnerRateLoop_B.lat = QS_InnerRateLoop_U.input_lat;
    QS_InnerRateLoop_B.col_h = QS_InnerRateLoop_U.input_col;
    QS_InnerRateLoop_B.ped = QS_InnerRateLoop_U.input_ped;
  }

  // End of Logic: '<S10>/Logical Operator3'
  // End of Outputs for SubSystem: '<S10>/Enabled Subsystem1'

  // Sum: '<S10>/Sum1' incorporates:
  //   Inport: '<Root>/input_lon'

  rtb_TrigonometricFunction3 = QS_InnerRateLoop_U.input_lon -
    QS_InnerRateLoop_B.lon;

  // DeadZone: '<S91>/Dead Zone2'
  if (rtb_TrigonometricFunction3 > 0.05F) {
    rtb_TrigonometricFunction3 -= 0.05F;
  } else if (rtb_TrigonometricFunction3 >= -0.05F) {
    rtb_TrigonometricFunction3 = 0.0F;
  } else {
    rtb_TrigonometricFunction3 -= -0.05F;
  }

  // End of DeadZone: '<S91>/Dead Zone2'

  // Abs: '<S91>/Abs'
  rtb_TrigonometricFunction3 = static_cast<real32_T>(fabs((real_T)
    rtb_TrigonometricFunction3));

  // Sum: '<S10>/Sum2' incorporates:
  //   Inport: '<Root>/input_lat'

  rtb_TrigonometricFunction6 = QS_InnerRateLoop_U.input_lat -
    QS_InnerRateLoop_B.lat;

  // DeadZone: '<S91>/Dead Zone1'
  if (rtb_TrigonometricFunction6 > 0.05F) {
    rtb_TrigonometricFunction6 -= 0.05F;
  } else if (rtb_TrigonometricFunction6 >= -0.05F) {
    rtb_TrigonometricFunction6 = 0.0F;
  } else {
    rtb_TrigonometricFunction6 -= -0.05F;
  }

  // End of DeadZone: '<S91>/Dead Zone1'

  // Abs: '<S91>/Abs1'
  rtb_TrigonometricFunction6 = static_cast<real32_T>(fabs((real_T)
    rtb_TrigonometricFunction6));

  // Sum: '<S10>/Sum3' incorporates:
  //   Inport: '<Root>/input_col'

  rtb_Saturation_h = QS_InnerRateLoop_U.input_col - QS_InnerRateLoop_B.col_h;

  // DeadZone: '<S91>/Dead Zone3'
  if (rtb_Saturation_h > 0.05F) {
    rtb_Saturation_h -= 0.05F;
  } else if (rtb_Saturation_h >= -0.05F) {
    rtb_Saturation_h = 0.0F;
  } else {
    rtb_Saturation_h -= -0.05F;
  }

  // End of DeadZone: '<S91>/Dead Zone3'

  // Abs: '<S91>/Abs2'
  rtb_Saturation_h = static_cast<real32_T>(fabs((real_T)rtb_Saturation_h));

  // Sum: '<S10>/Sum4' incorporates:
  //   Inport: '<Root>/input_ped'

  rtb_Saturation1_p = QS_InnerRateLoop_U.input_ped - QS_InnerRateLoop_B.ped;

  // DeadZone: '<S91>/Dead Zone4'
  if (rtb_Saturation1_p > 0.05F) {
    rtb_Saturation1_p -= 0.05F;
  } else if (rtb_Saturation1_p >= -0.05F) {
    rtb_Saturation1_p = 0.0F;
  } else {
    rtb_Saturation1_p -= -0.05F;
  }

  // End of DeadZone: '<S91>/Dead Zone4'

  // Abs: '<S91>/Abs3'
  rtb_Saturation1_p = static_cast<real32_T>(fabs((real_T)rtb_Saturation1_p));

  // Logic: '<S10>/Logical Operator2' incorporates:
  //   Inport: '<Root>/CH8_flag'
  //   Logic: '<S91>/Logical Operator'
  //   Logic: '<S91>/Logical Operator1'

  rtb_LogicalOperator2_g = ((is_zero(rtb_TrigonometricFunction3)) &&
    (is_zero(rtb_TrigonometricFunction6)) && (is_zero(rtb_Saturation_h)) &&
    (is_zero(rtb_Saturation1_p)) && (!is_zero(QS_InnerRateLoop_U.CH8_flag)));

  // Logic: '<S10>/Logical Operator1'
  rtb_LogicalOperator1_n = ((!is_zero(rtb_Sum2_h)) && rtb_LogicalOperator2_g);

  // DiscreteIntegrator: '<S89>/Discrete-Time Integrator'
  if (rtb_LogicalOperator1_n &&
      (QS_InnerRateLoop_DWork.DiscreteTimeIntegrator_PrevRese <= 0)) {
    QS_InnerRateLoop_DWork.DiscreteTimeIntegrator_DSTATE_a = 0.0F;
  }

  // Lookup_n-D: '<S87>/1-D Lookup Table2'
  bpIdx = plook_u32ff_evencg(rtb_Saturation8, 0.0F, 1.75F, 4U,
    &rtb_Saturation5_k);

  // DiscreteIntegrator: '<S64>/Discrete-Time Integrator' incorporates:
  //   DiscreteIntegrator: '<S12>/Discrete-Time Integrator'
  //   DiscreteIntegrator: '<S64>/Discrete-Time Integrator1'
  //   DiscreteIntegrator: '<S64>/Discrete-Time Integrator2'
  //   Inport: '<Root>/pos North (KF)'

  if (QS_InnerRateLoop_DWork.DiscreteTimeIntegrator_IC_LOADI != 0) {
    QS_InnerRateLoop_DWork.DiscreteTimeIntegrator_DSTATE_m =
      QS_InnerRateLoop_U.posNorthKF;
  }

  rtb_RelationalOperator4_e = !rtb_LogicalOperator1_n;
  if ((rtb_LogicalOperator1_n &&
       (QS_InnerRateLoop_DWork.DiscreteTimeIntegrator_PrevRe_a <= 0)) ||
      (rtb_RelationalOperator4_e &&
       (QS_InnerRateLoop_DWork.DiscreteTimeIntegrator_PrevRe_a == 1))) {
    QS_InnerRateLoop_DWork.DiscreteTimeIntegrator_DSTATE_m =
      QS_InnerRateLoop_U.posNorthKF;
  }

  // Product: '<S87>/Product' incorporates:
  //   DiscreteIntegrator: '<S64>/Discrete-Time Integrator'
  //   Inport: '<Root>/pos North (KF)'
  //   Lookup_n-D: '<S87>/1-D Lookup Table2'
  //   Sum: '<S72>/Sum'

  rtb_Product = (QS_InnerRateLoop_DWork.DiscreteTimeIntegrator_DSTATE_m -
                 QS_InnerRateLoop_U.posNorthKF) * intrp1d_fu32fl_pw(bpIdx,
    rtb_Saturation5_k, QS_InnerRateLoop_ConstP.pooled19);

  // Sum: '<S72>/Sum1' incorporates:
  //   DiscreteIntegrator: '<S89>/Discrete-Time Integrator'

  rtb_Saturation_h = QS_InnerRateLoop_DWork.DiscreteTimeIntegrator_DSTATE_a +
    rtb_Product;

  // Saturate: '<S65>/Saturation'
  if (rtb_Saturation_h > 10.0F) {
    rtb_Saturation_h = 10.0F;
  } else {
    if (rtb_Saturation_h < -10.0F) {
      rtb_Saturation_h = -10.0F;
    }
  }

  // End of Saturate: '<S65>/Saturation'

  // DiscreteIntegrator: '<S86>/Discrete-Time Integrator'
  if (rtb_LogicalOperator1_n &&
      (QS_InnerRateLoop_DWork.DiscreteTimeIntegrator_PrevRe_o <= 0)) {
    QS_InnerRateLoop_DWork.DiscreteTimeIntegrator_DSTATE_h = 0.0F;
  }

  // Lookup_n-D: '<S84>/1-D Lookup Table2'
  bpIdx = plook_u32ff_evencg(rtb_Saturation8, 0.0F, 1.75F, 4U,
    &rtb_Saturation5_k);

  // DiscreteIntegrator: '<S64>/Discrete-Time Integrator1' incorporates:
  //   Inport: '<Root>/pos East (KF)'

  if (QS_InnerRateLoop_DWork.DiscreteTimeIntegrator1_IC_LOAD != 0) {
    QS_InnerRateLoop_DWork.DiscreteTimeIntegrator1_DSTATE =
      QS_InnerRateLoop_U.posEastKF;
  }

  if ((rtb_LogicalOperator1_n &&
       (QS_InnerRateLoop_DWork.DiscreteTimeIntegrator1_PrevRes <= 0)) ||
      (rtb_RelationalOperator4_e &&
       (QS_InnerRateLoop_DWork.DiscreteTimeIntegrator1_PrevRes == 1))) {
    QS_InnerRateLoop_DWork.DiscreteTimeIntegrator1_DSTATE =
      QS_InnerRateLoop_U.posEastKF;
  }

  // Product: '<S84>/Product' incorporates:
  //   DiscreteIntegrator: '<S64>/Discrete-Time Integrator1'
  //   Inport: '<Root>/pos East (KF)'
  //   Lookup_n-D: '<S84>/1-D Lookup Table2'
  //   Sum: '<S71>/Sum'

  rtb_Product_ng = (QS_InnerRateLoop_DWork.DiscreteTimeIntegrator1_DSTATE -
                    QS_InnerRateLoop_U.posEastKF) * intrp1d_fu32fl_pw(bpIdx,
    rtb_Saturation5_k, QS_InnerRateLoop_ConstP.pooled19);

  // Sum: '<S71>/Sum1' incorporates:
  //   DiscreteIntegrator: '<S86>/Discrete-Time Integrator'

  rtb_Saturation1_p = QS_InnerRateLoop_DWork.DiscreteTimeIntegrator_DSTATE_h +
    rtb_Product_ng;

  // Saturate: '<S65>/Saturation1'
  if (rtb_Saturation1_p > 10.0F) {
    rtb_Saturation1_p = 10.0F;
  } else {
    if (rtb_Saturation1_p < -10.0F) {
      rtb_Saturation1_p = -10.0F;
    }
  }

  // End of Saturate: '<S65>/Saturation1'

  // DiscreteIntegrator: '<S83>/Discrete-Time Integrator'
  if (rtb_LogicalOperator1_n &&
      (QS_InnerRateLoop_DWork.DiscreteTimeIntegrator_PrevRe_b <= 0)) {
    QS_InnerRateLoop_DWork.DiscreteTimeIntegrator_DSTATE_c = 0.0F;
  }

  // Lookup_n-D: '<S82>/1-D Lookup Table2'
  bpIdx = plook_u32ff_evencg(rtb_Saturation8, 0.0F, 1.75F, 4U,
    &rtb_Saturation5_k);

  // DiscreteIntegrator: '<S64>/Discrete-Time Integrator2' incorporates:
  //   Inport: '<Root>/pos Down (KF)'

  if (QS_InnerRateLoop_DWork.DiscreteTimeIntegrator2_IC_LOAD != 0) {
    QS_InnerRateLoop_DWork.DiscreteTimeIntegrator2_DSTATE =
      QS_InnerRateLoop_U.posDownKF;
  }

  if ((rtb_LogicalOperator1_n &&
       (QS_InnerRateLoop_DWork.DiscreteTimeIntegrator2_PrevRes <= 0)) ||
      (rtb_RelationalOperator4_e &&
       (QS_InnerRateLoop_DWork.DiscreteTimeIntegrator2_PrevRes == 1))) {
    QS_InnerRateLoop_DWork.DiscreteTimeIntegrator2_DSTATE =
      QS_InnerRateLoop_U.posDownKF;
  }

  // Product: '<S82>/Product' incorporates:
  //   DiscreteIntegrator: '<S64>/Discrete-Time Integrator2'
  //   Inport: '<Root>/pos Down (KF)'
  //   Lookup_n-D: '<S82>/1-D Lookup Table2'
  //   Sum: '<S70>/Sum'

  rtb_Product_ee = (QS_InnerRateLoop_DWork.DiscreteTimeIntegrator2_DSTATE -
                    QS_InnerRateLoop_U.posDownKF) * intrp1d_fu32fl_pw(bpIdx,
    rtb_Saturation5_k, QS_InnerRateLoop_ConstP.uDLookupTable2_tableData_k);

  // Sum: '<S70>/Sum1' incorporates:
  //   DiscreteIntegrator: '<S83>/Discrete-Time Integrator'

  rtb_Saturation2_h = QS_InnerRateLoop_DWork.DiscreteTimeIntegrator_DSTATE_c +
    rtb_Product_ee;

  // Saturate: '<S65>/Saturation2'
  if (rtb_Saturation2_h > 15.0F) {
    rtb_Saturation2_h = 15.0F;
  } else {
    if (rtb_Saturation2_h < -15.0F) {
      rtb_Saturation2_h = -15.0F;
    }
  }

  // End of Saturate: '<S65>/Saturation2'

  // Product: '<S11>/Product2' incorporates:
  //   DataTypeConversion: '<Root>/Data Type Conversion'
  //   Sum: '<S11>/Sum21'
  //   UnitDelay: '<S11>/Unit Delay'

  rtb_Product2 = (static_cast<real32_T>(rtb_LogicalOperator1_n) +
                  QS_InnerRateLoop_DWork.UnitDelay_DSTATE) * static_cast<
    real32_T>(rtb_LogicalOperator1_n);

  // Gain: '<S11>/Gain2'
  rtb_Gain2 = 0.0025F * rtb_Product2;

  // Switch: '<S11>/Switch1' incorporates:
  //   Constant: '<S11>/Constant'
  //   Constant: '<S11>/Constant1'
  //   Sum: '<S11>/Sum'

  if (rtb_Gain2 >= 20.0F) {
    rtb_uDLookupTable3 = rtb_Gain2 - 20.0F;
  } else {
    rtb_uDLookupTable3 = 0.0F;
  }

  // End of Switch: '<S11>/Switch1'

  // Product: '<S11>/Divide1' incorporates:
  //   Inport: '<Root>/Rp'
  //   Inport: '<Root>/Rv'

  rtb_Sum4_a = rtb_uDLookupTable3 / QS_InnerRateLoop_U.Rv *
    QS_InnerRateLoop_U.Rp;

  // Lookup_n-D: '<S11>/1-D Lookup Table3'
  bpIdx = plook_u32ff_evenca(rtb_Sum4_a, 0.0F, 0.192F, 37U, &rtb_Saturation5_k);
  rtb_uDLookupTable3 = intrp1d_fu32fla_pw(bpIdx, rtb_Saturation5_k,
    QS_InnerRateLoop_ConstP.pooled25, 37U);

  // Gain: '<S11>/Gain1'
  rtb_Sum3_f = 0.0174532924F * rtb_uDLookupTable3;

  // Trigonometry: '<S93>/Trigonometric Function3'
  rtb_derivativecutofffrequency_b = static_cast<real32_T>(cos((real_T)rtb_Sum3_f));

  // Trigonometry: '<S93>/Trigonometric Function6'
  rtb_Sum3_f = static_cast<real32_T>(sin((real_T)rtb_Sum3_f));

  // Lookup_n-D: '<S11>/1-D Lookup Table1'
  bpIdx = plook_u32ff_evenca(rtb_Sum4_a, 0.0F, 0.192F, 37U, &rtb_Saturation5_k);

  // Product: '<S11>/Divide3' incorporates:
  //   Inport: '<Root>/Rv'
  //   Lookup_n-D: '<S11>/1-D Lookup Table1'

  rtb_Sum4_b = intrp1d_fu32fla_pw(bpIdx, rtb_Saturation5_k,
    QS_InnerRateLoop_ConstP.uDLookupTable1_tableData, 37U) /
    QS_InnerRateLoop_U.Rv;

  // Lookup_n-D: '<S11>/1-D Lookup Table'
  bpIdx = plook_u32ff_evenca(rtb_Sum4_a, 0.0F, 0.192F, 37U, &rtb_Saturation5_k);

  // Product: '<S11>/Divide2' incorporates:
  //   Inport: '<Root>/Rv'
  //   Lookup_n-D: '<S11>/1-D Lookup Table'

  rtb_Add5_ky = intrp1d_fu32fla_pw(bpIdx, rtb_Saturation5_k,
    QS_InnerRateLoop_ConstP.pooled25, 37U) / QS_InnerRateLoop_U.Rv;

  // Lookup_n-D: '<S11>/1-D Lookup Table2'
  bpIdx = plook_u32ff_evenca(rtb_Sum4_a, 0.0F, 0.192F, 37U, &rtb_Saturation5_k);

  // Product: '<S11>/Divide4' incorporates:
  //   Inport: '<Root>/Rv'
  //   Lookup_n-D: '<S11>/1-D Lookup Table2'

  rtb_Sum4_a = intrp1d_fu32fla_pw(bpIdx, rtb_Saturation5_k,
    QS_InnerRateLoop_ConstP.pooled25, 37U) / QS_InnerRateLoop_U.Rv;

  // Product: '<S93>/Divide4' incorporates:
  //   Product: '<S93>/Divide9'

  rtb_Add7_d = QS_InnerRateLoop_ConstB.TrigonometricFunction1_k *
    QS_InnerRateLoop_ConstB.TrigonometricFunction5_o;

  // Sum: '<S93>/Add7' incorporates:
  //   Product: '<S93>/Divide10'
  //   Product: '<S93>/Divide12'
  //   Product: '<S93>/Divide14'
  //   Product: '<S93>/Divide16'
  //   Product: '<S93>/Divide4'
  //   Product: '<S93>/Divide5'
  //   Product: '<S93>/Divide9'
  //   Sum: '<S93>/Add2'
  //   Sum: '<S93>/Add4'

  rtb_Add7_d = ((rtb_Add7_d * rtb_derivativecutofffrequency_b +
                 QS_InnerRateLoop_ConstB.TrigonometricFunction4_n * rtb_Sum3_f) *
                rtb_Sum4_b + (rtb_Add7_d * rtb_Sum3_f -
    QS_InnerRateLoop_ConstB.TrigonometricFunction4_n *
    rtb_derivativecutofffrequency_b) * rtb_Add5_ky) +
    QS_InnerRateLoop_ConstB.TrigonometricFunction1_k *
    QS_InnerRateLoop_ConstB.TrigonometricFunction2_l * rtb_Sum4_a;

  // Product: '<S67>/Divide4' incorporates:
  //   Product: '<S67>/Divide9'

  rtb_Sum2_k = QS_InnerRateLoop_ConstB.TrigonometricFunction1_g *
    QS_InnerRateLoop_ConstB.TrigonometricFunction5_j;

  // Sum: '<S65>/Sum2' incorporates:
  //   Product: '<S67>/Divide10'
  //   Product: '<S67>/Divide12'
  //   Product: '<S67>/Divide14'
  //   Product: '<S67>/Divide16'
  //   Product: '<S67>/Divide4'
  //   Product: '<S67>/Divide5'
  //   Product: '<S67>/Divide9'
  //   Sum: '<S67>/Add2'
  //   Sum: '<S67>/Add4'
  //   Sum: '<S67>/Add7'

  rtb_Sum2_k = (((rtb_Sum2_k * rtb_Gain1 +
                  QS_InnerRateLoop_ConstB.TrigonometricFunction4_k *
                  rtb_uDLookupTable_l_tmp) * rtb_Saturation_h + (rtb_Sum2_k *
    rtb_uDLookupTable_l_tmp - QS_InnerRateLoop_ConstB.TrigonometricFunction4_k *
    rtb_Gain1) * rtb_Saturation1_p) +
                QS_InnerRateLoop_ConstB.TrigonometricFunction1_g *
                QS_InnerRateLoop_ConstB.TrigonometricFunction2_a *
                rtb_Saturation2_h) + rtb_Add7_d;

  // Saturate: '<S12>/Saturation2'
  if (rtb_Sum2_k > 15.0F) {
    rtb_Saturation2_o = 15.0F;
  } else if (rtb_Sum2_k < -15.0F) {
    rtb_Saturation2_o = -15.0F;
  } else {
    rtb_Saturation2_o = rtb_Sum2_k;
  }

  // End of Saturate: '<S12>/Saturation2'

  // Outputs for Enabled SubSystem: '<S12>/Enabled Subsystem1' incorporates:
  //   EnablePort: '<S94>/Enable'

  // Logic: '<S12>/Logical Operator2' incorporates:
  //   Inport: '<Root>/engage'
  //   Inport: '<Root>/input_col'
  //   Inport: '<S94>/col'

  if (!QS_InnerRateLoop_U.engage) {
    QS_InnerRateLoop_B.col = QS_InnerRateLoop_U.input_col;
  }

  // End of Logic: '<S12>/Logical Operator2'
  // End of Outputs for SubSystem: '<S12>/Enabled Subsystem1'

  // Switch: '<S98>/Switch' incorporates:
  //   Gain: '<S12>/wcmd'

  if (rtb_LogicalOperator1_n) {
    rtb_Switch_ep = rtb_Saturation2_o;
  } else {
    // Sum: '<S12>/Sum2' incorporates:
    //   Inport: '<Root>/input_col'

    rtb_DeadZone = QS_InnerRateLoop_U.input_col - QS_InnerRateLoop_B.col;

    // DeadZone: '<S12>/Dead Zone'
    if (rtb_DeadZone > 0.05F) {
      rtb_DeadZone -= 0.05F;
    } else if (rtb_DeadZone >= -0.05F) {
      rtb_DeadZone = 0.0F;
    } else {
      rtb_DeadZone -= -0.05F;
    }

    // End of DeadZone: '<S12>/Dead Zone'
    rtb_Switch_ep = -6.0F * rtb_DeadZone;
  }

  // End of Switch: '<S98>/Switch'

  // Switch: '<S98>/Switch1' incorporates:
  //   RelationalOperator: '<S98>/Relational Operator'
  //   Sum: '<S98>/Sum1'
  //   UnitDelay: '<S98>/Unit Delay'
  //   UnitDelay: '<S98>/Unit Delay1'
  //   UnitDelay: '<S98>/Unit Delay2'

  if (QS_InnerRateLoop_DWork.UnitDelay_DSTATE_ax == rtb_LogicalOperator1_n) {
    rtb_DeadZone = QS_InnerRateLoop_DWork.UnitDelay1_DSTATE;
  } else {
    rtb_DeadZone = QS_InnerRateLoop_DWork.UnitDelay2_DSTATE - rtb_Switch_ep;
  }

  // End of Switch: '<S98>/Switch1'

  // Saturate: '<S98>/Saturation'
  if (rtb_DeadZone > 0.0025F) {
    rtb_Product_of = 0.0025F;
  } else if (rtb_DeadZone < -0.0025F) {
    rtb_Product_of = -0.0025F;
  } else {
    rtb_Product_of = rtb_DeadZone;
  }

  // End of Saturate: '<S98>/Saturation'

  // Sum: '<S98>/Sum'
  rtb_DeadZone -= rtb_Product_of;

  // Sum: '<S98>/Sum2'
  rtb_Switch_ep += rtb_DeadZone;

  // Lookup_n-D: '<S37>/1-D Lookup Table2'
  bpIdx = plook_u32ff_evencg(rtb_Saturation8, 0.0F, 1.75F, 4U,
    &rtb_Saturation5_k);

  // Product: '<S37>/Product' incorporates:
  //   Lookup_n-D: '<S37>/1-D Lookup Table2'
  //   Sum: '<S34>/Sum'
  //   UnitDelay: '<S34>/Unit Delay'

  rtb_Product_of = (rtb_Switch_ep - QS_InnerRateLoop_DWork.UnitDelay_DSTATE_a) /
    intrp1d_fu32fl_pw(bpIdx, rtb_Saturation5_k,
                      QS_InnerRateLoop_ConstP.uDLookupTable2_tableData_j);

  // Product: '<S93>/Divide1' incorporates:
  //   Product: '<S93>/Divide7'

  rtb_DiscreteTimeIntegrator1 = QS_InnerRateLoop_ConstB.TrigonometricFunction4_n
    * QS_InnerRateLoop_ConstB.TrigonometricFunction5_o;

  // Sum: '<S93>/Add6' incorporates:
  //   Product: '<S93>/Divide1'
  //   Product: '<S93>/Divide11'
  //   Product: '<S93>/Divide13'
  //   Product: '<S93>/Divide15'
  //   Product: '<S93>/Divide3'
  //   Product: '<S93>/Divide7'
  //   Product: '<S93>/Divide8'
  //   Sum: '<S93>/Add1'
  //   Sum: '<S93>/Add3'

  rtb_Add6_a = ((rtb_DiscreteTimeIntegrator1 * rtb_derivativecutofffrequency_b -
                 QS_InnerRateLoop_ConstB.TrigonometricFunction1_k * rtb_Sum3_f) *
                rtb_Sum4_b + (rtb_DiscreteTimeIntegrator1 * rtb_Sum3_f +
    QS_InnerRateLoop_ConstB.TrigonometricFunction1_k *
    rtb_derivativecutofffrequency_b) * rtb_Add5_ky) +
    QS_InnerRateLoop_ConstB.TrigonometricFunction4_n *
    QS_InnerRateLoop_ConstB.TrigonometricFunction2_l * rtb_Sum4_a;

  // DiscreteIntegrator: '<S27>/Discrete-Time Integrator1' incorporates:
  //   Inport: '<Root>/engage'

  if (QS_InnerRateLoop_U.engage &&
      (QS_InnerRateLoop_DWork.DiscreteTimeIntegrator1_PrevR_g <= 0)) {
    QS_InnerRateLoop_DWork.DiscreteTimeIntegrator1_DSTAT_o = 0.0F;
  }

  rtb_DiscreteTimeIntegrator1 =
    QS_InnerRateLoop_DWork.DiscreteTimeIntegrator1_DSTAT_o;

  // Gain: '<S25>/derivative cutoff frequency 1' incorporates:
  //   DiscreteIntegrator: '<S25>/Discrete-Time Integrator'
  //   DiscreteIntegrator: '<S27>/Discrete-Time Integrator1'
  //   Gain: '<S25>/derivative cutoff frequency '
  //   Sum: '<S25>/Sum1'

  rtb_derivativecutofffrequency_0 =
    (QS_InnerRateLoop_DWork.DiscreteTimeIntegrator1_DSTAT_o -
     QS_InnerRateLoop_DWork.DiscreteTimeIntegrator_DSTATE_b) * 100.0F;

  // Sum: '<S93>/Add5' incorporates:
  //   Product: '<S93>/Divide'
  //   Product: '<S93>/Divide2'
  //   Product: '<S93>/Divide6'

  rtb_Add5_ky = (QS_InnerRateLoop_ConstB.TrigonometricFunction2_l *
                 rtb_derivativecutofffrequency_b * rtb_Sum4_b +
                 QS_InnerRateLoop_ConstB.TrigonometricFunction2_l * rtb_Sum3_f *
                 rtb_Add5_ky) +
    -QS_InnerRateLoop_ConstB.TrigonometricFunction5_o * rtb_Sum4_a;

  // DiscreteIntegrator: '<S43>/Discrete-Time Integrator1' incorporates:
  //   Inport: '<Root>/engage'

  if (QS_InnerRateLoop_U.engage &&
      (QS_InnerRateLoop_DWork.DiscreteTimeIntegrator1_PrevR_j <= 0)) {
    QS_InnerRateLoop_DWork.DiscreteTimeIntegrator1_DSTAT_m = 0.0F;
  }

  rtb_Sum3_f = QS_InnerRateLoop_DWork.DiscreteTimeIntegrator1_DSTAT_m;

  // Gain: '<S41>/derivative cutoff frequency 1' incorporates:
  //   DiscreteIntegrator: '<S41>/Discrete-Time Integrator'
  //   DiscreteIntegrator: '<S43>/Discrete-Time Integrator1'
  //   Gain: '<S41>/derivative cutoff frequency '
  //   Sum: '<S41>/Sum1'

  rtb_derivativecutofffrequency_b =
    (QS_InnerRateLoop_DWork.DiscreteTimeIntegrator1_DSTAT_m -
     QS_InnerRateLoop_DWork.DiscreteTimeIntegrator_DSTATE_o) * 100.0F;

  // Logic: '<S11>/Logical Operator2' incorporates:
  //   Constant: '<S11>/Constant7'
  //   DataTypeConversion: '<Root>/Data Type Conversion'
  //   RelationalOperator: '<S11>/Relational Operator4'

  rtb_LogicalOperator2_e = (rtb_LogicalOperator1_n && (rtb_Gain2 <= 18.0F));

  // Switch: '<S11>/Switch' incorporates:
  //   Constant: '<S11>/Constant5'
  //   RelationalOperator: '<S11>/Relational Operator3'
  //   Sum: '<S11>/Sum3'

  if (rtb_Gain2 >= 12.0F) {
    rtb_Sum4_a = rtb_uDLookupTable3;
  } else {
    rtb_Sum4_a = 0.0F;
  }

  // End of Switch: '<S11>/Switch'

  // RateLimiter: '<S11>/Rate Limiter'
  rtb_uDLookupTable3 = rtb_Sum4_a - QS_InnerRateLoop_DWork.PrevY;
  if (rtb_uDLookupTable3 > 0.25F) {
    rtb_Sum4_a = QS_InnerRateLoop_DWork.PrevY + 0.25F;
  } else {
    if (rtb_uDLookupTable3 < -0.25F) {
      rtb_Sum4_a = QS_InnerRateLoop_DWork.PrevY + -0.25F;
    }
  }

  QS_InnerRateLoop_DWork.PrevY = rtb_Sum4_a;

  // End of RateLimiter: '<S11>/Rate Limiter'

  // Outputs for Enabled SubSystem: '<Root>/Determine Heading at Start of Manuever  All trajectories relative to this heading' incorporates:
  //   EnablePort: '<S3>/Enable'

  // Logic: '<Root>/Logical Operator2'
  if (!rtb_LogicalOperator1_n) {
    // Gain: '<S3>/Gain' incorporates:
    //   Inport: '<Root>/psi_rad'

    QS_InnerRateLoop_B.Gain = 57.2957802F * QS_InnerRateLoop_U.psi_rad;
  }

  // End of Logic: '<Root>/Logical Operator2'
  // End of Outputs for SubSystem: '<Root>/Determine Heading at Start of Manuever  All trajectories relative to this heading' 

  // Sum: '<Root>/Sum4'
  rtb_Sum4_a += QS_InnerRateLoop_B.Gain;

  // Gain: '<S64>/Gain'
  rtb_uDLookupTable3 = 0.0174532924F * rtb_Sum4_a;

  // Delay: '<S12>/Delay'
  if (QS_InnerRateLoop_DWork.icLoad != 0) {
    QS_InnerRateLoop_DWork.Delay_DSTATE = rtb_uDLookupTable3;
  }

  // Switch: '<S12>/Switch3' incorporates:
  //   Delay: '<S12>/Delay'
  //   Delay: '<S12>/Delay1'
  //   Inport: '<Root>/psi_rad'

  if (QS_InnerRateLoop_DWork.Delay1_DSTATE_j[0]) {
    rtb_Sum4_b = QS_InnerRateLoop_DWork.Delay_DSTATE;
  } else {
    rtb_Sum4_b = QS_InnerRateLoop_U.psi_rad;
  }

  // End of Switch: '<S12>/Switch3'

  // DiscreteIntegrator: '<S12>/Discrete-Time Integrator'
  if (QS_InnerRateLoop_DWork.DiscreteTimeIntegrator_IC_LOA_b != 0) {
    QS_InnerRateLoop_DWork.DiscreteTimeIntegrator_DSTAT_mz = rtb_Sum4_b;
  }

  if ((rtb_LogicalOperator1_n &&
       (QS_InnerRateLoop_DWork.DiscreteTimeIntegrator_PrevRe_p <= 0)) ||
      (rtb_RelationalOperator4_e &&
       (QS_InnerRateLoop_DWork.DiscreteTimeIntegrator_PrevRe_p == 1))) {
    QS_InnerRateLoop_DWork.DiscreteTimeIntegrator_DSTAT_mz = rtb_Sum4_b;
  }

  // Switch: '<S12>/Switch' incorporates:
  //   DiscreteIntegrator: '<S12>/Discrete-Time Integrator'

  if (rtb_LogicalOperator1_n) {
    rtb_Sum4_b = rtb_uDLookupTable3;
  } else {
    rtb_Sum4_b = QS_InnerRateLoop_DWork.DiscreteTimeIntegrator_DSTAT_mz;
  }

  // End of Switch: '<S12>/Switch'

  // DiscreteIntegrator: '<S54>/Discrete-Time Integrator' incorporates:
  //   Inport: '<Root>/engage'

  if (QS_InnerRateLoop_U.engage &&
      (QS_InnerRateLoop_DWork.DiscreteTimeIntegrator_PrevR_bp <= 0)) {
    QS_InnerRateLoop_DWork.DiscreteTimeIntegrator_DSTATE = 0.0;
  }

  // Gain: '<S54>/Gain' incorporates:
  //   DiscreteIntegrator: '<S54>/Discrete-Time Integrator'

  rtb_Gain_e = 400.0 * QS_InnerRateLoop_DWork.DiscreteTimeIntegrator_DSTATE;

  // Switch: '<S21>/Switch2' incorporates:
  //   Constant: '<S21>/Constant1'

  if (rtb_Gain_e >= 100.0) {
    // Switch: '<S21>/Switch' incorporates:
    //   Constant: '<S21>/Constant'
    //   DiscreteIntegrator: '<S53>/Discrete-Time Integrator'
    //   Gain: '<S53>/derivative cutoff frequency 1'
    //   Sum: '<S53>/Sum1'

    if (rtb_LogicalOperator2_e) {
      rtb_Switch2_cz = 0.0F;
    } else {
      rtb_Switch2_cz = (rtb_Sum4_b -
                        QS_InnerRateLoop_DWork.DiscreteTimeIntegrator_DSTAT_mr) *
        100.0F;
    }

    // End of Switch: '<S21>/Switch'
  } else {
    rtb_Switch2_cz = 0.0F;
  }

  // End of Switch: '<S21>/Switch2'

  // DiscreteIntegrator: '<S35>/Discrete-Time Integrator' incorporates:
  //   Inport: '<Root>/engage'

  if (QS_InnerRateLoop_U.engage &&
      (QS_InnerRateLoop_DWork.DiscreteTimeIntegrator_PrevRe_m <= 0)) {
    QS_InnerRateLoop_DWork.DiscreteTimeIntegrator_DSTATE_f = 0.0F;
  }

  if (QS_InnerRateLoop_DWork.DiscreteTimeIntegrator_DSTATE_f >= 0.1F) {
    QS_InnerRateLoop_DWork.DiscreteTimeIntegrator_DSTATE_f = 0.1F;
  } else {
    if (QS_InnerRateLoop_DWork.DiscreteTimeIntegrator_DSTATE_f <= -0.1F) {
      QS_InnerRateLoop_DWork.DiscreteTimeIntegrator_DSTATE_f = -0.1F;
    }
  }

  // Lookup_n-D: '<S32>/1-D Lookup Table2'
  bpIdx = plook_u32ff_evencg(rtb_Saturation8, 0.0F, 1.75F, 4U,
    &rtb_Saturation5_k);

  // DiscreteIntegrator: '<S34>/Discrete-Time Integrator' incorporates:
  //   Inport: '<Root>/engage'

  if (QS_InnerRateLoop_U.engage &&
      (QS_InnerRateLoop_DWork.DiscreteTimeIntegrator_PrevRe_n <= 0)) {
    QS_InnerRateLoop_DWork.DiscreteTimeIntegrator_DSTAT_fs = 0.0F;
  }

  // Product: '<S32>/Product' incorporates:
  //   DiscreteIntegrator: '<S34>/Discrete-Time Integrator'
  //   Lookup_n-D: '<S32>/1-D Lookup Table2'
  //   Sum: '<S19>/Sum2'

  rtb_Product_ib = (QS_InnerRateLoop_DWork.DiscreteTimeIntegrator_DSTAT_fs -
                    rtb_uDLookupTable_cs) * intrp1d_fu32fl_pw(bpIdx,
    rtb_Saturation5_k, QS_InnerRateLoop_ConstP.uDLookupTable2_tableData_ok);

  // Sum: '<S19>/Sum1' incorporates:
  //   DiscreteIntegrator: '<S35>/Discrete-Time Integrator'

  rtb_Sum1_c0 = QS_InnerRateLoop_DWork.DiscreteTimeIntegrator_DSTATE_f +
    rtb_Product_ib;

  // Lookup_n-D: '<S19>/1-D Lookup Table'
  bpIdx = plook_u32ff_evencg(rtb_Saturation8, 0.0F, 1.75F, 4U,
    &rtb_Saturation5_k);
  rtb_uDLookupTable_cs = intrp1d_fu32fl_pw(bpIdx, rtb_Saturation5_k,
    QS_InnerRateLoop_ConstP.uDLookupTable_tableData);

  // Lookup_n-D: '<S19>/1-D Lookup Table1'
  bpIdx = plook_u32ff_evencg(rtb_Saturation8, 0.0F, 1.75F, 4U,
    &rtb_Saturation5_k);
  rtb_uDLookupTable1 = intrp1d_fu32fl_pw(bpIdx, rtb_Saturation5_k,
    QS_InnerRateLoop_ConstP.uDLookupTable1_tableData_g);

  // DiscreteIntegrator: '<S36>/Discrete-Time Integrator' incorporates:
  //   Inport: '<Root>/engage'

  if (QS_InnerRateLoop_U.engage &&
      (QS_InnerRateLoop_DWork.DiscreteTimeIntegrator_PrevR_by <= 0)) {
    QS_InnerRateLoop_DWork.DiscreteTimeIntegrator_DSTAT_c4 = 0.0F;
  }

  rtb_DiscreteTimeIntegrator_hs =
    QS_InnerRateLoop_DWork.DiscreteTimeIntegrator_DSTAT_c4;

  // DiscreteIntegrator: '<S28>/Discrete-Time Integrator' incorporates:
  //   Inport: '<Root>/engage'

  if (QS_InnerRateLoop_U.engage &&
      (QS_InnerRateLoop_DWork.DiscreteTimeIntegrator_PrevRe_e <= 0)) {
    QS_InnerRateLoop_DWork.DiscreteTimeIntegrator_DSTAT_o2 = 0.0F;
  }

  // Lookup_n-D: '<S23>/1-D Lookup Table2'
  bpIdx = plook_u32ff_evencg(rtb_Saturation8, 0.0F, 1.75F, 4U,
    &rtb_Saturation5_k);

  // Product: '<S23>/Product' incorporates:
  //   DiscreteIntegrator: '<S27>/Discrete-Time Integrator1'
  //   Inport: '<Root>/phi_rad'
  //   Lookup_n-D: '<S23>/1-D Lookup Table2'
  //   Sum: '<S18>/Sum'

  rtb_Product_jr = (QS_InnerRateLoop_DWork.DiscreteTimeIntegrator1_DSTAT_o -
                    QS_InnerRateLoop_U.phi_rad) * intrp1d_fu32fl_pw(bpIdx,
    rtb_Saturation5_k, QS_InnerRateLoop_ConstP.uDLookupTable2_tableData_a);

  // Lookup_n-D: '<S22>/1-D Lookup Table2'
  bpIdx = plook_u32ff_evencg(rtb_Saturation8, 0.0F, 1.75F, 4U,
    &rtb_Saturation5_k);

  // Sum: '<S18>/Sum1' incorporates:
  //   DiscreteIntegrator: '<S28>/Discrete-Time Integrator'
  //   Gain: '<S25>/derivative cutoff frequency 1'
  //   Inport: '<Root>/p_rps'
  //   Lookup_n-D: '<S22>/1-D Lookup Table2'
  //   Product: '<S22>/Product'
  //   Sum: '<S18>/Sum2'

  rtb_Sum1_fe = (rtb_derivativecutofffrequency_0 - QS_InnerRateLoop_U.p_rps) *
    intrp1d_fu32fl_pw(bpIdx, rtb_Saturation5_k,
                      QS_InnerRateLoop_ConstP.uDLookupTable2_tableData_fu) +
    (QS_InnerRateLoop_DWork.DiscreteTimeIntegrator_DSTAT_o2 + rtb_Product_jr);

  // Lookup_n-D: '<S18>/1-D Lookup Table'
  bpIdx = plook_u32ff_evencg(rtb_Saturation8, 0.0F, 1.75F, 4U,
    &rtb_Saturation5_k);
  rtb_uDLookupTable = intrp1d_fu32fl_pw(bpIdx, rtb_Saturation5_k,
    QS_InnerRateLoop_ConstP.uDLookupTable_tableData_l);

  // Lookup_n-D: '<S18>/1-D Lookup Table1'
  bpIdx = plook_u32ff_evencg(rtb_Saturation8, 0.0F, 1.75F, 4U,
    &rtb_Saturation5_k);
  rtb_uDLookupTable1_p = intrp1d_fu32fl_pw(bpIdx, rtb_Saturation5_k,
    QS_InnerRateLoop_ConstP.uDLookupTable1_tableData_n);

  // DiscreteIntegrator: '<S29>/Discrete-Time Integrator'
  rtb_DiscreteTimeIntegrator_cv =
    QS_InnerRateLoop_DWork.DiscreteTimeIntegrator_DSTAT_bw;

  // DiscreteIntegrator: '<S44>/Discrete-Time Integrator' incorporates:
  //   Inport: '<Root>/engage'

  if (QS_InnerRateLoop_U.engage &&
      (QS_InnerRateLoop_DWork.DiscreteTimeIntegrator_PrevRe_d <= 0)) {
    QS_InnerRateLoop_DWork.DiscreteTimeIntegrator_DSTATE_j = 0.0F;
  }

  // Lookup_n-D: '<S39>/1-D Lookup Table2'
  bpIdx = plook_u32ff_evencg(rtb_Saturation8, 0.0F, 1.75F, 4U,
    &rtb_Saturation5_k);

  // Product: '<S39>/Product' incorporates:
  //   DiscreteIntegrator: '<S43>/Discrete-Time Integrator1'
  //   Inport: '<Root>/theta_rad'
  //   Lookup_n-D: '<S39>/1-D Lookup Table2'
  //   Sum: '<S20>/Sum'

  rtb_Product_n = (QS_InnerRateLoop_DWork.DiscreteTimeIntegrator1_DSTAT_m -
                   QS_InnerRateLoop_U.theta_rad) * intrp1d_fu32fl_pw(bpIdx,
    rtb_Saturation5_k, QS_InnerRateLoop_ConstP.uDLookupTable2_tableData_ex);

  // Lookup_n-D: '<S38>/1-D Lookup Table2'
  bpIdx = plook_u32ff_evencg(rtb_Saturation8, 0.0F, 1.75F, 4U,
    &rtb_Saturation5_k);

  // Sum: '<S20>/Sum1' incorporates:
  //   DiscreteIntegrator: '<S44>/Discrete-Time Integrator'
  //   Gain: '<S41>/derivative cutoff frequency 1'
  //   Inport: '<Root>/q_rps'
  //   Lookup_n-D: '<S38>/1-D Lookup Table2'
  //   Product: '<S38>/Product'
  //   Sum: '<S20>/Sum2'

  rtb_uDLookupTable2_bw = (rtb_derivativecutofffrequency_b -
    QS_InnerRateLoop_U.q_rps) * intrp1d_fu32fl_pw(bpIdx, rtb_Saturation5_k,
    QS_InnerRateLoop_ConstP.uDLookupTable2_tableData_c) +
    (QS_InnerRateLoop_DWork.DiscreteTimeIntegrator_DSTATE_j + rtb_Product_n);

  // Lookup_n-D: '<S20>/1-D Lookup Table'
  bpIdx = plook_u32ff_evencg(rtb_Saturation8, 0.0F, 1.75F, 4U,
    &rtb_Saturation5_k);
  rtb_Saturation_k = intrp1d_fu32fl_pw(bpIdx, rtb_Saturation5_k,
    QS_InnerRateLoop_ConstP.uDLookupTable_tableData_m);

  // Lookup_n-D: '<S20>/1-D Lookup Table1'
  bpIdx = plook_u32ff_evencg(rtb_Saturation8, 0.0F, 1.75F, 4U,
    &rtb_Saturation5_k);
  rtb_uDLookupTable1_l = intrp1d_fu32fl_pw(bpIdx, rtb_Saturation5_k,
    QS_InnerRateLoop_ConstP.uDLookupTable1_tableData_d);

  // DiscreteIntegrator: '<S45>/Discrete-Time Integrator'
  rtb_DiscreteTimeIntegrator_nt =
    QS_InnerRateLoop_DWork.DiscreteTimeIntegrator_DSTAT_di;

  // DiscreteIntegrator: '<S55>/Discrete-Time Integrator' incorporates:
  //   Inport: '<Root>/engage'

  if (QS_InnerRateLoop_U.engage &&
      (QS_InnerRateLoop_DWork.DiscreteTimeIntegrator_PrevRe_j <= 0)) {
    QS_InnerRateLoop_DWork.DiscreteTimeIntegrator_DSTATE_l = 0.0F;
  }

  // Lookup_n-D: '<S49>/1-D Lookup Table2'
  bpIdx = plook_u32ff_evencg(rtb_Saturation8, 0.0F, 1.75F, 4U,
    &rtb_Saturation5_k);

  // Switch: '<S21>/Switch1' incorporates:
  //   Constant: '<S21>/Constant'

  if (rtb_Gain_e >= 100.0) {
    // Sum: '<S21>/Sum1' incorporates:
    //   Inport: '<Root>/psi_rad'

    rtb_Sum1_gw = rtb_Sum4_b - QS_InnerRateLoop_U.psi_rad;

    // Switch: '<S57>/Switch' incorporates:
    //   Constant: '<S57>/Constant1'
    //   Constant: '<S57>/Constant2'
    //   Gain: '<S57>/Gain1'
    //   Switch: '<S57>/Switch1'

    if (rtb_Sum1_gw >= 0.0F) {
      rtb_Abs = rtb_Sum1_gw;
      iU = 1;
    } else {
      rtb_Abs = -rtb_Sum1_gw;
      iU = -1;
    }

    // End of Switch: '<S57>/Switch'

    // Product: '<S57>/Product' incorporates:
    //   Constant: '<S57>/Constant'
    //   Gain: '<S57>/Gain'
    //   Product: '<S57>/Divide'
    //   Rounding: '<S57>/Rounding Function'
    //   Sum: '<S57>/Subtract'

    rtb_Product_cw = (rtb_Abs - static_cast<real32_T>(floor((real_T)(rtb_Abs *
      0.159154937F))) * 6.28318548F) * static_cast<real32_T>(iU);

    // Switch: '<S48>/Switch' incorporates:
    //   Abs: '<S48>/Abs'

    if (static_cast<real32_T>(fabs((real_T)rtb_Product_cw)) > 3.14159274F) {
      // Switch: '<S48>/Switch1' incorporates:
      //   Constant: '<S48>/Constant1'
      //   Constant: '<S48>/Constant2'
      //   Sum: '<S48>/Add'
      //   Sum: '<S48>/Subtract'

      if (rtb_Product_cw >= 0.0F) {
        rtb_Product_cw -= 6.28318548F;
      } else {
        rtb_Product_cw += 6.28318548F;
      }

      // End of Switch: '<S48>/Switch1'
    }

    // End of Switch: '<S48>/Switch'
  } else {
    rtb_Product_cw = 0.0F;
  }

  // End of Switch: '<S21>/Switch1'

  // Product: '<S49>/Product' incorporates:
  //   Lookup_n-D: '<S49>/1-D Lookup Table2'

  rtb_Product_ear = intrp1d_fu32fl_pw(bpIdx, rtb_Saturation5_k,
    QS_InnerRateLoop_ConstP.uDLookupTable2_tableData_au) * rtb_Product_cw;

  // Lookup_n-D: '<S51>/1-D Lookup Table2'
  bpIdx = plook_u32ff_evencg(rtb_Saturation8, 0.0F, 1.75F, 4U,
    &rtb_Saturation5_k);

  // Sum: '<S21>/Sum5' incorporates:
  //   DiscreteIntegrator: '<S55>/Discrete-Time Integrator'
  //   Inport: '<Root>/r_rps'
  //   Lookup_n-D: '<S51>/1-D Lookup Table2'
  //   Product: '<S51>/Product'
  //   Sum: '<S21>/Sum3'

  rtb_Product_cw = (rtb_Switch2_cz - QS_InnerRateLoop_U.r_rps) *
    intrp1d_fu32fl_pw(bpIdx, rtb_Saturation5_k,
                      QS_InnerRateLoop_ConstP.uDLookupTable2_tableData_c0) +
    (QS_InnerRateLoop_DWork.DiscreteTimeIntegrator_DSTATE_l + rtb_Product_ear);

  // Lookup_n-D: '<S21>/1-D Lookup Table'
  bpIdx = plook_u32ff_evencg(rtb_Saturation8, 0.0F, 1.75F, 4U,
    &rtb_Saturation5_k);
  rtb_Sum1_gw = intrp1d_fu32fl_pw(bpIdx, rtb_Saturation5_k,
    QS_InnerRateLoop_ConstP.uDLookupTable_tableData_h);

  // Lookup_n-D: '<S21>/1-D Lookup Table1'
  bpIdx = plook_u32ff_evencg(rtb_Saturation8, 0.0F, 1.75F, 4U,
    &rtb_Saturation5_k);
  rtb_Abs = intrp1d_fu32fl_pw(bpIdx, rtb_Saturation5_k,
    QS_InnerRateLoop_ConstP.uDLookupTable1_tableData_f);

  // DiscreteIntegrator: '<S56>/Discrete-Time Integrator'
  rtb_DiscreteTimeIntegrator_ia =
    QS_InnerRateLoop_DWork.DiscreteTimeIntegrator_DSTAT_hv;

  // Sum: '<S4>/Sum'
  rtb_Product_hg[0] = rtb_Product_of;

  // Gain: '<S26>/derivative cutoff frequency 1' incorporates:
  //   DiscreteIntegrator: '<S26>/Discrete-Time Integrator'
  //   Gain: '<S25>/derivative cutoff frequency 1'
  //   Gain: '<S26>/derivative cutoff frequency '
  //   Sum: '<S26>/Sum1'

  rtb_Product_b_tmp = (rtb_derivativecutofffrequency_0 -
                       QS_InnerRateLoop_DWork.DiscreteTimeIntegrator_DSTAT_hq) *
    100.0F;

  // Sum: '<S4>/Sum' incorporates:
  //   Gain: '<S26>/derivative cutoff frequency 1'

  rtb_Product_hg[1] = rtb_Product_b_tmp;

  // Sum: '<S20>/Sum3' incorporates:
  //   DiscreteIntegrator: '<S42>/Discrete-Time Integrator'
  //   Gain: '<S41>/derivative cutoff frequency 1'
  //   Gain: '<S42>/derivative cutoff frequency '
  //   Gain: '<S42>/derivative cutoff frequency 1'
  //   Sum: '<S42>/Sum1'

  rtb_Product_b_tmp_0 = (rtb_derivativecutofffrequency_b -
    QS_InnerRateLoop_DWork.DiscreteTimeIntegrator_DSTAT_mk) * 100.0F;

  // Sum: '<S4>/Sum' incorporates:
  //   Gain: '<S42>/derivative cutoff frequency 1'
  //   Sum: '<S20>/Sum3'

  rtb_Product_hg[2] = rtb_Product_b_tmp_0;

  // Gain: '<S52>/derivative cutoff frequency 1' incorporates:
  //   DiscreteIntegrator: '<S52>/Discrete-Time Integrator'
  //   Gain: '<S52>/derivative cutoff frequency '
  //   Sum: '<S52>/Sum1'

  rtb_Switch2_cz = (rtb_Switch2_cz -
                    QS_InnerRateLoop_DWork.DiscreteTimeIntegrator_DSTATE_d) *
    100.0F;

  // Sum: '<S4>/Sum' incorporates:
  //   DiscreteIntegrator: '<S29>/Discrete-Time Integrator'
  //   DiscreteIntegrator: '<S36>/Discrete-Time Integrator'
  //   DiscreteIntegrator: '<S45>/Discrete-Time Integrator'
  //   DiscreteIntegrator: '<S56>/Discrete-Time Integrator'
  //   Gain: '<S52>/derivative cutoff frequency 1'
  //   Product: '<S29>/Product1'
  //   Product: '<S36>/Product1'
  //   Product: '<S45>/Product1'
  //   Product: '<S56>/Product1'
  //   Product: '<S59>/Product'
  //   Sum: '<S29>/Sum1'
  //   Sum: '<S36>/Sum1'
  //   Sum: '<S45>/Sum1'
  //   Sum: '<S56>/Sum1'

  rtb_Product_hg[3] = rtb_Switch2_cz;
  rtb_Sum1_f[0] = rtb_Sum1_c0 * rtb_uDLookupTable_cs / rtb_uDLookupTable1 +
    QS_InnerRateLoop_DWork.DiscreteTimeIntegrator_DSTAT_c4;
  rtb_Sum1_f[1] = rtb_Sum1_fe * rtb_uDLookupTable / rtb_uDLookupTable1_p +
    QS_InnerRateLoop_DWork.DiscreteTimeIntegrator_DSTAT_bw;
  rtb_Sum1_f[2] = rtb_uDLookupTable2_bw * rtb_Saturation_k /
    rtb_uDLookupTable1_l +
    QS_InnerRateLoop_DWork.DiscreteTimeIntegrator_DSTAT_di;
  rtb_Sum1_f[3] = rtb_Product_cw * rtb_Sum1_gw / rtb_Abs +
    QS_InnerRateLoop_DWork.DiscreteTimeIntegrator_DSTAT_hv;
  for (iU = 0; iU < 4; iU++) {
    tmp = 0.0F;
    tmp_0 = 0;
    for (i = 0; i < 9; i++) {
      tmp += rtb_uDLookupTable2[tmp_0 + iU] * rtb_TmpSignalConversionAtProduc[i];
      tmp_0 += 4;
    }

    rtb_Product_b[iU] = (rtb_Product_hg[iU] + rtb_Sum1_f[iU]) - tmp;
  }

  // Product: '<S58>/Product'
  for (iU = 0; iU < 4; iU++) {
    rtb_Product_hg[iU] = 0.0F;
    rtb_Product_hg[iU] += rtb_uDLookupTable2_k5[iU] * rtb_Product_b[0];
    rtb_Product_hg[iU] += rtb_uDLookupTable2_k5[iU + 4] * rtb_Product_b[1];
    rtb_Product_hg[iU] += rtb_uDLookupTable2_k5[iU + 8] * rtb_Product_b[2];
    rtb_Product_hg[iU] += rtb_uDLookupTable2_k5[iU + 12] * rtb_Product_b[3];
  }

  // End of Product: '<S58>/Product'

  // Outputs for Enabled SubSystem: '<Root>/Enabled Subsystem Grab and Freeze Value Upon Engagement' incorporates:
  //   EnablePort: '<S5>/Enable'

  // Logic: '<Root>/Logical Operator' incorporates:
  //   Inport: '<Root>/engage'

  if (!QS_InnerRateLoop_U.engage) {
    // Saturate: '<Root>/Saturation' incorporates:
    //   Inport: '<Root>/mixer_in_throttle'
    //   Inport: '<S5>/In1'

    if (QS_InnerRateLoop_U.mixer_in_throttle > 2.0F) {
      QS_InnerRateLoop_B.In1[0] = 2.0F;
    } else if (QS_InnerRateLoop_U.mixer_in_throttle < -1.0F) {
      QS_InnerRateLoop_B.In1[0] = -1.0F;
    } else {
      QS_InnerRateLoop_B.In1[0] = QS_InnerRateLoop_U.mixer_in_throttle;
    }

    // End of Saturate: '<Root>/Saturation'

    // Saturate: '<Root>/Saturation1' incorporates:
    //   Inport: '<Root>/mixer_in_y'
    //   Inport: '<S5>/In1'

    if (QS_InnerRateLoop_U.mixer_in_y > 2.0F) {
      QS_InnerRateLoop_B.In1[1] = 2.0F;
    } else if (QS_InnerRateLoop_U.mixer_in_y < -2.0F) {
      QS_InnerRateLoop_B.In1[1] = -2.0F;
    } else {
      QS_InnerRateLoop_B.In1[1] = QS_InnerRateLoop_U.mixer_in_y;
    }

    // End of Saturate: '<Root>/Saturation1'

    // Saturate: '<Root>/Saturation2' incorporates:
    //   Inport: '<Root>/mixer_in_x'
    //   Inport: '<S5>/In1'

    if (QS_InnerRateLoop_U.mixer_in_x > 2.0F) {
      QS_InnerRateLoop_B.In1[2] = 2.0F;
    } else if (QS_InnerRateLoop_U.mixer_in_x < -2.0F) {
      QS_InnerRateLoop_B.In1[2] = -2.0F;
    } else {
      QS_InnerRateLoop_B.In1[2] = QS_InnerRateLoop_U.mixer_in_x;
    }

    // End of Saturate: '<Root>/Saturation2'

    // Saturate: '<Root>/Saturation3' incorporates:
    //   Inport: '<Root>/mixer_in_z'
    //   Inport: '<S5>/In1'

    if (QS_InnerRateLoop_U.mixer_in_z > 2.0F) {
      QS_InnerRateLoop_B.In1[3] = 2.0F;
    } else if (QS_InnerRateLoop_U.mixer_in_z < -2.0F) {
      QS_InnerRateLoop_B.In1[3] = -2.0F;
    } else {
      QS_InnerRateLoop_B.In1[3] = QS_InnerRateLoop_U.mixer_in_z;
    }

    // End of Saturate: '<Root>/Saturation3'
  }

  // End of Logic: '<Root>/Logical Operator'
  // End of Outputs for SubSystem: '<Root>/Enabled Subsystem Grab and Freeze Value Upon Engagement' 

  // DiscreteIntegrator: '<S60>/Discrete-Time Integrator'
  rtb_DiscreteTimeIntegrator_fi =
    QS_InnerRateLoop_DWork.DiscreteTimeIntegrator_DSTAT_co;

  // Sum: '<S60>/Sum1' incorporates:
  //   DiscreteIntegrator: '<S60>/Discrete-Time Integrator'
  //   Gain: '<S60>/Gain'

  rtb_DeadZone3 = 6.66666651F * rtb_Product_hg[0] +
    QS_InnerRateLoop_DWork.DiscreteTimeIntegrator_DSTAT_co;

  // DiscreteIntegrator: '<S61>/Discrete-Time Integrator'
  rtb_DiscreteTimeIntegrator_k1 =
    QS_InnerRateLoop_DWork.DiscreteTimeIntegrator_DSTATE_i;

  // Sum: '<S61>/Sum1' incorporates:
  //   DiscreteIntegrator: '<S61>/Discrete-Time Integrator'
  //   Gain: '<S61>/Gain'

  rtb_uDLookupTable_a = 6.66666651F * rtb_Product_hg[1] +
    QS_InnerRateLoop_DWork.DiscreteTimeIntegrator_DSTATE_i;

  // DiscreteIntegrator: '<S62>/Discrete-Time Integrator'
  rtb_DiscreteTimeIntegrator_h =
    QS_InnerRateLoop_DWork.DiscreteTimeIntegrator_DSTAT_ch;

  // Sum: '<S62>/Sum1' incorporates:
  //   DiscreteIntegrator: '<S62>/Discrete-Time Integrator'
  //   Gain: '<S62>/Gain'

  rtb_Sum1_lq = 6.66666651F * rtb_Product_hg[2] +
    QS_InnerRateLoop_DWork.DiscreteTimeIntegrator_DSTAT_ch;

  // DiscreteIntegrator: '<S63>/Discrete-Time Integrator'
  rtb_DiscreteTimeIntegrator_n =
    QS_InnerRateLoop_DWork.DiscreteTimeIntegrator_DSTAT_a5;

  // Sum: '<S63>/Sum1' incorporates:
  //   DiscreteIntegrator: '<S63>/Discrete-Time Integrator'
  //   Gain: '<S63>/Gain'

  rtb_Sum1_gg = 0.364F * rtb_Product_hg[3] +
    QS_InnerRateLoop_DWork.DiscreteTimeIntegrator_DSTAT_a5;

  // Sum: '<Root>/Sum1'
  rtb_Sum1_j_idx_0 = QS_InnerRateLoop_B.In1[0] + rtb_DeadZone3;
  rtb_Sum1_j_idx_1 = QS_InnerRateLoop_B.In1[1] + rtb_uDLookupTable_a;
  rtb_Sum1_j_idx_2 = QS_InnerRateLoop_B.In1[2] + rtb_Sum1_lq;
  rtb_Sum1_j_idx_3 = QS_InnerRateLoop_B.In1[3] + rtb_Sum1_gg;

  // Saturate: '<Root>/Saturation4'
  if (rtb_Sum1_j_idx_0 > 0.9F) {
    rtb_Saturation5_k = 0.9F;
  } else if (rtb_Sum1_j_idx_0 < 0.05F) {
    rtb_Saturation5_k = 0.05F;
  } else {
    rtb_Saturation5_k = rtb_Sum1_j_idx_0;
  }

  // End of Saturate: '<Root>/Saturation4'

  // Outport: '<Root>/mixer_throttle'
  QS_InnerRateLoop_Y.mixer_throttle = rtb_Saturation5_k;

  // Switch: '<S35>/Switch' incorporates:
  //   Constant: '<S35>/Constant'
  //   Lookup_n-D: '<S33>/1-D Lookup Table2'
  //   Product: '<S33>/Product'
  //   RelationalOperator: '<Root>/Relational Operator'

  if (!is_equal(rtb_Sum1_j_idx_0,rtb_Saturation5_k)) {
    rtb_Product_ib = 0.0F;
  } else {
    // Lookup_n-D: '<S33>/1-D Lookup Table2'
    bpIdx = plook_u32ff_evencg(rtb_Saturation8, 0.0F, 1.75F, 4U,
      &rtb_Saturation5_k);
    rtb_Product_ib *= intrp1d_fu32fl_pw(bpIdx, rtb_Saturation5_k,
      QS_InnerRateLoop_ConstP.uDLookupTable2_tableData);
  }

  // End of Switch: '<S35>/Switch'

  // Saturate: '<Root>/Saturation7'
  if (rtb_Sum1_j_idx_1 > 1.0F) {
    rtb_Saturation5_k = 1.0F;
  } else if (rtb_Sum1_j_idx_1 < -1.0F) {
    rtb_Saturation5_k = -1.0F;
  } else {
    rtb_Saturation5_k = rtb_Sum1_j_idx_1;
  }

  // End of Saturate: '<Root>/Saturation7'

  // Outport: '<Root>/mixer_x'
  QS_InnerRateLoop_Y.mixer_x = rtb_Saturation5_k;

  // Switch: '<S28>/Switch' incorporates:
  //   Constant: '<S28>/Constant'
  //   Lookup_n-D: '<S24>/1-D Lookup Table2'
  //   Product: '<S24>/Product'
  //   RelationalOperator: '<Root>/Relational Operator1'

  if (!is_equal(rtb_Sum1_j_idx_1,rtb_Saturation5_k)) {
    rtb_Product_jr = 0.0F;
  } else {
    // Lookup_n-D: '<S24>/1-D Lookup Table2'
    bpIdx = plook_u32ff_evencg(rtb_Saturation8, 0.0F, 1.75F, 4U,
      &rtb_Saturation5_k);
    rtb_Product_jr *= intrp1d_fu32fl_pw(bpIdx, rtb_Saturation5_k,
      QS_InnerRateLoop_ConstP.pooled6);
  }

  // End of Switch: '<S28>/Switch'

  // Saturate: '<Root>/Saturation6'
  if (rtb_Sum1_j_idx_2 > 1.0F) {
    rtb_Saturation5_k = 1.0F;
  } else if (rtb_Sum1_j_idx_2 < -1.0F) {
    rtb_Saturation5_k = -1.0F;
  } else {
    rtb_Saturation5_k = rtb_Sum1_j_idx_2;
  }

  // End of Saturate: '<Root>/Saturation6'

  // Outport: '<Root>/mixer_y'
  QS_InnerRateLoop_Y.mixer_y = rtb_Saturation5_k;

  // Switch: '<S44>/Switch' incorporates:
  //   Constant: '<S44>/Constant'
  //   Lookup_n-D: '<S40>/1-D Lookup Table2'
  //   Product: '<S40>/Product'
  //   RelationalOperator: '<Root>/Relational Operator2'

  if (!is_equal(rtb_Sum1_j_idx_2,rtb_Saturation5_k)) {
    rtb_Product_n = 0.0F;
  } else {
    // Lookup_n-D: '<S40>/1-D Lookup Table2'
    bpIdx = plook_u32ff_evencg(rtb_Saturation8, 0.0F, 1.75F, 4U,
      &rtb_Saturation5_k);
    rtb_Product_n *= intrp1d_fu32fl_pw(bpIdx, rtb_Saturation5_k,
      QS_InnerRateLoop_ConstP.uDLookupTable2_tableData_e);
  }

  // End of Switch: '<S44>/Switch'

  // Saturate: '<Root>/Saturation5'
  if (rtb_Sum1_j_idx_3 > 1.0F) {
    rtb_Saturation5_k = 1.0F;
  } else if (rtb_Sum1_j_idx_3 < -1.0F) {
    rtb_Saturation5_k = -1.0F;
  } else {
    rtb_Saturation5_k = rtb_Sum1_j_idx_3;
  }

  // End of Saturate: '<Root>/Saturation5'

  // Outport: '<Root>/mixer_z'
  QS_InnerRateLoop_Y.mixer_z = rtb_Saturation5_k;

  // Switch: '<S55>/Switch' incorporates:
  //   Constant: '<S55>/Constant'
  //   Lookup_n-D: '<S50>/1-D Lookup Table2'
  //   Product: '<S50>/Product'
  //   RelationalOperator: '<Root>/Relational Operator3'

  if (!is_equal(rtb_Saturation5_k,rtb_Sum1_j_idx_3)) {
    rtb_Product_ear = 0.0F;
  } else {
    // Lookup_n-D: '<S50>/1-D Lookup Table2'
    bpIdx = plook_u32ff_evencg(rtb_Saturation8, 0.0F, 1.75F, 4U,
      &rtb_Saturation5_k);
    rtb_Product_ear *= intrp1d_fu32fl_pw(bpIdx, rtb_Saturation5_k,
      QS_InnerRateLoop_ConstP.pooled6);
  }

  // End of Switch: '<S55>/Switch'

  // Outport: '<Root>/yaw_sweep'
  QS_InnerRateLoop_Y.yaw_sweep = rtb_Sum1_gg;

  // Outport: '<Root>/pitch_sweep'
  QS_InnerRateLoop_Y.pitch_sweep = rtb_Sum1_lq;

  // Outport: '<Root>/roll_sweep'
  QS_InnerRateLoop_Y.roll_sweep = rtb_uDLookupTable_a;

  // Outport: '<Root>/coll_sweep'
  QS_InnerRateLoop_Y.coll_sweep = rtb_DeadZone3;

  // Product: '<S56>/Product' incorporates:
  //   Product: '<S56>/Product2'
  //   Sum: '<S56>/Sum'
  //   Sum: '<S56>/Sum2'
  //   UnitDelay: '<S56>/Unit Delay'

  rtb_Sum1_lq = ((rtb_Abs - rtb_Sum1_gw) * rtb_Product_cw / rtb_Abs -
                 QS_InnerRateLoop_DWork.UnitDelay_DSTATE_o) * rtb_Sum1_gw;

  // Product: '<S45>/Product2' incorporates:
  //   Sum: '<S45>/Sum2'

  rtb_Sum1_gg = (rtb_uDLookupTable1_l - rtb_Saturation_k) *
    rtb_uDLookupTable2_bw / rtb_uDLookupTable1_l;

  // Outport: '<Root>/vz_cmd' incorporates:
  //   DiscreteIntegrator: '<S34>/Discrete-Time Integrator'

  QS_InnerRateLoop_Y.vz_cmd =
    QS_InnerRateLoop_DWork.DiscreteTimeIntegrator_DSTAT_fs;

  // Switch: '<S54>/Switch' incorporates:
  //   Constant: '<S54>/Constant'
  //   Constant: '<S54>/Constant1'
  //   Inport: '<Root>/engage'
  //   RelationalOperator: '<S54>/Relational Operator'

  if (rtb_Gain_e >= 100.0) {
    rtb_Gain_e = 0.0;
  } else {
    rtb_Gain_e = QS_InnerRateLoop_U.engage;
  }

  // End of Switch: '<S54>/Switch'

  // Outport: '<Root>/psi_cmd'
  QS_InnerRateLoop_Y.psi_cmd = rtb_Sum4_b;

  // Trigonometry: '<S66>/Trigonometric Function3'
  rtb_DeadZone3 = static_cast<real32_T>(cos((real_T)rtb_uDLookupTable3));

  // Trigonometry: '<S66>/Trigonometric Function6'
  rtb_Abs = static_cast<real32_T>(sin((real_T)rtb_uDLookupTable3));

  // Product: '<S66>/Divide4' incorporates:
  //   Product: '<S66>/Divide9'

  rtb_Saturation5_k = QS_InnerRateLoop_ConstB.TrigonometricFunction1_m *
    QS_InnerRateLoop_ConstB.TrigonometricFunction5_f;

  // Product: '<S66>/Divide1' incorporates:
  //   Product: '<S66>/Divide7'

  rtb_Product_cw = QS_InnerRateLoop_ConstB.TrigonometricFunction4_km *
    QS_InnerRateLoop_ConstB.TrigonometricFunction5_f;

  // Sum: '<S66>/Add5' incorporates:
  //   Product: '<S66>/Divide'
  //   Product: '<S66>/Divide1'
  //   Product: '<S66>/Divide13'
  //   Product: '<S66>/Divide14'
  //   Product: '<S66>/Divide3'
  //   Product: '<S66>/Divide4'
  //   Product: '<S66>/Divide5'
  //   Sum: '<S66>/Add1'
  //   Sum: '<S66>/Add2'

  rtb_Sum1_j_idx_0 = ((rtb_Saturation5_k * rtb_DeadZone3 +
                       QS_InnerRateLoop_ConstB.TrigonometricFunction4_km *
                       rtb_Abs) * rtb_Add7_d + (rtb_Product_cw * rtb_DeadZone3 -
    QS_InnerRateLoop_ConstB.TrigonometricFunction1_m * rtb_Abs) * rtb_Add6_a) +
    QS_InnerRateLoop_ConstB.TrigonometricFunction2_ag * rtb_DeadZone3 *
    rtb_Add5_ky;

  // Outport: '<Root>/Vnorth_cmd'
  QS_InnerRateLoop_Y.Vnorth_cmd = rtb_Sum1_j_idx_0;

  // Sum: '<S66>/Add6' incorporates:
  //   Product: '<S66>/Divide10'
  //   Product: '<S66>/Divide15'
  //   Product: '<S66>/Divide16'
  //   Product: '<S66>/Divide6'
  //   Product: '<S66>/Divide7'
  //   Product: '<S66>/Divide8'
  //   Product: '<S66>/Divide9'
  //   Sum: '<S66>/Add3'
  //   Sum: '<S66>/Add4'

  rtb_Sum1_j_idx_1 = ((rtb_Saturation5_k * rtb_Abs -
                       QS_InnerRateLoop_ConstB.TrigonometricFunction4_km *
                       rtb_DeadZone3) * rtb_Add7_d + (rtb_Product_cw * rtb_Abs +
    QS_InnerRateLoop_ConstB.TrigonometricFunction1_m * rtb_DeadZone3) *
                      rtb_Add6_a) +
    QS_InnerRateLoop_ConstB.TrigonometricFunction2_ag * rtb_Abs * rtb_Add5_ky;

  // Outport: '<Root>/Veast_cmd'
  QS_InnerRateLoop_Y.Veast_cmd = rtb_Sum1_j_idx_1;

  // Sum: '<S66>/Add7' incorporates:
  //   Product: '<S66>/Divide11'
  //   Product: '<S66>/Divide12'
  //   Product: '<S66>/Divide2'

  rtb_Add7_d = (QS_InnerRateLoop_ConstB.TrigonometricFunction1_m *
                QS_InnerRateLoop_ConstB.TrigonometricFunction2_ag * rtb_Add7_d +
                QS_InnerRateLoop_ConstB.TrigonometricFunction4_km *
                QS_InnerRateLoop_ConstB.TrigonometricFunction2_ag * rtb_Add6_a)
    + -QS_InnerRateLoop_ConstB.TrigonometricFunction5_f * rtb_Add5_ky;

  // Outport: '<Root>/Vdown_cmd'
  QS_InnerRateLoop_Y.Vdown_cmd = rtb_Add7_d;

  // Outport: '<Root>/vehheadingcmd'
  QS_InnerRateLoop_Y.vehheadingcmd = rtb_Sum4_a;

  // DiscreteIntegrator: '<S79>/Discrete-Time Integrator'
  if (rtb_LogicalOperator1_n &&
      (QS_InnerRateLoop_DWork.DiscreteTimeIntegrator_PrevRe_h <= 0)) {
    QS_InnerRateLoop_DWork.DiscreteTimeIntegrator_DSTATE_n = 0.0F;
  }

  if (QS_InnerRateLoop_DWork.DiscreteTimeIntegrator_DSTATE_n >= 0.0174520072F) {
    QS_InnerRateLoop_DWork.DiscreteTimeIntegrator_DSTATE_n = 0.0174520072F;
  } else {
    if (QS_InnerRateLoop_DWork.DiscreteTimeIntegrator_DSTATE_n <= -0.0174520072F)
    {
      QS_InnerRateLoop_DWork.DiscreteTimeIntegrator_DSTATE_n = -0.0174520072F;
    }
  }

  // Lookup_n-D: '<S77>/1-D Lookup Table2'
  bpIdx = plook_u32ff_evencg(rtb_Saturation8, 0.0F, 1.75F, 4U,
    &rtb_Saturation5_k);

  // Product: '<S77>/Product' incorporates:
  //   Lookup_n-D: '<S77>/1-D Lookup Table2'
  //   Product: '<S67>/Divide'
  //   Product: '<S67>/Divide2'
  //   Product: '<S67>/Divide6'
  //   Sum: '<S67>/Add5'
  //   Sum: '<S69>/Sum'
  //   Sum: '<S69>/Sum4'

  rtb_uDLookupTable1_l = ((((QS_InnerRateLoop_ConstB.TrigonometricFunction2_a *
    rtb_Gain1 * rtb_Saturation_h +
    QS_InnerRateLoop_ConstB.TrigonometricFunction2_a * rtb_uDLookupTable_l_tmp *
    rtb_Saturation1_p) + -QS_InnerRateLoop_ConstB.TrigonometricFunction5_j *
    rtb_Saturation2_h) + rtb_Add5_ky) - rtb_Add5_e) * intrp1d_fu32fl_pw(bpIdx,
    rtb_Saturation5_k, QS_InnerRateLoop_ConstP.uDLookupTable2_tableData_kg);

  // Sum: '<S69>/Sum1' incorporates:
  //   DiscreteIntegrator: '<S79>/Discrete-Time Integrator'

  rtb_DeadZone3 = QS_InnerRateLoop_DWork.DiscreteTimeIntegrator_DSTATE_n +
    rtb_uDLookupTable1_l;

  // Lookup_n-D: '<S69>/1-D Lookup Table'
  bpIdx = plook_u32ff_evencg(rtb_Saturation8, 0.0F, 1.75F, 4U,
    &rtb_Saturation5_k);
  rtb_Abs = intrp1d_fu32fl_pw(bpIdx, rtb_Saturation5_k,
    QS_InnerRateLoop_ConstP.uDLookupTable_tableData_d);

  // Lookup_n-D: '<S69>/1-D Lookup Table1'
  bpIdx = plook_u32ff_evencg(rtb_Saturation8, 0.0F, 1.75F, 4U,
    &rtb_Saturation5_k);
  rtb_Product_cw = intrp1d_fu32fl_pw(bpIdx, rtb_Saturation5_k,
    QS_InnerRateLoop_ConstP.uDLookupTable1_tableData_m);

  // DiscreteIntegrator: '<S80>/Discrete-Time Integrator'
  rtb_Add5_e = QS_InnerRateLoop_DWork.DiscreteTimeIntegrator_DSTATE_g;

  // Gain: '<S69>/Gain5' incorporates:
  //   DiscreteIntegrator: '<S80>/Discrete-Time Integrator'
  //   Product: '<S80>/Product1'
  //   Sum: '<S80>/Sum1'

  rtb_Saturation5_k = -(rtb_DeadZone3 * rtb_Abs / rtb_Product_cw +
                        QS_InnerRateLoop_DWork.DiscreteTimeIntegrator_DSTATE_g);

  // Sum: '<S12>/Sum'
  rtb_Sum1_gw = rtb_Saturation5_k;

  // Saturate: '<S12>/Saturation4' incorporates:
  //   Sum: '<S12>/Sum'

  if (rtb_Saturation5_k > 0.610820234F) {
    rtb_Sum1_j_idx_2 = 0.610820234F;
  } else if (rtb_Saturation5_k < -0.610820234F) {
    rtb_Sum1_j_idx_2 = -0.610820234F;
  } else {
    rtb_Sum1_j_idx_2 = rtb_Saturation5_k;
  }

  // End of Saturate: '<S12>/Saturation4'

  // Switch: '<S96>/Switch' incorporates:
  //   DeadZone: '<S12>/Dead Zone2'
  //   Gain: '<S12>/thetacmd'
  //   Inport: '<Root>/input_lon'

  if (rtb_LogicalOperator1_n) {
    // Switch: '<S12>/Switch2' incorporates:
    //   Sum: '<S12>/Sum1'

    if (rtb_LogicalOperator2_e) {
      // Saturate: '<S12>/Saturation5'
      if (rtb_Saturation5_k > 0.261780113F) {
        rtb_Saturation5_k = 0.261780113F;
      } else {
        if (rtb_Saturation5_k < -0.261780113F) {
          rtb_Saturation5_k = -0.261780113F;
        }
      }

      // End of Saturate: '<S12>/Saturation5'
    } else {
      rtb_Saturation5_k = rtb_Sum1_j_idx_2;
    }

    // End of Switch: '<S12>/Switch2'
  } else {
    if (QS_InnerRateLoop_U.input_lon > 0.05F) {
      // DeadZone: '<S12>/Dead Zone2' incorporates:
      //   Inport: '<Root>/input_lon'

      tmp = QS_InnerRateLoop_U.input_lon - 0.05F;
    } else if (QS_InnerRateLoop_U.input_lon >= -0.05F) {
      // DeadZone: '<S12>/Dead Zone2'
      tmp = 0.0F;
    } else {
      // DeadZone: '<S12>/Dead Zone2' incorporates:
      //   Inport: '<Root>/input_lon'

      tmp = QS_InnerRateLoop_U.input_lon - -0.05F;
    }

    rtb_Saturation5_k = 0.785340309F * tmp;
  }

  // End of Switch: '<S96>/Switch'

  // Switch: '<S96>/Switch1' incorporates:
  //   RelationalOperator: '<S96>/Relational Operator'
  //   Sum: '<S96>/Sum1'
  //   UnitDelay: '<S96>/Unit Delay'
  //   UnitDelay: '<S96>/Unit Delay1'
  //   UnitDelay: '<S96>/Unit Delay2'

  if (QS_InnerRateLoop_DWork.UnitDelay_DSTATE_e2 == rtb_LogicalOperator1_n) {
    rtb_uDLookupTable_a = QS_InnerRateLoop_DWork.UnitDelay1_DSTATE_f;
  } else {
    rtb_uDLookupTable_a = QS_InnerRateLoop_DWork.UnitDelay2_DSTATE_k -
      rtb_Saturation5_k;
  }

  // End of Switch: '<S96>/Switch1'

  // Saturate: '<S96>/Saturation'
  if (rtb_uDLookupTable_a > 0.0025F) {
    rtb_Sum4_a = 0.0025F;
  } else if (rtb_uDLookupTable_a < -0.0025F) {
    rtb_Sum4_a = -0.0025F;
  } else {
    rtb_Sum4_a = rtb_uDLookupTable_a;
  }

  // End of Saturate: '<S96>/Saturation'

  // Sum: '<S96>/Sum'
  rtb_Sum1_j_idx_3 = rtb_uDLookupTable_a - rtb_Sum4_a;

  // Sum: '<S96>/Sum2'
  rtb_Sum4_a = rtb_Saturation5_k + rtb_Sum1_j_idx_3;

  // Lookup_n-D: '<S46>/1-D Lookup Table2'
  bpIdx = plook_u32ff_evencg(rtb_Saturation8, 0.0F, 1.75F, 4U,
    &rtb_Saturation5_k);

  // Lookup_n-D: '<S47>/1-D Lookup Table2'
  bpIdx_0 = plook_u32ff_evencg(rtb_Saturation8, 0.0F, 1.75F, 4U,
    &rtb_uDLookupTable2_bw);

  // Product: '<S47>/Product' incorporates:
  //   Lookup_n-D: '<S46>/1-D Lookup Table2'
  //   Lookup_n-D: '<S47>/1-D Lookup Table2'
  //   Product: '<S46>/Product'
  //   Sum: '<S43>/Sum'
  //   Sum: '<S43>/Sum1'
  //   UnitDelay: '<S43>/Unit Delay'
  //   UnitDelay: '<S43>/Unit Delay1'

  rtb_Add5_ky = ((rtb_Sum4_a - QS_InnerRateLoop_DWork.UnitDelay1_DSTATE_c) *
                 intrp1d_fu32fl_pw(bpIdx, rtb_Saturation5_k,
    QS_InnerRateLoop_ConstP.uDLookupTable2_tableData_or) -
                 QS_InnerRateLoop_DWork.UnitDelay_DSTATE_j) * intrp1d_fu32fl_pw
    (bpIdx_0, rtb_uDLookupTable2_bw,
     QS_InnerRateLoop_ConstP.uDLookupTable2_tableData_gp);

  // RelationalOperator: '<S12>/Relational Operator4'
  rtb_RelationalOperator4_e = (!is_equal(rtb_Sum1_j_idx_2,rtb_Sum1_gw));

  // Switch: '<S79>/Switch' incorporates:
  //   Constant: '<S79>/Constant'
  //   Lookup_n-D: '<S78>/1-D Lookup Table2'
  //   Product: '<S78>/Product'

  if (rtb_RelationalOperator4_e) {
    rtb_Sum1_j_idx_2 = 0.0F;
  } else {
    // Lookup_n-D: '<S78>/1-D Lookup Table2'
    bpIdx = plook_u32ff_evenxg(rtb_Saturation8, 0.0F, 1.75F, 4U,
      &rtb_Saturation5_k);
    rtb_Sum1_j_idx_2 = intrp1d_fu32fl_pw(bpIdx, rtb_Saturation5_k,
      QS_InnerRateLoop_ConstP.uDLookupTable2_tableData_f) * rtb_uDLookupTable1_l;
  }

  // End of Switch: '<S79>/Switch'

  // DiscreteIntegrator: '<S75>/Discrete-Time Integrator'
  if (rtb_LogicalOperator1_n &&
      (QS_InnerRateLoop_DWork.DiscreteTimeIntegrator_PrevR_dc <= 0)) {
    QS_InnerRateLoop_DWork.DiscreteTimeIntegrator_DSTAT_cf = 0.0F;
  }

  if (QS_InnerRateLoop_DWork.DiscreteTimeIntegrator_DSTAT_cf >= 0.0174520072F) {
    QS_InnerRateLoop_DWork.DiscreteTimeIntegrator_DSTAT_cf = 0.0174520072F;
  } else {
    if (QS_InnerRateLoop_DWork.DiscreteTimeIntegrator_DSTAT_cf <= -0.0174520072F)
    {
      QS_InnerRateLoop_DWork.DiscreteTimeIntegrator_DSTAT_cf = -0.0174520072F;
    }
  }

  // Lookup_n-D: '<S73>/1-D Lookup Table2'
  bpIdx = plook_u32ff_evencg(rtb_Saturation8, 0.0F, 1.75F, 4U,
    &rtb_Saturation5_k);

  // Product: '<S67>/Divide1' incorporates:
  //   Product: '<S67>/Divide7'

  rtb_uDLookupTable1_l = QS_InnerRateLoop_ConstB.TrigonometricFunction4_k *
    QS_InnerRateLoop_ConstB.TrigonometricFunction5_j;

  // Product: '<S73>/Product' incorporates:
  //   Lookup_n-D: '<S73>/1-D Lookup Table2'
  //   Product: '<S67>/Divide1'
  //   Product: '<S67>/Divide11'
  //   Product: '<S67>/Divide13'
  //   Product: '<S67>/Divide15'
  //   Product: '<S67>/Divide3'
  //   Product: '<S67>/Divide7'
  //   Product: '<S67>/Divide8'
  //   Sum: '<S67>/Add1'
  //   Sum: '<S67>/Add3'
  //   Sum: '<S67>/Add6'
  //   Sum: '<S68>/Sum'
  //   Sum: '<S68>/Sum4'

  rtb_TrigonometricFunction6 = (((((rtb_uDLookupTable1_l * rtb_Gain1 -
    QS_InnerRateLoop_ConstB.TrigonometricFunction1_g * rtb_uDLookupTable_l_tmp) *
    rtb_Saturation_h + (rtb_uDLookupTable1_l * rtb_uDLookupTable_l_tmp +
                        QS_InnerRateLoop_ConstB.TrigonometricFunction1_g *
                        rtb_Gain1) * rtb_Saturation1_p) +
    QS_InnerRateLoop_ConstB.TrigonometricFunction4_k *
    QS_InnerRateLoop_ConstB.TrigonometricFunction2_a * rtb_Saturation2_h) +
    rtb_Add6_a) - rtb_Add6_i) * intrp1d_fu32fl_pw(bpIdx, rtb_Saturation5_k,
    QS_InnerRateLoop_ConstP.uDLookupTable2_tableData_n);

  // Sum: '<S68>/Sum1' incorporates:
  //   DiscreteIntegrator: '<S75>/Discrete-Time Integrator'

  rtb_Sum1_gw = QS_InnerRateLoop_DWork.DiscreteTimeIntegrator_DSTAT_cf +
    rtb_TrigonometricFunction6;

  // Lookup_n-D: '<S68>/1-D Lookup Table'
  bpIdx = plook_u32ff_evencg(rtb_Saturation8, 0.0F, 1.75F, 4U,
    &rtb_Saturation5_k);
  rtb_uDLookupTable_a = intrp1d_fu32fl_pw(bpIdx, rtb_Saturation5_k,
    QS_InnerRateLoop_ConstP.uDLookupTable_tableData_hs);

  // Lookup_n-D: '<S68>/1-D Lookup Table1'
  bpIdx = plook_u32ff_evencg(rtb_Saturation8, 0.0F, 1.75F, 4U,
    &rtb_Saturation5_k);
  rtb_uDLookupTable1_l = intrp1d_fu32fl_pw(bpIdx, rtb_Saturation5_k,
    QS_InnerRateLoop_ConstP.uDLookupTable1_tableData_p);

  // DiscreteIntegrator: '<S76>/Discrete-Time Integrator'
  rtb_Add6_i = QS_InnerRateLoop_DWork.DiscreteTimeIntegrator_DSTAT_cc;

  // Sum: '<S76>/Sum1' incorporates:
  //   DiscreteIntegrator: '<S76>/Discrete-Time Integrator'
  //   Product: '<S76>/Product1'

  rtb_TrigonometricFunction3 = rtb_Sum1_gw * rtb_uDLookupTable_a /
    rtb_uDLookupTable1_l +
    QS_InnerRateLoop_DWork.DiscreteTimeIntegrator_DSTAT_cc;

  // Saturate: '<S12>/Saturation1' incorporates:
  //   Sum: '<S12>/Sum3'

  if (rtb_TrigonometricFunction3 > 0.610820234F) {
    rtb_Add6_a = 0.610820234F;
  } else if (rtb_TrigonometricFunction3 < -0.610820234F) {
    rtb_Add6_a = -0.610820234F;
  } else {
    rtb_Add6_a = rtb_TrigonometricFunction3;
  }

  // End of Saturate: '<S12>/Saturation1'

  // RelationalOperator: '<S12>/Relational Operator1' incorporates:
  //   Sum: '<S12>/Sum3'

  rtb_RelationalOperator_b1 = (!is_equal(rtb_Add6_a,rtb_TrigonometricFunction3));

  // Switch: '<S86>/Switch' incorporates:
  //   Constant: '<S86>/Constant'
  //   Logic: '<S71>/Logical Operator'
  //   Lookup_n-D: '<S85>/1-D Lookup Table2'
  //   Product: '<S85>/Product'

  if (rtb_RelationalOperator4_e || rtb_RelationalOperator_b1) {
    rtb_Product_ng = 0.0F;
  } else {
    // Lookup_n-D: '<S85>/1-D Lookup Table2'
    bpIdx = plook_u32ff_evencg(rtb_Saturation8, 0.0F, 1.75F, 4U,
      &rtb_Saturation5_k);
    rtb_Product_ng *= intrp1d_fu32fl_pw(bpIdx, rtb_Saturation5_k,
      QS_InnerRateLoop_ConstP.pooled12);
  }

  // End of Switch: '<S86>/Switch'

  // Switch: '<S75>/Switch' incorporates:
  //   Constant: '<S75>/Constant'
  //   Lookup_n-D: '<S74>/1-D Lookup Table2'
  //   Product: '<S74>/Product'

  if (rtb_RelationalOperator_b1) {
    rtb_TrigonometricFunction6 = 0.0F;
  } else {
    // Lookup_n-D: '<S74>/1-D Lookup Table2'
    bpIdx = plook_u32ff_evencg(rtb_Saturation8, 0.0F, 1.75F, 4U,
      &rtb_Saturation5_k);
    rtb_TrigonometricFunction6 *= intrp1d_fu32fl_pw(bpIdx, rtb_Saturation5_k,
      QS_InnerRateLoop_ConstP.uDLookupTable2_tableData_o);
  }

  // End of Switch: '<S75>/Switch'

  // Switch: '<S89>/Switch' incorporates:
  //   Constant: '<S89>/Constant'
  //   Logic: '<S72>/Logical Operator'
  //   Lookup_n-D: '<S88>/1-D Lookup Table2'
  //   Product: '<S88>/Product'

  if (rtb_RelationalOperator4_e || rtb_RelationalOperator_b1) {
    rtb_Product = 0.0F;
  } else {
    // Lookup_n-D: '<S88>/1-D Lookup Table2'
    bpIdx = plook_u32ff_evencg(rtb_Saturation8, 0.0F, 1.75F, 4U,
      &rtb_Saturation5_k);
    rtb_Product *= intrp1d_fu32fl_pw(bpIdx, rtb_Saturation5_k,
      QS_InnerRateLoop_ConstP.pooled12);
  }

  // End of Switch: '<S89>/Switch'

  // Switch: '<S97>/Switch' incorporates:
  //   DeadZone: '<S12>/Dead Zone1'
  //   Gain: '<S12>/phicmd'
  //   Inport: '<Root>/input_lat'

  if (rtb_LogicalOperator1_n) {
    // Switch: '<S12>/Switch1' incorporates:
    //   Sum: '<S12>/Sum4'

    if (rtb_LogicalOperator2_e) {
      // Saturate: '<S12>/Saturation3'
      if (rtb_TrigonometricFunction3 > 0.174520075F) {
        rtb_Saturation5_k = 0.174520075F;
      } else if (rtb_TrigonometricFunction3 < -0.174520075F) {
        rtb_Saturation5_k = -0.174520075F;
      } else {
        rtb_Saturation5_k = rtb_TrigonometricFunction3;
      }

      // End of Saturate: '<S12>/Saturation3'
    } else {
      rtb_Saturation5_k = rtb_Add6_a;
    }

    // End of Switch: '<S12>/Switch1'
  } else {
    if (QS_InnerRateLoop_U.input_lat > 0.05F) {
      // DeadZone: '<S12>/Dead Zone1' incorporates:
      //   Inport: '<Root>/input_lat'

      tmp = QS_InnerRateLoop_U.input_lat - 0.05F;
    } else if (QS_InnerRateLoop_U.input_lat >= -0.05F) {
      // DeadZone: '<S12>/Dead Zone1'
      tmp = 0.0F;
    } else {
      // DeadZone: '<S12>/Dead Zone1' incorporates:
      //   Inport: '<Root>/input_lat'

      tmp = QS_InnerRateLoop_U.input_lat - -0.05F;
    }

    rtb_Saturation5_k = 0.785340309F * tmp;
  }

  // End of Switch: '<S97>/Switch'

  // Switch: '<S97>/Switch1' incorporates:
  //   RelationalOperator: '<S97>/Relational Operator'
  //   Sum: '<S97>/Sum1'
  //   UnitDelay: '<S97>/Unit Delay'
  //   UnitDelay: '<S97>/Unit Delay1'
  //   UnitDelay: '<S97>/Unit Delay2'

  if (QS_InnerRateLoop_DWork.UnitDelay_DSTATE_j1 == rtb_LogicalOperator1_n) {
    rtb_uDLookupTable2_bw = QS_InnerRateLoop_DWork.UnitDelay1_DSTATE_fj;
  } else {
    rtb_uDLookupTable2_bw = QS_InnerRateLoop_DWork.UnitDelay2_DSTATE_a -
      rtb_Saturation5_k;
  }

  // End of Switch: '<S97>/Switch1'

  // Saturate: '<S97>/Saturation'
  if (rtb_uDLookupTable2_bw > 0.0025F) {
    rtb_Gain1 = 0.0025F;
  } else if (rtb_uDLookupTable2_bw < -0.0025F) {
    rtb_Gain1 = -0.0025F;
  } else {
    rtb_Gain1 = rtb_uDLookupTable2_bw;
  }

  // End of Saturate: '<S97>/Saturation'

  // Sum: '<S97>/Sum'
  rtb_Gain1 = rtb_uDLookupTable2_bw - rtb_Gain1;

  // Sum: '<S97>/Sum2'
  rtb_TrigonometricFunction3 = rtb_Saturation5_k + rtb_Gain1;

  // Lookup_n-D: '<S30>/1-D Lookup Table2'
  bpIdx = plook_u32ff_evenxg(rtb_Saturation8, 0.0F, 1.75F, 4U,
    &rtb_Saturation5_k);

  // Sum: '<S27>/Sum' incorporates:
  //   Lookup_n-D: '<S30>/1-D Lookup Table2'
  //   Product: '<S30>/Product'
  //   Sum: '<S27>/Sum1'
  //   UnitDelay: '<S27>/Unit Delay'
  //   UnitDelay: '<S27>/Unit Delay1'

  rtb_Add6_a = (rtb_TrigonometricFunction3 -
                QS_InnerRateLoop_DWork.UnitDelay1_DSTATE_a) * intrp1d_fu32fl_pw
    (bpIdx, rtb_Saturation5_k,
     QS_InnerRateLoop_ConstP.uDLookupTable2_tableData_ob) -
    QS_InnerRateLoop_DWork.UnitDelay_DSTATE_g;

  // Lookup_n-D: '<S31>/1-D Lookup Table2'
  bpIdx = plook_u32ff_evencg(rtb_Saturation8, 0.0F, 1.75F, 4U,
    &rtb_Saturation5_k);

  // Sum: '<S80>/Sum' incorporates:
  //   Product: '<S80>/Product2'
  //   Sum: '<S80>/Sum2'
  //   UnitDelay: '<S80>/Unit Delay'

  rtb_Product_cw = (rtb_Product_cw - rtb_Abs) * rtb_DeadZone3 / rtb_Product_cw -
    QS_InnerRateLoop_DWork.UnitDelay_DSTATE_oc;

  // Outport: '<Root>/theta_cmd' incorporates:
  //   DiscreteIntegrator: '<S43>/Discrete-Time Integrator1'

  QS_InnerRateLoop_Y.theta_cmd =
    QS_InnerRateLoop_DWork.DiscreteTimeIntegrator1_DSTAT_m;

  // Outport: '<Root>/phi_cmd' incorporates:
  //   DiscreteIntegrator: '<S27>/Discrete-Time Integrator1'

  QS_InnerRateLoop_Y.phi_cmd =
    QS_InnerRateLoop_DWork.DiscreteTimeIntegrator1_DSTAT_o;

  // Switch: '<S83>/Switch' incorporates:
  //   Constant: '<S83>/Constant'
  //   Lookup_n-D: '<S81>/1-D Lookup Table2'
  //   Product: '<S81>/Product'
  //   RelationalOperator: '<S12>/Relational Operator2'

  if (!is_equal(rtb_Saturation2_o,rtb_Sum2_k)) {
    rtb_Saturation8 = 0.0F;
  } else {
    // Lookup_n-D: '<S81>/1-D Lookup Table2'
    bpIdx_0 = plook_u32ff_evencg(rtb_Saturation8, 0.0F, 1.75F, 4U,
      &rtb_uDLookupTable2_bw);
    rtb_Saturation8 = intrp1d_fu32fl_pw(bpIdx_0, rtb_uDLookupTable2_bw,
      QS_InnerRateLoop_ConstP.uDLookupTable2_tableData_ej) * rtb_Product_ee;
  }

  // End of Switch: '<S83>/Switch'

  // RelationalOperator: '<S11>/Relational Operator' incorporates:
  //   Constant: '<S11>/Constant3'

  rtb_RelationalOperator_b1 = (rtb_Gain2 >= 18.0F);

  // Outport: '<Root>/ScoreDisplay' incorporates:
  //   Logic: '<S11>/Logical Operator1'
  //   RelationalOperator: '<S11>/Relational Operator2'

  QS_InnerRateLoop_Y.ScoreDisplay = (rtb_RelationalOperator_b1 && (rtb_Gain2 <=
    QS_InnerRateLoop_ConstB.Sum2));

  // Outport: '<Root>/ScoreOn' incorporates:
  //   Logic: '<S11>/Logical Operator'
  //   RelationalOperator: '<S11>/Relational Operator1'

  QS_InnerRateLoop_Y.ScoreOn = (rtb_RelationalOperator_b1 && (rtb_Gain2 <=
    QS_InnerRateLoop_ConstB.Sum1));

  // Outport: '<Root>/Vdown_corr'
  QS_InnerRateLoop_Y.Vdown_corr = rtb_Saturation2_h;

  // Outport: '<Root>/Veast_corr'
  QS_InnerRateLoop_Y.Veast_corr = rtb_Saturation1_p;

  // Outport: '<Root>/Vnorth_corr'
  QS_InnerRateLoop_Y.Vnorth_corr = rtb_Saturation_h;

  // Outport: '<Root>/TrajectoryON'
  QS_InnerRateLoop_Y.TrajectoryON = rtb_LogicalOperator1_n;

  // Sum: '<S14>/Sum' incorporates:
  //   Constant: '<S1>/Constant'
  //   Inport: '<Root>/Ax_mpss'
  //   Inport: '<Root>/Ay_mpss'
  //   Inport: '<Root>/Az_mpss'
  //   Inport: '<Root>/theta_rad'
  //   Product: '<S6>/Divide11'
  //   Product: '<S6>/Divide12'
  //   Product: '<S6>/Divide2'
  //   Sum: '<S1>/Sum2'
  //   Sum: '<S6>/Add7'
  //   Trigonometry: '<S6>/Trigonometric Function5'
  //   UnitDelay: '<S14>/Unit Delay'

  rtb_Sum = (((rtb_TrigonometricFunction3_tmp * rtb_Saturation_fr_tmp *
               QS_InnerRateLoop_U.Az_mpss + rtb_TrigonometricFunction6_tmp *
               rtb_Saturation_fr_tmp * QS_InnerRateLoop_U.Ay_mpss) +
              -static_cast<real32_T>(sin((real_T)QS_InnerRateLoop_U.theta_rad)) *
              QS_InnerRateLoop_U.Ax_mpss) + 9.81) -
    QS_InnerRateLoop_DWork.UnitDelay_DSTATE_j2;

  // Sum: '<S15>/Sum' incorporates:
  //   Gain: '<Root>/Gain'
  //   Inport: '<Root>/Baro_Alt_m'
  //   UnitDelay: '<S15>/Unit Delay'

  rtb_Saturation1_p = -QS_InnerRateLoop_U.Baro_Alt_m -
    QS_InnerRateLoop_DWork.UnitDelay_DSTATE_da;

  // Sum: '<S16>/Sum' incorporates:
  //   Gain: '<Root>/Gain'
  //   Inport: '<Root>/Baro_Alt_m'
  //   UnitDelay: '<S16>/Unit Delay'

  rtb_Saturation_h = -QS_InnerRateLoop_U.Baro_Alt_m -
    QS_InnerRateLoop_DWork.UnitDelay_DSTATE_ag;

  // DiscreteIntegrator: '<S16>/Discrete-Time Integrator' incorporates:
  //   Gain: '<Root>/Gain'
  //   Inport: '<Root>/Baro_Alt_m'
  //   Inport: '<Root>/engage'

  if (QS_InnerRateLoop_DWork.DiscreteTimeIntegrator_IC_LOA_j != 0) {
    QS_InnerRateLoop_DWork.DiscreteTimeIntegrator_DSTATE_e =
      -QS_InnerRateLoop_U.Baro_Alt_m;
  }

  if (QS_InnerRateLoop_U.engage &&
      (QS_InnerRateLoop_DWork.DiscreteTimeIntegrator_PrevRe_l <= 0)) {
    QS_InnerRateLoop_DWork.DiscreteTimeIntegrator_DSTATE_e =
      -QS_InnerRateLoop_U.Baro_Alt_m;
  }

  // DiscreteIntegrator: '<S17>/Discrete-Time Integrator' incorporates:
  //   Inport: '<Root>/engage'

  if (QS_InnerRateLoop_U.engage &&
      (QS_InnerRateLoop_DWork.DiscreteTimeIntegrator_PrevR_em <= 0)) {
    QS_InnerRateLoop_DWork.DiscreteTimeIntegrator_DSTAT_cg = 0.0F;
  }

  rtb_Saturation2_h = QS_InnerRateLoop_DWork.DiscreteTimeIntegrator_DSTAT_cg;

  // Outport: '<Root>/CF_Alt' incorporates:
  //   DiscreteIntegrator: '<S16>/Discrete-Time Integrator'
  //   DiscreteIntegrator: '<S17>/Discrete-Time Integrator'
  //   Sum: '<S1>/Sum1'

  QS_InnerRateLoop_Y.CF_Alt =
    QS_InnerRateLoop_DWork.DiscreteTimeIntegrator_DSTATE_e +
    QS_InnerRateLoop_DWork.DiscreteTimeIntegrator_DSTAT_cg;

  // DiscreteIntegrator: '<S15>/Discrete-Time Integrator' incorporates:
  //   Gain: '<Root>/Gain'
  //   Inport: '<Root>/Baro_Alt_m'
  //   Inport: '<Root>/engage'

  if (QS_InnerRateLoop_DWork.DiscreteTimeIntegrator_IC_LOA_m != 0) {
    QS_InnerRateLoop_DWork.DiscreteTimeIntegrator_DSTAT_o3 =
      -QS_InnerRateLoop_U.Baro_Alt_m;
  }

  if (QS_InnerRateLoop_U.engage &&
      (QS_InnerRateLoop_DWork.DiscreteTimeIntegrator_PrevR_hn <= 0)) {
    QS_InnerRateLoop_DWork.DiscreteTimeIntegrator_DSTAT_o3 =
      -QS_InnerRateLoop_U.Baro_Alt_m;
  }

  // Sum: '<S15>/Sum1' incorporates:
  //   DiscreteIntegrator: '<S15>/Discrete-Time Integrator'
  //   Gain: '<Root>/Gain'
  //   Inport: '<Root>/Baro_Alt_m'

  rtb_Product_ee = -QS_InnerRateLoop_U.Baro_Alt_m -
    QS_InnerRateLoop_DWork.DiscreteTimeIntegrator_DSTAT_o3;

  // Sum: '<S13>/Sum3' incorporates:
  //   Gain: '<S13>/Gain1'
  //   Sum: '<S13>/Sum5'
  //   UnitDelay: '<S13>/Unit Delay'
  //   UnitDelay: '<S13>/Unit Delay1'

  rtb_Gain2 = (rtb_Product_ee - QS_InnerRateLoop_DWork.UnitDelay1_DSTATE_a1) *
    1.41442716F - QS_InnerRateLoop_DWork.UnitDelay_DSTATE_ak;

  // DiscreteIntegrator: '<S13>/Discrete-Time Integrator1' incorporates:
  //   Inport: '<Root>/engage'

  if (QS_InnerRateLoop_DWork.DiscreteTimeIntegrator1_IC_LO_e != 0) {
    QS_InnerRateLoop_DWork.DiscreteTimeIntegrator1_DSTAT_g = rtb_Product_ee;
  }

  if (QS_InnerRateLoop_U.engage &&
      (QS_InnerRateLoop_DWork.DiscreteTimeIntegrator1_Prev_gs <= 0)) {
    QS_InnerRateLoop_DWork.DiscreteTimeIntegrator1_DSTAT_g = rtb_Product_ee;
  }

  // DiscreteIntegrator: '<S14>/Discrete-Time Integrator' incorporates:
  //   Inport: '<Root>/engage'

  if (QS_InnerRateLoop_U.engage &&
      (QS_InnerRateLoop_DWork.DiscreteTimeIntegrator_PrevR_pr <= 0)) {
    QS_InnerRateLoop_DWork.DiscreteTimeIntegrator_DSTAT_nv = 0.0F;
  }

  // Sum: '<S1>/Sum' incorporates:
  //   DiscreteIntegrator: '<S13>/Discrete-Time Integrator1'
  //   DiscreteIntegrator: '<S14>/Discrete-Time Integrator'

  rtb_DeadZone3 = QS_InnerRateLoop_DWork.DiscreteTimeIntegrator1_DSTAT_g +
    QS_InnerRateLoop_DWork.DiscreteTimeIntegrator_DSTAT_nv;

  // Outport: '<Root>/CF_Vz'
  QS_InnerRateLoop_Y.CF_Vz = rtb_DeadZone3;

  // DiscreteIntegrator: '<S13>/Discrete-Time Integrator' incorporates:
  //   Inport: '<Root>/engage'

  if (QS_InnerRateLoop_U.engage &&
      (QS_InnerRateLoop_DWork.DiscreteTimeIntegrator_PrevR_lm <= 0)) {
    QS_InnerRateLoop_DWork.DiscreteTimeIntegrator_DSTAT_gh = 0.0F;
  }

  // DiscreteIntegrator: '<S27>/Discrete-Time Integrator' incorporates:
  //   Inport: '<Root>/engage'

  if (QS_InnerRateLoop_U.engage &&
      (QS_InnerRateLoop_DWork.DiscreteTimeIntegrator_PrevRe_f <= 0)) {
    QS_InnerRateLoop_DWork.DiscreteTimeIntegrator_DSTAT_dn = 0.0F;
  }

  // DiscreteIntegrator: '<S43>/Discrete-Time Integrator' incorporates:
  //   Inport: '<Root>/engage'

  if (QS_InnerRateLoop_U.engage &&
      (QS_InnerRateLoop_DWork.DiscreteTimeIntegrator_PrevR_f0 <= 0)) {
    QS_InnerRateLoop_DWork.DiscreteTimeIntegrator_DSTAT_nq = 0.0F;
  }

  // DeadZone: '<S12>/Dead Zone3' incorporates:
  //   Inport: '<Root>/input_ped'

  if (QS_InnerRateLoop_U.input_ped > 0.05F) {
    tmp = QS_InnerRateLoop_U.input_ped - 0.05F;
  } else if (QS_InnerRateLoop_U.input_ped >= -0.05F) {
    tmp = 0.0F;
  } else {
    tmp = QS_InnerRateLoop_U.input_ped - -0.05F;
  }

  // End of DeadZone: '<S12>/Dead Zone3'

  // Sum: '<S95>/Sum' incorporates:
  //   Gain: '<S12>/rcmd'
  //   UnitDelay: '<S95>/Unit Delay'

  rtb_Product_ee = 3.14136124F * tmp - QS_InnerRateLoop_DWork.UnitDelay_DSTATE_k;

  // DiscreteIntegrator: '<S95>/Discrete-Time Integrator' incorporates:
  //   Inport: '<Root>/engage'

  if ((QS_InnerRateLoop_U.engage &&
       (QS_InnerRateLoop_DWork.DiscreteTimeIntegrator_PrevR_bv <= 0)) ||
      ((!QS_InnerRateLoop_U.engage) &&
       (QS_InnerRateLoop_DWork.DiscreteTimeIntegrator_PrevR_bv == 1))) {
    QS_InnerRateLoop_DWork.DiscreteTimeIntegrator_DSTAT_gy = 0.0F;
  }

  // Update for Delay: '<S90>/Delay1' incorporates:
  //   Inport: '<Root>/CH8_flag'

  QS_InnerRateLoop_DWork.Delay1_DSTATE = QS_InnerRateLoop_U.CH8_flag;

  // Switch: '<S90>/Switch'
  if (rtb_LogicalOperator2_g) {
    // Update for Delay: '<S90>/Delay2'
    QS_InnerRateLoop_DWork.Delay2_DSTATE = rtb_Sum2_h;
  } else {
    // Update for Delay: '<S90>/Delay2' incorporates:
    //   Constant: '<S90>/Constant1'

    QS_InnerRateLoop_DWork.Delay2_DSTATE = 0.0;
  }

  // End of Switch: '<S90>/Switch'

  // Update for DiscreteIntegrator: '<S89>/Discrete-Time Integrator'
  QS_InnerRateLoop_DWork.DiscreteTimeIntegrator_DSTATE_a += 0.0025F *
    rtb_Product;
  QS_InnerRateLoop_DWork.DiscreteTimeIntegrator_PrevRese = static_cast<int8_T>
    (rtb_LogicalOperator1_n);

  // Update for DiscreteIntegrator: '<S64>/Discrete-Time Integrator'
  QS_InnerRateLoop_DWork.DiscreteTimeIntegrator_IC_LOADI = 0U;
  QS_InnerRateLoop_DWork.DiscreteTimeIntegrator_DSTATE_m += 0.0025F *
    rtb_Sum1_j_idx_0;
  QS_InnerRateLoop_DWork.DiscreteTimeIntegrator_PrevRe_a = static_cast<int8_T>
    (rtb_LogicalOperator1_n);

  // Update for DiscreteIntegrator: '<S86>/Discrete-Time Integrator'
  QS_InnerRateLoop_DWork.DiscreteTimeIntegrator_DSTATE_h += 0.0025F *
    rtb_Product_ng;
  QS_InnerRateLoop_DWork.DiscreteTimeIntegrator_PrevRe_o = static_cast<int8_T>
    (rtb_LogicalOperator1_n);

  // Update for DiscreteIntegrator: '<S64>/Discrete-Time Integrator1'
  QS_InnerRateLoop_DWork.DiscreteTimeIntegrator1_IC_LOAD = 0U;
  QS_InnerRateLoop_DWork.DiscreteTimeIntegrator1_DSTATE += 0.0025F *
    rtb_Sum1_j_idx_1;
  QS_InnerRateLoop_DWork.DiscreteTimeIntegrator1_PrevRes = static_cast<int8_T>
    (rtb_LogicalOperator1_n);

  // Update for DiscreteIntegrator: '<S83>/Discrete-Time Integrator'
  QS_InnerRateLoop_DWork.DiscreteTimeIntegrator_DSTATE_c += 0.0025F *
    rtb_Saturation8;
  QS_InnerRateLoop_DWork.DiscreteTimeIntegrator_PrevRe_b = static_cast<int8_T>
    (rtb_LogicalOperator1_n);

  // Update for DiscreteIntegrator: '<S64>/Discrete-Time Integrator2'
  QS_InnerRateLoop_DWork.DiscreteTimeIntegrator2_IC_LOAD = 0U;
  QS_InnerRateLoop_DWork.DiscreteTimeIntegrator2_DSTATE += 0.0025F * rtb_Add7_d;
  QS_InnerRateLoop_DWork.DiscreteTimeIntegrator2_PrevRes = static_cast<int8_T>
    (rtb_LogicalOperator1_n);

  // Update for UnitDelay: '<S11>/Unit Delay'
  QS_InnerRateLoop_DWork.UnitDelay_DSTATE = rtb_Product2;

  // Update for UnitDelay: '<S98>/Unit Delay1'
  QS_InnerRateLoop_DWork.UnitDelay1_DSTATE = rtb_DeadZone;

  // Update for UnitDelay: '<S98>/Unit Delay'
  QS_InnerRateLoop_DWork.UnitDelay_DSTATE_ax = rtb_LogicalOperator1_n;

  // Update for UnitDelay: '<S98>/Unit Delay2'
  QS_InnerRateLoop_DWork.UnitDelay2_DSTATE = rtb_Switch_ep;

  // Update for UnitDelay: '<S34>/Unit Delay' incorporates:
  //   DiscreteIntegrator: '<S34>/Discrete-Time Integrator'

  QS_InnerRateLoop_DWork.UnitDelay_DSTATE_a =
    QS_InnerRateLoop_DWork.DiscreteTimeIntegrator_DSTAT_fs;

  // Update for DiscreteIntegrator: '<S26>/Discrete-Time Integrator'
  QS_InnerRateLoop_DWork.DiscreteTimeIntegrator_DSTAT_hq += rtb_Product_b_tmp *
    0.0025F;

  // Update for DiscreteIntegrator: '<S25>/Discrete-Time Integrator'
  QS_InnerRateLoop_DWork.DiscreteTimeIntegrator_DSTATE_b +=
    rtb_derivativecutofffrequency_0 * 0.0025F;

  // Update for DiscreteIntegrator: '<S27>/Discrete-Time Integrator1' incorporates:
  //   DiscreteIntegrator: '<S27>/Discrete-Time Integrator'
  //   Inport: '<Root>/engage'

  QS_InnerRateLoop_DWork.DiscreteTimeIntegrator1_DSTAT_o += 0.0025F *
    QS_InnerRateLoop_DWork.DiscreteTimeIntegrator_DSTAT_dn;
  QS_InnerRateLoop_DWork.DiscreteTimeIntegrator1_PrevR_g = static_cast<int8_T>
    (QS_InnerRateLoop_U.engage);

  // Update for DiscreteIntegrator: '<S42>/Discrete-Time Integrator'
  QS_InnerRateLoop_DWork.DiscreteTimeIntegrator_DSTAT_mk += rtb_Product_b_tmp_0 *
    0.0025F;

  // Update for DiscreteIntegrator: '<S41>/Discrete-Time Integrator'
  QS_InnerRateLoop_DWork.DiscreteTimeIntegrator_DSTATE_o +=
    rtb_derivativecutofffrequency_b * 0.0025F;

  // Update for DiscreteIntegrator: '<S43>/Discrete-Time Integrator1' incorporates:
  //   DiscreteIntegrator: '<S43>/Discrete-Time Integrator'
  //   Inport: '<Root>/engage'

  QS_InnerRateLoop_DWork.DiscreteTimeIntegrator1_DSTAT_m += 0.0025F *
    QS_InnerRateLoop_DWork.DiscreteTimeIntegrator_DSTAT_nq;
  QS_InnerRateLoop_DWork.DiscreteTimeIntegrator1_PrevR_j = static_cast<int8_T>
    (QS_InnerRateLoop_U.engage);

  // Update for DiscreteIntegrator: '<S52>/Discrete-Time Integrator'
  QS_InnerRateLoop_DWork.DiscreteTimeIntegrator_DSTATE_d += rtb_Switch2_cz *
    0.0025F;

  // Update for DiscreteIntegrator: '<S53>/Discrete-Time Integrator' incorporates:
  //   Gain: '<S53>/derivative cutoff frequency '
  //   Sum: '<S53>/Sum'

  QS_InnerRateLoop_DWork.DiscreteTimeIntegrator_DSTAT_mr += (rtb_Sum4_b -
    QS_InnerRateLoop_DWork.DiscreteTimeIntegrator_DSTAT_mr) * 100.0F * 0.0025F;

  // Update for Delay: '<S12>/Delay'
  QS_InnerRateLoop_DWork.icLoad = 0U;
  QS_InnerRateLoop_DWork.Delay_DSTATE = rtb_uDLookupTable3;

  // Update for Delay: '<S12>/Delay1'
  QS_InnerRateLoop_DWork.Delay1_DSTATE_j[0] =
    QS_InnerRateLoop_DWork.Delay1_DSTATE_j[1];
  QS_InnerRateLoop_DWork.Delay1_DSTATE_j[1] = rtb_LogicalOperator1_n;

  // Update for DiscreteIntegrator: '<S12>/Discrete-Time Integrator' incorporates:
  //   DiscreteIntegrator: '<S95>/Discrete-Time Integrator'

  QS_InnerRateLoop_DWork.DiscreteTimeIntegrator_IC_LOA_b = 0U;
  QS_InnerRateLoop_DWork.DiscreteTimeIntegrator_DSTAT_mz += 0.0025F *
    QS_InnerRateLoop_DWork.DiscreteTimeIntegrator_DSTAT_gy;
  QS_InnerRateLoop_DWork.DiscreteTimeIntegrator_PrevRe_p = static_cast<int8_T>
    (rtb_LogicalOperator1_n);

  // Update for DiscreteIntegrator: '<S54>/Discrete-Time Integrator' incorporates:
  //   Inport: '<Root>/engage'

  QS_InnerRateLoop_DWork.DiscreteTimeIntegrator_DSTATE += 0.0025 * rtb_Gain_e;
  QS_InnerRateLoop_DWork.DiscreteTimeIntegrator_PrevR_bp = static_cast<int8_T>
    (QS_InnerRateLoop_U.engage);

  // Update for DiscreteIntegrator: '<S35>/Discrete-Time Integrator' incorporates:
  //   Inport: '<Root>/engage'

  QS_InnerRateLoop_DWork.DiscreteTimeIntegrator_DSTATE_f += 0.0025F *
    rtb_Product_ib;
  if (QS_InnerRateLoop_DWork.DiscreteTimeIntegrator_DSTATE_f >= 0.1F) {
    QS_InnerRateLoop_DWork.DiscreteTimeIntegrator_DSTATE_f = 0.1F;
  } else {
    if (QS_InnerRateLoop_DWork.DiscreteTimeIntegrator_DSTATE_f <= -0.1F) {
      QS_InnerRateLoop_DWork.DiscreteTimeIntegrator_DSTATE_f = -0.1F;
    }
  }

  QS_InnerRateLoop_DWork.DiscreteTimeIntegrator_PrevRe_m = static_cast<int8_T>
    (QS_InnerRateLoop_U.engage);

  // End of Update for DiscreteIntegrator: '<S35>/Discrete-Time Integrator'

  // Update for DiscreteIntegrator: '<S34>/Discrete-Time Integrator' incorporates:
  //   Inport: '<Root>/engage'

  QS_InnerRateLoop_DWork.DiscreteTimeIntegrator_DSTAT_fs += 0.0025F *
    rtb_Product_of;
  QS_InnerRateLoop_DWork.DiscreteTimeIntegrator_PrevRe_n = static_cast<int8_T>
    (QS_InnerRateLoop_U.engage);

  // Update for DiscreteIntegrator: '<S36>/Discrete-Time Integrator' incorporates:
  //   Inport: '<Root>/engage'
  //   Product: '<S36>/Product'
  //   Product: '<S36>/Product2'
  //   Sum: '<S36>/Sum'
  //   Sum: '<S36>/Sum2'
  //   UnitDelay: '<S36>/Unit Delay'

  QS_InnerRateLoop_DWork.DiscreteTimeIntegrator_DSTAT_c4 += ((rtb_uDLookupTable1
    - rtb_uDLookupTable_cs) * rtb_Sum1_c0 / rtb_uDLookupTable1 -
    QS_InnerRateLoop_DWork.UnitDelay_DSTATE_h) * rtb_uDLookupTable_cs * 0.0025F;
  QS_InnerRateLoop_DWork.DiscreteTimeIntegrator_PrevR_by = static_cast<int8_T>
    (QS_InnerRateLoop_U.engage);

  // Update for DiscreteIntegrator: '<S28>/Discrete-Time Integrator' incorporates:
  //   Inport: '<Root>/engage'

  QS_InnerRateLoop_DWork.DiscreteTimeIntegrator_DSTAT_o2 += 0.0025F *
    rtb_Product_jr;
  QS_InnerRateLoop_DWork.DiscreteTimeIntegrator_PrevRe_e = static_cast<int8_T>
    (QS_InnerRateLoop_U.engage);

  // Update for DiscreteIntegrator: '<S29>/Discrete-Time Integrator' incorporates:
  //   Product: '<S29>/Product'
  //   Product: '<S29>/Product2'
  //   Sum: '<S29>/Sum'
  //   Sum: '<S29>/Sum2'
  //   UnitDelay: '<S29>/Unit Delay'

  QS_InnerRateLoop_DWork.DiscreteTimeIntegrator_DSTAT_bw +=
    ((rtb_uDLookupTable1_p - rtb_uDLookupTable) * rtb_Sum1_fe /
     rtb_uDLookupTable1_p - QS_InnerRateLoop_DWork.UnitDelay_DSTATE_b) *
    rtb_uDLookupTable * 0.0025F;

  // Update for DiscreteIntegrator: '<S44>/Discrete-Time Integrator' incorporates:
  //   Inport: '<Root>/engage'

  QS_InnerRateLoop_DWork.DiscreteTimeIntegrator_DSTATE_j += 0.0025F *
    rtb_Product_n;
  QS_InnerRateLoop_DWork.DiscreteTimeIntegrator_PrevRe_d = static_cast<int8_T>
    (QS_InnerRateLoop_U.engage);

  // Update for DiscreteIntegrator: '<S45>/Discrete-Time Integrator' incorporates:
  //   Product: '<S45>/Product'
  //   Sum: '<S45>/Sum'
  //   UnitDelay: '<S45>/Unit Delay'

  QS_InnerRateLoop_DWork.DiscreteTimeIntegrator_DSTAT_di += (rtb_Sum1_gg -
    QS_InnerRateLoop_DWork.UnitDelay_DSTATE_eo) * rtb_Saturation_k * 0.0025F;

  // Update for DiscreteIntegrator: '<S55>/Discrete-Time Integrator' incorporates:
  //   Inport: '<Root>/engage'

  QS_InnerRateLoop_DWork.DiscreteTimeIntegrator_DSTATE_l += 0.0025F *
    rtb_Product_ear;
  QS_InnerRateLoop_DWork.DiscreteTimeIntegrator_PrevRe_j = static_cast<int8_T>
    (QS_InnerRateLoop_U.engage);

  // Update for DiscreteIntegrator: '<S56>/Discrete-Time Integrator'
  QS_InnerRateLoop_DWork.DiscreteTimeIntegrator_DSTAT_hv += 0.0025F *
    rtb_Sum1_lq;

  // Update for DiscreteIntegrator: '<S60>/Discrete-Time Integrator' incorporates:
  //   Gain: '<S60>/Gain1'
  //   Gain: '<S60>/Gain2'
  //   Sum: '<S60>/Sum'
  //   UnitDelay: '<S60>/Unit Delay'

  QS_InnerRateLoop_DWork.DiscreteTimeIntegrator_DSTAT_co += (-5.66666651F *
    rtb_Product_hg[0] - QS_InnerRateLoop_DWork.UnitDelay_DSTATE_f) * 100.0F *
    0.0025F;

  // Update for DiscreteIntegrator: '<S61>/Discrete-Time Integrator' incorporates:
  //   Gain: '<S61>/Gain1'
  //   Gain: '<S61>/Gain2'
  //   Sum: '<S61>/Sum'
  //   UnitDelay: '<S61>/Unit Delay'

  QS_InnerRateLoop_DWork.DiscreteTimeIntegrator_DSTATE_i += (-5.66666651F *
    rtb_Product_hg[1] - QS_InnerRateLoop_DWork.UnitDelay_DSTATE_av) * 100.0F *
    0.0025F;

  // Update for DiscreteIntegrator: '<S62>/Discrete-Time Integrator' incorporates:
  //   Gain: '<S62>/Gain1'
  //   Gain: '<S62>/Gain2'
  //   Sum: '<S62>/Sum'
  //   UnitDelay: '<S62>/Unit Delay'

  QS_InnerRateLoop_DWork.DiscreteTimeIntegrator_DSTAT_ch += (-5.66666651F *
    rtb_Product_hg[2] - QS_InnerRateLoop_DWork.UnitDelay_DSTATE_d) * 100.0F *
    0.0025F;

  // Update for DiscreteIntegrator: '<S63>/Discrete-Time Integrator' incorporates:
  //   Gain: '<S63>/Gain1'
  //   Gain: '<S63>/Gain2'
  //   Sum: '<S63>/Sum'
  //   UnitDelay: '<S63>/Unit Delay'

  QS_InnerRateLoop_DWork.DiscreteTimeIntegrator_DSTAT_a5 += (0.636F *
    rtb_Product_hg[3] - QS_InnerRateLoop_DWork.UnitDelay_DSTATE_e) * 5.46F *
    0.0025F;

  // Update for UnitDelay: '<S60>/Unit Delay'
  QS_InnerRateLoop_DWork.UnitDelay_DSTATE_f = rtb_DiscreteTimeIntegrator_fi;

  // Update for UnitDelay: '<S61>/Unit Delay'
  QS_InnerRateLoop_DWork.UnitDelay_DSTATE_av = rtb_DiscreteTimeIntegrator_k1;

  // Update for UnitDelay: '<S62>/Unit Delay'
  QS_InnerRateLoop_DWork.UnitDelay_DSTATE_d = rtb_DiscreteTimeIntegrator_h;

  // Update for UnitDelay: '<S63>/Unit Delay'
  QS_InnerRateLoop_DWork.UnitDelay_DSTATE_e = rtb_DiscreteTimeIntegrator_n;

  // Update for UnitDelay: '<S56>/Unit Delay'
  QS_InnerRateLoop_DWork.UnitDelay_DSTATE_o = rtb_DiscreteTimeIntegrator_ia;

  // Update for UnitDelay: '<S45>/Unit Delay'
  QS_InnerRateLoop_DWork.UnitDelay_DSTATE_eo = rtb_DiscreteTimeIntegrator_nt;

  // Update for UnitDelay: '<S29>/Unit Delay'
  QS_InnerRateLoop_DWork.UnitDelay_DSTATE_b = rtb_DiscreteTimeIntegrator_cv;

  // Update for UnitDelay: '<S36>/Unit Delay'
  QS_InnerRateLoop_DWork.UnitDelay_DSTATE_h = rtb_DiscreteTimeIntegrator_hs;

  // Update for DiscreteIntegrator: '<S79>/Discrete-Time Integrator'
  QS_InnerRateLoop_DWork.DiscreteTimeIntegrator_DSTATE_n += 0.0025F *
    rtb_Sum1_j_idx_2;
  if (QS_InnerRateLoop_DWork.DiscreteTimeIntegrator_DSTATE_n >= 0.0174520072F) {
    QS_InnerRateLoop_DWork.DiscreteTimeIntegrator_DSTATE_n = 0.0174520072F;
  } else {
    if (QS_InnerRateLoop_DWork.DiscreteTimeIntegrator_DSTATE_n <= -0.0174520072F)
    {
      QS_InnerRateLoop_DWork.DiscreteTimeIntegrator_DSTATE_n = -0.0174520072F;
    }
  }

  QS_InnerRateLoop_DWork.DiscreteTimeIntegrator_PrevRe_h = static_cast<int8_T>
    (rtb_LogicalOperator1_n);

  // End of Update for DiscreteIntegrator: '<S79>/Discrete-Time Integrator'

  // Update for DiscreteIntegrator: '<S80>/Discrete-Time Integrator' incorporates:
  //   Product: '<S80>/Product'

  QS_InnerRateLoop_DWork.DiscreteTimeIntegrator_DSTATE_g += rtb_Abs *
    rtb_Product_cw * 0.0025F;

  // Update for UnitDelay: '<S96>/Unit Delay2'
  QS_InnerRateLoop_DWork.UnitDelay2_DSTATE_k = rtb_Sum4_a;

  // Update for UnitDelay: '<S96>/Unit Delay1'
  QS_InnerRateLoop_DWork.UnitDelay1_DSTATE_f = rtb_Sum1_j_idx_3;

  // Update for UnitDelay: '<S96>/Unit Delay'
  QS_InnerRateLoop_DWork.UnitDelay_DSTATE_e2 = rtb_LogicalOperator1_n;

  // Update for UnitDelay: '<S43>/Unit Delay1'
  QS_InnerRateLoop_DWork.UnitDelay1_DSTATE_c = rtb_Sum3_f;

  // Update for UnitDelay: '<S43>/Unit Delay' incorporates:
  //   DiscreteIntegrator: '<S43>/Discrete-Time Integrator'

  QS_InnerRateLoop_DWork.UnitDelay_DSTATE_j =
    QS_InnerRateLoop_DWork.DiscreteTimeIntegrator_DSTAT_nq;

  // Update for DiscreteIntegrator: '<S75>/Discrete-Time Integrator'
  QS_InnerRateLoop_DWork.DiscreteTimeIntegrator_DSTAT_cf += 0.0025F *
    rtb_TrigonometricFunction6;
  if (QS_InnerRateLoop_DWork.DiscreteTimeIntegrator_DSTAT_cf >= 0.0174520072F) {
    QS_InnerRateLoop_DWork.DiscreteTimeIntegrator_DSTAT_cf = 0.0174520072F;
  } else {
    if (QS_InnerRateLoop_DWork.DiscreteTimeIntegrator_DSTAT_cf <= -0.0174520072F)
    {
      QS_InnerRateLoop_DWork.DiscreteTimeIntegrator_DSTAT_cf = -0.0174520072F;
    }
  }

  QS_InnerRateLoop_DWork.DiscreteTimeIntegrator_PrevR_dc = static_cast<int8_T>
    (rtb_LogicalOperator1_n);

  // End of Update for DiscreteIntegrator: '<S75>/Discrete-Time Integrator'

  // Update for DiscreteIntegrator: '<S76>/Discrete-Time Integrator' incorporates:
  //   Product: '<S76>/Product'
  //   Product: '<S76>/Product2'
  //   Sum: '<S76>/Sum'
  //   Sum: '<S76>/Sum2'
  //   UnitDelay: '<S76>/Unit Delay'

  QS_InnerRateLoop_DWork.DiscreteTimeIntegrator_DSTAT_cc +=
    ((rtb_uDLookupTable1_l - rtb_uDLookupTable_a) * rtb_Sum1_gw /
     rtb_uDLookupTable1_l - QS_InnerRateLoop_DWork.UnitDelay_DSTATE_gi) *
    rtb_uDLookupTable_a * 0.0025F;

  // Update for UnitDelay: '<S97>/Unit Delay2'
  QS_InnerRateLoop_DWork.UnitDelay2_DSTATE_a = rtb_TrigonometricFunction3;

  // Update for UnitDelay: '<S97>/Unit Delay1'
  QS_InnerRateLoop_DWork.UnitDelay1_DSTATE_fj = rtb_Gain1;

  // Update for UnitDelay: '<S97>/Unit Delay'
  QS_InnerRateLoop_DWork.UnitDelay_DSTATE_j1 = rtb_LogicalOperator1_n;

  // Update for UnitDelay: '<S27>/Unit Delay1'
  QS_InnerRateLoop_DWork.UnitDelay1_DSTATE_a = rtb_DiscreteTimeIntegrator1;

  // Update for UnitDelay: '<S27>/Unit Delay' incorporates:
  //   DiscreteIntegrator: '<S27>/Discrete-Time Integrator'

  QS_InnerRateLoop_DWork.UnitDelay_DSTATE_g =
    QS_InnerRateLoop_DWork.DiscreteTimeIntegrator_DSTAT_dn;

  // Update for UnitDelay: '<S76>/Unit Delay'
  QS_InnerRateLoop_DWork.UnitDelay_DSTATE_gi = rtb_Add6_i;

  // Update for UnitDelay: '<S80>/Unit Delay'
  QS_InnerRateLoop_DWork.UnitDelay_DSTATE_oc = rtb_Add5_e;

  // Update for UnitDelay: '<S14>/Unit Delay' incorporates:
  //   DiscreteIntegrator: '<S14>/Discrete-Time Integrator'

  QS_InnerRateLoop_DWork.UnitDelay_DSTATE_j2 =
    QS_InnerRateLoop_DWork.DiscreteTimeIntegrator_DSTAT_nv;

  // Update for UnitDelay: '<S15>/Unit Delay' incorporates:
  //   DiscreteIntegrator: '<S15>/Discrete-Time Integrator'

  QS_InnerRateLoop_DWork.UnitDelay_DSTATE_da =
    QS_InnerRateLoop_DWork.DiscreteTimeIntegrator_DSTAT_o3;

  // Update for UnitDelay: '<S16>/Unit Delay' incorporates:
  //   DiscreteIntegrator: '<S16>/Discrete-Time Integrator'

  QS_InnerRateLoop_DWork.UnitDelay_DSTATE_ag =
    QS_InnerRateLoop_DWork.DiscreteTimeIntegrator_DSTATE_e;

  // Update for DiscreteIntegrator: '<S16>/Discrete-Time Integrator' incorporates:
  //   Gain: '<S16>/Gain'
  //   Inport: '<Root>/engage'

  QS_InnerRateLoop_DWork.DiscreteTimeIntegrator_IC_LOA_j = 0U;
  QS_InnerRateLoop_DWork.DiscreteTimeIntegrator_DSTATE_e += 0.5F *
    rtb_Saturation_h * 0.0025F;
  QS_InnerRateLoop_DWork.DiscreteTimeIntegrator_PrevRe_l = static_cast<int8_T>
    (QS_InnerRateLoop_U.engage);

  // Update for DiscreteIntegrator: '<S17>/Discrete-Time Integrator' incorporates:
  //   Gain: '<S17>/Gain'
  //   Inport: '<Root>/engage'
  //   Sum: '<S17>/Sum'
  //   UnitDelay: '<S17>/Unit Delay'

  QS_InnerRateLoop_DWork.DiscreteTimeIntegrator_DSTAT_cg += (rtb_DeadZone3 -
    QS_InnerRateLoop_DWork.UnitDelay_DSTATE_o1) * 0.5F * 0.0025F;
  QS_InnerRateLoop_DWork.DiscreteTimeIntegrator_PrevR_em = static_cast<int8_T>
    (QS_InnerRateLoop_U.engage);

  // Update for DiscreteIntegrator: '<S15>/Discrete-Time Integrator' incorporates:
  //   Gain: '<S15>/Gain'
  //   Inport: '<Root>/engage'

  QS_InnerRateLoop_DWork.DiscreteTimeIntegrator_IC_LOA_m = 0U;
  QS_InnerRateLoop_DWork.DiscreteTimeIntegrator_DSTAT_o3 += 0.5F *
    rtb_Saturation1_p * 0.0025F;
  QS_InnerRateLoop_DWork.DiscreteTimeIntegrator_PrevR_hn = static_cast<int8_T>
    (QS_InnerRateLoop_U.engage);

  // Update for UnitDelay: '<S13>/Unit Delay1' incorporates:
  //   DiscreteIntegrator: '<S13>/Discrete-Time Integrator1'

  QS_InnerRateLoop_DWork.UnitDelay1_DSTATE_a1 =
    QS_InnerRateLoop_DWork.DiscreteTimeIntegrator1_DSTAT_g;

  // Update for UnitDelay: '<S13>/Unit Delay' incorporates:
  //   DiscreteIntegrator: '<S13>/Discrete-Time Integrator'

  QS_InnerRateLoop_DWork.UnitDelay_DSTATE_ak =
    QS_InnerRateLoop_DWork.DiscreteTimeIntegrator_DSTAT_gh;

  // Update for DiscreteIntegrator: '<S13>/Discrete-Time Integrator1' incorporates:
  //   DiscreteIntegrator: '<S13>/Discrete-Time Integrator'
  //   Inport: '<Root>/engage'

  QS_InnerRateLoop_DWork.DiscreteTimeIntegrator1_IC_LO_e = 0U;
  QS_InnerRateLoop_DWork.DiscreteTimeIntegrator1_DSTAT_g += 0.0025F *
    QS_InnerRateLoop_DWork.DiscreteTimeIntegrator_DSTAT_gh;
  QS_InnerRateLoop_DWork.DiscreteTimeIntegrator1_Prev_gs = static_cast<int8_T>
    (QS_InnerRateLoop_U.engage);

  // Update for DiscreteIntegrator: '<S14>/Discrete-Time Integrator' incorporates:
  //   Gain: '<S14>/Gain'
  //   Inport: '<Root>/engage'

  QS_InnerRateLoop_DWork.DiscreteTimeIntegrator_DSTAT_nv += static_cast<real32_T>
    ((0.5 * rtb_Sum * 0.0025));
  QS_InnerRateLoop_DWork.DiscreteTimeIntegrator_PrevR_pr = static_cast<int8_T>
    (QS_InnerRateLoop_U.engage);

  // Update for UnitDelay: '<S17>/Unit Delay'
  QS_InnerRateLoop_DWork.UnitDelay_DSTATE_o1 = rtb_Saturation2_h;

  // Update for DiscreteIntegrator: '<S13>/Discrete-Time Integrator' incorporates:
  //   Gain: '<S13>/Gain'
  //   Inport: '<Root>/engage'

  QS_InnerRateLoop_DWork.DiscreteTimeIntegrator_DSTAT_gh += 2.828F * rtb_Gain2 *
    0.0025F;
  QS_InnerRateLoop_DWork.DiscreteTimeIntegrator_PrevR_lm = static_cast<int8_T>
    (QS_InnerRateLoop_U.engage);

  // Update for DiscreteIntegrator: '<S27>/Discrete-Time Integrator' incorporates:
  //   Inport: '<Root>/engage'
  //   Lookup_n-D: '<S31>/1-D Lookup Table2'
  //   Product: '<S31>/Product'

  QS_InnerRateLoop_DWork.DiscreteTimeIntegrator_DSTAT_dn += intrp1d_fu32fl_pw
    (bpIdx, rtb_Saturation5_k,
     QS_InnerRateLoop_ConstP.uDLookupTable2_tableData_l) * rtb_Add6_a * 0.0025F;
  QS_InnerRateLoop_DWork.DiscreteTimeIntegrator_PrevRe_f = static_cast<int8_T>
    (QS_InnerRateLoop_U.engage);

  // Update for DiscreteIntegrator: '<S43>/Discrete-Time Integrator' incorporates:
  //   Inport: '<Root>/engage'

  QS_InnerRateLoop_DWork.DiscreteTimeIntegrator_DSTAT_nq += 0.0025F *
    rtb_Add5_ky;
  QS_InnerRateLoop_DWork.DiscreteTimeIntegrator_PrevR_f0 = static_cast<int8_T>
    (QS_InnerRateLoop_U.engage);

  // Update for UnitDelay: '<S95>/Unit Delay' incorporates:
  //   DiscreteIntegrator: '<S95>/Discrete-Time Integrator'

  QS_InnerRateLoop_DWork.UnitDelay_DSTATE_k =
    QS_InnerRateLoop_DWork.DiscreteTimeIntegrator_DSTAT_gy;

  // Update for DiscreteIntegrator: '<S95>/Discrete-Time Integrator' incorporates:
  //   Gain: '<S95>/Gain'
  //   Inport: '<Root>/engage'

  QS_InnerRateLoop_DWork.DiscreteTimeIntegrator_DSTAT_gy += 10.0F *
    rtb_Product_ee * 0.0025F;
  QS_InnerRateLoop_DWork.DiscreteTimeIntegrator_PrevR_bv = static_cast<int8_T>
    (QS_InnerRateLoop_U.engage);
}

// Model initialize function
void untitledModelClass::initialize()
{
  // Registration code

  // initialize error status
  rtmSetErrorStatus((&QS_InnerRateLoop_M), (NULL));

  // block I/O
  (void) memset(((void *) &QS_InnerRateLoop_B), 0,
                sizeof(BlockIO_QS_InnerRateLoop_T));

  // states (dwork)
  (void) memset((void *)&QS_InnerRateLoop_DWork, 0,
                sizeof(D_Work_QS_InnerRateLoop_T));

  // external inputs
  (void)memset(&QS_InnerRateLoop_U, 0, sizeof(ExternalInputs_QS_InnerRateLo_T));

  // external outputs
  (void) memset((void *)&QS_InnerRateLoop_Y, 0,
                sizeof(ExternalOutputs_QS_InnerRateL_T));

  // InitializeConditions for DiscreteIntegrator: '<S89>/Discrete-Time Integrator' 
  QS_InnerRateLoop_DWork.DiscreteTimeIntegrator_PrevRese = 2;

  // InitializeConditions for DiscreteIntegrator: '<S64>/Discrete-Time Integrator' 
  QS_InnerRateLoop_DWork.DiscreteTimeIntegrator_IC_LOADI = 1U;
  QS_InnerRateLoop_DWork.DiscreteTimeIntegrator_PrevRe_a = 2;

  // InitializeConditions for DiscreteIntegrator: '<S86>/Discrete-Time Integrator' 
  QS_InnerRateLoop_DWork.DiscreteTimeIntegrator_PrevRe_o = 2;

  // InitializeConditions for DiscreteIntegrator: '<S64>/Discrete-Time Integrator1' 
  QS_InnerRateLoop_DWork.DiscreteTimeIntegrator1_IC_LOAD = 1U;
  QS_InnerRateLoop_DWork.DiscreteTimeIntegrator1_PrevRes = 2;

  // InitializeConditions for DiscreteIntegrator: '<S83>/Discrete-Time Integrator' 
  QS_InnerRateLoop_DWork.DiscreteTimeIntegrator_PrevRe_b = 2;

  // InitializeConditions for DiscreteIntegrator: '<S64>/Discrete-Time Integrator2' 
  QS_InnerRateLoop_DWork.DiscreteTimeIntegrator2_IC_LOAD = 1U;
  QS_InnerRateLoop_DWork.DiscreteTimeIntegrator2_PrevRes = 2;

  // InitializeConditions for DiscreteIntegrator: '<S27>/Discrete-Time Integrator1' 
  QS_InnerRateLoop_DWork.DiscreteTimeIntegrator1_PrevR_g = 2;

  // InitializeConditions for DiscreteIntegrator: '<S43>/Discrete-Time Integrator1' 
  QS_InnerRateLoop_DWork.DiscreteTimeIntegrator1_PrevR_j = 2;

  // InitializeConditions for RateLimiter: '<S11>/Rate Limiter'
  QS_InnerRateLoop_DWork.PrevY = 0.0F;

  // InitializeConditions for Delay: '<S12>/Delay'
  QS_InnerRateLoop_DWork.icLoad = 1U;

  // InitializeConditions for DiscreteIntegrator: '<S12>/Discrete-Time Integrator' 
  QS_InnerRateLoop_DWork.DiscreteTimeIntegrator_IC_LOA_b = 1U;
  QS_InnerRateLoop_DWork.DiscreteTimeIntegrator_PrevRe_p = 2;

  // InitializeConditions for DiscreteIntegrator: '<S54>/Discrete-Time Integrator' 
  QS_InnerRateLoop_DWork.DiscreteTimeIntegrator_PrevR_bp = 2;

  // InitializeConditions for DiscreteIntegrator: '<S35>/Discrete-Time Integrator' 
  QS_InnerRateLoop_DWork.DiscreteTimeIntegrator_PrevRe_m = 2;

  // InitializeConditions for DiscreteIntegrator: '<S34>/Discrete-Time Integrator' 
  QS_InnerRateLoop_DWork.DiscreteTimeIntegrator_PrevRe_n = 2;

  // InitializeConditions for DiscreteIntegrator: '<S36>/Discrete-Time Integrator' 
  QS_InnerRateLoop_DWork.DiscreteTimeIntegrator_PrevR_by = 2;

  // InitializeConditions for DiscreteIntegrator: '<S28>/Discrete-Time Integrator' 
  QS_InnerRateLoop_DWork.DiscreteTimeIntegrator_PrevRe_e = 2;

  // InitializeConditions for DiscreteIntegrator: '<S44>/Discrete-Time Integrator' 
  QS_InnerRateLoop_DWork.DiscreteTimeIntegrator_PrevRe_d = 2;

  // InitializeConditions for DiscreteIntegrator: '<S55>/Discrete-Time Integrator' 
  QS_InnerRateLoop_DWork.DiscreteTimeIntegrator_PrevRe_j = 2;

  // InitializeConditions for DiscreteIntegrator: '<S79>/Discrete-Time Integrator' 
  QS_InnerRateLoop_DWork.DiscreteTimeIntegrator_PrevRe_h = 2;

  // InitializeConditions for DiscreteIntegrator: '<S75>/Discrete-Time Integrator' 
  QS_InnerRateLoop_DWork.DiscreteTimeIntegrator_PrevR_dc = 2;

  // InitializeConditions for DiscreteIntegrator: '<S16>/Discrete-Time Integrator' 
  QS_InnerRateLoop_DWork.DiscreteTimeIntegrator_IC_LOA_j = 1U;
  QS_InnerRateLoop_DWork.DiscreteTimeIntegrator_PrevRe_l = 2;

  // InitializeConditions for DiscreteIntegrator: '<S17>/Discrete-Time Integrator' 
  QS_InnerRateLoop_DWork.DiscreteTimeIntegrator_PrevR_em = 2;

  // InitializeConditions for DiscreteIntegrator: '<S15>/Discrete-Time Integrator' 
  QS_InnerRateLoop_DWork.DiscreteTimeIntegrator_IC_LOA_m = 1U;
  QS_InnerRateLoop_DWork.DiscreteTimeIntegrator_PrevR_hn = 2;

  // InitializeConditions for DiscreteIntegrator: '<S13>/Discrete-Time Integrator1' 
  QS_InnerRateLoop_DWork.DiscreteTimeIntegrator1_IC_LO_e = 1U;
  QS_InnerRateLoop_DWork.DiscreteTimeIntegrator1_Prev_gs = 2;

  // InitializeConditions for DiscreteIntegrator: '<S14>/Discrete-Time Integrator' 
  QS_InnerRateLoop_DWork.DiscreteTimeIntegrator_PrevR_pr = 2;

  // InitializeConditions for DiscreteIntegrator: '<S13>/Discrete-Time Integrator' 
  QS_InnerRateLoop_DWork.DiscreteTimeIntegrator_PrevR_lm = 2;

  // InitializeConditions for DiscreteIntegrator: '<S27>/Discrete-Time Integrator' 
  QS_InnerRateLoop_DWork.DiscreteTimeIntegrator_PrevRe_f = 2;

  // InitializeConditions for DiscreteIntegrator: '<S43>/Discrete-Time Integrator' 
  QS_InnerRateLoop_DWork.DiscreteTimeIntegrator_PrevR_f0 = 2;

  // InitializeConditions for DiscreteIntegrator: '<S95>/Discrete-Time Integrator' 
  QS_InnerRateLoop_DWork.DiscreteTimeIntegrator_PrevR_bv = 2;
}

// Constructor
untitledModelClass::untitledModelClass()
{
  // Currently there is no constructor body generated.
}

// Destructor
untitledModelClass::~untitledModelClass()
{
  // Currently there is no destructor body generated.
}

// Real-Time Model get method
RT_MODEL_QS_InnerRateLoop_T * untitledModelClass::getRTM()
{
  return (&QS_InnerRateLoop_M);
}

//
// File trailer for generated code.
//
// [EOF]
//
