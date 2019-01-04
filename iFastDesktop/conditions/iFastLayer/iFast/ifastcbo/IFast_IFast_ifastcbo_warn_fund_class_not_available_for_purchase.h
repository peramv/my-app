#pragma once

#include "ConditionObject.h"

namespace CND
{
	class CIFast_IFast_ifastcbo_warn_fund_class_not_available_for_purchase : public CConditionObject
	{
	public:
		CIFast_IFast_ifastcbo_warn_fund_class_not_available_for_purchase() { }
		~CIFast_IFast_ifastcbo_warn_fund_class_not_available_for_purchase() { }

	public:
		// General
		virtual DString GetConditionName() const { return DString(I_("WARN_FUND_CLASS_NOT_AVAILABLE_FOR_PURCHASE")); }
		virtual DString GetGroupName() const { return DString(I_("iFast")); }
		virtual DString GetModuleName() const { return DString(I_("ifastcbo")); }
		virtual int GetSeverity() const { return 5; }

		// Messages
		virtual DString GetMessage_EN_US() const { return DString(I_("%PARAM% is not available for the Purchase.")); }
		virtual DString GetMessage_FR_CA() const { return DString(I_("%PARAM% n'est pas disponible pour l'achat.")); }

        // Actions
	};
}



