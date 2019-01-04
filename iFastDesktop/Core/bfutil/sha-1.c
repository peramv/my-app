/**
 * FILE     :  sha-1.c
 *
 * AUTHOR   :  Ram Singaram
 *
 * COPYRIGHT:
 *
 *   The computer systems, procedures, data bases and programs
 *   created and maintained by IFDS Canada, Ltd., are proprietary
 *   in nature and as such are confidential.  Any unauthorized
 *   use or disclosure of such information may result in civil
 *   liabilities.
 *
 *   Copyright 2001 by IFDS Canada, Ltd.
 *   All Rights Reserved.
 */
#include "sha-1.h"
#include <cstdlib>
#include <cstdio>
#include <cstring>


typedef unsigned int  Word;

static const Byte one = 0x80;
static const Byte zero = 0x00;

static const Word K0 = 0x5A827999;
static const Word K1 = 0x6ED9EBA1;
static const Word K2 = 0x8F1BBCDC;
static const Word K3 = 0xCA62C1D6;

Byte block[64];
Word A,B,C,D,E;
Word W[80];

Word getS(int , Word );
Word getW(int);
Word getK(int);
Word XplusY(Word , Word );
void printWord(char *, int, Word );
Word func(int);
Word getWord( Byte * );
void copyWord( Byte *, Word );

Byte* DigestMessage( const Byte *src, unsigned int srcLen )
{

   Word H0 = 0x67452301;
   Word H1 = 0xEFCDAB89;
   Word H2 = 0x98BADCFE;
   Word H3 = 0x10325476;
   Word H4 = 0xC3D2E1F0;

   unsigned int numZeroBytes = 0;
   unsigned int i, j;
   int t;

   Byte *result = 0;

   Word srcLenInBits = 0;
   Word TEMP;

   if( srcLen > 54 )
      return(0);

   result = (Byte *) malloc(41 * sizeof(Byte));

   memcpy(block, src, srcLen);
   block[srcLen] = one;

   numZeroBytes = 59 - srcLen;

   j = srcLen + 1;
   for( i = 0 ; i < numZeroBytes; i++ )
   {
      block[j] = zero;
      j++;
   }

   srcLenInBits = srcLen * 8;

   //memcpy(&block[j], (void *)(&srcLenInBits), 4);
   copyWord(&block[j], srcLenInBits);

   A = H0;
   B = H1;
   C = H2;
   D = H3; 
   E = H4;


   for( t = 0; t < 80; t++ )
   {
      //S5(A) + ft(B,C,D) + E + Wt + Kt; 
      TEMP = XplusY( getS(5,A), func(t) );
      TEMP = XplusY( TEMP, E);
      TEMP = XplusY( TEMP, getW(t));
      TEMP = XplusY( TEMP, getK(t));

      //E = D; D = C; C = S30(B); B = A; A = TEMP; 
      E = D;
      D = C; 
      C = getS(30,B); 
      B = A; 
      A = TEMP; 
   }

   //H0 = H0 + A, H1 = H1 + B, H2 = H2 + C, H3 = H3 + D, H4 = H4 + E.
   H0 = XplusY(H0,A);
   H1 = XplusY(H1,B);
   H2 = XplusY(H2,C);
   H3 = XplusY(H3,D); 
   H4 = XplusY(H4,E);

   sprintf((char *) result, "%8.8x", H0);
   sprintf((char *) &result[8], "%8.8x", H1);
   sprintf((char *) &result[16], "%8.8x", H2);
   sprintf((char *) &result[24], "%8.8x", H3);
   sprintf((char *) &result[32], "%8.8x", H4);
   result[40] = 0x0;

   return(result);

}

/**
 *
 * K0 = 0x5A827999; ( 0 <= t <= 19) 
 * K1 = 0x6ED9EBA1; (20 <= t <= 39) 
 * K2 = 0x8F1BBCDC; (40 <= t <= 59) 
 * K3 = 0xCA62C1D6; (60 <= t <= 79)
 *
 */
Word getK(int t)
{
   if( t >= 0 && t <= 19 )
      return(K0);
   else if( t >=20 && t <= 39 )
      return(K1);
   else if( t >=40 && t <= 59 )
      return(K2);
   else if( t >=60 && t <= 79 )
      return(K3);
   return( 0 );
}


Word getW(int t)
{
   Byte* p;
   Word tmp;

   if( t >=0 && t <= 15 )
   {
      p = &block[t * 4];
      //memcpy(&W[t], p, 4);
      W[t] = getWord(p);
   }
   else
   {
      tmp = (W[t-3] ^ W[t-8] ^ W[t-14] ^ W[t-16]);
      W[t] = getS(1, tmp);
   }

   return(W[t]);
}


Word getS(int n, Word X)
{
   Word qq;
   qq = ((X << n) | (X >> (32-n))); 
   return(qq);
}


Word XplusY( Word X, Word Y)
{
   return( X + Y );
}



/**
 *
 * ft(B,C,D) = (B AND C) OR ((NOT B) AND D) ( 0 <= t <= 19) 
 *
 * ft(B,C,D) = B XOR C XOR D (20 <= t <= 39) 
 *
 * ft(B,C,D) = (B AND C) OR (B AND D) OR (C AND D) (40 <= t <= 59) 
 *
 * ft(B,C,D) = B XOR C XOR D (60 <= t <= 79)
 *
 */
Word func(int t)
{
   if( t >= 0 && t <= 19 )
      return((B & C) | ((~B)& D));
   else if( t >=20 && t <= 39 )
      return( B ^ C ^ D );
   else if( t >=40 && t <= 59 )
      return( (B & C) | (B & D) | (C & D) );
   else if( t >=60 && t <= 79 )
      return( B ^ C ^ D );
   return( 0 );
}


void copyWord(Byte * copyTo, Word wordToCopy)
{
#if defined(_WIN32)

   Byte *copyFrom = (Byte *) &wordToCopy;
   *copyTo = *(copyFrom + 3);
   *(copyTo + 1) = *(copyFrom + 2);
   *(copyTo + 2) = *(copyFrom + 1);
   *(copyTo + 3) = *copyFrom;

#else

   memcpy(copyTo, (void *)(&wordToCopy), 4);

#endif


}



Word getWord(Byte * byteAddress)
{

   Word tmp;

#if defined(_WIN32)

   Byte *bp = (Byte *) &tmp;
   *bp = *(byteAddress + 3);
   *(bp + 1) = *(byteAddress + 2);
   *(bp + 2) = *(byteAddress + 1);
   *(bp + 3) = *byteAddress;

#else

   memcpy(&tmp, byteAddress, 4);

#endif

   return(tmp);

}


void printWord( char * title, int d, Word qq)
{
   printf("\n%s[%d] : %8.8x",title,d,qq);
}
