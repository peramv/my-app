#pragma once

#include "ConditionObject.h"

namespace CND
{
	class CIFast_IFast_ifastcbo_warn_loss_situation : public CConditionObject
	{
	public:
		CIFast_IFast_ifastcbo_warn_loss_situation() { }
		~CIFast_IFast_ifastcbo_warn_loss_situation() { }

	public:
		// General
		virtual DString GetConditionName() const { return DString(I_("WARN_LOSS_SITUATION")); }
		virtual DString GetGroupName() const { return DString(I_("iFast")); }
		virtual DString GetModuleName() const { return DString(I_("ifastcbo")); }
		virtual int GetSeverity() const { return 5; }

		// Messages
		virtual DString GetMessage_EN_US() const { return DString(I_("Aggregate Order is in loss situation.")); }
		virtual DString GetMessage_DE_DE() const { return DString(I_("Aggregate Order is in loss situation.")); }
		virtual DString GetMessage_FR_CA() const { return DString(I_("L'ordre global est en situation de perte.")); }

        // Actions
	};
}



