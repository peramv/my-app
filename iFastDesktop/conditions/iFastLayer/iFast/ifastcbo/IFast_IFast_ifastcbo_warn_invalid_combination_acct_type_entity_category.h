#pragma once

#include "ConditionObject.h"

namespace CND
{
	class CIFast_IFast_ifastcbo_warn_invalid_combination_acct_type_entity_category : public CConditionObject
	{
	public:
		CIFast_IFast_ifastcbo_warn_invalid_combination_acct_type_entity_category() { }
		~CIFast_IFast_ifastcbo_warn_invalid_combination_acct_type_entity_category() { }

	public:
		// General
		virtual DString GetConditionName() const { return DString(I_("WARN_INVALID_COMBINATION_ACCT_TYPE_ENTITY_CATEGORY")); }
		virtual DString GetGroupName() const { return DString(I_("iFast")); }
		virtual DString GetModuleName() const { return DString(I_("ifastcbo")); }
		virtual int GetSeverity() const { return 5; }

		// Messages
		virtual DString GetMessage_EN_US() const { return DString(I_("Invalid combination of account type and entity category.")); }

        // Actions
	};
}



