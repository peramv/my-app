#pragma once

#include "ConditionObject.h"

namespace CND
{
	class CIFast_IFast_ifastdbrkr_err_eq_trade_cancel : public CConditionObject
	{
	public:
		CIFast_IFast_ifastdbrkr_err_eq_trade_cancel() { }
		~CIFast_IFast_ifastdbrkr_err_eq_trade_cancel() { }

	public:
		// General
		virtual DString GetConditionName() const { return DString(I_("ERR_EQ_TRADE_CANCEL")); }
		virtual DString GetGroupName() const { return DString(I_("iFast")); }
		virtual DString GetModuleName() const { return DString(I_("ifastdbrkr")); }
		virtual int GetSeverity() const { return 6; }

		// Messages
		virtual DString GetMessage_EN_US() const { return DString(I_("Equalisation trade cannot be cancelled individually.")); }
		virtual DString GetMessage_FR_CA() const { return DString(I_("La transaction d'égalisation ne peut être annulée individuellement.")); }

        // Actions
	};
}



