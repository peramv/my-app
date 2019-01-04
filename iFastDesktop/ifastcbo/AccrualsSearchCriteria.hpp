#pragma once



//******************************************************************************
//
// COPYRIGHT:
//
//    The computer systems, procedures, data bases and
//    programs created and maintained by International Financial, Inc.,
//    are proprietary in nature and as such are confidential.
//    Any unauthorized use or disclosure of such information
//    may result in civil liabilities.
//
//    Copyright 2002 by International Financial, Inc.
//
//
//******************************************************************************
//
// ^FILE   : AccrualsSearchCriteria.hpp
// ^AUTHOR : 
// ^DATE   : Jan 09, 2002
//
// ^CLASS    : AccrualsSearchCriteria
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

class FundDetailList;
class MFAccountHoldingList;

class IFASTCBO_LINKAGE AccrualsSearchCriteria : public MFCanBFCbo, private boost::noncopyable
{
public:

//*****************************************************************************
// Constructor
//*****************************************************************************

   AccrualsSearchCriteria( BFAbstractCBO &parent );

//*****************************************************************************
// Destructor
//*****************************************************************************

   virtual ~AccrualsSearchCriteria();

//*****************************************************************************
// Initializes search criteria cbo with default information.  Sets up a local
// pointer to Account Holdings for later verification.
// @param   DString dstrAccountNum - Account Number used to get Account Holdings
//          DString dstrAccrualType - Interest, MF, MFR are the 3 different types.
//          const BFDataGroupId& idDataGroup - current datagroup.
// @returns void.
//*****************************************************************************

   void init( const DString dstrAccountNum,
              const DString dstrAccrualType, 
              const BFDataGroupId& idDataGroup );

//*****************************************************************************
// Validates the field information. The following fields are validated.
// FundClass - Cross edit of FundCode, ClassCode
// StartDate
// FundNumber - Sets FundCode/Class Code when valid.
// @param   const BFFieldId& idField - field to be validated.
//          const DString& strValue - Value contained in field.
//          const BFDataGroupId& idDataGroup - datagroup to be validated.
// @returns SEVERITY.
//*****************************************************************************

   SEVERITY doValidateField( const BFFieldId& idField, 
                             const DString& strValue, 
                             const BFDataGroupId& idDataGroup );

private:

//*****************************************************************************
// Function which iterates through the fund holding comparing with the
// Fund/Class passed in.
// @param   const DString& dstrFundCode - Fund Code.
//          const DString& dstrClassCode - Class Code.
//          const BFDataGroupId& idDataGroup - current data group.
// @returns SEVERITY.
//*****************************************************************************

   SEVERITY isFundinHoldings ( const DString& dstrFundCode, const DString& dstrClassCode, const BFDataGroupId& idDataGroup );

//*****************************************************************************
// Sets the start date to the last divident date and stores additional fund 
// information for later validatation eg. Start date must be before fund 
// effective date.
// @param   const DString& dstrFundCode - Fund Code.
//          const DString& dstrClassCode - Class Code.
//          long lDataGroupid - current data group.
// @returns SEVERITY.
//*****************************************************************************

   SEVERITY setDefaultStartDate ( const DString& dstrFundCode, const DString& dstrClassCode, const BFDataGroupId& idDataGroup );  

//*****************************************************************************
// Validates the Date range.  Start date must be before end date. Start date
// must be later than Fund Effective date. Start date must be later than
// fund's last divident date.
// @param   const BFDataGroupId& idDataGroup - current date group.
// @returns SEVERITY.
//*****************************************************************************

   SEVERITY ValidateDateRange(const BFDataGroupId& idDataGroup);

//*****************************************************************************
// Functions which checks to see the current Fund/Class code is in the Account
// holdings.  NULL_STRING for Fund/Class codes is accepted and considered as all
// funds.
// @param   const BFDataGroupId& idDataGroup - current data group.
// @retursn SEVERITY.
//*****************************************************************************

   SEVERITY ValidateFundClass ( const BFDataGroupId& idDataGroup );

//*****************************************************************************
// This function will iterate through account holdings and Fund Details list
// seeking the earliest IntAccrLastDivDate (Last Divident Date) and Effective 
// date (Fund Effective Date).  These dates will then be stored to the private
// member variables _dstrIntAccrLastDivDate and _dstrEarliestStartDate.  This is
// used for All Fund mode for MF/MFR since Interest Accruals do not require
// start date for All Fund mode.
//
// @param   const BFDataGroupId& idDataGroup - current data group.
// @returns void
//*****************************************************************************

   void setEarliestAllFundDates ( const BFDataGroupId& idDataGroup );

//******************************************************************************
// Override the doPreValidationAll to mark the FundClass Field dirty so that
// doValidateField will always execute.
//
// @param   const BFDataGroupId& idDataGroup - current data group.
//******************************************************************************

   SEVERITY doPreValidateAll( const BFDataGroupId& idDataGroup );   

//******************************************************************************

   SEVERITY doApplyRelatedChanges( const BFFieldId& idField, const BFDataGroupId& idDataGroup );

//*****************************************************************************
// Not implemented
//*****************************************************************************
   AccrualsSearchCriteria( const AccrualsSearchCriteria& copy );      

//*****************************************************************************
// Not implemented
//*****************************************************************************
SEVERITY  validateStartDateFundClass( const BFDataGroupId& idDataGroup );

SEVERITY validateFundTypeForInterest(  const BFDataGroupId& idDataGroup );

   FundDetailList *_pFundDetailsList;              // Pointer to fund detail list.
   DString _dstrAccrualType;                       // Current accrual type.
   MFAccountHoldingList *_pMFAccountHoldingList;   // Pointer to account holdings list.
   DString _dstrEarliestStartDate;                 // Earliest start date of current fund.
   DString _dstrEarliestStartDateFormatted;                
   DString _dstrDefaultStartDate;
   DString _dstrDefaultStartDateFormatted;
	DString _dstrFundCode;
	DString _dstrClassCode;
};


//******************************************************************************
//              Revision Control Entries
//******************************************************************************
/* $Log:   Y:/VCS/BF iFAST/ifastcbo/AccrualsSearchCriteria.hpp-arc  $
//
//   Rev 1.12   Sep 08 2003 09:10:20   YINGBAOL
//add business rules for SSII
//
//   Rev 1.11   Mar 21 2003 17:55:32   PURDYECH
//BFDataGroupId/BFContainerId changeover
//
//   Rev 1.10   Oct 09 2002 23:53:56   PURDYECH
//PVCS Database Conversion
//
//   Rev 1.9   Aug 29 2002 12:51:34   SMITHDAV
//ClientLocale and typed field changes.
//
//   Rev 1.8   Jul 17 2002 13:44:10   HSUCHIN
//bug fix - DSTCommonFunction::formatToolTipDate is no longer use since getMask fails. 
//
//   Rev 1.7   22 May 2002 18:21:58   PURDYECH
//BFData Implementation
//
//   Rev 1.6   04 Apr 2002 13:48:28   HSUCHIN
//changed _dstrIntAccrLastDivDate to _dstrDefaultStartDate
//
//   Rev 1.5   03 Apr 2002 12:33:40   HSUCHIN
//added doapplyrelated changes
//
//   Rev 1.4   19 Mar 2002 13:14:52   PURDYECH
//Use #pragma once as include guard
//Remove compile time "including..." message
//
//   Rev 1.3   12 Mar 2002 15:43:46   HSUCHIN
//added doprevalidateall
//
//   Rev 1.2   12 Mar 2002 10:26:24   HSUCHIN
//added doinitwithdefaultvalues
//
//   Rev 1.1   27 Feb 2002 16:08:06   HSUCHIN
//added new function to setEarliestAllFundDates
//
//   Rev 1.0   21 Feb 2002 15:59:02   HSUCHIN
//Initial revision.
*/
