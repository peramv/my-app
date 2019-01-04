#pragma once

#include "ConditionObject.h"

namespace CND
{
	class CIFast_Infrastructure_didbrkr_didbrkr_invalid_line_length : public CConditionObject
	{
	public:
		CIFast_Infrastructure_didbrkr_didbrkr_invalid_line_length() { }
		~CIFast_Infrastructure_didbrkr_didbrkr_invalid_line_length() { }

	public:
		// General
		virtual DString GetConditionName() const { return DString(I_("DIDBRKR_INVALID_LINE_LENGTH")); }
		virtual DString GetGroupName() const { return DString(I_("Infrastructure")); }
		virtual DString GetModuleName() const { return DString(I_("didbrkr")); }
		virtual int GetSeverity() const { return 7; }

		// Messages
		virtual DString GetMessage_EN_US() const { return DString(I_("There is an internal problem reading file data due to a read line with invalid length from file %file%.")); }
		virtual DString GetMessage_FR_FR() const { return DString(I_("There is an internal problem reading file data due to a read line with invalid length from file %file%.")); }
		virtual DString GetMessage_DE_DE() const { return DString(I_("Es gibt ein internes Problem beim Lesen von Daten wegen einer gelesenen Zeile mit ungültiger Länge aus der Datei %file%.")); }
		virtual DString GetMessage_ES_ES() const { return DString(I_("Hay un problema interno para leer los datos del archivo debido a una línea de lectura con una longitud no válida en el archivo %file%.")); }
		virtual DString GetMessage_FR_CA() const { return DString(I_("Il y a un problème interne lors de la lecture des données du fichier en raison d'une ligne de lecture de longueur invalide dans le fichier %file%.")); }
		virtual DString GetMessage_NL_NL() const { return DString(I_("Er is een intern probleem bij het lezen van de bestandsgegevens als gevolg van een leesregel met een ongeldige lengte van bestand %file%")); }

        // Actions
		virtual DString GetAction_EN_US() const { return DString(I_("Contact a support representative and report this message.")); }
		virtual DString GetAction_FR_FR() const { return DString(I_("Contactez un representant en assitance technique et communiquez-lui ce message.")); }
		virtual DString GetAction_DE_DE() const { return DString(I_("Wenden Sie sich an einen Support-Mitarbeiter und teilen Sie ihm die Meldung mit.")); }
		virtual DString GetAction_ES_ES() const { return DString(I_("Contact a support representative and report this message.")); }
		virtual DString GetAction_FR_CA() const { return DString(I_("Communiquez avec un représentant technique et signalez ce message.")); }
		virtual DString GetAction_NL_NL() const { return DString(I_("Neem contact op met een supportmedewerker en meld dit bericht")); }
	};
}



