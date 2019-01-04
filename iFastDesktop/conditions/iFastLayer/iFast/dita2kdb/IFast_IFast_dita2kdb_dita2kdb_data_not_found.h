#pragma once

#include "ConditionObject.h"

namespace CND
{
	class CIFast_IFast_dita2kdb_dita2kdb_data_not_found : public CConditionObject
	{
	public:
		CIFast_IFast_dita2kdb_dita2kdb_data_not_found() { }
		~CIFast_IFast_dita2kdb_dita2kdb_data_not_found() { }

	public:
		// General
		virtual DString GetConditionName() const { return DString(I_("DITA2KDB_DATA_NOT_FOUND")); }
		virtual DString GetGroupName() const { return DString(I_("iFast")); }
		virtual DString GetModuleName() const { return DString(I_("dita2kdb")); }
		virtual int GetSeverity() const { return 6; }

		// Messages
		virtual DString GetMessage_EN_US() const { return DString(I_("There is an internal problem.  Method initialization has already been called.")); }
		virtual DString GetMessage_FR_FR() const { return DString(I_("There is an internal problem.  Method initialization has already been called.")); }
		virtual DString GetMessage_DE_DE() const { return DString(I_("Es gibt ein internes Problem.  Methoden-Initialisierung wurde bereits aufgerufen.")); }
		virtual DString GetMessage_ES_ES() const { return DString(I_("Hay un problema interno.  Ya se llamó el método init.")); }
		virtual DString GetMessage_FR_CA() const { return DString(I_("Il y a un problème interne. L'initialisation de la méthode a déjà été appelée.")); }
		virtual DString GetMessage_NL_NL() const { return DString(I_("Er is een intern probleem.  Methode init is al aangeroepen")); }

        // Actions
		virtual DString GetAction_EN_US() const { return DString(I_("Contact a support representative and report this message.")); }
		virtual DString GetAction_FR_FR() const { return DString(I_("Contactez un representant en assitance technique et communiquez-lui ce message.")); }
		virtual DString GetAction_DE_DE() const { return DString(I_("Wenden Sie sich an einen Support-Mitarbeiter und teilen Sie ihm die Meldung mit.")); }
		virtual DString GetAction_ES_ES() const { return DString(I_("Contact a support representative and report this message.")); }
		virtual DString GetAction_FR_CA() const { return DString(I_("Communiquez avec un représentant technique et signalez ce message.")); }
		virtual DString GetAction_NL_NL() const { return DString(I_("Neem contact op met een supportmedewerker en meld dit bericht")); }
	};
}



