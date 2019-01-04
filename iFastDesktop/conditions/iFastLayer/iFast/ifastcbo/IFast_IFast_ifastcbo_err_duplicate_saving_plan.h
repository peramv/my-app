#pragma once

#include "ConditionObject.h"

namespace CND
{
	class CIFast_IFast_ifastcbo_err_duplicate_saving_plan : public CConditionObject
	{
	public:
		CIFast_IFast_ifastcbo_err_duplicate_saving_plan() { }
		~CIFast_IFast_ifastcbo_err_duplicate_saving_plan() { }

	public:
		// General
		virtual DString GetConditionName() const { return DString(I_("ERR_DUPLICATE_SAVING_PLAN")); }
		virtual DString GetGroupName() const { return DString(I_("iFast")); }
		virtual DString GetModuleName() const { return DString(I_("ifastcbo")); }
		virtual int GetSeverity() const { return 6; }

		// Messages
		virtual DString GetMessage_EN_US() const { return DString(I_("The savings plan %PLANCODE% for the same %FUNDNAME% %CLASSNAME% and Effective Date %EFFECDATE% already exists.")); }
		virtual DString GetMessage_DE_DE() const { return DString(I_("Der Sparplan %PLANCODE%für den selben %FUNDNAME%  %CLASSNAME%und Effektivdatum %EFFECDATE% existiert bereits.")); }
		virtual DString GetMessage_ES_ES() const { return DString(I_("El plan de ahorro %PLANCODE% para el mismo %FUNDNAME% %PLANCODE% y la fecha de entrada en vigencia %EFFECDATE% ya existe.")); }
		virtual DString GetMessage_FR_CA() const { return DString(I_("Le régime d'épargne %PLANCODE% pour les mêmes fonds %FUNDNAME%, classe %CLASSNAME% et date d'entrée en vigueur %EFFECDATE% existe déjà.")); }
		virtual DString GetMessage_NL_NL() const { return DString(I_("Het spaarplan %PLANCODE% voor dezelfde %FUNDNAME% %CLASSNAME% en ingangsdatum %EFFECDATE% bestaat al")); }

        // Actions
	};
}



