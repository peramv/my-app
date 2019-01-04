#pragma once

#include "ConditionObject.h"

namespace CND
{
	class CIFast_IFast_ifastdbrkr_err_shr_fund_broker_already_exists : public CConditionObject
	{
	public:
		CIFast_IFast_ifastdbrkr_err_shr_fund_broker_already_exists() { }
		~CIFast_IFast_ifastdbrkr_err_shr_fund_broker_already_exists() { }

	public:
		// General
		virtual DString GetConditionName() const { return DString(I_("ERR_SHR_FUND_BROKER_ALREADY_EXISTS")); }
		virtual DString GetGroupName() const { return DString(I_("iFast")); }
		virtual DString GetModuleName() const { return DString(I_("ifastdbrkr")); }
		virtual int GetSeverity() const { return 6; }

		// Messages
		virtual DString GetMessage_EN_US() const { return DString(I_("Fund Broker already exists for Shareholder.")); }
		virtual DString GetMessage_DE_DE() const { return DString(I_("Fund Broker already exists for Shareholder.")); }
		virtual DString GetMessage_FR_CA() const { return DString(I_("Le courtier en fonds existe déjà pour l'actionnaire.")); }

        // Actions
	};
}



