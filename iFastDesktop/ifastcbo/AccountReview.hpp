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
// ^FILE   : AccountReview.hpp
// ^AUTHOR : 
// ^DATE   : 
//
// ^CLASS    : AccountReview
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

class IFASTCBO_LINKAGE AccountReview : public MFCanBFCbo, private boost::noncopyable
{
public:

   AccountReview( BFAbstractCBO &parent );
   virtual ~AccountReview();
   SEVERITY init( const BFData& data );
   SEVERITY init( const BFDataGroupId& idDataGroup );
   virtual SEVERITY doApplyRelatedChanges( const BFFieldId& idField, const BFDataGroupId& idDataGroup );
   virtual SEVERITY doValidateField( const BFFieldId& idField, const DString& strValue, const BFDataGroupId& idDataGroup );
   virtual SEVERITY checkActualReviewDate(const DString& dstrActualReviewDate, const BFDataGroupId& idDataGroup );

};


//*****************************************************************************
// Revision Control Entries
//*****************************************************************************
//
// $Log:   Y:/VCS/BF iFAST/ifastcbo/AccountReview.hpp-arc  $
//
//   Rev 1.6   Mar 17 2005 11:59:32   aguilaam
//IN_234826 : year of 9999 is invalid actual review date
//
//   Rev 1.5   Mar 21 2003 17:55:06   PURDYECH
//BFDataGroupId/BFContainerId changeover
//
//   Rev 1.4   Oct 09 2002 23:53:54   PURDYECH
//PVCS Database Conversion
//
//   Rev 1.3   Aug 29 2002 12:51:30   SMITHDAV
//ClientLocale and typed field changes.
//
//   Rev 1.2   31 May 2002 13:45:12   HERNANDO
//Revised for Rel47.
//
//   Rev 1.1   22 May 2002 18:22:06   PURDYECH
//BFData Implementation
//
