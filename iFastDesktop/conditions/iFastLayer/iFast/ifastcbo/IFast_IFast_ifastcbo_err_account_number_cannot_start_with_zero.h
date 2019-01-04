#pragma once

#include "ConditionObject.h"

namespace CND
{
	class CIFast_IFast_ifastcbo_err_account_number_cannot_start_with_zero : public CConditionObject
	{
	public:
		CIFast_IFast_ifastcbo_err_account_number_cannot_start_with_zero() { }
		~CIFast_IFast_ifastcbo_err_account_number_cannot_start_with_zero() { }

	public:
		// General
		virtual DString GetConditionName() const { return DString(I_("ERR_ACCOUNT_NUMBER_CANNOT_START_WITH_ZERO")); }
		virtual DString GetGroupName() const { return DString(I_("iFast")); }
		virtual DString GetModuleName() const { return DString(I_("ifastcbo")); }
		virtual int GetSeverity() const { return 6; }

		// Messages
		virtual DString GetMessage_EN_US() const { return DString(I_("Account number cannot start with 0.")); }
		virtual DString GetMessage_FR_FR() const { return DString(I_("Le numero de compte ne peut pas commencer par 0.")); }
		virtual DString GetMessage_DE_DE() const { return DString(I_("Die Kontonummer darf nicht mit 0 beginnen.")); }
		virtual DString GetMessage_ES_ES() const { return DString(I_("El número de cuenta no puede comenzar con 0")); }
		virtual DString GetMessage_FR_CA() const { return DString(I_("Le numéro de compte ne peut commencer par zéro.")); }
		virtual DString GetMessage_NL_NL() const { return DString(I_("Accountnummer kan niet met 0 beginnen")); }

        // Actions
	};
}



