#pragma once

#include "ConditionObject.h"

namespace CND
{
	class CIFast_IFast_ifastcbo_warn_cmd_later_than_legal_maturity_date : public CConditionObject
	{
	public:
		CIFast_IFast_ifastcbo_warn_cmd_later_than_legal_maturity_date() { }
		~CIFast_IFast_ifastcbo_warn_cmd_later_than_legal_maturity_date() { }

	public:
		// General
		virtual DString GetConditionName() const { return DString(I_("WARN_CMD_LATER_THAN_LEGAL_MATURITY_DATE")); }
		virtual DString GetGroupName() const { return DString(I_("iFast")); }
		virtual DString GetModuleName() const { return DString(I_("ifastcbo")); }
		virtual int GetSeverity() const { return 5; }

		// Messages
		virtual DString GetMessage_EN_US() const { return DString(I_("User defined Contract Maturity Date should be earlier or equal to calculated Legal Maturity Date.")); }
		virtual DString GetMessage_FR_CA() const { return DString(I_("La date d'échéance du contrat définie par l'utilisateur devrait être antérieure ou identique à la date d'échéance légale calculée.")); }

        // Actions
	};
}



