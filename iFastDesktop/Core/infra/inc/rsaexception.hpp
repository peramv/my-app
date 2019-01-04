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
 * ^FILE   : RSAException.hpp
 * ^AUTHOR : Intan Ismail
 * ^DATE   : 07/25/2002
 *
 ***************************************************************************	
*/

#ifndef RSAEXCEPTION_HPP
#define RSAEXCEPTION_HPP

#include <string>

#undef DIRSAENC_LINKAGE
#ifdef DIRSAENC_DLL 
	#define DIRSAENC_LINKAGE __declspec(dllexport)
#else
	#define DIRSAENC_LINKAGE __declspec(dllimport)
#endif

/**
 * RSAException class provides the functionality to throw an exception 
 * when failed to generate keypair, get public and private keys, and encrypt 
 * and decrypt file.
 * 
*/
class DIRSAENC_LINKAGE RSAException
{
	public:

		/**
		 * Constructor
		*/
		RSAException();

		/**
		 * Constructor
		 *
		 * @param error
		 *			Error message to display 
		 *		
		 * @param file
		 *			The filename that cause an error
		 *
		 * @param method
		 *			Method where the error occur
		 *
		 * @param errCode
		 *			Polar Crypto error code 
		 *
		*/
		RSAException( std::string error, std::string file, std::string method, int errCode );

		/**
		 * Destructor
		*/
		virtual ~RSAException();

		/**
		 * Get Polar Crypto Error Message
		 * 
		 * @param errCode		
		 *			Polar Crypto Error Code
		*/
		virtual std::string getErrorMessage( int errCode );

		/**
		 * Display error, file, method, and Polar Crypto error
		*/
		virtual std::string showReason();


	private:

		std::string m_error;
		std::string m_file;
		std::string m_method;
		std::string m_reason;
		std::string m_message;
		int m_errCode;
};


#endif // RSAEXCEPTION_HPP



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
// $Log:   Y:/VCS/iFastAWD/inc/rsaexception.hpp-arc  $   
//
//   Rev 1.0   28 Jan 2008 13:32:38   kovacsro
//Initial revision.
//
//   Rev 1.2   Sep 20 2002 10:52:18   dt39990
// 


