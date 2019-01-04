#pragma once

#include "ConditionObject.h"

namespace CND
{
	class CIFast_IFast_vision_err_no_work_session : public CConditionObject
	{
	public:
		CIFast_IFast_vision_err_no_work_session() { }
		~CIFast_IFast_vision_err_no_work_session() { }

	public:
		// General
		virtual DString GetConditionName() const { return DString(I_("ERR_NO_WORK_SESSION")); }
		virtual DString GetGroupName() const { return DString(I_("iFast")); }
		virtual DString GetModuleName() const { return DString(I_("vision")); }
		virtual int GetSeverity() const { return 6; }

		// Messages
		virtual DString GetMessage_EN_US() const { return DString(I_("No work session with the id %wkid% for the user with the session id %usid%")); }
		virtual DString GetMessage_FR_FR() const { return DString(I_("No work session with the id %wkid% for the user with the session id %usid%")); }
		virtual DString GetMessage_DE_DE() const { return DString(I_("Keine Arbeitssitzung mit der ID %wkid% für den Benutzer mit der Sitzungs-ID %usid%.")); }
		virtual DString GetMessage_ES_ES() const { return DString(I_("No hay sesión de tareas con la identificación %wkid% para el usuario con la identificación de sesión %usid%")); }
		virtual DString GetMessage_FR_CA() const { return DString(I_("Il n'y a aucune session de travail avec le code %wkid% pour l'utilisateur avec le code de session %usid%.")); }
		virtual DString GetMessage_NL_NL() const { return DString(I_("Geen werksessie met het ID %wkid% voor de gebruiker met het sessie-ID %usid%")); }

        // Actions
	};
}



