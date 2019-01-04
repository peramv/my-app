#pragma once

#include "ConditionObject.h"

namespace CND
{
	class CIFast_IFast_ifastcbo_err_plan_type_must_be_same : public CConditionObject
	{
	public:
		CIFast_IFast_ifastcbo_err_plan_type_must_be_same() { }
		~CIFast_IFast_ifastcbo_err_plan_type_must_be_same() { }

	public:
		// General
		virtual DString GetConditionName() const { return DString(I_("ERR_PLAN_TYPE_MUST_BE_SAME")); }
		virtual DString GetGroupName() const { return DString(I_("iFast")); }
		virtual DString GetModuleName() const { return DString(I_("ifastcbo")); }
		virtual int GetSeverity() const { return 6; }

		// Messages
		virtual DString GetMessage_EN_US() const { return DString(I_("Tax Type of the from account and the to account must be under the same plan type.")); }
		virtual DString GetMessage_DE_DE() const { return DString(I_("Steuerart des Von-Kontos und des Zu-Kontos müssen unter der selben Planart sein.")); }
		virtual DString GetMessage_ES_ES() const { return DString(I_("El tipo tributario de la cuenta de origen y de la cuenta de destino deben estar bajo el mismo tipo de plan")); }
		virtual DString GetMessage_FR_CA() const { return DString(I_("Le type d'imposition des comptes source et cible doit être dans le même type de régime.")); }
		virtual DString GetMessage_NL_NL() const { return DString(I_("Belastingtype van het van-account en het naar-account moeten onder hetzelfde plantype vallen")); }

        // Actions
	};
}



