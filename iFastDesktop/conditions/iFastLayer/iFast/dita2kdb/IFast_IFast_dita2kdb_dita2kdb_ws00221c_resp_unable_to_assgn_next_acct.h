#pragma once

#include "ConditionObject.h"

namespace CND
{
	class CIFast_IFast_dita2kdb_dita2kdb_ws00221c_resp_unable_to_assgn_next_acct : public CConditionObject
	{
	public:
		CIFast_IFast_dita2kdb_dita2kdb_ws00221c_resp_unable_to_assgn_next_acct() { }
		~CIFast_IFast_dita2kdb_dita2kdb_ws00221c_resp_unable_to_assgn_next_acct() { }

	public:
		// General
		virtual DString GetConditionName() const { return DString(I_("DITA2KDB_WS00221C_RESP_UNABLE_TO_ASSGN_NEXT_ACCT")); }
		virtual DString GetGroupName() const { return DString(I_("iFast")); }
		virtual DString GetModuleName() const { return DString(I_("dita2kdb")); }
		virtual int GetSeverity() const { return 6; }

		// Messages
		virtual DString GetMessage_EN_US() const { return DString(I_("Payment Amount is below minimum.")); }
		virtual DString GetMessage_FR_FR() const { return DString(I_("Payment Amount is below minimum.")); }
		virtual DString GetMessage_DE_DE() const { return DString(I_("Zahlungsbetrag liegt unter dem Minimum.")); }
		virtual DString GetMessage_ES_ES() const { return DString(I_("El monto de pago se encuentra por debajo del mínimo.")); }
		virtual DString GetMessage_FR_CA() const { return DString(I_("Le montant du paiement est inférieur au minimum.")); }
		virtual DString GetMessage_NL_NL() const { return DString(I_("Betalingsbedrag ligt onder het minimum")); }

        // Actions
	};
}



