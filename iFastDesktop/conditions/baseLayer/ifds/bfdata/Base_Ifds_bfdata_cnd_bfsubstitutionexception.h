#pragma once

#include "ConditionObject.h"

namespace CND
{
	class CBase_Ifds_bfdata_cnd_bfsubstitutionexception : public CConditionObject
	{
	public:
		CBase_Ifds_bfdata_cnd_bfsubstitutionexception() { }
		~CBase_Ifds_bfdata_cnd_bfsubstitutionexception() { }

	public:
		// General
		virtual DString GetConditionName() const { return DString(I_("CND_BFSubstitutionException")); }
		virtual DString GetGroupName() const { return DString(I_("ifds")); }
		virtual DString GetModuleName() const { return DString(I_("bfdata")); }
		virtual int GetSeverity() const { return 7; }

		// Messages
		virtual DString GetMessage_EN_US() const { return DString(I_("The value does not correspond to a code value.")); }
		virtual DString GetMessage_DE_DE() const { return DString(I_("“Mit Wirkung vom…”-Datum war nicht eingetragen")); }
		virtual DString GetMessage_ES_ES() const { return DString(I_("The value does not correspond to a code value.")); }
		virtual DString GetMessage_FR_CA() const { return DString(I_("La valeur ne correspond pas à une valeur de code.")); }
		virtual DString GetMessage_NL_NL() const { return DString(I_("The value does not correspond to a code value.")); }

        // Actions
		virtual DString GetAction_EN_US() const { return DString(I_("Correct the value and try again.")); }
		virtual DString GetAction_DE_DE() const { return DString(I_("Correct the value and try again.")); }
		virtual DString GetAction_ES_ES() const { return DString(I_("Correct the value and try again.")); }
		virtual DString GetAction_FR_CA() const { return DString(I_("Corrigez le champ et réessayez.")); }
		virtual DString GetAction_NL_NL() const { return DString(I_("Correct the value and try again.")); }
	};
}



