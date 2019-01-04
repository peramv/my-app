#pragma once

#include "ConditionObject.h"

namespace CND
{
	class CIFast_IFast_ifastdbrkr_err_broker_not_eligible_wrap : public CConditionObject
	{
	public:
		CIFast_IFast_ifastdbrkr_err_broker_not_eligible_wrap() { }
		~CIFast_IFast_ifastdbrkr_err_broker_not_eligible_wrap() { }

	public:
		// General
		virtual DString GetConditionName() const { return DString(I_("ERR_BROKER_NOT_ELIGIBLE_WRAP")); }
		virtual DString GetGroupName() const { return DString(I_("iFast")); }
		virtual DString GetModuleName() const { return DString(I_("ifastdbrkr")); }
		virtual int GetSeverity() const { return 6; }

		// Messages
		virtual DString GetMessage_EN_US() const { return DString(I_("Broker is not eligible for Wrap.")); }
		virtual DString GetMessage_DE_DE() const { return DString(I_("Broker is not eligible for Wrap.")); }
		virtual DString GetMessage_ES_ES() const { return DString(I_("Broker is not eligible for Wrap.")); }
		virtual DString GetMessage_FR_CA() const { return DString(I_("Le courtier n'est pas admissible pour le fonds de fonds.")); }

        // Actions
	};
}



