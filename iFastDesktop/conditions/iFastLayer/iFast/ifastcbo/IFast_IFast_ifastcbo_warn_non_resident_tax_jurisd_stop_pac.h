#pragma once

#include "ConditionObject.h"

namespace CND
{
	class CIFast_IFast_ifastcbo_warn_non_resident_tax_jurisd_stop_pac : public CConditionObject
	{
	public:
		CIFast_IFast_ifastcbo_warn_non_resident_tax_jurisd_stop_pac() { }
		~CIFast_IFast_ifastcbo_warn_non_resident_tax_jurisd_stop_pac() { }

	public:
		// General
		virtual DString GetConditionName() const { return DString(I_("WARN_NON_RESIDENT_TAX_JURISD_STOP_PAC")); }
		virtual DString GetGroupName() const { return DString(I_("iFast")); }
		virtual DString GetModuleName() const { return DString(I_("ifastcbo")); }
		virtual int GetSeverity() const { return 5; }

		// Messages
		virtual DString GetMessage_EN_US() const { return DString(I_("Stop Active PAC / AT as contribution not allowed for non-resident")); }
		virtual DString GetMessage_FR_CA() const { return DString(I_("Arrêt du PAC/transfert automatique puisque la cotisation n'est pas autorisée pour un non-résident.")); }

        // Actions
	};
}



