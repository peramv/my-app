#pragma once

#include "ConditionObject.h"

namespace CND
{
	class CIFast_IFast_ifastdbrkr_err_shr_fund_sponsor_agrmnt_does_not_exist : public CConditionObject
	{
	public:
		CIFast_IFast_ifastdbrkr_err_shr_fund_sponsor_agrmnt_does_not_exist() { }
		~CIFast_IFast_ifastdbrkr_err_shr_fund_sponsor_agrmnt_does_not_exist() { }

	public:
		// General
		virtual DString GetConditionName() const { return DString(I_("ERR_SHR_FUND_SPONSOR_AGRMNT_DOES_NOT_EXIST")); }
		virtual DString GetGroupName() const { return DString(I_("iFast")); }
		virtual DString GetModuleName() const { return DString(I_("ifastdbrkr")); }
		virtual int GetSeverity() const { return 6; }

		// Messages
		virtual DString GetMessage_EN_US() const { return DString(I_("Fund Sponsor Agreement does not exist for Shareholder.")); }
		virtual DString GetMessage_DE_DE() const { return DString(I_("Fund Sponsor Agreement does not exist for Shareholder.")); }
		virtual DString GetMessage_FR_CA() const { return DString(I_("L'accord de promoteur de fonds n'existe pas pour l'actionnaire.")); }

        // Actions
	};
}



