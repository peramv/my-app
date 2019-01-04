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
//    Copyright 2000 by DST Systems, Inc.
//
//******************************************************************************
//
// ^FILE   : ContractInfoProcess.hpp
// ^AUTHOR : Celia Zhang
// ^DATE   : 02/01/2000
//
// ----------------------------------------------------------
//
// ^CLASS    : ContractInfoProcess
//
// ^MEMBER VARIABLES :
//
// ^CODING COMMENTS  :  
//
//******************************************************************************


#include <bfproc\AbstractProcess.hpp>

// Forward references
class ContractInfoList;
class MFAccount;
class MasterContractList;
// Import/Export resolution
#undef IFASTBP_LINKAGE
#ifdef IFASTBP_DLL
   #define IFASTBP_LINKAGE CLASS_EXPORT
#else
   #define IFASTBP_LINKAGE CLASS_IMPORT
#endif

#include <ifastbp\ifasthistoricalparameters.hpp>

/**
 * Class that manages the entity process.
 *
 * @author 
 * </dd></dl><p><dl><dt><b>Date Created:</b></dt><dd> 03/04/1999</dd></dl>
 * @version 0.1
 */

class IFASTBP_LINKAGE ContractInfoProcess : public AbstractProcess,
      public IFastHistoricalParameters
{
// Construction
public:
   /**
    * Default constructor
    */
//CP20030319   ContractInfoProcess();
   ContractInfoProcess( GenericInterfaceContainer* pGIC, GenericInterface* pGIParent, const Command& rCommand );
   virtual ~ContractInfoProcess();

protected:
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
   virtual bool doRefresh( GenericInterface *rpGICaller,
                           const I_CHAR *szOriginalCommand );
   virtual bool doModelessSetFocus( GenericInterface *rpGICaller );

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
   virtual bool doModelessChildComplete( const Command &cmd );
   
   void doPostOk( GenericInterface *rpGICaller,
                   bool bSuccessFlag );

   SEVERITY doSetField( const GenericInterface *rpGICaller,
                        const BFContainerId& idContainer,
                        const BFFieldId& idField,
                        const BFDataGroupId& idDataGroup,
                        const DString& strValue,
                        bool bFormatted );

   /**
     * Search a proper entity and get the DofBirth of that entity base on
     * Business rule.
     * @param strDofBirth - The DofBirth which will be passed to CBO for validating.
     */
   void GetDofBirth( const BFDataGroupId& idDataGroup, DString &strDofBirth );
   virtual void doGetField(
                          const GenericInterface *rpGICaller,
                          const BFContainerId& idContainer,
                          const BFFieldId& idField,
                          const BFDataGroupId& idDataGroup,
                          DString &strValueOut,
                          bool bFormatted
                          ) const;


   const BFProperties *doGetFieldAttributes( const GenericInterface *rpGICaller, 
                                             const BFContainerId& idContainer, 
                                             const BFFieldId& idField, 
                                             const BFDataGroupId& idDataGroup );

   SEVERITY getHistoricalParameters( const BFContainerId& idContainer, HISTORICAL_VECTOR &vectorInput );
   void *getPtrForContainer (const BFContainerId& idContainer,const BFDataGroupId& idDataGroup);
   
   virtual bool doMoreRecordsExist(GenericInterface *rpGICaller,
                                   const BFContainerId& idSearch );

   virtual bool doOk (GenericInterface* rpGICaller);

private:

   // Private member function

   // Private member data
   ContractInfoList *_pContractInfoList;
   MasterContractList *_pMasterContractList;
   GenericInterface *_rpChildGI;
   MFAccount* _pMFAccount;
   DString _strAccountNum;
   DString strShareholdNum;
   DString strKey;
   DString strTransIdEmpty;
//   DString strDofBirth;
//   DString strEntityType;
   DString strSeqNumber;
   DString _dstrOrgKey;
   DString _dstrDestKey;
   DString _dstrSpouseName;
   DString _dstrAskDofBirthSp;
   DString _dstrAskDofBirthEntity;
   DString _dstrOwnerName;
   DString _dstrEntityIdOw;
   DString _dstrEntityIdSp;
   DString _dstrNewShareholder;
   DString _dstrNewAccount;
   bool _bPermMultiContract;
   bool _bIsDuringNASU;
};

///#endif 

//******************************************************************************
//              Revision Control Entries
//******************************************************************************
//
/* $Log:   Y:/VCS/BF iFAST/ifastbp/ContractInfoProcess.hpp-arc  $
 * 
 *    Rev 1.19   Aug 13 2012 00:00:08   popescu
 * IN2972860 - Cannot changes account status to death and death transfer.
 * 
 *    Rev 1.18   Aug 10 2012 18:02:12   kitticha
 * IN2972860 - Cannot changes account status to death and death transfer.
 * 
 *    Rev 1.17   Dec 27 2011 00:59:14   dchatcha
 * P0186484 - FN 05 - work on Contract Information Screen
 * 
 *    Rev 1.16   Mar 21 2003 17:38:20   PURDYECH
 * BFDataGroupId/BFContainerId changeover
 * 
 *    Rev 1.15   Oct 09 2002 23:53:10   PURDYECH
 * PVCS Database Conversion
 * 
 *    Rev 1.14   Aug 29 2002 12:52:04   SMITHDAV
 * ClientLocale and typed field changes.
 * 
 *    Rev 1.13   22 May 2002 18:21:28   PURDYECH
 * BFData Implementation
 * 
 *    Rev 1.12   19 Mar 2002 13:15:28   PURDYECH
 * Use #pragma once as include guard
 * Remove compile time "including..." message
 * 
 *    Rev 1.11   Nov 07 2001 14:39:22   ZHANGCEL
 * Remove some member datas those are no longer needed
 * 
 *    Rev 1.10   Jul 17 2001 09:39:14   OLTEANCR
 * added logic for multicontracts
 * 
 *    Rev 1.9   May 11 2001 16:05:28   OLTEANCR
 * unchanged
 * 
 *    Rev 1.8   Oct 18 2000 10:56:32   KOVACSRO
 * Added doPostOk().
 * 
 *    Rev 1.7   Aug 02 2000 15:31:38   BUZILA
 * "locale" changes
 * 
 *    Rev 1.6   May 12 2000 17:51:18   ZHANGCEL
 * Deal with DofBirth checking problems
 * 
 *    Rev 1.5   Apr 11 2000 11:38:30   ZHANGCEL
 * Add some stuff for DofBirth
 * 
 *    Rev 1.4   Mar 17 2000 16:49:20   ZHANGCEL
 * Checked in for release
 * 
 *    Rev 1.3   Mar 15 2000 10:03:54   ZHANGCEL
 * Bugs fixed
 * 
 *    Rev 1.2   Mar 07 2000 10:25:34   HSUCHIN
 * changed to use new infra
 * 
 *    Rev 1.1   Feb 15 2000 18:56:22   MCNABBGL
 * changed comment format
 * 
 *    Rev 1.0   Feb 15 2000 10:59:02   SMITHDAV
 * Initial revision.
// 
//    Rev 1.0   Feb 03 2000 13:23:06   ZHANGCEL
// Initial revision.
 * 
 *
 */
