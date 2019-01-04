#pragma once

#include "ConditionObject.h"

namespace CND
{
	class CIFast_IFast_ifastcbo_err_invalid_investment_status : public CConditionObject
	{
	public:
		CIFast_IFast_ifastcbo_err_invalid_investment_status() { }
		~CIFast_IFast_ifastcbo_err_invalid_investment_status() { }

	public:
		// General
		virtual DString GetConditionName() const { return DString(I_("ERR_INVALID_INVESTMENT_STATUS")); }
		virtual DString GetGroupName() const { return DString(I_("iFast")); }
		virtual DString GetModuleName() const { return DString(I_("ifastcbo")); }
		virtual int GetSeverity() const { return 6; }

		// Messages
		virtual DString GetMessage_EN_US() const { return DString(I_("Invalid investment status.")); }
		virtual DString GetMessage_FR_CA() const { return DString(I_("Statut d'investissement invalide")); }

        // Actions
	};
}



