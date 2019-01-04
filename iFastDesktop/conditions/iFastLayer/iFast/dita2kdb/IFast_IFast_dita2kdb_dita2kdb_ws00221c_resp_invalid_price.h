#pragma once

#include "ConditionObject.h"

namespace CND
{
	class CIFast_IFast_dita2kdb_dita2kdb_ws00221c_resp_invalid_price : public CConditionObject
	{
	public:
		CIFast_IFast_dita2kdb_dita2kdb_ws00221c_resp_invalid_price() { }
		~CIFast_IFast_dita2kdb_dita2kdb_ws00221c_resp_invalid_price() { }

	public:
		// General
		virtual DString GetConditionName() const { return DString(I_("DITA2KDB_WS00221C_RESP_INVALID_PRICE")); }
		virtual DString GetGroupName() const { return DString(I_("iFast")); }
		virtual DString GetModuleName() const { return DString(I_("dita2kdb")); }
		virtual int GetSeverity() const { return 6; }

		// Messages
		virtual DString GetMessage_EN_US() const { return DString(I_("The allocation amount can not be greater than the total amount.")); }
		virtual DString GetMessage_FR_FR() const { return DString(I_("The allocation amount can not be greater than the total amount.")); }
		virtual DString GetMessage_DE_DE() const { return DString(I_("Der Zuweisungsbetrag darf nicht größer als der Gesamtbetrag sein.")); }
		virtual DString GetMessage_ES_ES() const { return DString(I_("El monto de asignación no puede ser mayor que el monto total.")); }
		virtual DString GetMessage_FR_CA() const { return DString(I_("Le montant de répartition ne peut excéder le montant total.")); }
		virtual DString GetMessage_NL_NL() const { return DString(I_("Het allocatiebedrag kan niet groter zijn dan het totale bedrag")); }

        // Actions
	};
}



