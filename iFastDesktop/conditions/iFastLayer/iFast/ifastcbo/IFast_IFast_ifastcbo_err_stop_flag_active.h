#pragma once

#include "ConditionObject.h"

namespace CND
{
	class CIFast_IFast_ifastcbo_err_stop_flag_active : public CConditionObject
	{
	public:
		CIFast_IFast_ifastcbo_err_stop_flag_active() { }
		~CIFast_IFast_ifastcbo_err_stop_flag_active() { }

	public:
		// General
		virtual DString GetConditionName() const { return DString(I_("ERR_STOP_FLAG_ACTIVE")); }
		virtual DString GetGroupName() const { return DString(I_("iFast")); }
		virtual DString GetModuleName() const { return DString(I_("ifastcbo")); }
		virtual int GetSeverity() const { return 6; }

		// Messages
		virtual DString GetMessage_EN_US() const { return DString(I_("Account FC re-balance Stop Flag is active.")); }
		virtual DString GetMessage_FR_FR() const { return DString(I_("Account FC re-balance Stop Flag is active.")); }
		virtual DString GetMessage_DE_DE() const { return DString(I_("Stopp-Kennzeichen für Konto FC-Neuausgleich ist aktiv.")); }
		virtual DString GetMessage_ES_ES() const { return DString(I_("El flag de detención de rebalanceo FC de la cuenta está activo.")); }
		virtual DString GetMessage_FR_CA() const { return DString(I_("Le signal d'arrêt de rebalancement de monnaie étrangère du compte est actif.")); }
		virtual DString GetMessage_NL_NL() const { return DString(I_("Eindvlag voor nieuwe saldering buitenlandse inhoud van account is actief")); }

        // Actions
	};
}



