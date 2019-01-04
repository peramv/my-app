#pragma once

#include "ConditionObject.h"

namespace CND
{
	class CIFast_IFast_ifastcbo_err_percentage_of_class_holdings_breached : public CConditionObject
	{
	public:
		CIFast_IFast_ifastcbo_err_percentage_of_class_holdings_breached() { }
		~CIFast_IFast_ifastcbo_err_percentage_of_class_holdings_breached() { }

	public:
		// General
		virtual DString GetConditionName() const { return DString(I_("ERR_PERCENTAGE_OF_CLASS_HOLDINGS_BREACHED")); }
		virtual DString GetGroupName() const { return DString(I_("iFast")); }
		virtual DString GetModuleName() const { return DString(I_("ifastcbo")); }
		virtual int GetSeverity() const { return 6; }

		// Messages
		virtual DString GetMessage_EN_US() const { return DString(I_("% of Class Holdings is breached.")); }
		virtual DString GetMessage_FR_CA() const { return DString(I_("Le % des positions de la catégorie est dépassé.")); }

        // Actions
	};
}



