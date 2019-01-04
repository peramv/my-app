﻿#pragma once

#include "ConditionObject.h"

namespace CND
{
	class CIFast_IFast_ifastcbo_err_sale_rep_is_not_eligible_for_fund_class : public CConditionObject
	{
	public:
		CIFast_IFast_ifastcbo_err_sale_rep_is_not_eligible_for_fund_class() { }
		~CIFast_IFast_ifastcbo_err_sale_rep_is_not_eligible_for_fund_class() { }

	public:
		// General
		virtual DString GetConditionName() const { return DString(I_("ERR_SALE_REP_IS_NOT_ELIGIBLE_FOR_FUND_CLASS")); }
		virtual DString GetGroupName() const { return DString(I_("iFast")); }
		virtual DString GetModuleName() const { return DString(I_("ifastcbo")); }
		virtual int GetSeverity() const { return 6; }

		// Messages
		virtual DString GetMessage_EN_US() const { return DString(I_("Fund %FUND%, class %CLASS% is not eligible for agent %SLSREP_CODE%.")); }
		virtual DString GetMessage_FR_CA() const { return DString(I_("Le fonds %FUND% et la classe %CLASS% ne sont pas admissibles pour l'agent %SLSREP_CODE%.")); }

        // Actions
	};
}