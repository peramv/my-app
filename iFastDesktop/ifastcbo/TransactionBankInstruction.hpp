#error "This file is obsolete!"
//no longer used anywhere
/*
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
// ^FILE   : TransactionBankInstruction.hpp
// ^AUTHOR : Yakov Prager
// ^DATE   : May 19, 1999
//
// ^CLASS  : TransactionBankInstruction
// ^PARENT : BFBase
//
// ^CLASS DESCRIPTION :
//    ements a map from the STL to hold fully instantiated BFBase objects
//    that are created from Data objects stored in the inherited ListBase class 
//
//******************************************************************************


#include <ifastcbo\mfcancbo.hpp>
#include <boost\utility.hpp>
///#endif

#undef IFASTCBO_LINKAGE
#ifdef IFASTCBO_DLL
   #define IFASTCBO_LINKAGE CLASS_EXPORT
#else
   #define IFASTCBO_LINKAGE CLASS_IMPORT
#endif


class IFASTCBO_LINKAGE TransactionBankInstruction : public MFCanBFCbo, private boost::noncopyable
{
public:
   // Creators
   TransactionBankInstruction( BFAbstractCBO &parent );
   virtual ~TransactionBankInstruction( void );

   // Initialize function
   SEVERITY init( const DString&  strTransId, 
                  const DString& strPendingRid, 
                  const DString& strTransPending,
                  const DString& dstrTrack= I_("N"),
                  const DString& dstrPageName = NULL_STRING );


private:
};

//*****************************************************************************
// Revision Control Entries
//*****************************************************************************
//
/* $Log:   Y:/VCS/BF iFAST/ifastcbo/TransactionBankInstruction.hpp-arc  $
 * 
 *    Rev 1.10   Nov 14 2004 14:58:10   purdyech
 * PET910 - .NET Conversion
 * 
 *    Rev 1.9   Sep 29 2003 14:44:14   popescu
 * this file is obsolete
 * 
 *    Rev 1.8   Mar 21 2003 18:27:36   PURDYECH
 * BFDataGroupId/BFContainerId changeover
 * 
 *    Rev 1.7   Oct 09 2002 23:55:12   PURDYECH
 * PVCS Database Conversion
 * 
 *    Rev 1.6   Aug 29 2002 12:53:56   SMITHDAV
 * ClientLocale and typed field changes.
 * 
 *    Rev 1.5   22 May 2002 22:22:26   PURDYECH
 * BFData Implementation
 * 
 *    Rev 1.4   22 May 2002 18:19:08   PURDYECH
 * BFData Implementation
 */
