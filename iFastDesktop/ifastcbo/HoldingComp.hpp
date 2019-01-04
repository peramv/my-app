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
// ^FILE   : HoldingComp.hpp
// ^AUTHOR : 
// ^DATE   : Jan 28, 2013
//
// ^CLASS    : HoldingComp
// ^SUBCLASS :
//
// ^CLASS DESCRIPTION :
//
//******************************************************************************

#include <boost\utility.hpp>

#undef IFASTCBO_LINKAGE
#ifdef IFASTCBO_DLL
   #define IFASTCBO_LINKAGE CLASS_EXPORT
#else
   #define IFASTCBO_LINKAGE CLASS_IMPORT
#endif

class IFASTCBO_LINKAGE HoldingComp : public MFCanBFCbo, private boost::noncopyable
{
public:
   HoldingComp( BFAbstractCBO &parent );
   virtual ~HoldingComp();

   SEVERITY Init(const BFData& data);

   virtual SEVERITY InitNew( const BFDataGroupId& idDataGroup ); //for creating new object
   virtual void getField ( const BFFieldId &idField, DString &fieldValue, const BFDataGroupId &idDataGroup, 
                              bool formattedReturn) const;
  
protected:
	virtual SEVERITY doValidateField( const BFFieldId& idField,
                                    const DString& strValue,
                                    const BFDataGroupId& idDataGroup );
   virtual void setFieldsReadOnly(const BFDataGroupId& idDataGroup, bool bReadOnly); 
	virtual SEVERITY doApplyRelatedChanges( const BFFieldId& idField, const BFDataGroupId& idDataGroup );
   virtual void doInitWithDefaultValues( const BFDataGroupId& idDataGroup );
   SEVERITY validateHoldingCompCode(const BFDataGroupId& idDataGroup );

   SEVERITY validateEffectiveStopDate( const BFDataGroupId& idDataGroup );
   SEVERITY getEntity(Entity* &pEntity, const BFDataGroupId& idDataGroup);
private:
	DString orgDEFF;

};