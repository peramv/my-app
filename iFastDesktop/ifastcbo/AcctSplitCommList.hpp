#pragma once

//******************************************************************************
//
// COPYRIGHT:
//
//    The computer systems, procedures, data bases and
//    programs created and maintained by DST Canada, Inc.,
//    are proprietary in nature and as such are confidential.
//    Any unauthorized use or disclosure of such information
//    may result in civil liabilities.
//
//    Copyright 2001 by DST Canada Inc.
//
//
//******************************************************************************
//
// ^FILE   : AcctSplitCommList.hpp
// ^AUTHOR : 
// ^DATE   : Aug 22, 2001
//
// ^CLASS    : AcctSplitCommList
// ^SUBCLASS :
//
// ^CLASS DESCRIPTION :
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

class AcctSplitComm;

class IFASTCBO_LINKAGE AcctSplitCommList : public MFCanBFCbo, private boost::noncopyable
{
public:

   /**
    * Constructor
    * @param   BFBase *parent - Pointer to the calling class.
    */
   AcctSplitCommList( BFAbstractCBO &parent );

   /**
    * Destructor
    */
   ~AcctSplitCommList();   

//********************************************************************************
// Initializes the List for view call.  The only required field is Account Number
// @param   const DString& dstrAccountNum - Account Number
// @param   const DString& dstrTrack - Default "N"
// @param   const DString& dstrPageName - Default NULL_STRING 
// @return  SEVERITY if view call failed, NO_CONDITION if view passed.
//********************************************************************************
   SEVERITY init( const DString& dstrAccountNum, 
                  const DString& dstrTrack = I_("N"),
                  const DString& dstrPageName = NULL_STRING );

   void initNew( const DString& dstrAccountNum );

   void getAccountNum ( DString& dstrAccountNum );

   AcctSplitComm* getLastActiveAcctSplitComm () { return(_pLastActiveAcctSplitComm);};

protected:

//********************************************************************************
// virtual function. Should be overwritten in order to do special processing on new list element creation
// @param pBase         - here will be filled in the new object
// @param strKey        - here will be filled in string key
// @param idDataGroup  - the identifier of the data group with which we want to add a new object
//********************************************************************************
   virtual SEVERITY doCreateNewObject(BFCBO*& pBase, DString & strKey, const BFDataGroupId& idDataGroup );

   virtual SEVERITY doDeleteObject ( const DString&  strKey, const BFDataGroupId& idDataGroup, bool bIsObjectDestroyed );

   virtual SEVERITY doValidateAll( const BFDataGroupId& idDataGroup, long lValidateGroup );   

private:

   void validateDateRange (const BFDataGroupId& idDataGroup);
   DString _dstrAccountNum;
   AcctSplitComm *_pLastActiveAcctSplitComm;
};


//******************************************************************************
//              Revision Control Entries
//******************************************************************************
//
/* $Log:   Y:/VCS/BF iFAST/ifastcbo/AcctSplitCommList.hpp-arc  $
//
//   Rev 1.10   Mar 21 2003 17:56:08   PURDYECH
//BFDataGroupId/BFContainerId changeover
//
//   Rev 1.9   Oct 09 2002 23:53:58   PURDYECH
//PVCS Database Conversion
//
//   Rev 1.8   Aug 29 2002 12:51:38   SMITHDAV
//ClientLocale and typed field changes.
//
//   Rev 1.7   Aug 08 2002 15:06:50   HSUCHIN
//added a pointer to keep track of last active acctsplitcommlist.
//
//   Rev 1.6   22 May 2002 18:22:00   PURDYECH
//BFData Implementation
//
//   Rev 1.5   19 Mar 2002 13:14:54   PURDYECH
//Use #pragma once as include guard
//Remove compile time "including..." message
//
//   Rev 1.4   16 Nov 2001 16:32:04   HSUCHIN
//added date range validation
//
//   Rev 1.3   25 Sep 2001 15:09:30   HSUCHIN
//added dovalidate all
//
//   Rev 1.2   03 Sep 2001 13:26:32   HSUCHIN
//added initNew for NASU usage and function to get/set the Account number for Acct Split Comm
//
//   Rev 1.1   29 Aug 2001 16:11:32   HSUCHIN
//added enhancements and validation
//
//   Rev 1.0   23 Aug 2001 14:51:38   HSUCHIN
//Initial revision.
*/
