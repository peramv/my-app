#pragma once

#include "ConditionObject.h"

namespace CND
{
	class CIFast_IFast_dicbocore_err_unknown_exception : public CConditionObject
	{
	public:
		CIFast_IFast_dicbocore_err_unknown_exception() { }
		~CIFast_IFast_dicbocore_err_unknown_exception() { }

	public:
		// General
		virtual DString GetConditionName() const { return DString(I_("ERR_UNKNOWN_EXCEPTION")); }
		virtual DString GetGroupName() const { return DString(I_("iFast")); }
		virtual DString GetModuleName() const { return DString(I_("dicbocore")); }
		virtual int GetSeverity() const { return 6; }

		// Messages
		virtual DString GetMessage_EN_US() const { return DString(I_("Fund %FUNDNAME% is not effective.")); }
		virtual DString GetMessage_FR_FR() const { return DString(I_("Le fond %FUNDNAME% n'est pas actif. Veuillez sélectionner un autre fonds.")); }
		virtual DString GetMessage_DE_DE() const { return DString(I_("Fonds %FUNDNAME% ist nicht wirksam. Bitte wählen Sie einen anderen Fonds.")); }
		virtual DString GetMessage_ES_ES() const { return DString(I_("El fondo %FUNDNAME% no entró en vigencia. Por favor seleccione otro fondo.")); }
		virtual DString GetMessage_FR_CA() const { return DString(I_("Le fonds %FUNDNAME% n'est pas en vigueur.")); }
		virtual DString GetMessage_NL_NL() const { return DString(I_("Fonds %FUNDNAME% is niet van kracht. Selecteer een ander fonds")); }

        // Actions
	};
}



