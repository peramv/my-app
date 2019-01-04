#pragma once

#include "ConditionObject.h"

namespace CND
{
	class CIFast_IFast_ifastcbo_warn_tfsa_update_effective_date_required : public CConditionObject
	{
	public:
		CIFast_IFast_ifastcbo_warn_tfsa_update_effective_date_required() { }
		~CIFast_IFast_ifastcbo_warn_tfsa_update_effective_date_required() { }

	public:
		// General
		virtual DString GetConditionName() const { return DString(I_("WARN_TFSA_UPDATE_EFFECTIVE_DATE_REQUIRED")); }
		virtual DString GetGroupName() const { return DString(I_("iFast")); }
		virtual DString GetModuleName() const { return DString(I_("ifastcbo")); }
		virtual int GetSeverity() const { return 5; }

		// Messages
		virtual DString GetMessage_EN_US() const { return DString(I_("Please update the effective date of the name change on the amendment record.")); }
		virtual DString GetMessage_FR_CA() const { return DString(I_("Veuillez mettre à jour la date d'entrée en vigueur du changement de nom dans l'enregistrement de modification.")); }

        // Actions
	};
}



