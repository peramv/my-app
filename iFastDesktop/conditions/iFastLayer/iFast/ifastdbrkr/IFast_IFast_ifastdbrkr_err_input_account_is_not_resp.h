#pragma once

#include "ConditionObject.h"

namespace CND
{
	class CIFast_IFast_ifastdbrkr_err_input_account_is_not_resp : public CConditionObject
	{
	public:
		CIFast_IFast_ifastdbrkr_err_input_account_is_not_resp() { }
		~CIFast_IFast_ifastdbrkr_err_input_account_is_not_resp() { }

	public:
		// General
		virtual DString GetConditionName() const { return DString(I_("ERR_INPUT_ACCOUNT_IS_NOT_RESP")); }
		virtual DString GetGroupName() const { return DString(I_("iFast")); }
		virtual DString GetModuleName() const { return DString(I_("ifastdbrkr")); }
		virtual int GetSeverity() const { return 6; }

		// Messages
		virtual DString GetMessage_EN_US() const { return DString(I_("Input Account is not an RESP account.")); }
		virtual DString GetMessage_FR_FR() const { return DString(I_("Input Account is not an RESP account.")); }
		virtual DString GetMessage_DE_DE() const { return DString(I_("Eingabe-Konto ist kein RESP-Konto")); }
		virtual DString GetMessage_ES_ES() const { return DString(I_("La cuenta introducida no es una cuenta RESP")); }
		virtual DString GetMessage_FR_CA() const { return DString(I_("Le compte saisi n'est pas un compte REEE.")); }
		virtual DString GetMessage_NL_NL() const { return DString(I_("Ingevoerd account is geen RESP-account")); }

        // Actions
	};
}



