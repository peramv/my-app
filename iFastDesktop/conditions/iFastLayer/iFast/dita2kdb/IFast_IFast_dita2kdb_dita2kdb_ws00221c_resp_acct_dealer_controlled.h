#pragma once

#include "ConditionObject.h"

namespace CND
{
	class CIFast_IFast_dita2kdb_dita2kdb_ws00221c_resp_acct_dealer_controlled : public CConditionObject
	{
	public:
		CIFast_IFast_dita2kdb_dita2kdb_ws00221c_resp_acct_dealer_controlled() { }
		~CIFast_IFast_dita2kdb_dita2kdb_ws00221c_resp_acct_dealer_controlled() { }

	public:
		// General
		virtual DString GetConditionName() const { return DString(I_("DITA2KDB_WS00221C_RESP_ACCT_DEALER_CONTROLLED")); }
		virtual DString GetGroupName() const { return DString(I_("iFast")); }
		virtual DString GetModuleName() const { return DString(I_("dita2kdb")); }
		virtual int GetSeverity() const { return 6; }

		// Messages
		virtual DString GetMessage_EN_US() const { return DString(I_("Fractional values not allowed.")); }
		virtual DString GetMessage_FR_FR() const { return DString(I_("Les valeurs fractionnaires ne sont pas autorisées.")); }
		virtual DString GetMessage_DE_DE() const { return DString(I_("Bruchwerte sind nicht erlaubt.")); }
		virtual DString GetMessage_ES_ES() const { return DString(I_("No se permiten valores fraccionarios.")); }
		virtual DString GetMessage_FR_CA() const { return DString(I_("Les valeurs fractionnelles ne sont pas autorisées.")); }
		virtual DString GetMessage_NL_NL() const { return DString(I_("Fractionele waarden zijn niet toegestaan")); }

        // Actions
	};
}



