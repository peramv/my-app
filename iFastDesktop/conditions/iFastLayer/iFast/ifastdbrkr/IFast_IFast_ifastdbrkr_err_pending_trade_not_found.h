#pragma once

#include "ConditionObject.h"

namespace CND
{
	class CIFast_IFast_ifastdbrkr_err_pending_trade_not_found : public CConditionObject
	{
	public:
		CIFast_IFast_ifastdbrkr_err_pending_trade_not_found() { }
		~CIFast_IFast_ifastdbrkr_err_pending_trade_not_found() { }

	public:
		// General
		virtual DString GetConditionName() const { return DString(I_("ERR_PENDING_TRADE_NOT_FOUND")); }
		virtual DString GetGroupName() const { return DString(I_("iFast")); }
		virtual DString GetModuleName() const { return DString(I_("ifastdbrkr")); }
		virtual int GetSeverity() const { return 6; }

		// Messages
		virtual DString GetMessage_EN_US() const { return DString(I_("Pending trade not found.")); }
		virtual DString GetMessage_FR_FR() const { return DString(I_("Pending trade not found.")); }
		virtual DString GetMessage_DE_DE() const { return DString(I_("Schwebender Handel nicht gefunden")); }
		virtual DString GetMessage_ES_ES() const { return DString(I_("No se encontró la operación pendiente")); }
		virtual DString GetMessage_FR_CA() const { return DString(I_("Transaction en suspens introuvable")); }
		virtual DString GetMessage_NL_NL() const { return DString(I_("In behandeling zijnde handel is niet gevonden")); }

        // Actions
	};
}



