#pragma once

//******************************************************************************
//
// COPYRIGHT:
//
// The computer systems, procedures, data bases and
// programs created and maintained by International Financial Data Services,
// are proprietary in nature and as such are confIdential.
// Any unauthorized use or disclosure of such information
// may result in civil liabilities.
//
// Copyright 2009 by International Financial Data Services.
//
//
//******************************************************************************
//
// ^FILE   : PSEEAPList.hpp
// ^AUTHOR : 
// ^DATE   : Nov 2009
//
// ^CLASS    : PSEEAPList
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

//Forward declarations

class IFASTCBO_LINKAGE PSEEAPList : public MFCanBFCbo, private boost::noncopyable
{
public:
   // X-structors
   PSEEAPList( BFAbstractCBO &parent );
   virtual ~PSEEAPList(void);

// Initialize function
   SEVERITY init( const DString &transId,
                  const DString &dstrTrack     = I_( "N" ),
                  const DString &dstrPageName  = NULL_STRING );


protected:

private:
};


//******************************************************************************
//              Revision Control Entries
//******************************************************************************
/** $Log:   Y:/VCS/BF iFAST/ifastcbo/PSEEAPList.hpp-arc  $
//
//   Rev 1.2   Jun 11 2010 06:28:26   kitticha
//PETP0165541 FN02 IN#2123752 - PSE Fix. Remove previous rev logic.
//
//   Rev 1.1   Jun 04 2010 03:21:28   kitticha
//IN#2123752 - Additional logic and validation for PSE.
//
//   Rev 1.0   Apr 21 2010 17:22:08   popescu
//Initial revision.
 **/
