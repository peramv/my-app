#pragma once

#include "ConditionObject.h"

namespace CND
{
	class CIFast_Infrastructure_ditabuscore_err_invalid_state_country : public CConditionObject
	{
	public:
		CIFast_Infrastructure_ditabuscore_err_invalid_state_country() { }
		~CIFast_Infrastructure_ditabuscore_err_invalid_state_country() { }

	public:
		// General
		virtual DString GetConditionName() const { return DString(I_("ERR_INVALID_STATE_COUNTRY")); }
		virtual DString GetGroupName() const { return DString(I_("Infrastructure")); }
		virtual DString GetModuleName() const { return DString(I_("ditabuscore")); }
		virtual int GetSeverity() const { return 6; }

		// Messages
		virtual DString GetMessage_EN_US() const { return DString(I_("State country code specified is invalid.")); }
		virtual DString GetMessage_FR_FR() const { return DString(I_("State country code specified is invalid.")); }
		virtual DString GetMessage_DE_DE() const { return DString(I_("Der angegebene Staat-/Ländercode ist ungültig.")); }
		virtual DString GetMessage_ES_ES() const { return DString(I_("El código de estado/país especificado no es válido.")); }
		virtual DString GetMessage_FR_CA() const { return DString(I_("Le code de pays de l'état/de la province spécifié est invalide.")); }
		virtual DString GetMessage_NL_NL() const { return DString(I_("Opgegeven staat/landcode is ongeldig")); }

        // Actions
	};
}



