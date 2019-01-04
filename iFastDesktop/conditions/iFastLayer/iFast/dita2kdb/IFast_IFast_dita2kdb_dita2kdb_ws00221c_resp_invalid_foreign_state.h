#pragma once

#include "ConditionObject.h"

namespace CND
{
	class CIFast_IFast_dita2kdb_dita2kdb_ws00221c_resp_invalid_foreign_state : public CConditionObject
	{
	public:
		CIFast_IFast_dita2kdb_dita2kdb_ws00221c_resp_invalid_foreign_state() { }
		~CIFast_IFast_dita2kdb_dita2kdb_ws00221c_resp_invalid_foreign_state() { }

	public:
		// General
		virtual DString GetConditionName() const { return DString(I_("DITA2KDB_WS00221C_RESP_INVALID_FOREIGN_STATE")); }
		virtual DString GetGroupName() const { return DString(I_("iFast")); }
		virtual DString GetModuleName() const { return DString(I_("dita2kdb")); }
		virtual int GetSeverity() const { return 6; }

		// Messages
		virtual DString GetMessage_EN_US() const { return DString(I_("Amount is mandatory, should be greater than 0.")); }
		virtual DString GetMessage_FR_FR() const { return DString(I_("Amount is mandatory, should be greater than 0.")); }
		virtual DString GetMessage_DE_DE() const { return DString(I_("Betrag ist obligatorisch, sollte größer als 0 sein.")); }
		virtual DString GetMessage_ES_ES() const { return DString(I_("El monto es obligatorio, debe ser mayor que 0.")); }
		virtual DString GetMessage_FR_CA() const { return DString(I_("Le montant est requis et devrait être supérieur à zéro.")); }
		virtual DString GetMessage_NL_NL() const { return DString(I_("Bedrag is verplicht, moet groter dan nul zijn")); }

        // Actions
	};
}



