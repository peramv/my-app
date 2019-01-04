#pragma once

#include "ConditionObject.h"

namespace CND
{
	class IFast_IFast_ifastcbo_warn_attention_biccode_linked_msg : public CConditionObject
	{
	public:
		IFast_IFast_ifastcbo_warn_attention_biccode_linked_msg() { }
		~IFast_IFast_ifastcbo_warn_attention_biccode_linked_msg() { }

	public:
		// General
		virtual DString GetConditionName() const { return DString(I_("WARN_BIC_CODE_LINKED_MSG")); }
		virtual DString GetGroupName() const { return DString(I_("iFast")); }
		virtual DString GetModuleName() const { return DString(I_("ifastcbo")); }
		virtual int GetSeverity() const { return 5; }

		// Messages
		virtual DString GetMessage_EN_US() const { return DString(I_("This will apply to every account that the platform is linked to.")); }
		virtual DString GetMessage_FR_CA() const { return DString(I_("Cela s'appliquera à tous les comptes auxquels la plateforme est liée.")); }

        // Actions
	};
}



