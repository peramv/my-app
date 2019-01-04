#pragma once

#include "ConditionObject.h"

namespace CND
{
	class CIFast_IFast_ifastcbo_err_deposit_type_must_be_06_or_07 : public CConditionObject
	{
	public:
		CIFast_IFast_ifastcbo_err_deposit_type_must_be_06_or_07() { }
		~CIFast_IFast_ifastcbo_err_deposit_type_must_be_06_or_07() { }

	public:
		// General
		virtual DString GetConditionName() const { return DString(I_("ERR_DEPOSIT_TYPE_MUST_BE_06_OR_07")); }
		virtual DString GetGroupName() const { return DString(I_("iFast")); }
		virtual DString GetModuleName() const { return DString(I_("ifastcbo")); }
		virtual int GetSeverity() const { return 6; }

		// Messages
		virtual DString GetMessage_EN_US() const { return DString(I_("Deposit type must be 06 or 07.")); }
		virtual DString GetMessage_DE_DE() const { return DString(I_("Depot-Typ muss 06 oder 07 sein.")); }
		virtual DString GetMessage_ES_ES() const { return DString(I_("El tipo de depósito debe ser 06 ó 07.")); }
		virtual DString GetMessage_FR_CA() const { return DString(I_("Le code de dépôt doit être 06 ou 07.")); }
		virtual DString GetMessage_NL_NL() const { return DString(I_("Depositotype moet 06 of 07 zijn")); }

        // Actions
	};
}



