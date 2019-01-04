#pragma once

#include "ConditionObject.h"

namespace CND
{
	class CIFast_Infrastructure_didbrkr_didbrkr_bad_format_in_stream_file : public CConditionObject
	{
	public:
		CIFast_Infrastructure_didbrkr_didbrkr_bad_format_in_stream_file() { }
		~CIFast_Infrastructure_didbrkr_didbrkr_bad_format_in_stream_file() { }

	public:
		// General
		virtual DString GetConditionName() const { return DString(I_("DIDBRKR_BAD_FORMAT_IN_STREAM_FILE")); }
		virtual DString GetGroupName() const { return DString(I_("Infrastructure")); }
		virtual DString GetModuleName() const { return DString(I_("didbrkr")); }
		virtual int GetSeverity() const { return 7; }

		// Messages
		virtual DString GetMessage_EN_US() const { return DString(I_("There is an internal problem because a file is corrupted. Bad format in input stream file %file%.")); }
		virtual DString GetMessage_FR_FR() const { return DString(I_("There is an internal problem because a file is corrupted. Bad format in input stream file %file%.")); }
		virtual DString GetMessage_DE_DE() const { return DString(I_("Es gibt ein internes Problem, da eine Datei beschädigt ist. Falsches Format in Eingabe-Streamdatei %file%.")); }
		virtual DString GetMessage_ES_ES() const { return DString(I_("Hay un problema interno porque un archivo está corrompido. Formato no válido en archivo de flujo de entrada %file%.")); }
		virtual DString GetMessage_FR_CA() const { return DString(I_("Il y a un problème interne en raison d'un fichier corrompu. Format erroné dans le fichier de communication saisi %file%.")); }
		virtual DString GetMessage_NL_NL() const { return DString(I_("Er is een intern probleem omdat een bestand is verminkt. Verkeerde indeling in invoerstroombestand %file%")); }

        // Actions
		virtual DString GetAction_EN_US() const { return DString(I_("Contact a support representative and report this message.")); }
		virtual DString GetAction_FR_FR() const { return DString(I_("Contactez un representant en assitance technique et communiquez-lui ce message.")); }
		virtual DString GetAction_DE_DE() const { return DString(I_("Wenden Sie sich an einen Support-Mitarbeiter und teilen Sie ihm die Meldung mit.")); }
		virtual DString GetAction_ES_ES() const { return DString(I_("Contact a support representative and report this message.")); }
		virtual DString GetAction_FR_CA() const { return DString(I_("Communiquez avec un représentant technique et signalez ce message.")); }
		virtual DString GetAction_NL_NL() const { return DString(I_("Neem contact op met een supportmedewerker en meld dit bericht")); }
	};
}



