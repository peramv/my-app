#pragma once

#include "ConditionObject.h"

namespace CND
{
	class CIFast_IFast_ifastcbo_err_fund_class_cannot_parent : public CConditionObject
	{
	public:
		CIFast_IFast_ifastcbo_err_fund_class_cannot_parent() { }
		~CIFast_IFast_ifastcbo_err_fund_class_cannot_parent() { }

	public:
		// General
		virtual DString GetConditionName() const { return DString(I_("ERR_FUND_CLASS_CANNOT_PARENT")); }
		virtual DString GetGroupName() const { return DString(I_("iFast")); }
		virtual DString GetModuleName() const { return DString(I_("ifastcbo")); }
		virtual int GetSeverity() const { return 6; }

		// Messages
		virtual DString GetMessage_EN_US() const { return DString(I_("The parent fund class cannot be set up for fund allocation.")); }
		virtual DString GetMessage_FR_CA() const { return DString(I_("La catégorie de fonds parent ne peut pas être choisie pour l’allocation des fonds.")); }

        // Actions
	};
}



