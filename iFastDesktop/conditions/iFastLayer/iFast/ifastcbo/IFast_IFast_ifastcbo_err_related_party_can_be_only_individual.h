#pragma once

#include "ConditionObject.h"

namespace CND
{
	class CIFast_IFast_ifastcbo_err_related_party_can_be_only_individual : public CConditionObject
	{
	public:
		CIFast_IFast_ifastcbo_err_related_party_can_be_only_individual() { }
		~CIFast_IFast_ifastcbo_err_related_party_can_be_only_individual() { }

	public:
		// General
		virtual DString GetConditionName() const { return DString(I_("ERR_RELATED_PARTY_CAN_BE_ONLY_INDIVIDUAL")); }
		virtual DString GetGroupName() const { return DString(I_("iFast")); }
		virtual DString GetModuleName() const { return DString(I_("ifastcbo")); }
		virtual int GetSeverity() const { return 6; }

		// Messages
		virtual DString GetMessage_EN_US() const { return DString(I_("Related Party can be only Individual.")); }
		virtual DString GetMessage_FR_CA() const { return DString(I_("Related Party can be only Individual.")); }

        // Actions
	};
}