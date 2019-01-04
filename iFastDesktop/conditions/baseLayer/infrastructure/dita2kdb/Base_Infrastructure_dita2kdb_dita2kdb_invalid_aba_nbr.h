#pragma once

#include "ConditionObject.h"

namespace CND
{
	class CBase_Infrastructure_dita2kdb_dita2kdb_invalid_aba_nbr : public CConditionObject
	{
	public:
		CBase_Infrastructure_dita2kdb_dita2kdb_invalid_aba_nbr() { }
		~CBase_Infrastructure_dita2kdb_dita2kdb_invalid_aba_nbr() { }

	public:
		// General
		virtual DString GetConditionName() const { return DString(I_("DITA2KDB_INVALID_ABA_NBR")); }
		virtual DString GetGroupName() const { return DString(I_("Infrastructure")); }
		virtual DString GetModuleName() const { return DString(I_("dita2kdb")); }
		virtual int GetSeverity() const { return 6; }

		// Messages
		virtual DString GetMessage_EN_US() const { return DString(I_("Invalid bank number.  CICS return code is %rc%.")); }
		virtual DString GetMessage_DE_DE() const { return DString(I_("Invalid bank number.  CICS return code is %rc%.")); }
		virtual DString GetMessage_ES_ES() const { return DString(I_("Invalid bank number.  CICS return code is %rc%.")); }
		virtual DString GetMessage_FR_CA() const { return DString(I_("Numéro de banque invalide. Le code de renvoi CICS est %rc%.")); }

        // Actions
		virtual DString GetAction_EN_US() const { return DString(I_("Verify bank number and re-enter.")); }
		virtual DString GetAction_DE_DE() const { return DString(I_("Verify bank number and re-enter.")); }
		virtual DString GetAction_ES_ES() const { return DString(I_("Verify bank number and re-enter.")); }
		virtual DString GetAction_FR_CA() const { return DString(I_("Vérifiez le numéro bancaire et réessayez.")); }
	};
}



