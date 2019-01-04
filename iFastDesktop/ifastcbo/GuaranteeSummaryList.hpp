#pragma once


//*****************************************************************************
//
// COPYRIGHT:
//
//    The computer systems, procedures, data bases and
//    programs created and maintained by International Financial Data Services
//    are proprietary in nature and as such are confidential.
//    Any unauthorized use or disclosure of such information
//    may result in civil liabilities.
//
//    Copyright 2005 by International Financial Data Services
//
//*****************************************************************************
//
// ^FILE   : GuaranteeSummaryList.hpp
// ^AUTHOR : 
// ^DATE   : 
//
// ^CLASS    :
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

class IFASTCBO_LINKAGE GuaranteeSummaryList : public MFCanBFCbo, private boost::noncopyable
{
public:
   GuaranteeSummaryList( BFAbstractCBO &parent );
   virtual ~GuaranteeSummaryList(void);
   SEVERITY init( const DString& dstrAccountNumber,
                  const DString& dstrTrack=I_("N"),
                  const DString& dstrPageName = NULL_STRING );  

   SEVERITY getGuaranteeInfoListByContract( const DString &dstrContractType,
	                                        const BFDataGroupId& idDataGroup,
			                                GuaranteeInfoList *&pGuaranteeInfoList,
								            const DString& dstrTrack =I_("N"),
                                            const DString& dstrPageName = NULL_STRING );

protected:
	virtual SEVERITY doCreateObject( const BFData& data, BFCBO *&pObjOut );	
	SEVERITY doCreateNewObject( BFCBO *& pBase, 
	                            DString &strKey, 
							    const BFDataGroupId& idDataGroup );

private:    
   BFData _requestData;

   DString _dstrAccountNum;
};

/* $Log:   Y:/VCS/BF iFAST/ifastcbo/GuaranteeSummaryList.hpp-arc  $
//
//   Rev 1.9   Jun 05 2006 16:53:42   porteanm
//Incident 635750 - Crash when no record available.
//
//   Rev 1.8   Sep 02 2005 12:13:14   porteanm
//Incident 393611 - Removed getStrKey() in order to keep the view sorting.
//
//   Rev 1.7   Aug 17 2005 16:31:54   porteanm
//Incident 351033 - Layout change.
 *  
 */

