#pragma once

#include "ConditionObject.h"

namespace CND
{
	class CIFast_IFast_ifastcbo_err_acct_has_stopped_swp_or_redem : public CConditionObject
	{
	public:
		CIFast_IFast_ifastcbo_err_acct_has_stopped_swp_or_redem() { }
		~CIFast_IFast_ifastcbo_err_acct_has_stopped_swp_or_redem() { }

	public:
		// General
		virtual DString GetConditionName() const { return DString(I_("ERR_ACCT_HAS_STOPPED_SWP_OR_REDEM")); }
		virtual DString GetGroupName() const { return DString(I_("iFast")); }
		virtual DString GetModuleName() const { return DString(I_("ifastcbo")); }
		virtual int GetSeverity() const { return 6; }

		// Messages
		virtual DString GetMessage_EN_US() const { return DString(I_("This account has %TRADE_TYPE% stopped. Unable to set up %TRADE_TYPE%.")); }
		virtual DString GetMessage_FR_FR() const { return DString(I_("%TRADE_TYPE% de ce compte a ete arretee. Impossible de definir %TRADE_TYPE%")); }
		virtual DString GetMessage_DE_DE() const { return DString(I_("Für dieses Konto wurde %TRADE_TYPE% gestoppt. %TRADE_TYPE% kann nicht erstellt werden.")); }
		virtual DString GetMessage_ES_ES() const { return DString(I_("Esta cuenta ha interrumpido %TRADE_TYPE%. Imposible configurar %TRADE_TYPE%.")); }
		virtual DString GetMessage_FR_CA() const { return DString(I_("Le type de transaction %TRADE_TYPE% est arrêté pour ce compte. Impossible de régler %TRADE_TYPE%.")); }
		virtual DString GetMessage_NL_NL() const { return DString(I_("Voor dit account is %TRADE_TYPE% beëindigd. %TRADE_TYPE% kon niet worden ingesteld")); }

        // Actions
	};
}



