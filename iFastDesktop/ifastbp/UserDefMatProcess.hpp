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


#include <bfproc\abstractprocess.hpp>

class MFAccount;
class UserDefMatList;

#undef IFASTBP_LINKAGE
#ifdef IFASTBP_DLL
   #define IFASTBP_LINKAGE CLASS_EXPORT
#else
   #define IFASTBP_LINKAGE CLASS_IMPORT
#endif

class IFASTBP_LINKAGE UserDefMatProcess : public AbstractProcess
{
public:
   UserDefMatProcess( GenericInterfaceContainer* pGIC, GenericInterface* pGIParent, const Command& rCommand );
   virtual ~UserDefMatProcess();

   SEVERITY performSearch( GenericInterface *rpGICaller, const BFContainerId& idSearch, E_SEARCHACTION eSearchAction );

protected:

   virtual void doGetField(
                          const GenericInterface *rpGICaller,
                          const BFContainerId& idContainer,
                          const BFFieldId& idField,
                          const BFDataGroupId& idDataGroup,
                          DString &strValueOut,
                          bool bFormatted
                          ) const;

   virtual SEVERITY doInit();
   virtual bool doModelessChildComplete( const Command &cmd );
   virtual bool doModelessSetFocus( GenericInterface *rpGICaller );
   virtual bool doMoreRecordsExist( GenericInterface *rpGICaller, const BFContainerId& idSearch );
   virtual void doPostOk( GenericInterface *rpGICaller, bool bSuccessFlag );
   virtual SEVERITY doValidateAll( BFAbstractCBO *rpWSD,  const BFDataGroupId& idDataGroup   );
   virtual E_COMMANDRETURN doProcess();
   void *getPtrForContainer( const BFContainerId& idContainer, const BFDataGroupId& idDataGroup );

private:

   GenericInterface *m_rpChildGI;
   DString m_dstrAccountNumber;
   DString m_dstrShareholderNumber;
   DString m_dstrIsContract;
   DString m_dstrLegalMaturityDate;
   DString m_dstrSegTransExist;
   DString m_dstrContractType;
	DString m_dstrModPerm;
   UserDefMatList *m_pUserDefMatList;
};


//******************************************************************************
//              Revision Control Entries
//******************************************************************************
//
// $Log:   Y:/VCS/BF iFAST/ifastbp/UserDefMatProcess.hpp-arc  $
//
//   Rev 1.4   Feb 14 2006 14:10:56   zhengcon
//Incident #528284 - add one field ModPerm for updatable permission of User Defined Maturity Date of converted account
//
//   Rev 1.3   Apr 14 2005 10:05:14   hernando
//PET1024 FN02 - Added parameter, Contract Type.
//
//   Rev 1.2   Mar 22 2005 09:48:38   hernando
//PET1024 FN02 - Added Seg Trans Exist string.
//
//   Rev 1.1   Mar 20 2005 20:11:30   hernando
//PET1024 FN02 - Added doPostOk.
