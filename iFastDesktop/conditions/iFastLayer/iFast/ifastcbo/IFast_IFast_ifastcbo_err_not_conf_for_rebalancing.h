#pragma once

#include "ConditionObject.h"

namespace CND
{
	class CIFast_IFast_ifastcbo_err_not_conf_for_rebalancing : public CConditionObject
	{
	public:
		CIFast_IFast_ifastcbo_err_not_conf_for_rebalancing() { }
		~CIFast_IFast_ifastcbo_err_not_conf_for_rebalancing() { }

	public:
		// General
		virtual DString GetConditionName() const { return DString(I_("ERR_NOT_CONF_FOR_REBALANCING")); }
		virtual DString GetGroupName() const { return DString(I_("iFast")); }
		virtual DString GetModuleName() const { return DString(I_("ifastcbo")); }
		virtual int GetSeverity() const { return 6; }

		// Messages
		virtual DString GetMessage_EN_US() const { return DString(I_("Tax Type %TAX_TYPE% accounts not configured for FC re-balancing.")); }
		virtual DString GetMessage_FR_FR() const { return DString(I_("Tax Type %TAX_TYPE% accounts not configured for FC re-balancing.")); }
		virtual DString GetMessage_DE_DE() const { return DString(I_("Steuerart %TAX_TYPE%-Konten nicht konfiguriert für FC-Neu-Ausgleich.")); }
		virtual DString GetMessage_ES_ES() const { return DString(I_("Las cuentas de tipo tributario %TAX_TYPE% no están configuradas para rebalanceo FC.")); }
		virtual DString GetMessage_FR_CA() const { return DString(I_("Les comptes dont le type d'imposition est %TAX_TYPE% ne sont pas configurés pour le rebalancement de monnaie étrangère.")); }
		virtual DString GetMessage_NL_NL() const { return DString(I_("Accounts met belastingtype %TAX_TYPE% zijn niet geconfigureerd voor nieuwe saldering buitenlandse inhoud")); }

        // Actions
	};
}



