#pragma once

#include "ConditionObject.h"

namespace CND
{
	class CIFast_IFast_ifastdbrkr_err_account_splitcomm_not_found : public CConditionObject
	{
	public:
		CIFast_IFast_ifastdbrkr_err_account_splitcomm_not_found() { }
		~CIFast_IFast_ifastdbrkr_err_account_splitcomm_not_found() { }

	public:
		// General
		virtual DString GetConditionName() const { return DString(I_("ERR_ACCOUNT_SPLITCOMM_NOT_FOUND")); }
		virtual DString GetGroupName() const { return DString(I_("iFast")); }
		virtual DString GetModuleName() const { return DString(I_("ifastdbrkr")); }
		virtual int GetSeverity() const { return 6; }

		// Messages
		virtual DString GetMessage_EN_US() const { return DString(I_("Account level split commissions not found.")); }
		virtual DString GetMessage_DE_DE() const { return DString(I_("Eintrag für verteilte Agenturvergütung auf Konto-Level nicht gefunden.")); }
		virtual DString GetMessage_ES_ES() const { return DString(I_("No se encontraron comisiones divididas a nivel de la cuenta.")); }
		virtual DString GetMessage_FR_CA() const { return DString(I_("Le partage de commission au niveau du compte est introuvable.")); }
		virtual DString GetMessage_NL_NL() const { return DString(I_("Gedeelde commissies op accountniveau zijn niet gevonden")); }

        // Actions
	};
}



