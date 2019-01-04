#pragma once

#include "ConditionObject.h"

namespace CND
{
	class CIFast_IFast_dita2kdb_dita2kdb_ws00221c_resp_invalid_ach_dividend_cde : public CConditionObject
	{
	public:
		CIFast_IFast_dita2kdb_dita2kdb_ws00221c_resp_invalid_ach_dividend_cde() { }
		~CIFast_IFast_dita2kdb_dita2kdb_ws00221c_resp_invalid_ach_dividend_cde() { }

	public:
		// General
		virtual DString GetConditionName() const { return DString(I_("DITA2KDB_WS00221C_RESP_INVALID_ACH_DIVIDEND_CDE")); }
		virtual DString GetGroupName() const { return DString(I_("iFast")); }
		virtual DString GetModuleName() const { return DString(I_("dita2kdb")); }
		virtual int GetSeverity() const { return 6; }

		// Messages
		virtual DString GetMessage_EN_US() const { return DString(I_("RESP Beneficiary Entity must be setup.")); }
		virtual DString GetMessage_FR_FR() const { return DString(I_("RESP Beneficiary Entity must be setup.")); }
		virtual DString GetMessage_DE_DE() const { return DString(I_("RESP-Begünstigten-Objekt muss erstellt sein.")); }
		virtual DString GetMessage_ES_ES() const { return DString(I_("Debe configurarse la entidad Beneficiario RESP")); }
		virtual DString GetMessage_FR_CA() const { return DString(I_("L'entité bénéficiaire REEE doit être créée.")); }
		virtual DString GetMessage_NL_NL() const { return DString(I_("Eenheid RESP-begunstigde moet worden ingesteld")); }

        // Actions
	};
}



