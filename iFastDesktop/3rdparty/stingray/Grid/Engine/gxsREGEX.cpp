///////////////////////////////////////////////////////////////////////////////
// gxsregex.cpp: String comparision with regular expressions
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
typedef unsigned char TBYTE;
#endif

/*
 * regex - Regular expression pattern matching
 *         and replacement
 *
 *
 * By:  Ozan S. Yigit (oz)
 *      Dept. of Computer Science
 *      York University
 *
 *
 * These routines are the PUBLIC DOMAIN equivalents
 * of regex routines as found in 4.nBSD UN*X, with minor
 * extensions.
 *
 * These routines are derived from various implementations
 * found in software tools books, and Conroy's grep. They
 * are NOT derived from licensed/restricted software.
 * For more interesting/academic/complicated implementations,
 * see Henry Spencer's regexp routines, or GNU Emacs pattern
 * matching module.
 *
 * Routines:
 *      _gx_XSre_comp:        compile a regular expression into
 *                      a DFA.
 *
 *          TCHAR *_gx_XSre_comp(s)
 *          TCHAR *s;
 *
 *      _gx_XSre_exec:        execute the DFA to match a pattern.
 *
 *          int _gx_XSre_exec(s)
 *          TCHAR *s;
 *
 *  _gx_XSre_modw       change _gx_XSre_exec's understanding of what
 *          a "word" looks like (for \< and \>)
 *          by adding into the hidden word-character
 *          table.
 *
 *          void _gx_XSre_modw(s)
 *          TCHAR *s;
 *
 *      _gx_XSre_subs:  substitute the matched portions in
 *                  a new string.
 *
 *          int _gx_XSre_subs(src, dst)
 *          TCHAR *src;
 *          TCHAR *dst;
 *
 *  _gx_XSre_fail:  failure routine for _gx_XSre_exec.
 *
 *          void _gx_XSre_fail(msg, op)
 *          TCHAR *msg;
 *          TCHAR op;
 *
 * Regular Expressions:
 *
 *      [1]     TCHAR    matches itself, unless it is a special
 *                      character (metachar): . \ [ ] * + ^ $
 *
 *      [2]     .       matches any character.
 *
 *      [3]     \       matches the character following it, except
 *          when followed by a left or right round bracket,
 *          a digit 1 to 9 or a left or right angle bracket.
 *          (see [7], [8] and [9])
 *          It is used as an escape character for all
 *          other meta-characters, and itself. When used
 *          in a set ([4]), it is treated as an ordinary
 *          character.
 *
 *      [4]     [set]   matches one of the characters in the set.
 *                      If the first character in the set is "^",
 *                      it matches a character NOT in the set. A
 *                      shorthand S-E is used to specify a set of
 *                      characters S upto E, inclusive. The special
 *                      characters "]" and "-" have no special
 *                      meaning if they appear as the first chars
 *                      in the set.
 *                      examples:        match:
 *
 *                              [a-z]    any lowercase alpha
 *
 *                              [^]-]    any TCHAR except ] and -
 *
 *                              [^A-Z]   any TCHAR except uppercase
 *                                       alpha
 *
 *                              [a-zA-Z] any alpha
 *
 *      [5]     *       any regular expression form [1] to [4], followed by
 *                      closure TCHAR (*) matches zero or more matches of
 *                      that form.
 *
 *      [6]     +       same as [5], except it matches one or more.
 *
 *      [7]             a regular expression in the form [1] to [10], enclosed
 *                      as \(form\) matches what form matches. The enclosure
 *                      creates a set of tags, used for [8] and for
 *                      pattern substution. The tagged forms are numbered
 *          starting from 1.
 *
 *      [8]             a \ followed by a digit 1 to 9 matches whatever a
 *                      previously tagged regular expression ([7]) matched.
 *
 *  [9] \<  a regular expression starting with a \< construct
 *      \>  and/or ending with a \> construct, restricts the
 *          pattern matching to the beginning of a word, and/or
 *          the end of a word. A word is defined to be a character
 *          string beginning and/or ending with the characters
 *          A-Z a-z 0-9 and _. It must also be preceded and/or
 *          followed by any character outside those mentioned.
 *
 *      [10]            a composite regular expression xy where x and y
 *                      are in the form [1] to [10] matches the longest
 *                      match of x followed by a match for y.
 *
 *      [11]    ^   a regular expression starting with a ^ character
 *      $   and/or ending with a $ character, restricts the
 *                      pattern matching to the beginning of the line,
 *                      or the end of line. [anchors] Elsewhere in the
 *          pattern, ^ and $ are treated as ordinary characters.
 *
 *
 * Acknowledgements:
 *
 *  HCR's Hugh Redelmeier has been most helpful in various
 *  stages of development. He convinced me to include BOW
 *  and EOW constructs, originally invented by Rob Pike at
 *  the University of Toronto.
 *
 * References:
 *              Software tools          Kernighan & Plauger
 *		Software tools in PASCAL	 Kernighan & Plauger
 *              Grep [rsx-11 C dist]            David Conroy
 *      ed - text editor        Un*x Programmer's Manual
 *      Advanced editing on Un*x    B. W. Kernighan
 *      RegExp routines         Henry Spencer
 *
 * Notes:
 *
 *  This implementation uses a bit-set representation for character
 *  classes for speed and compactness. Each character is represented
 *  by one bit in a 128-bit block. Thus, CCL or NCL always takes a
 *  constant 16 bytes in the internal dfa, and _gx_XSre_exec does a single
 *  bit comparison to locate the character in the set.
 *
 * Examples:
 *
 *  pattern:    foo*.*
 *  compile:    CHR f CHR o CLO CHR o END CLO ANY END END
 *  matches:    fo foo fooo foobar fobar foxx ...
 *
 *  pattern:    fo[ob]a[rz]
 *  compile:    CHR f CHR o CCL 2 o b CHR a CCL bitset END
 *  matches:    fobar fooar fobaz fooaz
 *
 *  pattern:    foo\\+
 *  compile:    CHR f CHR o CHR o CHR \ CLO CHR \ END END
 *  matches:    foo\ foo\\ foo\\\  ...
 *
 *  pattern:    \(foo\)[1-3]\1  (same as foo[1-3]foo)
 *  compile:    BOT 1 CHR f CHR o CHR o EOT 1 CCL bitset REF 1 END
 *  matches:    foo1foo foo2foo foo3foo
 *
 *  pattern:    \(fo.*\)-\1
 *  compile:    BOT 1 CHR f CHR o CLO ANY END EOT 1 CHR - REF 1 END
 *  matches:    foo-foo fo-fo fob-fob foobar-foobar ...
 *
 */

#define MAXDFA  1024
#define MAXTAG  10

#define OKP     1
#define NOP     0

#define CHR     1
#define ANY     2
#define CCL     3
#define NCL     4
#define BOL     5
#define EOL     6
#define BOT     7
#define EOT     8
#define BOW 9
#define EOW 10
#define REF     11
#define CLO     12

#define END     0

/*
 * The following defines are not meant
 * to be changeable. They are for readibility
 * only.
 *
 */
#define MAXCHR  128
#define CHRBIT  8
#define BITBLK  MAXCHR/CHRBIT
#define BLKIND  0170
#define BITIND  07

#define ASCIIB  0177

// typedef /* unsigned */ TCHAR TCHAR;

// SH->

class GX_REGEX_STATE: public CObject
{
public:
	GX_REGEX_STATE();
	~GX_REGEX_STATE();

	int tagstk[MAXTAG];  /* subpat tag stack.. */
	TCHAR dfa[MAXDFA];    /* automaton..       */
	int sta;   /* status of lastpat */

	TCHAR bittab[BITBLK]; /* bit table for CCL */
	TCHAR *bol;
	TCHAR *bopat[MAXTAG];
	TCHAR *eopat[MAXTAG];
};

GX_REGEX_STATE::GX_REGEX_STATE()
{
	memset(tagstk, 0, sizeof(int)*MAXTAG);
	memset(dfa, 0, sizeof(TCHAR)*MAXDFA);
	sta = NOP;   /* status of lastpat */

	memset(bittab, 0, sizeof(TCHAR)*BITBLK);
	bol = NULL;
	memset(bopat, 0, sizeof(TCHAR*)*MAXTAG);
	memset(eopat, 0, sizeof(TCHAR*)*MAXTAG);
}

GX_REGEX_STATE::~GX_REGEX_STATE()
{
}

GX_REGEX_STATE* GXGetRegexState()
{
	CGXAppData* pAppData = GXGetAppData();
	if (pAppData->m_pRegexState == NULL)
		pAppData->m_pRegexState = new GX_REGEX_STATE;

	return (GX_REGEX_STATE*) pAppData->m_pRegexState;
}

// static int tagstk[MAXTAG];  /* subpat tag stack.. */
// static TCHAR dfa[MAXDFA];    /* automaton..       */
// static int sta = NOP;   /* status of lastpat */

// static TCHAR bittab[BITBLK]; /* bit table for CCL */

static void chset(TCHAR c)
{
	GXGetRegexState()->bittab[((c) & BLKIND) >> 3] |= 1 << ((c) & BITIND);
}

#define badpat(x)   return(*GXGetRegexState()->dfa = END, x)
#define store(x)    *mp++ = (TCHAR) x

static TCHAR *pmatch(TCHAR *lp, TCHAR * ap);

TCHAR * __cdecl _gx_XSre_comp(TCHAR *pat)
{
	register TCHAR *p;   /* pattern pointer   */
	register TCHAR *mp = GXGetRegexState()->dfa;    /* dfa pointer       */
	register TCHAR *lp;  /* saved pointer..   */
	register TCHAR *sp = GXGetRegexState()->dfa;    /* another one..     */

	register int tagi = 0;  /* tag stack index   */
	register int tagc = 1;  /* actual tag count  */

	register int n;
	int c1,
		c2;

	if (!pat || !*pat)
		if (GXGetRegexState()->sta)
			return (0);
		else
			badpat(_T("No previous regular expression"));
	GXGetRegexState()->sta = NOP;

	for (p = pat; *p; p++)
	{
		lp = mp;
		switch (*p)
		{

		case _T('.'):   /* match any TCHAR..  */
			store(ANY);
			break;

		case _T('^'):   /* match beginning.. */
			if (p == pat)
				store(BOL);
			else
			{
				store(CHR);
				store(*p);
			}
			break;

		case _T('$'):   /* match endofline.. */
			if (!*(p + 1))
				store(EOL);
			else
			{
				store(CHR);
				store(*p);
			}
			break;

		case _T('['):   /* match TCHAR class.. */

			if (*++p == _T('^'))
			{
				store(NCL);
				p++;
			}
			else
				store(CCL);

			if (*p == _T('-'))  /* real dash */
				chset(*p++);
			if (*p == _T(']'))  /* real brac */
				chset(*p++);
			while (*p && *p != _T(']'))
			{
				if (*p == _T('-') && *(p + 1) && *(p + 1) != _T(']'))
				{
					p++;
					c1 = *(p - 2) + 1;
					c2 = *p++;
					while (c1 <= c2)
						chset((TBYTE) c1++);
				}
#ifdef EXTEND
				else if (*p == _T('\\') && *(p + 1))
				{
					p++;
					chset(*p++);
				}
#endif
				else
					chset(*p++);
			}
			if (!*p)
				badpat(_T("Missing ]"));

			for (n = 0; n < BITBLK; GXGetRegexState()->bittab[n++] = (TCHAR) 0)
				store(GXGetRegexState()->bittab[n]);

			break;

		case _T('*'):   /* match 0 or more.. */
		case _T('+'):   /* match 1 or more.. */
			if (p == pat)
				badpat(_T("Empty closure"));
			lp = sp;    /* previous opcode */
			if (*lp == CLO) /* equivalence..   */
				break;
			switch (*lp)
			{

			case BOL:
			case BOT:
			case EOT:
			case BOW:
			case EOW:
			case REF:
				badpat(_T("Illegal closure"));
			default:
				break;
			}

			if (*p == _T('+'))
				for (sp = mp; lp < sp; lp++)
					store(*lp);

			store(END);
			store(END);
			sp = mp;
			while (--mp > lp)
				*mp = mp[-1];
			store(CLO);
			mp = sp;
			break;

		case _T('\\'):  /* tags, backrefs .. */
			switch (*++p)
			{

			case _T('('):
				if (tagc < MAXTAG)
				{
					GXGetRegexState()->tagstk[++tagi] = tagc;
					store(BOT);
					store(tagc++);
				}
				else
					badpat(_T("Too many \\(\\) pairs"));
				break;
			case _T(')'):
				if (*sp == BOT)
					badpat(_T("Null pattern inside \\(\\)"));
				if (tagi > 0)
				{
					store(EOT);
					store(GXGetRegexState()->tagstk[tagi--]);
				}
				else
					badpat(_T("Unmatched \\)"));
				break;
			case _T('<'):
				store(BOW);
				break;
			case _T('>'):
				if (*sp == BOW)
					badpat(_T("Null pattern inside \\<\\>"));
				store(EOW);
				break;
			case _T('1'):
			case _T('2'):
			case _T('3'):
			case _T('4'):
			case _T('5'):
			case _T('6'):
			case _T('7'):
			case _T('8'):
			case _T('9'):
				n = *p - _T('0');
				if (tagi > 0 && GXGetRegexState()->tagstk[tagi] == n)
					badpat(_T("Cyclical reference"));
				if (tagc > n)
				{
					store(REF);
					store(n);
				}
				else
					badpat(_T("Undetermined reference"));
				break;
#ifdef EXTEND
			case _T('b'):
				store(CHR);
				store(_T('\b'));
				break;
			case _T('n'):
				store(CHR);
				store(_T('\n'));
				break;
			case _T('f'):
				store(CHR);
				store(_T('\f'));
				break;
			case _T('r'):
				store(CHR);
				store_T(('\r)');
				break;
			case _T('t'):
				store(CHR);
				store(_T('\t'));
				break;
#endif
			default:
				store(CHR);
				store(*p);
			}
			break;

		default:    /* an ordinary TCHAR  */
			store(CHR);
			store(*p);
			break;
		}
		sp = lp;
	}
	if (tagi > 0)
		badpat(_T("Unmatched \\("));
	store(END);
	GXGetRegexState()->sta = OKP;
	return (0);
}


//static TCHAR *bol;
//static TCHAR *bopat[MAXTAG];
//static TCHAR *eopat[MAXTAG];

/*
 * _gx_XSre_exec:
 *  execute dfa to find a match.
 *
 *  special cases: (dfa[0])
 *      BOL
 *          Match only once, starting from the
 *          beginning.
 *      CHR
 *          First locate the character without
 *          calling pmatch, and if found, call
 *          pmatch for the remaining string.
 *      END
 *          _gx_XSre_comp failed, poor luser did not
 *          check for it. Fail fast.
 *
 *  If a match is found, bopat[0] and eopat[0] are set
 *  to the beginning and the end of the matched fragment,
 *  respectively.
 *
 */

int  __cdecl _gx_XSre_exec(TCHAR *lp)
{
	register TCHAR c;
	register TCHAR *ep = 0;
	register TCHAR *ap = GXGetRegexState()->dfa;

	GXGetRegexState()->bol = lp;

	GXGetRegexState()->bopat[0] = 0;
	GXGetRegexState()->bopat[1] = 0;
	GXGetRegexState()->bopat[2] = 0;
	GXGetRegexState()->bopat[3] = 0;
	GXGetRegexState()->bopat[4] = 0;
	GXGetRegexState()->bopat[5] = 0;
	GXGetRegexState()->bopat[6] = 0;
	GXGetRegexState()->bopat[7] = 0;
	GXGetRegexState()->bopat[8] = 0;
	GXGetRegexState()->bopat[9] = 0;

	switch (*ap)
	{

	case BOL:   /* anchored: match from BOL only */
		ep = pmatch(lp, ap);
		break;
	case CHR:   /* ordinary TCHAR: locate it fast */
		c = *(ap + 1);
		while (*lp && *lp != c)
			lp++;
		if (!*lp)   /* if EOS, fail, else fall thru. */
			return (0);
	default:    /* regular matching all the way. */
		while (*lp)
		{
			if (((ep = pmatch(lp, ap))) != NULL)
				break;
			lp++;
		}
		break;
	case END:   /* munged automaton. fail always */
		return (0);
	}
	if (!ep)
		return (0);

	GXGetRegexState()->bopat[0] = lp;
	GXGetRegexState()->eopat[0] = ep;
	return (1);
}

/*
 * pmatch:
 *  internal routine for the hard part
 *
 *  This code is mostly snarfed from an early
 *  grep written by David Conroy. The backref and
 *  tag stuff, and various other mods are by oZ.
 *
 *  special cases: (dfa[n], dfa[n+1])
 *      CLO ANY
 *          We KNOW ".*" will match ANYTHING
 *          upto the end of line. Thus, go to
 *          the end of line straight, without
 *          calling pmatch recursively. As in
 *          the other closure cases, the remaining
 *          pattern must be matched by moving
 *          backwards on the string recursively,
 *          to find a match for xy (x is ".*" and
 *          y is the remaining pattern) where
 *          the match satisfies the LONGEST match
 *          for x followed by a match for y.
 *      CLO CHR
 *          We can again scan the string forward
 *          for the single TCHAR without recursion,
 *          and at the point of failure, we execute
 *          the remaining dfa recursively, as
 *          described above.
 *
 *  At the end of a successful match, bopat[n] and eopat[n]
 *  are set to the beginning and end of subpatterns matched
 *  by tagged expressions (n = 1 to 9).
 *
 */

extern void __cdecl _gx_XSre_fail(TCHAR *s, TCHAR c);

/*
 * character classification table for word boundary
 * operators BOW and EOW. the reason for not using
 * ctype macros is that we can let the user add into
 * our own table. see _gx_XSre_modw. This table is not in
 * the bitset form, since we may wish to extend it
 * in the future for other character classifications.
 *
 *  TRUE for 0-9 A-Z a-z _
 */
static TCHAR chrtyp[MAXCHR] = {
	0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
	0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
	0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
	0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
	0, 0, 0, 0, 0, 0, 0, 0, 1, 1,
	1, 1, 1, 1, 1, 1, 1, 1, 0, 0,
	0, 0, 0, 0, 0, 1, 1, 1, 1, 1,
	1, 1, 1, 1, 1, 1, 1, 1, 1, 1,
	1, 1, 1, 1, 1, 1, 1, 1, 1, 1,
	1, 0, 0, 0, 0, 1, 0, 1, 1, 1,
	1, 1, 1, 1, 1, 1, 1, 1, 1, 1,
	1, 1, 1, 1, 1, 1, 1, 1, 1, 1,
	1, 1, 1, 0, 0, 0, 0, 0
};

#define inascii(x)  (0177&(x))
#define iswordc(x)  chrtyp[inascii(x)]
#define isinset(x,y)    ((x)[((y)&BLKIND)>>3] & (1<<((y)&BITIND)))

/*
 * skip values for CLO XXX to skip past the closure
 *
 */

#define ANYSKIP 2   /* CLO ANY END ...     */
#define CHRSKIP 3   /* CLO CHR chr END ...     */
#define CCLSKIP 18  /* CLO CCL 16bytes END ... */

static TCHAR *pmatch(TCHAR *lp, TCHAR * ap)
{
	register TCHAR *e;   /* extra pointer for CLO */
	register TCHAR *bp;  /* beginning of subpat.. */
	register TCHAR *ep;  /* ending of subpat..    */
	register TCHAR op,
		c,
		n;
	TCHAR *are;  /* to save the line ptr. */

	while ((op = *ap++) != END)
		switch (op)
		{

		case CHR:
			if (*lp++ != *ap++)
				return (0);
			break;
		case ANY:
			if (!*lp++)
				return (0);
			break;
		case CCL:
			c = *lp++;
			if (!isinset(ap, c))
				return (0);
			ap += BITBLK;
			break;
		case NCL:
			c = *lp++;
			if (isinset(ap, c))
				return (0);
			ap += BITBLK;
			break;
		case BOL:
			if (lp != GXGetRegexState()->bol)
				return (0);
			break;
		case EOL:
			if (*lp)
				return (0);
			break;
		case BOT:
			GXGetRegexState()->bopat[*ap++] = lp;
			break;
		case EOT:
			GXGetRegexState()->eopat[*ap++] = lp;
			break;
		case BOW:
			if (!(lp != GXGetRegexState()->bol && iswordc(lp[-1])) && iswordc(*lp))
				break;
			return (0);
		case EOW:
			if ((lp != GXGetRegexState()->bol && iswordc(lp[-1])) && !iswordc(*lp))
				break;
			return (0);
		case REF:
			n = *ap++;
			bp = GXGetRegexState()->bopat[n];
			ep = GXGetRegexState()->eopat[n];
			while (bp < ep)
				if (*bp++ != *lp++)
					return (0);
			break;
		case CLO:
			are = lp;
			switch (*ap)
			{

			case ANY:
				while (*lp)
					lp++;
				n = ANYSKIP;
				break;
			case CHR:
				c = *(ap + 1);
				while (*lp && c == *lp)
					lp++;
				n = CHRSKIP;
				break;
			case CCL:
			case NCL:
				while (*lp && ((e = pmatch(lp, ap))) != NULL)
					lp = e;
				n = CCLSKIP;
				break;
			default:
				_gx_XSre_fail(_T("closure: bad dfa."), *ap);
				return (0);
			}

			ap += n;

			while (lp >= are)
			{
				if ((e = pmatch(lp, ap)) != NULL)
					return (e);
				--lp;
			}
			return (0);
		default:
			_gx_XSre_fail(_T("re_exec: bad dfa."), op);
			return (0);
		}
	return (lp);
}

/*
 * _gx_XSre_modw:
 *  add new characters into the word table to
 *  change the _gx_XSre_exec's understanding of what
 *  a word should look like. Note that we only
 *  accept additions into the word definition.
 *
 *  If the string parameter is 0 or null string,
 *  the table is reset back to the default, which
 *  contains A-Z a-z 0-9 _. [We use the compact
 *  bitset representation for the default table]
 *
 */

static int deftab[16] = {
	0, 0, 0, 0, 0, 0, 0377, 003, 0376, 0377, 0377, 0207,
	0376, 0377, 0377, 007
};

void  __cdecl _gx_XSre_modw(TCHAR *s)
{
	register int i;

	if (!s || !*s)
	{
		for (i = 0; i < MAXCHR; i++)
			if (!isinset(deftab, i))
				iswordc(i) = 0;
	}
	else
		while (*s)
			iswordc(*s++) = 1;
}

/*
 * _gx_XSre_subs:
 *  substitute the matched portions of the src in
 *  dst.
 *
 *  &   substitute the entire matched pattern.
 *
 *  \digit  substitute a subpattern, with the given
 *      tag number. Tags are numbered from 1 to
 *      9. If the particular tagged subpattern
 *      does not exist, null is substituted.
 *
 */
int  __cdecl _gx_XSre_subs(TCHAR *src, TCHAR *dst)
{
	register TCHAR c;
	register int pin;
	register TCHAR *bp;
	register TCHAR *ep;

	if (!*src || !GXGetRegexState()->bopat[0])
		return (0);

	while ((c = *src++) != 0)
	{
		switch (c)
		{

		case _T('&'):
			pin = 0;
			break;

		case _T('\\'):
			c = *src++;
			if (c >= _T('0') && c <= _T('9'))
			{
				pin = c - _T('0');
				break;
			}
		default:
			*dst++ = c;
			continue;
		}

		if (((bp = GXGetRegexState()->bopat[pin]) != NULL) && ((ep = GXGetRegexState()->eopat[pin])) != NULL)
		{
			while (*bp && bp < ep)
				*dst++ = *bp++;
			if (bp < ep)
				return (0);
		}
	}
	*dst = (TCHAR) 0;
	return (1);
}

#if 0 
/*
 * symbolic - produce a symbolic dump of the
 *            dfa
 */
void symbolic(TCHAR *s)
{
	_tprintf(_T("pattern: %s\n"), s);
	_tprintf(_T("dfacode:\n"));
	dfadump(GXGetRegexState()->dfa);
}

static dfadump(TCHAR * ap)
{
	register int n;

	while (*ap != END)
		switch (*ap++)
		{
		case CLO:
			_tprintf(_T("CLOSURE"));
			dfadump(ap);
			switch (*ap)
			{
			case CHR:
				n = CHRSKIP;
				break;
			case ANY:
				n = ANYSKIP;
				break;
			case CCL:
			case NCL:
				n = CCLSKIP;
				break;
			}
			ap += n;
			break;
		case CHR:
			_tprintf(_T("\tCHR %c\n"), *ap++);
			break;
		case ANY:
			_tprintf(_T("\tANY .\n"));
			break;
		case BOL:
			_tprintf(_T("\tBOL -\n"));
			break;
		case EOL:
			_tprintf(_T("\tEOL -\n"));
			break;
		case BOT:
			_tprintf(_T("BOT: %d\n"), *ap++);
			break;
		case EOT:
			_tprintf(_T("EOT: %d\n"), *ap++);
			break;
		case BOW:
			_tprintf(_T("BOW\n"));
			break;
		case EOW:
			_tprintf(_T("EOW\n"));
			break;
		case REF:
			_tprintf(_T("REF: %d\n"), *ap++);
			break;
		case CCL:
			_tprintf(_T("\tCCL ["));
			for (n = 0; n < MAXCHR; n++)
				if (isinset(ap, (TCHAR) n))
					_tprintf(_T("%c"), n);
			_tprintf(_T("]\n"));
			ap += BITBLK;
			break;
		case NCL:
			_tprintf(_T("\tNCL ["));
			for (n = 0; n < MAXCHR; n++)
				if (isinset(ap, (TCHAR) n))
					_tprintf(_T("%c"), n);
			_tprintf(_T("]\n"));
			ap += BITBLK;
			break;
		default:
			_tprintf(_T("bad dfa. opcode %o\n"), ap[-1]);
			quit(1);
			break;
		}
}
#endif


/*
 * _gx_XSre_fail:
 *  internal error handler for _gx_XSre_exec.
 *
 *  should probably do something like a
 *  longjump to recover gracefully.
 */
void __cdecl _gx_XSre_fail(TCHAR *s, TCHAR c)
{
	s,c;
	//TCHAR text[100];

	// RaiseException( GX_REG_ERR_BADDFA, 0, 0, 0);
	// _stprintf(text, "%s [opcode %o]\n", s, c);
	// _gx_xs_error(_gx_get_expr_si(), GX_FATAL_ERROR, GX_ERROR_FILE,
	// "regex", 0, text);
}
