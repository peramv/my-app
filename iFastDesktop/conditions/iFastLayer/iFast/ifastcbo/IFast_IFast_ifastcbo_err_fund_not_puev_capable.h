﻿#pragma once

#include "ConditionObject.h"

namespace CND
{
	class CIFast_IFast_ifastcbo_err_fund_not_puev_capable : public CConditionObject
	{
	public:
		CIFast_IFast_ifastcbo_err_fund_not_puev_capable() { }
		~CIFast_IFast_ifastcbo_err_fund_not_puev_capable() { }

	public:
		// General
		virtual DString GetConditionName() const { return DString(I_("ERR_FUND_NOT_PUEV_CAPABLE")); }
		virtual DString GetGroupName() const { return DString(I_("iFast")); }
		virtual DString GetModuleName() const { return DString(I_("ifastcbo")); }
		virtual int GetSeverity() const { return 6; }

		// Messages
		virtual DString GetMessage_EN_US() const { return DString(I_("Fund is not PUEV capable.")); }
		virtual DString GetMessage_DE_DE() const { return DString(I_("Fund is not PUEV capable.")); }
		virtual DString GetMessage_FR_CA() const { return DString(I_("Le fonds ne supporte pas PUEV.")); }

        // Actions
	};
}



