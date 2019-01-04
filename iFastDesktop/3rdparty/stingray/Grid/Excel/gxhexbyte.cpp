///////////////////////////////////////////////////////////////////////////////
// gxhexbyte.cpp
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

// This if from a MS sample and is used for testing. You can use the routines provided for testing 
// fields

//****************************************************************************
//
// Purpose: Contains the functions to convert string data in hexdecimal format
//			to binary data.
//
// Functions:
//    Hex2BytesW() 	Converts a UNICODE string in hexdecimal format to binary values.
//	  Hex2BytesA()  Converts an ASCII string in hexdecimal format to binary values.
//	  Char2HexW()   Helper function for Hex2BytesW.  Converts a single hex character
//					(UNICODE) to a binary value.
//	  Char2HexA()	Helper function for Hex2BytesA.  Converts a single hex character
//					(ASCII) to a binary value.
//
//
// Development Team:
//     Geoff Darst
//
// Written by Microsoft Product Support Services, Windows Developer Support
// 
// 

#define _OG_EXPORT_IMPL

#include "stdafx.h"

#include <windows.h>
#include <stdlib.h>
#include "grid\gxhexbyte.h"

#pragma warning(disable: 4244)

//***********************************************************************
// Function: Hex2BytesW
//
// Purpose: Converts a hexadecimal formated UNICODE string to binary data.            
//
// Parameters:  
//		szRecord	A string buffer containing a hexdecimal formatted UNICODE 
//					string.  For example:  "10af721c"
//		pByte		A pointer to a buffer where the converted string will be 
//					written out as binary data.
//
// Returns: A LONG representing the number of bytes written to the buffer.
//
// Comments:  Uses Char2HexW.  Because we are converting hexdecimal strings
//			  to Bytes we need to remember that it takes two hex characters
//		      to make up a byte.where "FF" == 255 == 2^8 == 1 byte.  For that 
//			  reason, we have to convert 2 characters and add them together 
//			  to create a byte.
//
// History:  Date       Author          Reason
//           3/6/96    Geoff Darst      Created
//*************************************************************************

LONG WINAPI Hex2BytesW(LPWSTR szRecord, 
                       PBYTE pBuf)
{
	PWCHAR pwch;
	BYTE nHighVal, nLowVal;
	LONG cbBytesOut = 0;

	for (pwch = szRecord; *pwch != '\0'; pwch++){
		
		// The following two lines will generate a compiler
		// warning which can be safely ignored:
		// warning c4244: 'function' : conversion from 'unsigned 
		// short' to 'char' possible loss of data
		
		nHighVal = Char2HexW(*pwch);
		nLowVal = Char2HexW(*(++pwch));
		
		if (0xFF == nHighVal || 0xFF == nLowVal)
			return 0;
		else
			// Construct a byte:  Offset the first integer
			// by 16 and add it to the second integer.
			
			*pBuf++ = (nHighVal * 16) + nLowVal;
		
		cbBytesOut++;		
	}
	return cbBytesOut;
}


//***********************************************************************
// Function: Hex2BytesA
//
// Purpose: Converts a hexadecimal formated ASCII string to binary data.            
//
// Parameters:  
//		szRecord	A string buffer containing a hexdecimal formatted UNICODE 
//					string.  For example:  "10af721c"
//		pByte		A pointer to a buffer where the converted string will be 
//					written out as binary data.
//
// Returns: A LONG representing the number of bytes written to the buffer.
//
// Comments:  Uses Char2HexW.  Because we are converting hexdecimal strings
//			  to Bytes we need to remember that it takes two hex characters
//		      to make up a byte.where "FF" == 255 == 2^8 == 1 byte.  For that 
//			  reason, we have to convert 2 characters and add them together 
//			  to create a byte.
//
// History:  Date       Author          Reason
//           3/6/96    Geoff Darst      Created
//*************************************************************************

LONG WINAPI Hex2BytesA(LPSTR szRecord, 
                       PBYTE pBuf)
{
	PCHAR pch;
	BYTE nHighVal, nLowVal;
	LONG cbBytesOut = 0;

	for (pch = szRecord; *pch != '\0'; pch++){
		
		nHighVal = Char2HexA(*pch);
		nLowVal = Char2HexA(*(++pch));
		
		if (0xFF == nHighVal || 0xFF == nLowVal)
			return 0;
		else
			// Construct a byte:  Offset the first integer
			// by 16 and add it to the second integer.
			
			*pBuf++ = (nHighVal * 16) + nLowVal;
		
		cbBytesOut++;		
	}
	return cbBytesOut;
}


//***********************************************************************
// Function: Char2HexW
//
// Purpose: Converts a single character that represents a hexdecimal number
//			(i.e.; 'f') to a binary representation of the numerical value
//			(i.e.; 'f' == 15 == 1111).            
//
// Parameters:  
//		wch	 A UNICODE character containing the hexadecimal number to be
//			 converted.
//
// Returns: Sucess:  A BYTE containing the binary representation of the hexdecimal 
//			number.
//
//			Failure:  A BYTE containing 0xFF.  0xFF is an acceptable return since
//			we are only talking about converting a single hex character.  This
//			means that the largest legitimate value returned can never be more
//			than 0xF or 15 decimal.
//
// Comments:
//
// History:  Date       Author          Reason
//           3/6/96    Geoff Darst      Created
//*************************************************************************

BYTE WINAPI Char2HexW(WCHAR wch)
{
	if (IsCharAlpha((TCHAR)wch)){
		
		// wch == 'A' - 'F'
		
		if (iswxdigit(wch)){
			CharUpper((TCHAR*)&wch);
			return (wch - 55);
		}
		else
			return 0xFF;
	}
	// wch == '0' - '9'
	
	return (BYTE)_wtoi(&wch);
}


//***********************************************************************
// Function: Char2HexA
//
// Purpose: Converts a single character that represents a hexdecimal number
//			(i.e.; 'f') to a binary representation of the numerical value
//			(i.e.; 'f' == 15 == 1111).            
//
// Parameters:  
//		wch	 An ASCII character containing the hexadecimal number to be
//			 converted.
//
// Returns: Sucess:  A BYTE containing the binary representation of the hexdecimal 
//			number.
//
//			Failure:  A BYTE containing 0xFF.  0xFF is an acceptable return since
//			we are only talking about converting a single hex character.  This
//			means that the largest legitimate value returned can never be more
//			than 0xF or 15 decimal.
//
// Comments:
//
// History:  Date       Author          Reason
//           3/6/96    Geoff Darst      Created
//*************************************************************************

BYTE WINAPI Char2HexA(CHAR ch)
{
	if (IsCharAlpha(ch)){
		
		// wch == 'A' - 'F'
		
		if (isxdigit(ch)){
			CharUpper(&ch);
			return (ch - 55);
		}
		else
			return 0xFF;
	}
	// wch == '0' - '9'
	
	return (BYTE)atoi(&ch);
}


