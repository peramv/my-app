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
// ^FILE   : TransactionSummaryList.hpp
// ^AUTHOR : Adrian Vasile
// ^DATE   : 11/03/2001
//
// ^CLASS    : TransactionSummaryList
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

class IFASTCBO_LINKAGE TransactionSummaryList : public MFCanBFCbo, private boost::noncopyable
{
public:
   // X-structors
   TransactionSummaryList( BFAbstractCBO &parent );
   virtual ~TransactionSummaryList( void );

   // Initialize function
   SEVERITY init( DString& AccountNum,
                  const DString& Baycom = NULL_STRING,
                  const DString& FromDate = NULL_STRING, 
                  const DString& ToDate = NULL_STRING,
                  const DString& NextOrPrevious = I_( "Y" ), 
                  const DString& SortOrder = I_( "D" ),
                  const DString& FundCode = NULL_STRING, 
                  const DString& NextKey = NULL_STRING,
                  const DString& dstrTrack= I_("N"),
                  const DString& dstrPageName = NULL_STRING );

   SEVERITY init();

private:
   BFData _queryData;
};

//*****************************************************************************
// Revision Control Entries
//*****************************************************************************
//
// $Log:   Y:/VCS/BF iFAST/ifastcbo/TransactionSummaryList.hpp-arc  $
//
//   Rev 1.9   Nov 14 2004 14:58:26   purdyech
//PET910 - .NET Conversion
//
//   Rev 1.8   Oct 09 2002 23:55:12   PURDYECH
//PVCS Database Conversion
//
//   Rev 1.7   Aug 29 2002 12:53:58   SMITHDAV
//ClientLocale and typed field changes.
//
//   Rev 1.6   22 May 2002 18:19:12   PURDYECH
//BFData Implementation
//
