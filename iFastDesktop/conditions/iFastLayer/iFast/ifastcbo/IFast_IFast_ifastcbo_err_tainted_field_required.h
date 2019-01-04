#pragma once

#include "ConditionObject.h"

namespace CND
{
	class CIFast_IFast_ifastcbo_err_tainted_field_required : public CConditionObject
	{
	public:
		CIFast_IFast_ifastcbo_err_tainted_field_required() { }
		~CIFast_IFast_ifastcbo_err_tainted_field_required() { }

	public:
		// General
		virtual DString GetConditionName() const { return DString(I_("ERR_TAINTED_FIELD_REQUIRED")); }
		virtual DString GetGroupName() const { return DString(I_("iFast")); }
		virtual DString GetModuleName() const { return DString(I_("ifastcbo")); }
		virtual int GetSeverity() const { return 6; }

		// Messages
		virtual DString GetMessage_EN_US() const { return DString(I_("Tainted is required.")); }
		virtual DString GetMessage_FR_CA() const { return DString(I_("Le champ Contaminé est requis.")); }

        // Actions
		virtual DString GetAction_EN_US() const { return DString(I_("User must supply Yes \\ No to this field.")); }
		virtual DString GetAction_FR_CA() const { return DString(I_("L'utilisateur doit indiquer Oui/Non dans ce champ.")); }
	};
}



