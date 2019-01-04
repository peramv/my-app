#pragma once

#include "ConditionObject.h"

namespace CND
{
	class CBase_Infrastructure_bpbase_bp_err_list_not_valid : public CConditionObject
	{
	public:
		CBase_Infrastructure_bpbase_bp_err_list_not_valid() { }
		~CBase_Infrastructure_bpbase_bp_err_list_not_valid() { }

	public:
		// General
		virtual DString GetConditionName() const { return DString(I_("BP_ERR_LIST_NOT_VALID")); }
		virtual DString GetGroupName() const { return DString(I_("Infrastructure")); }
		virtual DString GetModuleName() const { return DString(I_("bpbase")); }
		virtual int GetSeverity() const { return 7; }

		// Messages
		virtual DString GetMessage_EN_US() const { return DString(I_("The system does not recognize this alpha code.")); }
		virtual DString GetMessage_FR_FR() const { return DString(I_("The system does not recognize this alpha code.")); }
		virtual DString GetMessage_DE_DE() const { return DString(I_("Das System erkennt diesen Alphacode nicht.")); }
		virtual DString GetMessage_ES_ES() const { return DString(I_("El sistema no reconoce este código alfabético.")); }
		virtual DString GetMessage_FR_CA() const { return DString(I_("Le système ne reconnaît pas ce code alphabétique.")); }
		virtual DString GetMessage_NL_NL() const { return DString(I_("Het systeem herkent deze alfabetische code niet")); }

        // Actions
		virtual DString GetAction_EN_US() const { return DString(I_("Verify alpha code and re-enter.")); }
		virtual DString GetAction_FR_FR() const { return DString(I_("Verify alpha code and re-enter.")); }
		virtual DString GetAction_DE_DE() const { return DString(I_("Überprüfen Sie den Alphacode und geben Sie ihn erneut ein.")); }
		virtual DString GetAction_ES_ES() const { return DString(I_("Verifique el código alfabético y vuelva a introducirlo.")); }
		virtual DString GetAction_FR_CA() const { return DString(I_("Vérifiez le code alphabétique et réessayez.")); }
		virtual DString GetAction_NL_NL() const { return DString(I_("Controleer de alfacode en voer deze opnieuw in")); }
	};
}



