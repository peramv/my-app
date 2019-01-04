#pragma once

#include "ConditionObject.h"

namespace CND
{
	class CIFast_IFast_ifastcbo_err_class_code_must_be_blank : public CConditionObject
	{
	public:
		CIFast_IFast_ifastcbo_err_class_code_must_be_blank() { }
		~CIFast_IFast_ifastcbo_err_class_code_must_be_blank() { }

	public:
		// General
		virtual DString GetConditionName() const { return DString(I_("ERR_CLASS_CODE_MUST_BE_BLANK")); }
		virtual DString GetGroupName() const { return DString(I_("iFast")); }
		virtual DString GetModuleName() const { return DString(I_("ifastcbo")); }
		virtual int GetSeverity() const { return 6; }

		// Messages
		virtual DString GetMessage_EN_US() const { return DString(I_("Class code must be blank.")); }
		virtual DString GetMessage_DE_DE() const { return DString(I_("Class code must be blank.")); }
		virtual DString GetMessage_ES_ES() const { return DString(I_("Class code must be blank.")); }
		virtual DString GetMessage_FR_CA() const { return DString(I_("Le champ Code de classe doit être vide.")); }

        // Actions
	};
}



