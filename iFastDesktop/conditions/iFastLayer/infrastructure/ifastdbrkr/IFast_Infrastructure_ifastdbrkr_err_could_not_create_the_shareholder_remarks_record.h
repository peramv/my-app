#pragma once

#include "ConditionObject.h"

namespace CND
{
	class CIFast_Infrastructure_ifastdbrkr_err_could_not_create_the_shareholder_remarks_record : public CConditionObject
	{
	public:
		CIFast_Infrastructure_ifastdbrkr_err_could_not_create_the_shareholder_remarks_record() { }
		~CIFast_Infrastructure_ifastdbrkr_err_could_not_create_the_shareholder_remarks_record() { }

	public:
		// General
		virtual DString GetConditionName() const { return DString(I_("ERR_COULD_NOT_CREATE_THE_SHAREHOLDER_REMARKS_RECORD")); }
		virtual DString GetGroupName() const { return DString(I_("Infrastructure")); }
		virtual DString GetModuleName() const { return DString(I_("ifastdbrkr")); }
		virtual int GetSeverity() const { return 6; }

		// Messages
		virtual DString GetMessage_EN_US() const { return DString(I_("The system does not recognize reinvest dollar.")); }
		virtual DString GetMessage_FR_FR() const { return DString(I_("The system does not recognize reinvest dollar.")); }
		virtual DString GetMessage_DE_DE() const { return DString(I_("Das System erkennt Dollar-Wiederanlage nicht.")); }
		virtual DString GetMessage_ES_ES() const { return DString(I_("The system does not recognize reinvest dollar.")); }
		virtual DString GetMessage_FR_CA() const { return DString(I_("Le système ne reconnaît pas le dollar réinvesti.")); }
		virtual DString GetMessage_NL_NL() const { return DString(I_("The system does not recognize reinvest dollar")); }

        // Actions
		virtual DString GetAction_EN_US() const { return DString(I_("Verify reinvest dollar and re-enter.")); }
		virtual DString GetAction_FR_FR() const { return DString(I_("Verify reinvest dollar and re-enter.")); }
		virtual DString GetAction_DE_DE() const { return DString(I_("Überprüfen Sie die Dollar-Wiederanlage und geben Sie sie erneut ein.")); }
		virtual DString GetAction_ES_ES() const { return DString(I_("Verify reinvest dollar and re-enter.")); }
		virtual DString GetAction_FR_CA() const { return DString(I_("Vérifiez le dollar réinvesti et réessayez.")); }
		virtual DString GetAction_NL_NL() const { return DString(I_("Controleer het herinvesteringsbedrag en voer dit opnieuw in")); }
	};
}



