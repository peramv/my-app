#pragma once

#include "ConditionObject.h"

namespace CND
{
	class CIFast_IFast_ifastdbrkr_err_batch_is_active : public CConditionObject
	{
	public:
		CIFast_IFast_ifastdbrkr_err_batch_is_active() { }
		~CIFast_IFast_ifastdbrkr_err_batch_is_active() { }

	public:
		// General
		virtual DString GetConditionName() const { return DString(I_("ERR_BATCH_IS_ACTIVE")); }
		virtual DString GetGroupName() const { return DString(I_("iFast")); }
		virtual DString GetModuleName() const { return DString(I_("ifastdbrkr")); }
		virtual int GetSeverity() const { return 6; }

		// Messages
		virtual DString GetMessage_EN_US() const { return DString(I_("Batch is active.")); }
		virtual DString GetMessage_DE_DE() const { return DString(I_("Batch ist aktiv")); }
		virtual DString GetMessage_ES_ES() const { return DString(I_("El lote está activo")); }
		virtual DString GetMessage_FR_CA() const { return DString(I_("Lot actif")); }
		virtual DString GetMessage_NL_NL() const { return DString(I_("Batch is actief")); }

        // Actions
	};
}



