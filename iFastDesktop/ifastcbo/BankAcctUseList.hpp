#define DISABLE_MACRO_REDEFINITION_WARNINGS 1

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
//    Copyright 2002 by DST Canada, Inc.
//
//
//******************************************************************************
//
// ^FILE   : BankAcctUseList.hpp
// ^AUTHOR : Robert Kovacs
// ^DATE   : 07/03/02
//
// ^CLASS    : BankAcctUseList
// ^SUBCLASS :
//
// ^CLASS DESCRIPTION :
//
//******************************************************************************

#include <ifastcbo\mfcancbo.hpp>
#include <bfutil\bfcritsec.hpp>

#undef IFASTCBO_LINKAGE
#ifdef IFASTCBO_DLL
   #define IFASTCBO_LINKAGE CLASS_EXPORT
#else
   #define IFASTCBO_LINKAGE CLASS_IMPORT
#endif

class IFASTCBO_LINKAGE BankAcctUseList : public MFCanBFCbo, private boost::noncopyable
{
public:
   // X-structors
   BankAcctUseList( BFAbstractCBO &parent );
   virtual ~BankAcctUseList( void );

   // Initialize function
   SEVERITY init( const DString& strBankType );

   DString getAcctUseSubstList( const DString& strBankType );
protected:
   SEVERITY doCreateNewObject(BFCBO *& pBase, DString & strKey, const BFDataGroupId& idDataGroup );
   SEVERITY doCreateObject( const BFData& data, BFCBO *&pObjOut );

private:
   DString buildSubList( const DString& strBankType );
   DString getBankingEntity(const DString& strBankType);
   DString getDataDictSubst(const DString& strBankType);
   DString m_strBankingEntity;
   BFCritSec _csBankAcctUseSubList;
};

//******************************************************************************
//              Revision Control Entries
//******************************************************************************
/* $Log:   Y:/VCS/BF iFAST/ifastcbo/BankAcctUseList.hpp-arc  $
//
//   Rev 1.4   May 23 2003 10:04:12   popescu
//Part of bank instructions cleaning up process, moved the bank types into the ifastids project
// 
*/