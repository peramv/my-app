#pragma once

#include "ConditionObject.h"

namespace CND
{
	class CIFast_IFast_dita2kdb_dita2kdb_systran_severe_error : public CConditionObject
	{
	public:
		CIFast_IFast_dita2kdb_dita2kdb_systran_severe_error() { }
		~CIFast_IFast_dita2kdb_dita2kdb_systran_severe_error() { }

	public:
		// General
		virtual DString GetConditionName() const { return DString(I_("DITA2KDB_SYSTRAN_SEVERE_ERROR")); }
		virtual DString GetGroupName() const { return DString(I_("iFast")); }
		virtual DString GetModuleName() const { return DString(I_("dita2kdb")); }
		virtual int GetSeverity() const { return 6; }

		// Messages
		virtual DString GetMessage_EN_US() const { return DString(I_("No management companies were found.")); }
		virtual DString GetMessage_FR_FR() const { return DString(I_("Impossible de trouver des societes de gestion.")); }
		virtual DString GetMessage_DE_DE() const { return DString(I_("Es wurden keine Management-Unternehmen gefunden.")); }
		virtual DString GetMessage_ES_ES() const { return DString(I_("No se encontraron compañías administradoras.")); }
		virtual DString GetMessage_FR_CA() const { return DString(I_("Aucun environnement n'a été trouvé.")); }
		virtual DString GetMessage_NL_NL() const { return DString(I_("Er zijn geen beheerbedrijven gevonden")); }

        // Actions
		virtual DString GetAction_EN_US() const { return DString(I_("Report this message to a System Administrator")); }
		virtual DString GetAction_FR_FR() const { return DString(I_("Communiquez ce message a l'administrateur systeme")); }
		virtual DString GetAction_DE_DE() const { return DString(I_("Geben Sie diese Meldung an einen Systemadministrator weiter")); }
		virtual DString GetAction_ES_ES() const { return DString(I_("Report this message to a System Administrator")); }
		virtual DString GetAction_FR_CA() const { return DString(I_("Signalez ce message à un administrateur de système.")); }
		virtual DString GetAction_NL_NL() const { return DString(I_("Meld dit bericht aan een systeembeheerder")); }
	};
}



