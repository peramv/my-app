﻿#pragma once

#include "ConditionObject.h"

namespace CND
{
	class CIFast_IFast_ifastcbo_err_fund_not_lsif : public CConditionObject
	{
	public:
		CIFast_IFast_ifastcbo_err_fund_not_lsif() { }
		~CIFast_IFast_ifastcbo_err_fund_not_lsif() { }

	public:
		// General
		virtual DString GetConditionName() const { return DString(I_("ERR_FUND_NOT_LSIF")); }
		virtual DString GetGroupName() const { return DString(I_("iFast")); }
		virtual DString GetModuleName() const { return DString(I_("ifastcbo")); }
		virtual int GetSeverity() const { return 6; }

		// Messages
		virtual DString GetMessage_EN_US() const { return DString(I_("Fund is not LSIF")); }
		virtual DString GetMessage_DE_DE() const { return DString(I_("Fund is not LSIF")); }
		virtual DString GetMessage_FR_CA() const { return DString(I_("Le fonds n'est pas FIT.")); }

        // Actions
	};
}



