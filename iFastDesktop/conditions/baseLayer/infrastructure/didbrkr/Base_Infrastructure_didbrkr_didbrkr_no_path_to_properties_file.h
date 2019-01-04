#pragma once

#include "ConditionObject.h"

namespace CND
{
	class CBase_Infrastructure_didbrkr_didbrkr_no_path_to_properties_file : public CConditionObject
	{
	public:
		CBase_Infrastructure_didbrkr_didbrkr_no_path_to_properties_file() { }
		~CBase_Infrastructure_didbrkr_didbrkr_no_path_to_properties_file() { }

	public:
		// General
		virtual DString GetConditionName() const { return DString(I_("DIDBRKR_NO_PATH_TO_PROPERTIES_FILE")); }
		virtual DString GetGroupName() const { return DString(I_("Infrastructure")); }
		virtual DString GetModuleName() const { return DString(I_("didbrkr")); }
		virtual int GetSeverity() const { return 7; }

		// Messages
		virtual DString GetMessage_EN_US() const { return DString(I_("There is an internal problem. Path to input properties file %file% not found.")); }
		virtual DString GetMessage_FR_FR() const { return DString(I_("There is an internal problem. Path to input properties file %file% not found.")); }
		virtual DString GetMessage_DE_DE() const { return DString(I_("Es gibt ein internes Problem. Der Pfad zu der Eingabe-Eigenschaften-Datei %file% wurde nicht gefunden.")); }
		virtual DString GetMessage_ES_ES() const { return DString(I_("Hay un problema interno. No se encontró la ruta de acceso al archivo de propiedades de entrada %file%.")); }
		virtual DString GetMessage_FR_CA() const { return DString(I_("Il y a un problème interne. Le chemin d'accès au fichier des propriétés d'entrée %file% est introuvable.")); }
		virtual DString GetMessage_NL_NL() const { return DString(I_("Er is een intern probleem. Pad naar het bestand voor invoereigenschappen %file% is niet gevonden")); }

        // Actions
		virtual DString GetAction_EN_US() const { return DString(I_("Contact a support representative and report this message.")); }
		virtual DString GetAction_FR_FR() const { return DString(I_("Contactez un representant en assitance technique et communiquez-lui ce message.")); }
		virtual DString GetAction_DE_DE() const { return DString(I_("Wenden Sie sich an einen Support-Mitarbeiter und teilen Sie ihm die Meldung mit.")); }
		virtual DString GetAction_ES_ES() const { return DString(I_("Notifique de este mensaje a un representante de soporte técnico.")); }
		virtual DString GetAction_FR_CA() const { return DString(I_("Communiquez avec un représentant technique et signalez ce message.")); }
		virtual DString GetAction_NL_NL() const { return DString(I_("Neem contact op met een supportmedewerker en meld dit bericht")); }
	};
}



