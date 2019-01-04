#pragma once
//******************************************************************************
//
// COPYRIGHT:
//
//    The computer systems, procedures, data bases and
//    programs created and maintained by DST Systems, Inc.,
//    are proprietary in nature and as such are confidential.
//    Any unauthorized use or disclosure of such information
//    may result in civil liabilities.
//
//    Copyright 1999 by DST Systems, Inc.
//
//
//******************************************************************************
//
// ^FILE   : AccShrNumCheck.hpp.
// ^AUTHOR : Serban Popescu
// ^DATE   : January 20, 2000
//
// ^CLASS    : AccShrNumCheck
// ^SUBCLASS :
//
// ^CLASS DESCRIPTION : The associated accounts for a shareholder number
//
//******************************************************************************

#include <ifastcbo\mfcancbo.hpp>
#include <boost\utility.hpp>

#undef IFASTCBO_LINKAGE
#ifdef IFASTCBO_DLL
   #define IFASTCBO_LINKAGE CLASS_EXPORT
#else
   #define IFASTCBO_LINKAGE CLASS_IMPORT
#endif

class IFASTCBO_LINKAGE AccShrNumCheck : public MFCanBFCbo, private boost::noncopyable
{
public:
   AccShrNumCheck( BFAbstractCBO &parent );
   virtual ~AccShrNumCheck( void );

   //used to initialize from the shareholder object, when shareholder is new,
   //the param here is passed for convenience
   SEVERITY initNew(const DString& shrNum, const BFDataGroupId& idDataGroup = BF::HOST);
   SEVERITY initCheck(const DString& shrNum, const DString& accountNum, const DString& dstrCallByProc = NULL_STRING,
      const DString& dstrTrack = I_("N"), const DString& dstrPageName = NULL_STRING);
   //called from the Shareholder object. to get a list of account numbers for the 
   //given shareholder number
   SEVERITY init(const DString& shrNum, 
      const DString& dstrCallByProc = NULL_STRING,
      const DString& dstrTrack = I_("N"), 
      const DString& dstrPageName = NULL_STRING);
   SEVERITY initAccNum(const DString& dstrAcctNum, 
      const DString& dstrTrack = I_("N"), const DString& dstrPageName = NULL_STRING );
   SEVERITY initShrNum(const DString& dstrShrtNum, 
      const DString& dstrTrack = I_("N"), const DString& dstrPageName = NULL_STRING );
};


//******************************************************************************
//              Revision Control Entries
//******************************************************************************
/* $Log:   Y:/VCS/BF iFAST/ifastcbo/AccShrNumCheck.hpp-arc  $
 * 
 *    Rev 1.12   Jan 27 2010 17:55:26   wutipong
 * IN1877040 -- More fix to remove hard-coding.
 * 
 *    Rev 1.11   May 22 2003 14:11:50   popescu
 * Replaced name 'BankInstr' with 'BankInstructions'; 
 * simplified child lists getters for the Shareholder object
 * 
 *    Rev 1.10   Mar 21 2003 17:55:36   PURDYECH
 * BFDataGroupId/BFContainerId changeover
 * 
 *    Rev 1.9   Oct 09 2002 23:53:56   PURDYECH
 * PVCS Database Conversion
 * 
 *    Rev 1.8   Aug 29 2002 12:51:34   SMITHDAV
 * ClientLocale and typed field changes.
 * 
 *    Rev 1.7   22 May 2002 18:21:58   PURDYECH
 * BFData Implementation
 * 
 *    Rev 1.6   19 Mar 2002 13:14:54   PURDYECH
 * Use #pragma once as include guard
 * Remove compile time "including..." message
 * 
 *    Rev 1.5   07 Feb 2002 17:30:30   KOVACSRO
 * Added a new init, initShrNum.
 * 
 *    Rev 1.4   13 Dec 2001 17:14:10   KOVACSRO
 * Added a new init
 * 
 *    Rev 1.3   09 May 2001 11:46:18   HSUCHIN
 * Sync up with SSB
 * 
 *    Rev 1.2   03 May 2001 14:03:40   SMITHDAV
 * Session management restructuring.
 * 
 *    Rev 1.1   Jan 18 2001 16:11:28   YINGBAOL
 * add etrack
 * 
 *    Rev 1.0   Feb 15 2000 10:58:56   SMITHDAV
 * Initial revision.
// 
//    Rev 1.1   Jan 21 2000 11:11:38   POPESCUS
// the user can change the account number and the shareholder number
// 
// 
*/