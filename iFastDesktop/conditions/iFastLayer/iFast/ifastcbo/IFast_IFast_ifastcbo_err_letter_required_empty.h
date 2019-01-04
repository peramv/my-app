#pragma once

#include "ConditionObject.h"

namespace CND
{
	class CIFast_IFast_ifastcbo_err_letter_required_empty : public CConditionObject
	{
	public:
		CIFast_IFast_ifastcbo_err_letter_required_empty() { }
		~CIFast_IFast_ifastcbo_err_letter_required_empty() { }

	public:
		// General
		virtual DString GetConditionName() const { return DString(I_("ERR_LETTER_REQUIRED_EMPTY")); }
		virtual DString GetGroupName() const { return DString(I_("iFast")); }
		virtual DString GetModuleName() const { return DString(I_("ifastcbo")); }
		virtual int GetSeverity() const { return 6; }

		// Messages
		virtual DString GetMessage_EN_US() const { return DString(I_("Generate notification letter is empty.")); }
		virtual DString GetMessage_FR_CA() const { return DString(I_("Le champ de génération de lettre de notification est vide.")); }

        // Actions
	};
}



