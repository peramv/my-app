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
//    Copyright 2002 by DST Canada, Inc.
//
//
//******************************************************************************
//
// ^FILE   : TradeAcctAlloc.hpp
// ^AUTHOR : Robert Kovacs
// ^DATE   : 08/04/02
//
// ^CLASS    : TradeAcctAlloc
// ^SUBCLASS :
//
// ^CLASS DESCRIPTION : trade account allocation
//
//******************************************************************************

#ifndef ACCTTALLOC_HPP
   #include <ifastcbo\AcctAlloc.hpp>
#endif 

class FundAllocList;

#undef IFASTCBO_LINKAGE
#ifdef IFASTCBO_DLL
   #define IFASTCBO_LINKAGE CLASS_EXPORT
#else
   #define IFASTCBO_LINKAGE CLASS_IMPORT
#endif

class IFASTCBO_LINKAGE TradeAcctAlloc : public AcctAlloc
{
public:
   // X-structors
   TradeAcctAlloc( BFAbstractCBO &parent );
   virtual ~TradeAcctAlloc( void );

   SEVERITY initNew( const BFDataGroupId& idDataGroup,
                     const DString& dstrTrack = I_("N"),
                     const DString& dstrPageName = NULL_STRING );
   SEVERITY initExisting(const BFData &data);
   SEVERITY copyDataFromParent(const BFDataGroupId& idDataGroup);
   void changeFieldsForRebook( );
protected:

   void doInitWithDefaultValues( const BFDataGroupId& idDataGroup );
   SEVERITY doApplyRelatedChanges( const BFFieldId& idField, const BFDataGroupId& idDataGroup );
   SEVERITY doValidateField( const BFFieldId& idField, const DString& strValue, const BFDataGroupId& idDataGroup );

private :

};

//******************************************************************************
//              Revision Control Entries
//******************************************************************************
//
/* $Log:   Y:/VCS/BF iFAST/ifastcbo/TradeAcctAlloc.hpp-arc  $
//
//   Rev 1.6   Jul 08 2005 09:33:08   Yingbaol
//PET1235,FN01:transaction cancellation rebook
//
//   Rev 1.5   Nov 14 2004 14:57:38   purdyech
//PET910 - .NET Conversion
//
//   Rev 1.4   Mar 21 2003 18:26:48   PURDYECH
//BFDataGroupId/BFContainerId changeover
//
//   Rev 1.3   Oct 09 2002 23:55:10   PURDYECH
//PVCS Database Conversion
//
//   Rev 1.2   Aug 29 2002 12:53:50   SMITHDAV
//ClientLocale and typed field changes.
//
//   Rev 1.1   22 May 2002 18:19:18   PURDYECH
//BFData Implementation
//
//   Rev 1.0   29 Apr 2002 16:56:22   KOVACSRO
//Initial revision.
 * 
 *
*/
