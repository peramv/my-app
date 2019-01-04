#pragma once

#include "ConditionObject.h"

namespace CND
{
	class CIFast_Infrastructure_ditabuscore_err_invalid_military_location : public CConditionObject
	{
	public:
		CIFast_Infrastructure_ditabuscore_err_invalid_military_location() { }
		~CIFast_Infrastructure_ditabuscore_err_invalid_military_location() { }

	public:
		// General
		virtual DString GetConditionName() const { return DString(I_("ERR_INVALID_MILITARY_LOCATION")); }
		virtual DString GetGroupName() const { return DString(I_("Infrastructure")); }
		virtual DString GetModuleName() const { return DString(I_("ditabuscore")); }
		virtual int GetSeverity() const { return 6; }

		// Messages
		virtual DString GetMessage_EN_US() const { return DString(I_("The military location code entered is invalid for the state/country code.")); }
		virtual DString GetMessage_FR_FR() const { return DString(I_("The military location code entered is invalid for the state/country code.")); }
		virtual DString GetMessage_DE_DE() const { return DString(I_("Der eingegebene Militärstationierungscode ist für diesen Staat-/Ländercode ungültig.")); }
		virtual DString GetMessage_ES_ES() const { return DString(I_("El código de destacamento militar introducido no es válido para el código de estado/país.")); }
		virtual DString GetMessage_FR_CA() const { return DString(I_("Le code de localisation militaire entré est invalide pour le code d'état/de province/de pays.")); }
		virtual DString GetMessage_NL_NL() const { return DString(I_("De ingevoerde code voor de militaire locatie is ongeldig voor de staat/landcode")); }

        // Actions
	};
}



