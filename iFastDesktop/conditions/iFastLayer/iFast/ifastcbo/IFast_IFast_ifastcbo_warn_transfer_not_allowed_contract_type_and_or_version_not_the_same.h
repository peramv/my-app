#pragma once

#include "ConditionObject.h"

namespace CND
{
	class CIFast_IFast_ifastcbo_warn_transfer_not_allowed_contract_type_and_or_version_not_the_same : public CConditionObject
	{
	public:
		CIFast_IFast_ifastcbo_warn_transfer_not_allowed_contract_type_and_or_version_not_the_same() { }
		~CIFast_IFast_ifastcbo_warn_transfer_not_allowed_contract_type_and_or_version_not_the_same() { }

	public:
		// General
		virtual DString GetConditionName() const { return DString(I_("WARN_TRANSFER_NOT_ALLOWED_CONTRACT_TYPE_AND_OR_VERSION_NOT_THE_SAME")); }
		virtual DString GetGroupName() const { return DString(I_("iFast")); }
		virtual DString GetModuleName() const { return DString(I_("ifastcbo")); }
		virtual int GetSeverity() const { return 5; }

		// Messages
		virtual DString GetMessage_EN_US() const { return DString(I_("Transfer not allowed: Contract Type and/or contract version not the same")); }

        // Actions
	};
}



