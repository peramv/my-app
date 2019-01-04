#pragma once

#include "ConditionObject.h"

namespace CND
{
	class CBase_Ifds_bfdata_cnd_digitoverflowexception : public CConditionObject
	{
	public:
		CBase_Ifds_bfdata_cnd_digitoverflowexception() { }
		~CBase_Ifds_bfdata_cnd_digitoverflowexception() { }

	public:
		// General
		virtual DString GetConditionName() const { return DString(I_("CND_DigitOverflowException")); }
		virtual DString GetGroupName() const { return DString(I_("ifds")); }
		virtual DString GetModuleName() const { return DString(I_("bfdata")); }
		virtual int GetSeverity() const { return 7; }

		// Messages
		virtual DString GetMessage_EN_US() const { return DString(I_("There are too many digits in the number.")); }
		virtual DString GetMessage_DE_DE() const { return DString(I_("Ungültiger Fondscode")); }
		virtual DString GetMessage_ES_ES() const { return DString(I_("There are too many digits in the number.")); }
		virtual DString GetMessage_FR_CA() const { return DString(I_("Il y a trop de caractères numériques dans le numéro.")); }
		virtual DString GetMessage_NL_NL() const { return DString(I_("There are too many digits in the number.")); }

        // Actions
		virtual DString GetAction_EN_US() const { return DString(I_("Correct the field and try again.")); }
		virtual DString GetAction_DE_DE() const { return DString(I_("Correct the field and try again.")); }
		virtual DString GetAction_ES_ES() const { return DString(I_("Correct the field and try again.")); }
		virtual DString GetAction_FR_CA() const { return DString(I_("Corrigez le champ et réessayez.")); }
		virtual DString GetAction_NL_NL() const { return DString(I_("Correct the field and try again.")); }
	};
}



