///////////////////////////////////////////////////////////////////////////////
// gxexft.cpp
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
// Author: Daniel Jebaraj
//
// Portions Copyright (C) 1995-1998 X Engineering Software Systems Corp
//

#define _OG_EXPORT_IMPL

#include "stdafx.h"
#include <stdio.h>
#include <errno.h>


#include "grid\gxexman.h"
#include "grid\gxexlog.h"

#include "grid\gxsexpr.h"
#include "grid\gxexhnd.h"
#include "grid\gxexhdr.h"
#include "grid\gxengine.h"

#include "grid\gxexft.h"

#define	LAST_FUNC	336


XlsFuncRec	func_table[] =
	{
	/* xlfCount			0	*/		{ -1,	"COUNT",		NULL },
	/*					1	*/		{  0,	NULL,			NULL },
	/* xlfIsna			2	*/		{  0,	"",				NULL },
	/* xlfIserror		3	*/		{  1,	"ISERROR",		NULL },
	/* xlfSum			4	*/		{ -1,	"SUM",			NULL },
	/* xlfAverage		5	*/		{ -1,	"AVG",			NULL },
	/* xlfMin			6	*/		{ -1,	"MIN",			NULL },
	/* xlfMax			7	*/		{ -1,	"MAX",			NULL },
	/* xlfRow			8	*/		{ -1,	"ROW",			NULL },
	/* xlfColumn		9	*/		{ -1,	"COL",			NULL },
	/* xlfNa			10	*/		{  0,	"NA",			NULL },
	/* xlfNpv			11	*/		{  0,	"",				NULL },		/* Args don't match */
	/* xlfStdev			12	*/		{  -1,	"STDS",			NULL },		/* TKM */
	/* xlfDollar		13	*/		{  0,	"",				NULL },
	/* xlfFixed			14	*/		{  0,	"",				NULL },		/* Similar to STRING */
	/* xlfSin			15	*/		{  1,	"SIN",			NULL },
	/* xlfCos			16	*/		{  1,	"COS",			NULL },
	/* xlfTan			17	*/		{  1,	"TAN",			NULL },
	/* xlfAtan			18	*/		{  1,	"ATAN",			NULL },
	/* xlfPi			19	*/		{  0,	"PI",			NULL },
	/* xlfSqrt			20	*/		{  1,	"SQRT",			NULL },
	/* xlfExp			21	*/		{  1,	"EXP",			NULL },
	/* xlfLn			22	*/		{  1,	"LN",			NULL },
	/* xlfLog10			23	*/		{  1,	"LOG10",		NULL },
	/* xlfAbs			24	*/		{  1,	"ABS",			NULL },
	/* xlfInt			25	*/		{  1,	"FLOOR",		NULL },
	/* xlfSign			26	*/		{  0,	"",				NULL },
	/* xlfRound			27	*/		{  2,	"ROUND",		NULL },
	/* xlfLookup		28	*/		{  0,	"",				NULL },
	/* xlfIndex			29	*/		{ -1,	"INDEX",		NULL },
	/* xlfRept			30	*/		{  2,	"REPEAT",		NULL },
	/* xlfMid			31	*/		{  3,	"MID",			NULL },
	/* xlfLen			32	*/		{  1,	"LENGTH",		NULL },
	/* xlfValue			33	*/		{  1,	"VALUE",		NULL },
	/* xlfTrue			34	*/		{  0,	"TRUE",			NULL },
	/* xlfFalse			35	*/		{  0,	"FALSE",		NULL },
	/* xlfAnd			36	*/		{ -1,	"AND",			NULL },		/* Not an exact match */
	/* xlfOr			37	*/		{ -1,	"OR",			NULL },
	/* xlfNot			38	*/		{  1,	"NOT",			NULL },
	/* xlfMod			39	*/		{  2,	"MOD",			NULL },		/* This is iffy */
	/* xlfDcount		40	*/		{  0,	"",				NULL },
	/* xlfDsum			41	*/		{  0,	"",				NULL },
	/* xlfDaverage		42	*/		{  0,	"",				NULL },
	/* xlfDmin			43	*/		{  0,	"",				NULL },
	/* xlfDmax			44	*/		{  0,	"",				NULL },
	/* xlfDstdev		45	*/		{  0,	"",				NULL },
	/* xlfVar			46	*/		{  -1,	"VARS",			NULL },		/* TKM */
	/* xlfDvar			47	*/		{  0,	"",				NULL },
	/* xlfText			48	*/		{  0,	"",				NULL },
	/* xlfLinest		49	*/		{  0,	"",				NULL },
	/* xlfTrend			50	*/		{  0,	"",				NULL },		/* Args don't match */
	/* xlfLogest		51	*/		{  0,	"",				NULL },
	/* xlfGrowth		52	*/		{  0,	"",				NULL },
	/* xlfGoto			53	*/		{  0,	"",				NULL },
	/* xlfHalt			54	*/		{  0,	"",				NULL },
	/*					55	*/		{  0,	NULL,			NULL },
	/* xlfPv			56	*/		{  0,	"",				NULL },		/* Args don't match */
	/* xlfFv			57	*/		{  0,	"",				NULL },		/* Args don't match */
	/* xlfNper			58	*/		{  0,	"",				NULL },
	/* xlfPmt			59	*/		{  0,	"",				NULL },		/* Args don't match */
	/* xlfRate			60	*/		{  0,	"",				NULL },		/* Args don't match */
	/* xlfMirr			61	*/		{  3,	"MIRR",			NULL },
	/* xlfIrr			62	*/		{  0,	"",				NULL },		/* Args don't match */
	/* xlfRand			63	*/		{  0,	"RAND",			NULL },
	/* xlfMatch			64	*/		{ -1,	"MATCH",		NULL },
	/* xlfDate			65	*/		{  3,	"DATE",			NULL },
	/* xlfTime			66	*/		{  3,	"TIME",			NULL },
	/* xlfDay			67	*/		{  1,	"DAY",			NULL },
	/* xlfMonth			68	*/		{  1,	"MONTH",		NULL },
	/* xlfYear			69	*/		{  1,	"YEAR",			NULL },
	/* xlfWeekday		70	*/		{  0,	"",				NULL },		/* Excel has an opt arg */
	/* xlfHour			71	*/		{  1,	"HOUR",			NULL },
	/* xlfMinute		72	*/		{  1,	"MINUTE",		NULL },
	/* xlfSecond		73	*/		{  1,	"SECOND",		NULL },
	/* xlfNow			74	*/		{  0,	"NOW",			NULL },
	/* xlfAreas			75	*/		{  0,	"",				NULL },
	/* xlfRows			76	*/		{  1,	"ROWS",			NULL },
	/* xlfColumns		77	*/		{  1,	"COLS",			NULL },
	/* xlfOffset		78	*/		{  0,	"",				NULL },
	/* xlfAbsref		79	*/		{  0,	"",				NULL },
	/* xlfRelref		80	*/		{  0,	"",				NULL },
	/* xlfArgument		81	*/		{  0,	"",				NULL },
	/* xlfSearch		82	*/		{  0,	"",				NULL },
	/* xlfTranspose		83	*/		{  1,	"TRANSPOSE",	NULL },
	/* xlfError			84	*/		{  0,	"",				NULL },
	/* xlfStep			85	*/		{  0,	"",				NULL },
	/* xlfType			86	*/		{  0,	"",				NULL },
	/* xlfEcho			87	*/		{  0,	"",				NULL },
	/* xlfSetName		88	*/		{  0,	"",				NULL },
	/* xlfCaller		89	*/		{  0,	"",				NULL },
	/* xlfDeref			90	*/		{  0,	"",				NULL },
	/* xlfWindows		91	*/		{  0,	"",				NULL },
	/* xlfSeries		92	*/		{  0,	"",				NULL },
	/* xlfDocuments		93	*/		{  0,	"",				NULL },
	/* xlfActiveCell	94	*/		{  0,	"",				NULL },
	/* xlfSelection		95	*/		{  0,	"",				NULL },
	/* xlfResult		96	*/		{  0,	"",				NULL },
	/* xlfAtan2			97	*/		{  1,	"ATAN2",		NULL },
	/* xlfAsin			98	*/		{  1,	"ASIN",			NULL },
	/* xlfAcos			99	*/		{  1,	"ACOS",			NULL },
	/* xlfChoose		100	*/		{ -1,	"CHOOSE",		NULL },
	/* xlfHlookup		101	*/		{ -1,	"HLOOKUP",		NULL },		/* Excel has opt arg */
	/* xlfVlookup		102	*/		{ -1,	"VLOOKUP",		NULL },		/* Excel has opt arg */
	/* xlfLinks			103	*/		{  0,	"",				NULL },
	/* xlfInput			104	*/		{  0,	"",				NULL },
	/* xlfIsref			105	*/		{  0,	"",				NULL },
	/* xlfGetFormula	106	*/		{  0,	"",				NULL },
	/* xlfGetName		107	*/		{  0,	"",				NULL },
	/* xlfSetValue		108	*/		{  0,	"",				NULL },
	/* xlfLog			109	*/		{ -1,	"LOG",			NULL },		/* Excel has opt arg */
	/* xlfExec			110	*/		{  0,	"",				NULL },
	/* xlfChar			111	*/		{  1,	"CHAR",			NULL },
	/* xlfLower			112	*/		{  1,	"LOWER",		NULL },
	/* xlfUpper			113	*/		{  1,	"UPPER",		NULL },
	/* xlfProper		114	*/		{  1,	"PROPER",		NULL },		/* Same function ? */
	/* xlfLeft			115	*/		{  0,	"",				NULL },		/* Args don't match */
	/* xlfRight			116	*/		{  0,	"",				NULL },		/* Args don't match */
	/* xlfExact			117	*/		{  2,	"EXACT",		NULL },
	/* xlfTrim			118	*/		{  1,	"TRIM",			NULL },
	/* xlfReplace		119	*/		{  4,	"REPLACE",		NULL },
	/* xlfSubstitute	120	*/		{  0,	"",				NULL },
	/* xlfCode			121	*/		{  1,	"CODE",			NULL },
	/* xlfNames			122	*/		{  0,	"",				NULL },
	/* xlfDirectory		123	*/		{  0,	"",				NULL },
	/* xlfFind			124	*/		{  0,	"",				NULL },		/* Args don't match */
	/* xlfCell			125	*/		{  2,	"CELLINFO",		NULL },
	/* xlfIserr			126	*/		{  1,	"ISERROR",		NULL },
	/* xlfIstext		127	*/		{  1,	"ISSTRING",		NULL },
	/* xlfIsnumber		128	*/		{  1,	"ISNUMBER",		NULL },
	/* xlfIsblank		129	*/		{  0,	"",				NULL },
	/* xlfT				130	*/		{  0,	"",				NULL },		/* Text func in Excel */
	/* xlfN				131	*/		{  0,	"",				NULL },		/* Function doesn't match */
	/* xlfFopen			132	*/		{  0,	"",				NULL },
	/* xlfFclose		133	*/		{  0,	"",				NULL },
	/* xlfFsize			134	*/		{  0,	"",				NULL },
	/* xlfFreadln		135	*/		{  0,	"",				NULL },
	/* xlfFread			136	*/		{  0,	"",				NULL },
	/* xlfFwriteln		137	*/		{  0,	"",				NULL },
	/* xlfFwrite		138	*/		{  0,	"",				NULL },
	/* xlfFpos			139	*/		{  0,	"",				NULL },
	/* xlfDatevalue		140	*/		{  1,	"DATEVALUE",	NULL },
	/* xlfTimevalue		141	*/		{  1,	"TIMEVALUE",	NULL },
	/* xlfSln			142	*/		{  3,	"SLN",			NULL },
	/* xlfSyd			143	*/		{  4,	"SYD",			NULL },
	/* xlfDdb			144	*/		{  0,	"",				NULL },
	/* xlfGetDef		145	*/		{  0,	"",				NULL },
	/* xlfReftext		146	*/		{  0,	"",				NULL },
	/* xlfTextref		147	*/		{  0,	"",				NULL },
	/* xlfIndirect		148	*/		{  0,	"",				NULL },
	/* xlfRegister		149	*/		{  0,	"",				NULL },
	/* xlfCall			150	*/		{  0,	"",				NULL },
	/* xlfAddBar		151	*/		{  0,	"",				NULL },
	/* xlfAddMenu		152	*/		{  0,	"",				NULL },
	/* xlfAddCommand	153	*/		{  0,	"",				NULL },
	/* xlfEnableCommand	154	*/		{  0,	"",				NULL },
	/* xlfCheckCommand	155	*/		{  0,	"",				NULL },
	/* xlfRenameCommand	156	*/		{  0,	"",				NULL },
	/* xlfShowBar		157	*/		{  0,	"",				NULL },
	/* xlfDeleteMenu	158	*/		{  0,	"",				NULL },
	/* xlfDeleteCommand	159	*/		{  0,	"",				NULL },
	/* xlfGetChartItem	160	*/		{  0,	"",				NULL },
	/* xlfDialogBox		161	*/		{  0,	"",				NULL },
	/* xlfClean			162	*/		{  1,	"CLEAN",		NULL },
	/* xlfMdeterm		163	*/		{  0,	"",				NULL },
	/* xlfMinverse		164	*/		{  0,	"",				NULL },
	/* xlfMmult			165	*/		{  2,	"MMUL",			NULL },
	/* xlfFiles			166	*/		{  0,	"",				NULL },
	/* xlfIpmt			167	*/		{ -1,	"IPMT",			NULL },		/* Args don't quite match */
	/* xlfPpmt			168	*/		{  0,	"",				NULL },		/* Args don't match */
	/* xlfCounta		169	*/		{  0,	"",				NULL },
	/* xlfCancelKey		170	*/		{  0,	"",				NULL },
	/*					171	*/		{  0,	NULL,			NULL },
	/*					172	*/		{  0,	NULL,			NULL },
	/*					173	*/		{  0,	NULL,			NULL },
	/*					174	*/		{  0,	NULL,			NULL },
	/* xlfInitiate		175	*/		{  0,	"",				NULL },
	/* xlfRequest		176	*/		{  0,	"",				NULL },
	/* xlfPoke			177	*/		{  0,	"",				NULL },
	/* xlfExecute		178	*/		{  0,	"",				NULL },
	/* xlfTerminate		179	*/		{  0,	"",				NULL },
	/* xlfRestart		180	*/		{  0,	"",				NULL },
	/* xlfHelp			181	*/		{  0,	"",				NULL },
	/* xlfGetBar		182	*/		{  0,	"",				NULL },
	/* xlfProduct		183	*/		{ -1,	"PRODUCT",		NULL },
	/* xlfFact			184	*/		{  1,	"FACT",			NULL },
	/* xlfGetCell		185	*/		{  0,	"",				NULL },
	/* xlfGetWorkspace	186	*/		{  0,	"",				NULL },
	/* xlfGetWindow		187	*/		{  0,	"",				NULL },
	/* xlfGetDocument	188	*/		{  0,	"",				NULL },
	/* xlfDproduct		189	*/		{  0,	"",				NULL },
	/* xlfIsnontext		190	*/		{  0,	"",				NULL },
	/* xlfGetNote		191	*/		{  0,	"",				NULL },
	/* xlfNote			192	*/		{  0,	"",				NULL },
	/* xlfStdevp		193	*/		{  -1,	"STD",			NULL },		/* TKM */
	/* xlfVarp			194	*/		{  -1,	"VAR",			NULL },		/* TKM */
	/* xlfDstdevp		195	*/		{  0,	"",				NULL },
	/* xlfDvarp			196	*/		{  0,	"",				NULL },
	/* xlfTrunc			197	*/		{ -1,	"INT",			NULL },		/* Excel has opt arg */
	/* xlfIslogical		198	*/		{  0,	"",				NULL },
	/* xlfDcounta		199	*/		{  0,	"",				NULL },
	/* xlfDeleteBar		200	*/		{  0,	"",				NULL },
	/* xlfUnregister	201	*/		{  0,	"",				NULL },
	/*					202	*/		{  0,	NULL,			NULL },
	/*					203	*/		{  0,	NULL,			NULL },
	/* xlfUsdollar		204	*/		{  0,	"",				NULL },
	/* xlfFindb			205	*/		{  0,	"",				NULL },
	/* xlfSearchb		206	*/		{  0,	"",				NULL },
	/* xlfReplaceb		207	*/		{  0,	"",				NULL },
	/* xlfLeftb			208	*/		{  0,	"",				NULL },
	/* xlfRightb		209	*/		{  0,	"",				NULL },
	/* xlfMidb			210	*/		{  0,	"",				NULL },
	/* xlfLenb			211	*/		{  0,	"",				NULL },
	/* xlfRoundup		212	*/		{  0,	"",				NULL },
	/* xlfRounddown		213	*/		{  0,	"",				NULL },
	/* xlfAsc			214	*/		{  0,	"",				NULL },
	/* xlfDbcs			215	*/		{  0,	"",				NULL },
	/* xlfRank			216	*/		{ -1,	"RANK",			NULL },
	/*					217	*/		{  0,	NULL,			NULL },
	/*					218	*/		{  0,	NULL,			NULL },
	/* xlfAddress		219	*/		{  0,	"",				NULL },
	/* xlfDays360		220	*/		{  2,	"DAYS360",		NULL },
	/* xlfToday			221	*/		{  0,	"TODAY",		NULL },
	/* xlfVdb			222	*/		{  0,	"",				NULL },		/* Args don't match */
	/*					223	*/		{  0,	NULL,			NULL },
	/*					224	*/		{  0,	NULL,			NULL },
	/*					225	*/		{  0,	NULL,			NULL },
	/*					226	*/		{  0,	NULL,			NULL },
	/* xlfMedian		227	*/		{ -1,	"MEDIAN",		NULL },
	/* xlfSumproduct	228	*/		{ -1,	"SUMPRODUCT",	NULL },		/* Excel has more args */
	/* xlfSinh			229	*/		{  1,	"SINH",			NULL },
	/* xlfCosh			230	*/		{  1,	"COSH",			NULL },
	/* xlfTanh			231	*/		{  1,	"TANH",			NULL },
	/* xlfAsinh			232	*/		{  1,	"ASINH",		NULL },
	/* xlfAcosh			233	*/		{  1,	"ACOSH",		NULL },
	/* xlfAtanh			234	*/		{  1,	"ATANH",		NULL },
	/* xlfDget			235	*/		{  0,	"",				NULL },
	/* xlfCreateObject	236	*/		{  0,	"",				NULL },
	/* xlfVolatile		237	*/		{  0,	"",				NULL },
	/* xlfLastError		238	*/		{  0,	"",				NULL },
	/* xlfCustomUndo	239	*/		{  0,	"",				NULL },
	/* xlfCustomRepeat	240	*/		{  0,	"",				NULL },
	/* xlfFormulaConvert 241*/		{  0,	"",				NULL },
	/* xlfGetLinkInfo	242	*/		{  0,	"",				NULL },
	/* xlfTextBox		243	*/		{  0,	"",				NULL },
	/* xlfInfo			244	*/		{  0,	"",				NULL },
	/* xlfGroup			245	*/		{  0,	"",				NULL },
	/* xlfGetObject		246	*/		{  0,	"",				NULL },
	/* xlfDb			247	*/		{  0,	"",				NULL },
	/* xlfPause			248	*/		{  0,	"",				NULL },
	/*					249	*/		{  0,	NULL,			NULL },
	/*					250	*/		{  0,	NULL,			NULL },
	/* xlfResume		251	*/		{  0,	"",				NULL },
	/* xlfFrequency		252	*/		{  2,	"FREQUENCY",	NULL },
	/* xlfAddToolbar	253	*/		{  0,	"",				NULL },
	/* xlfDeleteToolbar	254	*/		{  0,	"",				NULL },
	/*					255	*/		{  0,	NULL,			NULL },
	/* xlfResetToolbar	256	*/		{  0,	"",				NULL },
	/* xlfEvaluate		257	*/		{  0,	"",				NULL },
	/* xlfGetToolbar	258	*/		{  0,	"",				NULL },
	/* xlfGetTool		259	*/		{  0,	"",				NULL },
	/* xlfSpellingCheck	260	*/		{  0,	"",				NULL },
	/* xlfErrorType		261	*/		{  0,	"",				NULL },
	/* xlfAppTitle		262	*/		{  0,	"",				NULL },
	/* xlfWindowTitle	263	*/		{  0,	"",				NULL },
	/* xlfSaveToolbar	264	*/		{  0,	"",				NULL },
	/* xlfEnableTool	265	*/		{  0,	"",				NULL },
	/* xlfPressTool		266	*/		{  0,	"",				NULL },
	/* xlfRegisterId	267	*/		{  0,	"",				NULL },
	/* xlfGetWorkbook	268	*/		{  0,	"",				NULL },
	/* xlfAvedev		269	*/		{  0,	"",				NULL },
	/* xlfBetadist		270	*/		{  0,	"",				NULL },
	/* xlfGammaln		271	*/		{  0,	"",				NULL },
	/* xlfBetainv		272	*/		{  0,	"",				NULL },
	/* xlfBinomdist		273	*/		{  0,	"",				NULL },
	/* xlfChidist		274	*/		{  0,	"",				NULL },
	/* xlfChiinv		275	*/		{  0,	"",				NULL },
	/* xlfCombin		276	*/		{  0,	"",				NULL },
	/* xlfConfidence	277	*/		{  3,	"CONFIDENCE",	NULL },
	/* xlfCritbinom		278	*/		{  0,	"",				NULL },
	/* xlfEven			279	*/		{  0,	"",				NULL },
	/* xlfExpondist		280	*/		{  0,	"",				NULL },
	/* xlfFdist			281	*/		{  0,	"",				NULL },		/* Similar to F ? */
	/* xlfFinv			282	*/		{  0,	"",				NULL },
	/* xlfFisher		283	*/		{  0,	"",				NULL },
	/* xlfFisherinv		284	*/		{  0,	"",				NULL },
	/* xlfFloor			285	*/		{  2,	"FLOOR",		NULL },		/* Excel has 2 args */
	/* xlfGammadist		286	*/		{  0,	"",				NULL },
	/* xlfGammainv		287	*/		{  0,	"",				NULL },
	/* xlfCeiling		288	*/		{  2,	"CEIL",			NULL },		/* Excel has 2 args */
	/* xlfHypgeomdist	289	*/		{  0,	"",				NULL },
	/* xlfLognormdist	290	*/		{  0,	"",				NULL },
	/* xlfLoginv		291	*/		{  0,	"",				NULL },
	/* xlfNegbinomdist	292	*/		{  0,	"",				NULL },
	/* xlfNormdist		293	*/		{  4,	"NORMDIST",		NULL },
	/* xlfNormsdist		294	*/		{  1,	"NORMSDIST",	NULL },
	/* xlfNorminv		295	*/		{  3,	"NORMINV",		NULL },
	/* xlfNormsinv		296	*/		{  1,	"NORMSINV",		NULL },
	/* xlfStandardize	297	*/		{  3,	"STANDARDIZE",	NULL },
	/* xlfOdd			298	*/		{  0,	"",				NULL },
	/* xlfPermut		299	*/		{  2,	"PERMUT",		NULL },
	/* xlfPoisson		300	*/		{  0,	"",				NULL },
	/* xlfTdist			301	*/		{  0,	"",				NULL },
	/* xlfWeibull		302	*/		{  0,	"",				NULL },
	/* xlfSumxmy2		303	*/		{  0,	"",				NULL },
	/* xlfSumx2my2		304	*/		{  0,	"",				NULL },
	/* xlfSumx2py2		305	*/		{  0,	"",				NULL },
	/* xlfChitest		306	*/		{  0,	"",				NULL },
	/* xlfCorrel		307	*/		{  2,	"CORR",			NULL },
	/* xlfCovar			308	*/		{  0,	"",				NULL },
	/* xlfForecast		309	*/		{  0,	"",				NULL },		/* Args don't match */
	/* xlfFtest			310	*/		{  0,	"",				NULL },		/* Same ? */
	/* xlfIntercept		311	*/		{  0,	"",				NULL },
	/* xlfPearson		312	*/		{  0,	"",				NULL },
	/* xlfRsq			313	*/		{  0,	"",				NULL },
	/* xlfSteyx			314	*/		{  0,	"",				NULL },
	/* xlfSlope			315	*/		{  0,	"",				NULL },
	/* xlfTtest			316	*/		{  0,	"",				NULL },		/* Doesn't match ? */
	/* xlfProb			317	*/		{  0,	"",				NULL },
	/* xlfDevsq			318	*/		{  0,	"",				NULL },
	/* xlfGeomean		319	*/		{ -1,	"GMEAN",		NULL },
	/* xlfHarmean		320	*/		{ -1,	"HMEAN",		NULL },
	/* xlfSumsq			321	*/		{  0,	"",				NULL },
	/* xlfKurt			322	*/		{  0,	"",				NULL },
	/* xlfSkew			323	*/		{  0,	"",				NULL },
	/* xlfZtest			324	*/		{ -1,	"ZTEST",		NULL },
	/* xlfLarge			325	*/		{  2,	"LARGE",		NULL },
	/* xlfSmall			326	*/		{ -1,	"SMALL",		NULL },
	/* xlfQuartile		327	*/		{  2,	"QUARTILE",		NULL },
	/* xlfPercentile	328	*/		{  2,	"PERCENTILE",	NULL },
	/* xlfPercentrank	329	*/		{ -1,	"PERCENTRANK",	NULL },
	/* xlfMode			330	*/		{ -1,	"MODE",			NULL },
	/* xlfTrimmean		331	*/		{  0,	"",				NULL },
	/* xlfTinv			332	*/		{  0,	"",				NULL },
	/*					333	*/		{  0,	NULL,			NULL },
	/*					334	*/		{  0,	NULL,			NULL },
	/*					335	*/		{  0,	NULL,			NULL },
	/* xlfConcatenate	336	*/		{ -1,	"STRCAT",		NULL },
	};

extern gxKeyword * __cdecl _gx_fn_lookup(LPCTSTR text);


XlsFuncRec* gx_xls_func_lookup (int index)
{
	//gxKeyword	*fnp;

	if ((index < 0) || (index > LAST_FUNC))
		return NULL;
	else if (func_table[index].nexs_func == NULL)
		return NULL;
	else if (func_table[index].nexs_func[0] == '\0')
		return NULL;
	else
		{
		if (func_table[index].fnp == NULL)
			func_table[index].fnp = _gx_fn_lookup (func_table[index].nexs_func);
		return &func_table[index];
		}
}

int		xls_get_xlf_arg_count (int index)
{
	return func_table[index].num_xl_args;
}

