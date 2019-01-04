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
//    AUTHOR : Cristina Oltean
//    DATE   : Jan, 2001
//
//
//    Copyright 1997 by DST Systems, Inc.
//
//******************************************************************************


#include <bfproc\AbstractProcess.hpp>
///#endif


// Import/Export resolution
#undef IFASTBP_LINKAGE
#ifdef IFASTBP_DLL
   #define IFASTBP_LINKAGE CLASS_EXPORT
#else
   #define IFASTBP_LINKAGE CLASS_IMPORT
#endif

class Availability;

class IFASTBP_LINKAGE AvailabilityProcess : public AbstractProcess
{
public:

//CP20030319   AvailabilityProcess();
   AvailabilityProcess( GenericInterfaceContainer* pGIC, GenericInterface* pGIParent, const Command& rCommand );
   virtual ~AvailabilityProcess();


protected:

   virtual SEVERITY doInit();
   virtual E_COMMANDRETURN doProcess();
private:
   Availability* _pAvailability;   

};

///#endif // AvailabilityProcess_hpp
