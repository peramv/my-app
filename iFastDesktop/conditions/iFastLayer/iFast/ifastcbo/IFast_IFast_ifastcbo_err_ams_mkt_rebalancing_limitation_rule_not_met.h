#pragma once

#include "ConditionObject.h"

namespace CND
{
	class CIFast_IFast_ifastcbo_err_ams_mkt_rebalancing_limitation_rule_not_met : public CConditionObject
	{
	public:
		CIFast_IFast_ifastcbo_err_ams_mkt_rebalancing_limitation_rule_not_met() { }
		~CIFast_IFast_ifastcbo_err_ams_mkt_rebalancing_limitation_rule_not_met() { }

	public:
		// General
		virtual DString GetConditionName() const { return DString(I_("ERR_AMS_MKT_REBALANCING_LIMITATION_RULE_NOT_MET")); }
		virtual DString GetGroupName() const { return DString(I_("iFast")); }
		virtual DString GetModuleName() const { return DString(I_("ifastcbo")); }
		virtual int GetSeverity() const { return 6; }

		// Messages
		virtual DString GetMessage_EN_US() const { return DString(I_("Limitation rule, AMS market value rebalancing minimum is not met.")); }
		virtual DString GetMessage_DE_DE() const { return DString(I_("Limitation rule, AMS market value rebalancing minimum is not met.")); }
		virtual DString GetMessage_ES_ES() const { return DString(I_("Limitation rule, AMS market value rebalancing minimum is not met.")); }
		virtual DString GetMessage_FR_CA() const { return DString(I_("Règle de limitation, le minimum de rebalancement de la valeur du marché du service de gestion de portefeuille n'a pas été atteint.")); }

        // Actions
	};
}



