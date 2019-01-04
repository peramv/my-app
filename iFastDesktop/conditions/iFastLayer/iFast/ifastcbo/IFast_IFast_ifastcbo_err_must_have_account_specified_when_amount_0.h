#pragma once

#include "ConditionObject.h"

namespace CND
{
	class CIFast_IFast_ifastcbo_err_must_have_account_specified_when_amount_0 : public CConditionObject
	{
	public:
		CIFast_IFast_ifastcbo_err_must_have_account_specified_when_amount_0() { }
		~CIFast_IFast_ifastcbo_err_must_have_account_specified_when_amount_0() { }

	public:
		// General
		virtual DString GetConditionName() const { return DString(I_("ERR_MUST_HAVE_ACCOUNT_SPECIFIED_WHEN_AMOUNT_0")); }
		virtual DString GetGroupName() const { return DString(I_("iFast")); }
		virtual DString GetModuleName() const { return DString(I_("ifastcbo")); }
		virtual int GetSeverity() const { return 1; }

		// Messages
		virtual DString GetMessage_EN_US() const { return DString(I_("Must have account specified when amount is zero.")); }
		virtual DString GetMessage_DE_DE() const { return DString(I_("Ein Konto muss festgelegt sein, wenn der Betrag null ist.")); }
		virtual DString GetMessage_ES_ES() const { return DString(I_("Debe tener una cuenta especificada cuando el monto es cero")); }
		virtual DString GetMessage_FR_CA() const { return DString(I_("Un compte doit être spécifié lorsque le montant est de zéro.")); }
		virtual DString GetMessage_NL_NL() const { return DString(I_("Er moet een account zijn opgegeven als het bedrag nul is")); }

        // Actions
	};
}



