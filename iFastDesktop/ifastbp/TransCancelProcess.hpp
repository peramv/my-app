#pragma once



//******************************************************************************
//
// COPYRIGHT:
//
//    The computer systems, procedures, data bases and
//    programs created and maintained by International Financial Data Services,
//    are proprietary in nature and as such are confidential.
//    Any unauthorized use or disclosure of such information
//    may result in civil liabilities.
//
//    Copyright 1997 by International Financial Data Services
//
//******************************************************************************
//
// ^FILE   : TransCancelProcess.hpp
// ^AUTHOR : 
// ^DATE   : 02/15/2005
//
// ----------------------------------------------------------
//
// ^CLASS    : TransCancelProcess
//
// ^MEMBER VARIABLES :
//
// ^CODING COMMENTS  :  This is the code for the Transaction Details dialog
//
//******************************************************************************


#include <bfproc\AbstractProcess.hpp>
///#endif

// Forward references
class TransCancellist;
class TransCancel;
class BulkCancellist;
class BulkCancel;

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

class IFASTBP_LINKAGE TransCancelProcess : public AbstractProcess
{
// Construction
public:
   /**
    * Default constructor
    */
   TransCancelProcess( GenericInterfaceContainer* pGIC, GenericInterface* pGIParent, const Command& rCommand );
   virtual ~TransCancelProcess();
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

   virtual SEVERITY doSetField(
                              const GenericInterface *rpGICaller,
                              const BFContainerId& idContainer,
                              const BFFieldId& idField,
                              const BFDataGroupId& idDataGroup,
                              const DString& strValue,
                              bool bFormatted
                              );

   void * getPtrForContainer( const BFContainerId& idContainer, const BFDataGroupId& idDataGroup );   
   
   bool doOk(GenericInterface *rpGICaller);

   virtual bool doSend ( GenericInterface *rpGICaller, 
                         const I_CHAR *szMessage);

private:
   TransCancellist *_pTransCancellist;
   TransCancel     *_pTransCancel;
   BulkCancellist  *_pBulkCancellist;
   BulkCancel      *_pBulkCancel;
   GenericInterface *_rpChildGI;

   DString _TransNum,_FromScreen,accountNum_,cashDivPaidAfter_,transType_, _transId, _TransactionId, _SettleBatch;

   DString _dstrBulkCancel,
         _dstrTradeDate,
         _dstrFund,
         _dstrClass,
         _dstrTradeAdjustID,
         _dstrSWPSettleESGElig,
         _dstrTransSettleDate,
         _dstrRecptIssued,
         _dstrINDC,
         _grantExists,
         _trfResubmit,
         _isAGrantTrade;
};

///#endif 

//******************************************************************************
//              Revision Control Entries
//******************************************************************************
//
/* $Log:   Y:/VCS/BF iFAST/ifastbp/TransCancelProcess.hpp-arc  $
//
//   Rev 1.17   Apr 05 2011 06:58:42   kitticha
//PETP0181067_FN00_IN2460780_Empire Autobatch Development on Cancelled SP and DC trades.
//
//   Rev 1.16   Oct 29 2010 08:28:26   kitticha
//PET0165541 FN03 - QESI Phase3.
//
//   Rev 1.15   Jun 01 2010 23:25:48   dchatcha
//IN#2128812 - PETP0165541 FN 01 - Cancellation of processed transaction for RESP Accounts.
//
//   Rev 1.14   Apr 14 2010 23:57:02   popescu
//PET165541_FN01_QESI - RESP Gap_Dsk_Trading
//
//   Rev 1.13   Jul 17 2009 14:14:04   jankovii
//IN 1724320 - ESG19 - ICT - rebooked ICT trade reported as CON 69 instead of CON6
//
//   Rev 1.12   Dec 11 2007 15:47:54   wongsakw
//PET 2360 FN60 -- Automatically Cancel Contribution Reciept
//
//   Rev 1.11   Mar 10 2006 13:57:18   porteanm
//Incident 563764 - TradeDate/SettleDate validation support for a cancelled transaction.
//
//   Rev 1.10   Mar 02 2006 17:31:54   ZHANGCEL
//PET1334 - FN01 -- ESG Settlement enhancement
//
//   Rev 1.9   Dec 29 2005 13:14:10   porteanm
//Incident 501804 - Allow multiple Bulk Cancellation Instructions for the same Trade Date/Fund/Class.
//
//   Rev 1.8   Nov 11 2005 17:17:02   porteanm
//PET 1286 FN01 - Bulk Cancellation.
//
//   Rev 1.7   Nov 08 2005 18:39:28   porteanm
//PET1286 FN01 - Bulk Cancellation.
//
//   Rev 1.6   Jul 20 2005 14:02:24   Yingbaol
//PET1235,FN01:fix refresh issue
//
//   Rev 1.5   Jul 08 2005 09:38:30   Yingbaol
//PET1235,FN01:cancellation rebook
//
//   Rev 1.4   Apr 01 2005 13:45:36   Fengyong
//Remove doValidateAll fundction
//
//   Rev 1.3   Mar 16 2005 15:45:30   Fengyong
//PET1190 FN05 - change view 337 to repeatable
//
//   Rev 1.2   Mar 08 2005 19:42:24   Fengyong
//PET1190FN04 - Add DOOK
//
//   Rev 1.1   Mar 07 2005 14:06:30   Fengyong
//PET1190FN04 - Add AccountableCode rules
 */
