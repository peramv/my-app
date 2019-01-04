#pragma once

#include "ConditionObject.h"

namespace CND
{
	class CIFast_IFast_dita2kdb_dita2kdb_ws00221c_resp_invalid_lot_value : public CConditionObject
	{
	public:
		CIFast_IFast_dita2kdb_dita2kdb_ws00221c_resp_invalid_lot_value() { }
		~CIFast_IFast_dita2kdb_dita2kdb_ws00221c_resp_invalid_lot_value() { }

	public:
		// General
		virtual DString GetConditionName() const { return DString(I_("DITA2KDB_WS00221C_RESP_INVALID_LOT_VALUE")); }
		virtual DString GetGroupName() const { return DString(I_("iFast")); }
		virtual DString GetModuleName() const { return DString(I_("dita2kdb")); }
		virtual int GetSeverity() const { return 6; }

		// Messages
		virtual DString GetMessage_EN_US() const { return DString(I_("No Qualified original purchase for commission rebate.")); }
		virtual DString GetMessage_FR_FR() const { return DString(I_("No Qualified original purchase for commission rebate.")); }
		virtual DString GetMessage_DE_DE() const { return DString(I_("Kein eingeschränkter Originalkauf für Provisions Provisionsabzug")); }
		virtual DString GetMessage_ES_ES() const { return DString(I_("No hay un compra original calificada para reembolso de comisión.")); }
		virtual DString GetMessage_FR_CA() const { return DString(I_("Aucun achat d'origine n'est qualifié pour une remise de commission.")); }
		virtual DString GetMessage_NL_NL() const { return DString(I_("Geen gekwalificeerde originele aankoop voor commissiekorting")); }

        // Actions
	};
}



