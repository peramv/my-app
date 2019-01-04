#pragma once

#include "ConditionObject.h"

namespace CND
{
	class CIFast_IFast_ifastcbo_err_no_one_equal_to_broker_code : public CConditionObject
	{
	public:
		CIFast_IFast_ifastcbo_err_no_one_equal_to_broker_code() { }
		~CIFast_IFast_ifastcbo_err_no_one_equal_to_broker_code() { }

	public:
		// General
		virtual DString GetConditionName() const { return DString(I_("ERR_NO_ONE_EQUAL_TO_BROKER_CODE")); }
		virtual DString GetGroupName() const { return DString(I_("iFast")); }
		virtual DString GetModuleName() const { return DString(I_("ifastcbo")); }
		virtual int GetSeverity() const { return 6; }

		// Messages
		virtual DString GetMessage_EN_US() const { return DString(I_("Among ClearingFirm, AgentForFirm and TPA, at least one must be equal to  broker code.")); }
		virtual DString GetMessage_DE_DE() const { return DString(I_("Among ClearingFirm, AgentForFirm and TPA, at least one must be equal to  broker code.")); }
		virtual DString GetMessage_FR_CA() const { return DString(I_("Parmi le cabinet de compensation, l'agent de cabinet et TPA, au moins l'un doit être identique au code de courtier.")); }

        // Actions
	};
}



