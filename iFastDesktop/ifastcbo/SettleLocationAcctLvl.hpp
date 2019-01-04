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
//    Copyright 2003, By International Financial Data Service
//
//
//******************************************************************************
//
// ^FILE   : SettleLocationAcctLvl.hpp
// ^AUTHOR : 
// ^DATE   : 
//
// ^CLASS    : SettleLocationAcctLvl
// ^SUBCLASS :
//
// ^CLASS DESCRIPTION :
//
//******************************************************************************

#include <ifastcbo\mfcancbo.hpp>

#undef IFASTCBO_LINKAGE
#ifdef IFASTCBO_DLL
   #define IFASTCBO_LINKAGE CLASS_EXPORT
#else
   #define IFASTCBO_LINKAGE CLASS_IMPORT
#endif

class IFASTCBO_LINKAGE SettleLocationAcctLvl : public MFCanBFCbo
{
public:

   SettleLocationAcctLvl( BFAbstractCBO &parent );
   virtual ~SettleLocationAcctLvl();

   SEVERITY init(const BFData& data, const DString&  );
	void     initNew(const BFDataGroupId& idDataGroup, const DString&, const DString& dstrIndexCode );

protected:

   virtual SEVERITY doValidateField( const BFFieldId& idField, const DString& strValue, const BFDataGroupId& idDataGroup );
   virtual SEVERITY doValidateAll( const BFDataGroupId& idDataGroup, long lValidateGroup );
   virtual SEVERITY doApplyRelatedChanges( const BFFieldId& idField, const BFDataGroupId& idDataGroup );

private:

   SEVERITY validateSettlementLocation( const DString& strValue, const BFDataGroupId& idDataGroup );
   SEVERITY validateDefault( const DString& strValue, const BFDataGroupId& idDataGroup );
	void setFieldStates(const BFDataGroupId& idDataGroup);
};

//***********************************************
//R E V I S I O N   C O N T R O L   E N T R I E S
//***********************************************
//
// $Log:   Y:/VCS/BF iFAST/ifastcbo/SettleLocationAcctLvl.hpp-arc  $
//
//   Rev 1.2   Nov 14 2004 14:53:50   purdyech
//PET910 - .NET Conversion
//
//   Rev 1.1   Nov 24 2003 18:11:26   HERNANDO
//Next revision.
//
//   Rev 1.0   Nov 20 2003 11:08:42   HERNANDO
//Initial revision.
//