﻿#pragma once

#include "ConditionObject.h"

namespace CND
{
	class CIFast_IFast_ifastdbrkr_err_erjd_exists : public CConditionObject
	{
	public:
		CIFast_IFast_ifastdbrkr_err_erjd_exists() { }
		~CIFast_IFast_ifastdbrkr_err_erjd_exists() { }

	public:
		// General
		virtual DString GetConditionName() const { return DString(I_("IFASTDBRKR_ERR_ERJD_EXISTS")); }
		virtual DString GetGroupName() const { return DString(I_("iFast")); }
		virtual DString GetModuleName() const { return DString(I_("ifastdbrkr")); }
		virtual int GetSeverity() const { return 6; }

		// Messages
		virtual DString GetMessage_EN_US() const { return DString(I_("Active ERJD exists for tax payer for the certificate jurisdiction.")); }
		virtual DString GetMessage_FR_CA() const { return DString(I_("Active ERJD exists for tax payer for the certificate jurisdiction.")); }

        // Actions
	};
}



