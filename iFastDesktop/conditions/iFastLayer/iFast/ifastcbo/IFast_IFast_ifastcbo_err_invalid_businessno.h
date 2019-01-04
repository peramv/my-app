#pragma once

#include "ConditionObject.h"

namespace CND
{
	class CIFast_IFast_ifastcbo_err_invalid_businessno : public CConditionObject
	{
	public:
		CIFast_IFast_ifastcbo_err_invalid_businessno() { }
		~CIFast_IFast_ifastcbo_err_invalid_businessno() { }

	public:
		// General
		virtual DString GetConditionName() const { return DString(I_("ERR_INVALID_BUSINESSNO")); }
		virtual DString GetGroupName() const { return DString(I_("iFast")); }
		virtual DString GetModuleName() const { return DString(I_("ifastcbo")); }
		virtual int GetSeverity() const { return 6; }

		// Messages
		virtual DString GetMessage_EN_US() const { return DString(I_("Invalid Business number. The format of a valid Business No is 999999999-XX-9999, where the first 9 digits represent a valid SIN no.")); }
		virtual DString GetMessage_DE_DE() const { return DString(I_("Invalid Business number.")); }
		virtual DString GetMessage_ES_ES() const { return DString(I_("Invalid Business number.")); }
		virtual DString GetMessage_FR_CA() const { return DString(I_("Numéro d'entreprise invalide. Le format de numéro d'entreprise valide est 999999999-XX-9999, les 9 premiers chiffres représentant un numéro de NAS valide.")); }

        // Actions
	};
}



