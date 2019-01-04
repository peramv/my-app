///////////////////////////////////////////////////////////////////////////////
// gxserror.cpp: Engine Errors
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

static LPCTSTR errors[] =
{
	_T("unknown error") /* 0 */ ,
	_T("") /* 1 */ ,
	_T("") /* 2 */ ,
	_T("") /* 3 */ ,
	_T("") /* 4 */ ,
	_T("out of memory") /* 5 */ ,
	_T("illegal range specification") /* 6 */ ,
	_T("illegal cell address specification") /* 7 */ ,
	_T("") /* 8 */ ,
	_T("") /* 9 */ ,
	_T("") /* 10 */ ,
	_T("") /* 11 */ ,
	_T("") /* 12 */ ,
	_T("") /* 13 */ ,
	_T("") /* 14 */ ,
	_T("") /* 15 */ ,
	_T("") /* 16 */ ,
	_T("") /* 17 */ ,
	_T("") /* 18 */ ,
	_T("") /* 19 */ ,
	_T("invalid range name") /* 20 */ ,
	_T("") /* 21 */ ,
	_T("") /* 22 */ ,
	_T("") /* 23 */ ,
	_T("") /* 24 */ ,
	_T("") /* 25 */ ,
	_T("") /* 26 */ ,
	_T("") /* 27 */ ,
	_T("") /* 28 */ ,
	_T("") /* 29 */ ,
	_T("") /* 30 */ ,
	_T("") /* 31 */ ,
	_T("") /* 32 */ ,
	_T("") /* 33 */ ,
	_T("") /* 34 */ ,
	_T("") /* 35 */ ,
	_T("") /* 36 */ ,
	_T("") /* 37 */ ,
	_T("") /* 38 */ ,
	_T("F must be >= 0") /* 39 */ ,
	_T("IEEE Floating Exception (Infinity or NaN)") /* 40 */ ,
	_T("\"#\" in primary expression") /* 41 */ ,
	_T("\"Life\" and \"Period\" must be integers") /* 42 */ ,
	_T("\"Life\" must be > 0") /* 43 */ ,
	_T("\"PV\" and \"FV\" must be non-zero") /* 44 */ ,
	_T("\"PV\" and \"FV\" must have the same sign") /* 45 */ ,
	_T("\"Payment\" and \"FV\" must have the same sign") /* 46 */ ,
	_T("\"Payment\" must be non-zero") /* 47 */ ,
	_T("\"Period\" must be >= 0") /* 48 */ ,
	_T("\"Period\" must be an integer > 0") /* 49 */ ,
	_T("\"Rate\" must be greater than -1") /* 50 */ ,
	_T("\"Rate\" must be non-zero") /* 51 */ ,
	_T("argument is negative") /* 52 */ ,
	_T("argument must be an integer") /* 53 */ ,
	_T("argument not a cell or range") /* 54 */ ,
	_T("argument out of range") /* 55 */ ,
	_T("arguments must be numeric") /* 56 */ ,
	_T("can not parse condition string") /* 57 */ ,
	_T("cash flow series must be a range") /* 58 */ ,
	_T("cash flow series must be single column or row") /* 59 */ ,
	_T("cell operand contains error condition") /* 60 */ ,
	_T("coefficient matrix has linearly dependent columns") /* 61 */ ,
	_T("column offset out of range") /* 62 */ ,
	_T("could not find real root") /* 63 */ ,
	_T("count less than zero") /* 64 */ ,
	_T("data set size must be >= 3") /* 65 */ ,
	_T("data set size must be >= polynomial degree + 2") /* 66 */ ,
	_T("decimal places out of range") /* 67 */ ,
	_T("degrees of freedom must be > 0") /* 68 */ ,
	_T("dimension must be power of 2") /* 69 */ ,
	_T("divide by zero") /* 70 */ ,
	_T("does not accept arguments") /* 71 */ ,
	_T("domain is -1 < x < 1") /* 72 */ ,
	_T("domain is -1 <= x <= 1") /* 73 */ ,
	_T("domain is 0 <= x <= 170") /* 74 */ ,
	_T("domain is 0 <= x <= 33") /* 75 */ ,
	_T("domain is x > 0") /* 76 */ ,
	_T("domain is x >= 1") /* 77 */ ,
	_T("error executing alarm action") /* 78 */ ,
	_T("error in regular expression") /* 79 */ ,
	_T("expecting a function") /* 80 */ ,
	_T("expecting an operand") /* 81 */ ,
	_T("expecting an operator") /* 82 */ ,
	_T("extraneous operands") /* 83 */ ,
	_T("first argument (\"Rate\") must be numeric") /* 84 */ ,
	_T("first argument must be numeric") /* 85 */ ,
	_T("floating exception") /* 86 */ ,
	_T("function stack overflow") /* 87 */ ,
	_T("hex number greater than 32 bits") /* 88 */ ,
	_T("illegal cell or range reference") /* 89 */ ,
	_T("illegal operand of \"!=\"") /* 90 */ ,
	_T("illegal operand of \"&\"") /* 91 */ ,
	_T("illegal operand of \"<=\"") /* 92 */ ,
	_T("illegal operand of \"<\"") /* 93 */ ,
	_T("illegal operand of \"==\"") /* 94 */ ,
	_T("illegal operand of \">=\"") /* 95 */ ,
	_T("illegal operand of \">\"") /* 96 */ ,
	_T("improper argument value") /* 97 */ ,
	_T("improper argument type") /* 98 */ ,
	_T("improper argument 1 type") /* 99 */ ,
	_T("improper argument 2 type") /* 100 */ ,
	_T("improper argument 3 type") /* 101 */ ,
	_T("improper coefficient type") /* 102 */ ,
	_T("improper dimensions") /* 103 */ ,
	_T("incompatible matrix dimensions") /* 104 */ ,
	_T("incompatible range dimensions") /* 105 */ ,
	_T("index column contains empty cell") /* 106 */ ,
	_T("index out of range") /* 107 */ ,
	_T("index row contains empty cell") /* 108 */ ,
	_T("integer parameter out of range") /* 109 */ ,
	_T("invalid cell reference") /* 110 */ ,
	_T("invalid date") /* 111 */ ,
	_T("invalid range reference") /* 112 */ ,
	_T("invalid time") /* 113 */ ,
	_T("less than 2 arguments") /* 114 */ ,
	_T("lookup failed to produce a match") /* 115 */ ,
	_T("magnitude too large") /* 116 */ ,
	_T("matrix is singular") /* 117 */ ,
	_T("matrix must be square") /* 118 */ ,
	_T("matrix must be symmetric") /* 119 */ ,
	_T("missing condition string") /* 120 */ ,
	_T("incomplete or improper conditional operator (?:)") /* 121 */ ,
	_T("modulo divide by zero") /* 122 */ ,
	_T("must be -15 to +15 places") /* 123 */ ,
	_T("must have \"Cost\" >= \"Salvage\" >= 0") /* 124 */ ,
	_T("must have \"Life\" >= \"Period\" >= 1") /* 125 */ ,
	_T("need at least 2 cash flow values") /* 126 */ ,
	_T("non hex digits in string") /* 127 */ ,
	_T("non-numeric operand") /* 128 */ ,
	_T("non-numeric value in cash flow series") /* 129 */ ,
	_T("non-numeric value in matrix") /* 130 */ ,
	_T("non-numeric value in vector") /* 131 */ ,
	_T("one argument must be non-zero") /* 132 */ ,
	_T("operand contains error condition") /* 133 */ ,
	_T("operand equal to 0") /* 134 */ ,
	_T("both index operands equal to 0") /* 135 */ ,
	_T("operand larger than 32 bits") /* 136 */ ,
	_T("operand less than or equal to 0") /* 137 */ ,
	_T("operand out of range") /* 138 */ ,
	_T("operand stack overflow") /* 139 */ ,
	_T("operands of \"&\" must be same type") /* 140 */ ,
	_T("operands of \"..\" must be cell references") /* 141 */ ,
	_T("operator stack overflow") /* 142 */ ,
	_T("polynomial degree must be between 1 and 10") /* 143 */ ,
	_T("pooled sample size less than 3") /* 144 */ ,
	_T("population less than 1") /* 145 */ ,
	_T("ranges must be same dimensions") /* 146 */ ,
	_T("rate found is less than -1") /* 147 */ ,
	_T("recursion too deep") /* 148 */ ,
	_T("result of expression is a range") /* 149 */ ,
	_T("resultant string too long") /* 150 */ ,
	_T("row offset out of range") /* 151 */ ,
	_T("sample missing from pair") /* 152 */ ,
	_T("sample size less than 1") /* 153 */ ,
	_T("sample size less than 2") /* 154 */ ,
	_T("selector out of range") /* 155 */ ,
	_T("string result") /* 156 */ ,
	_T("substring longer than string") /* 157 */ ,
	_T("substring not found") /* 158 */ ,
	_T("too few arguments") /* 159 */ ,
	_T("too many arguments") /* 160 */ ,
	_T("unexpected question mark") /* 161 */ ,
	_T("unknown format") /* 162 */ ,
	_T("unmatched left parenthesis") /* 163 */ ,
	_T("unmatched right parenthesis") /* 164 */ ,
	_T("wrong number of arguments") /* 165 */ ,
	_T("function not installed") /* 166 */ ,
	_T("") /* 167 */ ,
	_T("") /* 168 */ ,
	_T("") /* 169 */ ,
	_T("") /* 170 */ ,
	_T("") /* 171 */ ,
	_T("") /* 172 */ ,
	_T("") /* 173 */ ,
	_T("") /* 174 */ ,
	_T("") /* 175 */ ,
	_T("") /* 176 */ ,
	_T("") /* 177 */ ,
	_T("") /* 178 */ ,
	_T("") /* 179 */ ,
	_T("") /* 180 */ ,
	_T("") /* 181 */ ,
	_T("") /* 182 */ ,
	_T("") /* 183 */ ,
	_T("") /* 184 */ ,
	_T("") /* 185 */ ,
	_T("label missing opening quote") /* 186 */ ,
	_T("label missing closing quote") /* 187 */ ,
	_T("") /* 188 */ ,
	_T("") /* 189 */ ,
	_T("") /* 190 */ ,
	_T("") /* 191 */ ,
	_T("") /* 192 */ ,
	_T("") /* 193 */ ,
	_T("") /* 194 */ ,
	_T("") /* 195 */ ,
	_T("") /* 196 */ ,
	_T("") /* 197 */ ,
	_T("") /* 198 */ ,
	_T("") /* 199 */ ,
	_T("") /* 200 */ ,
	_T("") /* 201 */ ,
	_T("") /* 202 */ ,
	_T("") /* 203 */ ,
	_T("") /* 204 */ ,
	_T("illegal combination of source/destination range") /* 205 */ ,
	_T("") /* 206 */ ,
	_T("") /* 207 */ ,
	_T("") /* 208 */ ,
	_T("constraint check not supported with \"As Needed\"") /* 209 */ ,
	_T("iterative calculcation not supported with \"As Needed\"") /* 210 */ ,
	_T("") /* 211 */ ,
	_T("") /* 212 */ ,
	_T("unable to parse search condition") /* 213 */ ,
	_T("unable to parse extract filter") /* 214 */ ,
	_T("") /* 215 */ ,
	_T("") /* 216 */ ,
	_T("") /* 217 */ ,
	_T("") /* 218 */ ,
	_T("") /* 219 */ ,
	_T("") /* 220 */ ,
	_T("") /* 221 */ ,
	_T("Lost contact with floating license manager") /* 222 */ ,
	_T("invalid character in formula") /* 223 */ ,
	_T("") /* 224 */ ,
	_T("found something unexpected here") /* 225 */ ,
	_T("cell reference out of range") /* 226 */ ,
	_T("undefined function") /* 227 */ ,
	_T("internal error freeing node") /* 228 */ ,
	_T("too many arguments to function") /* 229 */ ,
	_T("not enough arguments to function") /* 230 */ ,
	_T("expected to find \";\" here") /* 231 */ ,
	_T("expected to find \":\" here") /* 232 */ ,
	_T("expected to find \",\" here") /* 233 */ ,
	_T("expected to find \"?\" here") /* 234 */ ,
	_T("expected to find \"#\" here") /* 235 */ ,
	_T("expected to find \"\\\" here") /* 236 */ ,
	_T("expected to find \"+\" here") /* 237 */ ,
	_T("expected to find \"-\" here") /* 238 */ ,
	_T("expected to find \"*\" here") /* 239 */ ,
	_T("expected to find \"/\" here") /* 240 */ ,
	_T("expected to find \"%\" here") /* 241 */ ,
	_T("expected to find \"|\" here") /* 242 */ ,
	_T("expected to find \"^\" here") /* 243 */ ,
	_T("expected to find \"&\" here") /* 244 */ ,
	_T("expected to find \"!\" here") /* 245 */ ,
	_T("expected to find \"~\" here") /* 246 */ ,
	_T("expected to find \"<\" here") /* 247 */ ,
	_T("expected to find \">\" here") /* 248 */ ,
	_T("expected to find \"(\" here") /* 249 */ ,
	_T("expected to find \")\" here") /* 250 */ ,
	_T("expected to find \"{\" here") /* 251 */ ,
	_T("expected to find \"}\" here") /* 252 */ ,
	_T("expected to find \"=\" here") /* 253 */ ,
	_T("expected to find \"**\" here") /* 254 */ ,
	_T("expected to find \"&&\" here") /* 255 */ ,
	_T("expected to find \"||\" here") /* 256 */ ,
	_T("expected to find \"<<\" here") /* 257 */ ,
	_T("expected to find \">>\" here") /* 258 */ ,
	_T("expected to find \"<=\" here") /* 259 */ ,
	_T("expected to find \">=\" here") /* 260 */ ,
	_T("expected to find \"!=\" here") /* 261 */ ,
	_T("expected to find \"==\" here") /* 262 */ ,
	_T("expected to find \"..\" here") /* 263 */ ,
	_T("expected to find a cell name here") /* 264 */ ,
	_T("expected to find a cell or range name here") /* 265 */ ,
	_T("expected to find a function name here") /* 266 */ ,
	_T("expected to find a string here") /* 267 */ ,
	_T("expected to find a number here") /* 268 */ ,
	_T("expected to find a hex number here") /* 269 */ ,
	_T("expected to find a comment here") /* 270 */ ,
	_T("expected to find the end of formula here") /* 271 */ ,
	_T("expected to find an error here") /* 272 */ ,
	_T("expected to find a \".\" here") /* 273 */ ,
	_T("expected to find an operand here") /* 274 */ ,
	_T("expected the right hand side of a range here") /* 275 */ ,
	_T("constraint expression not allowed") /* 276 */ ,
	_T("invalid offset specifier") /* 277 */ ,
	_T("invalid operator") /* 278 */ ,
	_T("operator not allowed") /* 279 */ ,
	_T("token buffer overflow") /* 280 */ ,
	_T("undefined symbolic name") /* 281 */ ,
	_T("unrepresentable number") /* 282 */ ,
	_T("unresolved name in expression") /* 283 */ ,
	_T("internal error---unconsumed operands") /* 284 */ ,
	_T("\"Start Period\" must be >= 1") /* 285 */ ,
	_T("\"End Period\" must be >= 1") /* 286 */ ,
	_T("\"End Period\" must be >= \"Start Period\"") /* 287 */ ,
	_T("Invalid \"Period\"") /* 288 */ ,
	_T("\"Fraction\" must be >= 1") /* 289 */ ,
	_T("interest rate should be > 0") /* 290 */ ,
	_T("number of compounding periods should be >= 1") /* 291 */ ,
	_T("settlement date should be < maturity date") /* 292 */ ,
	_T("settlement date should be >= issue date") /* 293 */ ,
	_T("invalid day count basis") /* 294 */ ,
	_T("\"Frequency\" must be 1, 2 or 4") /* 295 */ ,
	_T("date series must be single column or row") /* 296 */ ,
	_T("\"values\" \"dates\" series must have same dimentions") /* 297 */ ,
	_T("must have issue < first coupon < maturity") /* 298 */ ,
	_T("must have issue < last coupon < maturity") /* 299 */ ,
	_T("no duplicate number found") /* 300 */ ,
	_T("\"Number\" is not in the reference list") /* 301 */ ,
	_T("\"Match Type\" must be 0 for string match") /* 302 */ ,
	_T("no match was found") /* 303 */ ,
	_T("\"Values\" must have at least one inflow and one outflow") /* 304 */ ,
	_T("Treasury Bill should not be outstanding more than 1 year") /* 305 */ ,
	_T("invalid table") /* 306 */ ,
	_T("can not find interpolation") /* 307 */ ,
	_T("starting date should be at beginning of \"Dates\"") /* 308 */ ,
	_T("interest schedule must be single column or row") /* 309 */ ,
	_T("\"Lower limit\" must be >= 0") /* 310 */ ,
	_T("\"Upper limit\" must be >= 0") /* 311 */ ,
	_T("must have N > 0, K > 0 and N < K") /* 312 */ ,
	_T("arguments must be positive") /* 313 */ ,
	_T("non-existent object") /* 314 */ ,
	_T("unknown object command") /* 315 */ ,
	_T("odd character in numeric string") /* 316 */ ,
	_T("found number where string should be") /* 317 */ ,
	_T("") /* 318 */ ,
	_T("") /* 319 */ ,
	_T("") /* 320 */ ,
	_T("unspecified or invalid") /* 321 */ ,
	_T("range should not be a row") /* 322 */ ,
	_T("range should not be a column") /* 323 */ ,
	_T("range should not be a block") /* 324 */ ,
	_T("") /* 325 */ ,
	_T("") /* 326 */ ,
	_T("") /* 327 */ ,
	_T("") /* 328 */ ,
	_T("") /* 329 */ ,
	_T("stacking different types of data") /* 330 */ ,
	_T("cannot stack non-numeric data") /* 331 */ ,
	_T("allocating negative-dimensional matrix") /* 332 */ ,
	_T("freeing negative-dimensional matrix") /* 333 */ ,
	_T("freeing data pointed to by NULL") /* 334 */ ,
	_T("") /* 335 */ ,
	_T("") /* 336 */ ,
	_T("") /* 337 */ ,
	_T("") /* 338 */ ,
	_T("") /* 339 */ ,
	_T("") /* 340 */ ,
	_T("") /* 341 */ ,
	_T("") /* 342 */ ,
	_T("") /* 343 */ ,
	_T("") /* 344 */ ,
	_T("") /* 345 */ ,
	_T("") /* 346 */ ,
	_T("") /* 347 */ ,
	_T("") /* 348 */ ,
	_T("") /* 349 */ ,
	_T("") /* 350 */ ,
	_T("") /* 351 */ ,
	_T("beginning line with subscript command") /* 352 */ ,
	_T("ending line with subscript command") /* 353 */ ,
	_T("ending line with a superscript command") /* 354 */ ,
	_T("ending line with a \\") /* 355 */ ,
	_T("mismatched {}'s") /* 356 */ ,
	_T("misplaced }") /* 357 */ ,
	_T("misplaced newline") /* 358 */ ,
	_T("") /* 359 */ ,
	_T("") /* 360 */ ,
	_T("") /* 361 */ ,
	_T("") /* 362 */ ,
	_T("normalizing zero-length vector") /* 363 */ ,
	_T("making null list") /* 364 */ ,
	_T("removing NULL list") /* 365 */ ,
	_T("removing NULL item") /* 366 */ ,
	_T("searching NULL list") /* 367 */ ,
	_T("searching list with a NULL function") /* 368 */ ,
	_T("showing NULL list") /* 369 */ ,
	_T("showing list with a NULL function") /* 370 */ ,
	_T("unknown type of graph data") /* 371 */ ,
	_T("number is too large") /* 372 */ ,
	_T("number is too small") /* 373 */ ,
	_T("") /* 374 */ ,
	_T("") /* 375 */ ,
	_T("") /* 376 */ ,
	_T("contains an error indicator") /* 377 */ ,
	_T("") /* 378 */ ,
	_T("skewing is always ignored") /* 379 */ ,
	_T("skewing is always enforced") /* 380 */ ,
	_T("precompiled regular expression is invalid") /* 381 */
};

//static int xs_error_silence = 0,
//	xs_error_status = 0,
//	xs_error_code = 0;

void  __cdecl _gx_xs_error(int si, int severity, int audience, LPCTSTR tag, int err,
					   LPTSTR text)
{
	// Unused:
	audience, si;

	TCHAR line[GX_MAX_TEXT];

	GXGetEngineState()->xs_error_status = 1;
	GXGetEngineState()->xs_error_code = err;

	if (GXGetEngineState()->xs_error_silence)
		return;

	// QA: 31989 - #if Secure Code Cleanup.
	if (tag == NULL)
	{
		_stprintf(line, _T("ERROR: %s "), errors[err]);
	}else
	{
		_stprintf(line, _T("ERROR: %s - %s "), tag, errors[err]);
	}

	if (text)
	{
		// QA: 31989 - #if Secure Code Cleanup.
		_tcscat(line, text);
	}

	GXGetEngineState()->last_severity = severity;
}

LPCTSTR  __cdecl _gx_xs_error_msg(int err)
{  /* returns ptr to text of error message */
	if (err >= 0 && err <= GX_MAX_ERRORS)
		return errors[err];
	else
		return errors[0];   /* unknown error */
}


/*
 * The following function turns off error reporting on the GUI, but
 * allows error information to be obtained using _gx_get_xs_error_status()
 * and _gx_get_xs_error_code().
 */

void  __cdecl _gx_silence_xs_error(int state)
{
	GXGetEngineState()->xs_error_silence = state;   /* silent mode true or false */
	GXGetEngineState()->xs_error_status = 0;    /* reset the error status indicator */
	GXGetEngineState()->xs_error_code = 0;  /* and the error code indicator */
}

int  __cdecl _gx_get_xs_error_status(void)
{
	return GXGetEngineState()->xs_error_status;
}

int  __cdecl _gx_get_xs_error_code(void)
{
	return GXGetEngineState()->xs_error_code;
}
