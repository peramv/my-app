#pragma once

#include "ConditionObject.h"

namespace CND
{
	class CIFast_IFast_ifastcbo_err_warn_cannot_transfer_from_rrif : public CConditionObject
	{
	public:
		CIFast_IFast_ifastcbo_err_warn_cannot_transfer_from_rrif() { }
		~CIFast_IFast_ifastcbo_err_warn_cannot_transfer_from_rrif() { }

	public:
		// General
		virtual DString GetConditionName() const { return DString(I_("ERR_WARN_CANNOT_TRANSFER_FROM_RRIF")); }
		virtual DString GetGroupName() const { return DString(I_("iFast")); }
		virtual DString GetModuleName() const { return DString(I_("ifastcbo")); }
		virtual int GetSeverity() const { return 5; }

		// Messages
		virtual DString GetMessage_EN_US() const { return DString(I_("Cannot transfer from a %TAXTYPE% to a different shareholder.")); }
		virtual DString GetMessage_DE_DE() const { return DString(I_("Von einem RRIF zu einem anderen Aktionär kann nicht transferiert werden.")); }
		virtual DString GetMessage_ES_ES() const { return DString(I_("No se puede transferir de una cuenta RRIF a otro accionista.")); }
		virtual DString GetMessage_FR_CA() const { return DString(I_("Impossible de transférer de %TAXTYPE% à un actionnaire différent.")); }
		virtual DString GetMessage_NL_NL() const { return DString(I_("Er kan geen overdracht plaatsvinden van een RRIF naar een andere aandeelhouder")); }

        // Actions
	};
}



