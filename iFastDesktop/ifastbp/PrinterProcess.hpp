#pragma once
//******************************************************************************
//
// COPYRIGHT:
//
//    The computer systems, procedures, data bases and
//    programs created and maintained by International Financial, Inc.,
//    are proprietary in nature and as such are confidential.
//    Any unauthorized use or disclosure of such information
//    may result in civil liabilities.
//
//    Copyright 2002 by International Financial, Inc.
//
//******************************************************************************

#include <bfproc\AbstractProcess.hpp>
// Forward references

// Import/Export resolution
#undef IFASTBP_LINKAGE
#ifdef IFASTBP_DLL
   #define IFASTBP_LINKAGE CLASS_EXPORT
#else
   #define IFASTBP_LINKAGE CLASS_IMPORT
#endif

class IFASTBP_LINKAGE PrinterProcess : public AbstractProcess
{

   public:
   //******************************************************************************
   // Constructor
   //******************************************************************************
//CP20030319   PrinterProcess();
   PrinterProcess( GenericInterfaceContainer* pGIC, GenericInterface* pGIParent, const Command& rCommand );

   //******************************************************************************
   // Destructor
   //******************************************************************************
   virtual ~PrinterProcess();

   protected:

   //******************************************************************************
   // @returns SEVERITY.
   //******************************************************************************
   virtual SEVERITY doInit();

   void* getPtrForContainer( const BFContainerId& idContainer,
                             const BFDataGroupId& idDataGroup );

   //******************************************************************************
   // Function which tells the generic interface container that the modeless child
   // has been destroyed.
   // @param   const Command &cmd - cmd indicating the child is destroyed.
   // @returns bool - true when successful.
   //******************************************************************************
   virtual bool doModelessChildComplete( const Command &cmd );   

   virtual SEVERITY ok2( GenericInterface *rpGI );
   //******************************************************************************
   // This functions starts the Reports Dialog
   // @returns E_COMMANDRETURN.
   //******************************************************************************
   virtual E_COMMANDRETURN doProcess();

   private:
   GenericInterface *_rpChildGI;                      //Pointer to parent object.   
   DString _dstrCompanyId, _dstrLocal;
};


//******************************************************************************
//              Revision Control Entries
//******************************************************************************
//
/* $Log:   Y:/VCS/BF iFAST/ifastbp/PrinterProcess.hpp-arc  $
//
//   Rev 1.1   Mar 21 2003 17:46:04   PURDYECH
//BFDataGroupId/BFContainerId changeover
//
//   Rev 1.0   Dec 08 2002 22:10:44   HSUCHIN
//Initial Revision
 */
