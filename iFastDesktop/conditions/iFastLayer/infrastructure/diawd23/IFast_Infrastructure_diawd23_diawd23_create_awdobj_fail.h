#pragma once

#include "ConditionObject.h"

namespace CND
{
	class CIFast_Infrastructure_diawd23_diawd23_create_awdobj_fail : public CConditionObject
	{
	public:
		CIFast_Infrastructure_diawd23_diawd23_create_awdobj_fail() { }
		~CIFast_Infrastructure_diawd23_diawd23_create_awdobj_fail() { }

	public:
		// General
		virtual DString GetConditionName() const { return DString(I_("DIAWD23_CREATE_AWDOBJ_FAIL")); }
		virtual DString GetGroupName() const { return DString(I_("Infrastructure")); }
		virtual DString GetModuleName() const { return DString(I_("diawd23")); }
		virtual int GetSeverity() const { return 6; }

		// Messages
		virtual DString GetMessage_EN_US() const { return DString(I_("There is an internal problem.\n\nAWD work could not be created.\n\n")); }
		virtual DString GetMessage_FR_FR() const { return DString(I_("There is an internal problem.\n\nAWD work could not be created.\n\n")); }
		virtual DString GetMessage_DE_DE() const { return DString(I_("Es gibt ein internes Problem.\n\nAWD-Arbeit konnte nicht erstellt werden.\n\n")); }
		virtual DString GetMessage_ES_ES() const { return DString(I_("Hay un problema interno.\n\nNo se pudo crear la tarea de AWD.\n\n")); }
		virtual DString GetMessage_FR_CA() const { return DString(I_("Il y a un problème interne. \n\n Le travail AWD n'a pas pu être créé. \n\n")); }
		virtual DString GetMessage_NL_NL() const { return DString(I_("Er is een intern probleem.\n\nAWD-werk kon niet worden gemaakt.\n\n")); }

        // Actions
		virtual DString GetAction_EN_US() const { return DString(I_("Contact a support representative and report this message.")); }
		virtual DString GetAction_FR_FR() const { return DString(I_("Contactez un representant en assitance technique et communiquez-lui ce message.")); }
		virtual DString GetAction_DE_DE() const { return DString(I_("Wenden Sie sich an einen Support-Mitarbeiter und teilen Sie ihm die Meldung mit.")); }
		virtual DString GetAction_ES_ES() const { return DString(I_("Notifique de este mensaje a un representante de soporte técnico.")); }
		virtual DString GetAction_FR_CA() const { return DString(I_("Communiquez avec un représentant technique et signalez ce message.")); }
		virtual DString GetAction_NL_NL() const { return DString(I_("Neem contact op met een supportmedewerker en meld dit bericht")); }
	};
}



