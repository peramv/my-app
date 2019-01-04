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
//    Copyright 2000 by DST Canada, Inc.
//
//
//******************************************************************************
//
// ^FILE   : FinInstRegDetlList.hpp
// ^AUTHOR : Aurkarn Mongkonrat
// ^DATE   : 04 June 2013
//
// ^CLASS    : FinInstRegDetlList
// ^SUBCLASS :
//
// ^CLASS DESCRIPTION :
//
//******************************************************************************


#include <ifastcbo\mfcancbo.hpp>
#include <boost\utility.hpp>
///#endif

class MgmtCoOptions;
class MFAccount;

#undef IFASTCBO_LINKAGE
#ifdef IFASTCBO_DLL
#define IFASTCBO_LINKAGE CLASS_EXPORT
#else
#define IFASTCBO_LINKAGE CLASS_IMPORT
#endif

class IFASTCBO_LINKAGE FinInstRegDetlList : public MFCanBFCbo, private boost::noncopyable
{
public:
   FinInstRegDetlList( BFAbstractCBO &parent );
   virtual ~FinInstRegDetlList( void );

   SEVERITY init (const DString &dstrComplyRule,
                  const BFDataGroupId& idDataGroup = BF::HOST,
                  const DString &dstrAcctNum = NULL_STRING,
                  const DString &dstrAcctDesignation = NULL_STRING,
                  const DString &dstrBrokerCode = NULL_STRING,
                  const DString &dstrInterCode = NULL_STRING,
                  const DString& dstrTrack = I_("N"), 
                  const DString& dstrPageName = NULL_STRING);

   void getFFIStartStopDate (const BFDataGroupId &idDataGroup, 
                             const DString &dstrFinInstRegDetlUUID,
                             DString &startDate, DString &stopDate);

protected:

private:

};
