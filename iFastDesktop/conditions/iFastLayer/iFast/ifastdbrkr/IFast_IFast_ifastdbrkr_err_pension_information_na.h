#pragma once

#include "ConditionObject.h"

namespace CND
{
	class CIFast_IFast_ifastdbrkr_err_pension_information_na : public CConditionObject
	{
	public:
		CIFast_IFast_ifastdbrkr_err_pension_information_na() { }
		~CIFast_IFast_ifastdbrkr_err_pension_information_na() { }

	public:
		// General
		virtual DString GetConditionName() const { return DString(I_("ERR_PENSION_INFORMATION_NA")); }
		virtual DString GetGroupName() const { return DString(I_("iFast")); }
		virtual DString GetModuleName() const { return DString(I_("ifastdbrkr")); }
		virtual int GetSeverity() const { return 6; }

		// Messages
		virtual DString GetMessage_EN_US() const { return DString(I_("Pension information is not aplicable for this tax type.")); }
		virtual DString GetMessage_FR_FR() const { return DString(I_("Pension information is not aplicable for this tax type.")); }
		virtual DString GetMessage_DE_DE() const { return DString(I_("Renten-Informationen sind für diese Steuerart nicht anwendbar.")); }
		virtual DString GetMessage_ES_ES() const { return DString(I_("La información de jubilación no se aplica a este tipo tributario")); }
		virtual DString GetMessage_FR_CA() const { return DString(I_("L'information sur le fonds de pension ne s'applique pas à ce type d'imposition.")); }
		virtual DString GetMessage_NL_NL() const { return DString(I_("Pensioengegevens zijn niet van toepassing op dit belastingtype")); }

        // Actions
	};
}



