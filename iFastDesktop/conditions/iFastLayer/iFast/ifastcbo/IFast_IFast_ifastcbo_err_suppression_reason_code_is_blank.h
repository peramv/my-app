#pragma once

#include "ConditionObject.h"

namespace CND
{
	class CIFast_IFast_ifastcbo_err_suppression_reason_code_is_blank : public CConditionObject
	{
	public:
		CIFast_IFast_ifastcbo_err_suppression_reason_code_is_blank() { }
		~CIFast_IFast_ifastcbo_err_suppression_reason_code_is_blank() { }

	public:
		// General
		virtual DString GetConditionName() const { return DString(I_("ERR_suppression_reason_code_BLANK")); }
		virtual DString GetGroupName() const { return DString(I_("iFast")); }
		virtual DString GetModuleName() const { return DString(I_("ifastcbo")); }
		virtual int GetSeverity() const { return 6; }

		// Messages
		virtual DString GetMessage_EN_US() const { return DString(I_("Suppression Reason Code cannot be blank.")); }
		virtual DString GetMessage_DE_DE() const { return DString(I_("Suppression Reason Code cannot be blank.")); }
		virtual DString GetMessage_ES_ES() const { return DString(I_("Suppression Reason Code cannot be blank.")); }
		virtual DString GetMessage_FR_CA() const { return DString(I_("Code de r�pression de la Raison ne peut �tre vide.")); }

        // Actions
	};
}



