#pragma once

#include "ConditionObject.h"

namespace CND
{
	class CIFast_IFast_ifastcbo_warn_shareholder_taxjur_resprov_unassigned : public CConditionObject
	{
	public:
		CIFast_IFast_ifastcbo_warn_shareholder_taxjur_resprov_unassigned() { }
		~CIFast_IFast_ifastcbo_warn_shareholder_taxjur_resprov_unassigned() { }

	public:
		// General
		virtual DString GetConditionName() const { return DString(I_("WARN_SHAREHOLDER_TAXJUR_RESPROV_UNASSIGNED")); }
		virtual DString GetGroupName() const { return DString(I_("iFast")); }
		virtual DString GetModuleName() const { return DString(I_("ifastcbo")); }
		virtual int GetSeverity() const { return 5; }

		// Messages
		virtual DString GetMessage_EN_US() const { return DString(I_("%STR% has unassigned value.")); }
		virtual DString GetMessage_FR_CA() const { return DString(I_("Le champ %STR% a une valeur non attribuée.")); }

        // Actions
	};
}



