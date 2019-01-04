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
//    Copyright 1999 by DST Canada, Inc.
//
//
//******************************************************************************
//
// ^FILE   : ProtectedFundList.hpp
// ^AUTHOR : Serban Popescu
// ^DATE   : 01/08/2003
//
// ^CLASS    : ProtectedFundList
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

class IFASTCBO_LINKAGE ProtectedFundList : public MFCanBFCbo, private boost::noncopyable
{
public:
   // X-structors
   ProtectedFundList( BFAbstractCBO &parent );
   virtual ~ProtectedFundList();

   // Initialize function
   SEVERITY init(const BFDataGroupId& idDataGroup = BF::HOST, 
      const DString& dstrTrack = I_("N"), const DString& dstrPageName = NULL_STRING);
   SEVERITY doCreateObject(const BFData& data, BFCBO *&pObjOut);
   SEVERITY doCreateNewObject(BFCBO *&pBase, DString &strKey, const BFDataGroupId& idDataGroup);
   SEVERITY reInit();
   virtual void getStrKey( DString &strKey, const BFData *data );
   bool isProtectedFund (const DString& dstrFundCode, const DString& dstrClassCode, 
      const BFDataGroupId& idDataGroup);

private:
   void buildKey(DString& dstrKey, DString &dstrFundCode, DString& dstrClassCode);
};

//******************************************************************************
//              Revision Control Entries
//******************************************************************************
//
/* $Log:   Y:/VCS/BF iFAST/ifastcbo/ProtectedFundList.hpp-arc  $
//
//   Rev 1.10   Nov 14 2004 14:51:16   purdyech
//PET910 - .NET Conversion
//
//   Rev 1.9   May 27 2003 18:29:50   popescu
//due to several memory leaks found in some list getters at the DSTCWorkSession level caused by copy/paste, I've created a common template function to retrieve the dependent objects
//
//   Rev 1.8   Mar 21 2003 18:20:30   PURDYECH
//BFDataGroupId/BFContainerId changeover
//
//   Rev 1.7   Feb 06 2003 10:34:58   WINNIE
//change isProtectedFund input parameters to const since call methods have fund and class as constant.
//
//   Rev 1.6   Feb 05 2003 15:56:34   HSUCHIN
//added get string key and new method to check if fund/class passed in is a protected fund
//
//   Rev 1.5   Feb 03 2003 11:54:14   popescu
//Changes to support the KeyString field of view 249
//
//   Rev 1.4   Jan 26 2003 15:51:04   popescu
//Added the Revsion Control entry section
 */
