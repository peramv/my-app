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
// ^FILE   : AccountMailingList.hpp
// ^AUTHOR :  Yingbao Li
// ^DATE   : 11/16/99
//
// ^CLASS    : AccountMailingList
// ^SUBCLASS :
//
// ^CLASS DESCRIPTION :
//
//******************************************************************************

#include <ifastcbo\mfcancbo.hpp>
#include <boost\utility.hpp>

// Forward references
class Shareholder;
class AddressList;
class MgmtCoOptions; 
class AccountMailingInfo;

#undef IFASTCBO_LINKAGE
#ifdef IFASTCBO_DLL
   #define IFASTCBO_LINKAGE CLASS_EXPORT
#else
   #define IFASTCBO_LINKAGE CLASS_IMPORT
#endif

class IFASTCBO_LINKAGE AccountMailingList : public MFCanBFCbo, private boost::noncopyable
{
public:
   static void buildKey(DString &strKeyOut, const DString& AccountNum);
   // X-structors
   AccountMailingList(BFAbstractCBO &parent);
   virtual ~AccountMailingList();
   // Initialize functions
   //used to initialize from the shareholder object, when shareholder is new,
   SEVERITY initNew(const DString& shrNum, const BFDataGroupId& idDataGroup = BF::HOST);
   //calls the back-end
   SEVERITY init(const DString& shrNum, 
      const DString& dstrTrack = I_("N"), const DString& dstrPageName = NULL_STRING);
   //
   void setNewAccountNumber(const DString& strAccount);
   bool IsAddrCodeUsedByMailing(DString &strAddrCode, const BFDataGroupId& idDataGroup);
//******************************************************************************
//Methods which returns the private variable _strAccountNum set by the function
//setNewAccountNumber.
//@param - none.
//@returns - DString - Account Number.
//******************************************************************************
   DString getAccountNum () { return(_strAccountNum);};
protected:
   virtual SEVERITY doCreateObject( const BFData& data, BFCBO*& pObjOut );
   virtual SEVERITY doCreateNewObject( BFCBO*& pBase, DString &strKey, const BFDataGroupId& idDataGroup );
   virtual void doCommitDataGroup( const BFDataGroupId& idDataGroup );
   virtual void getStrKey( DString &strKey, const BFData *data );
   virtual void getStrKeyForNewItem( DString &strKey );
   virtual SEVERITY doValidateAll( const BFDataGroupId& idDataGroup, long lValidateGroup );
private:
   //validation helpers
   bool IsMailingTypeSameAsCode( AccountMailingInfo* pMailInfo, DString &strCode, const BFFieldId& mailType, const BFDataGroupId& idDataGroup );
   SEVERITY validateMailingCode( BFCBO* pBase, const BFFieldId& idField, const BFDataGroupId& idDataGroup );
   bool IsAddressCodeExist(DString& strCode, const BFDataGroupId& idDataGroup);

   DString _dstrKey;
   DString _strAccountNum;
   DString _shrNum;
   std::vector<DString> vecAddr;
};

//******************************************************************************
//              Revision Control Entries
//******************************************************************************
//
/* $Log:   Y:/VCS/BF iFAST/ifastcbo/AccountMailingList.hpp-arc  $
 * 
 *    Rev 1.10   May 22 2003 14:11:48   popescu
 * Replaced name 'BankInstr' with 'BankInstructions'; 
 * simplified child lists getters for the Shareholder object
 * 
 *    Rev 1.9   Mar 21 2003 17:55:02   PURDYECH
 * BFDataGroupId/BFContainerId changeover
 * 
 *    Rev 1.8   Oct 09 2002 23:53:54   PURDYECH
 * PVCS Database Conversion
 * 
 *    Rev 1.7   Aug 29 2002 12:51:30   SMITHDAV
 * ClientLocale and typed field changes.
 * 
 *    Rev 1.6   Jul 17 2002 10:31:22   HSUCHIN
 * added function to get Account Number and beautfied source
 * 
 *    Rev 1.5   22 May 2002 18:22:06   PURDYECH
 * BFData Implementation
 * 
 *    Rev 1.4   19 Mar 2002 13:14:50   PURDYECH
 * Use #pragma once as include guard
 * Remove compile time "including..." message
 * 
 *    Rev 1.3   03 May 2001 14:03:40   SMITHDAV
 * Session management restructuring.
 * 
 *    Rev 1.2   Jan 18 2001 16:11:28   YINGBAOL
 * add etrack
 * 
 *    Rev 1.1   Feb 15 2000 18:56:10   MCNABBGL
 * changed comment format
 * 
 *    Rev 1.0   Feb 15 2000 10:58:54   SMITHDAV
 * Initial revision.
// 
//    Rev 1.14   Feb 01 2000 14:36:14   BUZILA
// added lValidateGroup parameter to doValidateAll method
// 
//    Rev 1.13   Jan 23 2000 16:59:30   POPESCUS
// fixes related to accessing the lists and rolling back a cloned account
// 
//    Rev 1.12   Jan 21 2000 16:44:00   YINGBAOL
// change the way access other list
// 
//    Rev 1.11   Jan 21 2000 11:11:38   POPESCUS
// the user can change the account number and the shareholder number
// 
//    Rev 1.10   Jan 14 2000 15:09:40   YINGBAOL
// modify validation
// 
//    Rev 1.9   Jan 10 2000 13:59:26   POPESCUS
// fixes for NASU
// 
//    Rev 1.8   Jan 07 2000 17:03:20   YINGBAOL
// modify validation
// 
//    Rev 1.7   Jan 06 2000 13:37:50   YINGBAOL
// change
// 
//    Rev 1.6   Dec 30 1999 10:35:18   YINGBAOL
// more validate added
// 
//    Rev 1.5   Dec 21 1999 10:14:48   YINGBAOL
// No change.
// 
//    Rev 1.4   Dec 17 1999 18:00:06   YINGBAOL
// add validation
// 
//    Rev 1.3   Dec 10 1999 18:37:06   BUZILA
// changed #ifdef LISTBASE_HPP => BFBASE_HPP
// 
//    Rev 1.2   Dec 08 1999 09:50:16   YINGBAOL
// fix Nasu bug
*/

