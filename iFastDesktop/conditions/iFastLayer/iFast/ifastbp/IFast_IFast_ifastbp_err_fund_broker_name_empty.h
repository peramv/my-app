#pragma once

#include "ConditionObject.h"

namespace CND
{
	class CIFast_IFast_ifastbp_err_fund_broker_name_empty : public CConditionObject
	{
	public:
		CIFast_IFast_ifastbp_err_fund_broker_name_empty() { }
		~CIFast_IFast_ifastbp_err_fund_broker_name_empty() { }

	public:
		// General
		virtual DString GetConditionName() const { return DString(I_("ERR_FUND_BROKER_NAME_EMPTY")); }
		virtual DString GetGroupName() const { return DString(I_("iFast")); }
		virtual DString GetModuleName() const { return DString(I_("ifastbp")); }
		virtual int GetSeverity() const { return 6; }

		// Messages
		virtual DString GetMessage_EN_US() const { return DString(I_("Fund broker name empty.")); }
		virtual DString GetMessage_FR_CA() const { return DString(I_("Le champ du nom du courtier en fonds est vide.")); }

        // Actions
	};
}



