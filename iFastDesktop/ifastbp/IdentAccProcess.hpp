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
//    AUTHOR : Mihai Virgil Buzila
//    DATE   : 03 Feb 2000
//
//
//    Copyright 2000 by DST Systems, Inc.
//
//******************************************************************************


#include <bfproc\AbstractProcess.hpp>
///#endif

//Forward declarations
class EntitySearchList;
class AccountEntityXref;

#undef IFASTBP_LINKAGE
#ifdef IFASTBP_DLL
   #define IFASTBP_LINKAGE CLASS_EXPORT
#else
   #define IFASTBP_LINKAGE CLASS_IMPORT
#endif

class IFASTBP_LINKAGE IdentAccProcess : public AbstractProcess
{
// Construction
public:
//CP20030319   IdentAccProcess();
   IdentAccProcess( GenericInterfaceContainer* pGIC, GenericInterface* pGIParent, const Command& rCommand );
   virtual ~IdentAccProcess();
protected:
   virtual void doGetField(
                          const GenericInterface *rpGICaller, 
                          const BFContainerId& idContainer, 
                          const BFFieldId& idField, 
                          const BFDataGroupId& idDataGroup, 
                          DString &strValueOut, 
                          bool bFormatted
                          ) const;
   virtual SEVERITY doSetField(
                              const GenericInterface *rpGICaller,
                              const BFContainerId& idContainer,
                              const BFFieldId& idField,
                              const BFDataGroupId& idDataGroup,
                              const DString& strValue,
                              bool bFormatted
                              );
   virtual SEVERITY doInit();
   virtual E_COMMANDRETURN doProcess();
   virtual void *getPtrForContainer( const BFContainerId& idContainer, const BFDataGroupId& idDataGroup );
   virtual const DString& getFirstListItemKey( const GenericInterface *rpGICaller, const BFContainerId& idList );
   virtual const DString& getNextListItemKey( const GenericInterface *rpGICaller, const BFContainerId& idList );
   virtual SEVERITY performSearch( GenericInterface *rpGI, const BFContainerId& idSearch, E_SEARCHACTION eSearchAction );
   bool doMoreRecordsExist( GenericInterface *rpGICaller, const BFContainerId& idSearch );
   void doPostOk( GenericInterface *rpGICaller, bool bSuccessFlag );
   bool doSend( GenericInterface * rpGICaller, const I_CHAR * szMessage );

private:
   EntitySearchList *_pEntitySearchList;
   AccountEntityXref *_pAccountEntityXref;
   DString _accountNum;
   DString _searchCode;
   DString _firstValue;
   DString _secondValue;
   DString  m_dstrsystematic;
   bool bGotAccount;
};

//******************************************************************************
//              Revision Control Entries
//******************************************************************************
//
/* $Log:   Y:/VCS/BF iFAST/ifastbp/IdentAccProcess.hpp-arc  $
 * 
 *    Rev 1.13   Mar 21 2003 17:41:50   PURDYECH
 * BFDataGroupId/BFContainerId changeover
 * 
 *    Rev 1.12   Oct 09 2002 23:53:20   PURDYECH
 * PVCS Database Conversion
 * 
 *    Rev 1.11   Aug 29 2002 12:52:44   SMITHDAV
 * ClientLocale and typed field changes.
 * 
 *    Rev 1.10   22 May 2002 18:20:40   PURDYECH
 * BFData Implementation
 * 
 *    Rev 1.9   19 Mar 2002 13:17:34   PURDYECH
 * Use #pragma once as include guard
 * Remove compile time "including..." message
 * 
 *    Rev 1.8   17 Jan 2002 10:50:14   KOVACSRO
 * Added a private member var.
 * 
 *    Rev 1.7   Aug 10 2001 14:07:48   YINGBAOL
 * disable NASU if it is lauched from Systematic and Allocation
 * 
 *    Rev 1.6   Oct 11 2000 14:17:34   KOVACSRO
 * Added doSend().
 * 
 *    Rev 1.5   Aug 02 2000 15:31:46   BUZILA
 * "locale" changes
 * 
 *    Rev 1.4   Mar 07 2000 15:45:02   POPESCUS
 * more work on the account search screen
 * 
 *    Rev 1.3   Mar 03 2000 19:33:58   POPESCUS
 * save the work
 * 
 *    Rev 1.2   Mar 03 2000 12:11:08   POPESCUS
 * account search work
 * 
 *    Rev 1.1   Feb 29 2000 15:37:00   BUZILA
 * changes
// 
*/
