#pragma once

//******************************************************************************
//
// COPYRIGHT:
//
// The computer systems, procedures, data bases and
// programs created and maintained by International Financial Data Services, Inc.,
// are proprietary in nature and as such are confIdential.
// Any unauthorized use or disclosure of such information
// may result in civil liabilities.
//
// Copyright 2010 by International Financial Data Services, Inc.
//
//
//******************************************************************************
//
// ^FILE   : AcctGuaranteeGuardOpt.hpp
// ^AUTHOR : 
// ^DATE   : Aug, 2010
//
// ^CLASS    : AcctGuaranteeGuardOpt
// ^SUBCLASS :
//
// ^CLASS DESCRIPTION :
//
//******************************************************************************

#include <boost\utility.hpp>
#include <ifastcbo\mfcancbo.hpp>


#undef IFASTCBO_LINKAGE
#ifdef IFASTCBO_DLL
   #define IFASTCBO_LINKAGE CLASS_EXPORT
#else
   #define IFASTCBO_LINKAGE CLASS_IMPORT
#endif

class IFASTCBO_LINKAGE AcctGuaranteeGuardOpt : public MFCanBFCbo, private boost::noncopyable
{
public:

   AcctGuaranteeGuardOpt( BFAbstractCBO &parent );
   virtual ~AcctGuaranteeGuardOpt();

   SEVERITY init (const BFData& data );
   SEVERITY initNew (const BFDataGroupId& idDataGroup );
   virtual void doInitWithDefaultValues( const BFDataGroupId& idDataGroup );
   void setUpdateStatus( const BFDataGroupId& idDataGroup, bool bStatus );

protected:
   SEVERITY initGuaranteeGuardOptList(const BFDataGroupId& idDataGroup );
   void initializeSubstitutionList( const BFFieldId& idField, 
									const DString &dstrGroupCode, 
									const BFDataGroupId& idDataGroup);

   SEVERITY doValidateField( const BFFieldId& idField, const DString& strValue, const BFDataGroupId& idDataGroup );
   SEVERITY doApplyRelatedChanges( const BFFieldId& idField, const BFDataGroupId& idDataGroup );
   SEVERITY commonInit(const BFDataGroupId& idDataGroup);

private:

};

//******************************************************************************
//              Revision Control Entries
//******************************************************************************
// 
// $Log:   Y:/VCS/BF iFAST/ifastcbo/AcctGuaranteeGuardOpt.hpp-arc  $
//
//   Rev 1.0   Sep 17 2010 03:38:36   kitticha
//Initial revision.
//
//
