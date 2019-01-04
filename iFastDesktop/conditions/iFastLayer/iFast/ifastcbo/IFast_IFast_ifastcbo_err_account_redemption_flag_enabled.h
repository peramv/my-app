#pragma once

#include "ConditionObject.h"

namespace CND
{
	class CIFast_IFast_ifastcbo_err_account_redemption_flag_enabled : public CConditionObject
	{
	public:
		CIFast_IFast_ifastcbo_err_account_redemption_flag_enabled() { }
		~CIFast_IFast_ifastcbo_err_account_redemption_flag_enabled() { }

	public:
		// General
		virtual DString GetConditionName() const { return DString(I_("ERR_ACCOUNT_REDEMPTION_FLAG_ENABLED")); }
		virtual DString GetGroupName() const { return DString(I_("iFast")); }
		virtual DString GetModuleName() const { return DString(I_("ifastcbo")); }
		virtual int GetSeverity() const { return 6; }

		// Messages
		virtual DString GetMessage_EN_US() const { return DString(I_("Account stop redemption flag is turned on.")); }
		virtual DString GetMessage_DE_DE() const { return DString(I_("Konto-Stop-Tilgungskennzeichen ist aktiviert")); }
		virtual DString GetMessage_ES_ES() const { return DString(I_("La cuenta tiene el flag de detención de rescate activado.")); }
		virtual DString GetMessage_FR_CA() const { return DString(I_("Le signal d'arrêt de rachat du compte est activé.")); }
		virtual DString GetMessage_NL_NL() const { return DString(I_("Vlag voor stoppen accountaflossing is ingeschakeld")); }

        // Actions
	};
}



