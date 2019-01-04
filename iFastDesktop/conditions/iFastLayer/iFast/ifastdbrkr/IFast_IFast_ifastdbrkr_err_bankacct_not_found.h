#pragma once

#include "ConditionObject.h"

namespace CND
{
	class CIFast_IFast_ifastdbrkr_err_bankacct_not_found : public CConditionObject
	{
	public:
		CIFast_IFast_ifastdbrkr_err_bankacct_not_found() { }
		~CIFast_IFast_ifastdbrkr_err_bankacct_not_found() { }

	public:
		// General
		virtual DString GetConditionName() const { return DString(I_("ERR_BANKACCT_NOT_FOUND")); }
		virtual DString GetGroupName() const { return DString(I_("iFast")); }
		virtual DString GetModuleName() const { return DString(I_("ifastdbrkr")); }
		virtual int GetSeverity() const { return 6; }

		// Messages
		virtual DString GetMessage_EN_US() const { return DString(I_("Request failed due to corresponding banking record is not found.")); }
		virtual DString GetMessage_FR_FR() const { return DString(I_("Request failed due to corresponding banking record is not found.")); }
		virtual DString GetMessage_DE_DE() const { return DString(I_("Anfrage fehlgeschlagen, da der entsprechende Banking-Eintrag nicht gefunden wurde.")); }
		virtual DString GetMessage_ES_ES() const { return DString(I_("Falló la solicitud debido a que no se encontró el registro bancario correspondiente")); }
		virtual DString GetMessage_FR_CA() const { return DString(I_("La requête a échoué car l'enregistrement bancaire correspondant est introuvable.")); }
		virtual DString GetMessage_NL_NL() const { return DString(I_("Opdracht is mislukt omdat het bijbehorende bankrecord niet is gevonden")); }

        // Actions
	};
}



