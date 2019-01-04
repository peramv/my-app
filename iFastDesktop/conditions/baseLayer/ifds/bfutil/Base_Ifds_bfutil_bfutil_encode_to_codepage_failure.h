#pragma once

#include "ConditionObject.h"

namespace CND
{
	class CBase_Ifds_bfutil_bfutil_encode_to_codepage_failure : public CConditionObject
	{
	public:
		CBase_Ifds_bfutil_bfutil_encode_to_codepage_failure() { }
		~CBase_Ifds_bfutil_bfutil_encode_to_codepage_failure() { }

	public:
		// General
		virtual DString GetConditionName() const { return DString(I_("BFUTIL_ENCODE_TO_CODEPAGE_FAILURE")); }
		virtual DString GetGroupName() const { return DString(I_("ifds")); }
		virtual DString GetModuleName() const { return DString(I_("bfutil")); }
		virtual int GetSeverity() const { return 7; }

		// Messages
		virtual DString GetMessage_EN_US() const { return DString(I_("Could not convert a string to unicode for CodePage %CODEPAGE%.  Reason: %RC%.")); }
		virtual DString GetMessage_DE_DE() const { return DString(I_("Kontoart kann nicht geändert werden – für dieses Konto existieren Transaktionen.")); }
		virtual DString GetMessage_ES_ES() const { return DString(I_("La cadena recibida no se puede convertir correctamente en unicode (%CODEPAGE%/%RC%).")); }
		virtual DString GetMessage_FR_CA() const { return DString(I_("Impossible de convertir une chaîne à Unicode pour la page de codes %CODEPAGE%. Raison : %RC%")); }
		virtual DString GetMessage_NL_NL() const { return DString(I_("De ontvangen string kan niet juist worden geconverteerd naar een unicode(%CODEPAGE%/%RC%).")); }

        // Actions
		virtual DString GetAction_EN_US() const { return DString(I_("Report this error to the help desk.")); }
		virtual DString GetAction_DE_DE() const { return DString(I_("Report this error to the help desk.")); }
		virtual DString GetAction_FR_CA() const { return DString(I_("Signalez cette erreur au centre d'assistance.")); }
		virtual DString GetAction_NL_NL() const { return DString(I_("Neem contact op met een supportmedewerker en meld dit bericht.")); }
	};
}



