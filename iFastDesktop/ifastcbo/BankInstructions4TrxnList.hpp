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
// ^FILE   : BankInstructions4TrxnList.hpp
// ^AUTHOR : Serban Popescu
// ^DATE   : October, 2003
//
// ^CLASS    : BankInstructions4TrxnList
// ^SUBCLASS :
//
// ^CLASS DESCRIPTION :
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

class IFASTCBO_LINKAGE BankInstructions4TrxnList : public MFCanBFCbo, private boost::noncopyable
{
public:
   // X-structors
   BankInstructions4TrxnList ( BFAbstractCBO &parent, 
                               const DString &dstrBankType);
   virtual ~BankInstructions4TrxnList();

   // Initialize function
   SEVERITY init ( const DString &accountNum,
                   const DString &recordId, 
                   const DString &transType, 
                   const DString &type, 
                   const DString &lastBankType , 
                   const DString &currency, 
                   const DString &effectiveDate,
                   const DString &dstrTrack = I_("N"), 
                   const DString &dstrPageName = NULL_STRING);
protected:
   virtual SEVERITY doCreateObject (const BFData &data, BFCBO *&pObjOut);
private:
   DString _dstrBankType,
      _dstrPayType;
};

//******************************************************************************
//              Revision Control Entries
//******************************************************************************
//
/* $Log:   Y:/VCS/BF iFAST/ifastcbo/BankInstructions4TrxnList.hpp-arc  $
//
//   Rev 1.2   27 Jul 2007 15:40:46   popescu
//Incident 948449 - disabled the last EFT banking records call
//
//   Rev 1.1   Nov 04 2004 17:37:14   popescu
//PET 1117/06, Trade processing
//
//   Rev 1.0   Nov 10 2003 14:55:04   popescu
//Initial revision.
//
//   Rev 1.2   Oct 30 2003 17:24:32   FENGYONG
//Add DString PayType
//
//   Rev 1.1   Oct 28 2003 10:38:18   FENGYONG
//Add banktype parameter to the init function
//
//   Rev 1.0   Oct 19 2003 19:08:36   popescu
//Initial revision.
//
//
 */
