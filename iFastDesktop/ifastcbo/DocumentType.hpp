#define DISABLE_MACRO_REDEFINITION_WARNINGS 1

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
//    Copyright 2005 by IFDS.
//
//
//******************************************************************************
//
// ^FILE   : DocumentType.hpp
// ^AUTHOR : Yingbao Li
// ^DATE   : 09/02/2005
//
//
//******************************************************************************

#include <ifastcbo\mfcancbo.hpp>
#include <boost\utility.hpp>


namespace DocType
{
   extern CLASS_IMPORT I_CHAR * const CONFIRMATION;
   extern CLASS_IMPORT I_CHAR * const STATEMENT;
   extern CLASS_IMPORT I_CHAR * const NON_FINANCIAL_CONFIRM;
   extern CLASS_IMPORT I_CHAR * const CONTRACT_NOTES;
   extern CLASS_IMPORT I_CHAR * const DIVIDEND_CONFIRM;
   extern CLASS_IMPORT I_CHAR * const DIVIDEND_CHEQUE;
   extern CLASS_IMPORT I_CHAR * const CERTIFICATE;
   extern CLASS_IMPORT I_CHAR * const TAX_RECEIPT;
   extern CLASS_IMPORT I_CHAR * const LETTERS;
   extern CLASS_IMPORT I_CHAR * const ANNUAL_REPORT;
   extern CLASS_IMPORT I_CHAR * const PROSPECTUSES;
   extern CLASS_IMPORT I_CHAR * const ADDITIONAL_CONFIRM;
   extern CLASS_IMPORT I_CHAR * const ADDITIONAL_STATEMENT;
   extern CLASS_IMPORT I_CHAR * const REGISTER;
   extern CLASS_IMPORT I_CHAR * const BENEFICIAL_OWNER;
   extern CLASS_IMPORT I_CHAR * const SEMI_ANNUAL_REPORT;
   extern CLASS_IMPORT I_CHAR * const CONTRIBUTION_RECEIPT;
   extern CLASS_IMPORT I_CHAR * const ANNUAL_MRFP;
   extern CLASS_IMPORT I_CHAR * const SEMI_ANNUAL_MRFP;
}

namespace DELIVER_OPTION
{
   extern CLASS_IMPORT I_CHAR * const MAIL;
   extern CLASS_IMPORT I_CHAR * const EMAIL;
   extern CLASS_IMPORT I_CHAR * const FAX;
   extern CLASS_IMPORT I_CHAR * const CD;
   extern CLASS_IMPORT I_CHAR * const EPOST;
}

