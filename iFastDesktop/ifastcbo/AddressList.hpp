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
//    Copyright 1999 by DST Canada, Inc.
//
//
//******************************************************************************
//
// ^FILE   : AddressList.hpp
// ^AUTHOR :  Yingbao Li
// ^DATE   : 04/06/99
//
// ^CLASS    : AddressList
// ^SUBCLASS :
//
// ^CLASS DESCRIPTION :
//
//******************************************************************************

#include <ifastcbo\mfcancbo.hpp>
#include <boost\utility.hpp>

// Forward references
class MgmtCoOptions;
class Address;

#undef IFASTCBO_LINKAGE
#ifdef IFASTCBO_DLL
   #define IFASTCBO_LINKAGE CLASS_EXPORT
#else
   #define IFASTCBO_LINKAGE CLASS_IMPORT
#endif
class AccountMailingList;

class IFASTCBO_LINKAGE AddressList : public MFCanBFCbo, private boost::noncopyable
{
public:
   AddressList( BFAbstractCBO &parent );
   virtual ~AddressList( void );

   // Initialize function
   SEVERITY init (
         const DString& shrNum, 
         bool ignoreDataNotFound = true, 
         const DString& dstrTrack = I_("N"),
         const DString& dstrPageName = NULL_STRING );    
   SEVERITY  initNew (
         const DString& shrNum);
   SEVERITY init2 (
         const BFData& recData); 
   SEVERITY refreshDefaultAddress01 (
         const BFDataGroupId &idDataGroup);
   SEVERITY getAddress (
         Address *&pAddress,
         const DString &addressCode, 
         const DString &date,
         const BFDataGroupId &idDataGroup);
   bool IsValidateAddressCode (DString& strCode, const BFDataGroupId& idDataGroup, bool &_bValid );
   bool DoesAddressCodeExist( const DString& dstrAddrCode, const BFDataGroupId& idDataGroup );
   SEVERITY validateAddressCode( const DString& dstrAddrCode, const BFDataGroupId& idDataGroup,
                                 const DString& strDate = NULL_STRING );
   bool isAfterPopupTaxJurisUpdate();
   void setAfterPopupTaxJurisUpdate(bool bAfter);
protected:
   virtual bool canDeleteObject (
            const DString &strKey, 
            const BFDataGroupId &idDataGroup);
   virtual SEVERITY doValidateAll (
            const BFDataGroupId &idDataGroup, 
            long lValidateGroup);
   virtual SEVERITY doCreateNewObject (
            BFCBO*& pBase, 
            DString &strKey, 
            const BFDataGroupId &idDataGroup);
   virtual SEVERITY doApplyRelatedChanges (
            const BFFieldId &idField, 
            const BFDataGroupId &idDataGroup);

   virtual void getStrKey (
            DString &strKey, 
            const BFData *data); 
   bool findKanaData(DString dstrKanaAddrCode,const BFData& recData, int& iDataNo);
private:
   SEVERITY initAddress( const DString& dstrKey, const BFData& recData );
   bool isDataWanted(const DString& dstrKey,const BFData& recData, int& iNo );
   bool IsAddrCodeUsedByMailing(DString& strAddrCode, const BFDataGroupId& idDataGroup);
   SEVERITY validateAddrCodeDateRanges( const BFDataGroupId& idDataGroup, bool& bmodified );
   bool  IsNew(){return(_bNew);}
   AccountMailingList*  getAccountMailingList(const BFDataGroupId& idDataGroup);
   bool _bNew;
   DString _shareholderNum;
   bool    _bAfterPopupTaxJurisUpdate;
};

//******************************************************************************
//              Revision Control Entries
//******************************************************************************
/* $Log:   Y:/VCS/BF iFAST/ifastcbo/AddressList.hpp-arc  $
 * 
 *    Rev 1.22   Nov 14 2004 14:25:34   purdyech
 * PET910 - .NET Conversion
 * 
 *    Rev 1.21   May 25 2004 20:34:20   popescu
 * PTS 10026123, address 01, for nominee and intermediary accounts by tax type and reg address code
 * 
 *    Rev 1.20   May 25 2004 20:32:14   popescu
 * PTS 10026123, address 01, for nominee and intermediary accounts by tax type and reg address code
 * 
 *    Rev 1.19   May 20 2004 14:16:56   popescu
 * PTS 10026123, address 01, for nominee and intermediary accounts by tax type and reg address code
*/
