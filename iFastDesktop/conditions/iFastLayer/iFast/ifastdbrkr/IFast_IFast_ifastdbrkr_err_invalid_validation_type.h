#pragma once

#include "ConditionObject.h"

namespace CND
{
	class CIFast_IFast_ifastdbrkr_err_invalid_validation_type : public CConditionObject
	{
	public:
		CIFast_IFast_ifastdbrkr_err_invalid_validation_type() { }
		~CIFast_IFast_ifastdbrkr_err_invalid_validation_type() { }

	public:
		// General
		virtual DString GetConditionName() const { return DString(I_("ERR_INVALID_VALIDATION_TYPE")); }
		virtual DString GetGroupName() const { return DString(I_("iFast")); }
		virtual DString GetModuleName() const { return DString(I_("ifastdbrkr")); }
		virtual int GetSeverity() const { return 6; }

		// Messages
		virtual DString GetMessage_EN_US() const { return DString(I_("Invalid Validation Type.")); }
		virtual DString GetMessage_DE_DE() const { return DString(I_("Ungültige Bestätigungsart")); }
		virtual DString GetMessage_ES_ES() const { return DString(I_("Tipo de validación no aceptado")); }
		virtual DString GetMessage_FR_CA() const { return DString(I_("Type de validation invalide")); }
		virtual DString GetMessage_NL_NL() const { return DString(I_("Ongeldig validatietype")); }

        // Actions
	};
}



