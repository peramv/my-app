#pragma once

#include "ConditionObject.h"

namespace CND
{
	class CIFast_IFast_ifastdbrkr_err_invalid_custom_trading_schd : public CConditionObject
	{
	public:
		CIFast_IFast_ifastdbrkr_err_invalid_custom_trading_schd() { }
		~CIFast_IFast_ifastdbrkr_err_invalid_custom_trading_schd() { }

	public:
		// General
		virtual DString GetConditionName() const { return DString(I_("ERR_INVALID_CUSTOM_TRADING_SCHD")); }
		virtual DString GetGroupName() const { return DString(I_("iFast")); }
		virtual DString GetModuleName() const { return DString(I_("ifastdbrkr")); }
		virtual int GetSeverity() const { return 6; }

		// Messages
		virtual DString GetMessage_EN_US() const { return DString(I_("Invalid custom trading schedule.")); }
		virtual DString GetMessage_FR_CA() const { return DString(I_("Le tableau d'opérations personnalisées est invalide.")); }

        // Actions
	};
}



