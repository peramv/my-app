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
// ^FILE   : SysLvlSettlementInstrList.hpp
// ^AUTHOR : 
// ^DATE   : 
//
// ^CLASS    : SysLvlSettlementInstrList
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

class SysLvlSettlementInstr;

class IFASTCBO_LINKAGE SysLvlSettlementInstrList : public MFCanBFCbo
{
public:

   SysLvlSettlementInstrList( BFAbstractCBO &parent );
   virtual ~SysLvlSettlementInstrList();

   SEVERITY init(const BFDataGroupId& idDataGroup,
					  const DString& dstrTrack = I_("N"),
					  const DString& dstrPageName = NULL_STRING );
   SEVERITY reInit();
   SEVERITY getMore();

   bool isDuplicateSettlementLocation( DString &, const BFDataGroupId& idDataGroup );

	SEVERITY getSysLvlSettlementInstr( const DString &dstrSettlementLocationCode, 
				      				       SysLvlSettlementInstr *&pSysLvlSettlementInstr, 
												 const BFDataGroupId& idDataGroup );

protected:

   virtual SEVERITY doCreateObject( const BFData& data, BFCBO*& pObjOut );
   virtual SEVERITY doValidateAll( const BFDataGroupId& idDataGroup, long lValidateGroup );
	virtual SEVERITY doCreateNewObject(BFCBO *&pObjOut, DString &strKey, const BFDataGroupId& idDataGroup );
	virtual void  getStrKey( DString &strKey, const BFData *data  );

   BFData m_requestData;
};


//***********************************************
//R E V I S I O N   C O N T R O L   E N T R I E S
//***********************************************
//
// $Log:   Y:/VCS/BF iFAST/ifastcbo/SysLvlSettlementInstrList.hpp-arc  $
//
//   Rev 1.1   Nov 14 2004 14:56:32   purdyech
//PET910 - .NET Conversion
//
//   Rev 1.0   Oct 13 2004 13:02:30   VADEANUM
//Initial revision.
//
//   Rev 1.2   Nov 25 2003 17:19:16   VADEANUM
//PET859 FN1 - Settlement Location at Trade Level support - added getSysLvlSettlementInstr().
//
//   Rev 1.1   Nov 24 2003 18:13:36   HERNANDO
//Next revision.
//
//   Rev 1.0   Nov 20 2003 11:08:48   HERNANDO
//Initial revision.
//
//