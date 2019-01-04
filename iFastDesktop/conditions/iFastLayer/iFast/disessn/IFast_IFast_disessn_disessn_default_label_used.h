#pragma once

#include "ConditionObject.h"

namespace CND
{
	class CIFast_IFast_disessn_disessn_default_label_used : public CConditionObject
	{
	public:
		CIFast_IFast_disessn_disessn_default_label_used() { }
		~CIFast_IFast_disessn_disessn_default_label_used() { }

	public:
		// General
		virtual DString GetConditionName() const { return DString(I_("DISESSN_DEFAULT_LABEL_USED")); }
		virtual DString GetGroupName() const { return DString(I_("iFast")); }
		virtual DString GetModuleName() const { return DString(I_("disessn")); }
		virtual int GetSeverity() const { return 5; }

		// Messages
		virtual DString GetMessage_EN_US() const { return DString(I_("Shareholder Number must not be greater than 6 digits.")); }
		virtual DString GetMessage_FR_FR() const { return DString(I_("Shareholder Number must not be greater than 6 digits.")); }
		virtual DString GetMessage_DE_DE() const { return DString(I_("Aktionärsnummer darf nicht länger als sechs Stellen sein")); }
		virtual DString GetMessage_ES_ES() const { return DString(I_("El número de accionista no puede tener más de 6 dígitos.")); }
		virtual DString GetMessage_FR_CA() const { return DString(I_("Le numéro d'actionnaire ne doit pas dépasser 6 caractères numériques.")); }
		virtual DString GetMessage_NL_NL() const { return DString(I_("Nummer aandeelhouder mag niet groter dan zes cijfers zijn")); }

        // Actions
	};
}



