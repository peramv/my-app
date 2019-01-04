#pragma once

#include "ConditionObject.h"

namespace CND
{
	class CIFast_IFast_dita2kdb_dita2kdb_ws00221c_resp_invalid_pre_agreement : public CConditionObject
	{
	public:
		CIFast_IFast_dita2kdb_dita2kdb_ws00221c_resp_invalid_pre_agreement() { }
		~CIFast_IFast_dita2kdb_dita2kdb_ws00221c_resp_invalid_pre_agreement() { }

	public:
		// General
		virtual DString GetConditionName() const { return DString(I_("DITA2KDB_WS00221C_RESP_INVALID_PRE_AGREEMENT")); }
		virtual DString GetGroupName() const { return DString(I_("iFast")); }
		virtual DString GetModuleName() const { return DString(I_("dita2kdb")); }
		virtual int GetSeverity() const { return 6; }

		// Messages
		virtual DString GetMessage_EN_US() const { return DString(I_("Invalid Transaction ID.  Pending trade does not exist.")); }
		virtual DString GetMessage_FR_FR() const { return DString(I_("Invalid Transaction ID.  Pending trade does not exist.")); }
		virtual DString GetMessage_DE_DE() const { return DString(I_("Ungültige Transaktions-ID. Schwebender Handel existiert nicht.")); }
		virtual DString GetMessage_ES_ES() const { return DString(I_("Identificación de transacción no válida. La operación pendiente no existe.")); }
		virtual DString GetMessage_FR_CA() const { return DString(I_("Code de transaction invalide. Transaction en suspens inexistante.")); }
		virtual DString GetMessage_NL_NL() const { return DString(I_("Ongeldig transactie-ID. In behandeling zijnde transactie bestaat niet")); }

        // Actions
	};
}



