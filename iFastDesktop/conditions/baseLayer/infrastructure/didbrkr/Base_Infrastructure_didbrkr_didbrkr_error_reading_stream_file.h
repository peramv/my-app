#pragma once

#include "ConditionObject.h"

namespace CND
{
	class CBase_Infrastructure_didbrkr_didbrkr_error_reading_stream_file : public CConditionObject
	{
	public:
		CBase_Infrastructure_didbrkr_didbrkr_error_reading_stream_file() { }
		~CBase_Infrastructure_didbrkr_didbrkr_error_reading_stream_file() { }

	public:
		// General
		virtual DString GetConditionName() const { return DString(I_("DIDBRKR_ERROR_READING_STREAM_FILE")); }
		virtual DString GetGroupName() const { return DString(I_("Infrastructure")); }
		virtual DString GetModuleName() const { return DString(I_("didbrkr")); }
		virtual int GetSeverity() const { return 7; }

		// Messages
		virtual DString GetMessage_EN_US() const { return DString(I_("There is an internal problem because stream file %file% could not be read.")); }
		virtual DString GetMessage_FR_FR() const { return DString(I_("There is an internal problem because stream file %file% could not be read.")); }
		virtual DString GetMessage_DE_DE() const { return DString(I_("Es gibt ein internes Problem, da die Streamdatei %file% nicht gelesen werden konnte.")); }
		virtual DString GetMessage_ES_ES() const { return DString(I_("Hay un problema interno porque no se pudo leer el archivo de flujo %file%.")); }
		virtual DString GetMessage_FR_CA() const { return DString(I_("Il y a un problème interne parce que le fichier de communication %file% n'a pu être lu.")); }
		virtual DString GetMessage_NL_NL() const { return DString(I_("Er is een intern probleem omdat stroombestand %file% niet kon worden gelezen")); }

        // Actions
		virtual DString GetAction_EN_US() const { return DString(I_("Contact a support representative and report this message.")); }
		virtual DString GetAction_FR_FR() const { return DString(I_("Contactez un representant en assitance technique et communiquez-lui ce message.")); }
		virtual DString GetAction_DE_DE() const { return DString(I_("Wenden Sie sich an einen Support-Mitarbeiter und teilen Sie ihm die Meldung mit.")); }
		virtual DString GetAction_ES_ES() const { return DString(I_("Contact a support representative and report this message.")); }
		virtual DString GetAction_FR_CA() const { return DString(I_("Communiquez avec un représentant technique et signalez ce message.")); }
		virtual DString GetAction_NL_NL() const { return DString(I_("Neem contact op met een supportmedewerker en meld dit bericht")); }
	};
}



