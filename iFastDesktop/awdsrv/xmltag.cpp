//******************************************************************************
//
// COPYRIGHT:
//
//    The computer systems, procedures, data bases and
//    programs created and maintained by International Financial Data Services,
//    are proprietary in nature and as such are confidential.
//    Any unauthorized use or disclosure of such information
//    may result in civil liabilities.
//
//    Copyright 2005 by International Financial Data Services
//
//
//******************************************************************************
//******************************************************************************
//
// ^FILE   : awdxml.cpp
// ^AUTHOR : Yingbao Li
// ^DATE   : Oct. 21, 2005
//
// ^CLASS    :
// ^SUBCLASS :
//
// ^CLASS DESCRIPTION :
//********************************************************************************
#include "stdafx.h"
namespace awdxml
{
   // Trace literals
   extern char * const package                      =  "iFAST_Package" ;
   extern char * const userId                       = "UserId" ;
   extern char * const userPassword                 = "UserPassword" ;
   extern char * const companyId                    = "CompanyId" ;
   extern char * const language                     = "Language" ;
   extern char * const logoff                       =  "Logoff" ;
   extern char * const batch                        =  "Batch" ;
   extern char * const classtag                     =  "class" ;
   extern char * const yes                          =  "yes" ;
   extern char * const no                           =  "no" ;
   extern char * const y_string                     =  "Y" ;
   extern char * const n_string                     =  "N" ;
   extern char * const format                       =  "formatted" ;
   extern char * const id                           =  "id" ;
   extern char * const ignoreWarnings               =  "ignoreWarnings" ;
   extern char * const accountNum                   =  "AccountNum" ;
   extern char * const parm                         =  "parm" ;
   extern char * const mailing                      =  "Mailing" ;
   extern char * const process                      =  "process" ; 
   extern char * const action                       =  "action" ; 
   extern char * const submit                       =  "submit" ; 
   extern char * const update                       =  "update" ;   
   extern char * const cbo                          =  "cbo" ; 
   extern char * const key                          =  "key" ; 
   extern char * const mailingKey                   =  "MailingKey" ; 
   extern char * const annlRptsHold                 =  "AnnlRptsHold" ;
   extern char * const annlMRFPHold                 =  "AnnlMRFPHold" ;
   extern char * const smAnnlMRFPHold               =  "SmAnnlMRFPHold" ;
   extern char * const semiAnnualOnHold             =  "SemiAnnualOnHold" ;
   extern char * const field                        =  "field" ;
}

namespace LOBName
{
   extern char * const ACCOUNT_NUM                  =  "ACCT" ;
   extern char * const COMPANY_ID                   =  "UNIT" ;
   extern char * const STATUS                       =  "STAT" ;
   extern char * const FUND_GROUP                   =  "FUND" ;
   extern char * const WORK_TYPE                    =  "WRKT" ;
}
//******************************************************************************
//              Revision Control Entries
//******************************************************************************
//
/* $Log:   Y:/VCS/BF iFAST/awdsrv/xmltag.cpp-arc  $
// 
//    Rev 1.1   Nov 08 2005 14:17:58   yingbaol
// PET1332,FN09: Remove DString and Infra structure
// 
//    Rev 1.0   Oct 31 2005 15:00:54   yingbaol
// Initial revision.
 * 
 *

 */


