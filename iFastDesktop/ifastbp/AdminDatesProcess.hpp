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
// ^FILE   : AdminDatesProcess.h
// ^AUTHOR : Yingbao Li
// ^DATE   : 6/05/1999
//
// -----------------------------------------------------------------------------
//
// ^CLASS    : AdminDatesProcess
//    This class manages the management company and profile selection.
//
// ^MEMBER VARIABLES :
//
// ^CODING COMMENTS  :
//
//******************************************************************************/



#include <bfproc\AbstractProcess.hpp>
///#endif

// Import/Export resolution
#undef IFASTBP_LINKAGE
#ifdef IFASTBP_DLL
   #define IFASTBP_LINKAGE CLASS_EXPORT
#else
   #define IFASTBP_LINKAGE CLASS_IMPORT
#endif

class IFASTBP_LINKAGE AdminDatesProcess : public AbstractProcess  
{
public:
//CP20030319   AdminDatesProcess();
   AdminDatesProcess( GenericInterfaceContainer* pGIC, GenericInterface* pGIParent, const Command& rCommand );
   virtual ~AdminDatesProcess();
protected:
   /**
     * Provide class specific implementation for some fields.
     * An exception will be thrown if the field cannot be found.
     * @param rpGICaller - A reference pointer to the calling object.
     * @param idContainer - ID of container we are using.
     * @param idField - ID of field we are getting.
     * @param idDataGroup - CBO data group ID we are operating with
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
   virtual bool doModelessChildComplete( const Command &cmd );
   virtual bool doModelessSetFocus( GenericInterface *rpGICaller );
   /**
     * Implementation to support the process method.
     * @returns an enum representing the return type
     */
   virtual E_COMMANDRETURN doProcess();


private:
   DString  strModUser;
   DString  strModDate;
   DString  strProcessDate;
   DString  strProcessUser;
   DString  strProcessTime;
   DString  strDisplayType;
   GenericInterface *_rpChildGI;
};

///#endif 

//******************************************************************************
//              Revision Control Entries
//******************************************************************************
//
/* $Log:   Y:/VCS/BF iFAST/ifastbp/AdminDatesProcess.hpp-arc  $
 * 
 *    Rev 1.9   Feb 19 2005 18:17:36   hernando
 * PET1117 FN66-68 - Added alternate display; Process Date and ProcessTime.
 * 
 *    Rev 1.8   Mar 21 2003 17:35:26   PURDYECH
 * BFDataGroupId/BFContainerId changeover
 * 
 *    Rev 1.7   Oct 09 2002 23:53:00   PURDYECH
 * PVCS Database Conversion
 * 
 *    Rev 1.6   Aug 29 2002 12:51:42   SMITHDAV
 * ClientLocale and typed field changes.
 * 
 *    Rev 1.5   22 May 2002 18:21:52   PURDYECH
 * BFData Implementation
 * 
 *    Rev 1.4   19 Mar 2002 13:15:00   PURDYECH
 * Use #pragma once as include guard
 * Remove compile time "including..." message
 * 
 *    Rev 1.3   Jun 07 2001 11:29:36   YINGBAOL
 * remove doRefresh
 * 
 *    Rev 1.2   Aug 02 2000 15:31:38   BUZILA
 * "locale" changes
 * 
 *    Rev 1.1   Feb 15 2000 18:56:12   MCNABBGL
 * changed comment format
 * 
 *    Rev 1.0   Feb 15 2000 10:58:56   SMITHDAV
 * Initial revision.
 * 
 *    Rev 1.4   Dec 07 1999 12:29:24   DT24433
 * added idDataGroup to doGetField parms
 * 
 *    Rev 1.3   Oct 28 1999 17:41:34   DT24433
 * removed doOk/doCancel
 * 
 *    Rev 1.2   Aug 31 1999 11:24:16   DT24433
 * changed dogetfield/dosetfield parms
 * 
 *    Rev 1.1   Jul 08 1999 10:03:26   SMITHDAV
 * Modify revision history commaent format to old
 * style comment -- I can't seem to get new style comments to work.
 *
 */
