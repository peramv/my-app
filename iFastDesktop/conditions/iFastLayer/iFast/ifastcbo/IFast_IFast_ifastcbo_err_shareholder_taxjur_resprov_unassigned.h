#pragma once

#include "ConditionObject.h"

namespace CND
{
	class CIFast_IFast_ifastcbo_err_shareholder_taxjur_resprov_unassigned : public CConditionObject
	{
	public:
		CIFast_IFast_ifastcbo_err_shareholder_taxjur_resprov_unassigned() { }
		~CIFast_IFast_ifastcbo_err_shareholder_taxjur_resprov_unassigned() { }

	public:
		// General
		virtual DString GetConditionName() const { return DString(I_("ERR_SHAREHOLDER_TAXJUR_RESPROV_UNASSIGNED")); }
		virtual DString GetGroupName() const { return DString(I_("iFast")); }
		virtual DString GetModuleName() const { return DString(I_("ifastcbo")); }
		virtual int GetSeverity() const { return 6; }

		// Messages
		virtual DString GetMessage_EN_US() const { return DString(I_("%STR% cannot be left Unassigned")); }
		virtual DString GetMessage_FR_CA() const { return DString(I_("Le champ %STR% ne peut être laissé Non Attribué.")); }

        // Actions
	};
}



