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
// ^FILE   : FeeParamSysSearchCriteria.hpp
// ^AUTHOR : Yingbao li
// ^DATE   : Jan. 08,  2003
//
// ^CLASS    : FeeParamSysSearchCriteria
// ^SUBCLASS :
//
// ^CLASS DESCRIPTION :
//
//******************************************************************************



#include <ifastcbo\mfcancbo.hpp>
#include <boost\utility.hpp>
///#endif

#include "FundClassRules.hpp"
class FeeParamSysList;
#undef IFASTCBO_LINKAGE
#ifdef IFASTCBO_DLL
   #define IFASTCBO_LINKAGE CLASS_EXPORT
#else
   #define IFASTCBO_LINKAGE CLASS_IMPORT
#endif

class IFASTCBO_LINKAGE FeeParamSysSearchCriteria : public MFCanBFCbo, private boost::noncopyable
{
public:
   //TODO: enter specific field enumerations
   FeeParamSysSearchCriteria( BFAbstractCBO &parent );
   virtual ~FeeParamSysSearchCriteria();
   SEVERITY init( const BFDataGroupId& idDataGroup,
      const DString& dstrTrack = I_("N"), 
      const DString& dstrPageName = NULL_STRING);
   void clearUpdateFlags(const BFDataGroupId& idDataGroup);
	SEVERITY GetFeeParamSysList();
	SEVERITY GetFeeParamSysList(FeeParamSysList*& pFeeParamSysList, const BFDataGroupId& idDataGroup,
										bool bInq = true ,bool bRemObj = true,bool nbCreateNew = false,bool bDel = false );
   virtual bool hasNonHostUpdates( ) const {return false;};
   virtual bool hasHostUpdates( bool inclSubObj = true ) {return false;};

protected:
	virtual SEVERITY doValidateFields( const BFFieldId& idField, const DString& strValue, const BFDataGroupId& idDataGroup);
   virtual SEVERITY doApplyRelatedChanges( const BFFieldId& idField, const BFDataGroupId& idDataGroup );

private:
	SEVERITY validateBrokerCode(const BFDataGroupId& idDataGroup);
	SEVERITY validateBranchCode(const BFDataGroupId& idDataGroup);
	SEVERITY validateSalesRepCode(const BFDataGroupId& idDataGroup);

    void SearchTypeRelatedChanges(const BFDataGroupId& idDataGroup );
	void setFieldsAsRequired( const BFFieldId idField[], const BFDataGroupId& idDataGroup,bool bReqired );
	void clearFieldsValue( const BFFieldId idField[], const BFDataGroupId& idDataGroup);
	bool slsRepByBranch ( const BFDataGroupId& idDataGroup );
	void doBrokerCodeRelatedChanges(const BFDataGroupId& idDataGroup);
   void doFeeCodeRelatedChanges(const BFDataGroupId& idDataGroup);



private:  // private member
	FundClassRules m_FundClassRules;
	DString _salesRepByBranch;

};
/******************************************************************************
//              Revision Control Entries
//******************************************************************************
//
/* $Log:   Y:/VCS/BF iFAST/ifastcbo/FeeParamSysSearchCriteria.hpp-arc  $
//
//   Rev 1.9   Nov 14 2004 14:40:28   purdyech
//PET910 - .NET Conversion
//
//   Rev 1.8   May 27 2003 18:29:40   popescu
//due to several memory leaks found in some list getters at the DSTCWorkSession level caused by copy/paste, I've created a common template function to retrieve the dependent objects
//
//   Rev 1.7   May 02 2003 15:03:50   linmay
//added logic for new search option: BranchCode, and SalesRepCode
//
//   Rev 1.6   Mar 25 2003 14:46:40   linmay
//modified getfeeparamsyslist()
//
//   Rev 1.5   Mar 21 2003 18:09:48   PURDYECH
//BFDataGroupId/BFContainerId changeover
//
//   Rev 1.4   Jan 21 2003 11:16:24   YINGBAOL
//sync. FundClassRules change
//
//   Rev 1.2   Jan 16 2003 15:33:38   YINGBAOL
//add classfieldinfo etc. 
//
//   Rev 1.1   Jan 09 2003 15:44:52   YINGBAOL
//change pointer to instance
//
//   Rev 1.0   Jan 09 2003 10:06:32   YINGBAOL
//Initial Revision
//
/
 * 
 
*/
///#endif
