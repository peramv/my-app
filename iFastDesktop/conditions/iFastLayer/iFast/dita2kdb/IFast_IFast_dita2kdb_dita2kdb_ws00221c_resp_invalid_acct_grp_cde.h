#pragma once

#include "ConditionObject.h"

namespace CND
{
	class CIFast_IFast_dita2kdb_dita2kdb_ws00221c_resp_invalid_acct_grp_cde : public CConditionObject
	{
	public:
		CIFast_IFast_dita2kdb_dita2kdb_ws00221c_resp_invalid_acct_grp_cde() { }
		~CIFast_IFast_dita2kdb_dita2kdb_ws00221c_resp_invalid_acct_grp_cde() { }

	public:
		// General
		virtual DString GetConditionName() const { return DString(I_("DITA2KDB_WS00221C_RESP_INVALID_ACCT_GRP_CDE")); }
		virtual DString GetGroupName() const { return DString(I_("iFast")); }
		virtual DString GetModuleName() const { return DString(I_("dita2kdb")); }
		virtual int GetSeverity() const { return 6; }

		// Messages
		virtual DString GetMessage_EN_US() const { return DString(I_("Address code  can not be blank.")); }
		virtual DString GetMessage_FR_FR() const { return DString(I_("Address code %CODE% has not been set up for this account.")); }
		virtual DString GetMessage_DE_DE() const { return DString(I_("Der Adresscode %CODE% wurde nicht für dieses Konto erstellt. Bitte erstellen Sie den Code.")); }
		virtual DString GetMessage_ES_ES() const { return DString(I_("No se ha configurado el código de dirección %CODE% para esta cuenta. Por favor configúrelo.")); }
		virtual DString GetMessage_FR_CA() const { return DString(I_("Le champ Code d'adresse doit être rempli.")); }
		virtual DString GetMessage_NL_NL() const { return DString(I_("Adrescode %CODE% is niet ingesteld voor dit account. Stel hem in")); }

        // Actions
	};
}



