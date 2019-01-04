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
//    Copyright 1999 by DST Systems, Inc.
//
//******************************************************************************


#include <bfproc\AbstractProcess.hpp>
#include <ifastbp\ifasthistoricalparameters.hpp>


// Import/Export resolution
#undef IFASTBP_LINKAGE
#ifdef IFASTBP_DLL
   #define IFASTBP_LINKAGE CLASS_EXPORT
#else
   #define IFASTBP_LINKAGE CLASS_IMPORT
#endif

/**
 * Class that manages the entity process.
 *
 * @author Yakov Prager
 * </dd></dl><p><dl><dt><b>Date Created:</b></dt><dd> 03/09/1999</dd></dl>
 * @version 0.1
 */

class IFASTBP_LINKAGE DemographicsProcess : public AbstractProcess, public IFastHistoricalParameters
{
// Construction
public:
   /**
    * Default constructor
    */
   DemographicsProcess(GenericInterfaceContainer* pGIC, 
      GenericInterface* pGIParent, const Command& rCommand);
   virtual ~DemographicsProcess();
protected:
   /**
      * Used to bring a modeless dialog (via parent process) to the top of the
      * window stack.
      * @param rpGICaller - A reference pointer to the calling object.
      * @returns true if successful, check conditions if false
      */
   virtual bool doModelessSetFocus(
                                  GenericInterface *rpGICaller
                                  );
   /**
      * Implementation to support the modelessChildComplete method.
      * modelessChildComplete is used by the GenericInterfaceContainer to tell
      * the parent that the modeless child has been destroyed.
      * @param cmd - A reference to a command representing the object that has
      * been destroyed.
      * @returns true if this modeless object should end as well, false if not
      * done yet.  When returning true, the calling modelessChildComplete method
      * will call GenericInterfaceContainer::modelessDestroySelf to delete and
      * remove this object from the container
      */
   virtual bool doModelessChildComplete(
                                       const Command &cmd
                                       );
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
   virtual SEVERITY doValidateAll ( BFAbstractCBO *rpWSD,
                                    const BFDataGroupId &idDataGroup);

   void *getPtrForContainer(const BFContainerId& idContainer,
      const BFDataGroupId& idDataGroup);

   virtual void doGetField(const GenericInterface *rpGICaller,
      const BFContainerId& idContainer, const BFFieldId& idField,
      const BFDataGroupId& idDataGroup, DString &strValueOut,
      bool bFormatted) const;

   SEVERITY doSetField( const GenericInterface *rpGICaller, 
                        const BFContainerId& idContainer,
                        const BFFieldId& idField, 
                        const BFDataGroupId& idDataGroup, 
                        const DString& strValueOut, 
                        bool bFormatted
                      );

   virtual bool doOk (GenericInterface* rpGICaller);

   virtual SEVERITY getHistoricalParameters(const BFContainerId& idContainer,
      BFFieldId &recordIdField, DString& tableId, DString& dstrKeys);
   SEVERITY getHistoricalParameters( const BFContainerId& idContainer, HISTORICAL_VECTOR &vectorInput );

private:
   GenericInterface *_rpChildGI;
   DString _strDemoTitle;
   DString _dstrShrNum;
   DString _dstrAcctNum;
   DString _dstrPrimaryShareholer;
   DString _dstrEntityId;
   DString _dstrNewShareholder;
   DString _dstrNewAccount;

   void getEntityName (const BFDataGroupId& idDataGroup, 
      DString& dstrAcctNum, DString &_dstrPrimaryShareholer);
};


//******************************************************************************
//              Revision Control Entries
//******************************************************************************
//
/* $Log:   Y:/VCS/BF iFAST/ifastbp/DemographicsProcess.hpp-arc  $
 * 
 *    Rev 1.18   Apr 24 2009 04:21:16   dchatcha
 * IN 1653090 - The KYC screen need to made mandatory in the NASU process.
 * 
 *    Rev 1.17   12 Nov 2008 17:09:44   popescu
 * Incident#  1476692 - fixed object required issue in shareholder
 * 
 *    Rev 1.16   Sep 16 2008 22:44:02   daechach
 * Restore rev. 1.14 , 
 * 
 *    Rev 1.15   Sep 15 2008 07:09:14   daechach
 * PET0128026 - KYC Phase 2 - Fix crashing after close Demographics screen.
 * 
 *    Rev 1.14   Sep 12 2008 06:55:42   daechach
 * PET0128026 - KYC Phase 2
 * 
 *    Rev 1.13   Mar 10 2004 11:31:12   HERNANDO
 * PET965 FN11 - Added getHistoricalParameters.
 * 
 *    Rev 1.12   Dec 31 2003 11:54:10   popescu
 * PTS 10025659, force a refresh of the Sahreholder object at host level if we have Demographics updates
 * 
 *    Rev 1.11   Aug 18 2003 16:09:02   HERNANDO
 * Added keys to getHistoricalParameters.
 * 
 *    Rev 1.10   Jul 31 2003 13:26:28   FENGYONG
 * Add Historical logic
 * 
 *    Rev 1.9   Jul 11 2003 16:10:54   FENGYONG
 * move KYC from sharholder to MFAccount
 * 
 *    Rev 1.8   Mar 21 2003 17:38:28   PURDYECH
 * BFDataGroupId/BFContainerId changeover
 * 
 *    Rev 1.7   Oct 09 2002 23:53:10   PURDYECH
 * PVCS Database Conversion
 * 
 *    Rev 1.6   Aug 29 2002 12:52:08   SMITHDAV
 * ClientLocale and typed field changes.
 * 
 *    Rev 1.5   22 May 2002 18:21:18   PURDYECH
 * BFData Implementation
 * 
 *    Rev 1.4   19 Mar 2002 13:15:32   PURDYECH
 * Use #pragma once as include guard
 * Remove compile time "including..." message
 * 
 *    Rev 1.3   Aug 02 2000 15:31:40   BUZILA
 * "locale" changes
 * 
 *    Rev 1.2   Jul 20 2000 16:53:40   HUANGSHA
 * Fixed the Crash problem lauched from NASU
 * 
 *    Rev 1.1   Feb 15 2000 18:56:24   MCNABBGL
 * changed comment format
 * 
 *    Rev 1.0   Feb 15 2000 10:59:04   SMITHDAV
 * Initial revision.
 * 
 *    Rev 1.6   Jan 19 2000 10:12:06   BUZILA
 * refresh stuf
 * 
 *    Rev 1.5   Dec 14 1999 17:37:58   DT24433
 * removed doOk/doCancel
 * 
 *    Rev 1.4   Nov 30 1999 12:21:54   ZHANGCEL
 * Delete doCancel() method
 * 
 *    Rev 1.3   Nov 11 1999 09:47:12   ZHANGCEL
 * implement for M2
 * 
 *    Rev 1.2   Oct 18 1999 11:40:02   BUZILA
 * Update transaction stuff
 * 
 *    Rev 1.1   Jul 08 1999 10:03:40   SMITHDAV
 * Modify revision history commaent format to old
 * style comment -- I can't seem to get new style comments to work.
 *
 */
