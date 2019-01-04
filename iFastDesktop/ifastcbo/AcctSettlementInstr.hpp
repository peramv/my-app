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
//    Copyright 2004, By International Financial Data Service
//
//
//******************************************************************************
//
// ^FILE   : AcctSettlementInstr.hpp
// ^AUTHOR : 
// ^DATE   : 
//
// ^CLASS    : AcctSettlementInstr
// ^SUBCLASS :
//
// ^CLASS DESCRIPTION :
//
//******************************************************************************

#include <ifastcbo\mfcancbo.hpp>
#include <ifastcbo\settlementinstr.hpp>

#undef IFASTCBO_LINKAGE
#ifdef IFASTCBO_DLL
   #define IFASTCBO_LINKAGE CLASS_EXPORT
#else
   #define IFASTCBO_LINKAGE CLASS_IMPORT
#endif

class IFASTCBO_LINKAGE AcctSettlementInstr : public SettlementInstr
{
public:

   AcctSettlementInstr( BFAbstractCBO &parent );
   virtual ~AcctSettlementInstr();
   
protected:

   virtual void doInitWithDefaultValues( const BFDataGroupId& idDataGroup );

   virtual SEVERITY doValidateField( const BFFieldId& idField, 
		                               const DString& strValue, 
												 const BFDataGroupId& idDataGroup );   

private:
      
};


//*****************************************************************************
// Revision Control Entries
//*****************************************************************************
//
// $Log:   Y:/VCS/BF iFAST/ifastcbo/AcctSettlementInstr.hpp-arc  $
//
//   Rev 1.1   Dec 03 2004 16:12:16   vadeanum
//PET1117_FN21:  settlement instructions.
//
//   Rev 1.0   Oct 13 2004 13:47:12   VADEANUM
//Initial revision.
//
