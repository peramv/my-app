#pragma once

#include "ConditionObject.h"

namespace CND
{
	class CIFast_IFast_dita2kdb_dita2kdb_ws00221c_resp_account_is_ppa : public CConditionObject
	{
	public:
		CIFast_IFast_dita2kdb_dita2kdb_ws00221c_resp_account_is_ppa() { }
		~CIFast_IFast_dita2kdb_dita2kdb_ws00221c_resp_account_is_ppa() { }

	public:
		// General
		virtual DString GetConditionName() const { return DString(I_("DITA2KDB_WS00221C_RESP_ACCOUNT_IS_PPA")); }
		virtual DString GetGroupName() const { return DString(I_("iFast")); }
		virtual DString GetModuleName() const { return DString(I_("dita2kdb")); }
		virtual int GetSeverity() const { return 6; }

		// Messages
		virtual DString GetMessage_EN_US() const { return DString(I_("Rate must be zero if Suppress Tax is \"Yes\".")); }
		virtual DString GetMessage_FR_FR() const { return DString(I_("Rate must be zero if Suppress Tax is \"Yes\".")); }
		virtual DString GetMessage_DE_DE() const { return DString(I_("Satz muss Null sein, wenn Steuer unterdrücken auf \"Ja\" steht.")); }
		virtual DString GetMessage_ES_ES() const { return DString(I_("La tasa debe ser cero si Suprimir impuesto es \"Sí\".")); }
		virtual DString GetMessage_FR_CA() const { return DString(I_("Le taux doit être de zéro si la suppression de l'imposition est activée.")); }
		virtual DString GetMessage_NL_NL() const { return DString(I_("Tarief moet nul zijn als Belasting achterwege laten 'Ja' is")); }

        // Actions
	};
}



