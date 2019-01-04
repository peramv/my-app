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
//    Copyright 1997 by DST Systems, Inc.
//
//
//******************************************************************************
//
// ^FILE   : DirectTrading.hpp
// ^AUTHOR : 
// ^DATE   : 
//
// ^CLASS    : DirectTrading
// ^SUBCLASS :
//
// ^CLASS DESCRIPTION :
//
//******************************************************************************

#include <ifastcbo\mfcancbo.hpp>
#include <boost\utility.hpp>

class MgmtCoOptions;
class DirectTradingList;

#undef IFASTCBO_LINKAGE
#ifdef IFASTCBO_DLL
   #define IFASTCBO_LINKAGE CLASS_EXPORT
#else
   #define IFASTCBO_LINKAGE CLASS_IMPORT
#endif

class IFASTCBO_LINKAGE DirectTrading : public MFCanBFCbo
{
public:
   //TODO: enter specific field enumerations
   enum FIELD
   {
      UNUSED_FIELD,
      MAX_FIELDS
   };

   //TODO: enter specific contained object enumerations
   enum OBJECT
   {
      UNUSED_OBJECT,
      MAX_OBJECTS
   };

   DirectTrading( BFAbstractCBO &parent );
   virtual ~DirectTrading();

   void init(DirectTradingList* DTAList, const BFDataGroupId& idDataGroup );
   
   SEVERITY init(DirectTradingList* DTAList, const BFData& InstData );

   SEVERITY doValidateField( const BFFieldId& idField, const DString& strValue, const BFDataGroupId& idDataGroup );

   virtual SEVERITY doApplyRelatedChanges( const BFFieldId& idField, const BFDataGroupId& idDataGroup );
   //virtual SEVERITY doValidateAll( const BFDataGroupId& idDataGroup, long lValidateGroup );

   virtual void doInitWithDefaultValues( const BFDataGroupId& idDataGroup );

private:

   void SetDefault(const BFDataGroupId& idDataGroup);
   void setDTATypeSubstitutionSet( const BFDataGroupId& idDataGroup );
   DirectTradingList* _pDirectTradingList;

   bool IsDTADuplicated(const DString& strAddrCode, const BFDataGroupId& idDataGroup);
   void validateEffectiveStopDate(const BFDataGroupId& idDataGroup);
   void validateCodeEffectStop(DString strAddrCode,const BFDataGroupId& idDataGroup);
   void validateDTAType(const BFDataGroupId& idDataGroup);
};
