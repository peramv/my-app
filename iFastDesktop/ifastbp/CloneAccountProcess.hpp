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
// ^FILE   : CloneAccountProcess.hpp
// ^AUTHOR : Serban Popescu
// ^DATE   : October, 2006
//
// ----------------------------------------------------------
//
// ^CLASS    : CloneAccountProcess
//
// ^MEMBER VARIABLES :
//
// ^CODING COMMENTS  :  
//
//******************************************************************************


#include <bfproc\AbstractProcess.hpp>
///#endif

// Forward references
class CloneAccount;
class MFAccount;

// Import/Export resolution
#undef IFASTBP_LINKAGE
#ifdef IFASTBP_DLL
   #define IFASTBP_LINKAGE CLASS_EXPORT
#else
   #define IFASTBP_LINKAGE CLASS_IMPORT
#endif

class IFASTBP_LINKAGE CloneAccountProcess : public AbstractProcess
{
// Construction
public:
   CloneAccountProcess ( GenericInterfaceContainer *pGIC, 
                             GenericInterface *pGIParent, 
                             const Command& rCommand);
   virtual ~CloneAccountProcess();
protected:
   virtual void doGetField( const GenericInterface *rpGICaller,
                            const BFContainerId& idContainer,
                            const BFFieldId& idField,
                            const BFDataGroupId& idDataGroup,
                            DString &strValueOut,
                            bool bFormatted) const;
   virtual SEVERITY doInit();
   virtual E_COMMANDRETURN doProcess();
   virtual bool doModelessChildComplete (const Command &cmd);
   virtual bool doModelessSetFocus (GenericInterface *rpGICaller);
   virtual SEVERITY doSetField( const GenericInterface *rpGICaller,
                                const BFContainerId& idContainer,
                                const BFFieldId& idField,
                                const BFDataGroupId& idDataGroup,
                                const DString& strValue,
                                bool bFormatted);

   void * getPtrForContainer ( const BFContainerId &idContainer, 
                               const BFDataGroupId &idDataGroup);
   virtual bool doOk (GenericInterface *rpGICaller);
   virtual void doPostOk ( GenericInterface *rpGICaller, 
                           bool bSuccessFlag);
   virtual SEVERITY doValidateAll ( BFAbstractCBO *rpWSD, 
                                    const BFDataGroupId& idDataGroup); 
   virtual bool setCommitDataGroupAsHost();
private:
   GenericInterface *_rpChildGI;
   DString _caller,
      _accountNum;
   CloneAccount *_pCloneAccount;
   MFAccount *_pMFAccount;
};

///#endif 
//******************************************************************************
//              Revision Control Entries
//******************************************************************************
//
/* $Log:   Y:/VCS/BF iFAST/ifastbp/CloneAccountProcess.hpp-arc  $
//
//   Rev 1.0   Nov 08 2006 17:32:16   popescu
//Initial revision.
//
//   Rev 1.2   Sep 22 2006 00:46:52   popescu
//STP 2217/13
//
//   Rev 1.1   Sep 21 2006 01:50:10   popescu
//STP PET 2217/13
//
//   Rev 1.0   Aug 29 2006 18:25:56   popescu
//Initial revision.
//
 */
