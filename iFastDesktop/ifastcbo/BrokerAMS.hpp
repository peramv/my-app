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
//    Copyright 1997 by DST Systems, Inc.
//
//
//******************************************************************************
//
// ^FILE   : BrokerAMS.hpp
// ^AUTHOR : 
// ^DATE   : 
//
// ^CLASS    : BrokerAMS
// ^SUBCLASS :
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

class BrokerAMSList;
class AmsFundAllocList;

class IFASTCBO_LINKAGE BrokerAMS : public MFCanBFCbo, private boost::noncopyable
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

   BrokerAMS( BFAbstractCBO &parent );
   virtual ~BrokerAMS();

   SEVERITY init( BrokerAMSList* amsbrokerList, const BFData& InstData );

   SEVERITY init(BrokerAMSList* amsbrokerList, const BFDataGroupId& idDataGroup);

   
   SEVERITY doPreValidateAll( const BFDataGroupId& idDataGroup );
/**
    * virtual function. Should be overwritten in order to do special processing in setField before the actual value is 
    * filled in into the CBO
    * @param idField      - the identifier of the field to be set
    * @param strValue      - the value to be set
    * @param idDataGroup  - the identifier of the data group with which the field should be set
    * @param bFormatted    - strValue is formatted or not
   */
   SEVERITY doPreSetField( const BFFieldId& idField, DString & strValue, const BFDataGroupId& idDataGroup, bool bFormatted );

   virtual void doInitWithDefaultValues( const BFDataGroupId& idDataGroup );
   SEVERITY getAMSFundAllocList( AmsFundAllocList *&pAmsFundAllocList,const BFDataGroupId& idDataGroup,bool bCreate = true,bool bDelExist = false);

  /**
   * Broker AMS Effective Date validation (this date should 
   * be today or less than today, today being Current Business Date)
   * 
   * @param idDataGroup
   * @return SEVERITY when Effective date is bigger than Current Business Date
   */
	SEVERITY validateBrokerAMSDeff( const BFDataGroupId& idDataGroup );
protected:
	virtual SEVERITY setField( const BFFieldId& idField, const DString& dstrValue, const BFDataGroupId& idDataGroup, 
                              bool bFormatted = true, bool bSideEffect = false, bool bCheckCurrentValue = true);
	SEVERITY doValidateField( const BFFieldId& idField, const DString& strValue, const BFDataGroupId& idDataGroup );
	
private:
   SEVERITY setDefault();
   BrokerAMSList * pBrokerAMSList;
   SEVERITY validateAMSCode(const DString& strValue,const BFDataGroupId& idDataGroup );
   SEVERITY doApplyRelatedChanges( const BFFieldId& idField, const BFDataGroupId& idDataGroup );
};
///#endif
