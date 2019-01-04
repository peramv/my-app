#pragma once

#include "ConditionObject.h"

namespace CND
{
	class CIFast_IFast_ifastdbrkr_err_commision_exceed_fund_default_rate : public CConditionObject
	{
	public:
		CIFast_IFast_ifastdbrkr_err_commision_exceed_fund_default_rate() { }
		~CIFast_IFast_ifastdbrkr_err_commision_exceed_fund_default_rate() { }

	public:
		// General
		virtual DString GetConditionName() const { return DString(I_("ERR_COMMISION_EXCEED_FUND_DEFAULT_RATE")); }
		virtual DString GetGroupName() const { return DString(I_("iFast")); }
		virtual DString GetModuleName() const { return DString(I_("ifastdbrkr")); }
		virtual int GetSeverity() const { return 6; }

		// Messages
		virtual DString GetMessage_EN_US() const { return DString(I_("Commission rate of Broker/Branch/Salesman exceeds the fund default rate.")); }
		virtual DString GetMessage_FR_CA() const { return DString(I_("Le taux de commission du courtier/de l'unité de service/du représentant des ventes excède le taux par défaut du fonds.")); }

        // Actions
	};
}



