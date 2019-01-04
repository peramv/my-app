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
// ^FILE   : AMSRebalancingCriteriaList.hpp
// ^AUTHOR : 
// ^DATE   : Nov 15, 2002
//
//-----------------------------------------------------------------------------
//
// ^CLASS  : AMSRebalancingCriteriaList
//
// ^MEMBER VARIABLES :
//
// ^CODING COMMENTS :
//
//*****************************************************************************

#include <ifastcbo\mfcancbo.hpp>
#include <boost\utility.hpp>
#include "ifastreportcriterialist.hpp"

#undef IFASTRPTCBO_LINKAGE
#ifdef IFASTRPTCBO_DLL
   #define IFASTRPTCBO_LINKAGE CLASS_EXPORT
#else
   #define IFASTRPTCBO_LINKAGE CLASS_IMPORT
#endif

class IFASTRPTCBO_LINKAGE AMSRebalancingCriteriaList : public ifastReportCriteriaList
{
	public:
	//*****************************************************************************
	// Constructor
	//*****************************************************************************
	AMSRebalancingCriteriaList( BFAbstractCBO &parent );

	//*****************************************************************************
	// Destructor
	//*****************************************************************************
	~AMSRebalancingCriteriaList();

   //*****************************************************************************
   // The init will set up the cardinality rules.  Refer to the struct 
   // m_CriteriaTypeCardinality for the rules.
   // @param   void.
   // @returns void.
   //*****************************************************************************
   void init ( );

   protected:

   //*****************************************************************************
   // This method will create a new AMSRebalancingCriteria cbo.
   // @param   BFCBO*& pBase - pointer to new AMSRebalancing cbo.
   //          DString& strKey - key of new AMSRebalacing cbo.
   //          long lDataGroupId - current data group id.
   // @returns SEVERITY - NO_CONDITION most of the time.
   //*****************************************************************************
   SEVERITY doCreateNewObject( BFCBO*& pBase, DString & strKey, long iDataGroupId  );   
};
//******************************************************************************
//              Revision Control Entries
//******************************************************************************
/* $Log:   Y:/VCS/BF iFAST/ifastrptcbo/AMSRebalancingCriteriaList.hpp-arc  $
//
//   Rev 1.0   Nov 19 2002 11:28:16   HSUCHIN
//Initial Revision
*/
