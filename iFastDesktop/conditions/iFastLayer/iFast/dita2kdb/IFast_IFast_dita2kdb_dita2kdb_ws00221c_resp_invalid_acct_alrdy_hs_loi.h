#pragma once

#include "ConditionObject.h"

namespace CND
{
	class CIFast_IFast_dita2kdb_dita2kdb_ws00221c_resp_invalid_acct_alrdy_hs_loi : public CConditionObject
	{
	public:
		CIFast_IFast_dita2kdb_dita2kdb_ws00221c_resp_invalid_acct_alrdy_hs_loi() { }
		~CIFast_IFast_dita2kdb_dita2kdb_ws00221c_resp_invalid_acct_alrdy_hs_loi() { }

	public:
		// General
		virtual DString GetConditionName() const { return DString(I_("DITA2KDB_WS00221C_RESP_INVALID_ACCT_ALRDY_HS_LOI")); }
		virtual DString GetGroupName() const { return DString(I_("iFast")); }
		virtual DString GetModuleName() const { return DString(I_("dita2kdb")); }
		virtual int GetSeverity() const { return 6; }

		// Messages
		virtual DString GetMessage_EN_US() const { return DString(I_("Account Owner Entity must be setup.")); }
		virtual DString GetMessage_FR_FR() const { return DString(I_("Account Owner Entity must be setup.")); }
		virtual DString GetMessage_DE_DE() const { return DString(I_("Kontoinhaber-Objekt muss erstellt sein.")); }
		virtual DString GetMessage_ES_ES() const { return DString(I_("Debe configurarse la entidad Propietario de la cuenta")); }
		virtual DString GetMessage_FR_CA() const { return DString(I_("L'entité titulaire du compte doit être créée.")); }
		virtual DString GetMessage_NL_NL() const { return DString(I_("Eenheid accounthouder moet worden ingesteld")); }

        // Actions
	};
}



