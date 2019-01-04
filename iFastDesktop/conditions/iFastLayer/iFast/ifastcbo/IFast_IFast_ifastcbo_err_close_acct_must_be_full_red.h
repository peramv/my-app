#pragma once

#include "ConditionObject.h"

namespace CND
{
	class CIFast_IFast_ifastcbo_err_close_acct_must_be_full_red : public CConditionObject
	{
	public:
		CIFast_IFast_ifastcbo_err_close_acct_must_be_full_red() { }
		~CIFast_IFast_ifastcbo_err_close_acct_must_be_full_red() { }

	public:
		// General
		virtual DString GetConditionName() const { return DString(I_("ERR_CLOSE_ACCT_MUST_BE_FULL_RED")); }
		virtual DString GetGroupName() const { return DString(I_("iFast")); }
		virtual DString GetModuleName() const { return DString(I_("ifastcbo")); }
		virtual int GetSeverity() const { return 6; }

		// Messages
		virtual DString GetMessage_EN_US() const { return DString(I_("A close account Redemption Code can only be used with FULL redemptions.")); }
		virtual DString GetMessage_DE_DE() const { return DString(I_("Ein Kontoabschluss-Tilgungscode kann nur bei VOLLEN Tilgungen verwendet werden.")); }
		virtual DString GetMessage_ES_ES() const { return DString(I_("Un código de rescate con cierre de cuenta sólo puede utilizarse con rescates TOTALES.")); }
		virtual DString GetMessage_FR_CA() const { return DString(I_("Un code de rachat de fermeture de compte ne peut être utilisé qu'avec des rachat totaux.")); }
		virtual DString GetMessage_NL_NL() const { return DString(I_("Een aflossingscode voor het sluiten van het account kan alleen worden gebruikt met VOLLEDIGE aflossing")); }

        // Actions
	};
}



