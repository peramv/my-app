#pragma once

#include "ConditionObject.h"

namespace CND
{
	class CIFast_IFast_ifastcbo_err_tpa_not_related_to_clearingfirm : public CConditionObject
	{
	public:
		CIFast_IFast_ifastcbo_err_tpa_not_related_to_clearingfirm() { }
		~CIFast_IFast_ifastcbo_err_tpa_not_related_to_clearingfirm() { }

	public:
		// General
		virtual DString GetConditionName() const { return DString(I_("ERR_TPA_NOT_RELATED_TO_CLEARINGFIRM")); }
		virtual DString GetGroupName() const { return DString(I_("iFast")); }
		virtual DString GetModuleName() const { return DString(I_("ifastcbo")); }
		virtual int GetSeverity() const { return 6; }

		// Messages
		virtual DString GetMessage_EN_US() const { return DString(I_("TPA is not related to the Clearing Firm.")); }
		virtual DString GetMessage_DE_DE() const { return DString(I_("TPA is not related to the Clearing Firm.")); }
		virtual DString GetMessage_FR_CA() const { return DString(I_("Le TPA n'est pas associé au cabinet de compensation.")); }

        // Actions
	};
}



