#pragma once

#include "ConditionObject.h"

namespace CND
{
	class CIFast_IFast_ifastdbrkr_err_no_pending_trades_found : public CConditionObject
	{
	public:
		CIFast_IFast_ifastdbrkr_err_no_pending_trades_found() { }
		~CIFast_IFast_ifastdbrkr_err_no_pending_trades_found() { }

	public:
		// General
		virtual DString GetConditionName() const { return DString(I_("ERR_NO_PENDING_TRADES_FOUND")); }
		virtual DString GetGroupName() const { return DString(I_("iFast")); }
		virtual DString GetModuleName() const { return DString(I_("ifastdbrkr")); }
		virtual int GetSeverity() const { return 6; }

		// Messages
		virtual DString GetMessage_EN_US() const { return DString(I_("No pending trades found for the account.")); }
		virtual DString GetMessage_FR_FR() const { return DString(I_("No pending trades found for the account.")); }
		virtual DString GetMessage_DE_DE() const { return DString(I_("Keine schwebenden Handel für das Konto gefunden.")); }
		virtual DString GetMessage_ES_ES() const { return DString(I_("No se encontraron operaciones pendientes para la cuenta")); }
		virtual DString GetMessage_FR_CA() const { return DString(I_("Aucune transaction en suspens n'a été trouvée pour ce compte.")); }
		virtual DString GetMessage_NL_NL() const { return DString(I_("Er zijn geen in behandeling zijnde transacties gevonden voor het account")); }

        // Actions
	};
}



