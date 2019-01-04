#pragma once

#include "ConditionObject.h"

namespace CND
{
	class CIFast_IFast_ifastbp_err_rrif_info_not_applicable : public CConditionObject
	{
	public:
		CIFast_IFast_ifastbp_err_rrif_info_not_applicable() { }
		~CIFast_IFast_ifastbp_err_rrif_info_not_applicable() { }

	public:
		// General
		virtual DString GetConditionName() const { return DString(I_("ERR_RRIF_INFO_NOT_APPLICABLE")); }
		virtual DString GetGroupName() const { return DString(I_("iFast")); }
		virtual DString GetModuleName() const { return DString(I_("ifastbp")); }
		virtual int GetSeverity() const { return 6; }

		// Messages
		virtual DString GetMessage_EN_US() const { return DString(I_("RRIF/LIF/LRIF information not applicable to the tax type.")); }
		virtual DString GetMessage_DE_DE() const { return DString(I_("RRIF/LIF/LRIF-Information nicht anwendbar auf die Steuerart")); }
		virtual DString GetMessage_ES_ES() const { return DString(I_("Información RRIF/LIF/LRIF no aplicable al tipo tributario")); }
		virtual DString GetMessage_FR_CA() const { return DString(I_("L'information FERR/FRV/FRRI ne s'applique pas au type d'imposition.")); }
		virtual DString GetMessage_NL_NL() const { return DString(I_("Gegevens RRIF/LIF/LRIF zijn niet van toepassing op het belastingtype")); }

        // Actions
	};
}



