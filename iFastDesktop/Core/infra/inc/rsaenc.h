/*
 *    COPYRIGHT:
 *
 *    The computer systems, procedures, data bases and
 *    programs created and maintained by DST Systems, Inc.,
 *    are proprietary in nature and as such are confidential.
 *    Any unauthorized use or disclosure of such information
 *    may result in civil liabilities.
 *
 *    Copyright 2002 by DST Systems, Inc.
 *
 ***************************************************************************	
 *
 * ^FILE   : RSAEnc.h
 * ^AUTHOR : Intan Ismail
 * ^DATE   : 08/05/2002
 *
 * ^FILE DESCRIPTION : C Interface for RSAEncryption
 *
 ***************************************************************************	
*/

#ifndef RSAENC_H
#define RSAENC_H

#include "rsaencryption.hpp"

#include <string>

// Definitions
#define SUCCESSFUL           0L
#define UN_SUCCESSFUL        4L
#define MAX_AGENTS           999
#define MAX_IDPASS			  8+1L

#undef DIRSAENC_LINKAGE
#ifdef DIRSAENC_DLL 
	#define DIRSAENC_LINKAGE __declspec(dllexport)
#else
	#define DIRSAENC_LINKAGE __declspec(dllimport)
#endif

/**
 * Used to provide an interface for RSAEncryption. RSAEncryption class provides 
 * the functionality to generate keypair, get public and private keys, and 
 * encrypt and decrypt file.
 * <BR><BR>
 * 
 * <B>RSA keypair details</B>
 * RSAEncryption supports 512, 1024 and 2048-bit key RSA encryption. It stores 
 * the keys in format described in RSA PKCS#1 document (A.1 'Key representation') 
 * and other PKCS documents. For more information about Public-key cryptography 
 * standards, refer to http://www.rsasecurity.com/rsalabs/pkcs/index.html.
 * <BR><BR> 
 * 
 * <B>RSA encryption/decryption details</B>
 * RSAEncryption uses PKCS1 encryption schema to encrypt and decrypt file.
 * <BR><BR> 
 *
 * Please note that this interface is created by using PolarCrypto Software API. 
 * You must have a PolarCrypto license purchases before you can use this interface. 
 * For more information about PolarCrypto, please visit http://www.polarsoftware.com
 * <BR><BR>
 */
extern "C"
{
		/**
		 * Decrypt a file using private key and writes the decrypted data to file.
		 * Please note that the srcPath and destPath cannot be the same.
		 * 
		 * @param key 
		 *				A private key to decrypt the file       
		 * @param srcPath 
		 *				A string that represents the location of the file to be decrypted
		 *				(i.e: c:\\data\\encrypted.doc)
		 * @param destPath
		 *				A string that represents the location to place the decrypted file
		 *				(i.e: c:\\data\\decrypted.doc)
		 * @param plRC
		 *				Return code
		 * @param lHandle
		 *				Equipment line ID
		*/
		DIRSAENC_LINKAGE void DECRYPTFILE( long key, 
													  char* srcPath,
													  char* destPath,
													  long* plRC,
													  long lHandle );

		/**
		 * Encrypt a file using public key and writes the encrypted data to file.
		 * Please note that the srcPath and destPath cannot be the same.
		 * 
		 * @param key
		 *				A public key to encrypt the file       
		 * @param srcPath 
		 *				A string that represents the location of the file to be encrypted
		 *				(i.e: c:\\data\\encrypt.doc)
		 * @param destPath
		 *				A string that represents the location to place the encrypted file
		 *				(i.e: c:\\data\\encrypted.doc)
		 * @param plRC
		 *				Return code
		 * @param lHandle
		 *				Equipment line ID
		*/
		DIRSAENC_LINKAGE void ENCRYPTFILE( long key, 
													  char* srcPath,
													  char* destPath,
													  long* plRC,
													  long lHandle );

		/**
		 * Generate private and public keys and write the keys to file. 
		 * Please note that the pubFilename and privFilename cannot be the same.
		 * 
		 * @param pubFilename
		 *				A string that represents the location to place the public key
		 *				(i.e: c:\\key\\pub.key)
		 * @param privFilename 
		 *				A string that represents the location to place the private key
		 *				(i.e: c:\\key\\priv.key)
		 * @param length
		 *				A key length for RSAEncryption. 
		 *				Possible key lengths: 128, 192, 256, 512, 1024, 2048				  
		 * @param plRC
		 *				Return code
		 * @param lHandle
		 *				Equipment line ID
		*/
		DIRSAENC_LINKAGE void GENERATEKEY( char* pubFilename, 
													  char* privFilename, 
													  int length,
													  long* plRC,
													  long lHandle );
                                           
		/**
		 * Load a private key from a file. 
		 * 
		 * @param privkey  
		 *				A private key 
		 * @param filename
		 *				The filename containing the private key data
		 *				(i.e: c:\\key\\priv.key)
		 * @param plRC
		 *				Return code
		 * @param lHandle
		 *				Equipment line ID
		*/
		DIRSAENC_LINKAGE void GETPRIVATEKEY( long* privkey,
														 char* filename,
														 long* plRC,
														 long lHandle );
																					
		/**
		 * Load a public key from a file. 
		 * 
		 * @param pubkey 
		 *				A public key 
		 * @param filename
		 *				The filename containing the public key data
		 *				(i.e: c:\\key\\pub.key)
		 * @param plRC
		 *				Return code
		 * @param lHandle
		 *				Equipment line ID
		*/
		DIRSAENC_LINKAGE void GETPUBLICKEY( long* pubkey,
														char* filename,
														long* plRC,
														long lHandle );
					
		/**
		 * Get error text message
		 *
		 * @param pcText
		 *				Error text
		 * @param plRC
		 *				Return code
		 * @param lHandle
		 *				Equipment line ID
		*/
		DIRSAENC_LINKAGE void GETRSAENCERRORTEXT( char* pcText,
																long* plRC,
																long lHandle );
};

#endif // RSAENC_H



//************************************************************************
//              Revision Control Entries
//************************************************************************
//
// Name:
//    %PM%
//    %PID%
//
// Description:
//    %PD%
//
// Design Parts:
//    %PIRP%
//
// Last Changed:
//    %PO%  -  %PRT%
//
// Changes:
//    %PLA%
//
//
// $Log:   Y:/VCS/iFastAWD/inc/rsaenc.h-arc  $
//
//   Rev 1.0   28 Jan 2008 13:32:36   kovacsro
//Initial revision.
//
//   Rev 1.1   Sep 20 2002 10:52:12   dt39990
// 
