#pragma once



//******************************************************************************
//
// COPYRIGHT:
//
//    The computer systems, procedures, data bases and
//    programs created and maintained by Internation Financial Data Services
//    are proprietary in nature and as such are confidential.
//    Any unauthorized use or disclosure of such information
//    may result in civil liabilities.
//
//    Copyright 2003 by Internation Financial Data Services
//
//
//******************************************************************************
//
// ^FILE      : AmsLmtOverride.hpp
// ^AUTHOR    : May Lin
// ^DATE      : May 22, 2003
//
// ^CLASS     : AmsLmtOverride
// ^SUBCLASS  :
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


class IFASTCBO_LINKAGE AmsLmtOverride : public MFCanBFCbo, private boost::noncopyable
{
public:
   AmsLmtOverride( BFAbstractCBO &parent );
   virtual ~AmsLmtOverride();

   SEVERITY init( const BFData& data );
   void initNew(const BFDataGroupId& idDataGroup );
   void ModelAMS(AmsLmtOverride *Model, const BFDataGroupId& idDataGroup);

   int isCodeAllowed ( const DString& dstrCode, const DString& dstrCodeList );   
   SEVERITY isCodeListValid( const DString& dstrCodeList );
   bool isTaxJurisInList( const DString& dstrTaxJuris, const BFDataGroupId& idDataGroup );
   bool isProvResInList( const DString& dstrProvResid, const BFDataGroupId& idDataGroup );
   bool isTaxTypeInList( const DString& dstrTaxType, const BFDataGroupId& idDataGroup );
   bool isAcctTypeInList( const DString& dstrAcctType, const BFDataGroupId& idDataGroup );
   bool isAcctDesignationInList( const DString& dstrAcctDesignation, const BFDataGroupId& idDataGroup );
   bool isError( const BFDataGroupId& idDataGroup );
   bool isWarning( const BFDataGroupId& idDataGroup );
   void getFundOverride ( bool& bFundOverride, const BFDataGroupId& idDataGroup );
   void getDecimalField ( DString& dstrDecimal, const BFDataGroupId& idDataGroup );
   void getLogicalField ( DString& dstrLogical, const BFDataGroupId& idDataGroup );

protected:
   virtual void doInitWithDefaultValues( const BFDataGroupId& idDataGroup );
   SEVERITY doApplyRelatedChanges( const BFFieldId& idField, const BFDataGroupId& idDataGroup );
   SEVERITY doValidateField( const BFFieldId& idField, const DString& strValue, const BFDataGroupId& idDataGroup );


private:
   SEVERITY validateMaxRedPercent (const DString& strValue,const BFDataGroupId& idDataGroup );
   void doRuleTypeRelatedChanges(const BFDataGroupId& idDataGroup);

};


//******************************************************************************
//              Revision Control Entries
//******************************************************************************
//
/* $Log:   Y:/VCS/BF iFAST/ifastcbo/AmsLmtOverride.hpp-arc  $
//
//   Rev 1.2   Aug 14 2003 13:03:14   HSUCHIN
//Change the fund override from pass by copy to pass by reference.
//
//   Rev 1.1   Jul 25 2003 17:05:30   HSUCHIN
//added support for limit override checks such as stop purchase, stop PAC etc. etc.
//
//   Rev 1.0   Jul 23 2003 09:23:40   linmay
//Initial Revision
//
*/