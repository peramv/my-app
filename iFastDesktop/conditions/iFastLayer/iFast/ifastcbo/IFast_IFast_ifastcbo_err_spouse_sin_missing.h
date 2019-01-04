#pragma once

#include "ConditionObject.h"

namespace CND
{
	class CIFast_IFast_ifastcbo_err_spouse_sin_missing : public CConditionObject
	{
	public:
		CIFast_IFast_ifastcbo_err_spouse_sin_missing() { }
		~CIFast_IFast_ifastcbo_err_spouse_sin_missing() { }

	public:
		// General
		virtual DString GetConditionName() const { return DString(I_("ERR_SPOUSE_SIN_MISSING")); }
		virtual DString GetGroupName() const { return DString(I_("iFast")); }
		virtual DString GetModuleName() const { return DString(I_("ifastcbo")); }
		virtual int GetSeverity() const { return 5; }

		// Messages
		virtual DString GetMessage_EN_US() const { return DString(I_("Spouse's social insurance number is missing")); }
		virtual DString GetMessage_DE_DE() const { return DString(I_("Die SIN des Ehepartners fehlt.")); }
		virtual DString GetMessage_ES_ES() const { return DString(I_("Falta el SIN del cónyuge.")); }
		virtual DString GetMessage_FR_CA() const { return DString(I_("Le NAS du conjoint est manquant.")); }
		virtual DString GetMessage_NL_NL() const { return DString(I_("SIN van echtgenoot of echtgenote ontbreekt")); }

        // Actions
	};
}



