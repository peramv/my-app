#pragma once

#include "ConditionObject.h"

namespace CND
{
	class CIFast_IFast_dicore_dicore_parse_idi_missing_terminator : public CConditionObject
	{
	public:
		CIFast_IFast_dicore_dicore_parse_idi_missing_terminator() { }
		~CIFast_IFast_dicore_dicore_parse_idi_missing_terminator() { }

	public:
		// General
		virtual DString GetConditionName() const { return DString(I_("DICORE_PARSE_IDI_MISSING_TERMINATOR")); }
		virtual DString GetGroupName() const { return DString(I_("iFast")); }
		virtual DString GetModuleName() const { return DString(I_("dicore")); }
		virtual int GetSeverity() const { return 7; }

		// Messages
		virtual DString GetMessage_EN_US() const { return DString(I_("Service %service% has not been initialized for the user with the id %usid% and for the work session with the id %wksid%")); }
		virtual DString GetMessage_FR_FR() const { return DString(I_("Service %service% has not been initialized for the user with the id %usid% and for the work session with the id %wksid%")); }
		virtual DString GetMessage_DE_DE() const { return DString(I_("Service %service% wurde nicht initialisiert für den Benutzer mit der ID %usid% und für die Arbeitssitzung mit der ID %wksid%.")); }
		virtual DString GetMessage_ES_ES() const { return DString(I_("El servicio %service% no se ha inicializado para el usuario con identificación %usid% ni para la sesión de tareas con la identificación %wksid%")); }
		virtual DString GetMessage_FR_CA() const { return DString(I_("Le service %service% n'a pas été initialisé pour l'utilisateur %usid% et pour la session de travail %wksid%.")); }
		virtual DString GetMessage_NL_NL() const { return DString(I_("Dienst %service% is niet geïnitialiseerd voor de gebruiker met het ID %usid% en voor de werksessie met het  ID %wksid%")); }

        // Actions
		virtual DString GetAction_EN_US() const { return DString(I_("1")); }
		virtual DString GetAction_FR_FR() const { return DString(I_("1")); }
		virtual DString GetAction_DE_DE() const { return DString(I_("1")); }
		virtual DString GetAction_ES_ES() const { return DString(I_("1")); }
		virtual DString GetAction_FR_CA() const { return DString(I_("1")); }
		virtual DString GetAction_NL_NL() const { return DString(I_("1")); }
	};
}



