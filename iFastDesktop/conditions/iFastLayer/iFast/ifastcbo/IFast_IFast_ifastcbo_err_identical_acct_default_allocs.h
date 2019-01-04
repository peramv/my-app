#pragma once

#include "ConditionObject.h"

namespace CND
{
	class CIFast_IFast_ifastcbo_err_identical_acct_default_allocs : public CConditionObject
	{
	public:
		CIFast_IFast_ifastcbo_err_identical_acct_default_allocs() { }
		~CIFast_IFast_ifastcbo_err_identical_acct_default_allocs() { }

	public:
		// General
		virtual DString GetConditionName() const { return DString(I_("ERR_IDENTICAL_ACCT_DEFAULT_ALLOCS")); }
		virtual DString GetGroupName() const { return DString(I_("iFast")); }
		virtual DString GetModuleName() const { return DString(I_("ifastcbo")); }
		virtual int GetSeverity() const { return 6; }

		// Messages
		virtual DString GetMessage_EN_US() const { return DString(I_("Account allocations must differ in account number.")); }
		virtual DString GetMessage_FR_FR() const { return DString(I_("Account allocations must differ in account number.")); }
		virtual DString GetMessage_DE_DE() const { return DString(I_("Konto-Zuweisungen müssen sich in der Kontonummer unterscheiden.")); }
		virtual DString GetMessage_ES_ES() const { return DString(I_("Las asignaciones de cuentas deben diferir en número de cuenta.")); }
		virtual DString GetMessage_FR_CA() const { return DString(I_("Les répartitions du compte doivent différer en numéro de compte.")); }
		virtual DString GetMessage_NL_NL() const { return DString(I_("Accountallocaties moeten een verschillend accountnummer hebben")); }

        // Actions
	};
}



