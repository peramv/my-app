#pragma once

#include "ConditionObject.h"

namespace CND
{
	class CIFast_IFast_dita2kdb_dita2kdb_ws00221c_resp_acct_coded_bank_card : public CConditionObject
	{
	public:
		CIFast_IFast_dita2kdb_dita2kdb_ws00221c_resp_acct_coded_bank_card() { }
		~CIFast_IFast_dita2kdb_dita2kdb_ws00221c_resp_acct_coded_bank_card() { }

	public:
		// General
		virtual DString GetConditionName() const { return DString(I_("DITA2KDB_WS00221C_RESP_ACCT_CODED_BANK_CARD")); }
		virtual DString GetGroupName() const { return DString(I_("iFast")); }
		virtual DString GetModuleName() const { return DString(I_("dita2kdb")); }
		virtual int GetSeverity() const { return 6; }

		// Messages
		virtual DString GetMessage_EN_US() const { return DString(I_("When Accounts Amount is zero, only funds percent is allowed.")); }
		virtual DString GetMessage_FR_FR() const { return DString(I_("Lorsque Montant des comptes est egal a zero, seul le pourcentage des fonds est autorisé.")); }
		virtual DString GetMessage_DE_DE() const { return DString(I_("Wenn der Kontenbetrag null beträgt, ist nur Fonds-Prozent erlaubt.")); }
		virtual DString GetMessage_ES_ES() const { return DString(I_("Cuando Monto de las cuentas es cero, sólo se permiten porcentajes de los fondos.")); }
		virtual DString GetMessage_FR_CA() const { return DString(I_("Quand le montant des comptes est zéro, seul le pourcentage des fonds est autorisé.")); }
		virtual DString GetMessage_NL_NL() const { return DString(I_("Als het accountbedrag nul is, is alleen een fondspercentage toegestaan")); }

        // Actions
	};
}



