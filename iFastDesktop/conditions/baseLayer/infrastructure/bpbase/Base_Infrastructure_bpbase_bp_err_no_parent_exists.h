#pragma once

#include "ConditionObject.h"

namespace CND
{
	class CBase_Infrastructure_bpbase_bp_err_no_parent_exists : public CConditionObject
	{
	public:
		CBase_Infrastructure_bpbase_bp_err_no_parent_exists() { }
		~CBase_Infrastructure_bpbase_bp_err_no_parent_exists() { }

	public:
		// General
		virtual DString GetConditionName() const { return DString(I_("BP_ERR_NO_PARENT_EXISTS")); }
		virtual DString GetGroupName() const { return DString(I_("Infrastructure")); }
		virtual DString GetModuleName() const { return DString(I_("bpbase")); }
		virtual int GetSeverity() const { return 7; }

		// Messages
		virtual DString GetMessage_EN_US() const { return DString(I_("The system does not recognize this debit type.")); }
		virtual DString GetMessage_FR_FR() const { return DString(I_("The system does not recognize this debit type.")); }
		virtual DString GetMessage_DE_DE() const { return DString(I_("Das System erkennt diese Lastschriften-Art nicht.")); }
		virtual DString GetMessage_ES_ES() const { return DString(I_("El sistema no reconoce este tipo de débito.")); }
		virtual DString GetMessage_FR_CA() const { return DString(I_("Le système ne reconnaît pas ce type de débit.")); }
		virtual DString GetMessage_NL_NL() const { return DString(I_("Het systeem herkent dit type debet niet")); }

        // Actions
		virtual DString GetAction_EN_US() const { return DString(I_("Verify debit type and re-enter.")); }
		virtual DString GetAction_FR_FR() const { return DString(I_("Verify debit type and re-enter.")); }
		virtual DString GetAction_DE_DE() const { return DString(I_("Überprüfen Sie das Datum und geben Sie es erneut ein.")); }
		virtual DString GetAction_ES_ES() const { return DString(I_("Verifique el tipo de débito y vuelva a introducirla.")); }
		virtual DString GetAction_FR_CA() const { return DString(I_("Vérifiez le type de débit et réessayez.")); }
		virtual DString GetAction_NL_NL() const { return DString(I_("Controleer het type debet en voer dit opnieuw in")); }
	};
}



