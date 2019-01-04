#pragma once

#include "ConditionObject.h"

namespace CND
{
	class CIFast_IFast_ifastdbrkr_err_addr_code_exists_for_entity : public CConditionObject
	{
	public:
		CIFast_IFast_ifastdbrkr_err_addr_code_exists_for_entity() { }
		~CIFast_IFast_ifastdbrkr_err_addr_code_exists_for_entity() { }

	public:
		// General
		virtual DString GetConditionName() const { return DString(I_("ERR_ADDR_CODE_EXISTS_FOR_ENTITY")); }
		virtual DString GetGroupName() const { return DString(I_("iFast")); }
		virtual DString GetModuleName() const { return DString(I_("ifastdbrkr")); }
		virtual int GetSeverity() const { return 6; }

		// Messages
		virtual DString GetMessage_EN_US() const { return DString(I_("Address code already exists for this entity.")); }
		virtual DString GetMessage_DE_DE() const { return DString(I_("Ein Adresscode für dieses Objekt existiert bereits")); }
		virtual DString GetMessage_ES_ES() const { return DString(I_("Ya existe un código de dirección para esta entidad.")); }
		virtual DString GetMessage_FR_CA() const { return DString(I_("Le code d'adresse existe déjà pour l'entité.")); }
		virtual DString GetMessage_NL_NL() const { return DString(I_("Adrescode bestaat al voor deze eenheid")); }

        // Actions
	};
}



