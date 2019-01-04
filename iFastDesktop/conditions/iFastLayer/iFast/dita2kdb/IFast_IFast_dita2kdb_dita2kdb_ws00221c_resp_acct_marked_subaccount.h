#pragma once

#include "ConditionObject.h"

namespace CND
{
	class CIFast_IFast_dita2kdb_dita2kdb_ws00221c_resp_acct_marked_subaccount : public CConditionObject
	{
	public:
		CIFast_IFast_dita2kdb_dita2kdb_ws00221c_resp_acct_marked_subaccount() { }
		~CIFast_IFast_dita2kdb_dita2kdb_ws00221c_resp_acct_marked_subaccount() { }

	public:
		// General
		virtual DString GetConditionName() const { return DString(I_("DITA2KDB_WS00221C_RESP_ACCT_MARKED_SUBACCOUNT")); }
		virtual DString GetGroupName() const { return DString(I_("iFast")); }
		virtual DString GetModuleName() const { return DString(I_("dita2kdb")); }
		virtual int GetSeverity() const { return 6; }

		// Messages
		virtual DString GetMessage_EN_US() const { return DString(I_("FundCode \"CASH\" is allowed only if TransType is \"FM\" and TaxType is not \"7\".")); }
		virtual DString GetMessage_FR_FR() const { return DString(I_("FundCode \"CASH\" is allowed only if TransType is \"FM\" and TaxType is not \"7\".")); }
		virtual DString GetMessage_DE_DE() const { return DString(I_("Fondscode \"Bargeld\" ist nur erlaubt, wenn Transaktionsart “FM” ist und Steuerart nicht “7” ist.")); }
		virtual DString GetMessage_ES_ES() const { return DString(I_("Sólo se permite el código de fondo \"EFECTIVO\" si el tipo de transferencia es \"FM\" y el tipo tributario no es \"7\".")); }
		virtual DString GetMessage_FR_CA() const { return DString(I_("Le code de fonds Comptant n'est autorisé que si le type de transaction est FM et le type d'imposition n'est pas 7.")); }
		virtual DString GetMessage_NL_NL() const { return DString(I_("Fondscode 'CONTANT' is alleen toegestaan als transactietype 'FM' is en belastingtype niet '7' is")); }

        // Actions
	};
}



