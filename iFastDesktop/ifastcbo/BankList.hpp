#error "This file is obsolete"
//Use FinancialInstitutionList.hpp instead
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
// ^FILE   : BankList.hpp
// ^AUTHOR : Zijian Ying
// ^DATE   : 10/21/99
//
// ^CLASS    : BankList
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

class IFASTCBO_LINKAGE BankList : public MFCanBFCbo, private boost::noncopyable
{
public:
   // X-structors
   BankList( BFAbstractCBO &parent );
   virtual ~BankList( void );

   // Initialize function
   SEVERITY init( const DString& dstrTrack = I_("N"), const DString& dstrPageName = NULL_STRING );
   bool IsValueExistInBankList(const BFFieldId& fieldID, const DString& Value);

};



/******************************************************************************
//              Revision Control Entries
//******************************************************************************
//
/* $Log:   Y:/VCS/BF iFAST/ifastcbo/BankList.hpp-arc  $
 * 
 *    Rev 1.11   Nov 14 2004 14:29:04   purdyech
 * PET910 - .NET Conversion
 * 
 *    Rev 1.10   Oct 04 2003 15:57:38   popescu
 * CIBC PET 809, FN 13;
 * also cleaned-up BankSearch and BankList objects,
 * replaced with FinancialInstitutionList
 * 
 *    Rev 1.9   Mar 21 2003 18:00:34   PURDYECH
 * BFDataGroupId/BFContainerId changeover
 * 
 *    Rev 1.8   Oct 09 2002 23:54:04   PURDYECH
 * PVCS Database Conversion
 * 
 *    Rev 1.7   Aug 29 2002 12:51:54   SMITHDAV
 * ClientLocale and typed field changes.
 * 
 *    Rev 1.6   22 May 2002 18:21:40   PURDYECH
 * BFData Implementation
 * 
 *    Rev 1.5   19 Mar 2002 13:15:16   PURDYECH
 * Use #pragma once as include guard
 * Remove compile time "including..." message
 * 
 *    Rev 1.4   03 May 2001 14:03:50   SMITHDAV
 * Session management restructuring.
 * 
 *    Rev 1.3   Jan 18 2001 16:11:40   YINGBAOL
 * add etrack
 * 
 *    Rev 1.2   Aug 04 2000 14:03:18   YINGBAOL
 * put enquiry bank at bankground
 * 
 *    Rev 1.1   Aug 01 2000 09:42:10   YINGBAOL
 * add business rules
 *
 
*/