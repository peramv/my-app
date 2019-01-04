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
//    Copyright 2004 by DST Systems, Inc.
//
//******************************************************************************
//
// ^FILE   : BrokerRemarkList.hpp
// ^AUTHOR : Yingbao Li	
// ^DATE   : September 10, 2004
//
// ^CLASS  : BrokerRemarkList
// ^PARENT : MFCanBFCbo
//
// ^CLASS DESCRIPTION :
//    Implements View 315.
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

class BrokerRemark;

class IFASTCBO_LINKAGE BrokerRemarkList : public MFCanBFCbo, private boost::noncopyable
{
public:
   // X-structors
   BrokerRemarkList( BFAbstractCBO &parent );
   virtual ~BrokerRemarkList( void );

SEVERITY init(
   const int iType,
	const DString& dstrBrokerCode, 
	const DString& dstrBranchCode, 
	const DString& dstrAgentCode,
	const DString& dstrAsofDate,
	const BFDataGroupId& idDataGroup, 
   const DString& dstrTrack /*=I_("N")*/, 
   const DString& dstrPageName /*=NULL_STRING*/);

   void  getBrokerBranchAgentCode(DString& brokerCode,DString& branchCode,DString& agentCode   )
	{
		brokerCode = _brokerCode;
		branchCode = _branchCode;
		agentCode = _agentCode;	
	}

protected:

   virtual SEVERITY doCreateObject( const BFData& data, BFCBO*& pObjOut );

	virtual SEVERITY doCreateNewObject(BFCBO *&pBase, DString &strKey, 
	const BFDataGroupId& idDataGroup );


	virtual void  getStrKey(DString &strKey, const BFData *data);
	
private:

	DString _brokerCode;
   DString _branchCode;
	DString _agentCode;

};

//******************************************************************************
//              Revision Control Entries
//******************************************************************************
/* $Log:   Y:/VCS/BF iFAST/ifastcbo/BrokerRemarkList.hpp-arc  $
//
//   Rev 1.2   Nov 14 2004 14:29:32   purdyech
//PET910 - .NET Conversion
//
//   Rev 1.1   Sep 24 2004 14:01:48   YINGBAOL
//PET1145:FN01 Add getBrokerBranchAgentCode mothed
//
//   Rev 1.0   Sep 15 2004 10:57:48   YINGBAOL
//Initial revision.
 * 
 *   


  */
