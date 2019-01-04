///////////////////////////////////////////////////////////////////////////////
// gxsfunc.cpp: Link dependency to all worksheet functions
//
// Copyright (c) 1997-2012 Rogue Wave Software, Inc.  All Rights Reserved.
//
// This computer software is owned by Rogue Wave Software, Inc. and is protected by
// U.S. copyright laws and other laws and by international treaties. This
// computer software is furnished by Rogue Wave Software, Inc. pursuant to a written
// license agreement and may be used, copied, transmitted, and stored
// only in accordance with the terms of such license agreement and with
// the inclusion of the above copyright notice.  This computer software or
// any other copies thereof may not be provided or otherwise made available
// to any other person.
//
// U.S. Government Restricted Rights.  This computer software:
//      (a) was developed at private expense and is in all respects the
//          proprietary information of Rogue Wave Software, Inc.;
//      (b) was not developed with government funds;
//      (c) is a trade secret of Rogue Wave Software, Inc. for all purposes of the
//          Freedom of Information Act; and
//      (d) is a commercial item and thus, pursuant to Section 12.212
//          of the Federal Acquisition Regulations (FAR) and DFAR
//          Supplement Section 227.7202, Government’s use, duplication or
//          disclosure of the computer software is subject to the restrictions
//          set forth by Rogue Wave Software, Inc.
//
///////////////////////////////////////////////////////////////////////////////
//
// Author: Stefan Hoenig
//
// Portions Copyright (C) 1995-1998 X Engineering Software Systems Corp
//

/*
 * NOTE: Functions are passed an argument list, the first element of which
 *       contains a count of the number of actual arguments to the function.
 *       Each argument is of type GX_NUMBER, GX_CELL, GX_RANGE, or GX_STRING.  Functions
 *       which return a string should store it in the buffer pointed to by
 *       _gx_get_expr_sbuf(), which is guaranteed to be a safe place of length
 *       GX_MAX_TEXT.
 *
 *       The elements of the argument list should not be altered unless you
 *       are sure you know what you are doing.  The functions all use
 *       _gx_eval_error() to handle errors, which causes a "long jump" back
 *       to the beginning of evaluate().  This means that you must not call
 *       these functions from outside of evaluate()!  (They can call each
 *       other, of course, as long as evaluate() is somewhere down on the
 *       stack frame.)  You also don't need to worry about floating point
 *       errors (overflows, underflows, etc.) within the functions
 *       since evaluate() sets up a trap for that, too.
 */

#define _OG_EXPORT_IMPL
#define _RW_IMPL

#include "stdafx.h"
#include "grid\gxsinc.h"


#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#define new DEBUG_NEW
#endif

///////////////////////////////////////////////////////////////////////
// call GXGetEngineState()->SetDefaultWorksheetFunctions() from
// your InitInstance method to enable all worksheet functions

void GX_ENGINE_STATE::SetDefaultWorksheetFunctions()
{
	SetWorksheetFunctionClass(new CGXDefaultWorksheetFunctions);
}

void __cdecl GXEnableWorksheetFunctions()
{
	GXGetEngineState()->SetWorksheetFunctionClass(new CGXDefaultWorksheetFunctions);
}

///////////////////////////////////////////////////////////////////////
// class CGXDefaultWorksheetFunctions

CGXDefaultWorksheetFunctions::CGXDefaultWorksheetFunctions()
{
}

gxKeyword* CGXDefaultWorksheetFunctions::LookupFunction(LPCTSTR text)
{
	// Override this methode in your derived class and 
	// return Lookup(text, fn_table, sizeof(fn_table)); 
	// (see CGXAllWorksheetFunctions::Lookup as an example)

	return Lookup(text, fn_table, fn_table_size); 
}

gxKeyword* CGXDefaultWorksheetFunctions::Get_fn_table()
{
	return fn_table;
}

///////////////////////////////////////////////////////////////////////
// Reference (and link dependency) to all worksheet functions


/*
  The following are not in <math.h> for some reason!
*/
extern double __cdecl acosh(), asinh(), atanh();

static int fn_fn_cmp(const gxKeyword * fn_1, const gxKeyword * fn_2);

static int fn_text_cmp(LPCTSTR text, const gxKeyword * fn);


/*------------------------------- XS Functions -------------------------------*/

#define A gxOperand argv[]
#define C __cdecl

/*
  Math functions (math_fns.c)
*/

gxOperand 
		  C _gx_fn_abs(A), C _gx_fn_acos(A), C _gx_fn_asin(A), C _gx_fn_atan(A), C _gx_fn_atan2(A), C _gx_fn_cos(A),
		  C _gx_fn_degrees(A), C _gx_fn_exp(A), C _gx_fn_int(A), C _gx_fn_ln(A), C _gx_fn_log(A), C _gx_fn_mod(A),
		  C _gx_fn_pi(A), C _gx_fn_radians(A), C _gx_fn_rand(A), C _gx_fn_round(A), C _gx_fn_sin(A), C _gx_fn_sqrt(A),
		  C _gx_fn_tan(A), C _gx_fn_frac(A), C _gx_fn_ceil(A), C _gx_fn_floor(A), C _gx_fn_veclen(A), C _gx_fn_grand(A),
		  C _gx_fn_cosh(A), C _gx_fn_sinh(A), C _gx_fn_tanh(A), C _gx_fn_acosh(A), C _gx_fn_asinh(A), C _gx_fn_atanh(A),
		  C _gx_fn_dot(A), C _gx_fn_poly(A), C _gx_fn_sigmoid(A), C _gx_fn_log2(A), C _gx_fn_gamma(A), C _gx_fn_lngamma(A),
		  C _gx_fn_modulus(A), C _gx_fn_fact(A);

/*
  Statistical functions (stat_fns.c)
*/
gxOperand 
          C _gx_fn_vsum(A), C _gx_fn_sum(A), C _gx_fn_avg(A), C _gx_fn_min(A), C _gx_fn_max(A), C _gx_fn_var(A), C _gx_fn_std(A),
		  C _gx_fn_vars(A), C _gx_fn_stds(A), C _gx_fn_count(A),
		  C _gx_fn_t(A), C _gx_fn_f(A), C _gx_fn_ttest(A), C _gx_fn_pttest(A), C _gx_fn_ttest2ev(A),
		  C _gx_fn_ttest2uv(A), C _gx_fn_ftest(A),
		  C _gx_fn_sse(A), C _gx_fn_ssq(A), C _gx_fn_gmean(A), C _gx_fn_hmean(A), C _gx_fn_msq(A),
		  C _gx_fn_rms(A), C _gx_fn_corr(A),
		  C _gx_fn_normsdist(A), C _gx_fn_normdist(A), C _gx_fn_normsinv(A), C _gx_fn_norminv(A),
		  C _gx_fn_ztest(A), C _gx_fn_standardize(A), C _gx_fn_confidence(A);

/*
  Statistical functions developed by Rose (stat_fns2.c)
*/
gxOperand 
          C _gx_fn_frequency(A), C _gx_fn_large(A), C _gx_fn_small(A), C _gx_fn_percentile(A),
		  C _gx_fn_quartile(A), C _gx_fn_mode(A), C _gx_fn_rank(A), C _gx_fn_permut(A), C _gx_fn_median(A),
		  C _gx_fn_percentrank(A), C _gx_fn_forecast(A), C _gx_fn_trend(A), C _gx_fn_erf(A), C _gx_fn_erfc(A);

/*
  Conditional statistical functions (cstat_fns.c)
*/
gxOperand 
          C _gx_fn_csum(A), C _gx_fn_cavg(A), C _gx_fn_cmin(A), C _gx_fn_cmax(A), C _gx_fn_cvar(A), C _gx_fn_cstd(A),
		  C _gx_fn_cvars(A), C _gx_fn_cstds(A), C _gx_fn_ccount(A);

/*
  String functions (string_fns.c)
*/
gxOperand 
          C _gx_fn_char(A), C _gx_fn_clean(A), C _gx_fn_code(A), C _gx_fn_exact(A), C _gx_fn_find(A),
		  C _gx_fn_hextonum(A), C _gx_fn_numtohex(A), C _gx_fn_left(A), C _gx_fn_right(A), C _gx_fn_mid(A),
		  C _gx_fn_length(A), C _gx_fn_lower(A), C _gx_fn_upper(A), C _gx_fn_proper(A), C _gx_fn_repeat(A),
		  C _gx_fn_replace(A), C _gx_fn_trim(A), C _gx_fn_value(A), C _gx_fn_string(A), C _gx_fn_s(A), C _gx_fn_n(A),
		  C _gx_fn_strlen(A), C _gx_fn_strcat(A), C _gx_fn_format(A),
		  C _gx_fn_tsv(A);

/*
  Logical functions (logical_fns.c)
*/
gxOperand 
          C _gx_fn_true(A), C _gx_fn_false(A), C _gx_fn_if(A), C _gx_fn_isnumber(A), C _gx_fn_isstring(A),
		  C _gx_fn_fileexists(A), C _gx_fn_iserror(A);

/*
  Miscellaneous functions (misc_fns.c)
*/
gxOperand 
          C _gx_fn_indirect(A), C _gx_fn_row(A), C _gx_fn_col(A), C _gx_fn_cellref(A), C _gx_fn_rangeref(A),
		  C _gx_fn_choose(A), C _gx_fn_date(A), C _gx_fn_datevalue(A), C _gx_fn_time(A), C _gx_fn_timevalue(A),
		  C _gx_fn_hour(A), C _gx_fn_minute(A), C _gx_fn_second(A), C _gx_fn_year(A), C _gx_fn_month(A), C _gx_fn_day(A),
		  C _gx_fn_now(A), C _gx_fn_today(A), C _gx_fn_hlookup(A), C _gx_fn_vlookup(A), C _gx_fn_alarm(A),
		  C _gx_fn_salarm(A), C _gx_fn_message(A), C _gx_fn_init(A), C _gx_fn_regex(A), C _gx_fn_annotate(A),
		  C _gx_fn_rows(A), C _gx_fn_cols(A), C _gx_fn_xvalue(A);

/*
  Miscellaneous functions developed by Rose (misc_fns2.c)
*/
gxOperand 
          C _gx_fn_days360(A), C _gx_fn_edate(A), C _gx_fn_eomonth(A), C _gx_fn_weekday(A), C _gx_fn_match(A),
		  C _gx_fn_yearfrac(A), C _gx_fn_networkdays(A), C _gx_fn_workday(A), C _gx_fn_product(A),
		  C _gx_fn_interp2d(A), C _gx_fn_interp3d(A);

/*
  Digital logic functions (logic_fns.c)
*/
gxOperand 
          C _gx_fn_and(A), C _gx_fn_or(A), C _gx_fn_nand(A), C _gx_fn_nor(A), C _gx_fn_xor(A), C _gx_fn_not(A);

/*
  Embedded matrix functions (matrix_fns.c)
*/
gxOperand 
          C _gx_fn_mmul(A), C _gx_fn_invert(A), C _gx_fn_det(A), C _gx_fn_transpose(A), C _gx_fn_lls(A), C _gx_fn_fft(A),
		  C _gx_fn_invfft(A), C _gx_fn_dft(A), C _gx_fn_invdft(A), C _gx_fn_eigen(A), C _gx_fn_polyfit(A),
		  C _gx_fn_linfit(A), C _gx_fn_pls(A), C _gx_fn_lincoef(A), C _gx_fn_polycoef(A);

/*
  Financial functions (finance_fns.c)
*/
gxOperand 
          C _gx_fn_cterm(A), C _gx_fn_ddb(A), C _gx_fn_fv(A), C _gx_fn_irr(A), C _gx_fn_npv(A), C _gx_fn_pmt(A),
		  C _gx_fn_pv(A), C _gx_fn_rate(A), C _gx_fn_sln(A), C _gx_fn_syd(A), C _gx_fn_term(A);

/*
  Financial functions added by Rose (finance_fns2.c)
*/
gxOperand 
          C _gx_fn_coupdaybs(A), C _gx_fn_coupdays(A), C _gx_fn_coupdaysnc(A), C _gx_fn_coupncd(A),
		  C _gx_fn_couppcd(A), C _gx_fn_coupnum(A), C _gx_fn_accrint(A), C _gx_fn_accrintm(A),
		  C _gx_fn_cumipmt(A), C _gx_fn_cumprinc(A), C _gx_fn_db(A), C _gx_fn_vdb(A), C _gx_fn_disc(A),
		  C _gx_fn_dollarde(A), C _gx_fn_dollarfr(A), C _gx_fn_duration(A), C _gx_fn_mduration(A),
		  C _gx_fn_mirr(A), C _gx_fn_fvschedule(A), C _gx_fn_effect(A), C _gx_fn_nominal(A),
		  C _gx_fn_oddfprice(A), C _gx_fn_ppmt(A), C _gx_fn_ipmt(A), C _gx_fn_intrate(A),
		  C _gx_fn_oddfyield(A), C _gx_fn_oddlprice(A),
		  C _gx_fn_oddlyield(A), C _gx_fn_price(A), C _gx_fn_pricedisc(A), C _gx_fn_pricemat(A),
		  C _gx_fn_received(A), C _gx_fn_tbilleq(A), C _gx_fn_tbillprice(A), C _gx_fn_tbillyield(A),
		  C _gx_fn_xnpv(A), C _gx_fn_xirr(A), C _gx_fn_yield(A), C _gx_fn_yielddisc(A),
		  C _gx_fn_yieldmat(A);

/*
  Excel compatibility functions
*/
gxOperand 
          C _gx_fn_intersect(A), C _gx_fn_na(A), C _gx_fn_index(A), C _gx_fn_cellinfo(A);

#undef A
#undef C

/*
		The function table equates the function name to the function
		entry point.  Functions may be known by more than one name
		(e.g., _gx_fn_dot is invoked by @DOT() as well as @SUMPRODUCT()).
		The function table must be lexigraphically sorted.
		(Hint: the vi command "!}sort" will sort the table automatically!)
*/

#ifdef STRICT
#undef STRICT
#endif
#define STRICT GX_STRICT

#ifdef OPTIONAL
#undef OPTIONAL
#endif
#define OPTIONAL GX_OPTIONAL


gxKeyword CGXDefaultWorksheetFunctions::fn_table[] =
{
	{_T("@"), _gx_fn_indirect, 0, 0, GX_TC_RANGE, 1,
		{{GX_TC_STRING, STRICT, GX_REQUIRED}
	}, -1},
	{_T("ABS"), _gx_fn_abs, 0, 0, GX_TC_NUMBER, 1,
		{{GX_TC_NUMERIC, STRICT, GX_REQUIRED}
	}, gxxlfAbs},
	{_T("ACCRINT"), _gx_fn_accrint, 0, 0, GX_TC_NUMBER, 7,
		{{GX_TC_NUMERIC, STRICT, GX_REQUIRED},
		{GX_TC_NUMERIC, STRICT, GX_REQUIRED},
		{GX_TC_NUMERIC, STRICT, GX_REQUIRED},
		{GX_TC_NUMERIC, STRICT, GX_REQUIRED},
		{GX_TC_NUMERIC, STRICT, GX_REQUIRED},
		{GX_TC_NUMERIC, STRICT, GX_REQUIRED},
		{GX_TC_NUMERIC, STRICT, OPTIONAL}
	}, -1},
	{_T("ACCRINTM"), _gx_fn_accrintm, 0, 0, GX_TC_NUMBER, 5,
		{{GX_TC_NUMERIC, STRICT, GX_REQUIRED},
		{GX_TC_NUMERIC, STRICT, GX_REQUIRED},
		{GX_TC_NUMERIC, STRICT, GX_REQUIRED},
		{GX_TC_NUMERIC, STRICT, GX_REQUIRED},
		{GX_TC_NUMERIC, STRICT, OPTIONAL}
	}, -1},
	{_T("ACOS"), _gx_fn_acos, 0, 0, GX_TC_NUMBER, 1,
		{{GX_TC_NUMERIC, STRICT, GX_REQUIRED}
	}, gxxlfAcos},
	{_T("AND"), _gx_fn_and, 0, 0, GX_TC_NUMBER, 1,
		{{GX_TC_NUM_RNG, STRICT, GX_VARIABLE}
	}, gxxlfAnd},
	{_T("ASIN"), _gx_fn_asin, 0, 0, GX_TC_NUMBER, 1,
		{{GX_TC_NUMERIC, STRICT, GX_REQUIRED}
	}, gxxlfAsin},
	{_T("ATAN"), _gx_fn_atan, 0, 0, GX_TC_NUMBER, 1,
		{{GX_TC_NUMERIC, STRICT, GX_REQUIRED}
	}, gxxlfAtan},
	{_T("ATAN2"), _gx_fn_atan2, 0, 0, GX_TC_NUMBER, 2,
		{{GX_TC_NUMERIC, STRICT, GX_REQUIRED},
		{GX_TC_NUMERIC, STRICT, GX_REQUIRED}
	}, gxxlfAtan2},
	{_T("AVG"), _gx_fn_avg, 0, 0, GX_TC_NUMBER, 1,
		{{GX_TC_NUM_RNG, STRICT, GX_VARIABLE}
	}, gxxlfAverage},
	{_T("CAVG"), _gx_fn_cavg, 0, 0, GX_TC_NUMBER, 2,
		{{GX_TC_RANGE, STRICT, GX_VARIABLE},
		{GX_TC_NUMERIC, GX_NONSTRICT, GX_REQUIRED}
	}, -1},
	{_T("CCOUNT"), _gx_fn_ccount, 0, 0, GX_TC_NUMBER, 2,
		{{GX_TC_RANGE, STRICT, GX_VARIABLE},
		{GX_TC_NUMERIC, GX_NONSTRICT, GX_REQUIRED}
	}, -1},
	{_T("CEIL"), _gx_fn_ceil, 0, 0, GX_TC_NUMBER, 1,
		{{GX_TC_NUMERIC, STRICT, GX_REQUIRED}
	}, gxxlfCeiling},
	{_T("CELLINFO"), _gx_fn_cellinfo, 0, 0, GX_TC_POLY, 2,
		{{GX_TC_STRING, STRICT, GX_REQUIRED},
		{GX_TC_RANGE, STRICT, GX_REQUIRED}
	}, -1},
	{_T("CELLREF"), _gx_fn_cellref, 0, 0, GX_TC_CELL, 2,
		{{GX_TC_NUMERIC, STRICT, GX_REQUIRED},
		{GX_TC_NUMERIC, STRICT, GX_REQUIRED}
	}, gxxlfCell},
	{_T("CHAR"), _gx_fn_char, 0, 0, GX_TC_STRING, 1,
		{{GX_TC_NUMERIC, STRICT, GX_REQUIRED}
	}},
	{_T("CHOOSE"), _gx_fn_choose, 0, 0, GX_TC_POLY, 2,
		{{GX_TC_NUMERIC, STRICT, GX_REQUIRED},
		{GX_TC_POLY, GX_NONSTRICT, GX_VARIABLE}
	}, gxxlfChoose},
	{_T("CLEAN"), _gx_fn_clean, 0, 0, GX_TC_STRING, 1,
		{{GX_TC_STR_CL, STRICT, GX_REQUIRED}
	}, gxxlfClean},
	{_T("CMAX"), _gx_fn_cmax, 0, 0, GX_TC_NUMBER, 2,
		{{GX_TC_RANGE, STRICT, GX_VARIABLE},
		{GX_TC_NUMERIC, GX_NONSTRICT, GX_REQUIRED}
	}, -1},
	{_T("CMIN"), _gx_fn_cmin, 0, 0, GX_TC_NUMBER, 2,
		{{GX_TC_RANGE, STRICT, GX_VARIABLE},
		{GX_TC_NUMERIC, GX_NONSTRICT, GX_REQUIRED}
	}, -1},
	{_T("CODE"), _gx_fn_code, 0, 0, GX_TC_NUMBER, 1,
		{{GX_TC_STR_CL, STRICT, GX_REQUIRED}
	}, gxxlfCode},
	{_T("COL"), _gx_fn_col, 0, 0, GX_TC_NUMBER, 1,
		{{GX_TC_RANGE, STRICT, OPTIONAL}
	}, gxxlfColumn},
	{_T("COLS"), _gx_fn_cols, 0, 0, GX_TC_NUMBER, 1,
		{{GX_TC_RANGE, STRICT, OPTIONAL}
	}, gxxlfColumns},	  
	{_T("CONFIDENCE"), _gx_fn_confidence, 0, 0, GX_TC_NUMBER, 3,
		{{GX_TC_NUMERIC, STRICT, GX_REQUIRED},
		{GX_TC_NUMERIC, STRICT, GX_REQUIRED},
		{GX_TC_NUMERIC, STRICT, GX_REQUIRED}
	}, gxxlfConfidence},
	{_T("CORR"), _gx_fn_corr, 0, 0, GX_TC_NUMBER, 2,
		{{GX_TC_RANGE, STRICT, GX_REQUIRED},
		{GX_TC_RANGE, STRICT, GX_REQUIRED}
	}, gxxlfCorrel},
	{_T("COS"), _gx_fn_cos, 0, 0, GX_TC_NUMBER, 1,
		{{GX_TC_NUMERIC, STRICT, GX_REQUIRED}
	}, gxxlfCos},
	{_T("COSH"), _gx_fn_cosh, 0, 0, GX_TC_NUMBER, 1,
		{{GX_TC_NUMERIC, STRICT, GX_REQUIRED}
	}, gxxlfCosh},
	{_T("COUNT"), _gx_fn_count, 0, 0, GX_TC_NUMBER, 1,
		{{GX_TC_POLY, STRICT, GX_VARIABLE}
	}, gxxlfCount},
	{_T("COUPDAYBS"), _gx_fn_coupdaybs, 0, 0, GX_TC_NUMBER, 4,
		{{GX_TC_NUMERIC, STRICT, GX_REQUIRED},
		{GX_TC_NUMERIC, STRICT, GX_REQUIRED},
		{GX_TC_NUMERIC, STRICT, GX_REQUIRED},
		{GX_TC_NUMERIC, STRICT, OPTIONAL}
	}, -1},
	{_T("COUPDAYS"), _gx_fn_coupdays, 0, 0, GX_TC_NUMBER, 4,
		{{GX_TC_NUMERIC, STRICT, GX_REQUIRED},
		{GX_TC_NUMERIC, STRICT, GX_REQUIRED},
		{GX_TC_NUMERIC, STRICT, GX_REQUIRED},
		{GX_TC_NUMERIC, STRICT, OPTIONAL}
	}, -1},
	{_T("COUPDAYSNC"), _gx_fn_coupdaysnc, 0, 0, GX_TC_NUMBER, 4,
		{{GX_TC_NUMERIC, STRICT, GX_REQUIRED},
		{GX_TC_NUMERIC, STRICT, GX_REQUIRED},
		{GX_TC_NUMERIC, STRICT, GX_REQUIRED},
		{GX_TC_NUMERIC, STRICT, OPTIONAL}
	}, -1},
	{_T("COUPNCD"), _gx_fn_coupncd, 0, 0, GX_TC_NUMBER, 4,
		{{GX_TC_NUMERIC, STRICT, GX_REQUIRED},
		{GX_TC_NUMERIC, STRICT, GX_REQUIRED},
		{GX_TC_NUMERIC, STRICT, GX_REQUIRED},
		{GX_TC_NUMERIC, STRICT, OPTIONAL}
	}, -1},
	{_T("COUPNUM"), _gx_fn_coupnum, 0, 0, GX_TC_NUMBER, 4,
		{{GX_TC_NUMERIC, STRICT, GX_REQUIRED},
		{GX_TC_NUMERIC, STRICT, GX_REQUIRED},
		{GX_TC_NUMERIC, STRICT, GX_REQUIRED},
		{GX_TC_NUMERIC, STRICT, OPTIONAL}
	}, -1},
	{_T("COUPPCD"), _gx_fn_couppcd, 0, 0, GX_TC_NUMBER, 4,
		{{GX_TC_NUMERIC, STRICT, GX_REQUIRED},
		{GX_TC_NUMERIC, STRICT, GX_REQUIRED},
		{GX_TC_NUMERIC, STRICT, GX_REQUIRED},
		{GX_TC_NUMERIC, STRICT, OPTIONAL}
	}, -1},
	{_T("CSTD"), _gx_fn_cstd, 0, 0, GX_TC_NUMBER, 2,
		{{GX_TC_RANGE, STRICT, GX_VARIABLE},
		{GX_TC_NUMERIC, GX_NONSTRICT, GX_REQUIRED}
	}, -1},
	{_T("CSTDS"), _gx_fn_cstds, 0, 0, GX_TC_NUMBER, 2,
		{{GX_TC_RANGE, STRICT, GX_VARIABLE},
		{GX_TC_NUMERIC, GX_NONSTRICT, GX_REQUIRED}
	}, -1},
	{_T("CSUM"), _gx_fn_csum, 0, 0, GX_TC_NUMBER, 2,
		{{GX_TC_RANGE, STRICT, GX_VARIABLE},
		{GX_TC_NUMERIC, GX_NONSTRICT, GX_REQUIRED}
	}, -1},
	{_T("CTERM"), _gx_fn_cterm, 0, 0, GX_TC_NUMBER, 3,
		{{GX_TC_NUMERIC, STRICT, GX_REQUIRED},
		{GX_TC_NUMERIC, STRICT, GX_REQUIRED},
		{GX_TC_NUMERIC, STRICT, GX_REQUIRED}
	}, -1},
	{_T("CUMIPMT"), _gx_fn_cumipmt, 0, 0, GX_TC_NUMBER, 6,
		{{GX_TC_NUMERIC, STRICT, GX_REQUIRED},
		{GX_TC_NUMERIC, STRICT, GX_REQUIRED},
		{GX_TC_NUMERIC, STRICT, GX_REQUIRED},
		{GX_TC_NUMERIC, STRICT, GX_REQUIRED},
		{GX_TC_NUMERIC, STRICT, GX_REQUIRED},
		{GX_TC_NUMERIC, STRICT, GX_REQUIRED}
	}, -1},
	{_T("CUMPRINC"), _gx_fn_cumprinc, 0, 0, GX_TC_NUMBER, 6,
		{{GX_TC_NUMERIC, STRICT, GX_REQUIRED},
		{GX_TC_NUMERIC, STRICT, GX_REQUIRED},
		{GX_TC_NUMERIC, STRICT, GX_REQUIRED},
		{GX_TC_NUMERIC, STRICT, GX_REQUIRED},
		{GX_TC_NUMERIC, STRICT, GX_REQUIRED},
		{GX_TC_NUMERIC, STRICT, GX_REQUIRED}
	}, -1},
	{_T("CVAR"), _gx_fn_cvar, 0, 0, GX_TC_NUMBER, 2,
		{{GX_TC_RANGE, STRICT, GX_VARIABLE},
		{GX_TC_NUMERIC, GX_NONSTRICT, GX_REQUIRED}
	}, -1},
	{_T("CVARS"), _gx_fn_cvars, 0, 0, GX_TC_NUMBER, 2,
		{{GX_TC_RANGE, STRICT, GX_VARIABLE},
		{GX_TC_NUMERIC, GX_NONSTRICT, GX_REQUIRED}
	}, -1},
	{_T("DATE"), _gx_fn_date, 0, 0, GX_TC_NUMBER, 3,
		{{GX_TC_NUMERIC, STRICT, GX_REQUIRED},
		{GX_TC_NUMERIC, STRICT, GX_REQUIRED},
		{GX_TC_NUMERIC, STRICT, GX_REQUIRED}
	}, gxxlfDate},
	{_T("DATEVALUE"), _gx_fn_datevalue, 0, 0, GX_TC_NUMBER, 1,
		{{GX_TC_STR_CL, STRICT, GX_REQUIRED}
	}, gxxlfDatevalue},
	{_T("DAY"), _gx_fn_day, 0, 0, GX_TC_NUMBER, 1,
		{{GX_TC_NUMERIC, STRICT, GX_REQUIRED}
	}, gxxlfDay},
	{_T("DAYS360"), _gx_fn_days360, 0, 0, GX_TC_NUMBER, 2,
		{{GX_TC_STR_CL, STRICT, GX_REQUIRED},
		{GX_TC_STR_CL, STRICT, GX_REQUIRED}
	}, gxxlfDays360},
	{_T("DB"), _gx_fn_db, 0, 0, GX_TC_NUMBER, 5,
		{{GX_TC_NUMERIC, STRICT, GX_REQUIRED},
		{GX_TC_NUMERIC, STRICT, GX_REQUIRED},
		{GX_TC_NUMERIC, STRICT, GX_REQUIRED},
		{GX_TC_NUMERIC, STRICT, GX_REQUIRED},
		{GX_TC_NUMERIC, STRICT, OPTIONAL}
	}, -1},
	{_T("DDB"), _gx_fn_ddb, 0, 0, GX_TC_NUMBER, 4,
		{{GX_TC_NUMERIC, STRICT, GX_REQUIRED},
		{GX_TC_NUMERIC, STRICT, GX_REQUIRED},
		{GX_TC_NUMERIC, STRICT, GX_REQUIRED},
		{GX_TC_NUMERIC, STRICT, GX_REQUIRED}
	}, -1},
	{_T("DEGREES"), _gx_fn_degrees, 0, 0, GX_TC_NUMBER, 1,
		{{GX_TC_NUMERIC, STRICT, GX_REQUIRED}
	}, -1},
	{_T("DET"), _gx_fn_det, 0, 0, GX_TC_NUMBER, 1,
		{{GX_TC_RNG_ONLY, STRICT, GX_REQUIRED}
	}, -1},
	{_T("DFT"), _gx_fn_dft, 0, 0, GX_TC_MATRIX, 1,
		{{GX_TC_RNG_ONLY, STRICT, GX_REQUIRED}
	}, -1},
	{_T("DISC"), _gx_fn_disc, 0, 0, GX_TC_NUMBER, 5,
		{{GX_TC_NUMERIC, STRICT, GX_REQUIRED},
		{GX_TC_NUMERIC, STRICT, GX_REQUIRED},
		{GX_TC_NUMERIC, STRICT, GX_REQUIRED},
		{GX_TC_NUMERIC, STRICT, GX_REQUIRED},
		{GX_TC_NUMERIC, STRICT, OPTIONAL}
	}, -1},
	{_T("DOLLARDE"), _gx_fn_dollarde, 0, 0, GX_TC_NUMBER, 2,
		{{GX_TC_NUMERIC, STRICT, GX_REQUIRED},
		{GX_TC_NUMERIC, STRICT, GX_REQUIRED}
	}, -1},
	{_T("DOLLARFR"), _gx_fn_dollarfr, 0, 0, GX_TC_NUMBER, 2,
		{{GX_TC_NUMERIC, STRICT, GX_REQUIRED},
		{GX_TC_NUMERIC, STRICT, GX_REQUIRED}
	}, -1},
	{_T("DOT"), _gx_fn_dot, 0, 0, GX_TC_NUMBER, 2,
		{{GX_TC_RNG_ONLY, STRICT, GX_REQUIRED},
		{GX_TC_RNG_ONLY, STRICT, GX_REQUIRED}
	}, -1},
	{_T("DURATION"), _gx_fn_duration, 0, 0, GX_TC_NUMBER, 6,
		{{GX_TC_NUMERIC, STRICT, GX_REQUIRED},
		{GX_TC_NUMERIC, STRICT, GX_REQUIRED},
		{GX_TC_NUMERIC, STRICT, GX_REQUIRED},
		{GX_TC_NUMERIC, STRICT, GX_REQUIRED},
		{GX_TC_NUMERIC, STRICT, GX_REQUIRED},
		{GX_TC_NUMERIC, STRICT, OPTIONAL}
	}, -1},
	{_T("EDATE"), _gx_fn_edate, 0, 0, GX_TC_NUMBER, 2,
		{{GX_TC_STR_CL, STRICT, GX_REQUIRED},
		{GX_TC_NUMERIC, STRICT, GX_REQUIRED}
	}, -1},
	{_T("EFFECT"), _gx_fn_effect, 0, 0, GX_TC_NUMBER, 2,
		{{GX_TC_NUMERIC, STRICT, GX_REQUIRED},
		{GX_TC_NUMERIC, STRICT, GX_REQUIRED}
	}, -1},
	{_T("EIGEN"), _gx_fn_eigen, 0, 0, GX_TC_MATRIX, 1,
		{{GX_TC_RNG_ONLY, STRICT, GX_REQUIRED}
	}, -1},
	{_T("EOMONTH"), _gx_fn_eomonth, 0, 0, GX_TC_NUMBER, 2,
		{{GX_TC_STR_CL, STRICT, GX_REQUIRED},
		{GX_TC_NUMERIC, STRICT, GX_REQUIRED}
	}, -1},
	{_T("ERF"), _gx_fn_erf, 0, 0, GX_TC_NUMBER, 2,
		{{GX_TC_NUMERIC, STRICT, GX_REQUIRED},
		{GX_TC_NUMERIC, STRICT, OPTIONAL}
	}, -1},
	{_T("ERFC"), _gx_fn_erfc, 0, 0, GX_TC_NUMBER, 1,
		{{GX_TC_NUMERIC, STRICT, GX_REQUIRED}
	}, -1},
	{_T("EXACT"), _gx_fn_exact, 0, 0, GX_TC_NUMBER, 2,
		{{GX_TC_STR_CL, STRICT, GX_REQUIRED},
		{GX_TC_STR_CL, STRICT, GX_REQUIRED}
	}, gxxlfExact},
	{_T("EXP"), _gx_fn_exp, 0, 0, GX_TC_NUMBER, 1,
		{{GX_TC_NUMERIC, STRICT, GX_REQUIRED}
	}, gxxlfExp},
	{_T("F"), _gx_fn_f, 0, 0, GX_TC_NUMBER, 3,
		{{GX_TC_NUMERIC, STRICT, GX_REQUIRED},
		{GX_TC_NUMERIC, STRICT, GX_REQUIRED},
		{GX_TC_NUMERIC, STRICT, GX_REQUIRED}
	}, -1},
	{_T("FACT"), _gx_fn_fact, 0, 0, GX_TC_NUMBER, 1,
		{{GX_TC_NUMERIC, STRICT, GX_REQUIRED}
	}, gxxlfFact},
	{_T("FALSE"), _gx_fn_false, 0, 0, GX_TC_NUMBER, 0,
	{0,0,0}, gxxlfFalse},
	{_T("FFT"), _gx_fn_fft, 0, 0, GX_TC_MATRIX, 1,
		{{GX_TC_RNG_ONLY, STRICT, GX_REQUIRED}
	}, -1},
	{_T("FILEEXISTS"), _gx_fn_fileexists, 0, 0, GX_TC_NUMBER, 1,
		{{GX_TC_STR_CL, STRICT, GX_REQUIRED}
	}, -1},
	{_T("FIND"), _gx_fn_find, 0, 0, GX_TC_NUMBER, 3,
		{{GX_TC_STR_CL, STRICT, GX_REQUIRED},
		{GX_TC_STR_CL, STRICT, GX_REQUIRED},
		{GX_TC_NUMERIC, STRICT, GX_REQUIRED}
	}, -1},
	{_T("FLOOR"), _gx_fn_floor, 0, 0, GX_TC_NUMBER, 1,
		{{GX_TC_NUMERIC, STRICT, GX_REQUIRED}
	}, gxxlfFloor},
	{_T("FORECAST"), _gx_fn_forecast, 0, 0, GX_TC_MATRIX, 3,
		{{GX_TC_NUMERIC, STRICT, GX_REQUIRED},
		{GX_TC_RNG_ONLY, STRICT, GX_REQUIRED},
		{GX_TC_RNG_ONLY, STRICT, GX_REQUIRED}
	}, -1},
	{_T("FRAC"), _gx_fn_frac, 0, 0, GX_TC_NUMBER, 1,
		{{GX_TC_NUMERIC, STRICT, GX_REQUIRED}
	}, -1},
	{_T("FREQUENCY"), _gx_fn_frequency, 0, 0, GX_TC_MATRIX, 2,
		{{GX_TC_RNG_ONLY, STRICT, GX_REQUIRED},
		{GX_TC_RANGE, STRICT, GX_REQUIRED}
	}, gxxlfFrequency},
	{_T("FTEST"), _gx_fn_ftest, 0, 0, GX_TC_NUMBER, 2,
		{{GX_TC_RNG_ONLY, STRICT, GX_REQUIRED},
		{GX_TC_RNG_ONLY, STRICT, GX_REQUIRED}
	}, -1},
	{_T("FV"), _gx_fn_fv, 0, 0, GX_TC_NUMBER, 3,
		{{GX_TC_NUMERIC, STRICT, GX_REQUIRED},
		{GX_TC_NUMERIC, STRICT, GX_REQUIRED},
		{GX_TC_NUMERIC, STRICT, GX_REQUIRED}
	}, -1},
	{_T("FVSCHEDULE"), _gx_fn_fvschedule, 0, 0, GX_TC_NUMBER, 2,
		{{GX_TC_NUMERIC, STRICT, GX_REQUIRED},
		{GX_TC_RNG_ONLY, STRICT, GX_REQUIRED}
	}, -1},
	{_T("GAMMA"), _gx_fn_gamma, 0, 0, GX_TC_NUMBER, 1,
		{{GX_TC_NUMERIC, STRICT, GX_REQUIRED}
	}, -1},
	{_T("GMEAN"), _gx_fn_gmean, 0, 0, GX_TC_NUMBER, 1,
		{{GX_TC_NUM_RNG, STRICT, GX_VARIABLE}
	}, gxxlfGeomean},
#if _MFC_VER >= 0x0300
	{_T("GRAND"), _gx_fn_grand, 0, 0, GX_TC_NUMBER, 0,
	{0,0,0}, -1},
#endif
	{_T("HEXTONUM"), _gx_fn_hextonum, 0, 0, GX_TC_NUMBER, 1,
		{{GX_TC_STR_CL, STRICT, GX_REQUIRED}
	}, -1},
	{_T("HLOOKUP"), _gx_fn_hlookup, 0, 0, GX_TC_POLY, 3,
		{{GX_TC_POLY, STRICT, GX_REQUIRED},
		{GX_TC_RNG_ONLY, STRICT, GX_REQUIRED},
		{GX_TC_NUMERIC, STRICT, GX_REQUIRED}
	}, gxxlfHlookup},
	{_T("HMEAN"), _gx_fn_hmean, 0, 0, GX_TC_NUMBER, 1,
		{{GX_TC_NUM_RNG, STRICT, GX_VARIABLE}
	}, gxxlfHarmean},
	{_T("HOUR"), _gx_fn_hour, 0, 0, GX_TC_NUMBER, 1,
		{{GX_TC_NUMERIC, STRICT, GX_REQUIRED}
	}, gxxlfHour},
	{_T("IF"), _gx_fn_if, 0, 0, GX_TC_POLY, 3,
		{{GX_TC_NUMERIC, STRICT, GX_REQUIRED},
		{GX_TC_POLY, GX_NONSTRICT, GX_REQUIRED},
		{GX_TC_POLY, GX_NONSTRICT, GX_REQUIRED}
	}, -1},
	{_T("INDEX"), _gx_fn_index, 0, 0, GX_TC_RANGE, 2,
		{{GX_TC_RNG_ONLY, STRICT, GX_REQUIRED},
		{GX_TC_NUMERIC, STRICT, GX_VARIABLE}
	}, gxxlfIndex},
	{_T("INIT"), _gx_fn_init, 0, 0, GX_TC_POLY, 2,
		{{GX_TC_POLY, GX_NONSTRICT, GX_REQUIRED},
		{GX_TC_POLY, GX_NONSTRICT, GX_REQUIRED}
	}, -1},
	{_T("INT"), _gx_fn_int, 0, 0, GX_TC_NUMBER, 1,
		{{GX_TC_NUMERIC, STRICT, GX_REQUIRED}
	}, gxxlfTrunc},
	{_T("INTERP2D"), _gx_fn_interp2d, 0, 0, GX_TC_MATRIX, 3,
		{{GX_TC_RNG_ONLY, STRICT, GX_REQUIRED},
		{GX_TC_RNG_ONLY, STRICT, GX_REQUIRED},
		{GX_TC_RANGE, STRICT, GX_REQUIRED}
	}, -1},
	{_T("INTERP3D"), _gx_fn_interp3d, 0, 0, GX_TC_MATRIX, 3,
		{{GX_TC_RNG_ONLY, STRICT, GX_REQUIRED},
		{GX_TC_RANGE, STRICT, GX_REQUIRED},
		{GX_TC_RANGE, STRICT, GX_REQUIRED}
	}, -1},
	{_T("INTERSECT"), _gx_fn_intersect, 0, 0, GX_TC_RANGE, 2,
		{{GX_TC_RNG_ONLY, STRICT, GX_REQUIRED},
		{GX_TC_RNG_ONLY, STRICT, GX_REQUIRED}
	}, -1},
	{_T("INTRATE"), _gx_fn_intrate, 0, 0, GX_TC_NUMBER, 5,
		{{GX_TC_NUMERIC, STRICT, GX_REQUIRED},
		{GX_TC_NUMERIC, STRICT, GX_REQUIRED},
		{GX_TC_NUMERIC, STRICT, GX_REQUIRED},
		{GX_TC_NUMERIC, STRICT, GX_REQUIRED},
		{GX_TC_NUMERIC, STRICT, OPTIONAL}
	}, -1},
	{_T("INVDFT"), _gx_fn_invdft, 0, 0, GX_TC_MATRIX, 1,
		{{GX_TC_RNG_ONLY, STRICT, GX_REQUIRED}
	}, -1},
	{_T("INVERT"), _gx_fn_invert, 0, 0, GX_TC_MATRIX, 1,
		{{GX_TC_RNG_ONLY, STRICT, GX_REQUIRED}
	}, -1},
	{_T("INVFFT"), _gx_fn_invfft, 0, 0, GX_TC_MATRIX, 1,
		{{GX_TC_RNG_ONLY, STRICT, GX_REQUIRED}
	}, -1},
	{_T("IPMT"), _gx_fn_ipmt, 0, 0, GX_TC_NUMBER, 6,
		{{GX_TC_NUMERIC, STRICT, GX_REQUIRED},
		{GX_TC_NUMERIC, STRICT, GX_REQUIRED},
		{GX_TC_NUMERIC, STRICT, GX_REQUIRED},
		{GX_TC_NUMERIC, STRICT, GX_REQUIRED},
		{GX_TC_NUMERIC, STRICT, GX_REQUIRED},
		{GX_TC_NUMERIC, STRICT, OPTIONAL}
	}, gxxlfIpmt},
	{_T("IRR"), _gx_fn_irr, 0, 0, GX_TC_NUMBER, 2,
		{{GX_TC_NUMERIC, STRICT, GX_REQUIRED},
		{GX_TC_RNG_ONLY, STRICT, GX_REQUIRED}
	}, -1},
	{_T("ISERROR"), _gx_fn_iserror, 0, 0, GX_TC_NUMBER, 1,
		{{GX_TC_POLY, GX_NONSTRICT, GX_REQUIRED}
	}, gxxlfIserror},
	{_T("ISNUMBER"), _gx_fn_isnumber, 0, 0, GX_TC_NUMBER, 1,
		{{GX_TC_POLY, STRICT, GX_REQUIRED}
	}, gxxlfIsnumber},
	{_T("ISSTRING"), _gx_fn_isstring, 0, 0, GX_TC_NUMBER, 1,
		{{GX_TC_POLY, STRICT, GX_REQUIRED}
	}, gxxlfIstext},
	{_T("LARGE"), _gx_fn_large, 0, 0, GX_TC_NUMBER, 2,
		{{GX_TC_RANGE, STRICT, GX_REQUIRED},
		{GX_TC_NUMERIC, STRICT, GX_REQUIRED}
	}, gxxlfLarge},
	{_T("LEFT"), _gx_fn_left, 0, 0, GX_TC_STRING, 2,
		{{GX_TC_STR_CL, STRICT, GX_REQUIRED},
		{GX_TC_NUMERIC, STRICT, GX_REQUIRED}
	}, -1},
	{_T("LENGTH"), _gx_fn_length, 0, 0, GX_TC_NUMBER, 1,
		{{GX_TC_STR_CL, STRICT, GX_REQUIRED}
	}, gxxlfLen},
	{_T("LINFIT"), _gx_fn_linfit, 0, 0, GX_TC_MATRIX, 2,
		{{GX_TC_RNG_ONLY, STRICT, GX_REQUIRED},
		{GX_TC_RNG_ONLY, STRICT, GX_REQUIRED}
	}, -1},
	{_T("LLS"), _gx_fn_lls, 0, 0, GX_TC_MATRIX, 2,
		{{GX_TC_RNG_ONLY, STRICT, GX_REQUIRED},
		{GX_TC_RNG_ONLY, STRICT, GX_REQUIRED}
	}, -1},
	{_T("LN"), _gx_fn_ln, 0, 0, GX_TC_NUMBER, 1,
		{{GX_TC_NUMERIC, STRICT, GX_REQUIRED}
	}, gxxlfLn},
	{_T("LNGAMMA"), _gx_fn_lngamma, 0, 0, GX_TC_NUMBER, 1,
		{{GX_TC_NUMERIC, STRICT, GX_REQUIRED}
	}, -1},
	{_T("LOG"), _gx_fn_log, 0, 0, GX_TC_NUMBER, 1,
		{{GX_TC_NUMERIC, STRICT, GX_REQUIRED}
	}, gxxlfLog},
	{_T("LOG10"), _gx_fn_log, 0, 0, GX_TC_NUMBER, 1,
		{{GX_TC_NUMERIC, STRICT, GX_REQUIRED}
	}, gxxlfLog10},
	{_T("LOG2"), _gx_fn_log2, 0, 0, GX_TC_NUMBER, 1,
		{{GX_TC_NUMERIC, STRICT, GX_REQUIRED}
	}, -1},
	{_T("LOWER"), _gx_fn_lower, 0, 0, GX_TC_STRING, 1,
		{{GX_TC_STR_CL, STRICT, GX_REQUIRED}
	}, gxxlfLower},
	{_T("MATCH"), _gx_fn_match, 0, 0, GX_TC_NUMBER, 3,
		{{GX_TC_POLY, STRICT, GX_REQUIRED},
		{GX_TC_RNG_ONLY, STRICT, GX_REQUIRED},
		{GX_TC_NUMERIC, STRICT, OPTIONAL}
	}, gxxlfMatch},
	{_T("MAX"), _gx_fn_max, 0, 0, GX_TC_NUMBER, 1,
		{{GX_TC_NUM_RNG, STRICT, GX_VARIABLE}
	}, gxxlfMax},
	{_T("MDURATION"), _gx_fn_mduration, 0, 0, GX_TC_NUMBER, 6,
		{{GX_TC_NUMERIC, STRICT, GX_REQUIRED},
		{GX_TC_NUMERIC, STRICT, GX_REQUIRED},
		{GX_TC_NUMERIC, STRICT, GX_REQUIRED},
		{GX_TC_NUMERIC, STRICT, GX_REQUIRED},
		{GX_TC_NUMERIC, STRICT, GX_REQUIRED},
		{GX_TC_NUMERIC, STRICT, GX_REQUIRED},
		{GX_TC_NUMERIC, STRICT, OPTIONAL}
	}, -1},
	{_T("MEDIAN"), _gx_fn_median, 0, 0, GX_TC_NUMBER, 1,
		{{GX_TC_NUM_RNG, STRICT, GX_VARIABLE}
	}, gxxlfMedian},
	{_T("MESSAGE"), _gx_fn_message, 0, 0, GX_TC_NUMBER, 2,
		{{GX_TC_NUMERIC, STRICT, GX_REQUIRED},
		{GX_TC_STR_CL, STRICT, GX_REQUIRED}
	}, -1},
	{_T("MID"), _gx_fn_mid, 0, 0, GX_TC_STRING, 3,
		{{GX_TC_STR_CL, STRICT, GX_REQUIRED},
		{GX_TC_NUMERIC, STRICT, GX_REQUIRED},
		{GX_TC_NUMERIC, STRICT, GX_REQUIRED}
	}, gxxlfMid},
	{_T("MIN"), _gx_fn_min, 0, 0, GX_TC_NUMBER, 1,
		{{GX_TC_NUM_RNG, STRICT, GX_VARIABLE}
	}, gxxlfMin},
	{_T("MINUTE"), _gx_fn_minute, 0, 0, GX_TC_NUMBER, 1,
		{{GX_TC_NUMERIC, STRICT, GX_REQUIRED}
	}, gxxlfMinute},
	{_T("MIRR"), _gx_fn_mirr, 0, 0, GX_TC_NUMBER, 3,
		{{GX_TC_RANGE, STRICT, GX_REQUIRED},
		{GX_TC_NUMERIC, STRICT, GX_REQUIRED},
		{GX_TC_NUMERIC, STRICT, GX_REQUIRED}
	}, gxxlfMirr},
	{_T("MMUL"), _gx_fn_mmul, 0, 0, GX_TC_MATRIX, 2,
		{{GX_TC_RNG_ONLY, STRICT, GX_REQUIRED},
		{GX_TC_RNG_ONLY, STRICT, GX_REQUIRED}
	}, gxxlfMmult},
	{_T("MOD"), _gx_fn_mod, 0, 0, GX_TC_NUMBER, 2,
		{{GX_TC_NUMERIC, STRICT, GX_REQUIRED},
		{GX_TC_NUMERIC, STRICT, GX_REQUIRED}
	}, gxxlfMod},
	{_T("MODE"), _gx_fn_mode, 0, 0, GX_TC_NUMBER, 1,
		{{GX_TC_NUM_RNG, STRICT, GX_VARIABLE}
	}, gxxlfMode},
	{_T("MODULUS"), _gx_fn_modulus, 0, 0, GX_TC_NUMBER, 2,
		{{GX_TC_NUMERIC, STRICT, GX_REQUIRED},
		{GX_TC_NUMERIC, STRICT, GX_REQUIRED}
	}, -1},
	{_T("MONTH"), _gx_fn_month, 0, 0, GX_TC_NUMBER, 1,
		{{GX_TC_NUMERIC, STRICT, GX_REQUIRED}
	}, gxxlfMonth},
	{_T("MSQ"), _gx_fn_msq, 0, 0, GX_TC_NUMBER, 1,
		{{GX_TC_NUM_RNG, STRICT, GX_VARIABLE}
	}, -1},
	{_T("N"), _gx_fn_n, 0, 0, GX_TC_NUMBER, 1,
		{{GX_TC_RANGE, STRICT, GX_REQUIRED}
	}, -1},
	{_T("NA"), _gx_fn_na, 0, 0, GX_TC_NUMBER, 0,
	{0,0,0}, gxxlfNa},
	{_T("NAND"), _gx_fn_nand, 0, 0, GX_TC_NUMBER, 1,
		{{GX_TC_NUM_RNG, STRICT, GX_VARIABLE}
	}, -1},
	{_T("NETWORKDAYS"), _gx_fn_networkdays, 0, 0, GX_TC_NUMBER, 3,
		{{GX_TC_NUMERIC, STRICT, GX_REQUIRED},
		{GX_TC_NUMERIC, STRICT, GX_REQUIRED},
		{GX_TC_NUMERIC, STRICT, OPTIONAL}
	}, -1},
	{_T("NOMINAL"), _gx_fn_nominal, 0, 0, GX_TC_NUMBER, 2,
		{{GX_TC_NUMERIC, STRICT, GX_REQUIRED},
		{GX_TC_NUMERIC, STRICT, GX_REQUIRED}
	}, -1},
	{_T("NOR"), _gx_fn_nor, 0, 0, GX_TC_NUMBER, 1,
		{{GX_TC_NUM_RNG, STRICT, GX_VARIABLE}
	}, -1},
	{_T("NORMDIST"), _gx_fn_normdist, 0, 0, GX_TC_NUMBER, 4,
		{{GX_TC_NUMERIC, STRICT, GX_REQUIRED},
		{GX_TC_NUMERIC, STRICT, GX_REQUIRED},
		{GX_TC_NUMERIC, STRICT, GX_REQUIRED},
		{GX_TC_NUMERIC, STRICT, GX_REQUIRED}
	}, gxxlfNormdist},
	{_T("NORMINV"), _gx_fn_norminv, 0, 0, GX_TC_NUMBER, 3,
		{{GX_TC_NUMERIC, STRICT, GX_REQUIRED},
		{GX_TC_NUMERIC, STRICT, GX_REQUIRED},
		{GX_TC_NUMERIC, STRICT, GX_REQUIRED}
	}, gxxlfNorminv},
	{_T("NORMSDIST"), _gx_fn_normsdist, 0, 0, GX_TC_NUMBER, 1,
		{{GX_TC_NUMERIC, STRICT, GX_REQUIRED}
	}, gxxlfNormsdist},
	{_T("NORMSINV"), _gx_fn_normsinv, 0, 0, GX_TC_NUMBER, 1,
		{{GX_TC_NUMERIC, STRICT, GX_REQUIRED}
	}, gxxlfNormsinv},
	{_T("NOT"), _gx_fn_not, 0, 0, GX_TC_NUMBER, 1,
		{{GX_TC_NUMERIC, STRICT, GX_REQUIRED}
	}, gxxlfNot},
	{_T("NOW"), _gx_fn_now, 0, 0, GX_TC_NUMBER, 0,
	{0,0,0}, gxxlfNow},
	{_T("NUMTOHEX"), _gx_fn_numtohex, 0, 0, GX_TC_STRING, 1,
		{{GX_TC_NUMERIC, STRICT, GX_REQUIRED}
	}, -1},
	{_T("ODDFPRICE"), _gx_fn_oddfprice, 0, 0, GX_TC_NUMBER, 9,
		{{GX_TC_NUMERIC, STRICT, GX_REQUIRED},
		{GX_TC_NUMERIC, STRICT, GX_REQUIRED},
		{GX_TC_NUMERIC, STRICT, GX_REQUIRED},
		{GX_TC_NUMERIC, STRICT, GX_REQUIRED},
		{GX_TC_NUMERIC, STRICT, GX_REQUIRED},
		{GX_TC_NUMERIC, STRICT, GX_REQUIRED},
		{GX_TC_NUMERIC, STRICT, GX_REQUIRED},
		{GX_TC_NUMERIC, STRICT, GX_REQUIRED},
		{GX_TC_NUMERIC, STRICT, OPTIONAL}
	}, -1},
	{_T("ODDFYIELD"), _gx_fn_oddfyield, 0, 0, GX_TC_NUMBER, 9,
		{{GX_TC_NUMERIC, STRICT, GX_REQUIRED},
		{GX_TC_NUMERIC, STRICT, GX_REQUIRED},
		{GX_TC_NUMERIC, STRICT, GX_REQUIRED},
		{GX_TC_NUMERIC, STRICT, GX_REQUIRED},
		{GX_TC_NUMERIC, STRICT, GX_REQUIRED},
		{GX_TC_NUMERIC, STRICT, GX_REQUIRED},
		{GX_TC_NUMERIC, STRICT, GX_REQUIRED},
		{GX_TC_NUMERIC, STRICT, GX_REQUIRED},
		{GX_TC_NUMERIC, STRICT, OPTIONAL}
	}, -1},
	{_T("OR"), _gx_fn_or, 0, 0, GX_TC_NUMBER, 1,
		{{GX_TC_NUM_RNG, STRICT, GX_VARIABLE}
	}, gxxlfOr},
	{_T("PERCENTILE"), _gx_fn_percentile, 0, 0, GX_TC_NUMBER, 2,
		{{GX_TC_RANGE, STRICT, GX_REQUIRED},
		{GX_TC_NUMERIC, STRICT, GX_REQUIRED}
	}, gxxlfPercentile},
	{_T("PERCENTRANK"), _gx_fn_percentrank, 0, 0, GX_TC_NUMBER, 2,
		{{GX_TC_RANGE, STRICT, GX_REQUIRED},
		{GX_TC_NUMERIC, STRICT, GX_REQUIRED}
	}, gxxlfPercentrank},
	{_T("PERMUT"), _gx_fn_permut, 0, 0, GX_TC_NUMBER, 2,
		{{GX_TC_NUMERIC, STRICT, GX_REQUIRED},
		{GX_TC_NUMERIC, STRICT, GX_REQUIRED}
	}, gxxlfPermut},
	{_T("PI"), _gx_fn_pi, 0, 0, GX_TC_NUMBER, 0,
	{0,0,0}, gxxlfPi},
	{_T("PLS"), _gx_fn_pls, 0, 0, GX_TC_MATRIX, 3,
		{{GX_TC_RNG_ONLY, STRICT, GX_REQUIRED},
		{GX_TC_RNG_ONLY, STRICT, GX_REQUIRED},
		{GX_TC_NUMERIC, STRICT, GX_REQUIRED}
	}, -1},
	{_T("PMT"), _gx_fn_pmt, 0, 0, GX_TC_NUMBER, 3,
		{{GX_TC_NUMERIC, STRICT, GX_REQUIRED},
		{GX_TC_NUMERIC, STRICT, GX_REQUIRED},
		{GX_TC_NUMERIC, STRICT, GX_REQUIRED}
	}, -1},
	{_T("POLY"), _gx_fn_poly, 0, 0, GX_TC_NUMBER, 2,
		{{GX_TC_NUMERIC, STRICT, GX_REQUIRED},
		{GX_TC_NUM_RNG, STRICT, GX_VARIABLE}
	}, -1},
	{_T("POLYCOEF"), _gx_fn_polycoef, 0, 0, GX_TC_MATRIX, 3,
		{{GX_TC_RNG_ONLY, STRICT, GX_REQUIRED},
		{GX_TC_RNG_ONLY, STRICT, GX_REQUIRED},
		{GX_TC_NUMERIC, STRICT, GX_REQUIRED}
	}, -1},
	{_T("PPMT"), _gx_fn_ppmt, 0, 0, GX_TC_NUMBER, 6,
		{{GX_TC_NUMERIC, STRICT, GX_REQUIRED},
		{GX_TC_NUMERIC, STRICT, GX_REQUIRED},
		{GX_TC_NUMERIC, STRICT, GX_REQUIRED},
		{GX_TC_NUMERIC, STRICT, GX_REQUIRED},
		{GX_TC_NUMERIC, STRICT, GX_REQUIRED},
		{GX_TC_NUMERIC, STRICT, OPTIONAL}
	}, -1},
	{_T("PRICE"), _gx_fn_price, 0, 0, GX_TC_NUMBER, 7,
		{{GX_TC_NUMERIC, STRICT, GX_REQUIRED},
		{GX_TC_NUMERIC, STRICT, GX_REQUIRED},
		{GX_TC_NUMERIC, STRICT, GX_REQUIRED},
		{GX_TC_NUMERIC, STRICT, GX_REQUIRED},
		{GX_TC_NUMERIC, STRICT, GX_REQUIRED},
		{GX_TC_NUMERIC, STRICT, GX_REQUIRED},
		{GX_TC_NUMERIC, STRICT, OPTIONAL}
	}, -1},
	{_T("PRICEDISC"), _gx_fn_pricedisc, 0, 0, GX_TC_NUMBER, 5,
		{{GX_TC_NUMERIC, STRICT, GX_REQUIRED},
		{GX_TC_NUMERIC, STRICT, GX_REQUIRED},
		{GX_TC_NUMERIC, STRICT, GX_REQUIRED},
		{GX_TC_NUMERIC, STRICT, GX_REQUIRED},
		{GX_TC_NUMERIC, STRICT, OPTIONAL}
	}, -1},
	{_T("PRICEMAT"), _gx_fn_pricemat, 0, 0, GX_TC_NUMBER, 6,
		{{GX_TC_NUMERIC, STRICT, GX_REQUIRED},
		{GX_TC_NUMERIC, STRICT, GX_REQUIRED},
		{GX_TC_NUMERIC, STRICT, GX_REQUIRED},
		{GX_TC_NUMERIC, STRICT, GX_REQUIRED},
		{GX_TC_NUMERIC, STRICT, GX_REQUIRED},
		{GX_TC_NUMERIC, STRICT, OPTIONAL}
	}, -1},
	{_T("PRODUCT"), _gx_fn_product, 0, 0, GX_TC_NUMBER, 1,
		{{GX_TC_NUM_RNG, STRICT, GX_VARIABLE}
	}, gxxlfProduct},
	{_T("PROPER"), _gx_fn_proper, 0, 0, GX_TC_STRING, 1,
		{{GX_TC_STR_CL, STRICT, GX_REQUIRED}
	}, gxxlfProper},
	{_T("PTTEST"), _gx_fn_pttest, 0, 0, GX_TC_NUMBER, 2,
		{{GX_TC_RNG_ONLY, STRICT, GX_REQUIRED},
		{GX_TC_RNG_ONLY, STRICT, GX_REQUIRED}
	}, -1},
	{_T("PV"), _gx_fn_pv, 0, 0, GX_TC_NUMBER, 3,
		{{GX_TC_NUMERIC, STRICT, GX_REQUIRED},
		{GX_TC_NUMERIC, STRICT, GX_REQUIRED},
		{GX_TC_NUMERIC, STRICT, GX_REQUIRED}
	}, -1},
	{_T("QUARTILE"), _gx_fn_quartile, 0, 0, GX_TC_NUMBER, 2,
		{{GX_TC_RANGE, STRICT, GX_REQUIRED},
		{GX_TC_NUMERIC, STRICT, GX_REQUIRED}
	}, gxxlfQuartile},
	{_T("RADIANS"), _gx_fn_radians, 0, 0, GX_TC_NUMBER, 1,
		{{GX_TC_NUMERIC, STRICT, GX_REQUIRED}
	}, -1},
#if _MFC_VER >= 0x0300
	{_T("RAND"), _gx_fn_rand, 0, 0, GX_TC_NUMBER, 0,
	{0,0,0}, -1},
#endif
	{_T("RANGEREF"), _gx_fn_rangeref, 0, 0, GX_TC_RANGE, 4,
		{{GX_TC_NUMERIC, STRICT, GX_REQUIRED},
		{GX_TC_NUMERIC, STRICT, GX_REQUIRED},
		{GX_TC_NUMERIC, STRICT, GX_REQUIRED},
		{GX_TC_NUMERIC, STRICT, GX_REQUIRED}
	}, -1},
	{_T("RANK"), _gx_fn_rank, 0, 0, GX_TC_NUMBER, 3,
		{{GX_TC_NUMERIC, STRICT, GX_REQUIRED},
		{GX_TC_RNG_ONLY, STRICT, GX_REQUIRED},
		{GX_TC_NUMERIC, STRICT, OPTIONAL}
	}, gxxlfRank},
	{_T("RATE"), _gx_fn_rate, 0, 0, GX_TC_NUMBER, 3,
		{{GX_TC_NUMERIC, STRICT, GX_REQUIRED},
		{GX_TC_NUMERIC, STRICT, GX_REQUIRED},
		{GX_TC_NUMERIC, STRICT, GX_REQUIRED}
	}, -1},
	{_T("RECEIVED"), _gx_fn_received, 0, 0, GX_TC_NUMBER, 5,
		{{GX_TC_NUMERIC, STRICT, GX_REQUIRED},
		{GX_TC_NUMERIC, STRICT, GX_REQUIRED},
		{GX_TC_NUMERIC, STRICT, GX_REQUIRED},
		{GX_TC_NUMERIC, STRICT, GX_REQUIRED},
		{GX_TC_NUMERIC, STRICT, OPTIONAL}
	}, -1},
	{_T("REGEX"), _gx_fn_regex, 0, 0, GX_TC_NUMBER, 2,
		{{GX_TC_STR_CL, STRICT, GX_REQUIRED},
		{GX_TC_STR_CL, STRICT, GX_REQUIRED}
	}, -1},
	{_T("REPEAT"), _gx_fn_repeat, 0, 0, GX_TC_STRING, 2,
		{{GX_TC_STR_CL, STRICT, GX_REQUIRED},
		{GX_TC_NUMERIC, STRICT, GX_REQUIRED}
	}, gxxlfRept},
	{_T("REPLACE"), _gx_fn_replace, 0, 0, GX_TC_STRING, 4,
		{{GX_TC_STR_CL, STRICT, GX_REQUIRED},
		{GX_TC_NUMERIC, STRICT, GX_REQUIRED},
		{GX_TC_NUMERIC, STRICT, GX_REQUIRED},
		{GX_TC_STR_CL, STRICT, GX_REQUIRED}
	}, gxxlfReplace},
	{_T("RIGHT"), _gx_fn_right, 0, 0, GX_TC_STRING, 2,
		{{GX_TC_STR_CL, STRICT, GX_REQUIRED},
		{GX_TC_NUMERIC, STRICT, GX_REQUIRED}
	}, -1},
	{_T("RMS"), _gx_fn_rms, 0, 0, GX_TC_NUMBER, 1,
		{{GX_TC_NUM_RNG, STRICT, GX_VARIABLE}
	}, -1},
	{_T("ROUND"), _gx_fn_round, 0, 0, GX_TC_NUMBER, 2,
		{{GX_TC_NUMERIC, STRICT, GX_REQUIRED},
		{GX_TC_NUMERIC, STRICT, GX_REQUIRED}
	}, gxxlfRound},
	{_T("ROW"), _gx_fn_row, 0, 0, GX_TC_NUMBER, 1,
		{{GX_TC_RANGE, STRICT, OPTIONAL}
	}, gxxlfRow},
	{_T("ROWS"), _gx_fn_rows, 0, 0, GX_TC_NUMBER, 1,
		{{GX_TC_RNG_ONLY, STRICT, GX_REQUIRED}
	}, gxxlfRows},
	{_T("S"), _gx_fn_s, 0, 0, GX_TC_STRING, 1,
		{{GX_TC_RANGE, STRICT, GX_REQUIRED}
	}, -1},
	{_T("SECOND"), _gx_fn_second, 0, 0, GX_TC_NUMBER, 1,
		{{GX_TC_NUMERIC, STRICT, GX_REQUIRED}
	}, gxxlfSecond},
	{_T("SIGMOID"), _gx_fn_sigmoid, 0, 0, GX_TC_NUMBER, 1,
		{{GX_TC_NUMERIC, STRICT, GX_REQUIRED}
	}, -1},
	{_T("SIN"), _gx_fn_sin, 0, 0, GX_TC_NUMBER, 1,
		{{GX_TC_NUMERIC, STRICT, GX_REQUIRED}
	}, gxxlfSin},
	{_T("SINH"), _gx_fn_sinh, 0, 0, GX_TC_NUMBER, 1,
		{{GX_TC_NUMERIC, STRICT, GX_REQUIRED}
	}, gxxlfSinh},
	{_T("SLN"), _gx_fn_sln, 0, 0, GX_TC_NUMBER, 3,
		{{GX_TC_NUMERIC, STRICT, GX_REQUIRED},
		{GX_TC_NUMERIC, STRICT, GX_REQUIRED},
		{GX_TC_NUMERIC, STRICT, GX_REQUIRED}
	}, gxxlfSln},
	{_T("SMALL"), _gx_fn_small, 0, 0, GX_TC_NUMBER, 2,
		{{GX_TC_RANGE, STRICT, GX_REQUIRED},
		{GX_TC_NUMERIC, STRICT, GX_REQUIRED}
	}, gxxlfSmall},
	{_T("SQRT"), _gx_fn_sqrt, 0, 0, GX_TC_NUMBER, 1,
		{{GX_TC_NUMERIC, STRICT, GX_REQUIRED}
	}, gxxlfSqrt},
	{_T("SSE"), _gx_fn_sse, 0, 0, GX_TC_NUMBER, 1,
		{{GX_TC_NUM_RNG, STRICT, GX_VARIABLE}
	}, -1},
	{_T("SSQ"), _gx_fn_ssq, 0, 0, GX_TC_NUMBER, 1,
		{{GX_TC_NUM_RNG, STRICT, GX_VARIABLE}
	}, -1},
	{_T("STANDARDIZE"), _gx_fn_standardize, 0, 0, GX_TC_NUMBER, 3,
		{{GX_TC_NUMERIC, STRICT, GX_REQUIRED},
		{GX_TC_NUMERIC, STRICT, GX_REQUIRED},
		{GX_TC_NUMERIC, STRICT, GX_REQUIRED}
	}, gxxlfStandardize},
	{_T("STD"), _gx_fn_std, 0, 0, GX_TC_NUMBER, 1,
		{{GX_TC_NUM_RNG, STRICT, GX_VARIABLE}
	}, gxxlfStdevp},
	{_T("STDS"), _gx_fn_stds, 0, 0, GX_TC_NUMBER, 1,
		{{GX_TC_NUM_RNG, STRICT, GX_VARIABLE}
	}, gxxlfStdev},
	{_T("STRCAT"), _gx_fn_strcat, 0, 0, GX_TC_STRING, 1,
		{{GX_TC_POLY, STRICT, GX_VARIABLE}
	}, gxxlfConcatenate},
	{_T("STRING"), _gx_fn_string, 0, 0, GX_TC_STRING, 2,
		{{GX_TC_NUMERIC, STRICT, GX_REQUIRED},
		{GX_TC_NUMERIC, STRICT, GX_REQUIRED}
	}, -1},
	{_T("STRLEN"), _gx_fn_strlen, 0, 0, GX_TC_NUMBER, 1,
		{{GX_TC_POLY, STRICT, GX_VARIABLE}
	}, -1},
	{_T("SUM"), _gx_fn_sum, 0, 0, GX_TC_NUMBER, 1,
		{{GX_TC_NUM_RNG, STRICT, GX_VARIABLE}
	}, gxxlfSum},
	{_T("SUMPRODUCT"), _gx_fn_dot, 0, 0, GX_TC_NUMBER, 2,
		{{GX_TC_RNG_ONLY, STRICT, GX_REQUIRED},
		{GX_TC_RNG_ONLY, STRICT, GX_REQUIRED}
	}, gxxlfSumproduct},
	{_T("SYD"), _gx_fn_syd, 0, 0, GX_TC_NUMBER, 4,
		{{GX_TC_NUMERIC, STRICT, GX_REQUIRED},
		{GX_TC_NUMERIC, STRICT, GX_REQUIRED},
		{GX_TC_NUMERIC, STRICT, GX_REQUIRED},
		{GX_TC_NUMERIC, STRICT, GX_REQUIRED}
	}, gxxlfSyd},
	{_T("T"), _gx_fn_t, 0, 0, GX_TC_NUMBER, 2,
		{{GX_TC_NUMERIC, STRICT, GX_REQUIRED},
		{GX_TC_NUMERIC, STRICT, GX_REQUIRED}
	}, -1},
	{_T("TAN"), _gx_fn_tan, 0, 0, GX_TC_NUMBER, 1,
		{{GX_TC_NUMERIC, STRICT, GX_REQUIRED}
	}, gxxlfTan},
	{_T("TANH"), _gx_fn_tanh, 0, 0, GX_TC_NUMBER, 1,
		{{GX_TC_NUMERIC, STRICT, GX_REQUIRED}
	}, gxxlfTanh},
	{_T("TBILLEQ"), _gx_fn_tbilleq, 0, 0, GX_TC_NUMBER, 3,
		{{GX_TC_NUMERIC, STRICT, GX_REQUIRED},
		{GX_TC_NUMERIC, STRICT, GX_REQUIRED},
		{GX_TC_NUMERIC, STRICT, GX_REQUIRED}
	}, -1},
	{_T("TBILLYIELD"), _gx_fn_tbillyield, 0, 0, GX_TC_NUMBER, 3,
		{{GX_TC_NUMERIC, STRICT, GX_REQUIRED},
		{GX_TC_NUMERIC, STRICT, GX_REQUIRED},
		{GX_TC_NUMERIC, STRICT, GX_REQUIRED}
	}, -1},
	{_T("TERM"), _gx_fn_term, 0, 0, GX_TC_NUMBER, 3,
		{{GX_TC_NUMERIC, STRICT, GX_REQUIRED},
		{GX_TC_NUMERIC, STRICT, GX_REQUIRED},
		{GX_TC_NUMERIC, STRICT, GX_REQUIRED}
	}, -1},
	{_T("TIME"), _gx_fn_time, 0, 0, GX_TC_NUMBER, 3,
		{{GX_TC_NUMERIC, STRICT, GX_REQUIRED},
		{GX_TC_NUMERIC, STRICT, GX_REQUIRED},
		{GX_TC_NUMERIC, STRICT, GX_REQUIRED}
	}, gxxlfTime},
	{_T("TIMEVALUE"), _gx_fn_timevalue, 0, 0, GX_TC_NUMBER, 1,
		{{GX_TC_STR_CL, STRICT, GX_REQUIRED}
	}, gxxlfTimevalue},
	{_T("TODAY"), _gx_fn_today, 0, 0, GX_TC_NUMBER, 0,
	{0,0,0}, gxxlfToday},
	{_T("TRANSPOSE"), _gx_fn_transpose, 0, 0, GX_TC_MATRIX, 1,
		{{GX_TC_RNG_ONLY, STRICT, GX_REQUIRED}
	}, gxxlfTranspose},
	{_T("TREND"), _gx_fn_trend, 0, 0, GX_TC_MATRIX, 3,
		{{GX_TC_RNG_ONLY, STRICT, GX_REQUIRED},
		{GX_TC_RNG_ONLY, STRICT, GX_REQUIRED},
		{GX_TC_RNG_ONLY, STRICT, GX_REQUIRED}
	}, -1},
	{_T("TRIM"), _gx_fn_trim, 0, 0, GX_TC_STRING, 1,
		{{GX_TC_STR_CL, STRICT, GX_REQUIRED}
	}, gxxlfTrim},
	{_T("TRUE"), _gx_fn_true, 0, 0, GX_TC_NUMBER, 0,
	{0,0,0}, gxxlfTrue},
	{_T("TSV"), _gx_fn_tsv, 0, 0, GX_TC_STRING, 1,
		{{GX_TC_POLY, STRICT, GX_VARIABLE}
	}, -1},
	{_T("TTEST"), _gx_fn_ttest, 0, 0, GX_TC_NUMBER, 2,
		{{GX_TC_RNG_ONLY, STRICT, GX_REQUIRED},
		{GX_TC_NUMERIC, STRICT, GX_REQUIRED}
	}, -1},
	{_T("TTEST2EV"), _gx_fn_ttest2ev, 0, 0, GX_TC_NUMBER, 2,
		{{GX_TC_RNG_ONLY, STRICT, GX_REQUIRED},
		{GX_TC_RNG_ONLY, STRICT, GX_REQUIRED}
	}, -1},
	{_T("TTEST2UV"), _gx_fn_ttest2uv, 0, 0, GX_TC_NUMBER, 2,
		{{GX_TC_RNG_ONLY, STRICT, GX_REQUIRED},
		{GX_TC_RNG_ONLY, STRICT, GX_REQUIRED}
	}, -1},
	{_T("UPPER"), _gx_fn_upper, 0, 0, GX_TC_STRING, 1,
		{{GX_TC_STR_CL, STRICT, GX_REQUIRED}
	}, gxxlfUpper},
	{_T("VALUE"), _gx_fn_value, 0, 0, GX_TC_NUMBER, 1,
		{{GX_TC_STR_CL, STRICT, GX_REQUIRED}
	}, gxxlfValue},
	{_T("VAR"), _gx_fn_var, 0, 0, GX_TC_NUMBER, 1,
		{{GX_TC_NUM_RNG, STRICT, GX_VARIABLE}
	}, gxxlfVarp},
	{_T("VARS"), _gx_fn_vars, 0, 0, GX_TC_NUMBER, 1,
		{{GX_TC_NUM_RNG, STRICT, GX_VARIABLE}
	}, gxxlfVar},
	{_T("VDB"), _gx_fn_vdb, 0, 0, GX_TC_NUMBER, 5,
		{{GX_TC_NUMERIC, STRICT, GX_REQUIRED},
		{GX_TC_NUMERIC, STRICT, GX_REQUIRED},
		{GX_TC_NUMERIC, STRICT, GX_REQUIRED},
		{GX_TC_NUMERIC, STRICT, GX_REQUIRED},
		{GX_TC_NUMERIC, STRICT, GX_REQUIRED}
	}, -1},
	{_T("VECLEN"), _gx_fn_veclen, 0, 0, GX_TC_NUMBER, 1,
		{{GX_TC_NUM_RNG, STRICT, GX_VARIABLE}
	}, -1},
	{_T("VLOOKUP"), _gx_fn_vlookup, 0, 0, GX_TC_POLY, 3,
		{{GX_TC_POLY, STRICT, GX_REQUIRED},
		{GX_TC_RNG_ONLY, STRICT, GX_REQUIRED},
		{GX_TC_NUMERIC, STRICT, GX_REQUIRED}
	}, gxxlfVlookup},
	{_T("VSUM"), _gx_fn_vsum, 0, 0, GX_TC_NUMBER, 1,
		{{GX_TC_NUM_RNG, STRICT, GX_VARIABLE}
	}, -1},
	{_T("WEEKDAY"), _gx_fn_weekday, 0, 0, GX_TC_NUMBER, 1,
		{{GX_TC_NUMERIC, STRICT, GX_REQUIRED}
	}, -1},
	{_T("WORKDAY"), _gx_fn_workday, 0, 0, GX_TC_NUMBER, 3,
		{{GX_TC_NUMERIC, STRICT, GX_REQUIRED},
		{GX_TC_NUMERIC, STRICT, GX_REQUIRED},
		{GX_TC_NUMERIC, STRICT, OPTIONAL}
	}, -1},
	{_T("XIRR"), _gx_fn_xirr, 0, 0, GX_TC_NUMBER, 3,
		{{GX_TC_RANGE, STRICT, GX_REQUIRED},
		{GX_TC_RANGE, STRICT, GX_REQUIRED},
		{GX_TC_NUMERIC, STRICT, GX_REQUIRED}
	}, -1},
	{_T("XNPV"), _gx_fn_xnpv, 0, 0, GX_TC_NUMBER, 3,
		{{GX_TC_NUMERIC, STRICT, GX_REQUIRED},
		{GX_TC_RANGE, STRICT, GX_REQUIRED},
		{GX_TC_RANGE, STRICT, GX_REQUIRED}
	}, -1},
	{_T("XOR"), _gx_fn_xor, 0, 0, GX_TC_NUMBER, 1,
		{{GX_TC_NUM_RNG, STRICT, GX_VARIABLE}
	}, -1},
	{_T("YEAR"), _gx_fn_year, 0, 0, GX_TC_NUMBER, 1,
		{{GX_TC_NUMERIC, STRICT, GX_REQUIRED}
	}, gxxlfYear},
	{_T("YEARFRAC"), _gx_fn_yearfrac, 0, 0, GX_TC_NUMBER, 3,
		{{GX_TC_NUMERIC, STRICT, GX_REQUIRED},
		{GX_TC_NUMERIC, STRICT, GX_REQUIRED},
		{GX_TC_NUMERIC, STRICT, OPTIONAL}
	}, -1},
	{_T("YIELD"), _gx_fn_yield, 0, 0, GX_TC_NUMBER, 7,
		{{GX_TC_NUMERIC, STRICT, GX_REQUIRED},
		{GX_TC_NUMERIC, STRICT, GX_REQUIRED},
		{GX_TC_NUMERIC, STRICT, GX_REQUIRED},
		{GX_TC_NUMERIC, STRICT, GX_REQUIRED},
		{GX_TC_NUMERIC, STRICT, GX_REQUIRED},
		{GX_TC_NUMERIC, STRICT, GX_REQUIRED},
		{GX_TC_NUMERIC, STRICT, OPTIONAL}
	}, -1},
	{_T("YIELDMAT"), _gx_fn_yieldmat, 0, 0, GX_TC_NUMBER, 6,
		{{GX_TC_NUMERIC, STRICT, GX_REQUIRED},
		{GX_TC_NUMERIC, STRICT, GX_REQUIRED},
		{GX_TC_NUMERIC, STRICT, GX_REQUIRED},
		{GX_TC_NUMERIC, STRICT, GX_REQUIRED},
		{GX_TC_NUMERIC, STRICT, GX_REQUIRED},
		{GX_TC_NUMERIC, STRICT, OPTIONAL}
	}, -1},
	{_T("ZTEST"), _gx_fn_ztest, 0, 0, GX_TC_NUMBER, 3,
		{{GX_TC_NUMERIC, STRICT, GX_REQUIRED},
		{GX_TC_NUMERIC, STRICT, GX_REQUIRED},
		{GX_TC_NUMERIC, STRICT, OPTIONAL}
	}, gxxlfZtest},
};

int CGXDefaultWorksheetFunctions::fn_table_size = sizeof(fn_table);
