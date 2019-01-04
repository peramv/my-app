#pragma once

#include "ConditionObject.h"

namespace CND
{
	class CBase_Infrastructure_bpbase_bp_err_unknown_exception : public CConditionObject
	{
	public:
		CBase_Infrastructure_bpbase_bp_err_unknown_exception() { }
		~CBase_Infrastructure_bpbase_bp_err_unknown_exception() { }

	public:
		// General
		virtual DString GetConditionName() const { return DString(I_("BP_ERR_UNKNOWN_EXCEPTION")); }
		virtual DString GetGroupName() const { return DString(I_("Infrastructure")); }
		virtual DString GetModuleName() const { return DString(I_("bpbase")); }
		virtual int GetSeverity() const { return 7; }

		// Messages
		virtual DString GetMessage_EN_US() const { return DString(I_("The system does not recognize this transaction number.")); }
		virtual DString GetMessage_FR_FR() const { return DString(I_("The system does not recognize this transaction number.")); }
		virtual DString GetMessage_DE_DE() const { return DString(I_("Das System erkennt diese Transaktionsnummer nicht.")); }
		virtual DString GetMessage_ES_ES() const { return DString(I_("El sistema no reconoce este número de transacción.")); }
		virtual DString GetMessage_FR_CA() const { return DString(I_("Le système ne reconnaît pas ce numéro de transaction.")); }
		virtual DString GetMessage_NL_NL() const { return DString(I_("Het systeem herkent dit transactienummer niet")); }

        // Actions
		virtual DString GetAction_EN_US() const { return DString(I_("Verify number and re-enter.")); }
		virtual DString GetAction_FR_FR() const { return DString(I_("Verify number and re-enter.")); }
		virtual DString GetAction_DE_DE() const { return DString(I_("Bestätigen Sie die Nummer und geben Sie sie erneut ein.")); }
		virtual DString GetAction_ES_ES() const { return DString(I_("Verifique el número y vuelva a introducirlo.")); }
		virtual DString GetAction_FR_CA() const { return DString(I_("Vérifiez le numéro et réessayez.")); }
		virtual DString GetAction_NL_NL() const { return DString(I_("Controleer het nummer en voer dit opnieuw in")); }
	};
}



