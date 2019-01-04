#pragma once

#include "ConditionObject.h"

namespace CND
{
	class CIFast_IFast_ditabuscore_err_invalid_zipcode : public CConditionObject
	{
	public:
		CIFast_IFast_ditabuscore_err_invalid_zipcode() { }
		~CIFast_IFast_ditabuscore_err_invalid_zipcode() { }

	public:
		// General
		virtual DString GetConditionName() const { return DString(I_("ERR_INVALID_ZIPCODE")); }
		virtual DString GetGroupName() const { return DString(I_("iFast")); }
		virtual DString GetModuleName() const { return DString(I_("ditabuscore")); }
		virtual int GetSeverity() const { return 6; }

		// Messages
		virtual DString GetMessage_EN_US() const { return DString(I_("Account use code in this currency already exist.")); }
		virtual DString GetMessage_FR_FR() const { return DString(I_("Le code d'utilisation de compte dans cette devise existe deja. Veuillez resélectionner.")); }
		virtual DString GetMessage_DE_DE() const { return DString(I_("Konto-Nutzungscode existiert bereits in dieser Währung. Bitte wählen Sie neu.")); }
		virtual DString GetMessage_ES_ES() const { return DString(I_("El código de uso de cuenta en esta divisa ya existe. Por favor seleccione otro código.")); }
		virtual DString GetMessage_FR_CA() const { return DString(I_("Le code d'utilisation de cette monnaie pour le compte existe déjà.")); }
		virtual DString GetMessage_NL_NL() const { return DString(I_("Gebruikerscode account in deze valuta bestaat al. Selecteer opnieuw")); }

        // Actions
	};
}



