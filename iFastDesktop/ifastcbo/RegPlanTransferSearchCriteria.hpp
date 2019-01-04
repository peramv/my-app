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
//    Copyright 2003 by DST Systems, Inc.
//
//
//******************************************************************************
//
// ^FILE   : RegPlanTransferSearchCriteria.hpp
// ^AUTHOR : Mihai Buzila
// ^DATE   : November 4, 2016
//
// ^CLASS    : RegPlanTransferSearchCriteria
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


namespace REG_TRANSF_SEARCH_CRITERIA
{
  extern IFASTCBO_LINKAGE I_CHAR* const ACCOUNT_NUM;
}

class RegPlanTransferList;
class Broker;

class IFASTCBO_LINKAGE RegPlanTransferSearchCriteria : public MFCanBFCbo, private boost::noncopyable
{
public:
   RegPlanTransferSearchCriteria( BFAbstractCBO &parent );
   virtual ~RegPlanTransferSearchCriteria();
   SEVERITY init( const BFDataGroupId& idDataGroup, const DString& dstrTrack = I_("N"), const DString& dstrPageName = NULL_STRING);
   void clearUpdateFlags(const BFDataGroupId& idDataGroup);
   SEVERITY getRegPlanTransferList( RegPlanTransferList *&pRegPlanTransferList, const BFDataGroupId& idDataGroup);
   void doReset ( const BFDataGroupId& idDataGroup );
   SEVERITY validateExternalInst(const DString& strValue, const BFDataGroupId& idDataGroup );
protected:
   virtual SEVERITY doApplyRelatedChanges( const BFFieldId& idField, const BFDataGroupId& idDataGroup );
   bool slsRepByBranch ( const BFDataGroupId& idDataGroup );
   virtual SEVERITY doValidateField( const BFFieldId& idField, const DString& strValue, const BFDataGroupId& idDataGroup );
   SEVERITY checkBroker( const DString& brokerCode, const BFDataGroupId& idDataGroup, bool condition_returned );
   SEVERITY checkBranches( const DString& branchCode, const BFDataGroupId& idDataGroup, bool condition_returned );
   SEVERITY checkAgents( const DString& slsrepCode, const BFDataGroupId& idDataGroup, bool condition_returned, bool& bNewAgent );
   void parseName (const DString &originalName, DString &newName);
   SEVERITY getBroker ( Broker *&pBroker, const DString& dstrBrokerCode, const BFDataGroupId &idDataGroup );

private:
   void SearchTypeRelatedChanges(const BFDataGroupId& idDataGroup );
   void setFieldsAsRequired( const BFFieldId idField[], const BFDataGroupId& idDataGroup,bool bReqired );
   void clearFieldValues( const BFFieldId idField[], const BFDataGroupId& idDataGroup);
   void getAMSTypeList(DString &dstrAMSTypeList);

   DString _salesRepByBranch;
   DString _brokerName;
   DString _branchName;
   DString _branchCode;
   DString _agentName;
   DString _agentAltName;
};
