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
// ^FILE   : Settlement.hpp
// ^AUTHOR : Yingbao Li
// ^DATE   : May 24,2002
//
// ^CLASS    : Settlement
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

class SettlementTotalList;
class SettlementTradeList;
class BatchInfoList;


//Abstract class to handle Noticement
class Noticement
{

public:  
   Noticement(){}
   ~Noticement(){}
   virtual void  UserChangeSettle(const MFCanBFCbo* pCbo, const BFFieldId& idField,const BFDataGroupId& idDataGroup ){};
};


class IFASTCBO_LINKAGE Settlement : public MFCanBFCbo
{
public:
   Settlement( BFAbstractCBO &parent );
   virtual ~Settlement();

   SEVERITY init( const BFDataGroupId& idDataGroup, 
      const DString& dstrTrack = I_("N"), 
      const DString& dstrPageName = NULL_STRING);
   SEVERITY reInit();
   SEVERITY getSettlementTotalList( SettlementTotalList*& pSettlementTotalList,const BFDataGroupId& idDataGroup,bool bInq = true,bool bRemObj = true );
   SEVERITY getSettlementTradeList( SettlementTradeList*& pSettlementTradeList, const BFDataGroupId& idDataGroup, bool bInq = true, bool bRemObj = true );

   void  UserChangeSettle(const MFCanBFCbo* pCbo, const BFFieldId& idField,const BFDataGroupId& idDataGroup );
   SEVERITY setParameters(DString& dstrTransType,DString& dstrAccountNum, const BFDataGroupId& idDataGroup  );
   SEVERITY setParameters(const BFFieldId& idField, const DString& strValue, const BFDataGroupId& idDataGroup, bool lFormatted = false );
   SEVERITY setParameters(DString& dstrTransType,
						  DString& dstrAccountNum, 
						  DString& dstrWireOrderNum,
						  const BFDataGroupId& idDataGroup  );

   bool hasPermissionForSearchType(const DString& dstrSearchType,bool bInq = false);
protected:

   virtual SEVERITY doValidateField( const BFFieldId& idField, const DString& strValue, const BFDataGroupId& idDataGroup );
   //virtual SEVERITY doValidateAll( const BFDataGroupId& idDataGroup, long lValidateGroup );
   virtual SEVERITY doApplyRelatedChanges( const BFFieldId& idField, const BFDataGroupId& idDataGroup );
   virtual SEVERITY setField( const BFFieldId& idField,
                              const DString& strValue,
                              const BFDataGroupId& idDataGroup, 
                              bool  lFormatted = true,
                              bool  lSideEffect = false,
                              bool  bCheckCurrentValue = true);

private:
   void buildKey( DString &strKey,const BFDataGroupId& idDataGroup, unsigned int uiListType );
   void setFieldsAsRequired( const BFFieldId idField[], const BFDataGroupId& idDataGroup,bool bReqired );
   void setFieldsAsReadOnly(  const BFDataGroupId& idDataGroup,bool bReadOnly );  
   void setFieldsAsUpdated(  const BFDataGroupId& idDataGroup,bool bUpdate );
   SEVERITY validateStartEndDate(const BFDataGroupId& idDataGroup );
   SEVERITY validateStartDate(const DString& strDate,  const BFDataGroupId& idDataGroup );

   void noticeMe(Noticement* noteObj );
   SEVERITY SearchRelatedChanges( const BFDataGroupId& idDataGroup );
   SEVERITY BrokerCodeRelatedChanges( const BFDataGroupId& idDataGroup );

   SEVERITY validateFundCodeCurrency( const BFDataGroupId& idDataGroup  );
   SEVERITY validateBrokerCode( const DString& dstrValue,  const BFDataGroupId& idDataGroup  );
   SEVERITY validateFundCode(const DString& dstrFundCode,const BFDataGroupId& idDataGroup);
   SEVERITY validateSearchType(DString dstrValue, const BFDataGroupId& idDataGroup);
   SEVERITY initBatchList(const BFDataGroupId& idDataGroup);
   SEVERITY validateSettleDate(const DString& dstrSettleDate,const BFDataGroupId& idDataGroup);

   // copy constructor
   Settlement( const Settlement& copy ); //not implemented
   // = Operator
   Settlement& operator= ( const Settlement& copy );//not implemented
   typedef std::vector<Noticement *>                                  NOTICEMENT;        
   NOTICEMENT   _vecNotice;

   BatchInfoList *pBatchInfoList;

};

//*****************************************************************************
//              Revision Control Entries
//*****************************************************************************
//
// $Log:   Y:/VCS/BF iFAST/ifastcbo/Settlement.hpp-arc  $
//
//   Rev 1.18   Dec 09 2010 15:08:48   jankovii
//IN 2339013 - P0175778: Uptreaming QA testing
//
//   Rev 1.17   Dec 01 2010 06:12:28   dchatcha
//P0175716 FN02 - Client Name Redemption - EPA Auto Settlement.
//
//   Rev 1.16   May 12 2009 13:52:52   jankovii
//PET 159770 FN05 Auto Batching.
//
//   Rev 1.15   Nov 14 2004 14:54:00   purdyech
//PET910 - .NET Conversion
//
//   Rev 1.14   May 27 2003 18:29:54   popescu
//due to several memory leaks found in some list getters at the DSTCWorkSession level caused by copy/paste, I've created a common template function to retrieve the dependent objects
//
//   Rev 1.13   Apr 07 2003 15:12:26   FENGYONG
//Add setParameters fundcion
//
//   Rev 1.12   Mar 21 2003 18:23:54   PURDYECH
//BFDataGroupId/BFContainerId changeover
//
//   Rev 1.11   Oct 09 2002 23:54:58   PURDYECH
//PVCS Database Conversion
//
//   Rev 1.10   Aug 29 2002 12:53:36   SMITHDAV
//ClientLocale and typed field changes.
//
//   Rev 1.9   Aug 16 2002 13:53:30   YINGBAOL
//add permission check
//
//   Rev 1.8   Jul 05 2002 13:42:14   YINGBAOL
//add validate fundCode
//
//   Rev 1.7   Jun 27 2002 13:30:22   YINGBAOL
//add  validateStartEndDate and validateStartDate method
//
//   Rev 1.6   Jun 20 2002 14:06:46   YINGBAOL
//add setFieldsAsUpdated
//
//   Rev 1.5   Jun 18 2002 12:29:30   YINGBAOL
//code clean up
//
//   Rev 1.4   Jun 14 2002 14:41:34   YINGBAOL
//add doSearchTypeRelatedChanges
//
//   Rev 1.3   Jun 13 2002 15:52:38   YINGBAOL
//change view 200 
//
//   Rev 1.2   Jun 11 2002 11:43:48   YINGBAOL
//more business rules added
//
//   Rev 1.1   Jun 06 2002 16:07:42   YINGBAOL
//save work
//



//
