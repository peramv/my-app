#pragma once

#include "ConditionObject.h"

namespace CND
{
	class CIFast_IFast_ifastcbo_err_warn_transfer_to_diff : public CConditionObject
	{
	public:
		CIFast_IFast_ifastcbo_err_warn_transfer_to_diff() { }
		~CIFast_IFast_ifastcbo_err_warn_transfer_to_diff() { }

	public:
		// General
		virtual DString GetConditionName() const { return DString(I_("ERR_WARN_TRANSFER_TO_DIFF")); }
		virtual DString GetGroupName() const { return DString(I_("iFast")); }
		virtual DString GetModuleName() const { return DString(I_("ifastcbo")); }
		virtual int GetSeverity() const { return 5; }

		// Messages
		virtual DString GetMessage_EN_US() const { return DString(I_("Transfering registered account to a different shareholder.")); }
		virtual DString GetMessage_DE_DE() const { return DString(I_("Transferieren des registrierten Kontos auf einen anderen Aktionär.")); }
		virtual DString GetMessage_ES_ES() const { return DString(I_("Transfiriendo cuenta registrada a otro accionista.")); }
		virtual DString GetMessage_FR_CA() const { return DString(I_("Transfert du compte enregistré à un actionnaire différent en cours…")); }
		virtual DString GetMessage_NL_NL() const { return DString(I_("Geregistreerd account wordt overgedragen naar een andere aandeelhouder")); }

        // Actions
	};
}



