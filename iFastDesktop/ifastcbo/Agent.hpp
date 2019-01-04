#pragma once
//******************************************************************************
//
// COPYRIGHT:
//
//    The computer systems, procedures, data bases and
//    programs created and maintained by International Financial.,
//    are proprietary in nature and as such are confidential.
//    Any unauthorized use or disclosure of such information
//    may result in civil liabilities.
//
//    Copyright 2003 by International Financial.
//
//
//******************************************************************************
//
// ^FILE   : Agent.hpp
// ^AUTHOR : 
// ^DATE   : Mar 04, 2003
//
// ^CLASS    : Agent
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

class IFASTCBO_LINKAGE Agent : public MFCanBFCbo, private boost::noncopyable
{

public:   
   //****************************************************************************
   // Constructor
   //****************************************************************************
   Agent( BFAbstractCBO &parent );

   //****************************************************************************
   // Destructor
   //****************************************************************************
   ~Agent();   

   //****************************************************************************
   //Initializes the CBO
   //@param const BFData& InstData - Data object to attach to AgentList.
   //@returns SEVERITY
   //****************************************************************************
   SEVERITY init( const BFData& InstData ); 

   //****************************************************************************
   //Compares the date passed in with the effective and stop date of the Agent.
   //Returns NO_CONDITION when the date passed in is within the effective and stop
   //date range.
   //@param const DString& dstAsOfDate - Date to compare to.
   //       const BFDataGroupId& idDataGroup - current data group id.
   //@returns SEVERITY - ERR_AGENT_INVALID_AS_OF_DATE - date is later than stop date
   //                    ERR_AGENT_NOT_EFFECTIVE - date is before effective date.
   //****************************************************************************
   SEVERITY checkEffective( const DString& dstrAsOfDate, const BFDataGroupId& idDataGroup );
   SEVERITY canCreateAccount( const BFDataGroupId& idDataGroup, bool bCheckLevel );
   SEVERITY canPurchase( const BFDataGroupId& idDataGroup, bool bCheckLevel );
};

//******************************************************************************
//              Revision Control Entries
//******************************************************************************
//
/* $Log:   Y:/VCS/BF iFAST/ifastcbo/Agent.hpp-arc  $
//
//   Rev 1.2   Aug 19 2003 09:07:24   HSUCHIN
//added canCreateAccount/canPurchase level check
//
//   Rev 1.1   Mar 21 2003 17:56:54   PURDYECH
//BFDataGroupId/BFContainerId changeover
//
//   Rev 1.0   Mar 05 2003 12:04:40   HSUCHIN
//Initial revision.
 */