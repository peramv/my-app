//*****************************************************************************
//
// COPYRIGHT:
//
//    The computer systems, procedures, data bases and
//    programs created and maintained by DST Systems, Inc.,
//    are proprietary in nature and as such are confidential.
//    Any unauthorized use or disclosure of such information
//    may result in civil liabilities.
//
//    Copyright 2002 by International Financial
//
//*****************************************************************************
//
// ^FILE   : ReportParamList.hpp
// ^AUTHOR : 
// ^DATE   : Nov 25, 2002
//
//-----------------------------------------------------------------------------
//
// ^CLASS  : ReportParamList
//
// ^MEMBER VARIABLES :
//
// ^CODING COMMENTS :
//
//*****************************************************************************

#include <ifastcbo\mfcancbo.hpp>
#include <boost\utility.hpp>

#undef IFASTCBO_LINKAGE
#ifdef IFASTCBO_DLL
   #define IFASTCBO_LINKAGE CLASS_EXPORT
#else
   #define IFASTCBO_LINKAGE CLASS_IMPORT
#endif

class IFASTCBO_LINKAGE ReportParamList : public MFCanBFCbo, private boost::noncopyable
{
   public:
	//******************************************************************************
	// Constructor
	// @param   BFBase - pointer to the parent BFBase
	//******************************************************************************
	ReportParamList( BFAbstractCBO &parent );

	//******************************************************************************
	// Destructor
	//******************************************************************************
	~ReportParamList();

	//******************************************************************************
	//******************************************************************************
	SEVERITY init( const DString& dstrSchedJobId, 
                  const DString& dstrCompanyId,
                  const BFDataGroupId& idDataGroup,
				      const DString& dstrTrack = I_("N"),
                  const DString& dstrPageName = NULL_STRING );

	//******************************************************************************
	// getMore retrieves more data.
	// @return SEVERITY - NO_CONDITION/WARNING/SEVERE_ERROR based view call.
	//                    SEVERE_ERROR if the accural type is not defined to be
	//                    INTEREST_ACCRUAL/MF_ACCRUAL/MF_REBATE_ACCRUAL
	//******************************************************************************
	SEVERITY getMore( );

   private:
   BFData* _pRequestData;

};

//******************************************************************************
//              Revision Control Entries
//******************************************************************************
/* $Log:   Y:/VCS/BF iFAST/ifastcbo/ReportParamList.hpp-arc  $
//
//   Rev 1.4   Nov 14 2004 14:51:56   purdyech
//PET910 - .NET Conversion
//
//   Rev 1.3   Mar 21 2003 18:21:26   PURDYECH
//BFDataGroupId/BFContainerId changeover
//
//   Rev 1.2   Dec 08 2002 22:05:16   HSUCHIN
//added companyid to init
//
//   Rev 1.1   Nov 29 2002 14:52:12   HSUCHIN
//check in for rel 50
//
//   Rev 1.0   Nov 27 2002 11:40:44   HSUCHIN
//Initial Revision
*/