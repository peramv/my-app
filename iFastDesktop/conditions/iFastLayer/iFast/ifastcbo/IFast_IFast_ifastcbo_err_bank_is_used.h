#pragma once

#include "ConditionObject.h"

namespace CND
{
	class CIFast_IFast_ifastcbo_err_bank_is_used : public CConditionObject
	{
	public:
		CIFast_IFast_ifastcbo_err_bank_is_used() { }
		~CIFast_IFast_ifastcbo_err_bank_is_used() { }

	public:
		// General
		virtual DString GetConditionName() const { return DString(I_("ERR_BANK_IS_USED")); }
		virtual DString GetGroupName() const { return DString(I_("iFast")); }
		virtual DString GetModuleName() const { return DString(I_("ifastcbo")); }
		virtual int GetSeverity() const { return 6; }

		// Messages
		virtual DString GetMessage_EN_US() const { return DString(I_("Same account is used for %CURRENCY% fund.")); }
		virtual DString GetMessage_DE_DE() const { return DString(I_("Das gleiche Konto wird für den %CURRENCY%-Fonds verwendet.")); }
		virtual DString GetMessage_ES_ES() const { return DString(I_("Se utiliza la misma cuenta para el fondo %CURRENCY%.")); }
		virtual DString GetMessage_FR_CA() const { return DString(I_("Le même compte est utilisé pour le fonds %CURRENCY%.")); }
		virtual DString GetMessage_NL_NL() const { return DString(I_("Hetzelfde account is gebruikt voor %CURRENCY% fonds")); }

        // Actions
	};
}



