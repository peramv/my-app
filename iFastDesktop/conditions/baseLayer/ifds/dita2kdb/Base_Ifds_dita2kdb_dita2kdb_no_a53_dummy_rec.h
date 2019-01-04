#pragma once

#include "ConditionObject.h"

namespace CND
{
	class CBase_Ifds_dita2kdb_dita2kdb_no_a53_dummy_rec : public CConditionObject
	{
	public:
		CBase_Ifds_dita2kdb_dita2kdb_no_a53_dummy_rec() { }
		~CBase_Ifds_dita2kdb_dita2kdb_no_a53_dummy_rec() { }

	public:
		// General
		virtual DString GetConditionName() const { return DString(I_("DITA2KDB_NO_A53_DUMMY_REC")); }
		virtual DString GetGroupName() const { return DString(I_("ifds")); }
		virtual DString GetModuleName() const { return DString(I_("dita2kdb")); }
		virtual int GetSeverity() const { return 6; }

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



