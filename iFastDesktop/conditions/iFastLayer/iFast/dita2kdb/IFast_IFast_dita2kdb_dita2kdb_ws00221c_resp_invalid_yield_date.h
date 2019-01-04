#pragma once

#include "ConditionObject.h"

namespace CND
{
	class CIFast_IFast_dita2kdb_dita2kdb_ws00221c_resp_invalid_yield_date : public CConditionObject
	{
	public:
		CIFast_IFast_dita2kdb_dita2kdb_ws00221c_resp_invalid_yield_date() { }
		~CIFast_IFast_dita2kdb_dita2kdb_ws00221c_resp_invalid_yield_date() { }

	public:
		// General
		virtual DString GetConditionName() const { return DString(I_("DITA2KDB_WS00221C_RESP_INVALID_YIELD_DATE")); }
		virtual DString GetGroupName() const { return DString(I_("iFast")); }
		virtual DString GetModuleName() const { return DString(I_("dita2kdb")); }
		virtual int GetSeverity() const { return 6; }

		// Messages
		virtual DString GetMessage_EN_US() const { return DString(I_("Allocation total does not equal to the trading amount.")); }
		virtual DString GetMessage_FR_FR() const { return DString(I_("Allocation total does not equal to the trading amount.")); }
		virtual DString GetMessage_DE_DE() const { return DString(I_("Die Zuweisungssumme stimmt nicht mit dem Handelsbetrag überein.")); }
		virtual DString GetMessage_ES_ES() const { return DString(I_("El total de asignación no es igual al monto de la operación")); }
		virtual DString GetMessage_FR_CA() const { return DString(I_("Le total de répartition n'est pas égal au montant de l'opération.")); }
		virtual DString GetMessage_NL_NL() const { return DString(I_("Allocatietotaal is niet gelijk aan handelsbedrag")); }

        // Actions
	};
}



