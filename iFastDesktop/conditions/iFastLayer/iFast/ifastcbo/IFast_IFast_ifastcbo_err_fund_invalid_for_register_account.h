#pragma once

#include "ConditionObject.h"

namespace CND
{
	class CIFast_IFast_ifastcbo_err_fund_invalid_for_register_account : public CConditionObject
	{
	public:
		CIFast_IFast_ifastcbo_err_fund_invalid_for_register_account() { }
		~CIFast_IFast_ifastcbo_err_fund_invalid_for_register_account() { }

	public:
		// General
		virtual DString GetConditionName() const { return DString(I_("ERR_FUND_INVALID_FOR_REGISTER_ACCOUNT")); }
		virtual DString GetGroupName() const { return DString(I_("iFast")); }
		virtual DString GetModuleName() const { return DString(I_("ifastcbo")); }
		virtual int GetSeverity() const { return 6; }

		// Messages
		virtual DString GetMessage_EN_US() const { return DString(I_("Fund invalid for registered account.")); }
		virtual DString GetMessage_FR_FR() const { return DString(I_("Fund invalid for registered account.")); }
		virtual DString GetMessage_DE_DE() const { return DString(I_("Fonds für Ausländerkonten ungültig")); }
		virtual DString GetMessage_ES_ES() const { return DString(I_("Fondo no válido para la cuenta registrada")); }
		virtual DString GetMessage_FR_CA() const { return DString(I_("Fonds invalide pour le compte enregistré")); }
		virtual DString GetMessage_NL_NL() const { return DString(I_("Fonds is ongeldig voor registeraccount")); }

        // Actions
	};
}



