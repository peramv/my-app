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
// ^FILE   : SeqFundValidation.hpp
// ^AUTHOR : Robert Kovacs
// ^DATE   : 08/14/2000
//
// ^CLASS    : SeqFundValidation
// ^SUBCLASS :
//
// ^CLASS DESCRIPTION :
//
//******************************************************************************


#include <ifastcbo\mfcancbo.hpp>
#include <boost\utility.hpp>
///#endif

#undef IFASTCBO_LINKAGE
#ifdef IFASTCBO_DLL
   #define IFASTCBO_LINKAGE CLASS_EXPORT
#else
   #define IFASTCBO_LINKAGE CLASS_IMPORT
#endif

class MasterContractList;

class IFASTCBO_LINKAGE SeqFundValidation : public MFCanBFCbo, private boost::noncopyable
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

   SeqFundValidation( BFAbstractCBO &parent );
   virtual ~SeqFundValidation();

   SEVERITY init( const BFData& InstData, 
                  const DString& strFundCode, 
                  const DString& strClassCode,
                  const DString& strAccountNum,
                  const DString& strEffectiveDate,
                  const DString& strEventTransType = NULL_STRING);

   SEVERITY init( const DString& strFundCode, 
                  const DString& strClassCode,
                  const DString& strAccountNum,
                  const DString& strEffectiveDate,
                  const DString& strEventTransType = NULL_STRING,
                  const DString& strFundCodeTo = NULL_STRING ,
                  const DString& strClassCodeTo = NULL_STRING ,
                  const DString& strAccountNumTo = NULL_STRING ,
                  const DString& strTransType = NULL_STRING,
                  bool  bViewCall = true,
                  const DString& dstrTrack= I_("N"),
                  const DString& dstrPageName = NULL_STRING );

   SEVERITY init( const DString& strFundCode, 
                  const DString& strClassCode,
                  const DString& strEffectiveDate,
                  const DString& strAcctDesignation,
                  const DString& strTaxType,
                  const DString& strPensionJuris,
                  const DString& strDofBirth,
                  const DString& strContractType,
                  const DString& strMaturityType,
                  const DString& strUserMaturityDate,
                  const DString& strAgeBasedOn,
                  bool  bViewCall = true,
                  const DString& dstrTrack= I_("N"),
                  const DString& dstrPageName = NULL_STRING );

   void getInitValues(DString &strFundCode, DString &strClassCode, DString &strAccountNum, 
                      DString &strEffectiveDate, DString& strEventTransType);
   SEVERITY canTradeFundClass ( const BFDataGroupId& idDataGroup );
   SEVERITY validateSegFund( DString dstrAcctGroup, DString dstrEffectiveDate, 
                             DString dstrEffectDateCnt, DString dstrContractType, 
                             const BFDataGroupId& idDataGroup );
   SEVERITY checkBackdatedAllowed ( const DString &strTradeDate, const BFDataGroupId& idDataGroup );


   bool isChanged( const DString& strFundCode, 
                   const DString& strClassCode,
                   const DString& strAccountNum, 
                   const DString& strEffectiveDate,
                   const DString& strEventTransType = NULL_STRING ,
                   const DString& strFundCodeTo = NULL_STRING ,
                   const DString& strClassCodeTo = NULL_STRING ,
                   const DString& strAccountNumTo = NULL_STRING );

   SEVERITY reInit( const DString& strFundCode, 
                    const DString& strClassCode, 
                    const DString& strAccountNum, 
                    const DString& strEffectiveDate,
                    const DString& strEventTransType = NULL_STRING ,
                    const DString& strFundCodeTo = NULL_STRING ,
                    const DString& strClassCodeTo = NULL_STRING ,
                    const DString& strAccountNumTo = NULL_STRING,
                    const DString& strTransType = NULL_STRING);

   SEVERITY init354( const DString& strAcctNum, 
                     const DString& strContractType,
                     const DString& strEffectiveDate,
                     const DString& dstrContractTypeId = NULL_STRING,
                     bool  bViewCall = true,
                     const DString& dstrTrack = I_("N"),
                     const DString& dstrPageName = NULL_STRING ); 

   SEVERITY addSegFundValidationWarnings( const BFDataGroupId& idDataGroup );
   SEVERITY SegFundValidationWarnings( const BFDataGroupId& idDataGroup );

protected:
   void getErrMsgValue( DString dstrErrNum,
                        const BFDataGroupId& idDataGroup, 
                        DString& dstrErrValue);

private:

   DString m_strFundCode;
   DString m_strClassCode;
   DString m_strAccountNum;
   DString m_strEffectiveDate;
   DString m_strFundCodeTo;
   DString m_strClassCodeTo;
   DString m_strAccountNumTo;
   DString m_strEventTransType;
   DString m_strTransType;

   bool bValid;//the purpose is to keep track of a SeqFundValidation if it's valid or not - only for performance reasons
   bool bChecked;//was it chequed if valid or not ?
   bool bIsNewAccount; //the purpose is to execute different logic in canTradeFundClass() base on New account or existing account

   void saveInitValues( const DString& strFundCode, 
                        const DString& strClassCode,
                        const DString& strAccountNum, 
                        const DString& strEffectiveDate,
                        const DString& strEventTransType = NULL_STRING,
                        const DString& strTransType = NULL_STRING,
                        const DString& strFundCodeTo = NULL_STRING ,
                        const DString& strClassCodeTo = NULL_STRING ,
                        const DString& strAccountNumTo = NULL_STRING );

   SEVERITY getMasterContractList(MasterContractList*& _pMasterContractList, const BFDataGroupId& idDataGroup);

   BFData *_pV140ReceivedData;
   BFData *_pV354ReceivedData;
};

//******************************************************************************
//              Revision Control Entries
//******************************************************************************
/* $Log:   Y:/VCS/BF iFAST/ifastcbo/SeqFundValidation.hpp-arc  $
//
//   Rev 1.18   Jun 01 2012 15:43:16   dchatcha
//IN#2952786 - Err Msg when keying Purchase Before Guarantee Adjustment- Trade Entry Screen
//
//   Rev 1.17   Jan 30 2012 14:58:14   dchatcha
//IN# 2799812 - Contract Screen Issues.
//
//   Rev 1.16   Jul 25 2006 19:29:44   porteanm
//Incident 642056 - UDM validation. Layout change for 354 request and fixed response.
//
//   Rev 1.15   May 25 2006 09:41:12   jankovii
//PET 2102 FN02 - Manulife Flex Trade/Systematic Entry.
//
//   Rev 1.14   Sep 23 2005 18:25:00   ZHANGCEL
//PET1244 FN01 -- Seg Func Evolution enhancement
//
//   Rev 1.13   Jun 15 2005 15:44:34   porteanm
//PET1024 FN40 - Guarantee Adjustments.
 * 
*/