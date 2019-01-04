#pragma once

#include "ConditionObject.h"

namespace CND
{
	class CIFast_IFast_ifastcbo_err_accountholder_death_date_required : public CConditionObject
	{
	public:
		CIFast_IFast_ifastcbo_err_accountholder_death_date_required() { }
		~CIFast_IFast_ifastcbo_err_accountholder_death_date_required() { }

	public:
		// General
		virtual DString GetConditionName() const { return DString(I_("ERR_ACCOUNTHOLDER_DEATH_DATE_REQUIRED")); }
		virtual DString GetGroupName() const { return DString(I_("iFast")); }
		virtual DString GetModuleName() const { return DString(I_("ifastcbo")); }
		virtual int GetSeverity() const { return 6; }

		// Messages
		virtual DString GetMessage_EN_US() const { return DString(I_("Accountholder's death date must be entered.")); }
		virtual DString GetMessage_DE_DE() const { return DString(I_("Sterbedatum des Kontoinhabers muss eingegeben werden.")); }
		virtual DString GetMessage_ES_ES() const { return DString(I_("Debe introducirse la fecha de fallecimiento del titular de la cuenta")); }
		virtual DString GetMessage_FR_CA() const { return DString(I_("La date de décès du titulaire du compte est requise.")); }
		virtual DString GetMessage_NL_NL() const { return DString(I_("Overlijdensdatum accounthouder moet worden ingevoerd")); }

        // Actions
	};
}



