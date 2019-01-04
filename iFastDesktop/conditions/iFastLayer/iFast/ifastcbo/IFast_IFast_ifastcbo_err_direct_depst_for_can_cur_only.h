#pragma once

#include "ConditionObject.h"

namespace CND
{
	class CIFast_IFast_ifastcbo_err_direct_depst_for_can_cur_only : public CConditionObject
	{
	public:
		CIFast_IFast_ifastcbo_err_direct_depst_for_can_cur_only() { }
		~CIFast_IFast_ifastcbo_err_direct_depst_for_can_cur_only() { }

	public:
		// General
		virtual DString GetConditionName() const { return DString(I_("ERR_DIRECT_DEPST_FOR_CAN_CUR_ONLY")); }
		virtual DString GetGroupName() const { return DString(I_("iFast")); }
		virtual DString GetModuleName() const { return DString(I_("ifastcbo")); }
		virtual int GetSeverity() const { return 6; }

		// Messages
		virtual DString GetMessage_EN_US() const { return DString(I_("Direct deposit redemption apply for Canadian currency fund only.")); }
		virtual DString GetMessage_FR_CA() const { return DString(I_("Le rachat par dépôt direct n'est applicable qu'aux fonds en monnaie canadienne.")); }

        // Actions
	};
}



