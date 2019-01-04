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
//    Copyright 2002, By International Financial Data Service
//
//
//******************************************************************************
//
// ^FILE   : TradeVerification.hpp
// ^AUTHOR : Robbins Kuriakose
// ^DATE   : JuLY 22 2014
//
// ^CLASS    : TradeVerification
// ^SUBCLASS :
//
// ^CLASS DESCRIPTION :
//
//******************************************************************************

#include <ifastcbo\mfcancbo.hpp>

#undef IFASTCBO_LINKAGE
#ifdef IFASTCBO_DLL
   #define IFASTCBO_LINKAGE CLASS_EXPORT
#else
   #define IFASTCBO_LINKAGE CLASS_IMPORT
#endif

class TradeVerificationList;

class IFASTCBO_LINKAGE TradeVerification : public MFCanBFCbo, private boost::noncopyable
{
public:

   TradeVerification( BFAbstractCBO &parent );
   virtual ~TradeVerification();
   void  UserChangeVerifyDelete(const MFCanBFCbo* pCbo, const BFFieldId& idField,const BFDataGroupId& idDataGroup );
   SEVERITY setParameters(DString& dstrTransType,DString& dstrAccountNum, const BFDataGroupId& idDataGroup  );
   SEVERITY setParameters(const BFFieldId& idField, const DString& strValue, const BFDataGroupId& idDataGroup, bool lFormatted = false );
   SEVERITY setParameters(DString& dstrTransType, DString& dstrAccountNum, DString& dstrWireOrderNum, const BFDataGroupId& idDataGroup  );
   SEVERITY setAllTradesVerifyDeleteFlag(const BFFieldId& idField, const BFDataGroupId& idDataGroup );
   void setVerifyDeleteUpdated( const BFDataGroupId& idDataGroup, bool val = true );
   SEVERITY  init( const BFData& data );
   SEVERITY  init ( const BFDataGroupId &idDataGroup,
                    const DString &track, /*=I_("N")*/
                    const DString &pageName /*=NULL_STRING*/);
   void clearAllFlags( const BFDataGroupId& idDataGroup );
   virtual SEVERITY getTradeOverideRuleWarningsList( TradeOverideRuleWarningsList *&pTradeOverideRuleWarningsList, 
                                                     const DString& dstrTransNum, const BFDataGroupId& idDataGroup = BF::HOST , bool bCreate = true);      
   virtual SEVERITY setField( const BFFieldId &fieldId,
                              const DString& strValue,
                              const BFDataGroupId& idDataGroup, 
                              bool  lFormatted = true,
                              bool  lSideEffect = false,
                              bool  bCheckCurrentValue = true);
protected:

    SEVERITY doValidateField( const BFFieldId& idField, const DString& strValue, const BFDataGroupId& idDataGroup );
    SEVERITY doApplyRelatedChanges( const BFFieldId& idField, const BFDataGroupId& idDataGroup );
    void doInitWithDefaultValues( const BFDataGroupId& idDataGroup );
private:

   SEVERITY SearchRelatedChanges( const BFDataGroupId& idDataGroup );
   SEVERITY validateSearchType(DString dstrValue, const BFDataGroupId& idDataGroup);
   TradeVerification( const TradeVerification& copy ); //not implemented
   TradeVerification& operator= ( const TradeVerification& copy );//not implemented
   TradeOverideRuleWarningsList* _pTradeOverideRuleWarningsList;
   bool _bVerifyPerm ;
   bool _bDeletePerm;
};

//******************************************************************************
//              Revision Control Entries
//******************************************************************************
//
/* $Log:   Y:/VCS/BF iFAST/ifastbp/TradeVerificationProcess.cpp-arc  $
// 
//    Rev 1.0  22 July 2014
// Initial revision.
*/