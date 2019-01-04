#pragma once

#include "ConditionObject.h"

namespace CND
{
	class CIFast_IFast_ifastcbo_err_stop_flag_active_ignored : public CConditionObject
	{
	public:
		CIFast_IFast_ifastcbo_err_stop_flag_active_ignored() { }
		~CIFast_IFast_ifastcbo_err_stop_flag_active_ignored() { }

	public:
		// General
		virtual DString GetConditionName() const { return DString(I_("ERR_STOP_FLAG_ACTIVE_IGNORED")); }
		virtual DString GetGroupName() const { return DString(I_("iFast")); }
		virtual DString GetModuleName() const { return DString(I_("ifastcbo")); }
		virtual int GetSeverity() const { return 5; }

		// Messages
		virtual DString GetMessage_EN_US() const { return DString(I_("Account FC re-balance Stop Flag is active, but ignored for this group.")); }
		virtual DString GetMessage_FR_FR() const { return DString(I_("Account FC re-balance Stop Flag is active, but ignored for this group.")); }
		virtual DString GetMessage_DE_DE() const { return DString(I_("Stopp-Kennzeichen für Konto FC-Neuausgleich ist aktiv, wird aber für diese Gruppe ignoriert.")); }
		virtual DString GetMessage_ES_ES() const { return DString(I_("El flag de detención de rebalanceo FC de la cuenta está activo pero no se tiene en cuenta para este grupo.")); }
		virtual DString GetMessage_FR_CA() const { return DString(I_("Le signal d'arrêt de rebalancement de monnaie étrangère du compte est actif, mais ignoré pour ce groupe.")); }
		virtual DString GetMessage_NL_NL() const { return DString(I_("Eindvlag voor nieuwe saldering buitenlandse inhoud van account is actief, maar wordt genegeerd voor deze groep")); }

        // Actions
	};
}



