#pragma once

#include "ConditionObject.h"

namespace CND
{
	class CIFast_IFast_ifastcbo_err_spousal_consent_required : public CConditionObject
	{
	public:
		CIFast_IFast_ifastcbo_err_spousal_consent_required() { }
		~CIFast_IFast_ifastcbo_err_spousal_consent_required() { }

	public:
		// General
		virtual DString GetConditionName() const { return DString(I_("ERR_SPOUSAL_CONSENT_REQUIRED")); }
		virtual DString GetGroupName() const { return DString(I_("iFast")); }
		virtual DString GetModuleName() const { return DString(I_("ifastcbo")); }
		virtual int GetSeverity() const { return 6; }

		// Messages
		virtual DString GetMessage_EN_US() const { return DString(I_("Spousal consent required.")); }
		virtual DString GetMessage_DE_DE() const { return DString(I_("Zustimmung des Ehepartners erforderlich")); }
		virtual DString GetMessage_ES_ES() const { return DString(I_("Se requiere consentimiento conyugal.")); }
		virtual DString GetMessage_FR_CA() const { return DString(I_("Consentement du conjoint requis")); }
		virtual DString GetMessage_NL_NL() const { return DString(I_("Toestemming echtgenoot of echtgenote is vereist")); }

        // Actions
	};
}



