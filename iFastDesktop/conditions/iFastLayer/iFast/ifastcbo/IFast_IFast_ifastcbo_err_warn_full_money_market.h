#pragma once

#include "ConditionObject.h"

namespace CND
{
	class CIFast_IFast_ifastcbo_err_warn_full_money_market : public CConditionObject
	{
	public:
		CIFast_IFast_ifastcbo_err_warn_full_money_market() { }
		~CIFast_IFast_ifastcbo_err_warn_full_money_market() { }

	public:
		// General
		virtual DString GetConditionName() const { return DString(I_("ERR_WARN_FULL_MONEY_MARKET")); }
		virtual DString GetGroupName() const { return DString(I_("iFast")); }
		virtual DString GetModuleName() const { return DString(I_("ifastcbo")); }
		virtual int GetSeverity() const { return 5; }

		// Messages
		virtual DString GetMessage_EN_US() const { return DString(I_("All Full Money Market redemptions must include undistributed income.")); }
		virtual DString GetMessage_DE_DE() const { return DString(I_("Alle Vollen Geldmarkt-Tilgungen müssen unverteilte Erträge enthalten.")); }
		virtual DString GetMessage_ES_ES() const { return DString(I_("Todos los rescates totales de fondos del mercado monetario deben incluir ingresos no distribuidos.")); }
		virtual DString GetMessage_FR_CA() const { return DString(I_("Tous les rachats totaux du marché monétaire doivent comprendre du revenu non réparti.")); }
		virtual DString GetMessage_NL_NL() const { return DString(I_("Alle volledige aflossingen voor de geldmarkt moeten niet-gedistribueerd inkomen bevatten")); }

        // Actions
	};
}



