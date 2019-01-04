#pragma once

#include "ConditionObject.h"

namespace CND
{
	class CIFast_IFast_ifastdbrkr_err_invalid_callnum : public CConditionObject
	{
	public:
		CIFast_IFast_ifastdbrkr_err_invalid_callnum() { }
		~CIFast_IFast_ifastdbrkr_err_invalid_callnum() { }

	public:
		// General
		virtual DString GetConditionName() const { return DString(I_("ERR_INVALID_CALLNUM")); }
		virtual DString GetGroupName() const { return DString(I_("iFast")); }
		virtual DString GetModuleName() const { return DString(I_("ifastdbrkr")); }
		virtual int GetSeverity() const { return 6; }

		// Messages
		virtual DString GetMessage_EN_US() const { return DString(I_("Invalid Call Number.")); }
		virtual DString GetMessage_FR_FR() const { return DString(I_("Invalid Call Number.")); }
		virtual DString GetMessage_DE_DE() const { return DString(I_("Ungültige Rufnummer")); }
		virtual DString GetMessage_ES_ES() const { return DString(I_("Número de llamada no válido")); }
		virtual DString GetMessage_FR_CA() const { return DString(I_("Numéro d'appel invalide")); }
		virtual DString GetMessage_NL_NL() const { return DString(I_("Ongeldig aanroepnummer")); }

        // Actions
	};
}



