#pragma once

#include "ConditionObject.h"

namespace CND
{
	class CIFast_IFast_dita2kdb_dita2kdb_ws00221c_resp_last_cum_nbr_assign : public CConditionObject
	{
	public:
		CIFast_IFast_dita2kdb_dita2kdb_ws00221c_resp_last_cum_nbr_assign() { }
		~CIFast_IFast_dita2kdb_dita2kdb_ws00221c_resp_last_cum_nbr_assign() { }

	public:
		// General
		virtual DString GetConditionName() const { return DString(I_("DITA2KDB_WS00221C_RESP_LAST_CUM_NBR_ASSIGN")); }
		virtual DString GetGroupName() const { return DString(I_("iFast")); }
		virtual DString GetModuleName() const { return DString(I_("dita2kdb")); }
		virtual int GetSeverity() const { return 6; }

		// Messages
		virtual DString GetMessage_EN_US() const { return DString(I_("Amount entered is greater than that available for Fund.")); }
		virtual DString GetMessage_FR_FR() const { return DString(I_("Amount entered is greater than that available for Fund.")); }
		virtual DString GetMessage_DE_DE() const { return DString(I_("Der eingegebene Betrag ist größer als der für einen Fonds verfügbare Betrag.")); }
		virtual DString GetMessage_ES_ES() const { return DString(I_("El monto introducido es mayor que el monto disponible para el fondo")); }
		virtual DString GetMessage_FR_CA() const { return DString(I_("Le montant saisi est supérieur au montant disponible pour le fonds.")); }
		virtual DString GetMessage_NL_NL() const { return DString(I_("Opgegeven bedrag is groter dan beschikbaar voor het fonds")); }

        // Actions
	};
}



