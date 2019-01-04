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
class FireFighterLogonInfo;
// Import/Export resolution
#undef IFASTBP_LINKAGE
#ifdef IFASTBP_DLL
   #define IFASTBP_LINKAGE CLASS_EXPORT
#else
   #define IFASTBP_LINKAGE CLASS_IMPORT
#endif

class IFASTBP_LINKAGE FireFighterLogonProcess : public AbstractProcess
{

   public:
   //******************************************************************************
   // Constructor
   //******************************************************************************
   FireFighterLogonProcess( GenericInterfaceContainer* pGIC, GenericInterface* pGIParent, const Command& rCommand );

   //******************************************************************************
   // Destructor
   //******************************************************************************
   virtual ~FireFighterLogonProcess();

   protected:

   //******************************************************************************
   // @returns SEVERITY.
   //******************************************************************************
   virtual SEVERITY doInit();

   //******************************************************************************
   // Function which tells the generic interface container that the modeless child
   // has been destroyed.
   // @param   const Command &cmd - cmd indicating the child is destroyed.
   // @returns bool - true when successful.
   //******************************************************************************
   virtual bool doModelessChildComplete( const Command &cmd );   

   virtual SEVERITY ok2( GenericInterface *rpGI );
   //******************************************************************************
   // This functions starts the Fire Fighter Logon Dialog
   // @returns E_COMMANDRETURN.
   //******************************************************************************
   virtual E_COMMANDRETURN doProcess();
   void doGetField(
                    const GenericInterface *rpGICaller,
                    const BFContainerId& idContainer,
                    const BFFieldId& idField,
                    const BFDataGroupId& idDataGroup,
                    DString &strValueOut,
                    bool bFormatted
                    ) const;

   private:
   GenericInterface *_rpChildGI;                      //Pointer to parent object.   
   int _iTryCounter;
   FireFighterLogonInfo *_pFFLogonInfo;
};


//******************************************************************************
//              Revision Control Entries
//******************************************************************************
//
/* $Log:   Y:/VCS/BF iFAST/ifastbp/FireFighterLogonProcess.hpp-arc  $
//
//   Rev 1.1   Dec 11 2003 11:54:22   linmay
//added doGetField( )
//
//   Rev 1.0   Dec 09 2003 09:02:46   linmay
//Initial Revision
//
 */
