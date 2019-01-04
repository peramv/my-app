﻿#pragma once

#include "ConditionObject.h"

namespace CND
{
	class CIFast_IFast_ifastcbo_err_slsrep_less_than_min_init_red : public CConditionObject
	{
	public:
		CIFast_IFast_ifastcbo_err_slsrep_less_than_min_init_red() { }
		~CIFast_IFast_ifastcbo_err_slsrep_less_than_min_init_red() { }

	public:
		// General
		virtual DString GetConditionName() const { return DString(I_("ERR_SLSREP_LESS_THAN_MIN_INIT_RED")); }
		virtual DString GetGroupName() const { return DString(I_("iFast")); }
		virtual DString GetModuleName() const { return DString(I_("ifastcbo")); }
		virtual int GetSeverity() const { return 6; }

		// Messages
		virtual DString GetMessage_EN_US() const { return DString(I_("Sales Rep: Less than minimum Initial Redemption")); }
		virtual DString GetMessage_FR_CA() const { return DString(I_("Sales Rep: Less than minimum Initial Redemption")); }

        // Actions
	};
}