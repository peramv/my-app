#pragma once

#include "ConditionObject.h"

namespace CND
{
	class CIFast_IFast_ifastcbo_err_cannot_switch_taxtype : public CConditionObject
	{
	public:
		CIFast_IFast_ifastcbo_err_cannot_switch_taxtype() { }
		~CIFast_IFast_ifastcbo_err_cannot_switch_taxtype() { }

	public:
		// General
		virtual DString GetConditionName() const { return DString(I_("ERR_CANNOT_SWITCH_TAXTYPE")); }
		virtual DString GetGroupName() const { return DString(I_("iFast")); }
		virtual DString GetModuleName() const { return DString(I_("ifastcbo")); }
		virtual int GetSeverity() const { return 6; }

		// Messages
		virtual DString GetMessage_EN_US() const { return DString(I_("Switching from tax type %TAX_FRM% to %TAX_TO% is not allowed.")); }
		virtual DString GetMessage_FR_CA() const { return DString(I_("Le changement du type d'imposition %TAX_FRM% au type d'imposition %TAX_TO% n'est pas autorisé.")); }

        // Actions
	};
}



