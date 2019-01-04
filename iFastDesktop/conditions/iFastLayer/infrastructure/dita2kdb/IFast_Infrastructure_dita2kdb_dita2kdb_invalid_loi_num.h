#pragma once

#include "ConditionObject.h"

namespace CND
{
	class CIFast_Infrastructure_dita2kdb_dita2kdb_invalid_loi_num : public CConditionObject
	{
	public:
		CIFast_Infrastructure_dita2kdb_dita2kdb_invalid_loi_num() { }
		~CIFast_Infrastructure_dita2kdb_dita2kdb_invalid_loi_num() { }

	public:
		// General
		virtual DString GetConditionName() const { return DString(I_("DITA2KDB_INVALID_LOI_NUM")); }
		virtual DString GetGroupName() const { return DString(I_("Infrastructure")); }
		virtual DString GetModuleName() const { return DString(I_("dita2kdb")); }
		virtual int GetSeverity() const { return 6; }

		// Messages
		virtual DString GetMessage_EN_US() const { return DString(I_("The system does not recognize this LOI number.")); }
		virtual DString GetMessage_FR_FR() const { return DString(I_("The system does not recognize this LOI number.")); }
		virtual DString GetMessage_DE_DE() const { return DString(I_("Das System erkennt diese LOI-Nummer nicht.")); }
		virtual DString GetMessage_ES_ES() const { return DString(I_("El sistema no reconoce este número de LOI.")); }
		virtual DString GetMessage_FR_CA() const { return DString(I_("Le système ne reconnaît pas ce numéro de lettre d'indemnisation.")); }
		virtual DString GetMessage_NL_NL() const { return DString(I_("Het systeem herkent dit LOI-nummer niet")); }

        // Actions
		virtual DString GetAction_EN_US() const { return DString(I_("Verify LOI number and re-enter.")); }
		virtual DString GetAction_FR_FR() const { return DString(I_("Verify LOI number and re-enter.")); }
		virtual DString GetAction_DE_DE() const { return DString(I_("Bestätigen Sie die LOI-Nummer und geben Sie sie erneut ein.")); }
		virtual DString GetAction_ES_ES() const { return DString(I_("Verify LOI number and re-enter.")); }
		virtual DString GetAction_FR_CA() const { return DString(I_("Vérifiez le numéro de lettre d'indemnisation et réessayez.")); }
		virtual DString GetAction_NL_NL() const { return DString(I_("Controleer het LOI-nummer en voer dit opnieuw in")); }
	};
}



