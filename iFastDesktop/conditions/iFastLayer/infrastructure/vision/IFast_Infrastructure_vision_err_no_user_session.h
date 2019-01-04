#pragma once

#include "ConditionObject.h"

namespace CND
{
	class CIFast_Infrastructure_vision_err_no_user_session : public CConditionObject
	{
	public:
		CIFast_Infrastructure_vision_err_no_user_session() { }
		~CIFast_Infrastructure_vision_err_no_user_session() { }

	public:
		// General
		virtual DString GetConditionName() const { return DString(I_("ERR_NO_USER_SESSION")); }
		virtual DString GetGroupName() const { return DString(I_("Infrastructure")); }
		virtual DString GetModuleName() const { return DString(I_("vision")); }
		virtual int GetSeverity() const { return 6; }

		// Messages
		virtual DString GetMessage_EN_US() const { return DString(I_("AWD has indicated a problem with receiving comments.")); }
		virtual DString GetMessage_FR_FR() const { return DString(I_("AWD has indicated a problem with receiving comments.")); }
		virtual DString GetMessage_DE_DE() const { return DString(I_("AWD hat ein Problem beim Erhalt von Kommentaren erkannt.")); }
		virtual DString GetMessage_ES_ES() const { return DString(I_("AWD ha indicado un problema para recibir comentarios.")); }
		virtual DString GetMessage_FR_CA() const { return DString(I_("AWD a indiqué un problème avec la réception de commentaires.")); }
		virtual DString GetMessage_NL_NL() const { return DString(I_("AWD heeft een probleem aangegeven met het ontvangen van opmerkingen")); }

        // Actions
		virtual DString GetAction_EN_US() const { return DString(I_("Check the work object history to verify comments exist.")); }
		virtual DString GetAction_FR_FR() const { return DString(I_("Check the work object history to verify comments exist.")); }
		virtual DString GetAction_DE_DE() const { return DString(I_("Überprüfen Sie den Verlauf des Arbeitsobjekts nach vorhandenen Kommentaren.")); }
		virtual DString GetAction_ES_ES() const { return DString(I_("Check the work object history to verify comments exist.")); }
		virtual DString GetAction_FR_CA() const { return DString(I_("Vérifiez l'historique de l'objet de travail pour vérifier les commentaires existants.")); }
		virtual DString GetAction_NL_NL() const { return DString(I_("Controleer de historie van het werkobject om te controleren of er opmerkingen zijn")); }
	};
}



