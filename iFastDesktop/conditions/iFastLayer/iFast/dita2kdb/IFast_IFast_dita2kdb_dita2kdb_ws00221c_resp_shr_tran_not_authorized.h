#pragma once

#include "ConditionObject.h"

namespace CND
{
	class CIFast_IFast_dita2kdb_dita2kdb_ws00221c_resp_shr_tran_not_authorized : public CConditionObject
	{
	public:
		CIFast_IFast_dita2kdb_dita2kdb_ws00221c_resp_shr_tran_not_authorized() { }
		~CIFast_IFast_dita2kdb_dita2kdb_ws00221c_resp_shr_tran_not_authorized() { }

	public:
		// General
		virtual DString GetConditionName() const { return DString(I_("DITA2KDB_WS00221C_RESP_SHR_TRAN_NOT_AUTHORIZED")); }
		virtual DString GetGroupName() const { return DString(I_("iFast")); }
		virtual DString GetModuleName() const { return DString(I_("dita2kdb")); }
		virtual int GetSeverity() const { return 6; }

		// Messages
		virtual DString GetMessage_EN_US() const { return DString(I_("Maximum Amount is greater than current Account Value.")); }
		virtual DString GetMessage_FR_FR() const { return DString(I_("Maximum Amount is greater than current Account Value.")); }
		virtual DString GetMessage_DE_DE() const { return DString(I_("Maximaler Betrag ist größer als der aktuelle Kontowert.")); }
		virtual DString GetMessage_ES_ES() const { return DString(I_("El monto máximo es mayor que el valor actual de la cuenta.")); }
		virtual DString GetMessage_FR_CA() const { return DString(I_("Le montant maximal excède la valeur du compte courant.")); }
		virtual DString GetMessage_NL_NL() const { return DString(I_("Maximumbedrag is groter dan de huidige accountwaarde")); }

        // Actions
	};
}



