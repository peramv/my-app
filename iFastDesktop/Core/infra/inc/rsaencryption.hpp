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
 * ^FILE   : RSAEncryption.hpp
 * ^AUTHOR : Intan Ismail
 * ^DATE   : 07/25/2002
 *
 ***************************************************************************	
*/

#ifndef RSAENCRYPTION_HPP
#define RSAENCRYPTION_HPP

#include "rsaexception.hpp"
 
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
class DIRSAENC_LINKAGE RSAEncryption
{
	public:

		/**
		 * Constructor
		*/
		RSAEncryption();

		/**
		 * Destructor
		*/
		virtual ~RSAEncryption();
      
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
		 * @exception
		 *				Exception
		 *				if cannot load the file to decrypt OR 
		 *				if cannot place the decrypted file OR
		 *				if cannot decrypt the file  
		*/
		virtual void decryptFile( long key, 
										  char* srcPath,
										  char* destPath );

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
		 * @exception
		 *				Exception
		 *				if cannot load the file to encrypt OR 
		 *				if cannot place the encrypted file OR
		 *				if cannot encrypt the file  
		*/
		virtual void encryptFile( long key, 
										  char* srcPath,
										  char* destPath );

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
		 * @exception
		 *				Exception
		 *				if cannot place the public key OR
		 *				if cannot place the private key  
		*/
		virtual void generateKey( char* pubFilename, 
										  char* privFilename, 
										  int length );

		/**
		 * Load a private key from a file. 
		 * 
		 * @param privkey  
		 *				A private key 
		 * @param filename
		 *				The filename containing the private key data
		 *				(i.e: c:\\key\\priv.key)
		 * @exception 
		 *				Exception if the private key cannot be loaded 
		*/
		void getPrivateKey( long* privkey, char* filename );

		/**
		 * Load a public key from a file. 
		 * 
		 * @param pubkey  
		 *				A public key 
		 * @param filename
		 *				The filename containing the public key data
		 *				(i.e: c:\\key\\pub.key)
		 * @exception 
		 *				Exception if the public key cannot be loaded 
		*/
		void getPublicKey( long* pubkey, char* filename );


	private:

		int m_lret;
		long m_key;
};


#endif // RSAENCRYPTION_HPP



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
// $Log:   Y:/VCS/iFastAWD/inc/rsaencryption.hpp-arc  $
//
//   Rev 1.0   28 Jan 2008 13:32:36   kovacsro
//Initial revision.
//
//   Rev 1.2   Sep 20 2002 10:52:16   dt39990
// 
