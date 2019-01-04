#pragma once

#include "ConditionObject.h"

namespace CND
{
	class CIFast_IFast_ifastcbo_warn_guarantee_adjustment_exists_after_trade_date_ina : public CConditionObject
	{
	public:
		CIFast_IFast_ifastcbo_warn_guarantee_adjustment_exists_after_trade_date_ina() { }
		~CIFast_IFast_ifastcbo_warn_guarantee_adjustment_exists_after_trade_date_ina() { }

	public:
		// General
		virtual DString GetConditionName() const { return DString(I_("WARN_GUARANTEE_ADJUSTMENT_EXISTS_AFTER_TRADE_DATE_INA")); }
		virtual DString GetGroupName() const { return DString(I_("iFast")); }
		virtual DString GetModuleName() const { return DString(I_("ifastcbo")); }
		virtual int GetSeverity() const { return 5; }

		// Messages
		virtual DString GetMessage_EN_US() const { return DString(I_("Guarantee Adjustment exists after Trade Date. Cancel GA transaction before backdating %TRANSTYPE%.")); }
		virtual DString GetMessage_FR_CA() const { return DString(I_("Un ajustement de garantie existe après la date de la transaction. Annuler l'ajustement avant d'antidater %TRANSTYPE%.")); }

        // Actions
	};
}



