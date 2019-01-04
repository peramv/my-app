﻿#pragma once

#include "ConditionObject.h"

namespace CND
{
	class CIFast_Infrastructure_ifastdbrkr_err_unable_to_add_record_shareholder_exists : public CConditionObject
	{
	public:
		CIFast_Infrastructure_ifastdbrkr_err_unable_to_add_record_shareholder_exists() { }
		~CIFast_Infrastructure_ifastdbrkr_err_unable_to_add_record_shareholder_exists() { }

	public:
		// General
		virtual DString GetConditionName() const { return DString(I_("ERR_UNABLE_TO_ADD_RECORD_SHAREHOLDER_EXISTS")); }
		virtual DString GetGroupName() const { return DString(I_("Infrastructure")); }
		virtual DString GetModuleName() const { return DString(I_("ifastdbrkr")); }
		virtual int GetSeverity() const { return 6; }

		// Messages
		virtual DString GetMessage_EN_US() const { return DString(I_("ODBC Error returned: %SQL_ERROR%")); }
		virtual DString GetMessage_FR_FR() const { return DString(I_("ODBC Error returned: %SQL_ERROR%")); }
		virtual DString GetMessage_DE_DE() const { return DString(I_("ODBC-Fehler zurückgegeben: %SQL_ERROR%")); }
		virtual DString GetMessage_ES_ES() const { return DString(I_("Se devolvió un error ODBC: %SQL_ERROR%")); }
		virtual DString GetMessage_FR_CA() const { return DString(I_("Retour d'erreur de l'interface ODBC : %SQL_ERROR%")); }
		virtual DString GetMessage_NL_NL() const { return DString(I_("ODBC-fout geretourneerd: %SQL_ERROR%")); }

        // Actions
		virtual DString GetAction_EN_US() const { return DString(I_("Contact a support representative and report this message.")); }
		virtual DString GetAction_FR_FR() const { return DString(I_("Contactez un representant en assitance technique et communiquez-lui ce message.")); }
		virtual DString GetAction_DE_DE() const { return DString(I_("Wenden Sie sich an einen Support-Mitarbeiter und teilen Sie ihm die Meldung mit.")); }
		virtual DString GetAction_ES_ES() const { return DString(I_("Contact a support representative and report this message.")); }
		virtual DString GetAction_FR_CA() const { return DString(I_("Communiquez avec un représentant technique et signalez ce message.")); }
		virtual DString GetAction_NL_NL() const { return DString(I_("Neem contact op met een supportmedewerker en meld dit bericht")); }
	};
}



