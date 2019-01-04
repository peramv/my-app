#pragma once

#include "ConditionObject.h"

namespace CND
{
	class CIFast_IFast_ifastdbrkr_err_no_fee_defined_for_fee_override : public CConditionObject
	{
	public:
		CIFast_IFast_ifastdbrkr_err_no_fee_defined_for_fee_override() { }
		~CIFast_IFast_ifastdbrkr_err_no_fee_defined_for_fee_override() { }

	public:
		// General
		virtual DString GetConditionName() const { return DString(I_("ERR_NO_FEE_DEFINED_FOR_FEE_OVERRIDE")); }
		virtual DString GetGroupName() const { return DString(I_("iFast")); }
		virtual DString GetModuleName() const { return DString(I_("ifastdbrkr")); }
		virtual int GetSeverity() const { return 6; }

		// Messages
		virtual DString GetMessage_EN_US() const { return DString(I_("No fee defined for fee override.")); }
		virtual DString GetMessage_DE_DE() const { return DString(I_("Keine Provision definiert oder Provision außer Kraft gesetzt")); }
		virtual DString GetMessage_ES_ES() const { return DString(I_("No hay una comisión definida para el reemplazo de la comisión predeterminada")); }
		virtual DString GetMessage_FR_CA() const { return DString(I_("Aucuns frais définis pour la modification des frais")); }
		virtual DString GetMessage_NL_NL() const { return DString(I_("Er zijn geen kosten gedefinieerd voor vervangen van kosten")); }

        // Actions
	};
}



