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
//    DATE   : 16/04/99
//
//
//    Copyright 1997 by DST Systems, Inc.
//
//******************************************************************************


#include <bfproc\AbstractProcess.hpp>
///#endif

// Forward references

// Import/Export resolution
#undef IFASTBP_LINKAGE
#ifdef IFASTBP_DLL
   #define IFASTBP_LINKAGE CLASS_EXPORT
#else
   #define IFASTBP_LINKAGE CLASS_IMPORT
#endif

class MFAccount;
class Shareholder;
class COANavig;

class IFASTBP_LINKAGE COAProcess : public AbstractProcess
{
// Construction
public:
   DString _inNASU;
   MFAccount         *  _pMFAccount;
   void cboSetParameter(const DString& elementName, const DString& value );
   MFAccount*            getMFAccount()          { return(_pMFAccount);}
   /**
    * Default constructor
    */
//CP20030319   COAProcess();
   COAProcess( GenericInterfaceContainer* pGIC, GenericInterface* pGIParent, const Command& rCommand );
   virtual ~COAProcess();
protected:
   /**
     * Provide class specific implementation for some fields.
     * An exception will be thrown if the field cannot be found.
     * @param rpGICaller - A reference pointer to the calling object.
     * @param idContainer - ID of container we are using.
     * @param idField - ID of field we are getting.
     * @param strValue - A string reference where value is returned.
     * @param bFormatted - Flag where true means get data formatted.
     */
   virtual void doGetField(
                          const GenericInterface *rpGICaller,
                          const BFContainerId& idContainer,
                          const BFFieldId& idField,
                          const BFDataGroupId& idDataGroup,
                          DString &strValueOut,
                          bool bFormatted
                          ) const;
   /**
     * Set up the list and get parameters.
     * @returns SEVERITY noting any error/warning conditions
     */
   virtual SEVERITY doInit();
   /**
     * Implementation to support the process method.
     * @returns an enum representing the return type
     */
   virtual E_COMMANDRETURN doProcess();
   /**
     * Implementation for the refresh method.  Not implemented yet.
     * @param rpGICaller - A reference pointer to the calling object.
     * @param szOriginalCommand - A string literal representing the original
     * command issuing the refresh (which may provide a hint on whether this
     * object needs to check for refresh).
     * @returns true if successful, call getErrors for errors if false
     */
   virtual bool doRefresh(
                         GenericInterface *rpGICaller,
                         const I_CHAR *szOriginalCommand
                         );
   /**
     * Provide class specific implementation for some fields.
     * An exception will be thrown if the field is not found.
     * @param rpGICaller - A reference pointer to the calling object.
     * @param idContainer - ID of container we are using.
     * @param idField - ID of field we are getting.
     * @param strValue - A string reference for the value of the field to be
     * set.
     * @param bFormatted - Flag where true means incoming data is formatted.
     * @returns SEVERITY indicating any errors/warnings encountered.
     */
   virtual SEVERITY doSetField(
                              const GenericInterface *rpGICaller,
                              const BFContainerId& idContainer,
                              const BFFieldId& idField,
                              const BFDataGroupId& idDataGroup,
                              const DString& strValue,
                              bool bFormatted
                              );
   SEVERITY performSearch(
                         GenericInterface *rpGI, 
                         const BFContainerId& idSearch, 
                         E_SEARCHACTION eSearchAction 
                         );
   virtual bool setCommitDataGroupAsHost();
private:
   SEVERITY reload( );
   
   DString getComboValue(const BFFieldId& idField, const DString& strCode = NULL_STRING ) const;

//	COANavig          *  _pCOANavig;
   DString              _ShareholderNum;
//	MFAccount         *  _pMFAccount;
   Shareholder       *  _pShareholder;
   GenericInterface  *  _rpChildGI;
   DString              _pTransId; 
   DString              _AccountNum;
	DString					_LaunchCOA;
};


//******************************************************************************
//              Revision Control Entries
//******************************************************************************
//
/* $Log:   Y:/VCS/BF iFAST/ifastbp/COAProcess.hpp-arc  $
 * 
 *    Rev 1.12   Jul 06 2005 10:57:16   ZHANGCEL
 * PET1141 - FN05 -- NSCC Broker enhancement
 * 
 *    Rev 1.11   Mar 21 2003 17:38:04   PURDYECH
 * BFDataGroupId/BFContainerId changeover
 * 
 *    Rev 1.10   Mar 14 2003 08:50:50   sanchez
 * Takeout   void loadTitleSubstitutions();
 * 
 *    Rev 1.9   Oct 09 2002 23:53:08   PURDYECH
 * PVCS Database Conversion
 * 
 *    Rev 1.8   Aug 29 2002 12:52:02   SMITHDAV
 * ClientLocale and typed field changes.
 * 
 *    Rev 1.7   22 May 2002 18:21:36   PURDYECH
 * BFData Implementation
 * 
 *    Rev 1.6   19 Mar 2002 13:15:26   PURDYECH
 * Use #pragma once as include guard
 * Remove compile time "including..." message
 * 
 *    Rev 1.5   14 May 2001 13:57:48   YINGZ
 * code sync up
 * 
 *    Rev 1.4   Feb 16 2001 15:29:32   YINGBAOL
 * put some hardcode strings into DD
 * 
 *    Rev 1.3   Sep 22 2000 14:58:56   ZHANGCEL
 * Bug fixed
 * 
 *    Rev 1.2   Aug 02 2000 15:31:38   BUZILA
 * "locale" changes
 * 
 *    Rev 1.1   Feb 15 2000 18:56:20   MCNABBGL
 * changed comment format
 * 
 *    Rev 1.0   Feb 15 2000 10:59:02   SMITHDAV
 * Initial revision.
 * 
 *    Rev 1.12   Jan 22 2000 15:18:58   BUZILA
 * fixes
 * 
 *    Rev 1.11   Dec 24 1999 15:37:02   BUZILA
 * we don't need anymore COAlist
 * 
 *    Rev 1.10   Dec 22 1999 18:01:48   BUZILA
 * changes due to COA flags movament
 * 
 *    Rev 1.9   Dec 08 1999 12:16:54   BUZILA
 * added idDataGroup parameter to doGetField and doSetField
 * 
 *    Rev 1.8   Nov 30 1999 18:24:54   POPESCUS
 * changes related to the NASU flow
 * 
 *    Rev 1.7   Nov 25 1999 15:12:54   BUZILA
 * fixes
 * 
 *    Rev 1.6   Nov 20 1999 19:39:18   BUZILA
 * fixes
 * 
 *    Rev 1.5   Oct 28 1999 18:04:24   DT24433
 * removed doOk/doCancel
 * 
 *    Rev 1.4   Aug 31 1999 10:25:24   DT24433
 * changed dogetfield/dosetfield parms
 * 
 *    Rev 1.3   Jul 27 1999 16:03:34   BUZILA
 * Increment M2
 * 
 *    Rev 1.2   Jul 26 1999 10:36:30   BUZILA
 * changed doGetField
 * 
 *    Rev 1.1   Jul 08 1999 10:03:36   SMITHDAV
 * Modify revision history commaent format to old
 * style comment -- I can't seem to get new style comments to work.
 *
 */
