#pragma once

#include "ConditionObject.h"

namespace CND
{
	class CIFast_IFast_ifastcbo_warn_reg_doc_del_tax_stat_need_update : public CConditionObject
	{
	public:
		CIFast_IFast_ifastcbo_warn_reg_doc_del_tax_stat_need_update() { }
		~CIFast_IFast_ifastcbo_warn_reg_doc_del_tax_stat_need_update() { }

	public:
		// General
		virtual DString GetConditionName() const { return DString(I_("WARN_REG_DOC_DEL_TAX_STAT_NEED_UPDATE")); }
		virtual DString GetGroupName() const { return DString(I_("iFast")); }
		virtual DString GetModuleName() const { return DString(I_("ifastcbo")); }
		virtual int GetSeverity() const { return 5; }

		// Messages
		virtual DString GetMessage_EN_US() const { return DString(I_("Regulatory Document has been deleted, Tax payer status may need to be updated.")); }
		virtual DString GetMessage_FR_CA() const { return DString(I_("Le document réglementaire a été effacé, le statut du contribuable pourrait nécessiter une mise à jour.")); }

        // Actions
	};
}



