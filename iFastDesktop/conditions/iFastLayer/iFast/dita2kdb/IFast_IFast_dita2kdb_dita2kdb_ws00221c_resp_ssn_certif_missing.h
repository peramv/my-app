#pragma once

#include "ConditionObject.h"

namespace CND
{
	class CIFast_IFast_dita2kdb_dita2kdb_ws00221c_resp_ssn_certif_missing : public CConditionObject
	{
	public:
		CIFast_IFast_dita2kdb_dita2kdb_ws00221c_resp_ssn_certif_missing() { }
		~CIFast_IFast_dita2kdb_dita2kdb_ws00221c_resp_ssn_certif_missing() { }

	public:
		// General
		virtual DString GetConditionName() const { return DString(I_("DITA2KDB_WS00221C_RESP_SSN_CERTIF_MISSING")); }
		virtual DString GetGroupName() const { return DString(I_("iFast")); }
		virtual DString GetModuleName() const { return DString(I_("dita2kdb")); }
		virtual int GetSeverity() const { return 6; }

		// Messages
		virtual DString GetMessage_EN_US() const { return DString(I_("Only GIC fund purchases allowed for this account.")); }
		virtual DString GetMessage_FR_FR() const { return DString(I_("Only GIC fund purchases allowed for this account.")); }
		virtual DString GetMessage_DE_DE() const { return DString(I_("Für dieses Konto sind nur GIC-Fondskäufe erlaubt.")); }
		virtual DString GetMessage_ES_ES() const { return DString(I_("Sólo se permiten compras de fondo GIC para esta cuenta.")); }
		virtual DString GetMessage_FR_CA() const { return DString(I_("Seuls les achats de fonds CPG sont autorisés pour ce compte.")); }
		virtual DString GetMessage_NL_NL() const { return DString(I_("Alleen aankopen GIC-fonds zijn toegestaan voor dit account")); }

        // Actions
	};
}



