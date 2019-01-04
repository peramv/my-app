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
//
// ^FILE   : AcctCategoryProcess.cpp
// ^AUTHOR :  Robert Kovacs
// ^DATE   : 01/23/2003
//
// -----------------------------------------------------------------------------
//
// ^CLASS    : AcctCategoryProcess
//
// ^MEMBER VARIABLES :
//
// ^CODING COMMENTS  :
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


class IFASTBP_LINKAGE AcctCategoryProcess : public AbstractProcess , public IFastHistoricalParameters
{
// Construction
public:
   /**
    * Default constructor
    */
//CP20030319   AcctCategoryProcess();
   AcctCategoryProcess( GenericInterfaceContainer* pGIC, GenericInterface* pGIParent, const Command& rCommand );
   virtual ~AcctCategoryProcess();
   /**
     * This method is used (typically by a GUI object) to delete the current
     * item from a list.
     * An exception will be thrown if the list or item could not be found.
     * See note about lists in class document block.
     * @param rpGICaller - A reference pointer to the calling object.
     * @param idList - ID of list we are using.
     * @returns highest SEVERITY encountered, check conditions.
     */
   SEVERITY deleteItemFromList( const GenericInterface *rpGICaller,
                                const BFContainerId& idList );
protected:
   virtual bool doOk( GenericInterface *rpGICaller );

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
   virtual bool doModelessChildComplete( const Command &cmd );
   /**
      * Used to bring a modeless dialog (via parent process) to the top of the
      * window stack.
      * @param rpGICaller - A reference pointer to the calling object.
      * @returns true if successful, check conditions if false
      */
   virtual bool doModelessSetFocus( GenericInterface *rpGICaller );
   /**
     * Implementation to support the process method.
     * @returns an enum representing the return type
     */
   virtual E_COMMANDRETURN doProcess();
   void *getPtrForContainer( const BFContainerId& idContainer,
                             const BFDataGroupId& idDataGroup );

   virtual SEVERITY getHistoricalParameters ( const BFContainerId &idContainer,
                                              BFFieldId &recordIdField, 
                                              DString &tableId, 
                                              DString &dstrKeys);

   virtual SEVERITY getHistoricalParameters( const BFContainerId& idContainer, 
                                             HISTORICAL_VECTOR &vectorInput );
   
private:
   GenericInterface *_rpChildGI;
   DString m_strAcctNum;   
};

//******************************************************************************
//              Revision Control Entries
//******************************************************************************
//
/* $Log:   Y:/VCS/BF iFAST/ifastbp/AcctCategoryProcess.hpp-arc  $
//
//   Rev 1.4   Dec 01 2010 04:19:24   dchatcha
//P0175716 FN02 - Client Name Redemption - EPA Auto Settlement.
//
//   Rev 1.3   Dec 08 2003 15:40:34   HSUCHIN
//PTS 10024902 - bug fix with mfaccount refresh to show updated cautions list.
//
//   Rev 1.2   Mar 21 2003 17:35:02   PURDYECH
//BFDataGroupId/BFContainerId changeover
//
//   Rev 1.1   Jan 25 2003 16:57:42   KOVACSRO
//Added deleteItemFromList
//
//   Rev 1.0   Jan 23 2003 17:01:50   KOVACSRO
//Initial revision.

 */