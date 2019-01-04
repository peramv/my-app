///////////////////////////////////////////////////////////////////////////////
// fnfina2.cpp: Financial worksheet functions
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

#define _OG_EXPORT_IMPL
#define _RW_IMPL

#include "stdafx.h"
#include "grid\gxsinc.h"


#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#define new DEBUG_NEW
#endif

#if _MFC_VER < 0x0300
#pragma warning(disable:4051)
#endif
#pragma warning(disable:4244) // conversion from 'double' to 'int', possible loss of data
// This warning happens when a worksheet function needs an INT parameter
// and converts the Number value to an int without explicit type cast
// I prefer to turn that warning off here and not to type-cast each function - this
// lets me later find all those affected lines again easier

#pragma warning(disable:4100) // unreferenced formal parameter


#define MAX_IT 100		// matching Excel's number of iterations/tries to 100
#define CELLRANGE

/* For debuging purpose */
/*
#define DBG_ACCRINT
*/

static long days(long d1, long d2, int b)
{
	return (b ? d2 - d1 : _gx_days360(_gx_get_expr_si(), d1, d2));
}


static int get_basis(gxNumber basis_arg)
{
	if (basis_arg < 0 || basis_arg > 3)
	{
		_gx_function_error(GX_FN_ERR_INVALID_BASIS);
		return 0;
	}
	else
		return (int) basis_arg;
}

static int get_frequency(gxNumber frequency_arg)
{
	switch ((int) frequency_arg)
	{
	case 1:
	case 2:
	case 4:
		return (int) frequency_arg;
	default:
		_gx_function_error(GX_FN_ERR_INVALID_FQ);
		return 0;
	}
}

static long coupdaybs(long settlement, int maturity, int frequency, int basis)
{
	int period,
		i;
	long bs_date;
	int si = _gx_get_expr_si();

	bs_date = maturity;
	period = -(12 / frequency);

	for (i = 1; bs_date > settlement; i++)
		bs_date = _gx_edate(si, maturity, period * i);
	return (basis ? (settlement - bs_date) : _gx_days360(si, bs_date, settlement));
}


static long coupdays(int settlement, int maturity, int frequency, int basis)
{
	int period,
	    i;
	long
		bs_date1,
		bs_date2;
	int si = _gx_get_expr_si();

	if (!basis)
		return (360 / frequency);   /* it's trivial in 30/360 _tsystem */
	period = -(12 / frequency);
	bs_date1 = maturity;
	for (i = 1; bs_date1 > settlement; i++)
		bs_date1 = _gx_edate(si, maturity, period * i);

	bs_date2 = _gx_edate(si, bs_date1, 12 / frequency);
	return (basis ? (bs_date2 - bs_date1) : _gx_days360(si, bs_date1, bs_date2));
}


static int coupnum(int settlement, int maturity, int frequency, int basis)
{
	// Unused:
	basis;

	int period,
		dt;
	register int i;

	dt = maturity;
	period = -(12 / frequency);
	for (i = 1; dt > settlement; i++)
		dt = _gx_edate(_gx_get_expr_si(), maturity, period * i);
	return (i - 1);
}


gxOperand __cdecl _gx_fn_coupdaybs(gxOperand argv[])
{
	gxOperand op;
	int settlement,
		maturity,
		frequency,
		basis = 0,
		i;

	if (argv->val.count < 3 || argv->val.count > 4)
		_gx_function_error(GX_FN_ERR_ARG_CNT_WRONG);
	for (i = 1; i < argv->val.count + 1; i++)
	{
		_gx_cvt2constant(argv + i);
		if (argv[i].type != GX_NUMBER)
			_gx_function_error(GX_FN_ERR_ARG_NUMERIC);
	}
	settlement = argv[1].val.number;
	maturity   = argv[2].val.number;
	frequency	= get_frequency(argv[3].val.number);

	if (settlement <= 0 || settlement > 73050)
		_gx_function_error(GX_FN_ERR_INVALID_DATE);
	if (maturity <= 0 || maturity > 73050)
		_gx_function_error(GX_FN_ERR_INVALID_DATE);
	if (settlement >= maturity)
		_gx_function_error(GX_FN_ERR_SDT_GE_MDT);
	if (argv->val.count == 4)
		basis = get_basis(argv[4].val.number);

	op.val.number = (gxNumber) coupdaybs(settlement, maturity, frequency, basis);
	op.type = GX_NUMBER;
	return op;
}



gxOperand __cdecl _gx_fn_coupdays(gxOperand argv[])
{
	gxOperand op;
	int settlement,
		maturity,
		frequency,
		basis = 0,
		i;

	if (argv->val.count < 3 || argv->val.count > 4)
		_gx_function_error(GX_FN_ERR_ARG_CNT_WRONG);
	for (i = 1; i < argv->val.count + 1; i++)
	{
		_gx_cvt2constant(argv + i);
		if (argv[i].type != GX_NUMBER)
			_gx_function_error(GX_FN_ERR_ARG_NUMERIC);
	}
	settlement = argv[1].val.number;
	maturity   = argv[2].val.number;
	if (settlement <= 0 || settlement > 73050)
		_gx_function_error(GX_FN_ERR_INVALID_DATE);
	if (maturity <= 0 || maturity > 73050)
		_gx_function_error(GX_FN_ERR_INVALID_DATE);
	if (settlement >= maturity)
		_gx_function_error(GX_FN_ERR_SDT_GE_MDT);
	frequency = get_frequency(argv[3].val.number);
	if (argv->val.count == 4)
		basis = get_basis(argv[4].val.number);

	op.val.number = (gxNumber) coupdays(settlement, maturity, frequency, basis);
	op.type = GX_NUMBER;
	return op;
}


static int coupdaysnc(long settlement, long maturity, int frequency, int basis)
{
	int period,
		i;
	long bs_date;
	int si = _gx_get_expr_si();

	bs_date = maturity;
	period = -(12 / frequency);
	for (i = 1; bs_date > settlement; i++)
		bs_date = _gx_edate(si, maturity, period * i);
	bs_date = _gx_edate(si, bs_date, 12 / frequency);
	return (basis ? (bs_date - settlement) : _gx_days360(si, settlement, bs_date));
}


gxOperand __cdecl _gx_fn_coupdaysnc(gxOperand argv[])
{
	gxOperand op;
	int settlement,
		maturity,
		frequency,
		basis = 0,
		i;

	if (argv->val.count < 3 || argv->val.count > 4)
		_gx_function_error(GX_FN_ERR_ARG_CNT_WRONG);
	for (i = 1; i < argv->val.count + 1; i++)
	{
		_gx_cvt2constant(argv + i);
		if (argv[i].type != GX_NUMBER)
			_gx_function_error(GX_FN_ERR_ARG_NUMERIC);
	}
	settlement = argv[1].val.number;
	maturity   = argv[2].val.number;
	if (settlement <= 0 || settlement > 73050)
		_gx_function_error(GX_FN_ERR_INVALID_DATE);
	if (maturity <= 0 || maturity > 73050)
		_gx_function_error(GX_FN_ERR_INVALID_DATE);
	if (settlement >= maturity)
		_gx_function_error(GX_FN_ERR_SDT_GE_MDT);
	frequency = get_frequency(argv[3].val.number);
	if (argv->val.count == 4)
		basis = get_basis(argv[4].val.number);

	op.val.number = (gxNumber) coupdaysnc(settlement, maturity,
										  frequency, basis);
	op.type = GX_NUMBER;
	return op;
}


gxOperand __cdecl _gx_fn_coupncd(gxOperand argv[])
{
	gxOperand op;
	int settlement,
		maturity,
		frequency,
		basis = 0,
		i;
	int year,
		mon,
		day,
		period,
		bs_date;
	int si = _gx_get_expr_si();

	if (argv->val.count < 3 || argv->val.count > 4)
		_gx_function_error(GX_FN_ERR_ARG_CNT_WRONG);
	for (i = 1; i < argv->val.count + 1; i++)
	{
		_gx_cvt2constant(argv + i);
		if (argv[i].type != GX_NUMBER)
			_gx_function_error(GX_FN_ERR_ARG_NUMERIC);
	}
	settlement = argv[1].val.number;
	maturity   = bs_date = argv[2].val.number;
	if (settlement <= 0 || settlement > 73050)
		_gx_function_error(GX_FN_ERR_INVALID_DATE);
	if (maturity <= 0 || maturity > 73050)
		_gx_function_error(GX_FN_ERR_INVALID_DATE);
	if (settlement >= maturity)
		_gx_function_error(GX_FN_ERR_SDT_GE_MDT);
	frequency = get_frequency(argv[3].val.number);
	if (argv->val.count == 4)
		basis = get_basis(argv[4].val.number);

	period = -(12 / frequency);
	for (i = 1; bs_date > settlement; i++)
		bs_date = _gx_edate(si, maturity, period * i);
	bs_date = _gx_edate(si, bs_date, 12 / frequency);
	_gx_decode_date(si, bs_date, &year, &mon, &day);
	if (day == 31)
		day--;
	op.val.number = (gxNumber) _gx_encode_date(si, year, mon, day);
	op.type = GX_NUMBER;
	return op;
}


gxOperand __cdecl _gx_fn_couppcd(gxOperand argv[])
{
	gxOperand op;
	int settlement,
		maturity,
		frequency,
		basis = 0,
		i;
	int year,
		mon,
		day,
		period,
		bs_date;
	int si = _gx_get_expr_si();

	if (argv->val.count < 3 || argv->val.count > 4)
		_gx_function_error(GX_FN_ERR_ARG_CNT_WRONG);
	for (i = 1; i < argv->val.count + 1; i++)
	{
		_gx_cvt2constant(argv + i);
		if (argv[i].type != GX_NUMBER)
			_gx_function_error(GX_FN_ERR_ARG_NUMERIC);
	}
	settlement = argv[1].val.number;
	maturity   = bs_date = argv[2].val.number;
	if (settlement <= 0 || settlement > 73050)
		_gx_function_error(GX_FN_ERR_INVALID_DATE);
	if (maturity <= 0 || maturity > 73050)
		_gx_function_error(GX_FN_ERR_INVALID_DATE);
	if (settlement >= maturity)
		_gx_function_error(GX_FN_ERR_SDT_GE_MDT);
	frequency = get_frequency(argv[3].val.number);
	if (argv->val.count == 4)
		basis = get_basis(argv[4].val.number);

	period = -(12 / frequency);
	for (i = 1; bs_date > settlement; i++)
		bs_date = _gx_edate(si, maturity, period * i);
	_gx_decode_date(si, bs_date, &year, &mon, &day);
	if (!basis && day == 31)
		day--;
	op.val.number = (gxNumber) _gx_encode_date(si, year, mon, day);
	op.type = GX_NUMBER;
	return op;
}


gxOperand __cdecl _gx_fn_coupnum(gxOperand argv[])
{
	gxOperand op;
	int settlement,
		maturity,
		frequency,
		basis = 0,
		i;

	if (argv->val.count < 3 || argv->val.count > 4)
		_gx_function_error(GX_FN_ERR_ARG_CNT_WRONG);
	for (i = 1; i < argv->val.count + 1; i++)
	{
		_gx_cvt2constant(argv + i);
		if (argv[i].type != GX_NUMBER)
			_gx_function_error(GX_FN_ERR_ARG_NUMERIC);
	}
	settlement = argv[1].val.number;
	maturity   = argv[2].val.number;
	if (settlement <= 0 || settlement > 73050)
		_gx_function_error(GX_FN_ERR_INVALID_DATE);
	if (maturity <= 0 || maturity > 73050)
		_gx_function_error(GX_FN_ERR_INVALID_DATE);
	if (settlement >= maturity)
		_gx_function_error(GX_FN_ERR_SDT_GE_MDT);
	frequency = get_frequency(argv[3].val.number);
	if (argv->val.count == 4)
		basis = get_basis(argv[4].val.number);
	op.val.number = (gxNumber) coupnum(settlement, maturity, frequency, basis);
	op.type = GX_NUMBER;
	return op;
}


gxNumber __cdecl _gx_after_first(int first, int settlement, int frequency, int basis)
{
	int date1 = 0,
		date2,
		i,
		period = 12 / frequency;
	gxNumber accrued,
			 cbase;
	int si = _gx_get_expr_si();

	date2 = _gx_edate(si, first, period);
	if (date2 >= settlement)
	{
		cbase = (basis ? date2 - first : 360.0 / frequency);
		accrued = (basis ? settlement - first : _gx_days360(si, first, settlement));
	}
	else
	{
		for (i = 2; settlement > date2; i++)
		{
			date1 = date2;
			date2 = _gx_edate(si, first, period * i);
		}
		cbase = (basis ? date2 - date1 : _gx_days360(si, date1, date2));
		accrued = (basis ? settlement - date1 : _gx_days360(si, date1, settlement));
	}
	return accrued / cbase;
}


gxNumber __cdecl _gx_before_first(int issue, int first, int settlement, int frequency, int basis)
{
	int date1,
		date2,
		i,
		period;
	gxNumber cbase,
			 accrued,
			 frac = 0;
	int si = _gx_get_expr_si();

	period = 12 / frequency;
	date1 = _gx_edate(si, first, -period);
	date2 = first;
	for (i = 2; date1 > settlement; i++)    /* if there are several coup
											 * periods */
		date1 = _gx_edate(si, first, -period * i);  /* bettween settle and
													 * firstcoup */
	date2 = _gx_edate(si, date1, period);
	cbase = (gxNumber) (basis ? date2 - date1 : 360.0 / frequency);
	if (issue >= date1)
	{
		accrued = (gxNumber) (basis ? (settlement - issue) : _gx_days360(si, issue, settlement));
		frac = accrued / cbase;
		return frac;
	}
	accrued = (gxNumber) (basis ? (settlement - date1) : _gx_days360(si, date1, settlement));
	frac += accrued / cbase;
	date2 = date1;
	date1 = _gx_edate(si, date2, -period);
	if (date1 > issue)
	{
		for (i = 2; date1 > issue; i++)
		{
			frac += 1;
			date1 = _gx_edate(si, date2, -period * i);
		}
		date2 = _gx_edate(si, date1, period);
	}
	cbase = (basis ? date2 - date1 : 360.0 / frequency);
	accrued = (basis ? (date2 - issue) : _gx_days360(si, issue, date2));
	frac += accrued / cbase;
	return frac;

}


gxNumber __cdecl _gx_do_accrint(int issue, int first, int settlement, int frequency, int basis, gxNumber coup_pmt)
{

	gxNumber frac;

	if (settlement > first)
		frac = _gx_after_first(first, settlement, frequency, basis);
	else
		frac = _gx_before_first(issue, first, settlement, frequency, basis);
	return frac * coup_pmt;
}


gxOperand __cdecl _gx_fn_accrint(gxOperand argv[])
{

	gxOperand op;
	int issue,
		first,
		settlement,
		frequency,
		basis = 0,
		i;
	gxNumber coup_rt,
			 coup_pmt,
			 par,
			 accrint;

	if (argv->val.count < 6 || argv->val.count > 7)
		_gx_function_error(GX_FN_ERR_ARG_CNT_WRONG);
	for (i = 1; i < argv->val.count + 1; i++)
	{
		_gx_cvt2constant(argv + i);
		if (argv[i].type != GX_NUMBER)
			_gx_function_error(GX_FN_ERR_ARG_NUMERIC);
		if (argv[i].val.number < 0)
			_gx_function_error(GX_FN_ERR_NEG_FINA_ARG);
	}
	issue = argv[1].val.number;
	first = argv[2].val.number;
	settlement = argv[3].val.number;
	coup_rt = argv[4].val.number;
	par = argv[5].val.number;
	frequency = get_frequency(argv[6].val.number);

	if (!GX_VALID_DT(issue) || !GX_VALID_DT(first) || !GX_VALID_DT(settlement))
		_gx_function_error(GX_FN_ERR_INVALID_DATE);
	if (settlement <= issue)
		_gx_function_error(GX_FN_ERR_SDT_GE_MDT);
	if (first <= issue)
		_gx_function_error(GX_FN_ERR_SDT_GE_MDT);   /* incorrect error */
	if (argv->val.count == 7)
		basis = get_basis(argv[7].val.number);
	coup_pmt = (par * coup_rt) / frequency;
	accrint = _gx_do_accrint(issue, first, settlement,
							 frequency, basis, coup_pmt);
	op.val.number = accrint;
	op.type = GX_NUMBER;
	return op;
}


gxOperand __cdecl _gx_fn_accrintm(gxOperand argv[])
{
	gxOperand op;
	gxNumber coup_rt,
			 coup_pmt,
			 yearfrac;
	int issue,
		settlement,
		par = 1000,
		basis = 0,
		i;

	if (argv->val.count < 4 || argv->val.count > 5)
		_gx_function_error(GX_FN_ERR_ARG_CNT_WRONG);
	for (i = 1; i < argv->val.count + 1; i++)
	{
		_gx_cvt2constant(argv + i);
		if (argv[i].type != GX_NUMBER)
			_gx_function_error(GX_FN_ERR_ARG_NUMERIC);
		if (argv[i].val.number < 0)
			_gx_function_error(GX_FN_ERR_NEG_FINA_ARG);
	}

	issue = argv[1].val.number;
	settlement = argv[2].val.number;
	coup_rt		= argv[3].val.number;
	par = argv[4].val.number;

	if (argv->val.count == 5)
		basis = get_basis(argv[5].val.number);

	if (!GX_VALID_DT(issue) || !GX_VALID_DT(settlement))
		_gx_function_error(GX_FN_ERR_INVALID_DATE);
	if (issue > settlement)
		_gx_function_error(GX_FN_ERR_IDT_GT_SDT);

	coup_pmt = par * coup_rt;
	_gx_find_yearfrac(_gx_get_expr_si(), issue, settlement, basis, &yearfrac);
	op.val.number = coup_pmt * yearfrac;
	op.type = GX_NUMBER;
	return op;
}


static gxNumber mon_pmt(gxNumber rate, gxNumber nper, gxNumber pv, gxNumber fv, int type)
{
	gxNumber r,
			 f,
			 mp1,
			 mp;

	r = pow(1 + rate, nper);
	f = rate / (r - 1);
	mp1 = (pv * r + fv) * f;
	if (type == 1)
		mp = mp1 / (1 + rate);
	else
		mp = mp1;
	return mp;
}


static gxNumber do_cumipmt(gxNumber rate, gxNumber nper, gxNumber pv, gxNumber start_per, gxNumber end_per, gxNumber fv, int type)
{
	gxNumber mp,
			 cumipmt = 0.0;
	int i;

	mp = mon_pmt(rate, nper, pv, fv, type);
	if (type == 1)
	{   /* special case for first per if type is 1 */
		pv -= mp;
		start_per--;
		end_per--;
	}
	for (i = 1; i < (end_per + 1); i++)
	{
		if (i >= start_per)
			cumipmt += pv * rate;
		pv -= mp - pv * rate;
	}
	return cumipmt;
}


static gxNumber do_cumprinc(gxNumber rate, gxNumber nper, gxNumber pv, gxNumber start_per, gxNumber end_per, gxNumber fv, int type)
{
	gxNumber mp,
			 mi,
			 cumprinc = 0.0;
	int i;

	mp = mon_pmt(rate, nper, pv, fv, type);
	for (i = 1; i < (end_per + 1); i++)
	{
		if (i == 1 && type == 1)
			mi = 0;
		else
			mi = pv * rate;
		if (i >= start_per)
			cumprinc = cumprinc + (mp - mi);
		pv -= mp - mi;
	}
	return cumprinc;
}

gxOperand __cdecl _gx_fn_cumipmt(gxOperand argv[])
{
	gxOperand op;
	gxNumber rate,
			 nper,
			 pv,
			 start_per,
			 end_per,
			 cumipmt = 0.0;
	int type = 0;
	register int i;

	if (argv->val.count != 6)
		_gx_function_error(GX_FN_ERR_ARG_CNT_WRONG);
	for (i = 1; i < 7; i++)
	{
		_gx_cvt2constant(argv + i);
		if (argv[i].type != GX_NUMBER)
			_gx_function_error(GX_FN_ERR_ARG_NUMERIC);
		if (argv[i].val.number < 0)
			_gx_function_error(GX_FN_ERR_NEG_FINA_ARG);
	}

	rate = argv[1].val.number;
	nper = argv[2].val.number;
	pv = argv[3].val.number;
	start_per = argv[4].val.number;
	end_per = argv[5].val.number;
	if (start_per < 1)
		_gx_function_error(GX_FN_ERR_SP_LS_1);
	if (end_per < 1)
		_gx_function_error(GX_FN_ERR_EP_LS_1);
	if (start_per > end_per)
		_gx_function_error(GX_FN_ERR_SP_GT_EP);
	if (argv[6].val.number != 0.0)
		type = 1;

	cumipmt = do_cumipmt(rate, nper, pv, start_per, end_per, 0.0, type);
	op.type = GX_NUMBER;
	op.val.number = cumipmt;
	return op;
}


gxOperand __cdecl _gx_fn_cumprinc(gxOperand argv[])
{
	gxOperand op;
	gxNumber rate,
			 nper,
			 pv,
			 start_per,
			 end_per,
			 cumprinc = 0.0;
	int type = 0;
	register int i;

	if (argv->val.count != 6)
		_gx_function_error(GX_FN_ERR_ARG_CNT_WRONG);
	for (i = 1; i < 7; i++)
	{
		_gx_cvt2constant(argv + i);
		if (argv[i].type != GX_NUMBER)
			_gx_function_error(GX_FN_ERR_ARG_NUMERIC);
		if (argv[i].val.number < 0)
			_gx_function_error(GX_FN_ERR_NEG_FINA_ARG);
	}
	rate = argv[1].val.number;
	nper = argv[2].val.number;
	pv = argv[3].val.number;
	start_per = argv[4].val.number;
	end_per = argv[5].val.number;

	if (start_per < 1)
		_gx_function_error(GX_FN_ERR_SP_LS_1);
	if (end_per < 1)
		_gx_function_error(GX_FN_ERR_EP_LS_1);
	if (start_per > end_per)
		_gx_function_error(GX_FN_ERR_SP_GT_EP);

	if (argv[6].val.number != 0.0)
		type = 1;
	cumprinc = do_cumprinc(rate, nper, pv, start_per, end_per, 0.0, type);
	op.type = GX_NUMBER;
	op.val.number = cumprinc;
	return op;
}


gxOperand __cdecl _gx_fn_ppmt(gxOperand argv[])
{
	gxOperand op;
	gxNumber rate,
			 per,
			 nper,
			 pv,
			 fv = 0.0,
			 ppmt;
	int i,
		type = 0;

	if (argv->val.count < 5 || argv->val.count > 6)
		_gx_function_error(GX_FN_ERR_ARG_CNT_WRONG);
	for (i = 1; i < argv->val.count + 1; i++)
	{
		_gx_cvt2constant(argv + i);
		if (argv[i].type != GX_NUMBER)
			_gx_function_error(GX_FN_ERR_ARG_NUMERIC);
		if (argv[i].val.number < 0)
			_gx_function_error(GX_FN_ERR_NEG_FINA_ARG);
	}

	rate = argv[1].val.number;
	per = argv[2].val.number;
	nper = argv[3].val.number;
	pv = argv[4].val.number;
	fv = argv[5].val.number;
	if (argv->val.count == 6)
		if (argv[6].val.number != 0.0)
			type = 1;

	ppmt = do_cumprinc(rate, nper, pv, per, per, fv, type);
	op.type = GX_NUMBER;
	op.val.number = ppmt;
	return op;
}

gxOperand __cdecl _gx_fn_ipmt(gxOperand argv[])
{
	gxOperand op;
	gxNumber rate,
			 per,
			 nper,
			 pv,
			 fv,
			 ipmt = 0.0;
	int i,
		type = 0;

	if (argv->val.count < 5 || argv->val.count > 6)
		_gx_function_error(GX_FN_ERR_ARG_CNT_WRONG);
	for (i = 1; i < argv->val.count + 1; i++)
	{
		_gx_cvt2constant(argv + i);
		if (argv[i].type != GX_NUMBER)
			_gx_function_error(GX_FN_ERR_ARG_NUMERIC);
		if (argv[i].val.number < 0)
			_gx_function_error(GX_FN_ERR_NEG_FINA_ARG);
	}

	rate = argv[1].val.number;
	per = argv[2].val.number;
	nper = argv[3].val.number;
	pv = argv[4].val.number;
	fv = argv[5].val.number;
	if (argv->val.count == 6)
		if (argv[6].val.number != 0.0)
			type = 1;

	ipmt = do_cumipmt(rate, nper, pv, per, per, fv, type);
	op.type = GX_NUMBER;
	op.val.number = ipmt;
	return op;
}


gxOperand __cdecl _gx_fn_db(gxOperand argv[])
{
	gxOperand op;
	gxNumber cost,
			 salvage,
			 life,
			 month = 0,
			 rate,
			 db = 0,
			 total_db = 0;
	int period,
		max_period,
		i;

	if (!(argv->val.count == 4 || argv->val.count == 5))
		_gx_function_error(GX_FN_ERR_ARG_CNT_WRONG);
	for (i = 1; i < argv->val.count + 1; i++)
	{
		_gx_cvt2constant(argv + i);
		if (argv[i].type != GX_NUMBER)
			_gx_function_error(GX_FN_ERR_IMPROP_ARG_TYPE);
		if (argv[i].val.number < 0)
			_gx_function_error(GX_FN_ERR_NEG_FINA_ARG);
	}

	cost	= argv[1].val.number;
	salvage = argv[2].val.number;
	life	= argv[3].val.number;
	period = argv[4].val.number;
	if (argv->val.count == 5)
		month = argv[5].val.number; /* need error handling for >12 */
	if (month == 0)
		max_period = life;
	else
		max_period = life + 1;

	if (max_period < period || period < 1)
		_gx_function_error(GX_FN_ERR_L_GE_P_GE_1);
	if (cost < salvage || salvage < 0.0)
		_gx_function_error(GX_FN_ERR_C_GE_S_GE_0);

	rate = 1 - pow(salvage / cost, 1 / life);
	rate = rate * 1000.0;
	if (rate < (double) floor(rate) + 0.5)  /* round to 3 decimal places, to  */
		rate = floor(rate) / 1000;  /* be consistent with Excel       */
	else
		rate = ceil(rate) / 1000;

	for (i = 1; i < max_period + 1; i++)
	{
		if (i == 1 && month != 0)
			db = cost * rate * (month / 12);
		else if (i == max_period && month != 0)
			db = (cost - total_db) * rate * ((12 - month) / 12);
		else
			db = (cost - total_db) * rate;
		if (i == period)
			break;
		total_db = total_db + db;
	}
	op.type = GX_NUMBER;
	op.val.number = db;
	return op;
}

/* double declining balance */
gxOperand __cdecl _gx_fn_vdb(gxOperand argv[])
{
	gxOperand op;
	gxNumber cost,
			 salvage,
			 ddb,
			 vdb = 0.0,
			 bv;
	int life,
		start_period,
		end_period,
		i;

	if (argv->val.count != 5)
		_gx_function_error(GX_FN_ERR_ARG_CNT_WRONG);
	for (i = 1; i < 6; i++)
	{
		_gx_cvt2constant(argv + i);
		if (argv[i].type != GX_NUMBER)
			_gx_function_error(GX_FN_ERR_ARG_NUMERIC);
		if (argv[i].val.number < 0)
			_gx_function_error(GX_FN_ERR_NEG_FINA_ARG);
	}

	cost = argv[1].val.number;
	salvage = argv[2].val.number;
	life = _gx_cvt2int(argv[3].val.number);
	start_period = _gx_cvt2int(argv[4].val.number);
	end_period = _gx_cvt2int(argv[5].val.number);

	if ((life < start_period || start_period < 0) ||
		(life < end_period || end_period < 0))
		_gx_function_error(GX_FN_ERR_L_GE_P_GE_1);
	if (start_period > end_period)
		_gx_function_error(GX_FN_ERR_SP_GT_EP);
	if (cost < salvage || salvage < 0.0)
		_gx_function_error(GX_FN_ERR_C_GE_S_GE_0);

	bv = cost;
	for (i = 0; i < end_period; i++)
	{
		ddb = GX_MAX(2.0 * bv / life, 0.0);
		if (i >= start_period)
			vdb += ddb;
		bv = GX_MAX(bv - ddb, salvage);
	}
	op.type = GX_NUMBER;
	op.val.number = vdb;
	return op;
}


gxOperand __cdecl _gx_fn_disc(gxOperand argv[])
{

	gxOperand op;
	gxNumber price,
			 redemption,
			 yearfrac,
			 pfrac;
	int settlement,
		maturity,
		basis = 0,
		i;

	if (argv->val.count < 4 || argv->val.count > 5)
		_gx_function_error(GX_FN_ERR_ARG_CNT_WRONG);
	for (i = 1; i < argv->val.count + 1; i++)
	{
		_gx_cvt2constant(argv + i);
		if (argv[i].type != GX_NUMBER)
			_gx_function_error(GX_FN_ERR_ARG_NUMERIC);
		if (argv[i].val.number < 0)
			_gx_function_error(GX_FN_ERR_NEG_FINA_ARG);
	}

	settlement = argv[1].val.number;
	maturity = argv[2].val.number;
	price		= argv[3].val.number;
	redemption = argv[4].val.number;
	if (argv->val.count == 5)
		basis = get_basis(argv[5].val.number);

	if (!GX_VALID_DT(settlement) || !GX_VALID_DT(maturity))
		_gx_function_error(GX_FN_ERR_INVALID_DATE);
	if (settlement >= maturity)
		_gx_function_error(GX_FN_ERR_SDT_GE_MDT);

	pfrac = price / redemption;
	_gx_find_yearfrac(_gx_get_expr_si(), settlement, maturity, basis, &yearfrac);
	op.val.number = (1 - pfrac) / yearfrac;
	op.type = GX_NUMBER;
	return op;
}


gxOperand __cdecl _gx_fn_dollarde(gxOperand argv[])
{
	gxOperand op;
	gxNumber dollar,
			 fraction,
			 s = 10.0,
			 df,
			 dw;

	if (argv->val.count != 2)
		_gx_function_error(GX_FN_ERR_ARG_CNT_WRONG);

	_gx_cvt2constant(argv + 1);
	_gx_cvt2constant(argv + 2);
	if (argv[1].type != GX_NUMBER || argv[2].type != GX_NUMBER)
		_gx_function_error(GX_FN_ERR_IMPROP_ARG_TYPE);
	if (argv[1].val.number <= 0 || argv[2].val.number <= 0)
		_gx_function_error(GX_FN_ERR_NEG_FINA_ARG);

	dollar = argv[1].val.number;
	fraction = (gxNumber) floor(argv[2].val.number);
	if (fraction <= 0)
		_gx_function_error(GX_FN_ERR_FRAC_LE_0);
	while (fraction > s)
		s *= 10.0;
	dw = floor(dollar);
	df = (dollar - dw) * s;
	op.type = GX_NUMBER;
	op.val.number = dw + df / fraction;
	return op;
}


gxOperand __cdecl _gx_fn_dollarfr(gxOperand argv[])
{
	gxOperand op;
	gxNumber dollar,
			 fraction,
			 s = 10.0,
			 df,
			 dw;

	if (argv->val.count != 2)
		_gx_function_error(GX_FN_ERR_ARG_CNT_WRONG);

	_gx_cvt2constant(argv + 1);
	_gx_cvt2constant(argv + 2);
	if (argv[1].type != GX_NUMBER || argv[2].type != GX_NUMBER)
		_gx_function_error(GX_FN_ERR_ARG_NUMERIC);
	if (argv[1].val.number <= 0 || argv[2].val.number <= 0)
		_gx_function_error(GX_FN_ERR_NEG_FINA_ARG);

	dollar = argv[1].val.number;
	fraction = (gxNumber) floor(argv[2].val.number);
	if (fraction <= 0)
		_gx_function_error(GX_FN_ERR_FRAC_LE_0);
	while (fraction > s)
		s *= 10.0;
	dw = floor(dollar);
	df = (dollar - dw) / s;
	op.type = GX_NUMBER;
	op.val.number = dw + df * fraction;
	return op;
}


gxNumber __cdecl _gx_duration(int settlement, int maturity, gxNumber coup_rt, gxNumber yield, int frequency, int basis)
{

	register int i;
	gxNumber cnum,
			 cdfrac,
			 cpmt;
	gxNumber pvcfi,
			 pvcf = 0.0,
			 pvtcf = 0.0,
			 pvwtcf = 0.0,
			 _gx_duration;

	cnum = coupnum(settlement, maturity, frequency, basis);
	cdfrac = (gxNumber) coupdaysnc(settlement, maturity, frequency, basis) /
		(gxNumber) coupdays(settlement, maturity, frequency, basis);
	cpmt = 100.0 * coup_rt / frequency;
	for (i = 0; i < cnum; i++)
	{
		pvcfi = 1.0 / pow(1.0 + yield / frequency, i + cdfrac);
		if (i == cnum - 1)
			pvcf = pvcfi * (cpmt + 100.0);
		else
			pvcf = pvcfi * cpmt;
		pvtcf += pvcf;  /* pvtcf: total present value */
		pvwtcf += pvcf * (i + cdfrac);  /* pvwtcf: weited total */
	}
	_gx_duration = (pvwtcf / pvtcf) / frequency;
	return _gx_duration;
}


gxOperand __cdecl _gx_fn_duration(gxOperand argv[])
{

	gxOperand op;
	register int i;
	int settlement,
		maturity,
		frequency,
		basis = 0;
	gxNumber coup_rt,
			 yield;

	if (argv->val.count < 5 || argv->val.count > 6)
		_gx_function_error(GX_FN_ERR_ARG_CNT_WRONG);
	for (i = 1; i < argv->val.count + 1; i++)
	{
		_gx_cvt2constant(argv + i);
		if (argv[i].type != GX_NUMBER)
			_gx_function_error(GX_FN_ERR_ARG_NUMERIC);
		if (argv[i].val.number < 0)
			_gx_function_error(GX_FN_ERR_NEG_FINA_ARG);
	}

	settlement = argv[1].val.number;
	maturity = argv[2].val.number;
	coup_rt		= argv[3].val.number;
	yield		= argv[4].val.number;
	frequency	= get_frequency(argv[5].val.number);

	if (argv->val.count == 6)
		basis = get_basis(argv[6].val.number);

	if (!GX_VALID_DT(settlement) || !GX_VALID_DT(maturity))
		_gx_function_error(GX_FN_ERR_INVALID_DATE);
	if (settlement >= maturity)
		_gx_function_error(GX_FN_ERR_SDT_GE_MDT);
	op.val.number =
		_gx_duration(settlement, maturity, coup_rt, yield, frequency, basis);
	op.type = GX_NUMBER;
	return op;
}


gxOperand __cdecl _gx_fn_mirr(gxOperand argv[])
{
#ifdef CELLRANGE
	gxOperand op;

	gxNumber x,
			 frate,
			 rrate,
			 ffactor,
			 rfactor,
			 mirr;
	gxNumber npv_pos = 0.0,
			 npv_neg = 0.0;
	int count = 0;
	gxScanBuf scan;
	gxCell *cp;

	if (argv->val.count != 3)
		_gx_function_error(GX_FN_ERR_ARG_CNT_WRONG);
	_gx_cvt2constant(argv + 2);
	_gx_cvt2constant(argv + 3);
	if (argv[2].type != GX_NUMBER || argv[3].type != GX_NUMBER)
		_gx_function_error(GX_FN_ERR_IMPROP_ARG_TYPE);;
	frate = argv[2].val.number;
	rrate = argv[3].val.number;
	ffactor = 1.0 / (1 + frate);
	rfactor = 1.0 / (1 + rrate);
	GX_HANDLE_OP_ERROR(argv[1]);
	if (argv[1].type != GX_RANGE)
		_gx_function_error(GX_FN_ERR_CF_RANGE);
	if (argv[1].val.range.r0 != argv[1].val.range.r1 &&
		argv[1].val.range.c0 != argv[1].val.range.c1)
		_gx_function_error(GX_FN_ERR_CF_COL_OR_ROW);
	_gx_init_range_scan(_gx_get_expr_si(), argv[1].val.range, &scan,
						GX_CONSTANT_LIST | GX_RECALC_LIST);
	while ((cp = _gx_do_range_scan(&scan)) != NULL)
	{
		if (_gx_fn_get_value(cp->row, cp->col, &x))
		{
			if (x < 0)
				npv_neg += x * ffactor;
			else
				npv_pos += x * rfactor;
			ffactor /= 1.0 + frate;
			rfactor /= 1.0 + rrate;
			count++;
		}
	}
	if (npv_pos == 0 || npv_neg == 0)
		_gx_function_error(GX_FN_ERR_MIRR_CF);
	mirr = -(npv_pos * pow(1.0 + rrate, (double) count)) / (npv_neg * (1 + frate));
	mirr = pow(mirr, 1.0 / ((gxNumber) count - 1)) - 1;
	op.type = GX_NUMBER;
	op.val.number = mirr;
	return op;
#else
	gxOperand op;
	op.type = GX_NUMBER;
	_gx_function_error(GX_FN_ERR_IMPROP_ARG_TYPE);
	return op;
#endif
}


gxOperand __cdecl _gx_fn_mduration(gxOperand argv[])
{
#ifdef CELLRANGE
	gxOperand op;
	register int i;
	int settlement,
		maturity,
		frequency,
		basis = 0;
	gxNumber coup_rt,
			 yield,
			 d;

	if (argv->val.count < 5 || argv->val.count > 6)
		_gx_function_error(GX_FN_ERR_ARG_CNT_WRONG);
	for (i = 1; i < argv->val.count + 1; i++)
	{
		_gx_cvt2constant(argv + i);
		if (argv[i].type != GX_NUMBER)
			_gx_function_error(GX_FN_ERR_ARG_NUMERIC);
		if (argv[i].val.number < 0)
			_gx_function_error(GX_FN_ERR_NEG_FINA_ARG);
	}

	settlement = argv[1].val.number;
	maturity = argv[2].val.number;
	coup_rt		= argv[3].val.number;
	yield		= argv[4].val.number;
	frequency	= get_frequency(argv[5].val.number);

	if (argv->val.count == 6)
		basis = get_basis(argv[6].val.number);

	if (!GX_VALID_DT(settlement) || !GX_VALID_DT(maturity))
		_gx_function_error(GX_FN_ERR_INVALID_DATE);
	if (settlement >= maturity)
		_gx_function_error(GX_FN_ERR_SDT_GE_MDT);
	d = _gx_duration(settlement, maturity, coup_rt, yield, frequency, basis);
	op.val.number = d / (1.0 + (yield / frequency));
	op.type = GX_NUMBER;
	return op;
#else
	gxOperand op;
	op.type = GX_NUMBER;
	_gx_function_error(GX_FN_ERR_IMPROP_ARG_TYPE);
	return op;
#endif
}


gxOperand __cdecl _gx_fn_fvschedule(gxOperand argv[])
{
#ifdef CELLRANGE
	gxOperand op;
	unsigned r,
		c;
	gxNumber principal,
			 s;

	if (argv->val.count != 2)
		_gx_function_error(GX_FN_ERR_ARG_CNT_WRONG);
	_gx_cvt2constant(argv + 1);
	GX_HANDLE_OP_ERROR(argv[2]);
	if (argv[1].type != GX_NUMBER)
		_gx_function_error(GX_FN_ERR_ARG_NUMERIC);
	principal = argv[1].val.number;
	switch (argv[2].type)
	{
	case GX_NUMBER:
		principal = principal * (1 + argv[2].val.number);
		break;
	case GX_CELL:
		_gx_cvt2constant(argv + 2);
		principal = principal * (1 + argv[2].val.number);
		break;
	case GX_RANGE:
		if (argv[2].val.range.r0 != argv[2].val.range.r1 &&
			argv[2].val.range.c0 != argv[2].val.range.c1)
			_gx_function_error(GX_FN_ERR_INTS_COL_OR_ROW);
		for (r = argv[2].val.range.r0; r <= argv[2].val.range.r1; r++)
			for (c = argv[2].val.range.c0; c <= argv[2].val.range.c1; c++)
				if (_gx_fn_get_value(r, c, &s))
					principal = principal * (1 + s);
		break;
	default:
		_gx_function_error(GX_FN_ERR_ARG_NUMERIC);
		break;
	}
	op.type = GX_NUMBER;
	op.val.number = principal;
	return op;
#else
	gxOperand op;
	op.type = GX_NUMBER;
	_gx_function_error(GX_FN_ERR_IMPROP_ARG_TYPE);
	return op;
#endif
}


gxOperand __cdecl _gx_fn_effect(gxOperand argv[])
{
#ifdef CELLRANGE
	gxOperand op;
	gxNumber nominal_rate,
			 npery,
			 effective_rate;

	if (argv->val.count != 2)
		_gx_function_error(GX_FN_ERR_ARG_CNT_WRONG);

	_gx_cvt2constant(argv + 1);
	_gx_cvt2constant(argv + 2);
	if (argv[1].type != GX_NUMBER || argv[2].type != GX_NUMBER)
		_gx_function_error(GX_FN_ERR_IMPROP_ARG_TYPE);

	nominal_rate = argv[1].val.number;
	if (nominal_rate <= 0)
		_gx_function_error(GX_FN_ERR_INTR_LE_0);
	npery = argv[2].val.number;
	if (npery < 1)
		_gx_function_error(GX_FN_ERROR_NPERY_LS_1);
	effective_rate = pow(1 + nominal_rate / npery, npery) - 1;
	op.type = GX_NUMBER;
	op.val.number = effective_rate;
	return op;
#else
	gxOperand op;
	op.type = GX_NUMBER;
	_gx_function_error(GX_FN_ERR_IMPROP_ARG_TYPE);
	return op;
#endif
}


gxOperand __cdecl _gx_fn_nominal(gxOperand argv[])
{
#ifdef CELLRANGE
	gxOperand op;
	gxNumber effective_rate,
			 npery,
			 nominal_rate;

	if (argv->val.count != 2)
		_gx_function_error(GX_FN_ERR_ARG_CNT_WRONG);

	_gx_cvt2constant(argv + 1);
	_gx_cvt2constant(argv + 2);
	if (argv[1].type != GX_NUMBER || argv[2].type != GX_NUMBER)
		_gx_function_error(GX_FN_ERR_ARG_NUMERIC);

	effective_rate = argv[1].val.number;
	if (effective_rate <= 0)
		_gx_function_error(GX_FN_ERR_INTR_LE_0);
	npery = argv[2].val.number;
	if (npery < 1)
		_gx_function_error(GX_FN_ERROR_NPERY_LS_1);
	nominal_rate = (pow(1 + effective_rate, 1 / npery) - 1) * npery;
	op.type = GX_NUMBER;
	op.val.number = nominal_rate;
	return op;
#else
	gxOperand op;
	op.type = GX_NUMBER;
	_gx_function_error(GX_FN_ERR_IMPROP_ARG_TYPE);
	return op;
#endif
}


gxOperand __cdecl _gx_fn_intrate(gxOperand argv[])
{
#ifdef CELLRANGE
	gxOperand op;
	gxNumber investment,
			 redemption,
			 intrate,
			 year_frac;
	int settlement,
		maturity,
		basis = 0,
		i;


	if (argv->val.count < 4 || argv->val.count > 5)
		_gx_function_error(GX_FN_ERR_ARG_CNT_WRONG);
	for (i = 1; i < argv->val.count + 1; i++)
	{
		_gx_cvt2constant(argv + i);
		if (argv[i].type != GX_NUMBER)
			_gx_function_error(GX_FN_ERR_ARG_NUMERIC);
		if (argv[i].val.number < 0)
			_gx_function_error(GX_FN_ERR_NEG_FINA_ARG);
	}
	if (argv->val.count == 5)
		basis = get_basis(argv[5].val.number);

	settlement = (gxNumber) floor(argv[1].val.number);
	maturity = (gxNumber) floor(argv[2].val.number);
	investment	= argv[3].val.number;
	redemption	= argv[4].val.number;
	if (!GX_VALID_DT(settlement) || !GX_VALID_DT(maturity))
		_gx_function_error(GX_FN_ERR_INVALID_DATE);

	_gx_find_yearfrac(_gx_get_expr_si(), settlement, maturity, basis, &year_frac);
	intrate = ((redemption - investment) / investment) / year_frac;
	op.type = GX_NUMBER;
	op.val.number = intrate;
	return op;
#else
	gxOperand op;
	op.type = GX_NUMBER;
	_gx_function_error(GX_FN_ERR_IMPROP_ARG_TYPE);
	return op;
#endif
}


gxNumber __cdecl _gx_do_price(gxNumber pmt, gxNumber yield, gxNumber redemption, int frequency, int cdnum, gxNumber cdfrac, gxNumber accrint)
{

	gxNumber coef = 0,
			 coef_n,
			 price;
	register int i;

	for (i = 0; i < cdnum; i++)
		coef += 1 / pow(1.0 + yield / frequency, i + cdfrac);
	coef_n = 1 / pow(1.0 + yield / frequency, cdnum - 1 + cdfrac);
	price = pmt * coef + redemption * coef_n - accrint;
	return price;
}


gxOperand __cdecl _gx_fn_price(gxOperand argv[])
{

	gxOperand op;
	gxNumber price,
			 coup_rt,
			 yield,
			 redemption,
			 pmt,
			 accrint,
			 cdfrac;
	int settlement,
		maturity,
		frequency,
		basis = 0;
	int cdnum,
		cpdays,
		cdnc,
		cdpc;
	register int i;

	if (argv->val.count < 6 || argv->val.count > 7)
		_gx_function_error(GX_FN_ERR_ARG_CNT_WRONG);
	for (i = 1; i < argv->val.count + 1; i++)
	{
		_gx_cvt2constant(argv + i);
		if (argv[i].type != GX_NUMBER)
			_gx_function_error(GX_FN_ERR_ARG_NUMERIC);
		if (argv[i].val.number < 0)
			_gx_function_error(GX_FN_ERR_NEG_FINA_ARG);
	}

	settlement = argv[1].val.number;
	maturity = argv[2].val.number;
	coup_rt		= argv[3].val.number;
	yield		= argv[4].val.number;
	redemption	= argv[5].val.number;
	frequency	= get_frequency(argv[6].val.number);

	if (argv->val.count == 7)
		basis = get_basis(argv[7].val.number);

	if (!GX_VALID_DT(settlement) || !GX_VALID_DT(maturity))
		_gx_function_error(GX_FN_ERR_INVALID_DATE);
	if (settlement >= maturity)
		_gx_function_error(GX_FN_ERR_SDT_GE_MDT);

	cdnum = coupnum(settlement, maturity, frequency, basis);
	cdnc = coupdaysnc(settlement, maturity, frequency, basis);
	cdpc = coupdaybs(settlement, maturity, frequency, basis);
	cpdays = coupdays(settlement, maturity, frequency, basis);
	cdfrac = (gxNumber) cdnc / (gxNumber) cpdays;
	pmt = (100.0 * coup_rt) / frequency;
	accrint = pmt * ((gxNumber) cdpc) / (gxNumber) cpdays;
	price =
		_gx_do_price(pmt, yield, redemption, frequency, cdnum, cdfrac, accrint);
	op.val.number = price;
	op.type = GX_NUMBER;
	return op;
}


gxOperand __cdecl _gx_fn_pricedisc(gxOperand argv[])
{

	gxOperand op;
	gxNumber discount,
			 redemption,
			 yearfrac;
	int settlement,
		maturity,
		basis = 0,
		i;

	if (argv->val.count < 4 || argv->val.count > 5)
		_gx_function_error(GX_FN_ERR_ARG_CNT_WRONG);
	for (i = 1; i < argv->val.count + 1; i++)
	{
		_gx_cvt2constant(argv + i);
		if (argv[i].type != GX_NUMBER)
			_gx_function_error(GX_FN_ERR_ARG_NUMERIC);
		if (argv[i].val.number < 0)
			_gx_function_error(GX_FN_ERR_NEG_FINA_ARG);
	}

	settlement = argv[1].val.number;
	maturity = argv[2].val.number;
	discount	= argv[3].val.number;
	redemption	= argv[4].val.number;

	if (argv->val.count == 5)
		basis = get_basis(argv[5].val.number);

	if (!GX_VALID_DT(settlement) || !GX_VALID_DT(maturity))
		_gx_function_error(GX_FN_ERR_INVALID_DATE);
	if (settlement >= maturity)
		_gx_function_error(GX_FN_ERR_SDT_GE_MDT);

	_gx_find_yearfrac(_gx_get_expr_si(), settlement, maturity, basis, &yearfrac);
	op.val.number = redemption * (1 - discount * yearfrac);
	op.type = GX_NUMBER;
	return op;
}


gxOperand __cdecl _gx_fn_pricemat(gxOperand argv[])
{

	gxOperand op;
	gxNumber coup_rt,
			 yield,
			 fracis,
			 fracim,
			 fracsm;
	int settlement,
		maturity,
		issue,
		basis = 0;
	register int i;
	int si = _gx_get_expr_si();

	if (argv->val.count < 5 || argv->val.count > 6)
		_gx_function_error(GX_FN_ERR_ARG_CNT_WRONG);
	for (i = 1; i < argv->val.count + 1; i++)
	{
		_gx_cvt2constant(argv + i);
		if (argv[i].type != GX_NUMBER)
			_gx_function_error(GX_FN_ERR_ARG_NUMERIC);
		if (argv[i].val.number < 0)
			_gx_function_error(GX_FN_ERR_NEG_FINA_ARG);
	}

	settlement = argv[1].val.number;
	maturity = argv[2].val.number;
	issue = argv[3].val.number;
	coup_rt		= argv[4].val.number;
	yield		= argv[5].val.number;

	if (argv->val.count == 6)
		basis = get_basis(argv[6].val.number);

	if (!GX_VALID_DT(settlement) || !GX_VALID_DT(maturity) || !GX_VALID_DT(issue))
		_gx_function_error(GX_FN_ERR_INVALID_DATE);
	if (settlement >= maturity)
		_gx_function_error(GX_FN_ERR_SDT_GE_MDT);
	if (issue > settlement)
		_gx_function_error(GX_FN_ERR_IDT_GT_SDT);

	_gx_find_yearfrac(si, issue, settlement, basis, &fracis);
	_gx_find_yearfrac(si, issue, maturity, basis, &fracim);
	_gx_find_yearfrac(si, settlement, maturity, basis, &fracsm);
	op.val.number = ((100 + fracim * coup_rt * 100) / (1 + fracsm * yield)) -
		(fracis * coup_rt * 100);
	op.type = GX_NUMBER;
	return op;
}


gxNumber __cdecl _gx_do_oddfprice(gxNumber pmt, gxNumber pmt1, gxNumber pmtn, gxNumber yield, gxNumber redemption, int frequency, int cdnum, gxNumber cdfrac, gxNumber accrint, int longflag)
{

	gxNumber coef = 0,
			 coef_1,
			 coef_n,
			 price;
	register int i;

	if (!longflag)
		cdnum--;
	for (i = 1; i < cdnum; i++)
		coef += 1 / pow(1.0 + yield / frequency, i + cdfrac);
	coef_1 = 1 / pow(1.0 + yield / frequency, cdfrac);
	coef_n = 1 / pow(1.0 + yield / frequency, cdnum + cdfrac);

	price = (pmt1 * coef_1 + pmt * coef + pmtn * coef_n + redemption * coef_n);
	price = price - accrint;
	return price;
}


static gxNumber oddfpmt(int issue, int first, int /*settlement*/, gxNumber pmt, int frequency, int b)
{
	int d1,
		d2;
	gxNumber pmt1 = 0;
	int si = _gx_get_expr_si();

	d1 = _gx_edate(si, first, -12 / frequency);
	d2 = first;
	while (1)
	{
		if (d1 <= issue)
		{
			pmt1 += pmt * (gxNumber) days(issue, d2, b) / days(d1, d2, b);
			break;
		}
		else
		{
			pmt1 += pmt;
			d2 = d1;
			d1 = _gx_edate(si, d1, -12 / frequency);
		}
	}
	return pmt1;
}

static int coupnumwf(int settlement, int first, int frequency, int /*basis*/)
{

	int period,
		dt;
	register int i;

	if (settlement > first)
		return 0;
	dt = first;
	period = -(12 / frequency);
	for (i = 1; dt > settlement; i++)
		dt = _gx_edate(_gx_get_expr_si(), first, period * i);
	if (dt < settlement)
		i--;
	return (i - 1);
}

gxOperand __cdecl _gx_fn_oddfprice(gxOperand argv[])
{

	gxOperand op;
	gxNumber price,
			 coup_rt,
			 yield,
			 redemption,
			 cdfrac,
			 pmt,
			 pmt1,
			 accrint;
	int settlement,
		maturity,
		issue,
		fcoup,
		frequency,
		basis = 0;
	long cpdays,
		fcoupdays,
		cdnum,
		longflag = 0;
	register int i;
	int si = _gx_get_expr_si();

	if (argv->val.count < 8 || argv->val.count > 9)
		_gx_function_error(GX_FN_ERR_ARG_CNT_WRONG);
	for (i = 1; i < argv->val.count + 1; i++)
	{
		_gx_cvt2constant(argv + i);
		if (argv[i].type != GX_NUMBER)
			_gx_function_error(GX_FN_ERR_ARG_NUMERIC);
		if (argv[i].val.number < 0)
			_gx_function_error(GX_FN_ERR_NEG_FINA_ARG);
	}
	settlement = argv[1].val.number;
	maturity = argv[2].val.number;
	issue = argv[3].val.number;
	fcoup = argv[4].val.number;
	coup_rt		= argv[5].val.number;
	yield		= argv[6].val.number;
	redemption	= argv[7].val.number;
	frequency	= get_frequency(argv[8].val.number);
	if (argv->val.count == 9)
		basis = get_basis(argv[9].val.number);
	if (!GX_VALID_DT(settlement) || !GX_VALID_DT(maturity) ||
		!GX_VALID_DT(issue) || !GX_VALID_DT(fcoup))
		_gx_function_error(GX_FN_ERR_INVALID_DATE);
	if (issue > settlement)
		_gx_function_error(GX_FN_ERR_IDT_GT_SDT);
	if (settlement >= maturity)
		_gx_function_error(GX_FN_ERR_SDT_GE_MDT);
	if (!(issue < fcoup && fcoup < maturity))
		_gx_function_error(GX_FN_ERR_ODD1);

	cpdays = coupdays(settlement, maturity, frequency, basis);
	cdfrac = (gxNumber) coupdaysnc(settlement, maturity, frequency, basis) / cpdays;
	if (_gx_edate(si, fcoup, -12 / frequency) > issue)
	{
		longflag = 1;
		cdnum = coupnum(fcoup, maturity, frequency, basis);
		cdfrac += coupnumwf(settlement, fcoup, frequency, basis);
	}
	else
		cdnum = coupnum(settlement, maturity, frequency, basis);
	pmt = (100.0 * coup_rt) / frequency;
	fcoupdays = (basis ? fcoup - issue : _gx_days360(si, issue, fcoup));
	pmt1 = oddfpmt(issue, fcoup, settlement, pmt, frequency, basis);
	accrint = _gx_do_accrint(issue, fcoup, settlement, frequency, basis, pmt);
	price = _gx_do_oddfprice(pmt, pmt1, pmt, yield, redemption, frequency,
							 cdnum, cdfrac, accrint, longflag);
	op.val.number = price;
	op.type = GX_NUMBER;
	return op;
}


gxOperand __cdecl _gx_fn_oddfyield(gxOperand argv[])
{

	gxOperand op;
	gxNumber price,
			 coup_rt,
			 price_new,
			 redemption,
			 cdfrac,
			 pmt,
			 pmt1;
	gxNumber fcoupdays,
			 accrint,
			 yld1 = 0.0,
			 yld2,
			 yld3 = 0.0;
	int settlement,
		maturity,
		issue,
		fcoup,
		frequency,
		basis = 0;
	int cdnum,
		cpdays,
		longflag = 0;
	register int i;
	int si = _gx_get_expr_si();

	if (argv->val.count < 8 || argv->val.count > 9)
		_gx_function_error(GX_FN_ERR_ARG_CNT_WRONG);
	for (i = 1; i < argv->val.count + 1; i++)
	{
		_gx_cvt2constant(argv + i);
		if (argv[i].type != GX_NUMBER)
			_gx_function_error(GX_FN_ERR_ARG_NUMERIC);
		if (argv[i].val.number < 0)
			_gx_function_error(GX_FN_ERR_NEG_FINA_ARG);
	}

	settlement = argv[1].val.number;
	maturity = argv[2].val.number;
	issue = argv[3].val.number;
	fcoup = argv[4].val.number;
	coup_rt		= argv[5].val.number;
	price		= argv[6].val.number;
	redemption	= argv[7].val.number;
	frequency	= get_frequency(argv[8].val.number);

	if (argv->val.count == 9)
		basis = get_basis(argv[9].val.number);
	if (!GX_VALID_DT(settlement) || !GX_VALID_DT(maturity) ||
		!GX_VALID_DT(issue) || !GX_VALID_DT(fcoup))
		_gx_function_error(GX_FN_ERR_INVALID_DATE);
	if (issue > settlement)
		_gx_function_error(GX_FN_ERR_IDT_GT_SDT);
	if (settlement >= maturity)
		_gx_function_error(GX_FN_ERR_SDT_GE_MDT);
	if (!(issue < fcoup && fcoup < maturity))
		_gx_function_error(GX_FN_ERR_ODD1);

	cpdays = coupdays(settlement, maturity, frequency, basis);
	cdfrac = (gxNumber) coupdaysnc(settlement, maturity, frequency, basis) / cpdays;
	if (_gx_edate(si, fcoup, -12 / frequency) > issue)
	{
		longflag = 1;
		cdnum = coupnum(fcoup, maturity, frequency, basis);
		cdfrac += coupnumwf(settlement, fcoup, frequency, basis);
	}
	else
		cdnum = coupnum(settlement, maturity, frequency, basis);
	pmt = (100.0 * coup_rt) / frequency;
	fcoupdays = (basis ? fcoup - issue : _gx_days360(si, issue, fcoup));
	pmt1 = oddfpmt(issue, fcoup, settlement, pmt, frequency, basis);
	accrint = _gx_do_accrint(issue, fcoup, settlement, frequency, basis, pmt);
	do
	{   /* make sure yld3 is the "ceiling" */
		yld3 += 0.05;
		price_new = _gx_do_oddfprice(pmt, pmt1, pmt, yld3, redemption,
							   frequency, cdnum, cdfrac, accrint, longflag);
	} while (price_new > price);

	if (fabs(price - price_new) < 1.0e-8)
	{   /* if we are really lucky today */
		op.type = GX_NUMBER;
		op.val.number = yld3;
		return op;
	}
	yld2 = (yld1 + yld3) / 2.0;
	for (i = 0; i < MAX_IT; i++)
	{
		price_new =
			_gx_do_oddfprice(pmt, pmt1, pmt, yld2, redemption, frequency,
							 cdnum, cdfrac, accrint, longflag);
		if (fabs(price - price_new) < 1.0e-8)
			break;
		if (price_new < price)  /* need to lower the yield */
			yld3 = yld2;
		else
			yld1 = yld2;    /* need to raise the yield */
		yld2 = (yld1 + yld3) / 2.0;
	}
	op.type = GX_NUMBER;
	op.val.number = yld2;
	return op;
}


gxNumber __cdecl _gx_do_oddlprice(gxNumber pmt, gxNumber pmtn, gxNumber yield, gxNumber redemption, int frequency, int cdnum, gxNumber cdfrac, gxNumber cdfracn, gxNumber accrint)
{

	gxNumber coef = 0,
			 coef_n,
			 price;
	register int i;

	for (i = 0; i < cdnum - 1; i++)
		coef += 1 / pow(1.0 + yield / frequency, i + cdfrac);
	coef_n = 1 / pow(1.0 + yield / frequency, cdnum - 1 + cdfracn);

	price = (pmt * coef + pmtn * coef_n + redemption * coef_n);
	price = price - accrint;
	return price;
}

static gxNumber cpnum_oddl(int last, int maturity, int frequency, int b)
{

	int period,
		d1,
		d2;
	gxNumber count = 0.0;
	int si = _gx_get_expr_si();

	d1 = last;
	period = 12 / frequency;
	while (1)
	{
		d2 = _gx_edate(si, d1, period * ((int) count + 1));
		if (d2 >= maturity)
		{
			d1 = _gx_edate(si, d2, -period);
			count += (gxNumber) days(d1, maturity, b) / days(d1, d2, b);
			break;
		}
		else
			count++;
	}
	return count;
}


// _gx_fn_oddlprice did not validate with the sample
// data. Therefore I removed it from the keyword table.

gxOperand __cdecl _gx_fn_oddlprice(gxOperand argv[])
{

	gxOperand op;
	gxNumber price,
			 coup_rt,
			 yield,
			 redemption,
			 cdfrac,
			 cdfracn;
	gxNumber pmt,
			 pmtn,
			 cdnumlcp,
			 accrint;
	int settlement,
		maturity,
		lcoup,
		frequency,
		basis = 0;
	int cpdays,
		cdnum;
	register int i;

	if (argv->val.count < 7 || argv->val.count > 8)
		_gx_function_error(GX_FN_ERR_ARG_CNT_WRONG);
	for (i = 1; i < argv->val.count + 1; i++)
	{
		_gx_cvt2constant(argv + i);
		if (argv[i].type != GX_NUMBER)
			_gx_function_error(GX_FN_ERR_ARG_NUMERIC);
		if (argv[i].val.number < 0)
			_gx_function_error(GX_FN_ERR_NEG_FINA_ARG);
	}
	settlement = argv[1].val.number;
	maturity = argv[2].val.number;
	lcoup = argv[3].val.number;
	coup_rt		= argv[4].val.number;
	yield		= argv[5].val.number;
	redemption	= argv[6].val.number;
	frequency	= get_frequency(argv[7].val.number);
	if (argv->val.count == 8)
		basis = get_basis(argv[8].val.number);
	if (!GX_VALID_DT(settlement) || !GX_VALID_DT(maturity) || !GX_VALID_DT(lcoup))
		_gx_function_error(GX_FN_ERR_INVALID_DATE);
	if (settlement >= maturity)
		_gx_function_error(GX_FN_ERR_SDT_GE_MDT);
	if (lcoup >= maturity)
		_gx_function_error(GX_FN_ERR_ODD2);

	cdnum = coupnum(settlement, lcoup, frequency, basis);
	cpdays = coupdays(settlement, maturity, frequency, basis);
	cdfrac = (gxNumber) coupdaysnc(settlement, lcoup, frequency, basis) / cpdays;
	cdnumlcp = cpnum_oddl(lcoup, maturity, frequency, basis);
	cdfracn = cdfrac + cdnumlcp;
	pmt = (100.0 * coup_rt) / frequency;
	pmtn = cdnumlcp * pmt;
	accrint = pmt * ((gxNumber) coupdaybs(settlement, lcoup, frequency, basis) /
					 coupdays(settlement, lcoup, frequency, basis));
	price = _gx_do_oddlprice(pmt, pmtn, yield, redemption, frequency, cdnum,
							 cdfrac, cdfracn, accrint);
	op.val.number = price;
	op.type = GX_NUMBER;
	return op;
}

// _gx_fn_oddlyield did not validate with the sample
// data. Therefore I removed it from the keyword table.

gxOperand __cdecl _gx_fn_oddlyield(gxOperand argv[])
{

	gxOperand op;
	gxNumber price,
			 coup_rt,
			 redemption,
			 cdfrac,
			 cdfracn;
	gxNumber pmt,
			 pmtn,
			 cdnumlcp,
			 accrint,
			 price_new,
			 yld1 = 0.0,
			 yld2,
			 yld3 = 0.0;
	int settlement,
		maturity,
		lcoup,
		frequency,
		basis = 0;
	int cpdays,
		cdnum;
	register int i;

	if (argv->val.count < 7 || argv->val.count > 8)
		_gx_function_error(GX_FN_ERR_ARG_CNT_WRONG);
	for (i = 1; i < argv->val.count + 1; i++)
	{
		_gx_cvt2constant(argv + i);
		if (argv[i].type != GX_NUMBER)
			_gx_function_error(GX_FN_ERR_ARG_NUMERIC);
		if (argv[i].val.number < 0)
			_gx_function_error(GX_FN_ERR_NEG_FINA_ARG);
	}
	settlement = argv[1].val.number;
	maturity = argv[2].val.number;
	lcoup = argv[3].val.number;
	coup_rt		= argv[4].val.number;
	price		= argv[5].val.number;
	redemption	= argv[6].val.number;
	frequency	= get_frequency(argv[7].val.number);
	if (argv->val.count == 8)
		basis = get_basis(argv[8].val.number);
	if (!GX_VALID_DT(settlement) || !GX_VALID_DT(maturity) || !GX_VALID_DT(lcoup))
		_gx_function_error(GX_FN_ERR_INVALID_DATE);
	if (settlement >= maturity)
		_gx_function_error(GX_FN_ERR_SDT_GE_MDT);
	if (lcoup >= maturity)
		_gx_function_error(GX_FN_ERR_ODD1);
	cdnum = coupnum(settlement, lcoup, frequency, basis);
	cpdays = coupdays(settlement, maturity, frequency, basis);
	cdfrac = (gxNumber) coupdaysnc(settlement, lcoup, frequency, basis) / cpdays;
	cdnumlcp = cpnum_oddl(lcoup, maturity, frequency, basis);
	cdfracn = cdfrac + cdnumlcp;
	pmt = (100.0 * coup_rt) / frequency;
	pmtn = cdnumlcp * pmt;
	accrint = pmt * ((gxNumber) coupdaybs(settlement, lcoup, frequency, basis) /
					 coupdays(settlement, lcoup, frequency, basis));
	do
	{   /* make sure yld3 is the "ceiling" */
		yld3 += 0.05;
		price_new = _gx_do_oddlprice(pmt, pmtn, yld3, redemption, frequency,
									 cdnum, cdfrac, cdfracn, accrint);
	} while (price_new > price);

	if (fabs(price - price_new) < 1.0e-8)
	{   /* if we are really lucky today */
		op.type = GX_NUMBER;
		op.val.number = yld3;
		return op;
	}
	yld2 = (yld1 + yld3) / 2.0;
	for (i = 0; i < MAX_IT; i++)
	{
		price_new = _gx_do_oddlprice(pmt, pmtn, yld2, redemption, frequency,
									 cdnum, cdfrac, cdfracn, accrint);
		if (fabs(price - price_new) < 1.0e-8)
			break;
		if (price_new < price)  /* need to lower the yield */
			yld3 = yld2;
		else
			yld1 = yld2;    /* need to raise the yield */
		yld2 = (yld1 + yld3) / 2.0;
	}
	op.type = GX_NUMBER;
	op.val.number = yld2;
	return op;
}


gxOperand __cdecl _gx_fn_received(gxOperand argv[])
{

	gxOperand op;
	gxNumber investment,
			 discount,
			 yearfrac;
	int settlement,
		maturity,
		basis = 0,
		i;

	if (argv->val.count < 4 || argv->val.count > 5)
		_gx_function_error(GX_FN_ERR_ARG_CNT_WRONG);
	for (i = 1; i < argv->val.count + 1; i++)
	{
		_gx_cvt2constant(argv + i);
		if (argv[i].type != GX_NUMBER)
			_gx_function_error(GX_FN_ERR_ARG_NUMERIC);
		if (argv[i].val.number < 0)
			_gx_function_error(GX_FN_ERR_NEG_FINA_ARG);
	}

	settlement = argv[1].val.number;
	maturity = argv[2].val.number;
	investment	= argv[3].val.number;
	discount	= argv[4].val.number;
	if (argv->val.count == 5)
		basis = get_basis(argv[5].val.number);

	if (!GX_VALID_DT(settlement) || !GX_VALID_DT(maturity))
		_gx_function_error(GX_FN_ERR_INVALID_DATE);
	if (settlement >= maturity)
		_gx_function_error(GX_FN_ERR_SDT_GE_MDT);

	_gx_find_yearfrac(_gx_get_expr_si(), settlement, maturity, basis, &yearfrac);
	op.val.number = investment / (1.0 - discount * yearfrac);
	op.type = GX_NUMBER;
	return op;
}


gxOperand __cdecl _gx_fn_tbilleq(gxOperand argv[])
{

	gxOperand op;
	gxNumber discount,
			 yearfrac,
			 factor;
	int settlement,
		maturity,
		i;
	int si = _gx_get_expr_si();

	if (argv->val.count != 3)
		_gx_function_error(GX_FN_ERR_ARG_CNT_WRONG);
	for (i = 1; i < argv->val.count + 1; i++)
	{
		_gx_cvt2constant(argv + i);
		if (argv[i].type != GX_NUMBER)
			_gx_function_error(GX_FN_ERR_ARG_NUMERIC);
	}

	settlement = argv[1].val.number;
	maturity = argv[2].val.number;
	discount	= argv[3].val.number;
	if (!GX_VALID_DT(settlement) || !GX_VALID_DT(maturity))
		_gx_function_error(GX_FN_ERR_INVALID_DATE);
	if (settlement >= maturity)
		_gx_function_error(GX_FN_ERR_SDT_GE_MDT);
	if (_gx_edate(si, settlement, 12) < maturity)
		_gx_function_error(GX_FN_ERR_INVALID_TBILL);

	_gx_find_yearfrac(_gx_get_expr_si(), settlement, maturity, 2, &yearfrac);
	factor = 1 / (1 - discount * yearfrac);
	if (_gx_edate(si, settlement, 6) > maturity)
		op.val.number = discount * factor * (365.0 / 360.0);
	else
		op.val.number = 2 * (pow(factor, 182.5 / (maturity - settlement)) - 1);
	op.type = GX_NUMBER;
	return op;
}

// _gx_fn_tbillprice did not validate with the sample
// data. Therefore I removed it from the keyword table.

gxOperand __cdecl _gx_fn_tbillprice(gxOperand argv[])
{

	gxOperand op;
	gxNumber discount,
			 yearfrac;
	int settlement,
		maturity,
		i;

	if (argv->val.count != 3)
		_gx_function_error(GX_FN_ERR_ARG_CNT_WRONG);
	for (i = 1; i < argv->val.count + 1; i++)
	{
		_gx_cvt2constant(argv + i);
		if (argv[i].type != GX_NUMBER)
			_gx_function_error(GX_FN_ERR_ARG_NUMERIC);
	}

	settlement = argv[1].val.number;
	maturity = argv[2].val.number;
	discount	= argv[3].val.number;
	if (!GX_VALID_DT(settlement) || !GX_VALID_DT(maturity))
		_gx_function_error(GX_FN_ERR_INVALID_DATE);
	if (settlement >= maturity)
		_gx_function_error(GX_FN_ERR_SDT_GE_MDT);
	if (_gx_edate(_gx_get_expr_si(), settlement, 12) < maturity)
		_gx_function_error(GX_FN_ERR_INVALID_TBILL);

	_gx_find_yearfrac(_gx_get_expr_si(), settlement, maturity, 2, &yearfrac);
	op.val.number = 100.0 * (1 - discount * yearfrac);
	op.type = GX_NUMBER;
	return op;
}



gxOperand __cdecl _gx_fn_tbillyield(gxOperand argv[])
{

	gxOperand op;
	gxNumber price,
			 yearfrac;
	int settlement,
		maturity,
		i;

	if (argv->val.count != 3)
		_gx_function_error(GX_FN_ERR_ARG_CNT_WRONG);
	for (i = 1; i < argv->val.count + 1; i++)
	{
		_gx_cvt2constant(argv + i);
		if (argv[i].type != GX_NUMBER)
			_gx_function_error(GX_FN_ERR_ARG_NUMERIC);
	}

	settlement = argv[1].val.number;
	maturity = argv[2].val.number;
	price		= argv[3].val.number;
	if (!GX_VALID_DT(settlement) || !GX_VALID_DT(maturity))
		_gx_function_error(GX_FN_ERR_INVALID_DATE);
	if (settlement >= maturity)
		_gx_function_error(GX_FN_ERR_SDT_GE_MDT);
	if (_gx_edate(_gx_get_expr_si(), settlement, 12) < maturity)
		_gx_function_error(GX_FN_ERR_INVALID_TBILL);

	_gx_find_yearfrac(_gx_get_expr_si(), settlement, maturity, 2, &yearfrac);
	op.val.number = ((1 - price / 100.0) / yearfrac) / (price / 100.0);
	op.type = GX_NUMBER;    /* tbillyield = discount/(price/100) */
	return op;
}


gxOperand __cdecl _gx_fn_yield(gxOperand argv[])
{

	gxOperand op;
	gxNumber price,
			 coup_rt,
			 price_new,
			 redemption,
			 cdfrac,
			 pmt;
	gxNumber accrint,
			 yld1 = 0.0,
			 yld2,
			 yld3 = 0.05;
	int settlement,
		maturity,
		frequency,
		basis = 0;
	int cdnum,
		cdnc,
		cdpc,
		cpdays;
	register int i;

	if (argv->val.count < 6 || argv->val.count > 7)
		_gx_function_error(GX_FN_ERR_ARG_CNT_WRONG);
	for (i = 1; i < argv->val.count + 1; i++)
	{
		_gx_cvt2constant(argv + i);
		if (argv[i].type != GX_NUMBER)
			_gx_function_error(GX_FN_ERR_ARG_NUMERIC);
		if (argv[i].val.number < 0)
			_gx_function_error(GX_FN_ERR_NEG_FINA_ARG);
	}

	settlement = argv[1].val.number;
	maturity = argv[2].val.number;
	coup_rt		= argv[3].val.number;
	price		= argv[4].val.number;
	redemption	= argv[5].val.number;
	frequency	= get_frequency(argv[6].val.number);

	if (argv->val.count == 7)
		basis = get_basis(argv[7].val.number);

	if (!GX_VALID_DT(settlement) || !GX_VALID_DT(maturity))
		_gx_function_error(GX_FN_ERR_INVALID_DATE);
	if (settlement >= maturity)
		_gx_function_error(GX_FN_ERR_SDT_GE_MDT);
	cdnum = coupnum(settlement, maturity, frequency, basis);
	cdnc = coupdaysnc(settlement, maturity, frequency, basis);
	cdpc = coupdaybs(settlement, maturity, frequency, basis);
	cpdays = coupdays(settlement, maturity, frequency, basis);
	cdfrac = (gxNumber) cdnc / (gxNumber) cpdays;
	pmt = (100.0 * coup_rt) / frequency;
	accrint = pmt * ((gxNumber) cdpc) / (gxNumber) cpdays;

	do
	{   /* make sure yld3 is the "ceiling" */
		yld3 += 0.05;
		price_new = _gx_do_price(pmt, yld3, redemption, frequency,
								 cdnum, cdfrac, accrint);
	} while (price_new > price);

	if (fabs(price - price_new) < 1.0e-8)
	{   /* if we are really lucky today */
		op.type = GX_NUMBER;
		op.val.number = yld3;
		return op;
	}
	yld2 = (yld1 + yld3) / 2.0;
	for (i = 0; i < MAX_IT; i++)
	{
		price_new =
			_gx_do_price(pmt, yld2, redemption,
						 frequency, cdnum, cdfrac, accrint);
		if (fabs(price - price_new) < 1.0e-8)
			break;
		if (price_new < price)  /* need to lower the yield */
			yld3 = yld2;
		else
			yld1 = yld2;    /* need to raise the yield */
		yld2 = (yld1 + yld3) / 2.0;
	}
	op.type = GX_NUMBER;
	op.val.number = yld2;
	return op;
}

// _gx_fn_yielddisc did not validate with the sample
// data. Therefore I removed it from the keyword table.

gxOperand __cdecl _gx_fn_yielddisc(gxOperand argv[])
{

	gxOperand op;
	gxNumber price,
			 redemption,
			 yearfrac;
	int settlement,
		maturity,
		basis = 0,
		i;

	if (argv->val.count < 4 || argv->val.count > 5)
		_gx_function_error(GX_FN_ERR_ARG_CNT_WRONG);
	for (i = 1; i < argv->val.count + 1; i++)
	{
		_gx_cvt2constant(argv + i);
		if (argv[i].type != GX_NUMBER)
			_gx_function_error(GX_FN_ERR_ARG_NUMERIC);
		if (argv[i].val.number < 0)
			_gx_function_error(GX_FN_ERR_NEG_FINA_ARG);
	}

	settlement = argv[1].val.number;
	maturity = argv[2].val.number;
	price		= argv[3].val.number;
	redemption	= argv[4].val.number;

	if (argv->val.count == 5)
		basis = get_basis(argv[5].val.number);

	if (!GX_VALID_DT(settlement) || !GX_VALID_DT(maturity))
		_gx_function_error(GX_FN_ERR_INVALID_DATE);
	if (settlement >= maturity)
		_gx_function_error(GX_FN_ERR_SDT_GE_MDT);

	_gx_find_yearfrac(_gx_get_expr_si(), settlement, maturity, basis, &yearfrac);
	op.type = GX_NUMBER;
	op.val.number = (redemption / price - 1) / yearfrac;
	return op;
}


gxOperand __cdecl _gx_fn_yieldmat(gxOperand argv[])
{

	gxOperand op;
	gxNumber price,
			 rate,
			 fracis,
			 fracim,
			 fracsm,
			 p1,
			 yieldmat,
			 rd;
	int settlement,
		maturity,
		issue,
		basis = 0,
		i;
	int si = _gx_get_expr_si();

	if (argv->val.count < 5 || argv->val.count > 6)
		_gx_function_error(GX_FN_ERR_ARG_CNT_WRONG);
	for (i = 1; i < argv->val.count + 1; i++)
	{
		_gx_cvt2constant(argv + i);
		if (argv[i].type != GX_NUMBER)
			_gx_function_error(GX_FN_ERR_ARG_NUMERIC);
		if (argv[i].val.number < 0)
			_gx_function_error(GX_FN_ERR_NEG_FINA_ARG);
	}

	settlement = argv[1].val.number;
	maturity = argv[2].val.number;
	issue = argv[3].val.number;
	rate		= argv[4].val.number;
	price		= argv[5].val.number;
	if (argv->val.count == 6)
		basis = get_basis(argv[6].val.number);

	if (!GX_VALID_DT(settlement) || !GX_VALID_DT(maturity) || !GX_VALID_DT(issue))
		_gx_function_error(GX_FN_ERR_INVALID_DATE);
	if (settlement >= maturity)
		_gx_function_error(GX_FN_ERR_SDT_GE_MDT);
	if (issue > settlement)
		_gx_function_error(GX_FN_ERR_IDT_GT_SDT);

	_gx_find_yearfrac(si, issue, settlement, basis, &fracis);
	_gx_find_yearfrac(si, issue, maturity, basis, &fracim);
	_gx_find_yearfrac(si, settlement, maturity, basis, &fracsm);
	p1 = price + (fracis * rate * 100);
	rd = 100.0 + fracim * rate * 100;
	yieldmat = ((rd / p1) - 1) / fracsm;
	op.type = GX_NUMBER;
	op.val.number = yieldmat;
	return op;
}


gxNumber __cdecl _gx_do_xnpv(gxNumber * values, gxNumber * dates, gxNumber rate, int count)
{
	gxNumber factor,
			 yearfrac,
			 xnpv = 0.0;
	int i;
	int si = _gx_get_expr_si();

	for (i = 0; i < count; i++)
	{
		_gx_find_yearfrac1(si, (int) dates[0], (int) dates[i], 1, &yearfrac);
		factor = 1.0 / pow(1.0 + rate, yearfrac);
		xnpv += values[i] * factor;
	}
	return xnpv;
}


gxOperand __cdecl _gx_fn_xnpv(gxOperand argv[])
{
#ifdef CELLRANGE
	gxOperand op;

	gxNumber x,
			 rate,
			 xnpv = 0.0;
	gxNumber *values,
			*dates,
			 start_date;
	unsigned r,
		c;
	int n1,
		n2,
		count = 0;

	if (argv->val.count != 3)
		_gx_function_error(GX_FN_ERR_ARG_CNT_WRONG);
	_gx_cvt2constant(argv + 1);
	if (argv[1].type != GX_NUMBER)
		_gx_function_error(GX_FN_ERR_R_NUMERIC);
	rate = argv[1].val.number;
	if (rate < -1.0)
		_gx_function_error(GX_FN_ERR_R_INT_GT_NEG_1);
	GX_HANDLE_OP_ERROR(argv[2]);
	GX_HANDLE_OP_ERROR(argv[3]);
	if (!(argv[2].type == GX_RANGE && argv[3].type == GX_RANGE))
		_gx_function_error(GX_FN_ERR_CF_RANGE);
	if (argv[2].val.range.r0 != argv[2].val.range.r1 &&
		argv[2].val.range.c0 != argv[2].val.range.c1)
		_gx_function_error(GX_FN_ERR_CF_COL_OR_ROW);
	if (argv[3].val.range.r0 != argv[3].val.range.r1 &&
		argv[3].val.range.c0 != argv[3].val.range.c1)
		_gx_function_error(GX_FN_ERR_DT_COL_OR_ROW);

	n1 = (argv[2].val.range.r1 - argv[2].val.range.r0 + 1) *
		(argv[2].val.range.c1 - argv[2].val.range.c0 + 1);
	n2 = (argv[3].val.range.r1 - argv[3].val.range.r0 + 1) *
		(argv[3].val.range.c1 - argv[3].val.range.c0 + 1);

	if (n1 != n2)
		_gx_function_error(GX_FN_ERR_VA_DT_DIMS);

	values = _gx_mknumarray(n1);
	dates = _gx_mknumarray(n2);
	for (r = argv[2].val.range.r0; r <= argv[2].val.range.r1; r++)
		for (c = argv[2].val.range.c0; c <= argv[2].val.range.c1; c++)
		{
			if (!_gx_fn_get_value(r, c, &x))
				_gx_function_error(GX_FN_ERR_NON_NUM_CASH_FL);
			values[count] = x;
			count++;
		}
	count = 0;
	_gx_fn_get_value(argv[3].val.range.r0, argv[3].val.range.c0, &start_date);
	for (r = argv[3].val.range.r0; r <= argv[3].val.range.r1; r++)
		for (c = argv[3].val.range.c0; c <= argv[3].val.range.c1; c++)
		{
			if (!_gx_fn_get_value(r, c, &x))
				_gx_function_error(GX_FN_ERR_NON_NUM_CASH_FL);
			if (x < start_date)
				_gx_function_error(GX_FN_ERR_CF_DTS);
			dates[count] = x;
			count++;
		}
	xnpv = _gx_do_xnpv(values, dates, rate, count);
	op.type = GX_NUMBER;
	op.val.number = xnpv;
	return op;
#else
	gxOperand op;
	op.type = GX_NUMBER;
	_gx_function_error(GX_FN_ERR_IMPROP_ARG_TYPE);
	return op;
#endif
}


gxNumber __cdecl _gx_do_xirr(gxNumber * values, gxNumber * exponents, gxNumber rate, int count, int prime)
{
	gxNumber factor = 0,
	            xpv = 0.0;
	int i;

	//FILE *fp;
	//fp = _tfopen("/usr/users/rose/log", "a");

	for (i = 0; i < count; i++)
	{
		// when the rate parameter = -1, the base = 0, so...
		// ...if the exponent is positive, the power of zero is zero: 0 raised to the power of n = 0, where n > 0.
		// ...if the exponent is negative, the power of zero (0 raised to the power of n, where n < 0) is undefined, because division by zero is implied.
		// ...if the exponent is zero, some programmers define 0 raised to the 0th power as equal to 1 (Objective Grid uses this definition), whereas others define it as undefined.
		//    Refer to "History of differing points of view" in this section http://en.wikipedia.org/wiki/Exponentiation#Zero_to_the_zero_power for detailed information.
		if(rate + 1.0 == 0.0)
		{
			if ((exponents[i] - prime) == 0)     // 0 raised to the 0th power
			{
				factor = 1;
			}
            else if((exponents[i] - prime) > 0)  // 0 raised to the + nth power
			{
				factor = 0;
			}
            else if ((exponents[i] - prime) < 0) // 0 raised to the - nth power (UNDEFINED)
			{
				_gx_function_error(GX_FN_ERR_DIV_0);
			}
		}
		else
		{
		    factor = pow(rate + 1, exponents[i] - prime);
		}
		xpv += values[i] * factor;
		TRACE3("fnfina2.cpp _gx_do_xirr() ln 2492: (xpv = %d, values[i] = %d, factor = %d)\n", xpv, values[i], factor);
	}
	// fclose(fp);
	return xpv;
}


gxOperand __cdecl _gx_fn_xirr(gxOperand argv[])
{
#ifdef CELLRANGE
	gxOperand op;

	gxNumber x = 0.0,
			 xirr = 0.0, // guess, passed in as argv[1].val.number from cell formula
			 pv1 = 0.0,
			 pv2 = 0.0,
			 y = 0.0;
	gxNumber *values = NULL,
			*vprime = NULL,
			*dates = NULL,
			 coef_max = 0.0,
			 start_date = 0.0;
	unsigned r = 0,
		c = 0;
	int n1 = 0,
		n2 = 0,
		i = 0,
		j = 0,
		count = 0;
	int si = _gx_get_expr_si();

	// validate correct number of args
	if (argv->val.count != 3)
		_gx_function_error(GX_FN_ERR_ARG_CNT_WRONG);

	// validate 1st argv type == GX_NUMBER
	_gx_cvt2constant(argv + 1);
	if (argv[1].type != GX_NUMBER)
		_gx_function_error(GX_FN_ERR_R_NUMERIC);

	// validate 1st argv value > -1.0 
	if (argv[1].val.number <= -1.0)
		_gx_function_error(GX_FN_ERR_R_LT_M1);
	// assign validated 1st argv value, then revalidate
	xirr = argv[1].val.number;
	if (xirr < -1.0)
		_gx_function_error(GX_FN_ERR_R_INT_GT_NEG_1);
	TRACE1("fnfina2.cpp _gx_fn_xirr() ln 2537: (xirr = %d)\n", xirr);

	// validate 2nd (net cash flow data) and 3rd (datetime data) argv as valid GX_RANGE types and values
	GX_HANDLE_OP_ERROR(argv[2]);
	GX_HANDLE_OP_ERROR(argv[3]);
	if (!(argv[2].type == GX_RANGE && argv[3].type == GX_RANGE))
		_gx_function_error(GX_FN_ERR_CF_RANGE);
	if (argv[2].val.range.r0 != argv[2].val.range.r1 &&
		argv[2].val.range.c0 != argv[2].val.range.c1)
		_gx_function_error(GX_FN_ERR_CF_COL_OR_ROW);
	if (argv[3].val.range.r0 != argv[3].val.range.r1 &&
		argv[3].val.range.c0 != argv[3].val.range.c1)
		_gx_function_error(GX_FN_ERR_DT_COL_OR_ROW);

	// calculate the number of rows for net cash flow column and the datetime column
	n1 = (argv[2].val.range.r1 - argv[2].val.range.r0 + 1) *
		(argv[2].val.range.c1 - argv[2].val.range.c0 + 1);
	n2 = (argv[3].val.range.r1 - argv[3].val.range.r0 + 1) *
		(argv[3].val.range.c1 - argv[3].val.range.c0 + 1);

	// verify that the number of rows (dimensions) are equal for both sets of data
	if (n1 != n2)
		_gx_function_error(GX_FN_ERR_VA_DT_DIMS);
	TRACE2("fnfina2.cpp _gx_fn_xirr() ln 2492: (n1 = %d, n2 = %d)\n", n1, n2);

	// allocate memory for arrays
	values = _gx_mknumarray(n1);
	vprime = _gx_mknumarray(n1);
	dates = _gx_mknumarray(n2);

	// verify and fill values array from validated data (net cash flow) range
	// NOTE: count is set to 0 above in the data initialization section of this function
	for (r = argv[2].val.range.r0; r <= argv[2].val.range.r1; r++)
		for (c = argv[2].val.range.c0; c <= argv[2].val.range.c1; c++)
		{
			if (!_gx_fn_get_value(r, c, &x))
				_gx_function_error(GX_FN_ERR_NON_NUM_CASH_FL);
			values[count] = x;
			TRACE3("fnfina2.cpp _gx_fn_xirr() ln 2577: (count = %d, values[count] = %d, x = %d)\n", count, values[count], x);
			count++;
		}

	// reset counter
	count = 0;

	// validate date data, fill dates array with fractional periods AND determine the maximum coefficient to transform f(x) to a polynomial function
	_gx_fn_get_value(argv[3].val.range.r0, argv[3].val.range.c0, &start_date);
	for (r = argv[3].val.range.r0; r <= argv[3].val.range.r1; r++)
		for (c = argv[3].val.range.c0; c <= argv[3].val.range.c1; c++)
		{
			// data validation only
			if (!_gx_fn_get_value(r, c, &x))
				_gx_function_error(GX_FN_ERR_NON_NUM_CASH_FL);
			if (x < start_date)
				_gx_function_error(GX_FN_ERR_CF_DTS);
			// find fractional period
			_gx_find_yearfrac1(si, (int) start_date, (int) x, 1, &y);
			// find maximum coefficient value
			if (y > coef_max)
				coef_max = y;
			// store fractional period
			dates[count] = y;
			TRACE3("fnfina2.cpp _gx_fn_xirr() ln 2601: (dates[count] = %d, y = %d, coef_max = %d)\n", dates[count], y, coef_max);
			count++;
		}
	// transform f(x) to poly
		for (i = 0; i < count; i++) 
		{
			TRACE2("fnfina2.cpp _gx_fn_xirr() ln 2609 (before): (dates[i] = %d)\n", dates[i], coef_max);
			dates[i] = coef_max - dates[i]; 
			TRACE1("fnfina2.cpp _gx_fn_xirr() ln 2609 (after): (dates[i] = %d, coef_max = %d)\n", dates[i]);
		}
	
	// calculate the coefficients for the 1st derivitives
	// NOTE: reverse counter in for-loop
	for (i = count; i > 0; i--)
	{
		vprime[count - i] = values[count - i] * dates[count - i];
		TRACE3("fnfina2.cpp _gx_fn_xirr() ln 2617: (vprime[count-i] = %d, values[count-i] = %d, dates[count-i] = %d)\n", vprime[count - i], values[count - i], dates[count - i]);
	}

	// calcuate internal rate of return using the secant method (Newton-Raphson)
	pv1 = _gx_do_xirr(values, dates, xirr, count, 0);
	TRACE1("fnfina2.cpp _gx_fn_xirr() ln 2622: (pv1 = %d)\n", pv1);
	if (fabs(pv1) < 1.0e-8)
	{
		op.val.number = xirr;
		op.type = GX_NUMBER;
		return op;
	}
	// NOTE: count is NOT reset but used as a MAX value in _gx_do_xirr()
	for (j = 0; j < MAX_IT; j++)
	{
		pv2 = _gx_do_xirr(vprime, dates, xirr, count, 1);
		TRACE1("fnfina2.cpp _gx_fn_xirr() ln 2633: (pv2 = %d)\n", pv2);

		xirr = xirr - (pv1 / pv2);
		TRACE1("fnfina2.cpp _gx_fn_xirr() ln 2636: (xirr = %d)\n", xirr);

		pv1 = _gx_do_xirr(values, dates, xirr, count, 0);
		TRACE1("fnfina2.cpp _gx_fn_xirr() ln 2639: (pv1 = %d)\n", pv1);

		if (fabs(pv1) < 1.0e-8)
			break;
	}

	// validate internal rate of return value
	if (j == MAX_IT)
		_gx_function_error(GX_FN_ERR_NO_REAL_ROOT);

	if (xirr <= -1.0)
		_gx_function_error(GX_FN_ERR_R_LT_M1);

	op.type = GX_NUMBER;
	op.val.number = xirr;
	return op;
#else
	gxOperand op;
	op.type = GX_NUMBER;
	_gx_function_error(GX_FN_ERR_IMPROP_ARG_TYPE);
	return op;
#endif
}
