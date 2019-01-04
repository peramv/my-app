#pragma once

#include "ConditionObject.h"

namespace CND
{
	class CIFast_IFast_dita2kdb_dita2kdb_ws00221c_resp_request_on_uninit_tbl : public CConditionObject
	{
	public:
		CIFast_IFast_dita2kdb_dita2kdb_ws00221c_resp_request_on_uninit_tbl() { }
		~CIFast_IFast_dita2kdb_dita2kdb_ws00221c_resp_request_on_uninit_tbl() { }

	public:
		// General
		virtual DString GetConditionName() const { return DString(I_("DITA2KDB_WS00221C_RESP_REQUEST_ON_UNINIT_TBL")); }
		virtual DString GetGroupName() const { return DString(I_("iFast")); }
		virtual DString GetModuleName() const { return DString(I_("dita2kdb")); }
		virtual int GetSeverity() const { return 6; }

		// Messages
		virtual DString GetMessage_EN_US() const { return DString(I_("Transaction type invalid.")); }
		virtual DString GetMessage_FR_FR() const { return DString(I_("Transaction type invalid.")); }
		virtual DString GetMessage_DE_DE() const { return DString(I_("Transaktionsart ungültig.")); }
		virtual DString GetMessage_ES_ES() const { return DString(I_("Tipo de transacción no válido.")); }
		virtual DString GetMessage_FR_CA() const { return DString(I_("Type de transaction invalide")); }
		virtual DString GetMessage_NL_NL() const { return DString(I_("Transactietype is ongeldig")); }

        // Actions
	};
}



