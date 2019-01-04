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
// ^FILE   : DilutionProcess.hpp
// ^AUTHOR : 
// ^DATE   : 02/15/2005
//
// ----------------------------------------------------------
//
// ^CLASS    : DilutionProcess
//
// ^MEMBER VARIABLES :
//
// ^CODING COMMENTS  :  This is the code for the Transaction Details dialog
//
//******************************************************************************


#include <bfproc\AbstractProcess.hpp>
#include <ifastbp\ifasthistoricalparameters.hpp>
///#endif

// Forward references
class DilutionAllocList;
class TransCancel;
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

class IFASTBP_LINKAGE DilutionProcess : public AbstractProcess, public IFastHistoricalParameters
{
// Construction
public:
   /**
    * Default constructor
    */
   DilutionProcess( GenericInterfaceContainer* pGIC, GenericInterface* pGIParent, const Command& rCommand );
   virtual ~DilutionProcess();
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
	virtual SEVERITY doSetField (const GenericInterface *rpGICaller, 
                                 const BFContainerId &idContainer, 
                                 const BFFieldId &idField, 
                                 const BFDataGroupId &idDataGroup, 
                                 const DString &strValue, 
                                 bool bFormatted);

	virtual void doGetField (const GenericInterface *rpGICaller,  
                             const BFContainerId &idContainer, 
                             const BFFieldId &idField, 
                             const BFDataGroupId &idDataGroup, 
                             DString &strValueOut, 
                             bool bFormtted) const;

	
	virtual const BFProperties *doGetFieldAttributes (const GenericInterface *rpGICaller, 
                                                      const BFContainerId &idContainer, 
                                                      const BFFieldId &idField, 
                                                      const BFDataGroupId &idDataGroup);
    virtual SEVERITY doGetErrors ( const GenericInterface *rpGICaller,
                                  const BFContainerId &idContainer,
                                  const BFFieldId &idField,
                                  const BFDataGroupId &idDataGroup,
                                  CONDITIONVECTOR &conditions) const;
    virtual bool doRegisterObserver ( const GenericInterface *rpGICaller,
                                     const BFContainerId &idContainer,
                                     const BFFieldId &idField,
                                     const BFDataGroupId &idDataGroup,
                                     BFObserver &rpObserver);
	

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

   virtual bool doModelessChildComplete( const Command &cmd );
   virtual bool doModelessSetFocus( GenericInterface *rpGICaller );

   void * getPtrForContainer( const BFContainerId& idContainer, const BFDataGroupId& idDataGroup );   
   virtual bool doOk(GenericInterface *rpGICaller);
   virtual void doPostOk( GenericInterface *rpGICaller, bool bSuccessFlag );
   virtual SEVERITY doValidateAll( BFAbstractCBO *rpWSD, const BFDataGroupId& idDataGroup ); 

   virtual SEVERITY getHistoricalParameters ( const BFContainerId &idContainer,
                                              BFFieldId &recordIdField, 
                                              DString &tableId, 
                                              DString &dstrKeys);

   virtual SEVERITY getHistoricalParameters( const BFContainerId& idContainer, 
                                             HISTORICAL_VECTOR &vectorInput );

private:     
   TransCancel *_pTransCancel;
   BulkCancel  *_pBulkCancel;
   DilutionAllocList *_pDilutionList;

   GenericInterface *_rpChildGI;

   DString _TransNum,
	       _FromScreen, 
		   _TransId, 
		   _ListKey; 

   DString _dstrBulkCancel,
	       _dstrTradeDate,
		   _dstrFund,
		   _dstrClass,
		   _dstrAllowModify,
		   _dstrTransTradeDate,
		   _dstrTransSettleDate,
		   _dstrTransType;
};

///#endif 
//******************************************************************************
//              Revision Control Entries
//******************************************************************************
//
/* $Log:   Y:/VCS/BF iFAST/ifastbp/DilutionProcess.hpp-arc  $
//
//   Rev 1.11   May 11 2012 15:19:26   wp040027
//PETP0187485-CPF-Dilution
//
//   Rev 1.10   Aug 30 2007 15:16:56   jankovii
//PET 2360 FN11 - Dilution.
//
//   Rev 1.9   Mar 10 2006 13:59:22   porteanm
//Incident 563764 - TradeDate/SettleDate validation support for a cancelled transaction.
//
//   Rev 1.8   Jan 09 2006 17:03:16   porteanm
//Incident 424704 - gap - TranshistDilutionAlloc update support.
//
//   Rev 1.7   Dec 18 2005 14:50:06   porteanm
//Incident 421704 - gap - TranshistDilutionAlloc update support.
//
//   Rev 1.6   Dec 14 2005 11:11:22   porteanm
//Incident 421704 - gap - TranshistDilutionAlloc update support.
//
//   Rev 1.5   Nov 13 2005 15:57:08   porteanm
//PET 1286 FN01 - Bulk Cancellation.
//
//   Rev 1.4   Oct 18 2005 14:18:54   AGUILAAM
//IN 432022 - allow single dilution record (100%); validateall on dilution only
//
//   Rev 1.3   Jul 07 2005 12:17:32   AGUILAAM
//PET1235 : dilution, part of Rebook/Cancellation
//
//   Rev 1.2   Mar 16 2005 15:46:38   Fengyong
//PET1190 FN05 - change view 337 to repeatable
//
//   Rev 1.1   Mar 07 2005 14:29:14   Fengyong
//PET1190FN04 - Add AccountableCode rules
//
//   Rev 1.0   Mar 03 2005 18:58:02   Fengyong
//Initial revision.
 */
