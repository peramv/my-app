#pragma once

#include "ConditionObject.h"

namespace CND
{
	class CIFast_IFast_ifastcbo_err_fund_cannotbe_dif : public CConditionObject
	{
	public:
		CIFast_IFast_ifastcbo_err_fund_cannotbe_dif() { }
		~CIFast_IFast_ifastcbo_err_fund_cannotbe_dif() { }

	public:
		// General
		virtual DString GetConditionName() const { return DString(I_("ERR_FUND_CANNOTBE_DIF")); }
		virtual DString GetGroupName() const { return DString(I_("iFast")); }
		virtual DString GetModuleName() const { return DString(I_("ifastcbo")); }
		virtual int GetSeverity() const { return 6; }

		// Messages
		virtual DString GetMessage_EN_US() const { return DString(I_("Fund category cannot be DIF.")); }
		virtual DString GetMessage_FR_CA() const { return DString(I_("La catégorie de fonds ne peut pas être FIQ.")); }

        // Actions
	};
}



