#pragma once

#include "ConditionObject.h"

namespace CND
{
	class CIFast_IFast_dita2kdb_dita2kdb_ws00221c_resp_invalid_product_id : public CConditionObject
	{
	public:
		CIFast_IFast_dita2kdb_dita2kdb_ws00221c_resp_invalid_product_id() { }
		~CIFast_IFast_dita2kdb_dita2kdb_ws00221c_resp_invalid_product_id() { }

	public:
		// General
		virtual DString GetConditionName() const { return DString(I_("DITA2KDB_WS00221C_RESP_INVALID_PRODUCT_ID")); }
		virtual DString GetGroupName() const { return DString(I_("iFast")); }
		virtual DString GetModuleName() const { return DString(I_("dita2kdb")); }
		virtual int GetSeverity() const { return 6; }

		// Messages
		virtual DString GetMessage_EN_US() const { return DString(I_("Amount must be greater or equal to zero.")); }
		virtual DString GetMessage_FR_FR() const { return DString(I_("Amount must be greater or equal to zero.")); }
		virtual DString GetMessage_DE_DE() const { return DString(I_("Betrag muss größer oder gleich Null sein.")); }
		virtual DString GetMessage_ES_ES() const { return DString(I_("El monto debe ser superior o igual a cero.")); }
		virtual DString GetMessage_FR_CA() const { return DString(I_("Le montant doit être supérieur ou égal à zéro.")); }
		virtual DString GetMessage_NL_NL() const { return DString(I_("Bedrag moet groter zijn dan of gelijk aan nul")); }

        // Actions
	};
}



