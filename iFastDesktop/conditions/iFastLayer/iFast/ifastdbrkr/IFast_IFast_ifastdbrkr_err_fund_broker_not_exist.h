#pragma once

#include "ConditionObject.h"

namespace CND
{
	class CIFast_IFast_ifastdbrkr_err_fund_broker_not_exist : public CConditionObject
	{
	public:
		CIFast_IFast_ifastdbrkr_err_fund_broker_not_exist() { }
		~CIFast_IFast_ifastdbrkr_err_fund_broker_not_exist() { }

	public:
		// General
		virtual DString GetConditionName() const { return DString(I_("ERR_FUND_BROKER_NOT_EXIST")); }
		virtual DString GetGroupName() const { return DString(I_("iFast")); }
		virtual DString GetModuleName() const { return DString(I_("ifastdbrkr")); }
		virtual int GetSeverity() const { return 6; }

		// Messages
		virtual DString GetMessage_EN_US() const { return DString(I_("Fund Broker record does not exist")); }
		virtual DString GetMessage_DE_DE() const { return DString(I_("Fund Broker record does not exist")); }
		virtual DString GetMessage_FR_CA() const { return DString(I_("L'enregistrement du courtier en fonds n'existe pas.")); }

        // Actions
	};
}



