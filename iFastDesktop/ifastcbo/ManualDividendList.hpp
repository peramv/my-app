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
//    Copyright 2003
//
//
//******************************************************************************
//
// ^FILE   : ManualDividendList.hpp
// ^AUTHOR : 
// ^DATE   : 
//
// ^CLASS    : ManualDividendList
// ^SUBCLASS :
//
// ^CLASS DESCRIPTION :
//
//******************************************************************************

#include <ifastcbo\mfcancbo.hpp>
#include <boost\utility.hpp>

class ManualDividend;

#undef IFASTCBO_LINKAGE
#ifdef IFASTCBO_DLL
   #define IFASTCBO_LINKAGE CLASS_EXPORT
#else
   #define IFASTCBO_LINKAGE CLASS_IMPORT
#endif

class IFASTCBO_LINKAGE ManualDividendList : public MFCanBFCbo, private boost::noncopyable
{
public:

   ManualDividendList( BFAbstractCBO &parent );
   virtual ~ManualDividendList();

  SEVERITY init(const BFDataGroupId& idDataGroup, 
      const DString& dstrTrack = I_("N"), 
      const DString& dstrPageName = NULL_STRING);
   SEVERITY initNew( const BFDataGroupId& idDataGroup, const DString& dstrTrack, const DString& dstrPageName );
   SEVERITY doCreateNewObject( BFCBO*& pBase, DString &strKey, const BFDataGroupId& idDataGroup );
   SEVERITY doValidateAll( const BFDataGroupId& idDataGroup, long lValidateGroup );

   void getTrackParam( DString& dstrTrack, DString& dstrActivity )
   {
      dstrTrack = m_dstrTrack;
      dstrActivity = m_dstrActivity;
   }

private:

   DString m_dstrTrack;
   DString m_dstrActivity;
};

//*****************************************************************************
// Revision Control Entries
//*****************************************************************************
//
// $Log:   Y:/VCS/BF iFAST/ifastcbo/ManualDividendList.hpp-arc  $
//
//   Rev 1.2   Nov 14 2004 14:49:24   purdyech
//PET910 - .NET Conversion
//
//   Rev 1.1   May 27 2003 18:29:44   popescu
//due to several memory leaks found in some list getters at the DSTCWorkSession level caused by copy/paste, I've created a common template function to retrieve the dependent objects
//
//   Rev 1.0   May 22 2003 16:52:52   HERNANDO
//Initial revision.
