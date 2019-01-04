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
// ^FILE   : AutoTransAllocation.hpp
// ^AUTHOR : Yingbao Li
// ^DATE   : March 27, 2000
//
// ^CLASS    : AutoTransAllocation
// ^SUBCLASS :
//
// ^CLASS DESCRIPTION :
//
//******************************************************************************

#include <ifastcbo\mfcancbo.hpp>
#include <boost\utility.hpp>

class AutoTransAllocationList;
class Systematic;

#undef IFASTCBO_LINKAGE
#ifdef IFASTCBO_DLL
   #define IFASTCBO_LINKAGE CLASS_EXPORT
#else
   #define IFASTCBO_LINKAGE CLASS_IMPORT
#endif

class IFASTCBO_LINKAGE AutoAcctTransAllocation : public MFCanBFCbo, private boost::noncopyable
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

   //TODO: remove public default constructor if using repository
   AutoAcctTransAllocation( BFAbstractCBO &parent );

   virtual ~AutoAcctTransAllocation();

   SEVERITY init( const BFData &viewData );

   void getField( const BFFieldId& idField, 
                  DString& strFieldValue, 
                  const BFDataGroupId& idDataGroup, 
                  bool formattedReturn = false ) const;

   virtual SEVERITY setField( const BFFieldId& idField, 
                              const DString& dstrValue,
                              const BFDataGroupId& idDataGroup, 
                              bool  bFormatted = true, 
                              bool  bSideEffect = false,
                              bool  bCheckCurrentValue = true);

   SEVERITY doValidateField( const BFFieldId& idField, const DString& strValue, const BFDataGroupId& idDataGroup );
   SEVERITY  getAtAllocationList( AutoTransAllocationList *&pAtAllocationList );

   SEVERITY initAtAlloc( const BFDataGroupId& idDataGroup, 
                         const BFData &pViewData, 
                         const DString& strKey,
                         const DString& strAccount,
                         bool bHasAcct = false);

   SEVERITY  initNewAtAllocation( const BFDataGroupId& idDataGroup );

   void init(const DString& strAcct, const DString& strFundTo, const DString& strClassTo, const DString& strAmount);
	void parentFieldChangeNotify(const BFFieldId& fieldId,
				const BFDataGroupId& idDataGroup, 
				DString& dstrValue,
				bool bFormat);


   Systematic* getSystematicPtr() const
   {
      return(_pSystematic);
   };

   void setSystematicPtr(Systematic* pSystematic){
      _pSystematic = pSystematic;
   };

   void ModelOffer( AutoAcctTransAllocation * Model, const BFDataGroupId& idDataGroup );
   void GetDefaultSplitComm ( const BFDataGroupId& idDataGroup);
   void GetSplitCommFlag ( const BFDataGroupId& idDataGroup, DString &dstrSplitComm );

private:

   Systematic* _pSystematic;
	SEVERITY  calculateFieldsForAlloc(const BFDataGroupId& idDataGroup );

   void ValidatePercentage( const DString& strValue, const BFDataGroupId& idDataGroup ) const;
   void ValidateAmount( const DString& Amount, const BFDataGroupId& idDataGroup );

   AutoTransAllocationList* _pAtAllocationList;

   BFData* localData_;
};

///#endif
