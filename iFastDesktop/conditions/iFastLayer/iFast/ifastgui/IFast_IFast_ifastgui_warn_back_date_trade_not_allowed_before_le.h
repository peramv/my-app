#pragma once

#include "ConditionObject.h"

namespace CND
{
	class CIFast_IFast_ifastgui_warn_back_date_trade_not_allowed_before_le : public CConditionObject
	{
	public:
		CIFast_IFast_ifastgui_warn_back_date_trade_not_allowed_before_le() { }
		~CIFast_IFast_ifastgui_warn_back_date_trade_not_allowed_before_le() { }

	public:
		// General
		virtual DString GetConditionName() const { return DString(I_("WARN_BACK_DATE_TRADE_NOT_ALLOWED_BEFORE_LE")); }
		virtual DString GetGroupName() const { return DString(I_("iFast")); }
		virtual DString GetModuleName() const { return DString(I_("ifastgui")); }
		virtual int GetSeverity() const { return 5; }

		// Messages
		virtual DString GetMessage_EN_US() const { return DString(I_("Cannot backdate trades before LE scheduled date")); }
		virtual DString GetMessage_FR_CA() const { return DString(I_("Impossible d'antidater des transactions avant l'option MRV.")); }

        // Actions
	};
}



