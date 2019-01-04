/**
 * FILE     :  sha-1.h
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
typedef unsigned char Byte;

#ifdef __cplusplus
extern "C" 
#endif
Byte* DigestMessage( const Byte*, unsigned int);

