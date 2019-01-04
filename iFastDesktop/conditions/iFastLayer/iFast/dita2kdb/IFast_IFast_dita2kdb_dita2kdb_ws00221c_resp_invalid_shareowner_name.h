#pragma once

#include "ConditionObject.h"

namespace CND
{
	class CIFast_IFast_dita2kdb_dita2kdb_ws00221c_resp_invalid_shareowner_name : public CConditionObject
	{
	public:
		CIFast_IFast_dita2kdb_dita2kdb_ws00221c_resp_invalid_shareowner_name() { }
		~CIFast_IFast_dita2kdb_dita2kdb_ws00221c_resp_invalid_shareowner_name() { }

	public:
		// General
		virtual DString GetConditionName() const { return DString(I_("DITA2KDB_WS00221C_RESP_INVALID_SHAREOWNER_NAME")); }
		virtual DString GetGroupName() const { return DString(I_("iFast")); }
		virtual DString GetModuleName() const { return DString(I_("dita2kdb")); }
		virtual int GetSeverity() const { return 6; }

		// Messages
		virtual DString GetMessage_EN_US() const { return DString(I_("Collateral only valid for non-registered accounts.")); }
		virtual DString GetMessage_FR_FR() const { return DString(I_("Collateral only valid for non-registered accounts.")); }
		virtual DString GetMessage_DE_DE() const { return DString(I_("Collateral für nicht registriertes Konto gültig.")); }
		virtual DString GetMessage_ES_ES() const { return DString(I_("garantía sólo válida para cuenta no registrada")); }
		virtual DString GetMessage_FR_CA() const { return DString(I_("La garantie n'est valide que pour les comptes non enregistrés.")); }
		virtual DString GetMessage_NL_NL() const { return DString(I_("onderpand alleen geldig voor niet-registeraccount")); }

        // Actions
	};
}



