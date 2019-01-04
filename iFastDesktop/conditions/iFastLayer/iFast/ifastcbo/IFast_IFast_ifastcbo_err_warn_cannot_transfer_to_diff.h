#pragma once

#include "ConditionObject.h"

namespace CND
{
	class CIFast_IFast_ifastcbo_err_warn_cannot_transfer_to_diff : public CConditionObject
	{
	public:
		CIFast_IFast_ifastcbo_err_warn_cannot_transfer_to_diff() { }
		~CIFast_IFast_ifastcbo_err_warn_cannot_transfer_to_diff() { }

	public:
		// General
		virtual DString GetConditionName() const { return DString(I_("ERR_WARN_CANNOT_TRANSFER_TO_DIFF")); }
		virtual DString GetGroupName() const { return DString(I_("iFast")); }
		virtual DString GetModuleName() const { return DString(I_("ifastcbo")); }
		virtual int GetSeverity() const { return 5; }

		// Messages
		virtual DString GetMessage_EN_US() const { return DString(I_("Transferring to a different shareholder.")); }
		virtual DString GetMessage_DE_DE() const { return DString(I_("Transferieren auf einen anderen Aktionär nicht möglich.")); }
		virtual DString GetMessage_ES_ES() const { return DString(I_("No se puede transferir a otro accionista.")); }
		virtual DString GetMessage_FR_CA() const { return DString(I_("Transfert à un actionnaire différent en cours…")); }
		virtual DString GetMessage_NL_NL() const { return DString(I_("Er kan niet worden overgedragen naar een andere aandeelhouder")); }

        // Actions
	};
}



