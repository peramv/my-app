#pragma once

#include "ConditionObject.h"

namespace CND
{
	class CIFast_IFast_ifastcbo_err_comm_rate_greater_then_100 : public CConditionObject
	{
	public:
		CIFast_IFast_ifastcbo_err_comm_rate_greater_then_100() { }
		~CIFast_IFast_ifastcbo_err_comm_rate_greater_then_100() { }

	public:
		// General
		virtual DString GetConditionName() const { return DString(I_("ERR_COMM_RATE_GREATER_THEN_100")); }
		virtual DString GetGroupName() const { return DString(I_("iFast")); }
		virtual DString GetModuleName() const { return DString(I_("ifastcbo")); }
		virtual int GetSeverity() const { return 6; }

		// Messages
		virtual DString GetMessage_EN_US() const { return DString(I_("Commission rate percentage should not be greater than 100.")); }
		virtual DString GetMessage_DE_DE() const { return DString(I_("Commission rate percentage should not be greater than 100.")); }
		virtual DString GetMessage_ES_ES() const { return DString(I_("Commission rate percentage should not be greater than 100.")); }
		virtual DString GetMessage_FR_CA() const { return DString(I_("Le pourcentage de taux de commission ne devrait pas être supérieur à 100.")); }

        // Actions
	};
}



