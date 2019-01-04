#pragma once

#include "ConditionObject.h"

namespace CND
{
	class CIFast_IFast_ifastcbo_err_warn_acctholder_birthday_missing_nocheck : public CConditionObject
	{
	public:
		CIFast_IFast_ifastcbo_err_warn_acctholder_birthday_missing_nocheck() { }
		~CIFast_IFast_ifastcbo_err_warn_acctholder_birthday_missing_nocheck() { }

	public:
		// General
		virtual DString GetConditionName() const { return DString(I_("ERR_WARN_ACCTHOLDER_BIRTHDAY_MISSING_NOCHECK")); }
		virtual DString GetGroupName() const { return DString(I_("iFast")); }
		virtual DString GetModuleName() const { return DString(I_("ifastcbo")); }
		virtual int GetSeverity() const { return 5; }

		// Messages
		virtual DString GetMessage_EN_US() const { return DString(I_("Accountholder's birth date is missing.  An age check cannot be done.")); }
		virtual DString GetMessage_DE_DE() const { return DString(I_("Accountholder's birth date is missing.  An age check cannot be done.")); }
		virtual DString GetMessage_FR_CA() const { return DString(I_("La date de naissance du titulaire du compte est manquante. Une vérification  de l'âge ne peut être faite.")); }

        // Actions
	};
}



