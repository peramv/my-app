#pragma once

#include "ConditionObject.h"

namespace CND
{
	class CIFast_IFast_ifastcbo_err_fund_class_not_protected : public CConditionObject
	{
	public:
		CIFast_IFast_ifastcbo_err_fund_class_not_protected() { }
		~CIFast_IFast_ifastcbo_err_fund_class_not_protected() { }

	public:
		// General
		virtual DString GetConditionName() const { return DString(I_("ERR_FUND_CLASS_NOT_PROTECTED")); }
		virtual DString GetGroupName() const { return DString(I_("iFast")); }
		virtual DString GetModuleName() const { return DString(I_("ifastcbo")); }
		virtual int GetSeverity() const { return 6; }

		// Messages
		virtual DString GetMessage_EN_US() const { return DString(I_("Selected Fund/Class is not protected.")); }
		virtual DString GetMessage_DE_DE() const { return DString(I_("Selected Fund/Class is not protected.")); }
		virtual DString GetMessage_ES_ES() const { return DString(I_("Selected Fund/Class is not protected.")); }
		virtual DString GetMessage_FR_CA() const { return DString(I_("Le fonds/la classe sélectionné(e) n'est pas protégé(e).")); }

        // Actions
	};
}



