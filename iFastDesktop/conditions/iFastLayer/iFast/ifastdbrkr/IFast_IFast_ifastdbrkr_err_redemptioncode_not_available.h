#pragma once

#include "ConditionObject.h"

namespace CND
{
	class CIFast_IFast_ifastdbrkr_err_redemptioncode_not_available : public CConditionObject
	{
	public:
		CIFast_IFast_ifastdbrkr_err_redemptioncode_not_available() { }
		~CIFast_IFast_ifastdbrkr_err_redemptioncode_not_available() { }

	public:
		// General
		virtual DString GetConditionName() const { return DString(I_("ERR_REDEMPTIONCODE_NOT_AVAILABLE")); }
		virtual DString GetGroupName() const { return DString(I_("iFast")); }
		virtual DString GetModuleName() const { return DString(I_("ifastdbrkr")); }
		virtual int GetSeverity() const { return 6; }

		// Messages
		virtual DString GetMessage_EN_US() const { return DString(I_("Redemption code not available for this Tax Type.")); }
		virtual DString GetMessage_FR_FR() const { return DString(I_("Redemption code not available for this Tax Type.")); }
		virtual DString GetMessage_DE_DE() const { return DString(I_("Tilgungscode für diese Steuerart nicht verfügbar .")); }
		virtual DString GetMessage_ES_ES() const { return DString(I_("El código de rescate no está disponible para este tipo tributario")); }
		virtual DString GetMessage_FR_CA() const { return DString(I_("Le code de rachat n'est pas disponible pour ce type d'imposition.")); }
		virtual DString GetMessage_NL_NL() const { return DString(I_("Aflossingscode is niet beschikbaar voor dit belastingtype")); }

        // Actions
	};
}



