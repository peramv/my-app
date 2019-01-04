#pragma once

#include "ConditionObject.h"

namespace CND
{
	class CIFast_IFast_IFast_ifastdbrkr_err_trade_already_verified : public CConditionObject
	{
	public:
		CIFast_IFast_IFast_ifastdbrkr_err_trade_already_verified() { }
		~CIFast_IFast_IFast_ifastdbrkr_err_trade_already_verified() { }

	public:
		// General
		virtual DString GetConditionName() const { return DString(I_("ERR_TRADE_ALREADY_VERIFIED")); }
		virtual DString GetGroupName() const { return DString(I_("iFast")); }
		virtual DString GetModuleName() const { return DString(I_("ifastdbrkr")); }
		virtual int GetSeverity() const { return 6; }

		// Messages
		virtual DString GetMessage_EN_US() const { return DString(I_("Trade is already Verified.")); }
		virtual DString GetMessage_FR_CA() const { return DString(I_("Le commerce est déjà vérifié.")); }

        // Actions
	};
}