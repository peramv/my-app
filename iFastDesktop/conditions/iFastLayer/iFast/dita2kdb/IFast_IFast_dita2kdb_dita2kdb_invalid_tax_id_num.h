#pragma once

#include "ConditionObject.h"

namespace CND
{
	class CIFast_IFast_dita2kdb_dita2kdb_invalid_tax_id_num : public CConditionObject
	{
	public:
		CIFast_IFast_dita2kdb_dita2kdb_invalid_tax_id_num() { }
		~CIFast_IFast_dita2kdb_dita2kdb_invalid_tax_id_num() { }

	public:
		// General
		virtual DString GetConditionName() const { return DString(I_("DITA2KDB_INVALID_TAX_ID_NUM")); }
		virtual DString GetGroupName() const { return DString(I_("iFast")); }
		virtual DString GetModuleName() const { return DString(I_("dita2kdb")); }
		virtual int GetSeverity() const { return 6; }

		// Messages
		virtual DString GetMessage_EN_US() const { return DString(I_("There is an internal problem reading file due to an unexpected end of stream.  File %file%.")); }
		virtual DString GetMessage_FR_FR() const { return DString(I_("Probleme interne lors de la lecture des donnees du fichier suite a une fin de ficher %file% inattendue.")); }
		virtual DString GetMessage_DE_DE() const { return DString(I_("Es gibt ein internes Problem beim Lesen von Daten wegen eines unerwarteten Endes der Streamdatei %file%.")); }
		virtual DString GetMessage_ES_ES() const { return DString(I_("Hay un problema interno para leer los datos del archivo debido al final inesperado del archivo de flujo %file%.")); }
		virtual DString GetMessage_FR_CA() const { return DString(I_("Il y a un problème interne à la lecture du fichier, en raison d'une interruption imprévue du flux de données. Fichier : %file%.")); }
		virtual DString GetMessage_NL_NL() const { return DString(I_("Er is een intern probleem bij het lezen van de bestandsgegevens als gevolg van een onverwacht einde van stroombestand %file%")); }

        // Actions
		virtual DString GetAction_EN_US() const { return DString(I_("Contact a support representative and report this message.")); }
		virtual DString GetAction_FR_FR() const { return DString(I_("Contactez un representant en assitance technique et communiquez-lui ce message.")); }
		virtual DString GetAction_DE_DE() const { return DString(I_("Wenden Sie sich an einen Support-Mitarbeiter und teilen Sie ihm die Meldung mit.")); }
		virtual DString GetAction_ES_ES() const { return DString(I_("Contact a support representative and report this message.")); }
		virtual DString GetAction_FR_CA() const { return DString(I_("Communiquez avec un représentant technique et signalez ce message.")); }
		virtual DString GetAction_NL_NL() const { return DString(I_("Neem contact op met een supportmedewerker en meld dit bericht")); }
	};
}



