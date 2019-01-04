#pragma once
//******************************************************************************
//
// COPYRIGHT:
//
//    The computer systems, procedures, data bases and
//    programs created and maintained by International Financial Data Services,
//    are proprietary in nature and as such are confidential.
//    Any unauthorized use or disclosure of such information
//    may result in civil liabilities.
//
//    Copyright 1999-2016 by International Financial Data Services
//
//
//******************************************************************************
//
// ^FILE   : RegPlanTransfer.hpp
// ^AUTHOR : Mihai Buzila
// ^DATE   : November 4, 2016
//
// ^CLASS    : RegPlanTransfer
// ^SUBCLASS :
//
// ^CLASS DESCRIPTION :
//
//******************************************************************************

#include <ifastcbo\mfcancbo.hpp>
#include <boost\utility.hpp>



class RegPlanTransferList;
class RegPlanTransferAllocList;

#undef IFASTCBO_LINKAGE
#ifdef IFASTCBO_DLL
   #define IFASTCBO_LINKAGE CLASS_EXPORT
#else
   #define IFASTCBO_LINKAGE CLASS_IMPORT
#endif

class IFASTCBO_LINKAGE RegPlanTransfer : public MFCanBFCbo, private boost::noncopyable
{
public:
   RegPlanTransfer( BFAbstractCBO &parent );
   virtual ~RegPlanTransfer();

   SEVERITY init( const BFDataGroupId& idDataGroup, const BFData& viewData);
   SEVERITY initNew( const BFDataGroupId& idDataGroup);

   void init2( const BFDataGroupId& idDataGroup, RegPlanTransferList *pList );

   virtual void doInitWithDefaultValues(const BFDataGroupId& idDataGroup);

   virtual SEVERITY doApplyRelatedChanges( const BFFieldId& idField,const BFDataGroupId& idDataGroup );
   virtual SEVERITY doValidateAll( const BFDataGroupId& idDataGroup, long lValidateGroup );
   virtual SEVERITY doValidateField( const BFFieldId& idField, const DString& strValue, const BFDataGroupId& idDataGroup );
   SEVERITY validateFundCode( const DString& dstrfundCode, const BFDataGroupId& idDataGroup );
   SEVERITY validateClassCode( const DString& dstrfundCode, const DString& dstrClassCode, const BFDataGroupId& idDataGroup );
   SEVERITY validateExternalInst( const DString& strValue, const BFDataGroupId& idDataGroup);

   SEVERITY getRegPlanTransferAllocList(const BFDataGroupId& idDataGroup,  RegPlanTransferAllocList *&pRegPlanTransferAllocList );
   void applyAmountTypeAllocChange( const BFDataGroupId& idDataGroup);
   void ModelOffer(RegPlanTransfer *Model, const BFDataGroupId& idDataGroup);

};


