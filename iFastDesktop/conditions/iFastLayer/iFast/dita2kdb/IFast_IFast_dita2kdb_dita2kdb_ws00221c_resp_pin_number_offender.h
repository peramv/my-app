#pragma once

#include "ConditionObject.h"

namespace CND
{
	class CIFast_IFast_dita2kdb_dita2kdb_ws00221c_resp_pin_number_offender : public CConditionObject
	{
	public:
		CIFast_IFast_dita2kdb_dita2kdb_ws00221c_resp_pin_number_offender() { }
		~CIFast_IFast_dita2kdb_dita2kdb_ws00221c_resp_pin_number_offender() { }

	public:
		// General
		virtual DString GetConditionName() const { return DString(I_("DITA2KDB_WS00221C_RESP_PIN_NUMBER_OFFENDER")); }
		virtual DString GetGroupName() const { return DString(I_("iFast")); }
		virtual DString GetModuleName() const { return DString(I_("dita2kdb")); }
		virtual int GetSeverity() const { return 6; }

		// Messages
		virtual DString GetMessage_EN_US() const { return DString(I_("Bank account number must be entered.")); }
		virtual DString GetMessage_FR_FR() const { return DString(I_("Bank account number must be entered.")); }
		virtual DString GetMessage_DE_DE() const { return DString(I_("Bankkontonummer muss eingegeben werden.")); }
		virtual DString GetMessage_ES_ES() const { return DString(I_("Debe introducirse el número de cuenta bancaria")); }
		virtual DString GetMessage_FR_CA() const { return DString(I_("Le numéro de compte bancaire est requis.")); }
		virtual DString GetMessage_NL_NL() const { return DString(I_("Nummer bankrekening moet worden ingevoerd")); }

        // Actions
	};
}



