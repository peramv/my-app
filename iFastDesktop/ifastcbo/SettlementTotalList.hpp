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
// ^FILE   : SettlementTotalList.hpp
// ^AUTHOR : Yingbao Li
// ^DATE   : May 24,2002
//
// ^CLASS    : SettlementTotalList
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


class IFASTCBO_LINKAGE SettlementTotalList : public MFCanBFCbo, public Noticement
{
public:
   SettlementTotalList( BFAbstractCBO &parent );
   virtual ~SettlementTotalList();

   SEVERITY   init( const BFDataGroupId& idDataGroup,
                    const DString& dstrTrack = I_("N"),
                    const DString& dstrPageName = NULL_STRING );
   SEVERITY reInit();
   virtual void  UserChangeSettle(const MFCanBFCbo* pCbo, const BFFieldId& idField, const BFDataGroupId& idDataGroup );
   DString  getCountNum(bool bSettle,const BFDataGroupId& idDataGroup );



protected:
   virtual void getStrKey( DString &strKey, const BFData *data = NULL );
   virtual SEVERITY doCreateObject( const BFData& data, BFCBO*& pObjOut );

private:

   void prepareParameter(BFData& requestData,const BFDataGroupId& idDataGroup);  
   // copy constructor
   SettlementTotalList( const SettlementTotalList& copy ); //not implemented
   // = Operator
   SettlementTotalList& operator= ( const SettlementTotalList& copy );//not implemented


};


//*****************************************************************************
// Revision Control Entries
//*****************************************************************************
//
// $Log:   Y:/VCS/BF iFAST/ifastcbo/SettlementTotalList.hpp-arc  $
//
//   Rev 1.8   Nov 14 2004 14:54:10   purdyech
//PET910 - .NET Conversion
//
//   Rev 1.7   Mar 21 2003 18:24:06   PURDYECH
//BFDataGroupId/BFContainerId changeover
//
//   Rev 1.6   Oct 09 2002 23:54:58   PURDYECH
//PVCS Database Conversion
//
//   Rev 1.5   Aug 29 2002 12:53:38   SMITHDAV
//ClientLocale and typed field changes.
//
//   Rev 1.4   Jun 12 2002 17:04:50   YINGBAOL
//add getCountNum
//
//   Rev 1.3   Jun 11 2002 11:43:50   YINGBAOL
//more business rules added
//
//   Rev 1.2   Jun 06 2002 16:07:50   YINGBAOL
//save work
//



//