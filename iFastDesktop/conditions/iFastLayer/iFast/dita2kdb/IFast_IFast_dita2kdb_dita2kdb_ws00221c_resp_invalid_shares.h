#pragma once

#include "ConditionObject.h"

namespace CND
{
	class CIFast_IFast_dita2kdb_dita2kdb_ws00221c_resp_invalid_shares : public CConditionObject
	{
	public:
		CIFast_IFast_dita2kdb_dita2kdb_ws00221c_resp_invalid_shares() { }
		~CIFast_IFast_dita2kdb_dita2kdb_ws00221c_resp_invalid_shares() { }

	public:
		// General
		virtual DString GetConditionName() const { return DString(I_("DITA2KDB_WS00221C_RESP_INVALID_SHARES")); }
		virtual DString GetGroupName() const { return DString(I_("iFast")); }
		virtual DString GetModuleName() const { return DString(I_("dita2kdb")); }
		virtual int GetSeverity() const { return 6; }

		// Messages
		virtual DString GetMessage_EN_US() const { return DString(I_("Pay option must be either \"F\",\"M\",\"I\" or\" X\".")); }
		virtual DString GetMessage_FR_FR() const { return DString(I_("Pay option must be either \"F\",\"M\",\"I\" or\" X\".")); }
		virtual DString GetMessage_DE_DE() const { return DString(I_("Zahlungsoption muss \"F\",\"M\",\"I\" oder \"X\" sein.")); }
		virtual DString GetMessage_ES_ES() const { return DString(I_("La opción de pago debe ser \"F\",\"M\",\"I\" ó \" X\".")); }
		virtual DString GetMessage_FR_CA() const { return DString(I_("L'option de paiement doit être F, M, I ou X.")); }
		virtual DString GetMessage_NL_NL() const { return DString(I_("Betalingsoptie moet 'F', 'M', 'I' of 'X' zijn")); }

        // Actions
	};
}



