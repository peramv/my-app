#pragma once

#include "ConditionObject.h"

namespace CND
{
	class CIFast_IFast_ifastdbrkr_err_fundcode_cannot_be_blank_bank_entity : public CConditionObject
	{
	public:
		CIFast_IFast_ifastdbrkr_err_fundcode_cannot_be_blank_bank_entity() { }
		~CIFast_IFast_ifastdbrkr_err_fundcode_cannot_be_blank_bank_entity() { }

	public:
		// General
		virtual DString GetConditionName() const { return DString(I_("ERR_FUNDCODE_CANNOT_BE_BLANK_BANK_ENTITY")); }
		virtual DString GetGroupName() const { return DString(I_("iFast")); }
		virtual DString GetModuleName() const { return DString(I_("ifastdbrkr")); }
		virtual int GetSeverity() const { return 6; }

		// Messages
		virtual DString GetMessage_EN_US() const { return DString(I_("FundCode cannot be blank for BankingEntity 11.")); }
		virtual DString GetMessage_DE_DE() const { return DString(I_("Fondscode für Banking-Objekt 11 darf nicht leer sein.")); }
		virtual DString GetMessage_ES_ES() const { return DString(I_("El código de fondo no pueden dejarse en blanco para entidad bancaria 11.")); }
		virtual DString GetMessage_FR_CA() const { return DString(I_("Le code de fonds est requis pour l'entité bancaire 11.")); }
		virtual DString GetMessage_NL_NL() const { return DString(I_("Fondscode mag niet leeg zijn voor Bankeenheid 11")); }

        // Actions
	};
}



