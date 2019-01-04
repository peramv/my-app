#pragma once

#include "ConditionObject.h"

namespace CND
{
	class CIFast_IFast_ifastcbo_err_plan_type_must_same_in_kind_trans : public CConditionObject
	{
	public:
		CIFast_IFast_ifastcbo_err_plan_type_must_same_in_kind_trans() { }
		~CIFast_IFast_ifastcbo_err_plan_type_must_same_in_kind_trans() { }

	public:
		// General
		virtual DString GetConditionName() const { return DString(I_("ERR_PLAN_TYPE_MUST_SAME_IN_KIND_TRANS")); }
		virtual DString GetGroupName() const { return DString(I_("iFast")); }
		virtual DString GetModuleName() const { return DString(I_("ifastcbo")); }
		virtual int GetSeverity() const { return 6; }

		// Messages
		virtual DString GetMessage_EN_US() const { return DString(I_("Plan Type must be the same for In-Kind Transfer.")); }
		virtual DString GetMessage_DE_DE() const { return DString(I_("Für In-Kind-Transfer muss die gleiche Planart verwendet werden.")); }
		virtual DString GetMessage_ES_ES() const { return DString(I_("El tipo de plan debe ser igual para la transferencia en especie")); }
		virtual DString GetMessage_FR_CA() const { return DString(I_("Le type de régime doit être le même pour un transfert en biens.")); }
		virtual DString GetMessage_NL_NL() const { return DString(I_("Plantype moet hetzelfde zijn als voor overdracht in natura")); }

        // Actions
	};
}



