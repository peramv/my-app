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
//    Copyright 2000 by DST Systems, Inc.
//
//
//******************************************************************************
//
// ^FILE   : ESoPInfo.hpp
// ^AUTHOR : Robert Kovacs
// ^DATE   : 07/29/2000
//
// ^CLASS    : ESoPInfo
// ^SUBCLASS :
//
// ^CLASS DESCRIPTION :
//
//******************************************************************************

#include <ifastcbo\mfcancbo.hpp>
#include <boost\utility.hpp>

class ESoPHistoricalList;

#undef IFASTCBO_LINKAGE
#ifdef IFASTCBO_DLL
   #define IFASTCBO_LINKAGE CLASS_EXPORT
#else
   #define IFASTCBO_LINKAGE CLASS_IMPORT
#endif

class IFASTCBO_LINKAGE ESoPInfo : public MFCanBFCbo, private boost::noncopyable
{
public:

   ESoPInfo( BFAbstractCBO &parent );
   virtual ~ESoPInfo();

   SEVERITY init( const BFDataGroupId& idDataGroup, const DString& dstrTrack = I_("N"),
                  const DString& dstrPageName = NULL_STRING );
   SEVERITY initNew(const BFDataGroupId& idDataGroup, const DString& dstrTrack = I_("N"),
                    const DString& dstrPageName = NULL_STRING );
   SEVERITY getESoPHistoricalList( ESoPHistoricalList *&pESoPHistoricalList, 
                                   const BFDataGroupId& idDataGroup, bool bCreate = true);

protected:

   /**
    * virtual function. Should be overwritten in order to store custom default values into the CBO
    * @param idDataGroup  - the identifier of the data group with which the initialisation should be done
   */
   void doInitWithDefaultValues( const BFDataGroupId& idDataGroup );
   /**
    * virtual function. It should be overwritten in order to have special processing in a setField after the validation succeeds on in 
    * setFieldNoValidate after the value is stored in the CBO
    * @param idField      - the identifier of the field for which we want to apply the related changes
    * @param idDataGroup  - the identifier of the data group for which we want to apply the related field changes
   */
   SEVERITY doApplyRelatedChanges( const BFFieldId& idField, const BFDataGroupId& idDataGroup );
   /**
    * virtual function. It should be overwriten in order to do field validation. It is called by
    * validateField
    * @param idField     - the identifier of the field for which we are doing the validation
    * @param strValue     - the value of the field on which the validation is based on
    * @param idDataGroup - the identifier of the data group for which we are doing the validation
   */
   SEVERITY doValidateField( const BFFieldId& idField,
                             const DString& strValue,
                             const BFDataGroupId& idDataGroup );
   void getField( const BFFieldId& idField, DString & strValue, const BFDataGroupId& idDataGroup, bool formattedReturn = false ) const;

private:


   void setFundClassCode(const BFDataGroupId& idDataGroup);
   void setFundNumber(const BFDataGroupId& idDataGroup);
   void setFundName(const BFDataGroupId& idDataGroup);

   SEVERITY validateFundClass ( const BFDataGroupId& idDataGroup );
   SEVERITY validateFromFundNumber(const BFDataGroupId& idDataGroup);
   SEVERITY validateInterruptDate(const BFDataGroupId& idDataGroup);
   SEVERITY validateAmount(const BFDataGroupId& idDataGroup);
   SEVERITY validateFundCode(const BFDataGroupId& idDataGroup);

   void setFieldsReadOnly(const BFDataGroupId& idDataGroup);
   void setAllFieldsReadOnly(const BFDataGroupId& idDataGroup, bool bReadOnly = true);
   SEVERITY InitPurchDateRelChanges(const BFDataGroupId& idDataGroup);
   SEVERITY ContStartDateRelChanges(const BFDataGroupId& idDataGroup);
   SEVERITY InterruptCodeRelChanges(const BFDataGroupId& idDataGroup);
   bool isESopEligible(const DString& strFundCode, const DString& strClassCode, const BFDataGroupId& idDataGroup);
};

///#endif
