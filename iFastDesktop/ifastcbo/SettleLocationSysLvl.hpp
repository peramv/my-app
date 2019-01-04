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
// ^FILE   : SettleLocationSysLvl.hpp
// ^AUTHOR : 
// ^DATE   : 
//
// ^CLASS    : SettleLocationSysLvl
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

class MktIndexFundsList;

class IFASTCBO_LINKAGE SettleLocationSysLvl : public MFCanBFCbo
{
public:

   SettleLocationSysLvl( BFAbstractCBO &parent );
   virtual ~SettleLocationSysLvl();

   SEVERITY init(const BFData&   data );
	void		initNew(const BFDataGroupId& idDataGroup );

protected:

   virtual SEVERITY doValidateField( const BFFieldId& idField, const DString& strValue, const BFDataGroupId& idDataGroup );
   virtual SEVERITY doValidateAll( const BFDataGroupId& idDataGroup, long lValidateGroup );
   virtual SEVERITY doApplyRelatedChanges( const BFFieldId& idField, const BFDataGroupId& idDataGroup );

private:

	void setFieldStates(const BFDataGroupId& idDataGroup);
	SEVERITY validateSettleLocation(const DString& strValue,const const BFDataGroupId& idDataGroup );
};

//***********************************************
//R E V I S I O N   C O N T R O L   E N T R I E S
//***********************************************
//
// $Log:   Y:/VCS/BF iFAST/ifastcbo/SettleLocationSysLvl.hpp-arc  $
//
//   Rev 1.2   Nov 14 2004 14:53:54   purdyech
//PET910 - .NET Conversion
//
//   Rev 1.1   Nov 24 2003 18:12:58   HERNANDO
//Next revision.
//
//   Rev 1.0   Nov 20 2003 11:08:46   HERNANDO
//Initial revision.
//
//