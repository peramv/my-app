#pragma once

#include "ConditionObject.h"

namespace CND
{
	class CIFast_IFast_dita2kdb_dita2kdb_ws00221c_resp_invalid_no_spc_ctyst_cd : public CConditionObject
	{
	public:
		CIFast_IFast_dita2kdb_dita2kdb_ws00221c_resp_invalid_no_spc_ctyst_cd() { }
		~CIFast_IFast_dita2kdb_dita2kdb_ws00221c_resp_invalid_no_spc_ctyst_cd() { }

	public:
		// General
		virtual DString GetConditionName() const { return DString(I_("DITA2KDB_WS00221C_RESP_INVALID_NO_SPC_CTYST_CD")); }
		virtual DString GetGroupName() const { return DString(I_("iFast")); }
		virtual DString GetModuleName() const { return DString(I_("dita2kdb")); }
		virtual int GetSeverity() const { return 6; }

		// Messages
		virtual DString GetMessage_EN_US() const { return DString(I_("Fund %FUND% is capped.  Verify if transaction is allowed.")); }
		virtual DString GetMessage_FR_FR() const { return DString(I_("Error: %MESSAGE%.")); }
		virtual DString GetMessage_DE_DE() const { return DString(I_("Fonds %FUND% ist abgeschlossen. Überprüfen Sie, ob Transaktion zugelassen ist.")); }
		virtual DString GetMessage_ES_ES() const { return DString(I_("El fondo %FUND% tiene un tope. Verifique si se permite la transacción.")); }
		virtual DString GetMessage_FR_CA() const { return DString(I_("Le fonds %FUND% est plafonné. Vérifiez si la transaction est autorisée.")); }
		virtual DString GetMessage_NL_NL() const { return DString(I_("Fonds %FUND% is aan grenzen gebonden. Controleer of transactie is toegestaan")); }

        // Actions
	};
}



