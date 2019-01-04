#pragma once

#include "ConditionObject.h"

namespace CND
{
	class CIFast_IFast_ifastcbo_err_warn_cert_units_exists : public CConditionObject
	{
	public:
		CIFast_IFast_ifastcbo_err_warn_cert_units_exists() { }
		~CIFast_IFast_ifastcbo_err_warn_cert_units_exists() { }

	public:
		// General
		virtual DString GetConditionName() const { return DString(I_("ERR_WARN_CERT_UNITS_EXISTS")); }
		virtual DString GetGroupName() const { return DString(I_("iFast")); }
		virtual DString GetModuleName() const { return DString(I_("ifastcbo")); }
		virtual int GetSeverity() const { return 5; }

		// Messages
		virtual DString GetMessage_EN_US() const { return DString(I_("Warning: Certificate units %ISSUEUNITS% issued.")); }
		virtual DString GetMessage_DE_DE() const { return DString(I_("Warnung: Zertifikat-Anteile %ISSUEUNITS% herausgegeben")); }
		virtual DString GetMessage_ES_ES() const { return DString(I_("Advertencia: unidades de certificado %ISSUEUNITS% emitidas")); }
		virtual DString GetMessage_FR_CA() const { return DString(I_("Avertissement : unités de certificat %ISSUEUNITS% émises")); }
		virtual DString GetMessage_NL_NL() const { return DString(I_("Waarschuwing: Er zijn certificaateenheden %ISSUEUNITS% uitgegeven")); }

        // Actions
	};
}



