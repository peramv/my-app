#pragma once

#include "ConditionObject.h"

namespace CND
{
	class CIFast_IFast_dicore_dicore_parse_idi_missing_value : public CConditionObject
	{
	public:
		CIFast_IFast_dicore_dicore_parse_idi_missing_value() { }
		~CIFast_IFast_dicore_dicore_parse_idi_missing_value() { }

	public:
		// General
		virtual DString GetConditionName() const { return DString(I_("DICORE_PARSE_IDI_MISSING_VALUE")); }
		virtual DString GetGroupName() const { return DString(I_("iFast")); }
		virtual DString GetModuleName() const { return DString(I_("dicore")); }
		virtual int GetSeverity() const { return 7; }

		// Messages
		virtual DString GetMessage_EN_US() const { return DString(I_("Missing either the usersessionid or worksessionid")); }
		virtual DString GetMessage_FR_FR() const { return DString(I_("Missing either the usersessionid or worksessionid")); }
		virtual DString GetMessage_DE_DE() const { return DString(I_("Die Benutzersitzungs-ID oder die Arbeitssitzungs-ID fehlen.")); }
		virtual DString GetMessage_ES_ES() const { return DString(I_("Falta la identificación de sesión de usuario o la identificación de sesión de tarea.")); }
		virtual DString GetMessage_FR_CA() const { return DString(I_("Nom de session d'utilisateur ou de session de travail manquant")); }
		virtual DString GetMessage_NL_NL() const { return DString(I_("Het ID voor de gebruikerssessie of voor de werksessie ontbreekt")); }

        // Actions
	};
}



