#pragma once

#include "ConditionObject.h"

namespace CND
{
	class CIFast_IFast_dita2kdb_dita2kdb_ws00221c_resp_fund_marked_no_redmp_chks : public CConditionObject
	{
	public:
		CIFast_IFast_dita2kdb_dita2kdb_ws00221c_resp_fund_marked_no_redmp_chks() { }
		~CIFast_IFast_dita2kdb_dita2kdb_ws00221c_resp_fund_marked_no_redmp_chks() { }

	public:
		// General
		virtual DString GetConditionName() const { return DString(I_("DITA2KDB_WS00221C_RESP_FUND_MARKED_NO_REDMP_CHKS")); }
		virtual DString GetGroupName() const { return DString(I_("iFast")); }
		virtual DString GetModuleName() const { return DString(I_("dita2kdb")); }
		virtual int GetSeverity() const { return 6; }

		// Messages
		virtual DString GetMessage_EN_US() const { return DString(I_("GIC Fund Purchase not allowed for this account.")); }
		virtual DString GetMessage_FR_FR() const { return DString(I_("GIC Fund Purchase not allowed for this account.")); }
		virtual DString GetMessage_DE_DE() const { return DString(I_("GIC-Fondskauf ist für dieses Konto nicht erlaubt.")); }
		virtual DString GetMessage_ES_ES() const { return DString(I_("No se permite la compra de fondo GIC para esta cuenta.")); }
		virtual DString GetMessage_FR_CA() const { return DString(I_("L'achat de fonds CPG n'est pas autorisé pour ce compte.")); }
		virtual DString GetMessage_NL_NL() const { return DString(I_("Aankoop GIC-fonds is niet toegestaan voor dit account")); }

        // Actions
	};
}



