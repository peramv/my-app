#pragma once

#include "ConditionObject.h"

namespace CND
{
	class CIFast_IFast_dita2kdb_dita2kdb_ws00221c_resp_invalid_bank_micr_id : public CConditionObject
	{
	public:
		CIFast_IFast_dita2kdb_dita2kdb_ws00221c_resp_invalid_bank_micr_id() { }
		~CIFast_IFast_dita2kdb_dita2kdb_ws00221c_resp_invalid_bank_micr_id() { }

	public:
		// General
		virtual DString GetConditionName() const { return DString(I_("DITA2KDB_WS00221C_RESP_INVALID_BANK_MICR_ID")); }
		virtual DString GetGroupName() const { return DString(I_("iFast")); }
		virtual DString GetModuleName() const { return DString(I_("dita2kdb")); }
		virtual int GetSeverity() const { return 6; }

		// Messages
		virtual DString GetMessage_EN_US() const { return DString(I_("Trade in Unit not allowed for allocation transaction.")); }
		virtual DString GetMessage_FR_FR() const { return DString(I_("Trade in Unit not allowed for allocation transaction.")); }
		virtual DString GetMessage_DE_DE() const { return DString(I_("Handel in Anteilen für Zuweisungs-Transaktion nicht erlaubt.")); }
		virtual DString GetMessage_ES_ES() const { return DString(I_("No se permite operación en unidad para transacción de asignación")); }
		virtual DString GetMessage_FR_CA() const { return DString(I_("La transaction en unités n'est pas autorisée pour une transaction de répartition.")); }
		virtual DString GetMessage_NL_NL() const { return DString(I_("Handel in eenheid niet toegestaan voor allocatietransactie")); }

        // Actions
	};
}



