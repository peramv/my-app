#pragma once

#include "ConditionObject.h"

namespace CND
{
	class CIFast_IFast_ifastcbo_warn_onhold_flag_for_applicable_addr_must_be_released : public CConditionObject
	{
	public:
		CIFast_IFast_ifastcbo_warn_onhold_flag_for_applicable_addr_must_be_released() { }
		~CIFast_IFast_ifastcbo_warn_onhold_flag_for_applicable_addr_must_be_released() { }

	public:
		// General
		virtual DString GetConditionName() const { return DString(I_("WARN_ONHOLD_FLAG_FOR_APPLICABLE_ADDR_MUST_BE_RELEASED")); }
		virtual DString GetGroupName() const { return DString(I_("iFast")); }
		virtual DString GetModuleName() const { return DString(I_("ifastcbo")); }
		virtual int GetSeverity() const { return 5; }

		// Messages
		virtual DString GetMessage_EN_US() const { return DString(I_("Please review and update On-hold flag for applicable address.")); }
		virtual DString GetMessage_FR_CA() const { return DString(I_("Veuillez réviser et mettre à jour le signal de mise en attente pour l'adresse applicable.")); }

        // Actions
	};
}



