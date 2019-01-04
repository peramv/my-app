#ifndef COMMONPORT_H
   #include <commonport.h>
#endif

//defines the user access function codes, retured by view#64
namespace DocType
{
   extern CLASS_EXPORT I_CHAR * const CONFIRMATION             = I_( "01" );
   extern CLASS_EXPORT I_CHAR * const STATEMENT                = I_( "02" );
   extern CLASS_EXPORT I_CHAR * const NON_FINANCIAL_CONFIRM    = I_( "03" );
   extern CLASS_EXPORT I_CHAR * const CONTRACT_NOTES           = I_( "04" );
   extern CLASS_EXPORT I_CHAR * const DIVIDEND_CONFIRM         = I_( "05" );
   extern CLASS_EXPORT I_CHAR * const DIVIDEND_CHEQUE          = I_( "06" );
   extern CLASS_EXPORT I_CHAR * const CERTIFICATE              = I_( "07" );
   extern CLASS_EXPORT I_CHAR * const TAX_RECEIPT              = I_( "08" );
   extern CLASS_EXPORT I_CHAR * const LETTERS                  = I_( "09" );
   extern CLASS_EXPORT I_CHAR * const ANNUAL_REPORT            = I_( "10" );
   extern CLASS_EXPORT I_CHAR * const PROSPECTUSES             = I_( "11" );
   extern CLASS_EXPORT I_CHAR * const ADDITIONAL_CONFIRM       = I_( "12" );
   extern CLASS_EXPORT I_CHAR * const ADDITIONAL_STATEMENT     = I_( "13" );
   extern CLASS_EXPORT I_CHAR * const REGISTER                 = I_( "14" );
   extern CLASS_EXPORT I_CHAR * const BENEFICIAL_OWNER         = I_( "15" );
   extern CLASS_EXPORT I_CHAR * const SEMI_ANNUAL_REPORT       = I_( "16" );
   extern CLASS_EXPORT I_CHAR * const CONTRIBUTION_RECEIPT     = I_( "19" );
   extern CLASS_EXPORT I_CHAR * const ANNUAL_MRFP              = I_( "20" );
   extern CLASS_EXPORT I_CHAR * const SEMI_ANNUAL_MRFP         = I_( "21" );
}
namespace DELIVER_OPTION
{
   extern CLASS_EXPORT I_CHAR * const MAIL                     = I_( "01" );
   extern CLASS_EXPORT I_CHAR * const EMAIL                    = I_( "02" );
   extern CLASS_EXPORT I_CHAR * const FAX                      = I_( "03" );
   extern CLASS_EXPORT I_CHAR * const CD                       = I_( "04" );
   extern CLASS_EXPORT I_CHAR * const EPOST                    = I_( "05" );
}
	


