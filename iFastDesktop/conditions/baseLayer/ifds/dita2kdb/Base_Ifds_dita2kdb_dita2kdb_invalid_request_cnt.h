#pragma once

#include "ConditionObject.h"

namespace CND
{
	class CBase_Ifds_dita2kdb_dita2kdb_invalid_request_cnt : public CConditionObject
	{
	public:
		CBase_Ifds_dita2kdb_dita2kdb_invalid_request_cnt() { }
		~CBase_Ifds_dita2kdb_dita2kdb_invalid_request_cnt() { }

	public:
		// General
		virtual DString GetConditionName() const { return DString(I_("DITA2KDB_INVALID_REQUEST_CNT")); }
		virtual DString GetGroupName() const { return DString(I_("ifds")); }
		virtual DString GetModuleName() const { return DString(I_("dita2kdb")); }
		virtual int GetSeverity() const { return 6; }

		// Messages
		virtual DString GetMessage_EN_US() const { return DString(I_("There is an internal problem.  %CMD% command must run modelessly.  (Attempted to run modally.)")); }
		virtual DString GetMessage_FR_FR() const { return DString(I_("There is an internal problem.  %CMD% command must run modelessly.  (Attempted to run modally.)")); }
		virtual DString GetMessage_DE_DE() const { return DString(I_("Zugriff verweigert – Nach der vorgeschriebenen Abmeldezeit.")); }
		virtual DString GetMessage_ES_ES() const { return DString(I_("Hay un problema interno. El comando %CMD% debe ejecutarse sin modo.  (Se intentó ejecutarlo modalmente.)")); }
		virtual DString GetMessage_FR_CA() const { return DString(I_("Il y a un problème interne. La commande %COMMAND% doit s'exécuter de façon modale (tentative de s'exécuter de façon modale).")); }
		virtual DString GetMessage_NL_NL() const { return DString(I_("Er is een intern probleem. Opdracht %CMD% moet niet-modusgebonden worden uitgevoerd.  (Modusgebonden uitvoering geprobeerd.)")); }

        // Actions
		virtual DString GetAction_EN_US() const { return DString(I_("Contact a support representative and report this message.")); }
		virtual DString GetAction_FR_FR() const { return DString(I_("Contactez un representant en assitance technique et communiquez-lui ce message.")); }
		virtual DString GetAction_DE_DE() const { return DString(I_("Contact a support representative and report this message.")); }
		virtual DString GetAction_ES_ES() const { return DString(I_("Notifique de este mensaje a un representante de soporte técnico.")); }
		virtual DString GetAction_FR_CA() const { return DString(I_("Communiquez avec un représentant technique et signalez ce message.")); }
		virtual DString GetAction_NL_NL() const { return DString(I_("Neem contact op met een supportmedewerker en meld dit bericht.")); }
	};
}



