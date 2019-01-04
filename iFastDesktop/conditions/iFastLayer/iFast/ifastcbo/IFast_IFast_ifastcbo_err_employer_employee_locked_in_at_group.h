#pragma once

#include "ConditionObject.h"

namespace CND
{
	class CIFast_IFast_ifastcbo_err_employer_employee_locked_in_at_group : public CConditionObject
	{
	public:
		CIFast_IFast_ifastcbo_err_employer_employee_locked_in_at_group() { }
		~CIFast_IFast_ifastcbo_err_employer_employee_locked_in_at_group() { }

	public:
		// General
		virtual DString GetConditionName() const { return DString(I_("ERR_EMPLOYER_EMPLOYEE_LOCKED_IN_AT_GROUP")); }
		virtual DString GetGroupName() const { return DString(I_("iFast")); }
		virtual DString GetModuleName() const { return DString(I_("ifastcbo")); }
		virtual int GetSeverity() const { return 5; }

		// Messages
		virtual DString GetMessage_EN_US() const { return DString(I_("Employer and Employee locked-in flags are both on at group level.")); }
		virtual DString GetMessage_DE_DE() const { return DString(I_("Employer and Employee locked-in flags are both on at group level.")); }
		virtual DString GetMessage_ES_ES() const { return DString(I_("Employer and Employee locked-in flags are both on at group level.")); }
		virtual DString GetMessage_FR_CA() const { return DString(I_("Le signal d'immobilisation de l'employé et de l'employeur sont tous deux activés au niveau du groupe.")); }

        // Actions
	};
}



