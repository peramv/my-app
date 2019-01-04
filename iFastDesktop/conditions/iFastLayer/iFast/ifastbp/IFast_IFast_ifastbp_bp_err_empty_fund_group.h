#pragma once

#include "ConditionObject.h"

namespace CND
{
	class CIFast_IFast_ifastbp_bp_err_empty_fund_group : public CConditionObject
	{
	public:
		CIFast_IFast_ifastbp_bp_err_empty_fund_group() { }
		~CIFast_IFast_ifastbp_bp_err_empty_fund_group() { }

	public:
		// General
		virtual DString GetConditionName() const { return DString(I_("BP_ERR_EMPTY_FUND_GROUP")); }
		virtual DString GetGroupName() const { return DString(I_("iFast")); }
		virtual DString GetModuleName() const { return DString(I_("ifastbp")); }
		virtual int GetSeverity() const { return 6; }

		// Messages
		virtual DString GetMessage_EN_US() const { return DString(I_("Fund Group is empty.")); }
		virtual DString GetMessage_DE_DE() const { return DString(I_("Fund Group is empty.")); }
		virtual DString GetMessage_FR_CA() const { return DString(I_("Le groupe de fonds est manquant.")); }

        // Actions
	};
}



