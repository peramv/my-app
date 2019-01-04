#pragma once

#include "ConditionObject.h"

namespace CND
{
	class CIFast_IFast_ifastcbo_err_pending_parent_to_parent_full_exchg_exists : public CConditionObject
	{
	public:
		CIFast_IFast_ifastcbo_err_pending_parent_to_parent_full_exchg_exists() { }
		~CIFast_IFast_ifastcbo_err_pending_parent_to_parent_full_exchg_exists() { }

	public:
		// General
		virtual DString GetConditionName() const { return DString(I_("ERR_PENDING_PARENT_TO_PARENT_FULL_EXCHG_EXISTS")); }
		virtual DString GetGroupName() const { return DString(I_("iFast")); }
		virtual DString GetModuleName() const { return DString(I_("ifastcbo")); }
		virtual int GetSeverity() const { return 6; }

		// Messages
		virtual DString GetMessage_EN_US() const { return DString(I_("A pending parent-to-parent full exchange exists.")); }
		virtual DString GetMessage_FR_CA() const { return DString(I_("A pending parent-to-parent full exchange exists.")); }

        // Actions
	};
}