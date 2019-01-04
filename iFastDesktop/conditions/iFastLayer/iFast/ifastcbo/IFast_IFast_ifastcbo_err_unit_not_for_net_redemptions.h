#pragma once

#include "ConditionObject.h"

namespace CND
{
	class CIFast_IFast_ifastcbo_err_unit_not_for_net_redemptions : public CConditionObject
	{
	public:
		CIFast_IFast_ifastcbo_err_unit_not_for_net_redemptions() { }
		~CIFast_IFast_ifastcbo_err_unit_not_for_net_redemptions() { }

	public:
		// General
		virtual DString GetConditionName() const { return DString(I_("ERR_UNIT_NOT_FOR_NET_REDEMPTIONS")); }
		virtual DString GetGroupName() const { return DString(I_("iFast")); }
		virtual DString GetModuleName() const { return DString(I_("ifastcbo")); }
		virtual int GetSeverity() const { return 6; }

		// Messages
		virtual DString GetMessage_EN_US() const { return DString(I_("Unit values cannot be entered for Net redemptions.")); }
		virtual DString GetMessage_DE_DE() const { return DString(I_("Anteilwerte können nicht für Nettotilgungen eingegeben werden.")); }
		virtual DString GetMessage_ES_ES() const { return DString(I_("No pueden introducirse los valores de las unidades para rescates netos.")); }
		virtual DString GetMessage_FR_CA() const { return DString(I_("Les valeurs d'unités ne peuvent pas être saisies pour les rachats nets.")); }
		virtual DString GetMessage_NL_NL() const { return DString(I_("Er kunnen geen eenheidswaarden worden opgegeven voor netto aflossingen")); }

        // Actions
	};
}



