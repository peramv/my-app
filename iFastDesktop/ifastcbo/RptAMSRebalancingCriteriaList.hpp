//*****************************************************************************
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
//*****************************************************************************
//
// ^FILE   : RptAMSRebalancingCriteriaList.hpp
// ^AUTHOR : 
// ^DATE   : Nov 15, 2002
//
//-----------------------------------------------------------------------------
//
// ^CLASS  : RptAMSRebalancingCriteriaList
//
// ^MEMBER VARIABLES :
//
// ^CODING COMMENTS :
//
//*****************************************************************************

#include "mfcancbo.hpp"
#include <boost\utility.hpp>
#include "ifastreportcriterialist.hpp"
#include "AMSHypoAllocList.hpp"
#include "FundAllocList.hpp"

#undef IFASTCBO_LINKAGE
#ifdef IFASTCBO_DLL
   #define IFASTCBO_LINKAGE CLASS_EXPORT
#else
   #define IFASTCBO_LINKAGE CLASS_IMPORT
#endif

class IFASTCBO_LINKAGE RptAMSRebalancingCriteriaList : public ifastReportCriteriaList
{
	public:
	//*****************************************************************************
	// Constructor
	//*****************************************************************************
	RptAMSRebalancingCriteriaList( BFAbstractCBO &parent );

	//*****************************************************************************
	// Destructor
	//*****************************************************************************
	~RptAMSRebalancingCriteriaList();

   //*****************************************************************************
   // The init will set up the cardinality rules.  Refer to the struct 
   // m_CriteriaTypeCardinality for the rules.
   // @param   void.
   // @returns void.
   //*****************************************************************************
   void init ( const BFDataGroupId& idDataGroup);
   virtual void initWithRptName ( const BFDataGroupId& idDataGroup, DString dstrRptName );
   //*****************************************************************************
   // This method is invoked by the ifastCommonReportCriteria to apply rules when the 
   // Report Type switches between online/cycle.  AMS requires that the Incl Pending
   // Trades to be set to No when the Report Type is cycle.
   // @param   bool bOnline - boolean to indicate whether it is online or cycle.
   //          const BFDataGroupId& idDataGroup - current data group id.
   //*****************************************************************************
   virtual void doReportTypeRelatedChanges ( bool bOnline, const BFDataGroupId& idDataGroup );

   virtual SEVERITY doAllReportModeRelatedChanges ( const BFDataGroupId& idDataGroup );

   virtual SEVERITY doInitPendingModeRelatedChanges ( const BFDataGroupId& idDataGroup );

   virtual SEVERITY doAllReportNameRelatedChanges ( const BFDataGroupId& idDataGroup );

   virtual SEVERITY createAMSHypoAllocList ( AMSHypoAllocList*& pAMSHypoAllocList, 
											 DString identifyType,
											 DString identifyCode, 
											 FundAllocList* pFundAllocList, 
											 const BFDataGroupId& idDataGroup );

   virtual AMSHypoAllocList* getAMSHypoAllocList( const BFDataGroupId& idDataGroup );

   virtual SEVERITY deleteAMSHypoAllocList ( const BFDataGroupId& idDataGroup );

   protected:
	   
   //*****************************************************************************
   // This method will create a new rptAMSRebalancingCriteria cbo.
   // @param   BFCBO*& pBase - pointer to new AMSRebalancing cbo.
   //          DString& strKey - key of new AMSRebalacing cbo.
   //          const BFDataGroupId& idDataGroup - current data group id.
   // @returns SEVERITY - NO_CONDITION most of the time.
   //*****************************************************************************
   SEVERITY doCreateNewObject( BFCBO*& pBase, DString & strKey, const BFDataGroupId& idDataGroup  ); 
   
   virtual SEVERITY doValidateAll( const BFDataGroupId& idDataGroup, long lValidateGroup );

   private:

   //*****************************************************************************
   // This method creates a rptAMSRebalancingCriteria cbo and sets it up to the 
   // criteria type passed in marking it required and with default values.
   // @param   BFFieldId criteriaType - required criteria type to add to list.
   // @returns SEVERITY.
   //*****************************************************************************
   SEVERITY addRequiredRecord( BFFieldId fieldId, const BFDataGroupId& idDataGroup );

   AMSHypoAllocList* _pAMSHypoAllocList;
};
//******************************************************************************
//              Revision Control Entries
//******************************************************************************
/* $Log:   Y:/VCS/BF iFAST/ifastcbo/RptAMSRebalancingCriteriaList.hpp-arc  $
//
//   Rev 1.7   Nov 14 2004 14:53:12   purdyech
//PET910 - .NET Conversion
//
//   Rev 1.6   Jun 21 2004 12:25:44   VADEANUM
//PTS 10031151 - InclPending validation.
//
//   Rev 1.5   Jun 21 2004 10:19:00   VADEANUM
//PTS 10031437 - Exclude the edit check for error number 405 and 406 when user is running the option in 'Report' mode. Backed out changes for PTS ticket 10031151.
//
//   Rev 1.4   Jun 09 2004 15:08:26   VADEANUM
//PTS 10031151 - Include Pending Trades in Report mode, Online.
//
//   Rev 1.3   Mar 21 2003 18:22:34   PURDYECH
//BFDataGroupId/BFContainerId changeover
//
//   Rev 1.2   Dec 08 2002 21:51:40   HSUCHIN
//added doReportTypeRelatedChanges changes
//
//   Rev 1.1   Nov 29 2002 14:19:32   HSUCHIN
//rename cbo name
//
//   Rev 1.0   Nov 29 2002 13:38:38   HSUCHIN
//Initial revision.
//
//   Rev 1.0   Nov 27 2002 11:40:52   HSUCHIN
//Initial Revision
*/
