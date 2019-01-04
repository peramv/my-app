#pragma once

#include "ConditionObject.h"

namespace CND
{
	class CIFast_IFast_ifastcbo_err_reason_code_empty : public CConditionObject
	{
	public:
		CIFast_IFast_ifastcbo_err_reason_code_empty() { }
		~CIFast_IFast_ifastcbo_err_reason_code_empty() { }

	public:
		// General
		virtual DString GetConditionName() const { return DString(I_("ERR_REASON_CODE_EMPTY")); }
		virtual DString GetGroupName() const { return DString(I_("iFast")); }
		virtual DString GetModuleName() const { return DString(I_("ifastcbo")); }
		virtual int GetSeverity() const { return 6; }

		// Messages
		virtual DString GetMessage_EN_US() const { return DString(I_("Reason cannot be empty.")); }
		virtual DString GetMessage_FR_FR() const { return DString(I_("Reason cannot be empty.")); }
		virtual DString GetMessage_DE_DE() const { return DString(I_("Begründung muss eingegeben werden.")); }
		virtual DString GetMessage_ES_ES() const { return DString(I_("El motivo no puede estar vacío.")); }
		virtual DString GetMessage_FR_CA() const { return DString(I_("Vous devez fournir une raison.")); }
		virtual DString GetMessage_NL_NL() const { return DString(I_("Reden kan niet leeg zijn")); }

        // Actions
	};
}



