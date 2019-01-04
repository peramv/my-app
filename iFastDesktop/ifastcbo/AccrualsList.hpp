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
//    Copyright 2002 by DST Systems, Inc.
//
//******************************************************************************
//
// ^FILE   : AccrualsList.hpp
// ^AUTHOR : 
// ^DATE   : Jan 9, 2002
//
// ^CLASS  : AccrualsList
// ^PARENT : ListBase
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

class AccrualsSearchCriteria;
class BFData;

class IFASTCBO_LINKAGE AccrualsList : public MFCanBFCbo, private boost::noncopyable
{
public:

   //******************************************************************************
   // Constructor
   // @param   BFBase - pointer to the parent BFBase
   //******************************************************************************

   AccrualsList( BFAbstractCBO &parent );

   //******************************************************************************
   // Destructor
   //******************************************************************************

   virtual ~AccrualsList();

   //******************************************************************************
   // Overloaded Function - Initalize CBO and executes view call
   // @param   const DString& dstrAccountNumber - Account Number ( Required )
   // @param   const DString& dstrFundCode - Fund Code ( Required )
   // @param   const DString& dstrClassCode - Class Code ( Required )
   // @param   const DString& dstrStartDate - Start Date ( Required )
   // @param   const DString& dstrEndDate - End Date ( Required )
   // @param   const DString& dstrInclUnsettled - Include Unsettled Trade is either
   //             I_("Y") or I_("N") ( Required ).
   // @param   const DString& dstrSummary - Summary Information is either I_("Y") or 
   //             I_("N") ( Required )
   // @param   const DString& dstrType - Type of Accrual has the values INTEREST_ACCRUAL,
   //             MF_ACCRUAL or MF_REBATE_ACCRUAL. ( Required )
   // @param   const DString& dstrTrack - Tracking flag ( used by eAdvisor )
   // @param   const DString& dstrPageName - Page Name value ( used by eAdvisor )
   // @return  SEVERITY - NO_CONDITION/WARNING/SEVERE_ERROR based view call.
   //******************************************************************************

   SEVERITY init( const DString& strAccountNumber, 
                  const DString& dstrFundCode, 
                  const DString& dstrClassCode,
                  const DString& dstrStartDate,
                  const DString& dstrEndDate, 
                  const DString& dstrInclUnsettled, 
                  const DString& dstrSummary, 
                  const DString& dstrType,
                  const DString& dstrTrack= I_("N"),                  
                  const DString& dstrPageName = NULL_STRING );

   //******************************************************************************
   // Overloaded Function - Inits CBO and executes view call
   // @param   AccrualsSearchCriteria *pAccrualsSearchCriteria - pointer to 
   //             AccrualsSearchCriteria CBO containing information such as Accrual Type.
   // @param   const BFDataGroupId& idDataGroup - Data Group.
   // @param   const DString& dstrTrack - Tracking flag ( used by eAdvisor )
   // @param   const DString& dstrPageName - Page Name value ( used by eAdvisor )
   // @return  SEVERITY - NO_CONDITION/WARNING/SEVERE_ERROR based view call.
   //******************************************************************************

   SEVERITY init( const AccrualsSearchCriteria *pAccrualsSearchCriteria, 
                  const BFDataGroupId& idDataGroup,
                  const DString& dstrTrack = I_("N"),
                  const DString& dstrPageName = NULL_STRING );

   //******************************************************************************
   // getMore retrieves more data for the current search criteria
   // @return  SEVERITY - NO_CONDITION/WARNING/SEVERE_ERROR based view call.
   //             SEVERE_ERROR if the accural type is not defined to be 
   //             INTEREST_ACCRUAL/MF_ACCRUAL/MF_REBATE_ACCRUAL
   //******************************************************************************

   SEVERITY getMore ( );   

   //******************************************************************************
   // getTotalEarned returns a DString representing the total earned.
   // @return  DString - sum of field IntValue for Interest Accrual.
   //                    sum of field Amount for MF/MFR.
   //******************************************************************************

   DString getTotalEarned () { return(_dstrTotalEarned);};

   //******************************************************************************
   // getTotalPaid returns a DString representing the total paid.
   // @return  DString - sum of field IntPaid for Interest Accrual.
   //                    sum of field AmtPaid for MF/MFR.
   //******************************************************************************

   DString getTotalPaid () { return(_dstrTotalPaid);};

   //******************************************************************************
   // getTotalAccumTotal returns a DString representing the total paid.
   // @return  DString - sum of field AccumTotal.
   //******************************************************************************

   DString getTotalAccumTotal () { return(_dstrTotalAccumTotal);};

   // The following methods are used by Management Fee and Management Fee Rebate.

   //******************************************************************************
   // getTotalGSTPaid returns a DString representing the total GST Paid
   // @return  DString - sum of the field GSTPaid.
   //******************************************************************************

   DString getTotalGSTPaid () { return(_dstrTotalGSTPaid);};

   //******************************************************************************
   // getTotalGSTOutstanding returns a DString representing the total GST Oustanding
   // @return  DString - sum of the field GSTOutstanding.
   //******************************************************************************

   DString getTotalGSTOutstanding () { return(_dstrTotalGSTOutstanding);};

   //******************************************************************************
   // getTotalNRTaxPaid returns a DString representing the total Non resisdent tax
   // Paid.
   // @return  DString - sum of the field NRTaxPaid.
   //******************************************************************************

   DString getTotalNRTaxPaid () { return(_dstrTotalNRTaxPaid);};

   //******************************************************************************
   // getTotalNRTaxOutstanding returns a DString representing the total Non resisdent 
   // tax outstanding.
   // @return  DString - sum of the field NRTaxoutstanding.
   //******************************************************************************

   DString getTotalNRTaxOutstanding () { return(_dstrTotalNRTaxOutstanding);};

   //******************************************************************************
   // getAsofDate returns the starting date used to return the accruals information.
   // NULL_STRING is returned whenever the accrual information request is summary
   // info since no starting date is required.
   // @return  start date used to return the accruals info.
   //******************************************************************************

   DString getAsofDate () { return(_dstrAsofDate);};

private:

   BFData *_pRequestData;                //Stores the request data object to be used by getMore
   DString _dstrAccrualType;           //Stores the accrual type.
   DString _dstrTotalEarned;           //Stores the total earned
   DString _dstrTotalPaid;             //Stores the total paid/charged.
   DString _dstrTotalAccumTotal;       //Stores the current accrued
   DString _dstrTotalGSTPaid;          //Stores the total GST paid
   DString _dstrTotalGSTOutstanding;   //Stores the total GST outstanding
   DString _dstrTotalNRTaxPaid;        //Stores the total Non resident tax paid
   DString _dstrTotalNRTaxOutstanding; //Stores the total Non resident tax outstanding
   DString _dstrAsofDate;              //Stores the Starting Date from the returned list.
   DString _dstrAsofDateFormatted;
};

///#endif //ACCRUALSLIST_HPP

//******************************************************************************
//              Revision Control Entries
//******************************************************************************
/* $Log:   Y:/VCS/BF iFAST/ifastcbo/AccrualsList.hpp-arc  $
//
//   Rev 1.7   Mar 21 2003 17:55:26   PURDYECH
//BFDataGroupId/BFContainerId changeover
//
//   Rev 1.6   Oct 09 2002 23:53:56   PURDYECH
//PVCS Database Conversion
//
//   Rev 1.5   Aug 29 2002 12:51:32   SMITHDAV
//ClientLocale and typed field changes.
//
//   Rev 1.4   Jul 17 2002 13:44:08   HSUCHIN
//bug fix - DSTCommonFunction::formatToolTipDate is no longer use since getMask fails. 
//
//   Rev 1.3   22 May 2002 22:22:18   PURDYECH
//BFData Implementation
//
//   Rev 1.2   16 Apr 2002 14:48:22   HSUCHIN
//added DString var and member functions to store totals
//
//   Rev 1.1   19 Mar 2002 13:14:52   PURDYECH
//Use #pragma once as include guard
//Remove compile time "including..." message
//
//   Rev 1.0   21 Feb 2002 15:58:20   HSUCHIN
//Initial revision.
*/