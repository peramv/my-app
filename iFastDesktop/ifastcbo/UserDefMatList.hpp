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
// ^FILE   : UserDefMatList.hpp
// ^CLASS  : UserDefMatList
// ^PARENT : ListBase
//
//******************************************************************************


#include <ifastcbo\mfcancbo.hpp>
#include <boost\utility.hpp>

#undef IFASTCBO_LINKAGE
#ifdef IFASTCBO_DLL
   #define IFASTCBO_LINKAGE CLASS_EXPORT
#else
   #define IFASTCBO_LINKAGE CLASS_IMPORT
#endif

class IFASTCBO_LINKAGE UserDefMatList : public MFCanBFCbo, private boost::noncopyable
{
public:

   UserDefMatList( BFAbstractCBO &parent );
   virtual ~UserDefMatList();

   SEVERITY init( const DString& accountNum, 
                  const BFDataGroupId& idDataGroup,
                  const DString& LegalMaturityDate = NULL_STRING,
                  const DString& ContractType = NULL_STRING,
                  const DString& dstrTrack= I_("N"),
                  const DString& dstrPageName = NULL_STRING );

   SEVERITY initNew( const DString& accountNum, 
                     const DString& contracttype,
                     const BFDataGroupId& idDataGroup);
   SEVERITY getMore();

protected:

   virtual SEVERITY doCreateObject( const BFData& data, BFCBO *&pObjOut );
   SEVERITY doCreateNewObject(BFCBO *& pBase, DString &strKey , const BFDataGroupId& idDataGroup );
   virtual void doReset (const BFDataGroupId &idDataGroup);

private:

   BFData m_requestData;
   DString m_LegalMaturityDate;
   DString m_AccountNum;
   DString m_ContractType;
};


//*****************************************************************************
// Revision Control Entries
//*****************************************************************************
//
// $Log:   Y:/VCS/BF iFAST/ifastcbo/UserDefMatList.hpp-arc  $
//
//   Rev 1.4   Jul 08 2005 16:11:42   hernando
//Incident 344960 - Added ContractType to initNew sig.
//
//   Rev 1.3   Jun 22 2005 13:11:50   popescu
//Incident #339563 - fixed NASU flow crash on the UserDefMat screen
//
//   Rev 1.2   Apr 18 2005 17:21:32   hernando
//PET1024 FN02 - Added doReset to retain list values.
//
//   Rev 1.1   Apr 14 2005 10:10:18   hernando
//PET1024 FN02 - Added Contract Type support.
//
//   Rev 1.0   Mar 20 2005 17:12:58   hernando
//Initial revision.
