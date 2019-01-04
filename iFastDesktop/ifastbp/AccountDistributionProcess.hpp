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
//    Copyright 1997 by DST Systems, Inc.
//
//******************************************************************************
//
// ^FILE   : AccountDistributionProcess.hpp
// ^AUTHOR : Zijian Ying
// ^DATE   : 04/22/1999
//
// ----------------------------------------------------------
//
// ^CLASS    : AccountDistributionProcess
//
// ^MEMBER VARIABLES :
//
// ^CODING COMMENTS  :  This is the code for the Transaction Details dialog
//
//******************************************************************************


#include <bfproc\abstractprocess.hpp>
#include <ifastbp\ifasthistoricalparameters.hpp>

// Forward references
class AccountDistributionList;
class FundDetailList;
class ServerData;

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
 * @author 
 * </dd></dl><p><dl><dt><b>Date Created:</b></dt><dd> 03/04/1999</dd></dl>
 * @version 0.1
 */

class IFASTBP_LINKAGE AccountDistributionProcess : public AbstractProcess,
   public IFastHistoricalParameters

{
// Construction
public:
   /**
    * Default constructor
    */
//CP20030319   AccountDistributionProcess();
   AccountDistributionProcess( GenericInterfaceContainer* pGIC, GenericInterface* pGIParent, const Command& rCommand );
   virtual ~AccountDistributionProcess();
   virtual SEVERITY deleteItemFromList(
                                      const GenericInterface *rpGICaller,
                                      const BFContainerId& idList
                                      );
   ServerData* getServerData();

protected:
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
   virtual bool doModelessSetFocus(
                                  GenericInterface *rpGICaller
                                  );
   /**
     * Implementation to support the process method.
     * @returns an enum representing the return type
     */
   virtual E_COMMANDRETURN doProcess();
   virtual void* getPtrForContainer( const BFContainerId& idContainer, const BFDataGroupId& idDataGroup );
   virtual SEVERITY doValidateAll( BFAbstractCBO *rpWSD,  const BFDataGroupId& idDataGroup   );


   /*virtual SEVERITY doSetField(
       const GenericInterface *rpGICaller,
       const BFContainerId& idContainer,
       const BFFieldId& idField,
       const DString& strValue,
       bool bFormatted
       );*/

   SEVERITY getHistoricalParameters( const BFContainerId& idContainer, HISTORICAL_VECTOR &vectorInput );

   virtual SEVERITY performSearch( GenericInterface *rpGI, const BFContainerId& idSearch, 
                                   E_SEARCHACTION eSearchAction );

   virtual bool doMoreRecordsExist(GenericInterface *rpGICaller, const BFContainerId& idSearch );

private:
   DString _dstrFundCode, _dstrClassCode;
   DString _ListKey;
   DString _ShareholderNum;
   DString _EntityName;
   DString _dstrAccountNum;
   DString _dstrTaxType;
   DString _caller;


   AccountDistributionList *_pAccDistributionList;
   GenericInterface *_rpChildGI;
   ServerData *_pServerData;
};


//******************************************************************************
//              Revision Control Entries
//******************************************************************************
//
/* $Log:   Y:/VCS/BF iFAST/ifastbp/AccountDistributionProcess.hpp-arc  $
 * 
 *    Rev 1.19   Nov 25 2010 13:54:02   jankovii
 * PET175778FN01 - Upstreaming Phase 2
 * 
 *    Rev 1.18   23 Feb 2009 15:28:38   kovacsro
 * P0155543_FN01_ Account Level Distribution 
 * 
 *    Rev 1.15   Feb 26 2008 15:01:34   daechach
 * In# 1160207 - Desktop distribution - Added 'More' button to account distribution screen.
 * 
 *    Rev 1.14   Mar 10 2004 13:11:48   HERNANDO
 * PET965 FN11 - Changed getHistoricalParameters.
 * 
 *    Rev 1.13   Feb 28 2004 16:12:30   HERNANDO
 * PET965 FN11 - Additional historical enhancement.
 * 
 *    Rev 1.12   Mar 21 2003 17:34:16   PURDYECH
 * BFDataGroupId/BFContainerId changeover
 * 
 *    Rev 1.11   Oct 09 2002 23:52:56   PURDYECH
 * PVCS Database Conversion
 * 
 *    Rev 1.10   Aug 29 2002 12:51:26   SMITHDAV
 * ClientLocale and typed field changes.
 * 
 *    Rev 1.9   Jun 03 2002 16:55:10   HSUCHIN
 * bug fix to doValidateAll to use BFAbstractCBO rather than BFCBO
 * 
 *    Rev 1.8   22 May 2002 18:22:02   PURDYECH
 * BFData Implementation
 * 
 *    Rev 1.7   19 Mar 2002 13:14:44   PURDYECH
 * Use #pragma once as include guard
 * Remove compile time "including..." message
 * 
 *    Rev 1.6   15 Oct 2001 11:00:44   KOVACSRO
 * Added DString  _dstrTaxType;
 * 
 *    Rev 1.5   Nov 01 2000 10:04:36   VASILEAD
 * Added Purchase service
 * 
 *    Rev 1.4   Sep 11 2000 10:38:38   YINGBAOL
 * clean up and improve real time behavior
 * 
 *    Rev 1.3   Aug 02 2000 15:31:36   BUZILA
 * "locale" changes
 * 
 *    Rev 1.2   Mar 07 2000 16:23:34   HSUCHIN
 * added Fund Number for C2
 * 
 *    Rev 1.1   Feb 15 2000 18:56:10   MCNABBGL
 * changed comment format
 * 
 *    Rev 1.0   Feb 15 2000 10:58:54   SMITHDAV
 * Initial revision.
 * 
 *    Rev 1.14   Feb 02 2000 17:23:08   YINGZ
 * for Mihai
 * 
 *    Rev 1.13   Jan 25 2000 16:44:14   YINGZ
 * for release
 * 
 *    Rev 1.12   Jan 22 2000 18:42:18   YINGZ
 * bug fix
 * 
 *    Rev 1.11   Jan 20 2000 10:32:30   PRAGERYA
 * For Zijian
 * 
 *    Rev 1.10   Jan 18 2000 18:11:16   PRAGERYA
 * For release
 * 
 *    Rev 1.9   Jan 11 2000 18:02:24   PRAGERYA
 * Bugs fixed
 * 
 *    Rev 1.8   Jan 09 2000 16:42:08   PRAGERYA
 * Made compilable!
 * 
 *    Rev 1.7   Jan 07 2000 20:32:38   PRAGERYA
 * For Mihai
 * 
 *    Rev 1.6   Dec 30 1999 12:39:04   YINGBAOL
 * split list
 * 
 *    Rev 1.5   Nov 25 1999 12:02:58   YINGBAOL
 * check in for M2 release
 * 
 *    Rev 1.4   Nov 01 1999 16:00:08   DT24433
 * removed doOk/doCancel
 * 
 *    Rev 1.3   Oct 18 1999 11:40:00   BUZILA
 * Update transaction stuff
 * 
 *    Rev 1.2   Sep 23 1999 15:35:04   YINGZ
 * make it work for c1
 * 
 *    Rev 1.1   Jul 08 1999 10:03:24   SMITHDAV
 * Modify revision history commaent format to old
 * style comment -- I can't seem to get new style comments to work.
 *
 */
