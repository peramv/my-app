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
// ^FILE   : AsPensionPlan.hpp
// ^AUTHOR : Karen Jan
// ^DATE   : July 24, 2001
//
// ^CLASS    : AsPensionPlan
// ^SUBCLASS :
//
// ^CLASS DESCRIPTION :
//
//******************************************************************************

//TODO: add headers that need to be included in the interface class
#include <ifastcbo\mfcancbo.hpp>
#include <boost\utility.hpp>

#undef IFASTCBO_LINKAGE
#ifdef IFASTCBO_DLL
   #define IFASTCBO_LINKAGE CLASS_EXPORT
#else
   #define IFASTCBO_LINKAGE CLASS_IMPORT
#endif

class IFASTCBO_LINKAGE AsPensionPlan : public MFCanBFCbo, private boost::noncopyable
{
public:
   AsPensionPlan( BFAbstractCBO &parent );
   virtual ~AsPensionPlan();
   SEVERITY init( const BFDataGroupId& idDataGroup );
   SEVERITY init( const DString& accountNum, const BFDataGroupId& idDataGroup, const DString& dstrTrack=I_("N"),
                  const DString& dstrPageName = NULL_STRING );

protected:
   void doInitWithDefaultValues(const BFDataGroupId& idDataGroup);
   SEVERITY doApplyRelatedChanges( const BFFieldId& idField, const BFDataGroupId& idDataGroup );
   SEVERITY setEndDate( const BFDataGroupId& idDataGroup );
   void addYearToDate( DString& dstrInDate, DString& dstrOutDate, int numYear );
   SEVERITY setMaturityDate( const BFDataGroupId& idDataGroup );
   SEVERITY validateEndDate( const DString& EndDate, const BFDataGroupId& idDataGroup );
   SEVERITY getDofBirth( DString& DofBirth, const BFDataGroupId& idDataGroup );
   SEVERITY doValidateField( const BFFieldId& idField, const DString& strValue, const BFDataGroupId& idDataGroup );
   SEVERITY validateStatus( const DString& dstrASStatus, const BFDataGroupId& idDataGroup );
   void getNextQuarterEndDate( DString &dstrDateIn, DString &dstrDateOut );
   void getMonthEndDate( DString &dstrInOut, DString &dstrDateOut );
   SEVERITY validateMaturityDate( const DString& MaturityDate, const BFDataGroupId& idDataGroup );
   void getQuarterEndDate( DString &dstrDateIn, DString &dstrDateOut );

   DString dstrMaturDate_;
   DString currBusinessDate_;
};

//***************************************************************************************
/* $Log:   Y:/VCS/BF iFAST/ifastcbo/AsPensionPlan.hpp-arc  $
//
//   Rev 1.7   Mar 21 2003 17:59:24   PURDYECH
//BFDataGroupId/BFContainerId changeover
//
//   Rev 1.6   Oct 09 2002 23:54:00   PURDYECH
//PVCS Database Conversion
//
//   Rev 1.5   Aug 29 2002 12:51:46   SMITHDAV
//ClientLocale and typed field changes.
//
//   Rev 1.4   22 May 2002 18:21:44   PURDYECH
//BFData Implementation
//
//   Rev 1.3   19 Mar 2002 13:15:08   PURDYECH
//Use #pragma once as include guard
//Remove compile time "including..." message
//
//   Rev 1.2   Nov 29 2001 14:36:32   JANKAREN
//code clean up
//
//   Rev 1.1   Sep 27 2001 09:24:12   JANKAREN
//Added methods related to business logic
//
//   Rev 1.0   Aug 23 2001 12:58:28   JANKAREN
//Initial revision.
 * 
 * 
 */