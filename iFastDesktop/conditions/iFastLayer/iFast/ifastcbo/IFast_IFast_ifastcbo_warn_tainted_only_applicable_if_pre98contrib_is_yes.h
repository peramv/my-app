#pragma once

#include "ConditionObject.h"

namespace CND
{
	class CIFast_IFast_ifastcbo_warn_tainted_only_applicable_if_pre98contrib_is_yes : public CConditionObject
	{
	public:
		CIFast_IFast_ifastcbo_warn_tainted_only_applicable_if_pre98contrib_is_yes() { }
		~CIFast_IFast_ifastcbo_warn_tainted_only_applicable_if_pre98contrib_is_yes() { }

	public:
		// General
		virtual DString GetConditionName() const { return DString(I_("WARN_TAINTED_ONLY_APPLICABLE_IF_PRE98CONTRIB_IS_YES")); }
		virtual DString GetGroupName() const { return DString(I_("iFast")); }
		virtual DString GetModuleName() const { return DString(I_("ifastcbo")); }
		virtual int GetSeverity() const { return 5; }

		// Messages
		virtual DString GetMessage_EN_US() const { return DString(I_("Tainted is only applicable if the withdrawal include contributions prior to 1998.")); }
		virtual DString GetMessage_FR_CA() const { return DString(I_("Contaminé n'est applicable que si le retrait comprend les cotisations antérieures à 1998.")); }

        // Actions
	};
}



