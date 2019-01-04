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
// ^FILE   : FeeParam.hpp
// ^AUTHOR : Yingbao Li
// ^DATE   : January 24, 2002
//
// ^CLASS    : FeeParam
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

class FeeScaleList;
class FundFeeList;
class FeeParamConfig;
class IFASTCBO_LINKAGE FeeParam : public MFCanBFCbo, private boost::noncopyable
{
public:
   FeeParam( BFAbstractCBO &parent );
   virtual ~FeeParam();

   SEVERITY init(const BFData& data,const BFData *pAcctFeeScaleData,const DString& AcctFeeParamId);

   SEVERITY init( const BFDataGroupId& idDataGroup ); //for creating new object

   SEVERITY getFeeScaleList( FeeScaleList *&pFeeScaleList, const BFDataGroupId& idDataGroup );
   virtual void getField( const BFFieldId& idField, 
                          DString & strValue, 
                          const BFDataGroupId& idDataGroup, 
                          bool formattedReturn = false ) const;

   bool isTheSameBusinessDate( const BFDataGroupId& idDataGroup );
   SEVERITY validateFeeScaleList(const BFDataGroupId& idDataGroup);
   void getFundFeeList(FundFeeList*& pFundFeeList){
      pFundFeeList = _pFundFeeList;
   }
   SEVERITY refreshFundFeeList(const BFDataGroupId& idDataGroup);
	bool isActiveRecord(const BFDataGroupId& idDataGroup);

protected:
   virtual SEVERITY doValidateField( const BFFieldId& idField, const DString& strValue, const BFDataGroupId& idDataGroup );
   virtual SEVERITY doApplyRelatedChanges( const BFFieldId& idField, const BFDataGroupId& idDataGroup );
   virtual void doInitWithDefaultValues( const BFDataGroupId& idDataGroup );
   virtual SEVERITY doValidateAll( const BFDataGroupId& idDataGroup, long lValidateGroup );

   virtual SEVERITY setField( const BFFieldId& idField, 
                              const DString& dstrValue,
                              const BFDataGroupId& idDataGroup, 
                              bool bFormatted, 
                              bool bSideEffect, 
                              bool  bCheckCurrentValue);
/**
    * virtual function. Should be overwritten in order to do special processing in setField before the actual value is 
    * filled in into the CBO
    * @param idField      - the identifier of the field to be set
    * @param strValue      - the value to be set
    * @param idDataGroup  - the identifier of the data group with which the field should be set
    * @param bFormatted    - strValue is formatted or not
   */
   SEVERITY doPreSetField( const BFFieldId& idField, DString & strValue, const BFDataGroupId& idDataGroup, bool bFormatted );


private:
  // SEVERITY validateFeeParamTypeFundClass(const BFDataGroupId& idDataGroup );
//   SEVERITY refreshFundFeeList(const BFDataGroupId& idDataGroup);
   SEVERITY validateAllowOveride(const BFDataGroupId& idDataGroup);
   void setFundClassCode( const BFFieldId& idField,const BFDataGroupId& idDataGroup);
   SEVERITY ValidateDate( const BFFieldId& idField, const BFDataGroupId& idDataGroup );
   SEVERITY validateFundCode( const DString& dstrfundCode, const BFDataGroupId& idDataGroup );
   SEVERITY validateClassCode( const DString& dstrfundCode, 
                               const DString& dstrClassCode, const BFDataGroupId& idDataGroup );
   void setFieldsReadOnly(const BFDataGroupId& idDataGroup,  bool bReadOnly); 
   SEVERITY setFundNumber( const BFFieldId& idField,const BFDataGroupId& idDataGroup);
   void setFeeTypeRate(const BFDataGroupId& idDataGroup);
   SEVERITY validateFundClass(const BFDataGroupId& idDataGroup );
   SEVERITY FundManagementFeeOrRebate(const BFDataGroupId& idDataGroup,bool& bManageFee,
                                      bool& bManageFeeRebate );

   SEVERITY validateFeeCodeFundClass(const BFDataGroupId& idDataGroup);
   SEVERITY validateRate( const BFDataGroupId& idDataGroup );
   SEVERITY setFieldForScale( const BFFieldId& idField, const DString&  strValue, const BFDataGroupId& idDataGroup,bool bFormat );

   SEVERITY validateGroupFundClass(const BFDataGroupId& idDataGroup );
   SEVERITY validateFeeOverlap(const BFDataGroupId& idDataGroup);
 	void setupFeeCodeRelatedFields(const BFDataGroupId& idDataGroup, bool bIsSameDate);

   SEVERITY validateFeeCode (const DString &dstrFeeCode, const BFDataGroupId& idDataGroup);

	SEVERITY checkDuplicateAndCoexit (	 
									  const BFDataGroupId& idDataGroup
								     ,const DString& dstrFeeCode
									 ,const DString& dstrFundCode 
									 ,const DString& dstrClassCode
									 ,const DString& dstrCommGroupCode
									 ,const DString& dstrEffectiveDate
									 ,const DString& dstrAcctNum
									 ,const DString& dstrValidateType
									 ,const DString& dstrFeeId
									 ,const DString& dstrFamilyCode
									 ,const DString& dstrFundFrom
									 ,const DString& dstrClassFrom
									 ,const DString& dstrStopDate
									 ,const DString& dstrBrokerCode
									 ,const DString& dstrShGroup
									 ,const DString& dstrBranchCode 
									 ,const DString& dstrSalesRepCode
									 ,const DString& dstrExcludeFeeCode
									  	
									 							 	);
	FeeParamConfig*  getFeeConfigObject(const DString& dstrFeeCode);

   FundFeeList* _pFundFeeList;
};

//******************************************************************************
//              Revision Control Entries
//******************************************************************************
//
/* $Log:   Y:/VCS/BF iFAST/ifastcbo/FeeParam.hpp-arc  $
//
//   Rev 1.18   Oct 15 2010 09:38:24   jankovii
//IN 2292935 - R101 - AIC Trailer Phase 2 -  A/C Level existing Fee Parameter
//
//   Rev 1.17   Nov 14 2004 14:40:08   purdyech
//PET910 - .NET Conversion
//
//   Rev 1.16   Mar 18 2004 10:51:08   YINGBAOL
//PTS10021889: 1. separate checking overlapping and coeixst logic in view 197;2. Turning: if all records are already at desktop side, desktop will not call view 197, this will improve real time performance.
//
//   Rev 1.15   Aug 30 2003 16:06:28   YINGBAOL
//AMS Fee Calculation enhancement
//
//   Rev 1.14   Jun 20 2003 16:21:44   linmay
//added for flat fee
//
//   Rev 1.13   May 13 2003 08:47:10   sanchez
//sync  up with v.1.10.1.0 PTS#10016338
//
//   Rev 1.12   Mar 21 2003 18:09:04   PURDYECH
//BFDataGroupId/BFContainerId changeover
//
//   Rev 1.11   Mar 10 2003 14:43:00   linmay
//added validateFeeOverlap, setupFeeCodeRelatedFields
//
//   Rev 1.10   Jan 02 2003 15:21:58   linmay
//added validateGroupFundClass
//
//   Rev 1.9   Oct 09 2002 23:54:30   PURDYECH
//PVCS Database Conversion
//
//   Rev 1.8   Aug 29 2002 12:52:24   SMITHDAV
//ClientLocale and typed field changes.
//
//   Rev 1.7   24 May 2002 15:02:12   KOVACSRO
//doPresetField changes.
//
//   Rev 1.6   22 May 2002 18:21:10   PURDYECH
//BFData Implementation
//
//   Rev 1.5   Mar 19 2002 16:52:06   YINGBAOL
//add setFieldForScale
//
//   Rev 1.4   Mar 05 2002 14:09:26   YINGBAOL
//add validateRate etc.
//
//   Rev 1.3   Mar 01 2002 16:24:04   YINGBAOL
//add dopreSetField
//
//   Rev 1.2   Feb 28 2002 12:49:26   YINGBAOL
//add more function
//
//   Rev 1.1   Feb 22 2002 14:20:30   YINGBAOL
//more function added
 * 
 
*/

