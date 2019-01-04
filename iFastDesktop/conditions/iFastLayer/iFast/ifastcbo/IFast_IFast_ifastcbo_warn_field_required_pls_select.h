#pragma once

#include "ConditionObject.h"

namespace CND
{
	class CIFast_IFast_ifastcbo_warn_field_required_pls_select : public CConditionObject
	{
	public:
		CIFast_IFast_ifastcbo_warn_field_required_pls_select() { }
		~CIFast_IFast_ifastcbo_warn_field_required_pls_select() { }

	public:
		// General
		virtual DString GetConditionName() const { return DString(I_("WARN_FIELD_REQUIRED_PLS_SELECT")); }
		virtual DString GetGroupName() const { return DString(I_("iFast")); }
		virtual DString GetModuleName() const { return DString(I_("ifastcbo")); }
		virtual int GetSeverity() const { return 5; }

		// Messages
		virtual DString GetMessage_EN_US() const { return DString(I_("Field value is required for update.")); }
		virtual DString GetMessage_DE_DE() const { return DString(I_("Field value is required for update.")); }
		virtual DString GetMessage_ES_ES() const { return DString(I_("Field value is required for update.")); }
		virtual DString GetMessage_FR_CA() const { return DString(I_("La valeur du champ est requise pour la mise à jour.")); }

        // Actions
	};
}



