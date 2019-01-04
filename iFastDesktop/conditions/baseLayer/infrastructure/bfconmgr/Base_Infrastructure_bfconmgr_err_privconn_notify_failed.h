#pragma once

#include "ConditionObject.h"

namespace CND
{
	class CBase_Infrastructure_bfconmgr_err_privconn_notify_failed : public CConditionObject
	{
	public:
		CBase_Infrastructure_bfconmgr_err_privconn_notify_failed() { }
		~CBase_Infrastructure_bfconmgr_err_privconn_notify_failed() { }

	public:
		// General
		virtual DString GetConditionName() const { return DString(I_("ERR_PRIVCONN_NOTIFY_FAILED")); }
		virtual DString GetGroupName() const { return DString(I_("Infrastructure")); }
		virtual DString GetModuleName() const { return DString(I_("bfconmgr")); }
		virtual int GetSeverity() const { return 7; }

		// Messages
		virtual DString GetMessage_EN_US() const { return DString(I_("The system does not recognize accumulator years.")); }
		virtual DString GetMessage_FR_FR() const { return DString(I_("The system does not recognize accumulator years.")); }
		virtual DString GetMessage_DE_DE() const { return DString(I_("Es gibt ein internes Problem.\n\nAWD-Container konnte nicht geöffnet werden.")); }
		virtual DString GetMessage_ES_ES() const { return DString(I_("El sistema no reconoce los años de acumulación.")); }
		virtual DString GetMessage_FR_CA() const { return DString(I_("Il y a un problème interne. \n\n Échec d'ouverture du conteneur AWD.")); }
		virtual DString GetMessage_NL_NL() const { return DString(I_("Er is een intern probleem.\n\nAWD-container kon niet worden geopend")); }

        // Actions
		virtual DString GetAction_EN_US() const { return DString(I_("Verify accumulator years and re-enter.")); }
		virtual DString GetAction_FR_FR() const { return DString(I_("Verify accumulator years and re-enter.")); }
		virtual DString GetAction_DE_DE() const { return DString(I_("Wenden Sie sich an einen Support-Mitarbeiter und teilen Sie ihm die Meldung mit.")); }
		virtual DString GetAction_ES_ES() const { return DString(I_("Verifique los años acumulados y vuelva a introducirlos.")); }
		virtual DString GetAction_FR_CA() const { return DString(I_("Communiquez avec un représentant technique et signalez ce message.")); }
		virtual DString GetAction_NL_NL() const { return DString(I_("Neem contact op met een supportmedewerker en meld dit bericht")); }
	};
}



