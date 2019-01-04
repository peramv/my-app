#pragma once

#include "ConditionObject.h"

namespace CND
{
	class CIFast_IFast_ifastcbo_err_annitant_birthday_not_found : public CConditionObject
	{
	public:
		CIFast_IFast_ifastcbo_err_annitant_birthday_not_found() { }
		~CIFast_IFast_ifastcbo_err_annitant_birthday_not_found() { }

	public:
		// General
		virtual DString GetConditionName() const { return DString(I_("ERR_ANNITANT_BIRTHDAY_NOT_FOUND")); }
		virtual DString GetGroupName() const { return DString(I_("iFast")); }
		virtual DString GetModuleName() const { return DString(I_("ifastcbo")); }
		virtual int GetSeverity() const { return 6; }

		// Messages
		virtual DString GetMessage_EN_US() const { return DString(I_("Annuitant's Date of Birth is not found.")); }
		virtual DString GetMessage_DE_DE() const { return DString(I_("Geburtsdatum des Rentenempfängers nicht gefunden.")); }
		virtual DString GetMessage_ES_ES() const { return DString(I_("No se encontró la fecha de nacimiento del titular de la anualidad.")); }
		virtual DString GetMessage_FR_CA() const { return DString(I_("La date de naissance du crédirentier est introuvable.")); }
		virtual DString GetMessage_NL_NL() const { return DString(I_("Geboortedatum lijfrentetrekker is niet gevonden")); }

        // Actions
	};
}



