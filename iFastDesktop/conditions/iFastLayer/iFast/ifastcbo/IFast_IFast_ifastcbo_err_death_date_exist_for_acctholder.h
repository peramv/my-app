#pragma once

#include "ConditionObject.h"

namespace CND
{
	class CIFast_IFast_ifastcbo_err_death_date_exist_for_acctholder : public CConditionObject
	{
	public:
		CIFast_IFast_ifastcbo_err_death_date_exist_for_acctholder() { }
		~CIFast_IFast_ifastcbo_err_death_date_exist_for_acctholder() { }

	public:
		// General
		virtual DString GetConditionName() const { return DString(I_("ERR_DEATH_DATE_EXIST_FOR_ACCTHOLDER")); }
		virtual DString GetGroupName() const { return DString(I_("iFast")); }
		virtual DString GetModuleName() const { return DString(I_("ifastcbo")); }
		virtual int GetSeverity() const { return 6; }

		// Messages
		virtual DString GetMessage_EN_US() const { return DString(I_("Death Date exists for accountholder.")); }
		virtual DString GetMessage_DE_DE() const { return DString(I_("Todesdatum existiert für Kontoinhaber")); }
		virtual DString GetMessage_ES_ES() const { return DString(I_("Existe una fecha de fallecimiento para el titular de la cuenta")); }
		virtual DString GetMessage_FR_CA() const { return DString(I_("Date de décès existante pour le titulaire du compte")); }
		virtual DString GetMessage_NL_NL() const { return DString(I_("Overlijdensdatum bestaat voor accounthouder")); }

        // Actions
	};
}



