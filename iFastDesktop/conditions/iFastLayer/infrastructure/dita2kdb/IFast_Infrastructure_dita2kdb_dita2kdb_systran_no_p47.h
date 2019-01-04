#pragma once

#include "ConditionObject.h"

namespace CND
{
	class CIFast_Infrastructure_dita2kdb_dita2kdb_systran_no_p47 : public CConditionObject
	{
	public:
		CIFast_Infrastructure_dita2kdb_dita2kdb_systran_no_p47() { }
		~CIFast_Infrastructure_dita2kdb_dita2kdb_systran_no_p47() { }

	public:
		// General
		virtual DString GetConditionName() const { return DString(I_("DITA2KDB_SYSTRAN_NO_P47")); }
		virtual DString GetGroupName() const { return DString(I_("Infrastructure")); }
		virtual DString GetModuleName() const { return DString(I_("dita2kdb")); }
		virtual int GetSeverity() const { return 6; }

		// Messages
		virtual DString GetMessage_EN_US() const { return DString(I_("There is no Mutual Fund Systematic Processing Date Table (P47) record for SYSTRAN processing.")); }
		virtual DString GetMessage_FR_FR() const { return DString(I_("There is no Mutual Fund Systematic Processing Date Table (P47) record for SYSTRAN processing.")); }
		virtual DString GetMessage_DE_DE() const { return DString(I_("Es gibt keine Mutual Fund Systematic Processing-Datentabellen (P47)-Eintrag für die SYSTRAN-Verarbeitung.")); }
		virtual DString GetMessage_ES_ES() const { return DString(I_("No hay un registro de Tabla de fechas de procesamiento sistemático de fondo mutuo (P47) para el procesamiento SYSTRAN.")); }
		virtual DString GetMessage_FR_CA() const { return DString(I_("Il n'y a aucun enregistrement de tableau de date de traitement systématique de fonds commun de placement (P47) pour le traitement SYSTRAN.")); }
		virtual DString GetMessage_NL_NL() const { return DString(I_("Er is geen P47-record (datumtabel systematisch verwerken beleggingsfonds) voor SYSTRAN-verwerking")); }

        // Actions
		virtual DString GetAction_EN_US() const { return DString(I_("Contact a client service representative and report this message.")); }
		virtual DString GetAction_FR_FR() const { return DString(I_("Contact a client service representative and report this message.")); }
		virtual DString GetAction_DE_DE() const { return DString(I_("Wenden Sie sich an einen Kundendienstmitarbeiter und teilen Sie ihm die Meldung mit.")); }
		virtual DString GetAction_ES_ES() const { return DString(I_("Notifique de este mensaje a un representante de servicio al cliente.")); }
		virtual DString GetAction_FR_CA() const { return DString(I_("Communiquez avec un représentant du service à la clientèle et signalez ce message.")); }
		virtual DString GetAction_NL_NL() const { return DString(I_("Neem contact op met een medewerker van de klantendienst en meld dit bericht")); }
	};
}



