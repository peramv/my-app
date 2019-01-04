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
// ^FILE   : SettlementTradeList.hpp
// ^AUTHOR : Yingbao Li
// ^DATE   : May 24,2002
//
// ^CLASS    : SettlementTradeList
// ^SUBCLASS :
//
// ^CLASS DESCRIPTION :
//
//******************************************************************************

#include <ifastcbo\mfcancbo.hpp>
#include <ifastcbo\Settlement.hpp>

#undef IFASTCBO_LINKAGE
#ifdef IFASTCBO_DLL
   #define IFASTCBO_LINKAGE CLASS_EXPORT
#else
   #define IFASTCBO_LINKAGE CLASS_IMPORT
#endif


class IFASTCBO_LINKAGE SettlementTradeList : public MFCanBFCbo,public Noticement
{
public:
   SettlementTradeList( BFAbstractCBO &parent );
   virtual ~SettlementTradeList();

   SEVERITY init(const BFDataGroupId& idDataGroup,const DString& dstrSearchType,const bool bInd,
                 const DString& dstrTrack = I_("N"),
                 const DString& dstrPageName = NULL_STRING );
   SEVERITY reInit();
   SEVERITY getMore();

   SEVERITY setSetAllFields( const BFDataGroupId& idDataGroup,const DString& dstrValue,bool bFormat );
   virtual void  UserChangeSettle(const MFCanBFCbo* pCbo, const BFFieldId& idField,const BFDataGroupId& idDataGroup );

   BFData& getRequestData(){ return(_requestData);}
   bool settleMoreThenOne( const BFDataGroupId& idDataGroup,DString& dstrAccount );
   void clearUnsettleUpdatedFalg(const BFDataGroupId& idDataGroup);
   bool doYouHaveLegalToSettle(const BFDataGroupId& idDataGroup);

protected:

   virtual SEVERITY doCreateObject( const BFData& data, BFCBO*& pObjOut );
   virtual SEVERITY doValidateAll( const BFDataGroupId& idDataGroup, long lValidateGroup );

private:
   // copy constructor
   SettlementTradeList( const SettlementTradeList& copy ); //not implemented
   // = Operator
   SettlementTradeList& operator= ( const SettlementTradeList& copy );//not implemented   
   void prepareParameter(const BFDataGroupId& idDataGroup);

   BFData _requestData;
   bool    _bIndividual,_bInAll;
   DString _dstrSearchType;

};


//*****************************************************************************
// Revision Control Entries
//*****************************************************************************
//
// $Log:   Y:/VCS/BF iFAST/ifastcbo/SettlementTradeList.hpp-arc  $
//
//   Rev 1.14   May 12 2009 13:53:54   jankovii
//PET 159770 FN05 Auto Batching.
//
//   Rev 1.13   Nov 14 2004 14:54:24   purdyech
//PET910 - .NET Conversion
//
//   Rev 1.12   Oct 12 2004 14:24:14   YINGBAOL
//PTS10034502: Issue chritical error when user check "SettleAll" and all records selected is not allowed to settle.
//
//   Rev 1.11   Mar 21 2003 18:24:26   PURDYECH
//BFDataGroupId/BFContainerId changeover
//
//   Rev 1.10   Dec 11 2002 16:53:40   YINGBAOL
//fix individual Settlement
//
//   Rev 1.9   Oct 09 2002 23:55:00   PURDYECH
//PVCS Database Conversion
//
//   Rev 1.8   Aug 29 2002 12:53:38   SMITHDAV
//ClientLocale and typed field changes.
//
//   Rev 1.7   Jul 10 2002 16:24:28   YINGBAOL
//added  clearUnsettleUpdatedFalg method
//
//   Rev 1.6   Jul 05 2002 13:43:20   YINGBAOL
//add settlemore thanone function
//
//   Rev 1.5   Jun 20 2002 14:06:58   YINGBAOL
//add doValidateAll
//
//   Rev 1.4   Jun 13 2002 09:48:28   VASILEAD
//Added getRequestData to provide access to the search crieteria
//
//   Rev 1.3   Jun 11 2002 11:43:52   YINGBAOL
//more business rules added
//
//   Rev 1.2   Jun 06 2002 16:07:52   YINGBAOL
//save work
//



//