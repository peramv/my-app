#pragma once

#include "ConditionObject.h"

namespace CND
{
	class CIFast_IFast_dita2kdb_dita2kdb_ws00221c_resp_invalid_rein_dollar : public CConditionObject
	{
	public:
		CIFast_IFast_dita2kdb_dita2kdb_ws00221c_resp_invalid_rein_dollar() { }
		~CIFast_IFast_dita2kdb_dita2kdb_ws00221c_resp_invalid_rein_dollar() { }

	public:
		// General
		virtual DString GetConditionName() const { return DString(I_("DITA2KDB_WS00221C_RESP_INVALID_REIN_DOLLAR")); }
		virtual DString GetGroupName() const { return DString(I_("iFast")); }
		virtual DString GetModuleName() const { return DString(I_("dita2kdb")); }
		virtual int GetSeverity() const { return 6; }

		// Messages
		virtual DString GetMessage_EN_US() const { return DString(I_("Invalid Settlement Date. Next valid settlement date is %SETTLEDATE%.")); }
		virtual DString GetMessage_FR_FR() const { return DString(I_("Date de reglement invalide. La date de reglement valide suivante est %SETTLEDATE%")); }
		virtual DString GetMessage_DE_DE() const { return DString(I_("Ungültiges Abrechnungsdatum. Nächstes gültiges Abrechnungsdatum ist %SETTLEDATE%.")); }
		virtual DString GetMessage_ES_ES() const { return DString(I_("Fecha de liquidación no válida. La siguiente fecha de liquidación válida es %SETTLEDATE%")); }
		virtual DString GetMessage_FR_CA() const { return DString(I_("Date de règlement invalide. La prochaine date de règlement valide est le %SETTLEDATE%.")); }
		virtual DString GetMessage_NL_NL() const { return DString(I_("Ongeldige betalingsdatum. Volgende geldige betalingsdatum is %SETTLEDATE%")); }

        // Actions
	};
}



