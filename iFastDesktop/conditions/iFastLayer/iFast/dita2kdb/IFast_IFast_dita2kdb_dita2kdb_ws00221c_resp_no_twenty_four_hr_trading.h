#pragma once

#include "ConditionObject.h"

namespace CND
{
	class CIFast_IFast_dita2kdb_dita2kdb_ws00221c_resp_no_twenty_four_hr_trading : public CConditionObject
	{
	public:
		CIFast_IFast_dita2kdb_dita2kdb_ws00221c_resp_no_twenty_four_hr_trading() { }
		~CIFast_IFast_dita2kdb_dita2kdb_ws00221c_resp_no_twenty_four_hr_trading() { }

	public:
		// General
		virtual DString GetConditionName() const { return DString(I_("DITA2KDB_WS00221C_RESP_NO_TWENTY_FOUR_HR_TRADING")); }
		virtual DString GetGroupName() const { return DString(I_("iFast")); }
		virtual DString GetModuleName() const { return DString(I_("dita2kdb")); }
		virtual int GetSeverity() const { return 6; }

		// Messages
		virtual DString GetMessage_EN_US() const { return DString(I_("Effective Date is future dated.")); }
		virtual DString GetMessage_FR_FR() const { return DString(I_("Effective Date is future dated.")); }
		virtual DString GetMessage_DE_DE() const { return DString(I_("Effektivdatum liegt in der Zukunft.")); }
		virtual DString GetMessage_ES_ES() const { return DString(I_("La fecha de entrada en vigencia es futura.")); }
		virtual DString GetMessage_FR_CA() const { return DString(I_("La date d'entrée en vigueur est postérieure à la date actuelle.")); }
		virtual DString GetMessage_NL_NL() const { return DString(I_("Ingangsdatum ligt in de toekomst")); }

        // Actions
	};
}



