#pragma once

#include "ConditionObject.h"

namespace CND
{
	class CIFast_IFast_ifastdbrkr_err_batchtrace_rec_notfound : public CConditionObject
	{
	public:
		CIFast_IFast_ifastdbrkr_err_batchtrace_rec_notfound() { }
		~CIFast_IFast_ifastdbrkr_err_batchtrace_rec_notfound() { }

	public:
		// General
		virtual DString GetConditionName() const { return DString(I_("ERR_BATCHTRACE_REC_NOTFOUND")); }
		virtual DString GetGroupName() const { return DString(I_("iFast")); }
		virtual DString GetModuleName() const { return DString(I_("ifastdbrkr")); }
		virtual int GetSeverity() const { return 6; }

		// Messages
		virtual DString GetMessage_EN_US() const { return DString(I_("Batch-Trace record not found.")); }
		virtual DString GetMessage_FR_CA() const { return DString(I_("L'enregistrement de suivi du lot est introuvable.")); }

        // Actions
	};
}



