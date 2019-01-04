#pragma once

#include "ConditionObject.h"

namespace CND
{
	class CIFast_IFast_ifastcbo_err_acctowner_sin_invalid : public CConditionObject
	{
	public:
		CIFast_IFast_ifastcbo_err_acctowner_sin_invalid() { }
		~CIFast_IFast_ifastcbo_err_acctowner_sin_invalid() { }

	public:
		// General
		virtual DString GetConditionName() const { return DString(I_("ERR_ACCTOWNER_SIN_INVALID")); }
		virtual DString GetGroupName() const { return DString(I_("iFast")); }
		virtual DString GetModuleName() const { return DString(I_("ifastcbo")); }
		virtual int GetSeverity() const { return 5; }

		// Messages
		virtual DString GetMessage_EN_US() const { return DString(I_("Account owner's SIN is invalid.")); }
		virtual DString GetMessage_DE_DE() const { return DString(I_("Die SIN des Kontoinhabers ist ungültig.")); }
		virtual DString GetMessage_ES_ES() const { return DString(I_("El SIN del propietario de la cuenta no es válido.")); }
		virtual DString GetMessage_FR_CA() const { return DString(I_("Le NAS du titulaire du compte est invalide.")); }
		virtual DString GetMessage_NL_NL() const { return DString(I_("SIN van accounthouder is ongeldig")); }

        // Actions
	};
}



