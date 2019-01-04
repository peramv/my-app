//*****************************************************************************
//
// COPYRIGHT:
//
//    The computer systems, procedures, data bases and
//    programs created and maintained by International Financial,
//    are proprietary in nature and as such are confidential.
//    Any unauthorized use or disclosure of such information
//    may result in civil liabilities.
//
//    Copyright 2003 by International Financial
//
//*****************************************************************************
//
// ^FILE   : ResetInstrList.hpp
// ^AUTHOR : 
// ^DATE   : Jan 17, 2003
//
//-----------------------------------------------------------------------------
//
// ^CLASS  : ResetInstrList
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

class IFASTCBO_LINKAGE ResetInstrList : public MFCanBFCbo, private boost::noncopyable
{
public:
   //X-structors
	ResetInstrList(BFAbstractCBO &parent);
	~ResetInstrList();
   SEVERITY init( const BFDataGroupId& idDataGroup = BF::HOST, 
                  const DString& dstrTrack = I_("N"), 
                  const DString& dstrPageName = NULL_STRING);
	SEVERITY init( const DString& dstrAccountNum,
                  const DString& dstrResetDate,
				      const DString& dstrTrack = I_("N"),
                  const DString& dstrPageName = NULL_STRING );
   SEVERITY init( const BFFieldId& idField, 
                  const DString& dstrValue,                       
                  const DString& dstrTrack = I_("N"),
                  const DString& dstrPageName = NULL_STRING );
	//******************************************************************************
	// getMore retrieves more data.
	// @return SEVERITY - NO_CONDITION/WARNING/SEVERE_ERROR based view call.
	//                    SEVERE_ERROR if the accural type is not defined to be
	//                    INTEREST_ACCRUAL/MF_ACCRUAL/MF_REBATE_ACCRUAL
	//******************************************************************************
	SEVERITY getMore( );   
   DString getAccountNum () { return _dstrAccountNum; };
   
   void Reversal ( const DString& oriKey, const DString& destKey, 
                   const BFDataGroupId& idDataGroup );
   int getNumOfReset( const DString& dstrFundCode, 
                      const DString& dstrClassCode, 
                      const DString& dstrAccountNum, 
                      const DString& dstrDate,
                      const BFDataGroupId& idDataGroup );

   protected:

   SEVERITY doCreateObject( const BFData& data, BFCBO*& pObjOut );
   SEVERITY doCreateNewObject( BFCBO*& pBase, DString& strKey, const BFDataGroupId& idDataGroup );
   SEVERITY doValidateAll( const BFDataGroupId& idDataGroup, long lValidateGroup );
   bool canDeleteObject ( const DString &strKey,  const BFDataGroupId &idDataGroup);

   private:

   BFData* _pRequestData;  
   DString _dstrAccountNum;

};

//******************************************************************************
//              Revision Control Entries
//******************************************************************************
/* $Log:   Y:/VCS/BF iFAST/ifastcbo/ResetInstrList.hpp-arc  $
//
//   Rev 1.7   Aug 09 2005 17:19:22   AGUILAAM
//IN 376007 - should not allow delete of reset when user has no active batch
//
//   Rev 1.6   Apr 05 2005 15:52:24   yingbaol
//Incident 243363: fix 2 issues, 1) wrong duplicate check; 2) wrong max reset instruction check.
//
//   Rev 1.5   Nov 14 2004 14:52:18   purdyech
//PET910 - .NET Conversion
//
//   Rev 1.4   May 28 2003 10:52:20   popescu
//Part of the cleaning of DSTCWorksession, not finalized yet, more to come....
//
//   Rev 1.3   Mar 21 2003 18:21:58   PURDYECH
//BFDataGroupId/BFContainerId changeover
//
//   Rev 1.2   Feb 06 2003 15:05:48   HSUCHIN
//added 2 methods getNumOfReset to get the number of resets for the fund/class passed in and doValidateAll to check for duplicate resets.
//
//   Rev 1.1   Jan 27 2003 07:43:20   HSUCHIN
//added reversal support and method to get current accountnum
//
//   Rev 1.0   Jan 24 2003 10:19:40   HSUCHIN
//Initial Revision
*/