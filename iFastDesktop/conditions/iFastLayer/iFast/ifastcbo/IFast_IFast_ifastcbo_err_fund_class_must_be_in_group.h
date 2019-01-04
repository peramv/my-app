#pragma once

#include "ConditionObject.h"

namespace CND
{
	class CIFast_IFast_ifastcbo_err_fund_class_must_be_in_group : public CConditionObject
	{
	public:
		CIFast_IFast_ifastcbo_err_fund_class_must_be_in_group() { }
		~CIFast_IFast_ifastcbo_err_fund_class_must_be_in_group() { }

	public:
		// General
		virtual DString GetConditionName() const { return DString(I_("ERR_FUND_CLASS_MUST_BE_IN_GROUP")); }
		virtual DString GetGroupName() const { return DString(I_("iFast")); }
		virtual DString GetModuleName() const { return DString(I_("ifastcbo")); }
		virtual int GetSeverity() const { return 6; }

		// Messages
		virtual DString GetMessage_EN_US() const { return DString(I_("Fund and class must belong to fund group %GROUP_CODE%.")); }
		virtual DString GetMessage_DE_DE() const { return DString(I_("Fund and class must belong to fund group %GROUP_CODE%.")); }
		virtual DString GetMessage_ES_ES() const { return DString(I_("Fund and class must belong to fund group %GROUP_CODE%.")); }
		virtual DString GetMessage_FR_CA() const { return DString(I_("Le fonds et la classe doivent appartenir au groupe de fonds %GROUP_CODE%.")); }

        // Actions
	};
}



