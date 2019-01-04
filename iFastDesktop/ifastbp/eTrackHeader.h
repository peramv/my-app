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
//    Copyright 2001 by DST Systems, Inc.
//
//******************************************************************************
//
// ^FILE   :  eTrackHeader.h
// ^AUTHOR :  Yingbao Li
// ^DATE   : 01/18/2001
//
//*******************************************************************************

// Import/Export resolution
#undef IFASTBP_LINKAGE
#ifdef IFASTBP_DLL
   #define IFASTBP_LINKAGE CLASS_EXPORT
#else
   #define IFASTBP_LINKAGE CLASS_IMPORT
#endif

namespace ETRACK
{
   extern IFASTBP_LINKAGE const I_CHAR * const TRACK;
   extern IFASTBP_LINKAGE const I_CHAR * const ACTIVITY;  
   extern IFASTBP_LINKAGE const I_CHAR * const YES_TRACK;    
   extern IFASTBP_LINKAGE const I_CHAR * const NO_TRACK;  

}

//******************************************************************************
//              Revision Control Entries
//******************************************************************************
//
/* $Log:   D:/scc/ifds/ifast/archives/ifastbp/eTrackHeader.h-arc  $
//
//   Rev 1.3   Oct 09 2002 23:53:12   PURDYECH
//PVCS Database Conversion
//
//   Rev 1.2   22 May 2002 18:21:08   PURDYECH
//BFData Implementation
//
//   Rev 1.1   19 Mar 2002 13:17:00   PURDYECH
//Use #pragma once as include guard
//Remove compile time "including..." message
//
//   Rev 1.0   Jan 23 2001 15:16:24   YINGBAOL
//Initial revision.
 * 

 */