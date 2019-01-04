#pragma once

#include "ConditionObject.h"

namespace CND
{
	class CIFast_IFast_ifastcbo_err_guarantee_fee_trade_not_allowed : public CConditionObject
	{
	public:
		CIFast_IFast_ifastcbo_err_guarantee_fee_trade_not_allowed() { }
		~CIFast_IFast_ifastcbo_err_guarantee_fee_trade_not_allowed() { }

	public:
		// General
		virtual DString GetConditionName() const { return DString(I_("ERR_GUARANTEE_FEE_TRADE_NOT_ALLOWED")); }
		virtual DString GetGroupName() const { return DString(I_("iFast")); }
		virtual DString GetModuleName() const { return DString(I_("ifastcbo")); }
		virtual int GetSeverity() const { return 6; }

		// Messages
		virtual DString GetMessage_EN_US() const { return DString(I_("Not allowed to enter a guarantee fee.")); }
		virtual DString GetMessage_FR_CA() const { return DString(I_("La saisie de frais de garantie n'est pas autorisée.")); }

        // Actions
	};
}



