#pragma once

#include "ConditionObject.h"

namespace CND
{
	class CIFast_IFast_dita2kdb_dita2kdb_ws00221c_resp_acct_mkd_no_mthly_purch : public CConditionObject
	{
	public:
		CIFast_IFast_dita2kdb_dita2kdb_ws00221c_resp_acct_mkd_no_mthly_purch() { }
		~CIFast_IFast_dita2kdb_dita2kdb_ws00221c_resp_acct_mkd_no_mthly_purch() { }

	public:
		// General
		virtual DString GetConditionName() const { return DString(I_("DITA2KDB_WS00221C_RESP_ACCT_MKD_NO_MTHLY_PURCH")); }
		virtual DString GetGroupName() const { return DString(I_("iFast")); }
		virtual DString GetModuleName() const { return DString(I_("dita2kdb")); }
		virtual int GetSeverity() const { return 6; }

		// Messages
		virtual DString GetMessage_EN_US() const { return DString(I_("Full Redemptions not allowed for Net Redemptions.")); }
		virtual DString GetMessage_FR_FR() const { return DString(I_("Full Redemptions not allowed for Net Redemptions.")); }
		virtual DString GetMessage_DE_DE() const { return DString(I_("Volle Tilgung für Netto-Tilgungen nicht zugelassen.")); }
		virtual DString GetMessage_ES_ES() const { return DString(I_("No se permiten rescates totales para rescates netos")); }
		virtual DString GetMessage_FR_CA() const { return DString(I_("Rachats totaux non autorisés pour les rachats nets")); }
		virtual DString GetMessage_NL_NL() const { return DString(I_("Volledige aflossingen niet toegestaan voor netto aflossingen")); }

        // Actions
	};
}



