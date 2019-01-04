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
//    Copyright 1999 by DST Canada, Inc.
//
//
//******************************************************************************
//
// ^FILE   : TransTypeFileProcList.hpp
// ^AUTHOR : Zijian Ying
// ^DATE   : 05/31/02
//
// ^CLASS    : TransTypeFileProcList
// ^SUBCLASS :
//
// ^CLASS DESCRIPTION :
//
//******************************************************************************

#include <ifastcbo\mfcancbo.hpp>
#include <bfutil\bfcritsec.hpp>

#ifndef _MAP_
   #include <map>
#endif 


#undef IFASTCBO_LINKAGE
#ifdef IFASTCBO_DLL
   #define IFASTCBO_LINKAGE CLASS_EXPORT
#else
   #define IFASTCBO_LINKAGE CLASS_IMPORT
#endif

class IFASTCBO_LINKAGE TransTypeFileProcList : public MFCanBFCbo
{
public:
   static void buildKey (
         const DString &transType, 
         const DString &payMethod, 
         const DString &fileProcCode,
         DString &strKey);
public:
   // X-structors
   TransTypeFileProcList(BFAbstractCBO &parent);
   virtual ~TransTypeFileProcList(void);

   // Initialize function
   SEVERITY init (const DString &transType);

   DString getFileProcSubList ( const DString &transType, 
                                const DString &payMethod,
                                const DString &currency = NULL_STRING);
   DString getCurrencySubList ( const DString &TransType, 
                                const DString &PayMethod,
                                const DString &FileProc = NULL_STRING);
   DString getPayMethodSubList( const DString &transType, 
                                const DString &fileProc,
                                const DString &currency = NULL_STRING);
   DString getPayMethodSubList2( const DString &transType, 
                                 const DString &currency = NULL_STRING);

protected:
   virtual void getStrKey ( DString &strKey, 
                            const BFData *data);
private:
   BFCritSec _csTransTypeFileProcList;
   DString _usedTransTypes,
      _transType;

   TransTypeFileProcList(const TransTypeFileProcList& copy);
   // = Operator
   TransTypeFileProcList& operator= (const TransTypeFileProcList& copy);
};

//******************************************************************************
//              Revision Control Entries
//******************************************************************************
/* $Log:   Y:/VCS/BF iFAST/ifastcbo/TransTypeFileProcList.hpp-arc  $
//
//   Rev 1.12   Apr 08 2011 04:15:40   kitticha
//PETP0179308_FN01_IN2487930_Desktop not support EFT Purchase Check paytype.
//
//   Rev 1.11   Nov 14 2004 14:59:04   purdyech
//PET910 - .NET Conversion
//
//   Rev 1.10   Sep 13 2004 13:53:28   popescu
//PET 1094 FN4 - Activest Bank File Interface, changed the implementation to handle duplicates values
//
//   Rev 1.9   Jan 27 2004 20:08:30   popescu
//PTS 10026408, removed not needed method, added at the previous iteration
//
//   Rev 1.8   Jan 27 2004 20:04:12   popescu
//PTS 10026408, CITIBNK is not listed in Drop-down list for File Processor in setting up bank information, by Account - Income Distribution
//
//   Rev 1.7   Oct 02 2003 14:37:44   HSUCHIN
//added revision loggin
*/
