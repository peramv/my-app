#pragma once

#include "ConditionObject.h"

namespace CND
{
	class CIFast_IFast_ifastdbrkr_err_acct_entity_joint_not_found : public CConditionObject
	{
	public:
		CIFast_IFast_ifastdbrkr_err_acct_entity_joint_not_found() { }
		~CIFast_IFast_ifastdbrkr_err_acct_entity_joint_not_found() { }

	public:
		// General
		virtual DString GetConditionName() const { return DString(I_("ERR_ACCT_ENTITY_JOINT_NOT_FOUND")); }
		virtual DString GetGroupName() const { return DString(I_("iFast")); }
		virtual DString GetModuleName() const { return DString(I_("ifastdbrkr")); }
		virtual int GetSeverity() const { return 6; }

		// Messages
		virtual DString GetMessage_EN_US() const { return DString(I_("Corresponding account entity joint record not found.")); }
		virtual DString GetMessage_FR_FR() const { return DString(I_("Corresponding account entity joint record not found.")); }
		virtual DString GetMessage_DE_DE() const { return DString(I_("Entsprechender Gemeinschafts-Eintrag für das Konto-Objekt nicht gefunden.")); }
		virtual DString GetMessage_ES_ES() const { return DString(I_("No se encontró el registro conjunto de entidad de cuenta correspondiente")); }
		virtual DString GetMessage_FR_CA() const { return DString(I_("L'enregistrement conjoint de l'entité du compte correspondant est introuvable.")); }
		virtual DString GetMessage_NL_NL() const { return DString(I_("Bijbehorende gezamenlijk record voor accounteenheid is niet gevonden")); }

        // Actions
	};
}



