﻿#pragma once

#include "ConditionObject.h"

namespace CND
{
	class CIFast_IFast_ifastcbo_err_invalid_fund_class_codes : public CConditionObject
	{
	public:
		CIFast_IFast_ifastcbo_err_invalid_fund_class_codes() { }
		~CIFast_IFast_ifastcbo_err_invalid_fund_class_codes() { }

	public:
		// General
		virtual DString GetConditionName() const { return DString(I_("ERR_INVALID_FUND_CLASS_CODES")); }
		virtual DString GetGroupName() const { return DString(I_("iFast")); }
		virtual DString GetModuleName() const { return DString(I_("ifastcbo")); }
		virtual int GetSeverity() const { return 6; }

		// Messages
		virtual DString GetMessage_EN_US() const { return DString(I_("Invalid fund/class code.")); }
		virtual DString GetMessage_FR_FR() const { return DString(I_("Code de fonds et de catégorie invalides. Veuillez ressaisir.")); }
		virtual DString GetMessage_DE_DE() const { return DString(I_("Ungültiger Fonds/Klassencode. Bitte wählen Sie neu.")); }
		virtual DString GetMessage_ES_ES() const { return DString(I_("Código de fondo/clase no válido. Por favor vuelva a seleccionar otra opción.")); }
		virtual DString GetMessage_FR_CA() const { return DString(I_("Code de fonds/classe invalide")); }
		virtual DString GetMessage_NL_NL() const { return DString(I_("Ongeldige fonds- of categoriecode Selecteer opnieuw")); }

        // Actions
	};
}



