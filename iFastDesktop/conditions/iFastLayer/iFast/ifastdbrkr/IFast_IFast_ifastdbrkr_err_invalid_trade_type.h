#pragma once

#include "ConditionObject.h"

namespace CND
{
	class CIFast_IFast_ifastdbrkr_err_invalid_trade_type : public CConditionObject
	{
	public:
		CIFast_IFast_ifastdbrkr_err_invalid_trade_type() { }
		~CIFast_IFast_ifastdbrkr_err_invalid_trade_type() { }

	public:
		// General
		virtual DString GetConditionName() const { return DString(I_("ERR_INVALID_TRADE_TYPE")); }
		virtual DString GetGroupName() const { return DString(I_("iFast")); }
		virtual DString GetModuleName() const { return DString(I_("ifastdbrkr")); }
		virtual int GetSeverity() const { return 6; }

		// Messages
		virtual DString GetMessage_EN_US() const { return DString(I_("Invalid Trade Type")); }
		virtual DString GetMessage_FR_CA() const { return DString(I_("Type de transaction invalide")); }

        // Actions
	};
}



