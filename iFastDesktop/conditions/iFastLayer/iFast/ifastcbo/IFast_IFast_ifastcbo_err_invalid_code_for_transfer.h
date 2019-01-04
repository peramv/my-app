#pragma once

#include "ConditionObject.h"

namespace CND
{
	class CIFast_IFast_ifastcbo_err_invalid_code_for_transfer : public CConditionObject
	{
	public:
		CIFast_IFast_ifastcbo_err_invalid_code_for_transfer() { }
		~CIFast_IFast_ifastcbo_err_invalid_code_for_transfer() { }

	public:
		// General
		virtual DString GetConditionName() const { return DString(I_("ERR_INVALID_CODE_FOR_TRANSFER")); }
		virtual DString GetGroupName() const { return DString(I_("iFast")); }
		virtual DString GetModuleName() const { return DString(I_("ifastcbo")); }
		virtual int GetSeverity() const { return 6; }

		// Messages
		virtual DString GetMessage_EN_US() const { return DString(I_("Code is not valid for Transfer/Exchange.")); }
		virtual DString GetMessage_DE_DE() const { return DString(I_("Code für Transfer/Wechsel nicht gültig.")); }
		virtual DString GetMessage_ES_ES() const { return DString(I_("El código no es válido transferencias/traspasos.")); }
		virtual DString GetMessage_FR_CA() const { return DString(I_("Code invalide pour un transfert/échange")); }
		virtual DString GetMessage_NL_NL() const { return DString(I_("Code is niet geldig voor overdracht/ruil")); }

        // Actions
	};
}



