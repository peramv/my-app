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
//******************************************************************************
//
// ^FILE   : AccountReviewList.hpp
// ^AUTHOR : 
// ^DATE   : 
//
// ^CLASS  : AccountReviewList
// ^PARENT : ListBase
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

class IFASTCBO_LINKAGE AccountReviewList : public MFCanBFCbo, private boost::noncopyable
{
public:

   AccountReviewList( BFAbstractCBO &parent );
   virtual ~AccountReviewList();

   SEVERITY init( const DString& accountNum, 
                  const DString& dstrTrack= I_("N"),
                  const DString& dstrPageName = NULL_STRING );

   SEVERITY init();

   SEVERITY getMore();

   // List specific functions called by child CBOs
   SEVERITY validateActualReviewDate(BFAbstractCBO *pBFAbstractCBO, const DString& dstrValue, const BFDataGroupId& idDataGroup);
   SEVERITY validateScheduledReviewDate(const DString& dstrValue, const BFDataGroupId& idDataGroup);
   SEVERITY applyScheduleReviewDateChange(BFAbstractCBO *pBFAbstractCBO, const BFFieldId& idField, const BFDataGroupId& idDataGroup);
   SEVERITY setReadOnlyFieldsBasedOnRules(const BFDataGroupId& idDataGroup);

protected:

   virtual SEVERITY doCreateObject( const BFData& data, BFCBO *&pObjOut );
   SEVERITY doCreateNewObject(BFCBO *& pBase, DString &strKey , const BFDataGroupId& idDataGroup );

private:

   void addMonthsToDate(DString& dstrDateIn, DString& dstrDateOut, int iMonthIncrement);
   void getAccountReviewSettings();

   BFData m_requestData;
   bool m_bOverrideScheduledDateFlag;
   int m_iReviewMonths;
};


//*****************************************************************************
// Revision Control Entries
//*****************************************************************************
//
// $Log:   Y:/VCS/BF iFAST/ifastcbo/AccountReviewList.hpp-arc  $
//
//   Rev 1.5   Mar 21 2003 17:55:12   PURDYECH
//BFDataGroupId/BFContainerId changeover
//
//   Rev 1.4   Oct 09 2002 23:53:54   PURDYECH
//PVCS Database Conversion
//
//   Rev 1.3   Aug 29 2002 12:51:30   SMITHDAV
//ClientLocale and typed field changes.
//
//   Rev 1.2   31 May 2002 13:44:42   HERNANDO
//Revised for Rel47.
//
//   Rev 1.1   22 May 2002 18:22:00   PURDYECH
//BFData Implementation
//
