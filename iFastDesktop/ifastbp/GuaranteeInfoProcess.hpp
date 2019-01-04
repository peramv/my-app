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
// ^FILE   : GuaranteeInfoProcess.hpp
// ^AUTHOR : Celia Zhang
// ^DATE   : 01/18/2000
//
// ----------------------------------------------------------
//
// ^CLASS    : GuaranteeInfoProcess
//
// ^MEMBER VARIABLES :
//
// ^CODING COMMENTS  :  
//
//******************************************************************************


#include <bfproc\AbstractProcess.hpp>

// Import/Export resolution
#undef IFASTBP_LINKAGE
#ifdef IFASTBP_DLL
   #define IFASTBP_LINKAGE CLASS_EXPORT
#else
   #define IFASTBP_LINKAGE CLASS_IMPORT
#endif


class GuaranteeDetailList;
class GuaranteeInfoList;
class GuaranteeSummaryList;

class IFASTBP_LINKAGE GuaranteeInfoProcess : public AbstractProcess
{
public:   
   GuaranteeInfoProcess( GenericInterfaceContainer* pGIC, GenericInterface* pGIParent, const Command& rCommand );
   virtual ~GuaranteeInfoProcess();

   virtual bool doMoreRecordsExist( GenericInterface *rpGICaller,
                                    const BFContainerId& idContainer );

   virtual bool doGetData( GenericInterface * rpGICaller=NULL,
                           BFData * rpData=NULL ) const;
protected:

   virtual void *getPtrForContainer( const BFContainerId& idContainer, const BFDataGroupId& idDataGroup );   
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

    virtual void doGetField ( const GenericInterface *rpGICaller,  
                             const BFContainerId &idContainer, 
                             const BFFieldId &idField, 
                             const BFDataGroupId &idDataGroup, 
                             DString &strValueOut, 
                             bool bFormtted) const;
private:   
   GenericInterface     *_rpChildGI;
   GuaranteeSummaryList *_pGuaranteeSummaryList;
   GuaranteeInfoList    *_pGuaranteeInfoList;
   GuaranteeDetailList  *_pGuaranteeDetailList;
   GuaranteeInfoList    *_pDummyGuaranteeInfoList;
   GuaranteeDetailList  *_pDummyGuaranteeDetailList;
   
   DString strAccountNum;
   DString strShareholdNum;
   DString strKey;
   DString _strGuarAcctTotal;   
};

///#endif 

//******************************************************************************
//              Revision Control Entries
//******************************************************************************
//
/* $Log:   Y:/VCS/BF iFAST/ifastbp/GuaranteeInfoProcess.hpp-arc  $
 * 
 *    Rev 1.13   Jun 28 2006 19:53:04   popescu
 * Incident# 655992 - fixed crash in GuaranteeInfo screen when resizing
 * 
 *    Rev 1.12   Aug 17 2005 16:55:08   porteanm
 * Incident 351033 - Details support.
 * 
 *    Rev 1.11   Mar 21 2003 17:40:44   PURDYECH
 * BFDataGroupId/BFContainerId changeover
 * 
 *    Rev 1.10   Oct 09 2002 23:53:16   PURDYECH
 * PVCS Database Conversion
 * 
 *    Rev 1.9   22 May 2002 18:20:48   PURDYECH
 * BFData Implementation
 * 
 *    Rev 1.8   19 Mar 2002 13:17:20   PURDYECH
 * Use #pragma once as include guard
 * Remove compile time "including..." message
 * 
 *    Rev 1.7   Aug 21 2001 16:49:52   OLTEANCR
 * added   _strGuarAcctTotal;
 * 
 *    Rev 1.6   Jul 29 2001 12:33:26   OLTEANCR
 * added class GuaranteeSummaryList
 * 
 *    Rev 1.5   Jul 17 2001 09:41:14   OLTEANCR
 * added getPtrForContainer( )
 * 
 *    Rev 1.4   May 14 2001 10:55:24   OLTEANCR
 * unchanged
 * 
 *    Rev 1.3   Mar 17 2000 16:49:58   ZHANGCEL
 * Checked in for release
 * 
 *    Rev 1.2   Mar 10 2000 12:58:00   ZHANGCEL
 * Updated
 * 
 *    Rev 1.1   Feb 15 2000 18:56:30   MCNABBGL
 * changed comment format
 * 
 *    Rev 1.0   Feb 15 2000 10:59:10   SMITHDAV
 * Initial revision.
// 
//    Rev 1.0   Jan 28 2000 14:34:34   ZHANGCEL
// Initial revision.
 * 
 *
 */
