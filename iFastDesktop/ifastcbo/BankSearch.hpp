#error "This file is obsolete"
//Please use FinancialInstitutioList.hpp instead

/*
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
// ^FILE   : BankSearch.hpp
// ^AUTHOR : Celia Zhang
// ^DATE   : 03/08/2001
//
// ^CLASS    : BankSearch
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


class IFASTCBO_LINKAGE BankSearch : public MFCanBFCbo, private boost::noncopyable
{
public:
   // X-structors
   BankSearch( BFAbstractCBO &parent );
   virtual ~BankSearch( void );

   // Initialize function

   SEVERITY init( const DString&  dstrBankType,
                  const DString&  dstrBankIdNum, 
                  const DString&  dstrInstName, 
                  const DString&  dstrTrack = I_("N"),
                  const DString&  dstrPageName = NULL_STRING  );
// search for all list
   SEVERITY init( const DString&  dstrTrack = I_("N"),
                  const DString&  dstrPageName = NULL_STRING  );  

   SEVERITY init2( const DString&  dstrBankType, //BankType
                   const DString&  dstrBankIdNum, //BankId
                   const DString&  dstrTransitNo, // TransitNo					
                   const DString&  dstrTrack = I_("N"),
                   const DString&  dstrPageName = NULL_STRING);               

   bool IsValueExistInBankSearch(const BFFieldId& fieldID, const DString& Value);
   bool validateInstCodeTransitNo(const DString& InstCode, const DString& TransitNo  );

private:
};

///#endif


/******************************************************************************
//              Revision Control Entries
//******************************************************************************
//
/* $Log:   Y:/VCS/BF iFAST/ifastcbo/BankSearch.hpp-arc  $
//
//   Rev 1.11   Nov 14 2004 14:29:06   purdyech
//PET910 - .NET Conversion
//
//   Rev 1.10   Oct 04 2003 15:57:42   popescu
//CIBC PET 809, FN 13;
//also cleaned-up BankSearch and BankList objects,
//replaced with FinancialInstitutionList
//
//   Rev 1.9   Mar 21 2003 18:00:38   PURDYECH
//BFDataGroupId/BFContainerId changeover
//
//   Rev 1.8   Oct 09 2002 23:54:06   PURDYECH
//PVCS Database Conversion
//
//   Rev 1.7   Aug 29 2002 12:51:56   SMITHDAV
//ClientLocale and typed field changes.
//
//   Rev 1.6   22 May 2002 18:21:42   PURDYECH
//BFData Implementation
//
//   Rev 1.5   19 Mar 2002 13:15:18   PURDYECH
//Use #pragma once as include guard
//Remove compile time "including..." message
//
//   Rev 1.4   09 May 2001 14:42:22   HSUCHIN
//Sync up with SSB
//
//   Rev 1.3   03 May 2001 14:03:52   SMITHDAV
//Session management restructuring.
//
//   Rev 1.2   Apr 03 2001 15:47:22   YINGBAOL
//add  validateInstCodeTransitNo
//
//   Rev 1.1   Mar 23 2001 03:38:02   YINGBAOL
//make it work
//
//   Rev 1.0   Mar 08 2001 15:17:58   ZHANGCEL
//Initial revision.
 * 
 */
