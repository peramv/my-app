#pragma once
#undef IFASTBP_LINKAGE
#ifdef IFASTBP_DLL
   #define IFASTBP_LINKAGE CLASS_EXPORT
#else
   #define IFASTBP_LINKAGE CLASS_IMPORT
#endif
//******************************************************************************
//
// COPYRIGHT:
//
//    The computer systems, procedures, data bases and
//    programs created and maintained by International Financial, Inc.,
//    are proprietary in nature and as such are confidential.
//    Any unauthorized use or disclosure of such information
//    may result in civil liabilities.
//
//    Copyright 2002 by International Financial, Inc.
//
//******************************************************************************

namespace IFASTBP_PROC
{
//   extern IFASTBP_LINKAGE const BFContainerId FTPINFO;
}
namespace ifds
{
   extern CLASS_IMPORT const BFTextFieldId User_Id;
   extern CLASS_IMPORT const BFTextFieldId Password;
   extern CLASS_IMPORT const BFTextFieldId FTPSite;
   extern CLASS_IMPORT const BFTextFieldId FTPPort;
}

namespace FTP
{
   const I_CHAR * const FTPSITE = I_( "FtpSite" );   
   const I_CHAR * const FTPPORT = I_( "FtpPort" );
   const I_CHAR * const USERID = I_( "UserId" );
   const I_CHAR * const PWD = I_( "PassWord" );
//CP20030319   const int FTPINFO = 0;
}

//******************************************************************************
//              Revision Control Entries
//******************************************************************************
//
/* $Log:   Y:/VCS/BF iFAST/ifastbp/FTPLogonProcessIncludes.h-arc  $
//
//   Rev 1.2   Jun 05 2003 15:41:24   HERNANDO
//PTS 10017935 - Removed extern.
//
//   Rev 1.1   Mar 21 2003 17:40:16   PURDYECH
//BFDataGroupId/BFContainerId changeover
//
//   Rev 1.0   Dec 10 2002 09:52:14   HSUCHIN
//Initial Revision
 */
