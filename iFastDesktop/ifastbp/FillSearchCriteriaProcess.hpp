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
//    AUTHOR : Serban Popescu
//    DATE   : 21/07/99
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

/**
 * Class that manages the search criterias labels!
 *
 * @author Serban Popescu
 * </dd></dl><p><dl><dt><b>Date Created:</b></dt><dd> 25/06/1999</dd></dl>
 * @version 0.1
 */

class IFASTBP_LINKAGE FillSearchCriteriaProcess : public AbstractProcess
{
// Construction
public:
   /**
    * Default constructor
    */
//CP20030319   FillSearchCriteriaProcess();
   FillSearchCriteriaProcess( GenericInterfaceContainer* pGIC, GenericInterface* pGIParent, const Command& rCommand );
   virtual ~FillSearchCriteriaProcess();
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
   /**
     * Implementation to support the process method.
     * @returns an enum representing the return type
     */
   virtual E_COMMANDRETURN doProcess();
   virtual bool doRefresh( GenericInterface *rpGICaller, 
                           const I_CHAR *szOriginalCommand )
   {
      return(true);
   }
   /**
     * Provide class specific implementation for some fields.
     * An exception will be thrown if the field is not found.
     * @param rpGICaller - A reference pointer to the calling object.
     * @param idContainer - ID of container we are using.
     * @param idField - ID of field we are getting.
     * @param idDataGroup - CBO data group ID we are operating with
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
   virtual void setCurrentListItem(
                                  const GenericInterface *rpGICaller,
                                  const BFContainerId& idList,
                                  const DString& strListItemKey
                                  );
private:
   void assignSearchLabels(const BFContainerId &usingList, 
      const BFContainerId &searchLabelList);
   //keeps the current 'using' list if the current item in the SearchCriteria list 
   //is set to the search criteria code
   DString _currentUsingList;
   DString _label1;
   DString _label2;
   DString _label3;
};


//******************************************************************************
//              Revision Control Entries
//******************************************************************************
//
/* $Log:   Y:/VCS/BF iFAST/ifastbp/FillSearchCriteriaProcess.hpp-arc  $
 * 
 *    Rev 1.11   Aug 10 2004 11:12:04   FENGYONG
 * PET117 FN5 - Client Condition Fee
 * 
 *    Rev 1.10   Jul 16 2003 15:51:40   FENGYONG
 * Add Account search using businessno
 * 
 *    Rev 1.9   Jun 27 2003 18:12:26   popescu
 * Pay To Entity feature, dialog, process and CBO
 * 
 *    Rev 1.8   Mar 21 2003 17:39:54   PURDYECH
 * BFDataGroupId/BFContainerId changeover
 * 
 *    Rev 1.7   Oct 09 2002 23:53:14   PURDYECH
 * PVCS Database Conversion
 * 
 *    Rev 1.6   Aug 29 2002 12:52:26   SMITHDAV
 * ClientLocale and typed field changes.
 * 
 *    Rev 1.5   22 May 2002 18:21:02   PURDYECH
 * BFData Implementation
 * 
 *    Rev 1.4   19 Mar 2002 13:17:02   PURDYECH
 * Use #pragma once as include guard
 * Remove compile time "including..." message
 * 
 *    Rev 1.3   07 Mar 2001 15:41:54   BUZILAMI
 * Broker, Branch, SlsRep Bank Instructions changes
 * 
 *    Rev 1.2   Aug 02 2000 15:31:40   BUZILA
 * "locale" changes
 * 
 *    Rev 1.1   Feb 15 2000 18:56:28   MCNABBGL
 * changed comment format
 * 
 *    Rev 1.0   Feb 15 2000 10:59:08   SMITHDAV
 * Initial revision.
// 
//    Rev 1.5   Dec 07 1999 12:26:08   DT24433
// added idDataGroup to doGetField/doSetField parms
// 
//    Rev 1.4   Oct 29 1999 11:26:52   DT24433
// removed doOk
// 
//    Rev 1.3   Oct 18 1999 09:48:06   POPESCUS
// New search criterias
// 
//    Rev 1.2   24 Sep 1999 16:39:48   HUANGSHA
// Added search for Address Book
// 
//    Rev 1.1   Aug 31 1999 09:50:50   DT24433
// changed dogetfield/dosetfield parms
 * 
 */
