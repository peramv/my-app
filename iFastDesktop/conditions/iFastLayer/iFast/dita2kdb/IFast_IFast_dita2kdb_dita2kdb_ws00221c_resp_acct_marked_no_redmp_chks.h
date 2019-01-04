#pragma once

#include "ConditionObject.h"

namespace CND
{
	class CIFast_IFast_dita2kdb_dita2kdb_ws00221c_resp_acct_marked_no_redmp_chks : public CConditionObject
	{
	public:
		CIFast_IFast_dita2kdb_dita2kdb_ws00221c_resp_acct_marked_no_redmp_chks() { }
		~CIFast_IFast_dita2kdb_dita2kdb_ws00221c_resp_acct_marked_no_redmp_chks() { }

	public:
		// General
		virtual DString GetConditionName() const { return DString(I_("DITA2KDB_WS00221C_RESP_ACCT_MARKED_NO_REDMP_CHKS")); }
		virtual DString GetGroupName() const { return DString(I_("iFast")); }
		virtual DString GetModuleName() const { return DString(I_("dita2kdb")); }
		virtual int GetSeverity() const { return 6; }

		// Messages
		virtual DString GetMessage_EN_US() const { return DString(I_("Certificate is not applicable to %FUND% and %CLASS%.")); }
		virtual DString GetMessage_FR_FR() const { return DString(I_("Certificate is not applicable to %FUND% and %CLASS%.")); }
		virtual DString GetMessage_DE_DE() const { return DString(I_("Zertifikat ist nicht anwendbar auf  %FUND% und  %CLASS%.")); }
		virtual DString GetMessage_ES_ES() const { return DString(I_("El certificado no es aplicable a %FUND% y %CLASS")); }
		virtual DString GetMessage_FR_CA() const { return DString(I_("Le certificat ne s'applique pas au %FUND% et à la %CLASS%.")); }
		virtual DString GetMessage_NL_NL() const { return DString(I_("Certificaat is niet van toepassing op %FUND% en %CLASS")); }

        // Actions
	};
}



