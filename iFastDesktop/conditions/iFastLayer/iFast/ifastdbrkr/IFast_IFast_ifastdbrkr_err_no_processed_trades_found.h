#pragma once

#include "ConditionObject.h"

namespace CND
{
	class CIFast_IFast_ifastdbrkr_err_no_processed_trades_found : public CConditionObject
	{
	public:
		CIFast_IFast_ifastdbrkr_err_no_processed_trades_found() { }
		~CIFast_IFast_ifastdbrkr_err_no_processed_trades_found() { }

	public:
		// General
		virtual DString GetConditionName() const { return DString(I_("ERR_NO_PROCESSED_TRADES_FOUND")); }
		virtual DString GetGroupName() const { return DString(I_("iFast")); }
		virtual DString GetModuleName() const { return DString(I_("ifastdbrkr")); }
		virtual int GetSeverity() const { return 6; }

		// Messages
		virtual DString GetMessage_EN_US() const { return DString(I_("No processed trades found for the account.")); }
		virtual DString GetMessage_FR_FR() const { return DString(I_("No processed trades found for the account.")); }
		virtual DString GetMessage_DE_DE() const { return DString(I_("Keinen verarbeiteten Handel für das Konto gefunden.")); }
		virtual DString GetMessage_ES_ES() const { return DString(I_("No se encontraron operaciones procesadas para la cuenta")); }
		virtual DString GetMessage_FR_CA() const { return DString(I_("Aucune transaction traitée n'a été trouvée pour ce compte.")); }
		virtual DString GetMessage_NL_NL() const { return DString(I_("Er zijn geen verwerkte transacties gevonden voor het account")); }

        // Actions
	};
}



