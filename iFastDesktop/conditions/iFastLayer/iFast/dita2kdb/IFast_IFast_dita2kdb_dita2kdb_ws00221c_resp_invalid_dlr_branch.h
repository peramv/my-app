#pragma once

#include "ConditionObject.h"

namespace CND
{
	class CIFast_IFast_dita2kdb_dita2kdb_ws00221c_resp_invalid_dlr_branch : public CConditionObject
	{
	public:
		CIFast_IFast_dita2kdb_dita2kdb_ws00221c_resp_invalid_dlr_branch() { }
		~CIFast_IFast_dita2kdb_dita2kdb_ws00221c_resp_invalid_dlr_branch() { }

	public:
		// General
		virtual DString GetConditionName() const { return DString(I_("DITA2KDB_WS00221C_RESP_INVALID_DLR_BRANCH")); }
		virtual DString GetGroupName() const { return DString(I_("iFast")); }
		virtual DString GetModuleName() const { return DString(I_("dita2kdb")); }
		virtual int GetSeverity() const { return 6; }

		// Messages
		virtual DString GetMessage_EN_US() const { return DString(I_("Invalid Pay Type for %TRADETYPE%.")); }
		virtual DString GetMessage_FR_FR() const { return DString(I_("Invalid Pay Type for %TRADETYPE%.")); }
		virtual DString GetMessage_DE_DE() const { return DString(I_("Ungültige Zahlart für %TRADETYPE%")); }
		virtual DString GetMessage_ES_ES() const { return DString(I_("Tipo de pago no válido para %TRADETYPE%")); }
		virtual DString GetMessage_FR_CA() const { return DString(I_("Type de paiement invalide pour %TRADETYPE%")); }
		virtual DString GetMessage_NL_NL() const { return DString(I_("Ongeldig betalingstype voor %TRADETYPE%")); }

        // Actions
	};
}



